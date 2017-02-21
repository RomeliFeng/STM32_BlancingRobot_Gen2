/*
 * Power.h
 *
 *  Created on: 2017��2��18��
 *      Author: Romeli
 */

#ifndef POWER_H_
#define POWER_H_

#include "cmsis_device.h"

class PowerClass {
public:
	PowerClass() {
		GPIOInit();
	}
	void On();
	void Off();
private:
	void GPIOInit();
};

extern PowerClass Power;

#endif /* POWER_H_ */
