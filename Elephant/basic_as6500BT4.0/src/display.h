#ifndef DISPLAY_H
#define DISPLAY_H

#include <M5Stack.h>

extern byte left_encode_array[7][2];
extern byte left_atom_value_array[3];
extern byte right_atom_value_array[3];
extern byte right_encode_array[7][2];
extern byte version;

extern bool bleStatus;
extern bool wifiStatus;
extern bool deviceconnected;

void drawLCD();
void printText(uint16_t c, uint16_t b, int16_t x, int16_t y, uint8_t s, const char* text);
void print_left_Angle(uint16_t c, uint16_t b, int16_t x, int16_t y, uint8_t id);
void print_right_Angle(uint16_t c, uint16_t b, int16_t x, int16_t y, uint8_t id);

#endif
