/*
 * LEDS.c
 *
 *  Created on: Oct 4, 2024
 *      Author: mahmo
 */

#include "LEDS.h"
#include "gpio.h"

void LEDS_init(void) {
	/* Initializes all Leds (red, green, blue) pins direction, Turns off all the Leds */
	GPIO_setupPinDirection(PORTB_ID, LED_PIN5_ID, LOGIC_HIGH);
	GPIO_setupPinDirection(PORTB_ID, LED_PIN6_ID, LOGIC_HIGH);
	GPIO_setupPinDirection(PORTB_ID, LED_PIN7_ID, LOGIC_HIGH);
}
void LED_on(LED_ID id) {
	/* Turns on the specified LED */
	GPIO_writePin(PORTB_ID, id, LOGIC_HIGH);
}
void LED_off(LED_ID id) {
	/* Turns off the specified LED */
	GPIO_writePin(PORTB_ID, id, LOGIC_LOW);
}
