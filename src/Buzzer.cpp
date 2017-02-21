/*
 * Buzzer.cpp
 *
 *  Created on: 2017年2月19日
 *      Author: Romeli
 */

#include "Buzzer.h"

#define BUZZER_PIN GPIO_Pin_8
#define BUZZER_DEFAULT_FREQUENCY 2500
#define TIM1_ENABLE TIM1->CR1 |= (uint16_t) TIM_CR1_CEN
#define TIM1_DISABLE TIM1->CR1 &= ~(uint16_t) TIM_CR1_CEN
#define TIM1_PWM_ENABLE TIM1->BDTR |= TIM_BDTR_MOE;
#define TIM1_PWM_DISABLE TIM1->BDTR &= ~(uint16_t) TIM_BDTR_MOE
BuzzerClass Buzzer;

static uint32_t DelayLast, DelayLimit;

void BuzzerClass::Ring(uint32_t hz, uint32_t ms) {
	TIM1_DISABLE;

	TIM1->ARR = SystemCoreClock / hz; //设置ARR寄存器和CCR寄存器需要关闭外设才可设置
	TIM1->CCR1 = TIM1->ARR / 2;
	//延时所需的系统时钟周期数除以TIM周期长度，求得所需的TIM周期数
	DelayLast = 0;
	DelayLimit = SystemCoreClock / 1000 * ms / TIM1->ARR;

	TIM1_ENABLE;
	TIM1_PWM_ENABLE
	;
}

void BuzzerClass::Ring(uint32_t ms) {
	Ring(BUZZER_DEFAULT_FREQUENCY, ms);
}

void BuzzerClass::GPIOInit() {
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Pin = BUZZER_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void BuzzerClass::TIMInit() {
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 24000;
	TIM_TimeBaseInitStructure.TIM_Prescaler = 0;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStructure);

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
	TIM_OCInitStructure.TIM_Pulse = 12000;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);

	TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
}

void BuzzerClass::NVICInit() {
	NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	//设置为最低优先级
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 7;
	NVIC_Init(&NVIC_InitStructure);
}

extern "C" void TIM1_UP_IRQHandler(void) {
	if (TIM_GetITStatus(TIM1, TIM_IT_Update)) {
		DelayLast++;
		if (DelayLimit < DelayLast) {
			TIM1_DISABLE;
			TIM1_PWM_DISABLE; //关闭PWM输出，默认为低电平（防止蜂鸣器一直通电）
		}
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
	}
}
