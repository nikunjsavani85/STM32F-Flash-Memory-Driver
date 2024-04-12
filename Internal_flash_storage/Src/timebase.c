#include "timebase.h"
#include "stm32f4xx.h"

#define CTRL_ENABLE		(1<<0)
#define CTRL_TICKINT	(1<<1)
#define CRTL_CLCKSRC	(1<<2)
#define CRTL_COUNTFLAG	(1<<16)

#define ONE_SEC_LOAD	16000000

#define TICK_FREQ 		1

volatile uint32_t g_curr_tick;
volatile uint32_t g_curr_tick_p;

/*Delay in sec */

void delay(uint32_t delay){
	uint32_t tick_start = get_tick();
	uint32_t wait = delay;

	if(wait < MAX_DELAY){
		wait += (uint32_t) TICK_FREQ;
	}

	while((get_tick()- tick_start)< wait){}
}

uint32_t get_tick(void){
	__disable_irq();
	g_curr_tick_p = g_curr_tick;
	__enable_irq();

	return g_curr_tick_p;
}

static void tick_increments(void){
	g_curr_tick +=TICK_FREQ;
}
void timebase_init(void){

	/* Disable global interrupt */
	__disable_irq();
	/* Load the timer with number of clock per Second */
	SysTick->LOAD = ONE_SEC_LOAD - 1; /* starting from zero */
	/* Clear systick current value register */
	SysTick->VAL = 0;
	/* Select internal clock source */
	SysTick->CTRL = CRTL_CLCKSRC;
	/* enable interrupt */
	SysTick->CTRL |= CTRL_TICKINT;
	/* enable systick */
	SysTick->CTRL |= CTRL_ENABLE;
	/* Enable gloabl interrupt */
	__enable_irq();
}

void SysTick_Handler(void){
	tick_increments();
}
