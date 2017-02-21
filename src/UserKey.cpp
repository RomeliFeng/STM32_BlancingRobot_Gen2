/*
 * UserKey.cpp
 *
 *  Created on: 2017年2月19日
 *      Author: Romeli
 */

#include "UserKey.h"

#define KEY1_PIN GPIO_Pin_11
#define KEY2_PIN GPIO_Pin_12

UserKeyClass UserKey;

void UserKeyClass::GPIOInit() {
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Pin = KEY1_PIN | KEY2_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void UserKeyClass::EXTIInit() {
	EXTI_InitTypeDef EXTI_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource11);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource12);

	EXTI_InitStructure.EXTI_Line = EXTI_Line11 | EXTI_Line12;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStructure);
}

void UserKeyClass::NVICInit() {
	NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	//设置为最低优先级
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 7;
	NVIC_Init(&NVIC_InitStructure);
}

void __attribute__((weak)) UserKey1_ISR() {

}
void __attribute__((weak)) UserKey2_ISR() {

}

extern "C" void EXTI15_10_IRQHandler(void) {
	if (EXTI_GetITStatus(EXTI_Line11)) {
		UserKey1_ISR();
		EXTI_ClearITPendingBit(EXTI_Line11);
	}
	if (EXTI_GetITStatus(EXTI_Line12)) {
		UserKey2_ISR();
		EXTI_ClearITPendingBit(EXTI_Line12);
	}
}
