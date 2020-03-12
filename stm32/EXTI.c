/*
 * ECE 153B - Winter 2020
 *
 * Name(s): Norman Chung, Andrew Lu
 * Section: Wed 7-9:50 PM
 * Lab: 1B
 */

#include "EXTI.h"
#include "LED.h"

#include "string.h"
#include "stdio.h"

void EXTI_Init(void) {
	// Initialize Joystick
	GPIOA -> MODER &= ~GPIO_MODER_MODE0_0;
	GPIOA -> MODER &= ~GPIO_MODER_MODE0_1;
	GPIOA -> MODER &= ~GPIO_MODER_MODE1_0;
	GPIOA -> MODER &= ~GPIO_MODER_MODE1_1;
	GPIOA -> MODER &= ~GPIO_MODER_MODE2_0;
	GPIOA -> MODER &= ~GPIO_MODER_MODE2_1;
	GPIOA -> MODER &= ~GPIO_MODER_MODE3_0;
	GPIOA -> MODER &= ~GPIO_MODER_MODE3_1;

	GPIOA -> PUPDR &= ~GPIO_PUPDR_PUPD0_0;
	GPIOA -> PUPDR |= GPIO_PUPDR_PUPD0_1;
	GPIOA -> PUPDR &= ~GPIO_PUPDR_PUPD1_0;
	GPIOA -> PUPDR |= GPIO_PUPDR_PUPD1_1;
	GPIOA -> PUPDR &= ~GPIO_PUPDR_PUPD2_0;
	GPIOA -> PUPDR |= GPIO_PUPDR_PUPD2_1;
	GPIOA -> PUPDR &= ~GPIO_PUPDR_PUPD3_0;
	GPIOA -> PUPDR |= GPIO_PUPDR_PUPD3_1;
	
	// Configure SYSCFG EXTI
	// PA0
	SYSCFG -> EXTICR[0] &= ~SYSCFG_EXTICR1_EXTI0;
	SYSCFG -> EXTICR[0] |= SYSCFG_EXTICR1_EXTI0_PA;

	// PA1
	SYSCFG -> EXTICR[0] &= ~SYSCFG_EXTICR1_EXTI1;
	SYSCFG -> EXTICR[0] |= SYSCFG_EXTICR1_EXTI1_PA;

	// PA2
	SYSCFG -> EXTICR[0] &= ~SYSCFG_EXTICR1_EXTI2;
	SYSCFG -> EXTICR[0] |= SYSCFG_EXTICR1_EXTI2_PA;

	// PA3
	SYSCFG -> EXTICR[0] &= ~SYSCFG_EXTICR1_EXTI3;
	SYSCFG -> EXTICR[0] |= SYSCFG_EXTICR1_EXTI3_PA;
	
	// Configure EXTI Trigger
	EXTI -> RTSR1 |= EXTI_RTSR1_RT0;
	EXTI -> RTSR1 |= EXTI_RTSR1_RT1;
	EXTI -> RTSR1 |= EXTI_RTSR1_RT2;
	EXTI -> RTSR1 |= EXTI_RTSR1_RT3;
	EXTI -> FTSR1 |= EXTI_FTSR1_FT0;
	EXTI -> FTSR1 |= EXTI_FTSR1_FT1;
	EXTI -> FTSR1 |= EXTI_FTSR1_FT2;
	EXTI -> FTSR1 |= EXTI_FTSR1_FT3;
	
	// Enable EXTI
	EXTI -> IMR1 |= EXTI_IMR1_IM0;
	EXTI -> IMR1 |= EXTI_IMR1_IM1;
	EXTI -> IMR1 |= EXTI_IMR1_IM2;
	EXTI -> IMR1 |= EXTI_IMR1_IM3;
	
	// Configure and Enable in NVIC
	NVIC_EnableIRQ(EXTI0_IRQn);
	NVIC_SetPriority(EXTI0_IRQn, 0);
	NVIC_EnableIRQ(EXTI1_IRQn);
	NVIC_SetPriority(EXTI1_IRQn, 0);
	NVIC_EnableIRQ(EXTI2_IRQn);
	NVIC_SetPriority(EXTI2_IRQn, 0);
	NVIC_EnableIRQ(EXTI3_IRQn);
	NVIC_SetPriority(EXTI3_IRQn, 0);
}

// Write Interrupt Handlers (look in startup_stm32l476xx.s to find the 
// interrupt handler names that you should use)
void EXTI0_IRQHandler(void) {
	EXTI -> PR1 |= EXTI_PR1_PIF0;

	if((GPIOA -> IDR) & GPIO_IDR_ID0) {
		Red_LED_On();
		printf("UP");
	}
	else {
		Red_LED_Off();
		printf("UR");
	}
}

void EXTI1_IRQHandler(void) {
	EXTI -> PR1 |= EXTI_PR1_PIF1;

	if((GPIOA -> IDR) & GPIO_IDR_ID1) {
		Red_LED_On();
		printf("DP");
	}
	else {
		Red_LED_Off();
		printf("DR");
	}
}
void EXTI2_IRQHandler(void) {
	EXTI -> PR1 |= EXTI_PR1_PIF2;

	if((GPIOA -> IDR) & GPIO_IDR_ID2) {
		Red_LED_On();
		printf("LP");
	}
	else {
		Red_LED_Off();
		printf("LR");
	}
}

void EXTI3_IRQHandler(void) {
	EXTI -> PR1 |= EXTI_PR1_PIF3;

	if((GPIOA -> IDR) & GPIO_IDR_ID3) {
		Red_LED_On();
		printf("RP");
	}
	else {
		Red_LED_Off();
		printf("RR");
	}
}
