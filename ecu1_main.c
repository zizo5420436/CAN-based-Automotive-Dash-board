/*
 * File:   ecu1_main.c
 * Author: Muhammed Sanin A
 *
 * Created on 21 April, 2025, 8:21 AM
 */

#include <xc.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ecu1_sensor.h"
#include "clcd.h"
#include "can.h"
#include "msg_id.h"
//Checking speed from the channel and updating

uint16_t get_speed() {
    uint16_t adc_reg_val = read_adc(SPEED_ADC_CHANNEL);

    return (adc_reg_val / 10.33);
}

unsigned char get_gear_pos() {
    static unsigned char gear_pos = 0;
    char key = read_switches(STATE_CHANGE);

    if (key == GEAR_UP) {
        if (gear_pos < MAX_GEAR) {
            gear_pos++;
        }
    } else if (key == GEAR_DOWN) {
        if (gear_pos > 1) {
            gear_pos--;
        }
    } else if (key == COLLISION) {
        gear_pos = 7;
    }
    return gear_pos;
}

uint16_t get_engine_temp() {
    uint16_t adc_reg_val = read_adc(ENG_TEMP_ADC_CHANNEL);

    return ((adc_reg_val * ((float) 5 / 1023)) * 100);
}

void reverse(char *str) {
    int i = 0;
    char temp;
    int len = strlen(str);
    while (i < len / 2) {
        temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
        i++;
    }
}

void ITOA(unsigned short data, char *str) {
    int i = 0;
    char temp;
    if (data < 10) {
        str[0] = data + '0';
        str[1] = 0;
        return;
    }
    while (data) {
        temp = data % 10;
        data = data / 10;
        str[i++] = temp + '0';
    }
    str[i] = '\0';
    reverse(str);

}

static void init_config() {
    init_can();
    init_adc();
    init_matrix_keypad();
    init_clcd();
}

void main() {
    init_config(); //Configuring the pheripherals
    char speed_char[8] = "0000000";
    char temp_char[8] = "0000000";
    char posi[8] = "0000000";

    int delay = 0;
    while (1) {
        // Transmit Speed
        uint16_t speed = get_speed();
        unsigned char gear_pos = get_gear_pos();
        uint16_t engine_temp = get_engine_temp();
        
        if (gear_pos == 0) {
            strcpy(posi, "N");
        } else if (gear_pos == 6) {
            strcpy(posi, "R");
        } else {
            sprintf(posi, "%u", gear_pos); // convert number to string '1' to '5'
        }
        ITOA(engine_temp, temp_char);
        ITOA(speed, speed_char);
        if (delay++ == 100) {
              can_transmit(SPEED_MSG_ID, speed_char, strlen(speed_char) + 1);
        } else if (delay == 200)
            can_transmit(GEAR_MSG_ID, posi, strlen(posi) + 1);
        else if (delay == 300) {
            can_transmit(ENG_TEMP_MSG_ID, temp_char, strlen(temp_char) + 1);
            delay = 0;
        }
        clcd_print("SP GR TMP S RPM ", LINE1(0));
        clcd_print(speed_char, LINE2(0));
    }


}