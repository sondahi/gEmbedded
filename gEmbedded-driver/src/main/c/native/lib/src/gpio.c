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

#define MIN_VALID_PIN_NUMBER (0)
#define MAX_VALID_PIN_NUMBER (45)

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

// ALT_0, ALT_1, ALT_3, ALT_4, functions has no invalid pin number
static const jint invalidPinNumber_ALT2[] = {35, 40};
static const jint invalidPinNumber_ALT5[] = {35};

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

    if (pin == NULL || pinFunction == NULL) {
        jniController.throwANewJNIException (env, "setPinFunction error : pin or pinFunction is NULL");
        return;
    }

    jint pinNumber;
    const register JNI_STATUS pinStatus = jniController.getEnumDigit (env, pin, &pinNumber);
    if (pinStatus == JNI_ERROR) {
        jniController.throwANewJNIException (env, "setPinFunction error : getEnumDigit() method could not be called");
        return;
    }
    if (pinNumber < MIN_VALID_PIN_NUMBER || pinNumber > MAX_VALID_PIN_NUMBER) {
        jniController.throwANewJNIException (env, "setPinFunction error : not supported pin");
        return;
    }

    char pinFunctionText[LARGEST_NUMBER_WORD];
    const register JNI_STATUS pinFunctionStatus = jniController.getEnumText (env, pinFunction, pinFunctionText,sizeof (pinFunctionText));
    if (pinFunctionStatus == JNI_ERROR) {
        jniController.throwANewJNIException (env, "setPinFunction error : getEnumText() method could not be called");
        return;
    }

    jint pinFunctionNumber;
    if (strcmp (pinFunctionText, "Alternate 0") == 0) {
        pinFunctionNumber = ALT0;
    } else if (strcmp (pinFunctionText, "Alternate 1") == 0) {
        pinFunctionNumber = ALT1;
    } else if (strcmp (pinFunctionText, "Alternate 2") == 0) {
        pinFunctionNumber = ALT2;
    } else if (strcmp (pinFunctionText, "Alternate 3") == 0) {
        pinFunctionNumber = ALT3;
    } else if (strcmp (pinFunctionText, "Alternate 4") == 0) {
        pinFunctionNumber = ALT4;
    } else if (strcmp (pinFunctionText, "Alternate 5") == 0) {
        pinFunctionNumber = ALT5;
    } else if (strcmp (pinFunctionText, "Input") == 0) {
        pinFunctionNumber = INPUT;
    } else if (strcmp (pinFunctionText, "Output") == 0) {
        pinFunctionNumber = OUTPUT;
    } else {
        jniController.throwANewJNIException (env, "setPinFunction error : not supported pinFunction");
        return;
    }

    const register reg_t registerSelector = pinNumber / 10;

    gpioRegisters->GPFSEL[registerSelector] &= ~(7 << ((pinNumber % 10) * 3));
    gpioRegisters->GPFSEL[registerSelector] |= (pinFunctionNumber << ((pinNumber % 10) * 3));

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
    if (env == NULL || gpioRegisters != NULL) {
        return GPIO_ERROR;
    }

    void *pointer;

    const MAPPER_STATUS mapperStatus = mapBaseRegister (MEMORY_FILE_NAME, GPIO_BLOCK_SIZE, GPIO_BASE_ADDRESS, &pointer);
    if (mapperStatus == MAPPER_ERROR) {
        return GPIO_ERROR;
    }

    gpioRegisters = (GPIORegisters *) pointer;

    return GPIO_SUCCESS;
}

GPIO_STATUS gpioDriverShutdown (JNIEnv *env) {
    if (env == NULL || gpioRegisters == NULL) {
        return GPIO_ERROR;
    }

    const MAPPER_STATUS mapperStatus = unmapBaseRegister ((void *) gpioRegisters, GPIO_BLOCK_SIZE);
    if (mapperStatus == MAPPER_ERROR) {
        return GPIO_ERROR;
    }

    gpioRegisters = NULL;

    return GPIO_SUCCESS;
}

JNIEXPORT void JNICALL Java_com_comert_gEmbedded_pi_nativeinterface_GPIOController_setPinFunction
        (JNIEnv *env, const jclass GPIOController, jobject pin, jobject pinFunction, const jstring methodName,
         const jstring methodSignature){

    jint pinNumberToSet, pinFunctionToSet;

    const register JNI_STATUS  pinStatus = jniController.getConstantDigit(env, pin, methodName, methodSignature, &pinNumberToSet);
    if(pinStatus == JNI_EXCEPTION_OCCURRED){
        return;
    }

    const register JNI_STATUS pinFunctionStatus = jniController.getConstantDigit
            (env, pinFunction, methodName, methodSignature, &pinFunctionToSet);

    if(pinFunctionStatus == JNI_EXCEPTION_OCCURRED){
        return;
    }

    const register GPIO_STATUS gpioStatus = gpioDriver.setPinFunction(pinNumberToSet, pinFunctionToSet);

    const register GPIO_STATUS gpioExceptionStatus = gpioStatusCheck(env, gpioStatus);
    if (gpioExceptionStatus == GPIO_EXCEPTION_OCCURRED) {
        return;
    }

}

