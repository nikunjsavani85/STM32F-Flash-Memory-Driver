#include "adc.h"
#include "stm32f4xx.h"

#define GPIOAEN	(1U<<0)
#define ADC1EN	(1U<<8)		/* Enable from APB2 reg */
#define ADC_CH1	(1U<<0)
#define AD_SQR_LEN_1	0x00	// SQUENCE REG
#define CR2_ADCON	(1U<<0)
#define CR2_CONT	(1U<<1)
#define CR2_SWSTART	(1U<<30)	//CONTROL REG
#define SR_EOC		(1U<<1)		//STATUS REG

void pa1_adc_init(void){

	/***configure ADC GPIO pin       ***/
	/* Enable clock access to GPIOA    */
	RCC->AHB1ENR |= GPIOAEN;
	/* Set PA1 mode to analog mode     */
	GPIOA->MODER |= (1U<<2);	// Analog Mode pin 2,3 = 1
	GPIOA->MODER |=	(1U<<3);

	/*** Configure ADC Module 	     ***/
	/*Enable clock access to ADC module*/
	RCC->APB2ENR	|= ADC1EN;
	/* Set conversion Sequence start   */
	ADC1->SQR3 = ADC_CH1;		// Channel 1
	/* Set conversion Sequence length  */
	ADC1->SQR1 = AD_SQR_LEN_1;  // Single conversion
	/* Enable ADC module 			   */
	ADC1->CR2 |= CR2_ADCON;		// ADC converter ON
}


void start_conversion(void){
	/* Enable continuous conversion */
	ADC1->CR2 |= CR2_CONT;
	/* Start ADC conversion */
	ADC1->CR2 |= CR2_SWSTART;
}

uint32_t adc_read(void){
	/* wait for conversion complete */
	while(!(ADC1->SR & SR_EOC )){ }

	/* Read converted value */
	return (ADC1->DR);
}
