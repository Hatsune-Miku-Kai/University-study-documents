#include "serial_comm.h"
#include <SCServo.h>

extern SemaphoreHandle_t xMutex_latom; // 互斥锁句柄
extern SemaphoreHandle_t xMutex_ratom; // 互斥锁句柄
extern SemaphoreHandle_t xMutex_lgd;   // 互斥锁句柄
extern SemaphoreHandle_t xMutex_rgd;   // 互斥锁句柄
extern SMS_STS smR;
extern SMS_STS smL;
byte return_data[] = {HEADER, HEADER, 3, 0, 1, FOOTER};

void all_data(uint8_t send_buffer[63])
{
  send_buffer[0] = 0xFE;
  send_buffer[1] = 0xFE;
  send_buffer[2] = 0x3c;
  send_buffer[3] = 0x01;
  // 左臂编码器数据
  if (xSemaphoreTake(xMutex_lgd, portMAX_DELAY))
  {
    for (byte i = 0; i < 7; i++)
    {
      send_buffer[4 + 2 * i] = left_encode_array[i][0];
      send_buffer[4 + (2 * i + 1)] = left_encode_array[i][1];
    }
    xSemaphoreGive(xMutex_lgd);
  }
  // 左臂atom数据
  if (xSemaphoreTake(xMutex_latom, portMAX_DELAY))
  {
    for (byte j = 0; j < 3; j++)
    {
      send_buffer[18 + j] = left_atom_value_array[j];
    }
    xSemaphoreGive(xMutex_latom);
  }
  // 右臂编码器数据
  if (xSemaphoreTake(xMutex_rgd, portMAX_DELAY))
  {
    for (byte n = 0; n < 7; n++)
    {
      send_buffer[21 + 2 * n] = right_encode_array[n][0];
      send_buffer[21 + (2 * n + 1)] = right_encode_array[n][1];
    }
    xSemaphoreGive(xMutex_rgd);
  }
  // 右臂atom数据
  if (xSemaphoreTake(xMutex_ratom, portMAX_DELAY))
  {
    for (byte l = 0; l < 3; l++)
    {
      send_buffer[35 + l] = right_atom_value_array[l];
    }
    xSemaphoreGive(xMutex_ratom);
  }
   for (int j = 0; j < 2; ++j) 
  {
    Coords coords = GetCoords(j+1);
    for (int i = 0; i < AXES; ++i) 
    {
      send_buffer[38+(2*i)+(j*12)] = highByte(static_cast<int>(coords[i]*100));
      send_buffer[38+((2*i)+1)+(j*12)] = lowByte(static_cast<int>(coords[i]*100));
    }
  }
  send_buffer[62] = 0xFA;
}

void arm_all_data(uint8_t arm_id, uint8_t send_buffer[34])
{
  send_buffer[0] = 0xFE;
  send_buffer[1] = 0xFE;
  send_buffer[2] = 0x1F;
  send_buffer[3] = 0x02;
  if (arm_id == 1)
  {
    // 左臂编码器数据
    if (xSemaphoreTake(xMutex_lgd, portMAX_DELAY))
    {
      for (byte i = 0; i < 7; i++)
      {
        send_buffer[4 + 2 * i] = left_encode_array[i][0];
        send_buffer[4 + (2 * i + 1)] = left_encode_array[i][1];
      }
      xSemaphoreGive(xMutex_lgd);
    }
    // 左臂atom数据
    if (xSemaphoreTake(xMutex_latom, portMAX_DELAY))
    {
      for (byte j = 0; j < 3; j++)
      {
        send_buffer[18 + j] = left_atom_value_array[j];
      }
      xSemaphoreGive(xMutex_latom);
    }
  }
  else if (arm_id == 2)
  {
    // 右臂编码器数据
    if (xSemaphoreTake(xMutex_rgd, portMAX_DELAY))
    {
      for (byte k = 0; k < 7; k++)
      {
        send_buffer[4 + 2 * k] = right_encode_array[k][0];
        send_buffer[4 + (2 * k + 1)] = right_encode_array[k][1];
      }
      xSemaphoreGive(xMutex_rgd);
    }
    // 右臂atom数据
    if (xSemaphoreTake(xMutex_ratom, portMAX_DELAY))
    {
      for (byte l = 0; l < 3; l++)
      {
        send_buffer[18 + l] = right_atom_value_array[l];
      }
      xSemaphoreGive(xMutex_ratom);
    }
  }
 Coords coords = GetCoords(arm_id);
  for (int i = 0; i < AXES; ++i) {
    send_buffer[21+(2*i)] = highByte(static_cast<int>(coords[i] * 100));
    send_buffer[21+((2*i)+1)] = lowByte(static_cast<int>(coords[i] * 100));
  }
  send_buffer[33] = 0xFA;
}

