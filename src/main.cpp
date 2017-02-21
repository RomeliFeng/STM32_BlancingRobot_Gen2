#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

#include "cmsis_device.h"
#include "Power.h"
#include "UserKey.h"
#include "LED.h"
#include "Buzzer.h"

int main(int argc, char* argv[]) {
	Power.On();
	while (1) {

	}
}

void UserKey1_ISR() {
	static uint8_t i;
	if (i == 0) {
		LED.Set(Color_Red);
		i++;
	} else if (i == 1) {
		LED.Set(Color_Green);
		i++;
	} else if (i == 2) {
		LED.Set(Color_Blue);
		i = 0;
	}
	LED.Light(ENABLE);
}

void UserKey2_ISR() {
	Buzzer.Ring(20);
}

#pragma GCC diagnostic pop
