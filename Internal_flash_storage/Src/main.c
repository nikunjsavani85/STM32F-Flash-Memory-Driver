#include <stdio.h>
#include <string.h>
#include "stm32f4xx.h"
#include "fpu.h"
#include "uart.h"
#include "timebase.h"
#include "bsp.h"
#include "adc.h"
#include "flash_driver.h"

#define BUFF_SIZE		10

char buff_rcv_char[BUFF_SIZE + 30];
uint32_t buff_data_to_store[BUFF_SIZE] = {123,1126,4056,69,2024,143,1100,4444,9000,22};
uint32_t buff_rcv_data[BUFF_SIZE +30];
char *pbuff_test_string =  "Testing : string from firmware";

uint32_t g_curr_val =  3650;
uint32_t g_rcv_val;

static uint32_t get_word_length(char *buff);

int main()
{

	/* Enabling floating point */
	fpu_enable();

	/* Debug UART Init for print*/
	debug_uart_init();

	/* inatialized timebase  */
	timebase_init();

	/* IMPORTANS */
	delay(5);

	/*Write data*/
	flash_write_data(0x08060000,(uint32_t *)buff_data_to_store, BUFF_SIZE);

	/*Read data*/
	flash_read_data(0x08060000,buff_rcv_data,BUFF_SIZE);

	/*Write data*/
	flash_write_data(0x08040000,(uint32_t *)pbuff_test_string, get_word_length(pbuff_test_string));

	/*Read data*/
	flash_read_data(0x08040000,buff_rcv_data,get_word_length(pbuff_test_string));

	/*Convert to string*/
	get_str((uint32_t *)buff_rcv_data,buff_rcv_char);

	/*Test single word*/
	flash_write_num(0x08020000,g_curr_val);

	/*Get single word*/
	g_rcv_val = flash_read_num(0x08020000);

	while(1)
	{

	}
}

/* use for getting word length of buffer */
static uint32_t get_word_length(char *buff)
{
	uint32_t ret;

	ret =  (strlen(buff)/4) + ((strlen(buff)%4) !=0);

	return ret;

}
