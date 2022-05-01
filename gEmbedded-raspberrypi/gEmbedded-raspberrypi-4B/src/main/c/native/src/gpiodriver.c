#include "gpiodriver.h"
#include "gpioexception.h"

#include <jni.h>
#include "common.h"
#include <linux/gpio.h>
#include <poll.h>
#include "mapper.h"
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>

#define GPIO_BASE_ADDRESS   (PERIPHERAL_BASE_ADDRESS + 0x200000)
#define GPIO_BLOCK_SIZE     (0xF4)
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

GPIODriver gpioDriver;

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

typedef struct GPIOEvents_ {
    struct gpioevent_request request;
    struct gpioevent_data data;
    struct pollfd pollFd;
} GPIOEvents;

static GPIORegisters *gpioRegisters;
static GPIOEvents gpioEvents[GPIO_PIN_SIZE];

static GPIO_STATUS setPinFunction_ (const jint pinNumber, jint pinFunction) {

    const register reg_t registerSelector = pinNumber / 10;

    switch (pinFunction) {
        case 0: {
            pinFunction = ALT0;
            break;
        }
        case 1: {
            pinFunction = ALT1;
            break;
        }
        case 2: {
            pinFunction = ALT2;
            break;
        }
        case 3: {
            pinFunction = ALT3;
            break;
        }
        case 4: {
            pinFunction = ALT4;
            break;
        }
        case 5: {
            pinFunction = ALT5;
            break;
        }
        case 6: {
            pinFunction = INPUT;
            break;
        }
        case 7: {
            pinFunction = OUTPUT;
            break;
        }
        default: {
            return GPIO_PIN_FUNCTION_ERROR;
        }
    }

    gpioRegisters->GPFSEL[registerSelector] &= ~(7 << ((pinNumber % 10) * 3));
    gpioRegisters->GPFSEL[registerSelector] |= (pinFunction << ((pinNumber % 10) * 3));

    register reg_t registerLine = gpioRegisters->GPFSEL[registerSelector];
    register reg_t mask = (7 << ((pinNumber % 10) * 3));
    register reg_t pinFunction_ = registerLine & mask;
    pinFunction_ >>= ((pinNumber % 10) * 3);

    if (pinFunction_ != pinFunction) {
        return GPIO_PIN_FUNCTION_ERROR;
    }

    return GPIO_SUCCESS;

}

static GPIO_STATUS setPUDStatus_ (const jint pinNumber, jint pullUpDownStatus) {

    const register reg_t registerSelector = pinNumber / 16;

    switch (pullUpDownStatus) {
        case 0: {
            pullUpDownStatus = NONE;
            break;
        }
        case 1: {
            pullUpDownStatus = PULL_UP;
            break;
        }
        case 2: {
            pullUpDownStatus = PULL_DOWN;
            break;
        }
        case 3: {
            pullUpDownStatus = DEFAULT;
            break;
        }
        case 4: {
            pullUpDownStatus = RESERVED;
            break;
        }
        default: {
            return GPIO_PUD_STATUS_ERROR;
        }
    }

    gpioRegisters->PUD[registerSelector] &= ~(3 << ((pinNumber % 16) * 2));
    gpioRegisters->PUD[registerSelector] |= (pullUpDownStatus << ((pinNumber % 16) * 2));

    register reg_t registerLine = gpioRegisters->PUD[registerSelector];
    register reg_t mask = (3 << ((pinNumber % 16) * 2));
    register reg_t pullUpDownStatus_ = registerLine & mask;
    pullUpDownStatus_ >>= ((pinNumber % 16) * 2);

    if (pullUpDownStatus_ != pullUpDownStatus) {
        return GPIO_PUD_STATUS_ERROR;
    }

    return GPIO_SUCCESS;

}

