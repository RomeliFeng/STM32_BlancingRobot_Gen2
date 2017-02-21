/*
 * Power.cpp
 *
 *  Created on: 2017��2��18��
 *      Author: Romeli
 */

#include "Power.h"

#define P_VOLTAGE_PIN GPIO_Pin_4
#define P_CURRENT_PIN GPIO_Pin_5
#define P_ON_PIN GPIO_Pin_6

PowerClass Power;

void PowerClass::On() {
	GPIOC->BSRR = P_ON_PIN;
}

void PowerClass::Off() {
	GPIOC->BRR = P_ON_PIN;
}

void PowerClass::GPIOInit() {
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

	GPIO_InitStructure.GPIO_Pin = P_ON_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = P_VOLTAGE_PIN | P_VOLTAGE_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}
