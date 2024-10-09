/*
 *  Module: LDR
 *
 *  Created on: Oct 4, 2024
 *
 *  Author: Mahmoud Hashish
 */

#include "LDR.h"
#include "adc.h"


uint16 LDR_getLightIntensity(void) {

	uint8 LDR_Percentage = 0;

	uint16 adc_value = 0;

	/* Read ADC channel where the temperature sensor is connected */
	adc_value = ADC_readChannel(LDR_SENSOR_CHANNEL_ID);
	/* Calculate the LDR percentage */
	LDR_Percentage = (uint8)(((uint32)adc_value*LDR_SENSOR_MAX_LIGHT_INTENSITY*ADC_REF_VOLT_VALUE)/(ADC_MAXIMUM_VALUE*LDR_SENSOR_MAX_VOLT_VALUE));

	return LDR_Percentage;
}
