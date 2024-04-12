#include "bsp.h"
#include "stm32f4xx.h"

#define GPIOAEN 	(1U<<0)		/* Use for Button */
#define GPIODEN		(1U<<3)		/* Use for LED */

#define PIN12		(1U<<12)
#define LED_PIN		PIN12

#define PIN0		(1U<<0)
#define BTN_PIN		PIN0

void led_init(void)
{
	/*Enable clock access to GPIOD */
	RCC->AHB1ENR |= GPIODEN;
	/*Set PD12 mode as output */
	GPIOD->MODER |= (1U<<24);
	GPIOD->MODER &=~(1U<<25);
}

void led_on(void)
{
	/* set PD12 as High */
	GPIOD->ODR |= LED_PIN;
}

void led_off(void)
{
	/* set PD12 as Low */
	GPIOD->ODR &= ~LED_PIN;
}

void button_init(void)
{
	/* Enable clock access to PORTA */
	RCC->AHB1ENR |= GPIOAEN;
	/* Set PA0 pin as input */
	GPIOA->MODER &=~(1U<<24);	/* By default its reset , here setting as input */
	GPIOA->MODER &=~(1U<<25);
}

bool get_btn_state(void)
{
	/* checked button is pressed */
	if(GPIOA->IDR & BTN_PIN)
	{
		return true;
	}
	else{
		return false;
	}
}
