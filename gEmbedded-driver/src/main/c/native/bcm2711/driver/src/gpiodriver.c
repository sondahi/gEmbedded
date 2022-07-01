#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <linux/gpio.h>
#include <sys/poll.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <stdint.h>
#include <stdlib.h>
#include "gpiodriver.h"
#include "gpio.h"

static GpioRegisters_t volatile *p_regs = NULL;
static GpioEvents_t events[GPIO_PIN_SIZE];

u8 calculate1bitRegisterSelector (const GPIO_PIN pin) {

    return pin / 32;

}

u32 calculate1bitPinSet (const GPIO_PIN pin) {

    return (1 << (pin % 32));

}

u8 calculate2bitRegisterSelector (const GPIO_PIN pin) {

    return pin / 16;

}

u8 calculate3bitRegisterSelector (GPIO_PIN pin) {

    return pin / 10;
}

void setPinFunction (const GPIO_PIN pin, const GPIO_PIN_FUNCTION pinFunction) {

    const register u8 registerSelector = calculate3bitRegisterSelector (pin);

    GPIO_REGS->GPFSEL[registerSelector] &= ~(7 << ((pin % 10) * 3));
    GPIO_REGS->GPFSEL[registerSelector] |= (pinFunction << ((pin % 10) * 3));

}

GPIO_PIN_FUNCTION readPinFunction (const GPIO_PIN pin) {

    const register u8 registerSelector = calculate3bitRegisterSelector (pin);

    const register reg_l registerLine = GPIO_REGS->GPFSEL[registerSelector];
    const register u32 mask = (7 << ((pin % 10) * 3));

    register u32 pinFunction = registerLine & mask;
    pinFunction >>= ((pin % 10) * 3);
    switch (pinFunction) {
        case FUNCTION_INPUT: {
            return FUNCTION_INPUT;
        }
        case FUNCTION_OUTPUT: {
            return FUNCTION_OUTPUT;
        }
        case FUNCTION_ALT_0: {
            return FUNCTION_ALT_0;
        }
        case FUNCTION_ALT_1: {
            return FUNCTION_ALT_1;
        }
        case FUNCTION_ALT_2: {
            return FUNCTION_ALT_2;
        }
        case FUNCTION_ALT_3: {
            return FUNCTION_ALT_3;
        }
        case FUNCTION_ALT_4: {
            return FUNCTION_ALT_4;
        }
        default: {
            return FUNCTION_ALT_5;
        }
    }

}

void setPullupPulldown (const GPIO_PIN pin, const GPIO_PUP_PDN pullUpDown) {

    const register u8 registerSelector = calculate2bitRegisterSelector (pin);

    GPIO_REGS->GP_PUP_PDN[registerSelector] &= ~(3 << ((pin % 16) * 2));
    GPIO_REGS->GP_PUP_PDN[registerSelector] |= (pullUpDown << ((pin % 16) * 2));

}

GPIO_PUP_PDN readPullupPulldown (const GPIO_PIN pin) {

    const register u8 registerSelector = calculate2bitRegisterSelector (pin);

    const register reg_l registerLine = GPIO_REGS->GP_PUP_PDN[registerSelector];
    const register u32 mask = (3 << ((pin % 16) * 2));

    register u32 pullUpDown = registerLine & mask;
    pullUpDown >>= ((pin % 16) * 2);
    switch (pullUpDown) {
        case PUPPDN_NO_RESISTOR: {
            return PUPPDN_NO_RESISTOR;
        }
        case PUPPDN_PULL_UP: {
            return PUPPDN_PULL_UP;
        }
        case PUPPDN_PULL_DOWN: {
            return PUPPDN_PULL_DOWN;
        }
        default: {
            return PUPPDN_RESERVED;
        }
    }

}

GPIO_STATUS setEventDetectStatus (const GPIO_PIN pin, const GPIO_EVENT gpioEvent) {

    int fd, ret;
    fd = open (GPIO_CHIP_DEV_NAME, O_WRONLY);
    if (fd < 0) {
        close (fd);
        return GPIO_ERROR;
    }

    gpioEvents[pin].request.lineoffset = pin;
    gpioEvents[pin].request.handleflags = GPIOHANDLE_REQUEST_INPUT;
    gpioEvents[pin].request.eventflags = gpioEvent;

    ret = ioctl (fd, GPIO_GET_LINEEVENT_IOCTL, &gpioEvents[pin].request);
    if (ret < 0) {
        close (fd);
        return GPIO_ERROR;
    }
    close (fd);

    gpioEvents[pin].pollFd.fd = gpioEvents[pin].request.fd;
    gpioEvents[pin].pollFd.events = POLLIN | POLLPRI;

    return GPIO_SUCCESS;

}

