/*
 * Buzzer.h
 *
 *  Created on: 2017年2月19日
 *      Author: Romeli
 */

#ifndef BUZZER_H_
#define BUZZER_H_

#include <cmsis_device.h>

class BuzzerClass {
public:
	BuzzerClass() {
		GPIOInit();
		TIMInit();
		NVICInit();
	}
	void Ring(uint32_t hz,uint32_t ms);
	void Ring(uint32_t ms);
private:
	void GPIOInit();
	void TIMInit();
	void NVICInit();
};

extern BuzzerClass Buzzer;

#endif /* BUZZER_H_ */
