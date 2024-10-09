/*
 *  Module: DC_Motor
 *
 *  Created on: Oct 5, 2024
 *
 * 	Author: Mahmoud Hashish
 */

#include "DC_Motor.h"
#include "gpio.h"
#include "PWM.h"
#include <avr/io.h>
#include "PWM.h"

void DcMotor_Init(void) {
	/* Initializes the DC motor by setting the direction for the motor pins and stopping the motor at the beginning */
	GPIO_setupPinDirection(PORTB_ID, PIN0_ID, LOGIC_HIGH);
	GPIO_setupPinDirection(PORTB_ID, PIN1_ID, LOGIC_HIGH);
	GPIO_writePin(PORTB_ID, PIN0_ID, LOGIC_LOW);
	GPIO_writePin(PORTB_ID, PIN1_ID, LOGIC_LOW);

}


void DcMotor_Rotate(DcMotor_State state, uint8 fan_speed) {
	/* Controls the motor's state (Clockwise/Anti-Clockwise/Stop) and adjusts the speed based on the input duty cycle */

	uint8 Duty_cycle = (fan_speed * 255) / 100;
	PWM_Timer0_Start(Duty_cycle);

	if (state == CW) {
		GPIO_writePin(PORTB_ID, PIN0_ID, LOGIC_HIGH);
		GPIO_writePin(PORTB_ID, PIN1_ID, LOGIC_LOW);
	}

	else if (state == ACW) {
		GPIO_writePin(PORTB_ID, PIN0_ID, LOGIC_LOW);
		GPIO_writePin(PORTB_ID, PIN1_ID, LOGIC_HIGH);
	}

	else if (state == STOP) {
		GPIO_writePin(PORTB_ID, PIN0_ID, LOGIC_LOW);
		GPIO_writePin(PORTB_ID, PIN1_ID, LOGIC_LOW);
	}
}
