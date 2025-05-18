/*
 * File:   digital_keypad.c
 * Author: Muhammed Sanin A
 *
 * Created on 28 April, 2025, 7:46 PM
 */

#include "digital_keypad.h"
#include <xc.h>

void init_digital_keypad(void)
{
	TRISC = TRISC | INPUT_PINS;
    TRISB &= ~(0x07);        // Make only RB0, RB1, RB2 as output (0b00000111 = 0x07)
    PORTB = 0x00;
}

unsigned char read_digital_keypad(unsigned char detection_type)
{
	static unsigned char once = 1;

	if (detection_type == STATE_CHANGE)
	{
		if (((KEY_PORT & INPUT_PINS) != ALL_RELEASED) && once)
		{
			once = 0;

			return (KEY_PORT & INPUT_PINS);
		}
		else if ((KEY_PORT & INPUT_PINS) == ALL_RELEASED)
		{
			once = 1;
		}
	}
	else if (detection_type == LEVEL)
	{
		return (KEY_PORT & INPUT_PINS);
	}

	return 0xFF;
}