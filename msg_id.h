/* 
 * File:   msg_id.h
 * Author: Muhammed Sanin A
 *
 * Created on 21 April, 2025, 8:12 AM
 */

#ifndef MSG_ID_H
#define	MSG_ID_H

#define SPEED_MSG_ID 0x10
#define GEAR_MSG_ID 0x20
#define RPM_MSG_ID 0x30
#define ENG_TEMP_MSG_ID 0x40
#define INDICATOR_MSG_ID 0x50


#endif	/* MSG_ID_H */

void process_canbus_data();
void handle_speed_data(uint8_t *data, uint8_t len);
void handle_gear_data(uint8_t *data, uint8_t len);
void handle_rpm_data(uint8_t *data, uint8_t len);
void handle_engine_temp_data(uint8_t *data, uint8_t len);
void handle_indicator_data(uint8_t *data, uint8_t len);
