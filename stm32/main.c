#include "stm32l476xx.h"
#include "EXTI.h"
#include "LED.h"
#include "SysClock.h"
#include "UART.h"

#include "string.h"
#include "stdio.h"

void Init_USARTx(int part) {
	if(part == 1) {
		UART2_Init();
		UART2_GPIO_Init();
		USART_Init(USART2);
	} else if(part == 2) {
		UART1_Init();
		UART1_GPIO_Init();
		USART_Init(USART1);
	} else {
		// Do nothing...
	}
}

int main() {
	// Initialization
	System_Clock_Init();
	LED_Init();
	EXTI_Init();

	Init_USARTx(1);

	printf("Test\n");

	while(1) {};
	
	return 0;
}