static GPIO_STATUS setEventDetectStatus_ (const jint pinNumber, const jint eventDetectionStatus, const char *fileName) {

    int fileDescriptor = open (fileName, O_WRONLY);
    if (fileDescriptor < 0) {
        close (fileDescriptor);
        return GPIO_DEVICE_FILE_OPEN_ERROR;
    }

    gpioEvents[pinNumber].request.lineoffset = pinNumber;
    gpioEvents[pinNumber].request.handleflags = GPIOHANDLE_REQUEST_INPUT;
    switch (eventDetectionStatus) {
        case 1: {
            gpioEvents[pinNumber].request.eventflags = GPIOEVENT_REQUEST_RISING_EDGE;
            break;
        }
        case 2: {
            gpioEvents[pinNumber].request.eventflags = GPIOEVENT_REQUEST_FALLING_EDGE;
            break;
        }
        default: {
            gpioEvents[pinNumber].request.eventflags = GPIOEVENT_REQUEST_BOTH_EDGES;
            break;
        }
    }
    char pinLabel[2];
    sprintf (pinLabel, "%d", pinNumber);
    strcpy (gpioEvents[pinNumber].request.consumer_label, pinLabel);

    int result = ioctl (fileDescriptor, GPIO_GET_LINEEVENT_IOCTL, &gpioEvents[pinNumber].request);
    if (result < 0) {
        close (fileDescriptor);
        return GPIO_GET_LINE_EVENT_IOCTL_ERROR;
    }
    close (fileDescriptor);

    gpioEvents[pinNumber].pollFd.fd = gpioEvents[pinNumber].request.fd;
    gpioEvents[pinNumber].pollFd.events = POLLIN | POLLPRI;

    return GPIO_SUCCESS;

}

static jint getRegisterSelector_ (jint pinNumber) {
    return pinNumber / 32;
}

static jint getPinset_ (jint pinNumber) {
    return (1 << (pinNumber % 32));
}

static void releaseGPIOThreadResource_ (const jint pinNumber) {

    close (gpioEvents[pinNumber].request.fd);

}

static jboolean isHigh_ (const jint registerSelector, const jint pinSet) {

    register reg_t registerState = gpioRegisters->GPLEV[registerSelector];
    registerState &= pinSet;
    if (registerState > 1)
        return JNI_TRUE;
    else
        return JNI_FALSE;

}

static jboolean isLow_ (const jint registerSelector, const jint pinSet) {

    register reg_t registerState = gpioRegisters->GPLEV[registerSelector];
    registerState &= pinSet;
    if (registerState > 1)
        return JNI_FALSE;
    else
        return JNI_TRUE;

}

static void write_ (const jint registerSelector, const jint pinSet) {

    gpioRegisters->GPSET[registerSelector] = pinSet;

}

static void clear_ (const jint registerSelector, const jint pinSet) {

    gpioRegisters->GPCLR[registerSelector] = pinSet;

}

static void pulse_ (const jint registerSelector, const jint pinSet, const jint highSleepTimeInMicSec,
                    const jint lowSleepTimeInMicSec) {

    gpioRegisters->GPSET[registerSelector] = pinSet;
    usleep (highSleepTimeInMicSec);
    gpioRegisters->GPCLR[registerSelector] = pinSet;
    usleep (lowSleepTimeInMicSec);

}

static jint poll_ (const jint pinNumber, const jint timeoutInMilSec) {

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

GPIO_STATUS gpioDriverSetup () {

    void *pointer;
    const register MapperStatus mapperStatus = mapBaseRegister (GPIO_BASE_ADDRESS, GPIO_BLOCK_SIZE, MEMORY_FILE_NAME,
                                                                &pointer);
    if (mapperStatus == MAPPER_FILE_OPEN_ERROR) {
        return GPIO_DEVICE_FILE_OPEN_ERROR;
    } else if (mapperStatus == MAPPER_MEMORY_MAP_ERROR) {
        return GPIO_MEMORY_MAP_ERROR;
    } else {
        gpioRegisters = (GPIORegisters *) pointer;
    }

    gpioDriver.setPinFunction = setPinFunction_;
    gpioDriver.setPUDStatus = setPUDStatus_;
    gpioDriver.setEventDetectStatus = setEventDetectStatus_;
    gpioDriver.getRegisterSelector = getRegisterSelector_;
    gpioDriver.getPinset = getPinset_;
    gpioDriver.isHigh = isHigh_;
    gpioDriver.isLow = isLow_;
    gpioDriver.write = write_;
    gpioDriver.clear = clear_;
    gpioDriver.pulse = pulse_;
    gpioDriver.poll = poll_;
    gpioDriver.releaseGPIOThreadSource = releaseGPIOThreadResource_;

    return GPIO_SUCCESS;

}

GPIO_STATUS gpioDriverShutdown () {

    const register MapperStatus mapperStatus = unmapBaseRegister (GPIO_BLOCK_SIZE, (void *) gpioRegisters);
    if (mapperStatus == MAPPER_MEMORY_UNMAP_ERROR) {
        return GPIO_MEMORY_UNMAP_ERROR;
    }

    return GPIO_SUCCESS;

}