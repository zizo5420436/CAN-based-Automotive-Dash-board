/*
 * File:   ecu2_sensor.c
 * Author: Muhammed Sanin A
 *
 * Created on 24 April, 2025, 7:55 PM
 */
#include <xc.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ecu2_sensor.h"
#include "digital_keypad.h"
//#include "clcd.h"
#include "msg_id.h"
#include "adc.h"
#include "can.h"
volatile IndicatorStatus prev_ind_status = e_ind_off;
volatile IndicatorStatus cur_ind_status = e_ind_off;
extern unsigned char can_payload[13];
int get_rpm()
{
    unsigned int adc_rpm_val = read_adc(RPM_ADC_CHANNEL);
    return (adc_rpm_val*6.84269);
}
IndicatorStatus process_indicator()
{
   char key = read_digital_keypad(STATE_CHANGE);

        if (key == SWITCH1)
        {
            //cur_ind_status = e_ind_right;
            RB0 = 1;
            RB1 = 0;
            RB2 = 0;
            
            return e_ind_left;
        }
        else if (key == SWITCH2)
        {
           // cur_ind_status = e_ind_left;
            RB0 = 0;
            RB1 = 1;
            RB2 = 0;
            
            return e_ind_right;
        }
        else if (key == SWITCH3)
        {
           // cur_ind_status = e_ind_off;
            RB0 = 0;
            RB1 = 0;
            RB2 = 0;
            
            return e_ind_off;
        }
}

void reverse(char *str)
{
    int i=0;
    char temp;
    int len=strlen(str);
    while(i<len/2)
    {
        temp=str[i];
        str[i]=str[len-1-i];
        str[len-1-i]=temp;
        i++;
    }
}
void ITOA(unsigned int data,char *str)
{
    int i=0;
    char temp;
    if(data<10)
    {
        str[0]=data+'0';
        str[1]=0;
        return;
    }
    while(data)
    {
        temp=data%10;
        data=data/10;
        str[i++]=temp+'0';
    }
    str[i]='\0';
    reverse(str);
    
}
static void init_config()
{
    init_can();
    init_adc();
    init_digital_keypad();
    //init_clcd();
}

void main(void) 
{
    init_config();
    IndicatorStatus status;
    
    char rpm_str[6];
    char indicator[8] = "0000000";
    while(1)
    {
        int rpm_val = get_rpm();
        sprintf(rpm_str, "%u", rpm_val); // right align
        can_transmit(RPM_MSG_ID,rpm_str,strlen(rpm_str)+1);
        status = process_indicator();
        if(status == e_ind_off)
        {
            strcpy(indicator,"0");
            can_transmit(INDICATOR_MSG_ID,indicator,strlen(indicator)+1);
        }
        else if(status == e_ind_right)
        {
            strcpy(indicator,"R");
            can_transmit(INDICATOR_MSG_ID,indicator,strlen(indicator)+1);
        }
        else if(status == e_ind_left)
        {
            strcpy(indicator,"L");
            can_transmit(INDICATOR_MSG_ID,indicator,strlen(indicator)+1);
        }
        
    }
}

