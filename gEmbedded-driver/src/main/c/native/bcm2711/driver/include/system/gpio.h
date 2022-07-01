#ifndef GPIO_H
#define GPIO_H

#include <linux/gpio.h>
#include <sys/poll.h>
#include "common.h"

typedef struct {
    uPtr_t GPFSEL[6];
    uPtr_t Reserved1;
    uPtr_t GPSET[2];
    uPtr_t Reserved2;
    uPtr_t GPCLR[2];
    uPtr_t Reserved3;
    uPtr_t GPLEV[2];
    uPtr_t Reserved4;
    uPtr_t GPEDS[2];
    uPtr_t Reserved5;
    uPtr_t GPREN[2];
    uPtr_t Reserved6;
    uPtr_t GPFEN[2];
    uPtr_t Reserved7;
    uPtr_t GPHEN[2];
    uPtr_t Reserved8;
    uPtr_t GPLEN[2];
    uPtr_t Reserved9;
    uPtr_t GPAREN[2];
    uPtr_t Reserved10;
    uPtr_t GPAFEN[2];
    uPtr_t Reserved11[21];
    uPtr_t GP_PUP_PDN[4];
} GpioRegisters_t;

typedef struct {
    struct gpioevent_request request;
    struct gpioevent_data data;
    struct pollfd pollFd;
} GpioEvents_t;

#endif //GPIO_H
