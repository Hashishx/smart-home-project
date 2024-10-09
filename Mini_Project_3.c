/*
 * 	Mini_Project_3.c
 *
 *  Created on: Oct 4, 2024
 *
 *  Author: Mahmoud Hashish
 */

#include <avr/io.h>
#include "common_macros.h"
#include "adc.h"
#include "lcd.h"
#include "LDR.h"
#include "gpio.h"
#include "LEDS.h"
#include "Flame_Sensor.h"
#include "Buzzer.h"
#include "lm35_sensor.h"
#include "PWM.h"
#include "DC_Motor.h"

int main (void) {

	uint8 LDR_Percent        = 0;
	uint8 Flame_Sensor_Value = 0;
	uint8 Temp_Value         = 0;
	uint8 flag               = 0;

	LCD_init();				/* initialize LCD driver	  */
	ADC_init();				/* initialize ADC driver	 */
	LEDS_init();			/* initialize LEDS 		 	*/
	FlameSensor_init();		/* initialize Flame Sensor */
	Buzzer_init();			/* initialize Buzzer 	  */
	DcMotor_Init();			/* initialize DC Motor   */
	/* Text that will be shown only once*/
	LCD_displayStringRowColumn(0,3,"Fan is    ");
	LCD_displayStringRowColumn(1,0,"Temp=  C");
	LCD_displayStringRowColumn(1,8,"LDR=   %");

	while (1) {
		/* Check for fire */
		Flame_Sensor_Value = FlameSensor_getValue();

		if (Flame_Sensor_Value == LOGIC_HIGH) {
			if (flag == 0) {
				Buzzer_on();
				LCD_clearScreen();
				LCD_displayString("Critical Alert!!");
				while(Flame_Sensor_Value == LOGIC_HIGH) {
					Flame_Sensor_Value = FlameSensor_getValue();
				}
				LCD_clearScreen();
				LCD_displayStringRowColumn(0,3,"Fan is    ");
				LCD_displayStringRowColumn(1,0,"Temp= C");
				LCD_displayStringRowColumn(1,8,"LDR=   %");
			}
			flag = 1;
		}
		else {
			flag = 0;
			Buzzer_off();
		}

		/* Get the Light Intensity Percentage */
		LDR_Percent = LDR_getLightIntensity();
		/* 3 LEDS Configuration according to the LDR percentage */
		if (LDR_Percent < 15) {
			LED_on(LED_PIN5_ID);
			LED_on(LED_PIN6_ID);
			LED_on(LED_PIN7_ID);
		}
		else if (LDR_Percent >= 16 && LDR_Percent < 50) {
			LED_on(LED_PIN5_ID);
			LED_on(LED_PIN6_ID);
			LED_off(LED_PIN7_ID);
		}
		else if (LDR_Percent >= 51 && LDR_Percent < 70) {
			LED_on(LED_PIN5_ID);
			LED_off(LED_PIN6_ID);
			LED_off(LED_PIN7_ID);
		}
		else if (LDR_Percent > 70) {
			LED_off(LED_PIN5_ID);
			LED_off(LED_PIN6_ID);
			LED_off(LED_PIN7_ID);
		}
		/* Display the LDR percentage value every time at the same position */
		LCD_moveCursor(1, 12);
		if (LDR_Percent >= 100) {
			LCD_intgerToString(LDR_Percent);
		} else {
			LCD_intgerToString(LDR_Percent);
			/* In case the digital value is two or one digits print space in the next digit place */
			LCD_displayCharacter(' ');
		}

		/* Read the Temperature */
		Temp_Value = LM35_getTemperature();
		/* Display the Temperature value every time at the same position */
		LCD_moveCursor(1, 5);
		if (Temp_Value >= 100) {
			LCD_intgerToString(Temp_Value);
		} else {
			LCD_intgerToString(Temp_Value);
			/* In case the digital value is two or one digits print space in the next digit place */
			LCD_displayCharacter(' ');
		}

		/* Conditions for operating the fan and updating the LCD by the fan's new state */
		if (Temp_Value >= 40) {
			DcMotor_Rotate(CW, 100);
			LCD_displayStringRowColumn(0, 10, "ON");
			LCD_displayCharacter(' ');
		}

		else if (Temp_Value >= 35 && Temp_Value < 40) {
			DcMotor_Rotate(CW, 75);
			LCD_displayStringRowColumn(0, 10, "ON");
			LCD_displayCharacter(' ');

		}

		else if (Temp_Value >= 30 && Temp_Value < 35) {
			DcMotor_Rotate(ACW, 50);
			LCD_displayStringRowColumn(0, 10, "ON");
			LCD_displayCharacter(' ');

		}
		else if (Temp_Value >= 25 && Temp_Value < 30) {
			DcMotor_Rotate(ACW, 25);
			LCD_displayStringRowColumn(0, 10, "ON");
			LCD_displayCharacter(' ');

		}
		else if (Temp_Value < 25) {
			DcMotor_Rotate(STOP, 0);
			LCD_displayStringRowColumn(0, 10, "OFF");
		}
	}
}
