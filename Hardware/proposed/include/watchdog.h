#ifndef WATCHDOG_H
#define WATCHDOG_H

#include <msp430.h>


void watchdog_disable(void);
void watchdog_enable(void);
void watchdog_pet(void);

#endif /* WATCHDOG_H */