JNIEXPORT void JNICALL Java_com_comert_gEmbedded_pi_nativeinterface_GPIOController_setPullUpDownStatus
        (JNIEnv *env, const jclass GPIOController, jobject pin, jobject pullUpDownStatus, const jstring methodName,
         const jstring methodSignature){

    jint pinNumberToSet, pullUpDownStatusToSet;

    const register JNI_STATUS  pinStatus = jniController.getConstantDigit(env, pin, methodName, methodSignature, &pinNumberToSet);
    if(pinStatus == JNI_EXCEPTION_OCCURRED){
        return;
    }

    const register JNI_STATUS pullUpDownStatusStatus = jniController.getConstantDigit
            (env, pullUpDownStatus, methodName, methodSignature, &pullUpDownStatusToSet);
    if(pullUpDownStatusStatus == JNI_EXCEPTION_OCCURRED){
        return;
    }

    const register GPIO_STATUS gpioStatus = gpioDriver.setPUDStatus(pinNumberToSet, pullUpDownStatusToSet);

    const register GPIO_STATUS gpioExceptionStatus = gpioStatusCheck(env, gpioStatus);
    if (gpioExceptionStatus == GPIO_EXCEPTION_OCCURRED) {
        return;
    }

}

JNIEXPORT void JNICALL Java_com_comert_gEmbedded_pi_nativeinterface_GPIOController_setEventDetectStatus
        (JNIEnv *env, const jclass GPIOController, jobject pin, jobject eventDetectStatus, const jstring methodName,
         const jstring methodSignature, const jstring fileName){

    jint pinNumberToSet, eventDetectStatusToSet;

    const register JNI_STATUS pinStatus = jniController.getConstantDigit(env, pin, methodName, methodSignature, &pinNumberToSet);
    if(pinStatus == JNI_EXCEPTION_OCCURRED){
        return;
    }

    const register JNI_STATUS eventDetectStatusStatus = jniController.getConstantDigit
            (env, eventDetectStatus, methodName, methodSignature, &eventDetectStatusToSet);
    if(eventDetectStatusStatus == JNI_EXCEPTION_OCCURRED){
        return;
    }

    const char *gpioFileName = (*env)->GetStringUTFChars(env, fileName, JNI_FALSE);
    if(gpioFileName == NULL){
        char message[250];
        (*env)->ReleaseStringUTFChars(env, fileName, gpioFileName);
        sprintf(message, "Event detect status could not be setup");
        jniController.throwANewJNIException(env, message);
        return;
    }

    const register GPIO_STATUS gpioStatus = gpioDriver.setEventDetectStatus(pinNumberToSet, eventDetectStatusToSet, gpioFileName);

    const register GPIO_STATUS gpioExceptionStatus = gpioStatusCheck(env, gpioStatus);
    if (gpioExceptionStatus == GPIO_EXCEPTION_OCCURRED) {
        (*env)->ReleaseStringUTFChars(env, fileName, gpioFileName);
        return;
    }

    (*env)->ReleaseStringUTFChars(env, fileName, gpioFileName);

}

JNIEXPORT void JNICALL Java_com_comert_gEmbedded_pi_nativeinterface_GPIOController_releaseGPIOThreadRecourse
        (JNIEnv *env, const jclass GPIOController, const jint pinNumber) {

    gpioDriver.releaseGPIOThreadSource(pinNumber);

}

JNIEXPORT jboolean JNICALL Java_com_comert_gEmbedded_pi_nativeinterface_GPIOController_isHigh
        (JNIEnv *env, const jclass GPIOController, const jint registerSelector, const jint pinSet) {

    return gpioDriver.isHigh(registerSelector, pinSet);

}

JNIEXPORT jboolean JNICALL Java_com_comert_gEmbedded_pi_nativeinterface_GPIOController_isLow
        (JNIEnv *env, const jclass GPIOController, const jint registerSelector, const jint pinSet) {

    return gpioDriver.isLow(registerSelector, pinSet);

}

JNIEXPORT void JNICALL Java_com_comert_gEmbedded_pi_nativeinterface_GPIOController_write
        (JNIEnv *env, const jclass GPIOController, const jint registerSelector, const jint pinSet) {

    gpioDriver.write(registerSelector, pinSet);

}

