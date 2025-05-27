#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <array>

// #define API_DEBUG //上次API debug
// #define KI_DEBUG //算法debug

#define SYSTEM_VERSION 12
#define MODIFY_VERSION  0
#define LEFT 1
#define RIGHT 2
#define JOINTS 7
#define AXES 6
#define PER_ANGLE_ENCODER (2048.0 / 180.0)
#define RAD_TO_ENCODER_COEFFICIENT (2048.0 / PI);
#define ENCODER_TO_RAD_COEFFICIENT (PI / 2048.0);
#define COEFFICIENT = 180.0 / PI;

using Coords = std::array<float, AXES>;
using Angles = std::array<float, JOINTS>;
using Encoders = std::array<int, JOINTS>;



#endif