#include "gd32_comm.h"
#include "kinematics.hpp"
#include <set>
#include <SCServo.h>

RobotKinematics kinematics;

byte ID[7] = {1, 2, 3, 4, 5, 6, 7};
byte atom_command[5] = {0xFE, 0xFE, 0x02, 0x01, 0xFA};
Encoders encoders = {0};
Angles angles = {0};

extern SemaphoreHandle_t xMutex_latom; // 互斥锁句柄
extern SemaphoreHandle_t xMutex_ratom; // 互斥锁句柄
extern SemaphoreHandle_t xMutex_lgd;   // 互斥锁句柄
extern SemaphoreHandle_t xMutex_rgd;   // 互斥锁句柄
extern SMS_STS smR;
extern SMS_STS smL;

void int2Bytes(byte bytes_temp[2], int int_variable)
{
  bytes_temp[0] = (int_variable >> 8) & 0xFF;
  bytes_temp[1] = int_variable & 0xFF;
}

void LGD32Data()
{
  for (char i = 0; i < sizeof(ID); i++)
  {
    int encode = smL.ReadPos(ID[i]);
    if (encode == -1)
      continue;
    byte bytes_temp[2];
    int2Bytes(bytes_temp, encode);
    // Serial.printf("id: %d, encode: %d\n", ID[i], encode);
    if (xSemaphoreTake(xMutex_lgd, portMAX_DELAY))
    {
      left_encode_array[ID[i] - 1][0] = bytes_temp[0];
      left_encode_array[ID[i] - 1][1] = bytes_temp[1];
      xSemaphoreGive(xMutex_lgd);
    }
  }
  Serial2.write(atom_command, sizeof(atom_command));
  vTaskDelay(3);
  if (Serial2.available())
  {
    // 读取单数据判断帧头1
    uint8_t start1 = Serial2.read();
    // 判断是否帧头
    if (start1 != 0xfe)
      return;
    // 读取单数据判断帧头2
    uint8_t start2 = Serial2.read();
    // 判断是否帧头
    if (start2 != 0xfe)
      return;
    // 读取数据长度
    uint8_t data_len = Serial2.read();
    // 读取数据包并判断帧尾
    byte read_buf[data_len];
    if (Serial2.readBytes(read_buf, data_len) == data_len && read_buf[data_len - 1] == 0xfa)
    {
      // 读取数据包中的令
      u_int8_t command_data = read_buf[0];
      // 判断id和指令是否一致
     if (command_data == 0x01)
      {
        // 获取3字节按钮及摇杆数据
        if (xSemaphoreTake(xMutex_latom, portMAX_DELAY))
        {
          left_atom_value_array[0] = read_buf[1];
          left_atom_value_array[1] = read_buf[2];
          left_atom_value_array[2] = read_buf[3];
          version_l = read_buf[4];
          xSemaphoreGive(xMutex_latom);
        }
      }
    }
  }
}

void RGD32Data()
{
  for (char i = 0; i < sizeof(ID); i++)
  {
    int encode = smR.ReadPos(ID[i]);
    if (encode == -1)
      continue;
    byte bytes_temp[2];
    int2Bytes(bytes_temp, encode);
    if (xSemaphoreTake(xMutex_rgd, portMAX_DELAY))
    {
      right_encode_array[ID[i] - 1][0] = bytes_temp[0];
      right_encode_array[ID[i] - 1][1] = bytes_temp[1];
      xSemaphoreGive(xMutex_rgd);
    }
  }
  Serial1.write(atom_command, sizeof(atom_command));
  vTaskDelay(3);
  if (Serial1.available())
  {
    // 读取单数据判断帧头1
    uint8_t start1 = Serial1.read();
    // Serial.printf("s1: %x\n", start1);
    // 判断是否帧头
    if (start1 != 0xfe)
      return;
    // 读取单数据判断帧头2
    uint8_t start2 = Serial1.read();
    // 判断是否帧头
    if (start2 != 0xfe)
      return;
    // 读取数据长度
    uint8_t data_len = Serial1.read();
    // 读取数据包并判断帧尾
    byte read_buf[data_len];
    if (Serial1.readBytes(read_buf, data_len) == data_len && read_buf[data_len - 1] == 0xfa)
    {
      // 读取数据包中的令
      u_int8_t command_data = read_buf[0];
      // 判断id和指令是否一致
      if (command_data == 0x01)
      {
        // 获取3字节按钮及摇杆数据
        if (xSemaphoreTake(xMutex_ratom, portMAX_DELAY))
        {
          right_atom_value_array[0] = read_buf[1];
          right_atom_value_array[1] = read_buf[2];
          right_atom_value_array[2] = read_buf[3];
          version_r = read_buf[4];
          xSemaphoreGive(xMutex_ratom);
        }
      }
    }
  }
  // vTaskDelay(3);
}

/**
 * @brief Get the Angles object
 *
 * @param robot 1-left 2-right default 1
 * @return Angles
 */
Angles GetAngles(byte robot, bool is_rad)
{
  Angles rad = {0};
#ifdef API_DEBUG
  Serial.printf("GetAngles %d\n", robot);
#endif
  for (int i = 0; i < JOINTS; ++i)
  {
    if (robot == LEFT)
    {
      encoders[i] = (left_encode_array[i][0] << 8) | left_encode_array[i][1];
    }
    else
    {
      encoders[i] = (right_encode_array[i][0] << 8) | right_encode_array[i][1];
    }
    rad[i] = (encoders[i] - 2048) * ENCODER_TO_RAD_COEFFICIENT;
  }
  kinematics.cvDirServoToJoint(rad);
  rad[3] -= PI / 4.0;
  rad[5] += 3 * PI / 4.0;
  if (is_rad == true)
  {
    return rad;
  }
  Angles angles = kinematics.cvRadToDegree(rad);
#ifdef KI_DEBUG
  kinematics.ArrayPrintAngles(angles, "angles");
#endif
  return angles;
}

Coords GetCoords(byte robot)
{
  Angles rad = GetAngles(robot, 1);
  Coords coord = kinematics.ForwardKinematics(rad);
  Coords BaseCoord;
  if (robot == LEFT)
  {
    BaseCoord = kinematics.SingleToBaseCoords(coord, LEFT);
  }
  else
  {
    BaseCoord = kinematics.SingleToBaseCoords(coord, RIGHT);
  }
  kinematics.CvtRadCoordsToCoords(&BaseCoord);
#ifdef KI_DEBUG
  kinematics.ArrayPrintAngles(rad, "rad");
  kinematics.ArrayPrintCoords(BaseCoord, "BaseCoord");
#endif
  return BaseCoord;
}