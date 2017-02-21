/*
 * LED.h
 *
 *  Created on: 2017年2月19日
 *      Author: Romeli
 */

#ifndef LED_H_
#define LED_H_

#include "cmsis_device.h"

typedef enum _Color_Typedef {
	Color_Red, Color_Green, Color_Blue
} Color_Typedef;

class LEDClass {
public:
	LEDClass() {
		GPIOInit();
	}
	void Set(Color_Typedef color);
	void Light(uint8_t NewState);
private:
	void GPIOInit();
};

extern LEDClass LED;

#endif /* LED_H_ */
