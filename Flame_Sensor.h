/*
 *  Module: Flame_Sensor
 *
 *  Created on: Oct 4, 2024
 *
 *  Author: Mahmoud Hashish
 */

#ifndef FLAME_SENSOR_H_
#define FLAME_SENSOR_H_

#include "std_types.h"

void FlameSensor_init(void);

uint8 FlameSensor_getValue(void);

#endif /* FLAME_SENSOR_H_ */
