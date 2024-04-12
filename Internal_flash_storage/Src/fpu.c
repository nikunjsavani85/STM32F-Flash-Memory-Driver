#include "stm32f4xx.h"

void fpu_enable(void)
{
	/* Enable Floating point unit :
	 *
	 * Enable CP10 and CP11 : Full access mode
	 *
	 */

	SCB->CPACR |= (1U << 20);
	SCB->CPACR |= (1U << 21);
	SCB->CPACR |= (1U << 22);
	SCB->CPACR |= (1U << 23);
}
