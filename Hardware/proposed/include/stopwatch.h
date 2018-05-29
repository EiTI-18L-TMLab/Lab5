#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <stdint.h>

struct Time_struct
{
  uint16_t hour;
  uint16_t min;
  uint16_t sec;
  uint16_t ms;
} _time;


volatile uint16_t timer_10ms_ticks;

#endif /* STOPWATCH_H */
