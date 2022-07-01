#ifndef GPIODRIVER_H
#define GPIODRIVER_H

#include "common.h"
#include <linux/gpio.h>

#define GPIO_MEM_DEV_NAME   ("/dev/gpiomem")
#define GPIO_BLOCK_SIZE     (0xF4)
#define GPIO_CHIP_DEV_NAME  ("/dev/gpiochip0")
#define GPIO_PIN_SIZE       (28)

typedef enum {
    GPIO_ERROR = 0,
    GPIO_SUCCESS = 1
} GPIO_STATUS;

GPIO_STATUS gpioDriverSetup (void *gpioOffset);
GPIO_STATUS gpioDriverShutdown (void);

/*
 * Calculates register line of pin which is a 1 bit
 */
u8_t calculate1bitRegisterSelector (u8_t pin);

/*
 * Calculates position of pin in register line which is a 1 bit
 */
u32_t calculate1bitPinField (u8_t pin);

/*
 * Calculates register line of pin which is 2 bits
 */
u8_t calculate2bitRegisterSelector (u8_t pin);

/*
 * Calculates position of pin in register line which is 2 bits
 */
u32_t calculate2bitPinField (u8_t pin);

/*
 * Calculates register line of pin which is 3 bits
 */
u8 calculate3bitRegisterSelector (GPIO_PIN pin);

/*
 * Calculates position of pin in register line which is 3 bits
 */
u32 calculate3bitPinSet (GPIO_PIN pin);

/*
 * Sets gpio pin function
 */
void setGpioPinFunction (GPIO_PIN pin, GPIO_PIN_FUNCTION pinFunction);

/*
 * Reads gpio function
 */
GPIO_PIN_FUNCTION readGpioPinFunction (GPIO_PIN pin);

/*
 * Sets gpio pull-up, pull-down
 */
void setGpioPullUpPullDown (GPIO_PIN pin, GPIO_PUP_PDN pullUpPullDown);

/*
 * Reads gpio pull-up, pull-down
 */
GPIO_PUP_PDN readGpioPullUpPullDown (GPIO_PIN pin);

void setGpioEvent (GPIO_PIN pin, GPIO_EVENT gpioEvent);

GPIO_EVENT readGpioEvent (GPIO_PIN pin);

GPIO_PIN_LEVEL readPinLevel (u8 registerSelector, u32 pinSet);

GPIO_STATUS writePin (u8 registerSelector1bit, u32 pinSet1bit);

GPIO_STATUS clearPin (u8 registerSelector1bit, u32 pinSet1bit);

GPIO_STATUS pulsePin (u8 registerSelector1bit, u32 pinSet1bit, u32 highSleepTimeInMicSec, u32 lowSleepTimeInMicSec);

void writePinFaster (u8 registerSelector1bit, u32 pinSet1bit);

void clearPinFaster (u8 registerSelector1bit, u32 pinSet1bit);

void pulsePinFaster (u8 registerSelector1bit, u32 pinSet1bit, u32 highSleepTimeInMicSec, u32 lowSleepTimeInMicSec);

GPIO_EVENT_RESULT pollEvent (GPIO_PIN pin, int timeoutInMilSec);

void releaseGPIOEventResource (int pin);

#endif