void arm_data(uint8_t arm_id, uint8_t id, uint8_t send_buffer[7])
{
  send_buffer[0] = 0xFE;
  send_buffer[1] = 0xFE;
  send_buffer[2] = 0x04;
  send_buffer[3] = 0x03;
  if (arm_id == 1)
  {
    // 左臂编码器数据
    if (xSemaphoreTake(xMutex_lgd, portMAX_DELAY))
    {
      send_buffer[4] = left_encode_array[id - 1][0];
      send_buffer[5] = left_encode_array[id - 1][1];
      xSemaphoreGive(xMutex_lgd);
    }
  }
  else if (arm_id == 2)
  {
    // 右臂编码器数据
    if (xSemaphoreTake(xMutex_rgd, portMAX_DELAY))
    {
      send_buffer[4] = right_encode_array[id - 1][0];
      send_buffer[5] = right_encode_array[id - 1][1];
      xSemaphoreGive(xMutex_rgd);
    }
  }
  send_buffer[6] = 0xFA;
}

void serialRead()
{
  if (Serial.available())
  {
    // 读取单数据判断帧头1
    uint8_t start1 = Serial.read();
    // 判断是否帧头
    if (start1 != 0xfe)
      return;
    // 读取单数据判断帧头2
    uint8_t start2 = Serial.read();
    // 判断是否帧头
    if (start2 != 0xfe)
      return;
    // 读取数据长度
    uint8_t data_len = Serial.read();
    byte read_buffer[data_len];
    // 读取数据包并判断帧尾
    if (Serial.readBytes(read_buffer, data_len) == data_len && read_buffer[data_len - 1] == 0xfa)
    {
      // 读取数据包中的令
      u_int8_t command_data = read_buffer[0];
      // 判断id和指令是否一致
      if (command_data == 0x01)
      {
        // 读双臂所有数据
        uint8_t send_buffer[63];
        all_data(send_buffer);
        Serial.write(send_buffer, sizeof(send_buffer));
      }
      else if (command_data == 0x02)
      {
        // 读单臂所有数据
        uint8_t send_buffer[34];
        uint8_t arm_id = read_buffer[1];
        arm_all_data(arm_id, send_buffer);
        Serial.write(send_buffer, sizeof(send_buffer));
      }
      else if (command_data == 0x03)
      {
        // 读单臂单关节数据
        uint8_t send_buffer[7];
        uint8_t arm_id = read_buffer[1];
        uint8_t id = read_buffer[2];
        arm_data(arm_id, id, send_buffer);
        Serial.write(send_buffer, sizeof(send_buffer));
      }
      else if (command_data == 0x04)
      {
        // 设置零点
        uint8_t arm_id = read_buffer[1];
        uint8_t id = read_buffer[2];
        if (arm_id == 1)
        {
          smL.CalibrationOfs(id);
        }
        else if (arm_id == 2)
        {
          smR.CalibrationOfs(id);
        }
        return_data[3] = command_data;
        Serial.write(return_data, 6);
      }
      else if (command_data == 0x05)
      {
        // 设置ledRGB值
        uint8_t arm_id = read_buffer[1];
        uint8_t R = read_buffer[2];
        uint8_t G = read_buffer[3];
        uint8_t B = read_buffer[4];
        if (arm_id == 1)
        {
          uint8_t send_buffer[8] = {0xfe, 0xfe, 0x05, 0x02, read_buffer[2], read_buffer[3], read_buffer[4], 0xfa};
          Serial2.write(send_buffer, sizeof(send_buffer));
        }
        else if (arm_id == 2)
        {
          uint8_t send_buffer[8] = {0xfe, 0xfe, 0x05, 0x02, read_buffer[2], read_buffer[3], read_buffer[4], 0xfa};
          Serial1.write(send_buffer, sizeof(send_buffer));
        }
        return_data[3] = command_data;
        Serial.write(return_data, 6);
      }
      else if (command_data == 0x06)
      {
        uint8_t send_buffer[6] = {0xfe, 0xfe, 0x03, command_data, SYSTEM_VERSION, 0xfa};
        Serial.write(send_buffer, 6);
      }
      else if (command_data == 0x07)
      {
        uint8_t arm_id = read_buffer[1];
        if (arm_id == 1)
        {
          uint8_t return_version[7] = {0xfe, 0xfe, 0x04, 0x07, 0x01, version_l, 0xfa};
          Serial.write(return_version,sizeof(return_version));
        }
        else if (arm_id == 2)
        {
          uint8_t return_version[7] = {0xfe, 0xfe, 0x04, 0x07, 0x02, version_r, 0xfa};
          Serial.write(return_version,sizeof(return_version));
        }
      }
    }
  }
}

void Callback()
{
  serialRead();
}