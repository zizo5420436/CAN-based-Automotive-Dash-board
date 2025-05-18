/*
 * File:   main.c
 * Author: Muhammed Sanin A
 *
 * Created on 29 April, 2025, 7:30 PM
 */
#include <xc.h>
#include "can.h"
#include "clcd.h"
#include <string.h>
#include "msg_id.h"
#include "message_handler.h"
extern unsigned char can_payload[13];
void init_config()
{
    init_clcd();
    init_can();
    TRISB &= ~(0xC3);
    PORTB = 0x00;
}
void main(void) 
{
    init_config();
    char speed[3]="00";
    char gear[2]="0";
    char engine[3]="00";
    char rpm[6]="00000";
    char indicator[2]="0";
    while(1)
    {
        uint16_t sid = RXB0SIDH;
        if (can_receive()) {
            char speed[6] = "00000";
            char gear[3] = "00";
            char engine[6] = "00000";
            char rpm[6] = "00000";
            char indicator[3] = "00";
            // Correct way to extract 11-bit Standard ID
            uint16_t sid = ((can_payload[SIDH] << 3) | (can_payload[SIDL] >> 5)) & 0x7FF;
            clcd_print("SP GR TMP I RPM ", LINE1(0));
            switch (sid) 
            {
                case SPEED_MSG_ID:
                    handle_speed_data(speed, can_payload[DLC] - 1);
                    clcd_print(speed, LINE2(0));
                    break;
                case GEAR_MSG_ID:
                    handle_gear_data(gear, can_payload[DLC] - 1);
                    clcd_print(gear, LINE2(3));
                    break;
                case ENG_TEMP_MSG_ID:
                    handle_engine_temp_data(engine, can_payload[DLC] - 1);
                    clcd_print(engine, LINE2(6));
                    clcd_putch('C', LINE2(8));
                    break;
                case RPM_MSG_ID:
                    handle_rpm_data(rpm,can_payload[DLC] - 1);
                    clcd_print(rpm,LINE2(12)); 
                    break;
                case INDICATOR_MSG_ID:
                    handle_indicator_data(indicator,can_payload[DLC]);
                    if(strcmp(indicator,"R") == 0)
                    {
                        RB0 = 0;
                        RB1 = 0;
                        RB6 = 1;
                        RB7 = 1;
                        
                    }else if(strcmp(indicator,"L") == 0)
                    {
                        RB0 = 1;
                        RB1 = 1;
                        RB6 = 0;
                        RB7 = 0; 
                    }
                    else if(strcmp(indicator,"0") == 0)
                    {
                        RB0 = 0;
                        RB1 = 0;
                        RB6 = 0;
                        RB7 = 0;   
                    }
                    clcd_print(indicator,LINE2(10)); 
                    break;
            }
        }
    }
}
void handle_speed_data(uint8_t *data, uint8_t len) 
{
    int i;
    for (i = 0; i < len; i++) {
        data[i] = can_payload[D0 + i];
    }
    data[i] = '\0';
}
void handle_gear_data(uint8_t *data, uint8_t len) 
{
    int i;
    for (i = 0; i < len; i++) {
        data[i] = can_payload[D0 + i];
    }
    data[i] = '\0';
}
void handle_rpm_data(uint8_t *data, uint8_t len) 
{
    int i;
    for (i = 0; i < len; i++) {
        data[i] = can_payload[D0 + i];
    }
    data[i] = '\0';
}
void handle_engine_temp_data(uint8_t *data, uint8_t len) 
{
    int i;
    for (i = 0; i < len; i++) {
        data[i] = can_payload[D0 + i];
    }
    data[i] = '\0';
}
void handle_indicator_data(uint8_t *data, uint8_t len) 
{
    int i;
    for (i = 0; i < len; i++) 
    {
        data[i] = can_payload[D0 + i];
    }
    data[i] = '\0';
}