GPIO_EVENT_RESULT pollEvent (GPIO_PIN pin, int timeoutInMilSec) {

    const register int pollResult = poll (&gpioEvents[pin].pollFd, 1, timeoutInMilSec);
    switch (pollResult) {
        case -1: {
            return EVENT_POLL_ERROR;
        }
        case 0: {
            return EVENT_POLL_TIMEOUT;
        }
        default: {
            register const ssize_t readResult = read (gpioEvents[pin].request.fd, &gpioEvents[pin].data,
                                                      sizeof (gpioEvents[pin].data));
            switch (readResult) {
                case -1: {
                }
                case 0: {
                    return EVENT_READ_ERROR;
                }
                default: {
                    switch (gpioEvents[pin].data.id) {
                        case GPIOEVENT_EVENT_RISING_EDGE: {
                            return EVENT_RISING;
                        }
                        default: {
                            return EVENT_FALLING;
                        }
                    }
                }
            }
        }
    }

}

void releaseGPIOEventResource (const int pinNumber) {

    close (gpioEvents[pinNumber].request.fd);

}

GPIO_STATUS writePin (const u8 registerSelector, const u32 pinSet) {

    GPIO_REGS->GPSET[registerSelector] = pinSet;

    const register GPIO_PIN_LEVEL pinLevel = readPinLevel (registerSelector, pinSet);
    if (pinLevel == LEVEL_HIGH) {
        return GPIO_SUCCESS;
    } else {
        return GPIO_ERROR;
    }

}

void writePinFaster (const u8 registerSelector, const u32 pinSet) {

    GPIO_REGS->GPSET[registerSelector] = pinSet;

}

GPIO_STATUS clearPin (const u8 registerSelector, const u32 pinSet) {

    GPIO_REGS->GPCLR[registerSelector] = pinSet;

    const register GPIO_PIN_LEVEL pinLevel = readPinLevel (registerSelector, pinSet);
    if (pinLevel == LEVEL_LOW) {
        return GPIO_SUCCESS;
    } else {
        return GPIO_ERROR;
    }

}

void clearPinFaster (const u8 registerSelector, const u32 pinSet) {

    GPIO_REGS->GPCLR[registerSelector] = pinSet;

}

GPIO_PIN_LEVEL readPinLevel (const u8 registerSelector, const u32 pinSet) {

    const register reg_l registerLine = GPIO_REGS->GPLEV[registerSelector];
    const register u32 pinLevel = registerLine & pinSet;

    if (pinLevel > 0) {
        return LEVEL_HIGH;
    } else {
        return LEVEL_LOW;
    }

}

GPIO_STATUS
pulsePin (const u8 registerSelector, const u32 pinSet, const u32 highSleepTimeInMicSec,
          const u32 lowSleepTimeInMicSec) {

    register GPIO_STATUS status;

    status = writePin (registerSelector, pinSet);
    if (status == GPIO_ERROR) {
        return status;
    }

    usleep (highSleepTimeInMicSec);

    status = clearPin (registerSelector, pinSet);
    if (status == GPIO_ERROR) {
        return status;
    }

    usleep (lowSleepTimeInMicSec);

    return GPIO_SUCCESS;

}

void pulsePinFaster (const u8 registerSelector, const u32 pinSet, const u32 highSleepTimeInMicSec,
                     const u32 lowSleepTimeInMicSec) {

    GPIO_REGS->GPSET[registerSelector] = pinSet;
    usleep (highSleepTimeInMicSec);
    GPIO_REGS->GPCLR[registerSelector] = pinSet;
    usleep (lowSleepTimeInMicSec);

}

GPIO_STATUS gpioDriverSetup (void *gpioOffset) {

    if (GPIO_REGS != NULL) {
        return GPIO_ERROR;
    } else {
        GPIO_REGS = (GPIORegisters *) gpioOffset;
        return GPIO_SUCCESS;
    }

}

GPIO_STATUS gpioDriverShutdown () {

    if (GPIO_REGS == NULL) {
        return GPIO_ERROR;
    } else {
        GPIO_REGS = NULL;
        return GPIO_SUCCESS;
    }

}
