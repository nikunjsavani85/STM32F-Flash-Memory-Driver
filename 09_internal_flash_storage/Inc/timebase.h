#ifndef __TIMEBASE_H__
#define __TIMEBASE_H__

#include <stdint.h>

#define MAX_DELAY		0xFFFFFFFF

uint32_t get_tick(void);
void timebase_init(void);
void delay(uint32_t delay);

#endif
