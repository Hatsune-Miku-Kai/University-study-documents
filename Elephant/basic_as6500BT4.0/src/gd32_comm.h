#ifndef GD32_COMM_H
#define GD32_COMM_H

#include <M5Stack.h>
#include "config.h"

extern byte left_encode_array[7][2];
extern byte left_atom_value_array[3];
extern byte right_encode_array[7][2];
extern byte right_atom_value_array[3];
extern byte version_l;
extern byte version_r;

void RGD32Data();
void LGD32Data();
Angles GetAngles(byte robot = 1, bool is_rad = false);
Coords GetCoords(byte robot = 1);

#endif
