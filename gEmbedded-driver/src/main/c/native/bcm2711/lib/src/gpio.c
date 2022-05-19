#include "com_comert_gEmbedded_nativeinterface_GPIOController.h"
#include "gpio.h"
#include "jninative.h"
#include <fcntl.h>
#include <unistd.h>
#include <linux/gpio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <poll.h>
#include "common.h"
#include "mapper.h"

#define GPIO_BASE_ADDRESS   (PERIPHERAL_BASE_ADDRESS + 0x200000)
#define GPIO_BLOCK_SIZE     (0xF4)
#define GPIO_CHIP           ("/dev/gpiochip0")
#define GPIO_PIN_SIZE       (30)

#define FALLING             (0)
#define RISING              (1)
#define READ_ERROR          (2)
#define POLL_TIMEOUT        (3)
#define POLL_ERROR          (4)

typedef enum GPIO_PIN_FUNCTION_ {
    INPUT = 0b000,
    OUTPUT = 0b001,
    ALT0 = 0b100,
    ALT1 = 0b101,
    ALT2 = 0b110,
    ALT3 = 0b111,
    ALT4 = 0b011,
    ALT5 = 0b010
} GPIO_PIN_FUNCTION;

typedef enum GPIO_PUD_STATUS_ {
    NONE = 0,
    PULL_UP = 1,
    PULL_DOWN = 2,
    DEFAULT = 2,
    RESERVED = 3
} GPIO_PUD_STATUS;

typedef struct GPIORegisters_ {
    reg GPFSEL[6];
    reg Reserved1;
    reg GPSET[2];
    reg Reserved2;
    reg GPCLR[2];
    reg Reserved3;
    reg GPLEV[2];
    reg Reserved4;
    reg GPEDS[2];
    reg Reserved5;
    reg GPREN[2];
    reg Reserved6;
    reg GPFEN[2];
    reg Reserved7;
    reg GPHEN[2];
    reg Reserved8;
    reg GPLEN[2];
    reg Reserved9;
    reg GPAREN[2];
    reg Reserved10;
    reg GPAFEN[2];
    reg Reserved11[21];
    reg PUD[4];
} GPIORegisters;

GPIORegisters *gpioRegisters;

typedef struct GPIOEvents_ {
    struct gpioevent_request request;
    struct gpioevent_data data;
    struct pollfd pollFd;
} GPIOEvents;

static GPIOEvents gpioEvents[GPIO_PIN_SIZE];

JNIEXPORT void JNICALL Java_com_comert_gEmbedded_nativeinterface_GPIOController_setPinFunction
        (JNIEnv *env, const jclass GPIOController, jobject pin, jobject pinFunction) {

    jint pinNumberToSet, pinFunctionToSet;

    const register JNI_STATUS pinStatus = jniController.getEnumDigit (env, pin, &pinNumberToSet);
    if (pinStatus == JNI_ERROR) {
        return;
    }

    const register JNI_STATUS pinFunctionStatus = jniController.getEnumDigit (env, pinFunction, &pinFunctionToSet);

    if (pinFunctionStatus == JNI_ERROR) {
        return;
    }

    const register reg_t registerSelector = pinNumberToSet / 10;

    switch (pinFunctionToSet) {
        case 0: {
            pinFunctionToSet = ALT0;
            break;
        }
        case 1: {
            pinFunctionToSet = ALT1;
            break;
        }
        case 2: {
            pinFunctionToSet = ALT2;
            break;
        }
        case 3: {
            pinFunctionToSet = ALT3;
            break;
        }
        case 4: {
            pinFunctionToSet = ALT4;
            break;
        }
        case 5: {
            pinFunctionToSet = ALT5;
            break;
        }
        case 6: {
            pinFunctionToSet = INPUT;
            break;
        }
        case 7: {
            pinFunctionToSet = OUTPUT;
            break;
        }
        default: {
            jniController.throwANewJNIException (env, "Not supported pin function");
            return;
        }
    }

    gpioRegisters->GPFSEL[registerSelector] &= ~(7 << ((pinNumberToSet % 10) * 3));
    gpioRegisters->GPFSEL[registerSelector] |= (pinFunctionToSet << ((pinNumberToSet % 10) * 3));

}

