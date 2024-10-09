/*
 *  Module: LEDS
 *
 *  Created on: Oct 4, 2024
 *
 *  Author: Mahmoud Hashish
 */

#ifndef LEDS_H_
#define LEDS_H_

typedef enum {
	LED_PIN5_ID = 5, LED_PIN6_ID, LED_PIN7_ID
}LED_ID;

void LEDS_init(void);

void LED_on(LED_ID id);

void LED_off(LED_ID id);

#endif /* LEDS_H_ */
