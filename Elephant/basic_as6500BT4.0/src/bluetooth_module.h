#ifndef BLUETOOTH_MODULE_H
#define BLUETOOTH_MODULE_H
#include <string>
#include "serial_comm.h"
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <BluetoothSerial.h>


using namespace std;
// #define ARDUINOOSC_DEBUGLOG_ENABLE
// #define MAX_SRV_CLIENTS 1   //定义最大连接数量
// #define REMOVE_BONDED_DEVICES 0     //启动时不移除已配对的设备
// #define PAIR_MAX_DEVICES 20         //最大可存储的已配对设备数量

extern byte left_encode_array[7][2];
extern byte left_atom_value_array[3];
extern byte right_encode_array[7][2];
extern byte right_atom_value_array[3];
extern bool bleStatus;
#endif

void CreatBT();
void GetBTData();
void CloseBT();