JNIEXPORT void JNICALL Java_com_comert_gEmbedded_nativeinterface_GPIOController_setPullUpDownStatus
        (JNIEnv *env, const jclass GPIOController, jobject pin, jobject pullUpDownStatus) {

    jint pinNumberToSet, pullUpDownStatusToSet;

    const register JNI_STATUS pinStatus = jniController.getEnumDigit (env, pin, &pinNumberToSet);
    if (pinStatus == JNI_ERROR) {
        return;
    }

    const register JNI_STATUS pullUpDownStatusStatus = jniController.getEnumDigit
            (env, pullUpDownStatus, &pullUpDownStatusToSet);
    if (pullUpDownStatusStatus == JNI_ERROR) {
        return;
    }

    const register reg_t registerSelector = pinNumberToSet / 16;

    switch (pullUpDownStatusToSet) {
        case 0: {
            pullUpDownStatusToSet = NONE;
            break;
        }
        case 1: {
            pullUpDownStatusToSet = PULL_UP;
            break;
        }
        case 2: {
            pullUpDownStatusToSet = PULL_DOWN;
            break;
        }
        case 3: {
            pullUpDownStatusToSet = DEFAULT;
            break;
        }
        case 4: {
            pullUpDownStatusToSet = RESERVED;
            break;
        }
        default: {
            jniController.throwANewJNIException (env, "Not supported pull-up, pull-down status");
            return;
        }
    }

    gpioRegisters->PUD[registerSelector] &= ~(3 << ((pinNumberToSet % 16) * 2));
    gpioRegisters->PUD[registerSelector] |= (pullUpDownStatusToSet << ((pinNumberToSet % 16) * 2));

}

JNIEXPORT void JNICALL Java_com_comert_gEmbedded_nativeinterface_GPIOController_setEventDetectStatus
        (JNIEnv *env, const jclass GPIOController, jobject pin, jobject eventDetectStatus) {

    jint pinNumberToSet, eventDetectStatusToSet;

    const register JNI_STATUS pinStatus = jniController.getEnumDigit (env, pin, &pinNumberToSet);
    if (pinStatus == JNI_ERROR) {
        return;
    }

    const register JNI_STATUS eventDetectStatusStatus = jniController.getEnumDigit
            (env, eventDetectStatus, &eventDetectStatusToSet);
    if (eventDetectStatusStatus == JNI_ERROR) {
        return;
    }

    int fileDescriptor = open (GPIO_CHIP, O_WRONLY);
    if (fileDescriptor < 0) {
        close (fileDescriptor);
        jniController.throwANewJNIException (env, "GPIO chip file could not be opened");
        return;
    }

    gpioEvents[pinNumberToSet].request.lineoffset = pinNumberToSet;
    gpioEvents[pinNumberToSet].request.handleflags = GPIOHANDLE_REQUEST_INPUT;
    switch (eventDetectStatusToSet) {
        case 1: {
            gpioEvents[pinNumberToSet].request.eventflags = GPIOEVENT_REQUEST_RISING_EDGE;
            break;
        }
        case 2: {
            gpioEvents[pinNumberToSet].request.eventflags = GPIOEVENT_REQUEST_FALLING_EDGE;
            break;
        }
        default: {
            gpioEvents[pinNumberToSet].request.eventflags = GPIOEVENT_REQUEST_BOTH_EDGES;
            break;
        }
    }
    char pinLabel[2];
    sprintf (pinLabel, "%d", pinNumberToSet);
    strcpy (gpioEvents[pinNumberToSet].request.consumer_label, pinLabel);

    int result = ioctl (fileDescriptor, GPIO_GET_LINEEVENT_IOCTL, &gpioEvents[pinNumberToSet].request);
    if (result < 0) {
        close (fileDescriptor);
        jniController.throwANewJNIException (env, "I/O control could not be setup");
        return;
    }
    close (fileDescriptor);

    gpioEvents[pinNumberToSet].pollFd.fd = gpioEvents[pinNumberToSet].request.fd;
    gpioEvents[pinNumberToSet].pollFd.events = POLLIN | POLLPRI;

}

JNIEXPORT jint JNICALL Java_com_comert_gEmbedded_nativeinterface_GPIOController_getRegisterSelector
        (JNIEnv *env, jclass GPIOController, jobject pin) {

    jint pinNumber;

    const register JNI_STATUS pinStatus = jniController.getEnumDigit (env, pin, &pinNumber);
    if (pinStatus == JNI_ERROR) {
        return -1;
    }

    return pinNumber / 32;

}

JNIEXPORT jint JNICALL Java_com_comert_gEmbedded_nativeinterface_GPIOController_getPinSet
        (JNIEnv *env, jclass GPIOController, jobject pin) {

    jint pinNumber;

    const register JNI_STATUS pinStatus = jniController.getEnumDigit (env, pin, &pinNumber);
    if (pinStatus == JNI_ERROR) {
        return 0;
    }

    return (1 << (pinNumber % 32));

}

