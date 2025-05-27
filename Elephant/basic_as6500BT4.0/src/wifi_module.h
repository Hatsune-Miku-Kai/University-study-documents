#ifndef WIFI_MODULE_H
#define WIFI_MODULE_H
#include <M5Stack.h>

extern byte left_encode_array[7][2];
extern byte left_atom_value_array[3];
extern byte right_encode_array[7][2];
extern byte right_atom_value_array[3];
extern byte version_l;
extern byte version_r;

void wifi_init();
void wifi_read();
void wifi_close();

#endif
