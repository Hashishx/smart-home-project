/*
 *  Module: Flame_Sensor
 *
 *  Created on: Oct 4, 2024
 *
 *  Author: Mahmoud Hashish
 */

#include "Flame_Sensor.h"
#include "gpio.h"

void FlameSensor_init(void) {
	/* Initializes the flame sensor pin direction */
	GPIO_setupPinDirection(PORTD_ID, PIN2_ID, LOGIC_HIGH);
}
uint8 FlameSensor_getValue(void) {
	/* Reads the value from the flame sensor and returns it */
	uint8 value;
	value = GPIO_readPin(PORTD_ID, PIN2_ID);
	return value;
}