JNIEXPORT void JNICALL Java_com_comert_gEmbedded_nativeinterface_GPIOController_releaseGPIOThreadRecourse
        (JNIEnv *env, const jclass GPIOController, const jint pinNumber) {

    close (gpioEvents[pinNumber].request.fd);

}

JNIEXPORT jboolean JNICALL Java_com_comert_gEmbedded_nativeinterface_GPIOController_isHigh
        (JNIEnv *env, const jclass GPIOController, const jint registerSelector, const jint pinSet) {

    register reg_t registerState = gpioRegisters->GPLEV[registerSelector];
    registerState &= pinSet;
    if (registerState > 1)
        return JNI_TRUE;
    else
        return JNI_FALSE;

}

JNIEXPORT jboolean JNICALL Java_com_comert_gEmbedded_nativeinterface_GPIOController_isLow
        (JNIEnv *env, const jclass GPIOController, const jint registerSelector, const jint pinSet) {

    register reg_t registerState = gpioRegisters->GPLEV[registerSelector];
    registerState &= pinSet;
    if (registerState > 1)
        return JNI_FALSE;
    else
        return JNI_TRUE;

}

JNIEXPORT void JNICALL Java_com_comert_gEmbedded_nativeinterface_GPIOController_write
        (JNIEnv *env, const jclass GPIOController, const jint registerSelector, const jint pinSet) {

    gpioRegisters->GPSET[registerSelector] = pinSet;

}

JNIEXPORT void JNICALL Java_com_comert_gEmbedded_nativeinterface_GPIOController_clear
        (JNIEnv *env, const jclass GPIOController, const jint registerSelector, const jint pinSet) {

    gpioRegisters->GPCLR[registerSelector] = pinSet;

}

JNIEXPORT void JNICALL Java_com_comert_gEmbedded_nativeinterface_GPIOController_pulse
        (JNIEnv *env, const jclass GPIOController, const jint registerSelector, const jint pinSet,
         const jint highSleepTimeInMicSec,
         const jint lowSleepTimeInMicSec) {

    gpioRegisters->GPSET[registerSelector] = pinSet;
    usleep (highSleepTimeInMicSec);
    gpioRegisters->GPCLR[registerSelector] = pinSet;
    usleep (lowSleepTimeInMicSec);
}

JNIEXPORT jint JNICALL Java_com_comert_gEmbedded_nativeinterface_GPIOController_poll
        (JNIEnv *env, const jclass GPIOController, const jint pinNumber, const jint timeoutInMilSec) {

    const register int pollResult = poll (&gpioEvents[pinNumber].pollFd, 1, timeoutInMilSec);

    switch (pollResult) {
        case -1: {
            return POLL_ERROR;
        }
        case 0: {
            return POLL_TIMEOUT;
        }
        default: {
            register const ssize_t readResult = read (gpioEvents[pinNumber].request.fd, &gpioEvents[pinNumber].data,
                                                      sizeof (gpioEvents[pinNumber].data));
            switch (readResult) {
                case -1: {
                }
                case 0: {
                    return READ_ERROR;
                }
                default: {
                    switch (gpioEvents[pinNumber].data.id) {
                        case GPIOEVENT_EVENT_FALLING_EDGE: {
                            return FALLING;
                        }
                        default: {
                            return RISING;
                        }
                    }
                }
            }
        }
    }

}

GPIO_STATUS gpioDriverSetup (JNIEnv *env) {

    void *pointer;
    const register MAPPER_STATUS mapperStatus = mapBaseRegister (MEMORY_FILE_NAME, GPIO_BLOCK_SIZE, GPIO_BASE_ADDRESS,
                                                                 &pointer);
    if (mapperStatus == MAPPER_ERROR) {
        jniController.throwANewJNIException (env, "/dev/mem could not be opened");
        return GPIO_ERROR;
    } else if (mapperStatus == MAPPER_ERROR) {
        jniController.throwANewJNIException (env, "GPIO memory mapping could not be setup");
        return GPIO_ERROR;
    } else {
        gpioRegisters = (GPIORegisters *) pointer;
    }

    return GPIO_SUCCESS;

}

GPIO_STATUS gpioDriverShutdown (JNIEnv *env) {

    const register MAPPER_STATUS mapperStatus = unmapBaseRegister ((void *) gpioRegisters, GPIO_BLOCK_SIZE);
    if (mapperStatus == MAPPER_ERROR) {
        jniController.throwANewJNIException (env, "GPIO memory unmapping could not be setup");
        return GPIO_ERROR;
    }

    return GPIO_SUCCESS;

}