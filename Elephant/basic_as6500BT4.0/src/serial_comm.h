#ifndef SERIAL_COMM_H
#define SERIAL_COMM_H

#include <M5Stack.h>
#include "config.h"
#include "gd32_comm.h"
#include <SCServo.h>

#define HEADER 0xFE
#define FOOTER 0xFA

extern byte left_encode_array[7][2];
extern byte left_atom_value_array[3];
extern byte right_encode_array[7][2];
extern byte right_atom_value_array[3];
extern byte version_l;
extern byte version_r;

void serialRead();
void Callback();
void all_data(uint8_t send_buffer[39]);
void arm_data(uint8_t arm_id, uint8_t id, uint8_t send_buffer[7]);
void arm_all_data(uint8_t arm_id, uint8_t send_buffer[22]);
int16_t* ByteArrayToInt16(const uint8_t* arr, size_t len);
int16_t ByteToInt16(const uint8_t high, const uint8_t low);
bool CheckHeader(const uint8_t* arr, size_t len);

#endif
