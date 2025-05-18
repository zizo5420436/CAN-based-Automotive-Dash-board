/* 
 * File:   ecu2_sensor.h
 * Author: Muhammed Sanin A
 *
 * Created on 24 April, 2025, 7:46 PM
 */

#ifndef ECU2_SENSOR_H
#define	ECU2_SENSOR_H

#include <stdint.h>
#include "digital_keypad.h"

#define RPM_ADC_CHANNEL 0x04


#define LED_OFF 0
#define LED_ON 1

#define RIGHT_IND_ON() (PORTB = PORTB | 0xC0)
#define RIGHT_IND_OFF() (PORTB = PORTB & ~0xC0)
#define LEFT_IND_ON() (PORTB = PORTB | 0x03)
#define LEFT_IND_OFF() (PORTB = PORTB & ~0x03)

typedef enum {
    e_ind_off,
    e_ind_left,
    e_ind_right
} IndicatorStatus;

extern volatile IndicatorStatus prev_ind_status, cur_ind_status;
extern volatile unsigned char led_state;

int get_rpm();
IndicatorStatus process_indicator();

#endif	/* ECU1_SENSOR_H */

