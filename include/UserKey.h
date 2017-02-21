/*
 * UserKey.h
 *
 *  Created on: 2017年2月19日
 *      Author: Romeli
 */

#ifndef USERKEY_H_
#define USERKEY_H_

#include "cmsis_device.h"

class UserKeyClass {
public:
	UserKeyClass() {
		GPIOInit();
		EXTIInit();
		NVICInit();
	}
private:
	void GPIOInit();
	void EXTIInit();
	void NVICInit();
};

extern UserKeyClass UserKey;
extern void UserKey1_ISR();
extern void UserKey2_ISR();

#endif /* USERKEY_H_ */
