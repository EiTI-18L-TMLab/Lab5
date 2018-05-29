#ifndef SYSTEM_H
#define SYSTEM_H

#include <msp430.h>
#include "timerA.h"
#include "IOMapping.h"

void _clocks_init(void);
void system_init(void);
void _io_init(void);

#endif /* SYSTEM_H */
