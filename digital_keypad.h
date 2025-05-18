 /* 
 * File:   digital_keypad.h
 * Author: Muhammed Sanin A
 *
 * Created on 28 April, 2025, 7:46 PM
 */

#ifndef DIGITAL_KEYPAD_H
#define DIGITAL_KEYPAD_H

#define LEVEL					     	0
#define STATE_CHANGE			       	1

#define KEY_PORT					PORTC

//#define SWITCH1					0x0E
#define SWITCH1					0x0E
#define SWITCH2					0x0D
#define SWITCH3					0x0B
#define ALL_RELEASED					0x0F

#define INPUT_PINS					0x0F

void init_digital_keypad(void);
unsigned char read_digital_keypad(unsigned char detection_type);

#endif