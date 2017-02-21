/*
 * LED.cpp
 *
 *  Created on: 2017年2月19日
 *      Author: Romeli
 */

#include "LED.h"

#define RED_PIN GPIO_Pin_10
#define GREEN_PIN GPIO_Pin_11
#define BLUE_PIN GPIO_Pin_12
#define LIGHT_PIN GPIO_Pin_15

#define RED_ON GPIOC->BRR = RED_PIN //置为低电平
#define RED_OFF GPIOC->BSRR = RED_PIN //置为高电平
#define GREEN_ON GPIOC->BRR = GREEN_PIN //置为低电平
#define GREEN_OFF GPIOC->BSRR = GREEN_PIN //置为高电平
#define BLUE_ON GPIOC->BRR = BLUE_PIN //置为低电平
#define BLUE_OFF GPIOC->BSRR = BLUE_PIN //置为高电平
#define LIGHT_ON GPIOA->BSRR = LIGHT_PIN //置为高电平
#define LIGHT_OFF GPIOA->BRR = LIGHT_PIN //置为低电平

LEDClass LED;

void LEDClass::Set(Color_Typedef color) {
	switch (color) {
	case Color_Red:
		RED_ON;
		GREEN_OFF;
		BLUE_OFF;
		break;
	case Color_Green:
		RED_OFF;
		GREEN_ON;
		BLUE_OFF;
		break;
	case Color_Blue:
		RED_OFF;
		GREEN_OFF;
		BLUE_ON;
		break;
	default:
		break;
	}
}

void LEDClass::Light(uint8_t NewState) {
	if (NewState != DISABLE) {
		LIGHT_ON;
	} else {
		LIGHT_OFF;
	}
}

void LEDClass::GPIOInit() {
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(
	RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Pin = RED_PIN | GREEN_PIN | BLUE_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	RED_OFF;
	GREEN_OFF;
	BLUE_OFF;
	LIGHT_OFF;
}

