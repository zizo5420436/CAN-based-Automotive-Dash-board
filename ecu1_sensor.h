/* 
 * File:   ecu1_sensor.h
 * Author: Muhammed Sanin A
 *
 * Created on 21 April, 2025, 8:09 AM
 */

#ifndef ECU1_SENSOR_H
#define	ECU1_SENSOR_H

#include <stdint.h>
#include "matrix_keypad.h"
#include "adc.h"
#include "can.h"

#define MAX_GEAR 6
#define SPEED_ADC_CHANNEL 0x04
#define ENG_TEMP_ADC_CHANNEL 0x06

#define GEAR_UP             MK_SW1
#define GEAR_DOWN           MK_SW2
#define COLLISION           MK_SW3

uint16_t get_speed();
unsigned char get_gear_pos();
uint16_t get_engine_temp();
void can_demo(void);

#endif	/* ECU1_SENSOR_H */