JNIEXPORT void JNICALL Java_com_comert_gEmbedded_pi_nativeinterface_GPIOController_clear
        (JNIEnv *env, const jclass GPIOController, const jint registerSelector, const jint pinSet) {

    gpioDriver.clear(registerSelector, pinSet);

}

JNIEXPORT void JNICALL Java_com_comert_gEmbedded_pi_nativeinterface_GPIOController_pulse
        (JNIEnv *env, const jclass GPIOController, const jint registerSelector, const jint pinSet, const jint highSleepTimeInMicSec,
         const jint lowSleepTimeInMicSec) {

    gpioDriver.pulse(registerSelector, pinSet, highSleepTimeInMicSec, lowSleepTimeInMicSec);

}

JNIEXPORT jint JNICALL Java_com_comert_gEmbedded_pi_nativeinterface_GPIOController_poll
        (JNIEnv *env, const jclass GPIOController, const jint pinNumber, const jint timeoutInMilSec) {

    return gpioDriver.poll(pinNumber, timeoutInMilSec);

}

static GPIO_STATUS setEventDetectStatus_(const jint pinNumber, const jint eventDetectionStatus, const char *fileName) {

    int fileDescriptor = open(fileName, O_WRONLY);
    if (fileDescriptor < 0) {
        close(fileDescriptor);
        return GPIO_DEVICE_FILE_OPEN_ERROR;
    }

    gpioEvents[pinNumber].request.lineoffset = pinNumber;
    gpioEvents[pinNumber].request.handleflags = GPIOHANDLE_REQUEST_INPUT;
    switch (eventDetectionStatus) {
        case 1:
        {
            gpioEvents[pinNumber].request.eventflags = GPIOEVENT_REQUEST_RISING_EDGE;
            break;
        }
        case 2:
        {
            gpioEvents[pinNumber].request.eventflags = GPIOEVENT_REQUEST_FALLING_EDGE;
            break;
        }
        default:
        {
            gpioEvents[pinNumber].request.eventflags = GPIOEVENT_REQUEST_BOTH_EDGES;
            break;
        }
    }
    char pinLabel[2];
    sprintf(pinLabel, "%d", pinNumber);
    strcpy(gpioEvents[pinNumber].request.consumer_label, pinLabel);

    int result = ioctl(fileDescriptor, GPIO_GET_LINEEVENT_IOCTL, &gpioEvents[pinNumber].request);
    if (result < 0) {
        close(fileDescriptor);
        return GPIO_GET_LINE_EVENT_IOCTL_ERROR;
    }
    close(fileDescriptor);

    gpioEvents[pinNumber].pollFd.fd = gpioEvents[pinNumber].request.fd;
    gpioEvents[pinNumber].pollFd.events = POLLIN | POLLPRI;

    return GPIO_SUCCESS;

}

static void releaseGPIOThreadResource_(const jint pinNumber) {

    close(gpioEvents[pinNumber].request.fd);

}

static jint poll_(const jint pinNumber, const jint timeoutInMilSec) {

    const register int pollResult = poll(&gpioEvents[pinNumber].pollFd, 1, timeoutInMilSec);
    switch (pollResult) {
        case -1:
        {
            return POLL_ERROR;
        }
        case 0:
        {
            return POLL_TIMEOUT;
        }
        default:
        {
            register const ssize_t readResult = read(gpioEvents[pinNumber].request.fd, &gpioEvents[pinNumber].data, sizeof (gpioEvents[pinNumber].data));
            switch (readResult) {
                case -1:
                {
                }
                case 0:
                {
                    return READ_ERROR;
                }
                default:
                {
                    switch (gpioEvents[pinNumber].data.id) {
                        case GPIOEVENT_EVENT_FALLING_EDGE:
                        {
                            return FALLING;
                        }
                        default:
                        {
                            return RISING;
                        }
                    }
                }
            }
        }
    }

}

#define GPIO_BASE_ADDRESS   (PERIPHERAL_BASE_ADDRESS + 0x200000)
#define GPIO_BLOCK_SIZE     (0xF4)

#define GPIO_PIN_SIZE       (30)

#define FALLING             (0)
#define RISING              (1)
#define READ_ERROR          (2)
#define POLL_TIMEOUT        (3)
#define POLL_ERROR          (4)

typedef struct GPIOEvents_ {
    struct gpioevent_request request;
    struct gpioevent_data data;
    struct pollfd pollFd;
} GPIOEvents;

static GPIORegisters *gpioRegisters;
static GPIOEvents gpioEvents[GPIO_PIN_SIZE];