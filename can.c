/*
 * File:   can.c
 * Author: Muhammed Sanin A
 *
 * Created on 21 April, 2025, 8:20 AM
 */

#include <xc.h>
#include "can.h"

/* Global Variables */
unsigned char can_payload[13];

typedef enum _CanOpMode {
    e_can_op_mode_bits = 0xE0, /* Use this to access opmode bits */
    e_can_op_mode_normal = 0x00,
    e_can_op_mode_sleep = 0x20,
    e_can_op_mode_loop = 0x40,
    e_can_op_mode_listen = 0x60,
    e_can_op_mode_config = 0x80
} CanOpMode;

/* Configure the CAN Module */
void init_can(void) {
    /* CAN_TX = RB2, CAN_RX = RB3 */
    TRISB2 = 0; /* CAN TX */
    TRISB3 = 1; /* CAN RX */

    CAN_SET_OPERATION_MODE_NO_WAIT(e_can_op_mode_config);

    /* Enter CAN module into config mode */
    CANSTAT &= 0x1F; /* clear previous mode */
    CANSTAT |= 0x80; /* set new mode */

    /* Wait untill desired mode is set */
    while (CANSTAT != 0x80);

    /* Enter CAN module into Mode 0 */
    ECANCON = 0x00;

    /* Initialize CAN Timing 8MHz */
    BRGCON1 = 0xE1; /* 1110 0001, SJW=4, TQ, BRP 4 */
    BRGCON2 = 0x1B; /* 0001 1011, SEG2PHTS 1 sampled once PS1=4TQ PropagationT 4TQ */
    BRGCON3 = 0x03; /* 0000 0011, PS2, 4TQ */

    /*
     * Enable Filters
     * Filter 0
     */
    RXFCON0 = 0x00;

    /*
     * Initialize Receive Filters
     * Filter 0 = 0xFFC
     */
    RXF0EIDH = 0x00;
    RXF0EIDL = 0x00;
    RXF0SIDH = 0x00;
    RXF0SIDL = 0x00;

    /* Enter CAN module into Loop back mode */
    CAN_SET_OPERATION_MODE_NO_WAIT(e_can_op_mode_normal);
    /* Set Receive Mode for buffers */
    RXB0CON = 0x60;
}

/* Check the buffers, if it have message */
unsigned char can_receive(void) {
    unsigned char rx_msg_flag = 0;

    if (RXB0FUL) /* CheckRXB0 */ //set as 1 if recieved full 
    {
        can_payload[EIDH] = RXB0EIDH;
        can_payload[EIDL] = RXB0EIDL;
        can_payload[SIDH] = RXB0SIDH;
        can_payload[SIDL] = RXB0SIDL;
        can_payload[DLC] = RXB0DLC;
        //character array - user defined array D0-D7 
        can_payload[D0] = RXB0D0;
        can_payload[D1] = RXB0D1;
        can_payload[D2] = RXB0D2;
        can_payload[D3] = RXB0D3;
        can_payload[D4] = RXB0D4;
        can_payload[D5] = RXB0D5;
        can_payload[D6] = RXB0D6;
        can_payload[D7] = RXB0D7;

        RXB0FUL = 0;
        RXB0IF = 0;

        return TRUE;
    } else {
        return FALSE;
    }
}

/* Transmit Sample Mesaage */
void can_transmit(uint16_t msg_id, const uint8_t *data, uint8_t len) {
    TXB0EIDH = 0x00; /* Extended Identifier */
    TXB0EIDL = 0x00; /* Extended Identifier */

    TXB0SIDH = ((msg_id >> 3) & 0xFF); // Pack ID correctly
    TXB0SIDL = ((msg_id << 5) & 0xE0);

    TXB0DLC = len & 0x0F;

    TXB0D0 = data[0];
    TXB0D1 = data[1];
    TXB0D2 = data[2];
    TXB0D3 = data[3];
    TXB0D4 = data[4];
    TXB0D5 = data[5];
    TXB0D6 = data[6];
    TXB0D7 = data[7];

    TXB0REQ = 1; // Set to transmit

    while (TXB0REQ);
}
