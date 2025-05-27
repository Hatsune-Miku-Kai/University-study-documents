#include "bluetooth_module.h"
#include "serial_comm.h"
#include <SCServo.h>
extern SMS_STS smR;
extern SMS_STS smL;

BluetoothSerial SerialBT;
int BTConnect = false;
String BT_Name = "BT";
bool deviceconnected = false;

byte return_BT_data[] = {HEADER, HEADER, 3, 0, 1, FOOTER};

void CreatBT()
{
  SerialBT.begin(BT_Name);
  SerialBT.setPin("6666");
}

void GetBTData()
{
  // Serial.print("G");
  // Serial.print("t");
  while (SerialBT.connected())
  {
    long start_time = millis();
    deviceconnected = true;
    // Serial.print("0");
    if (SerialBT.available())
    {
      //Serial.print("INTO");
      uint8_t start1 = SerialBT.read();
      if (start1 != 0xfe)
        continue;

      uint8_t start2 = SerialBT.read();
      if (start2 != 0xfe)
        continue;

      if (SerialBT.available() < 1)
        continue;

      uint8_t data_len = SerialBT.read();

      if (SerialBT.available() < 1)
        continue;

      byte read_buffer[data_len];
      if (SerialBT.readBytes(read_buffer, data_len) == data_len && read_buffer[data_len - 1] == 0xfa && (millis() - start_time) < 100)
      {
        uint8_t command_data = read_buffer[0];
        switch (command_data)
        {
        case 0x01:
        {
          uint8_t send_buffer[63];
          all_data(send_buffer);
          SerialBT.write(send_buffer, sizeof(send_buffer));
        }
        break;

        case 0x02:
        {
          uint8_t send_buffer[34];
          uint8_t arm_id = read_buffer[1];
          arm_all_data(arm_id, send_buffer);
          SerialBT.write(send_buffer, sizeof(send_buffer));
        }
        break;

        case 0x03:
        {
          uint8_t send_buffer[7];
          uint8_t arm_id = read_buffer[1];
          uint8_t id = read_buffer[2];
          arm_data(arm_id, id, send_buffer);
          SerialBT.write(send_buffer, sizeof(send_buffer));
        }
        break;

        case 0x04:
        {
          uint8_t arm_id = read_buffer[1];
          uint8_t id = read_buffer[2];
          byte return_BT_data[] = {HEADER, HEADER, 0x03, 0x04, 0x01, FOOTER};
          if (arm_id == 1)
          {
            smL.CalibrationOfs(id);
          }
          else if (arm_id == 2)
          {
            smR.CalibrationOfs(id);
          }
          SerialBT.write(return_BT_data, sizeof(return_BT_data));
        }
        break;

        case 0x05:
        {
          uint8_t arm_id = read_buffer[1];
          uint8_t R = read_buffer[2];
          uint8_t G = read_buffer[3];
          uint8_t B = read_buffer[4];
          byte data_buffer[] = {HEADER, HEADER, 3, 0x05, 1, FOOTER};
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
          SerialBT.write(data_buffer, sizeof(data_buffer));
        }
        break;

        case 0x06:
        {
          byte return_data[] = {HEADER, HEADER, 3, 0x06, SYSTEM_VERSION, FOOTER};
          SerialBT.write(return_data, sizeof(return_data));
        }
        break;

        case 0x07:
        {
          uint8_t arm_id = read_buffer[1];
          if (arm_id == 1)
          {
            uint8_t return_version[7] = {HEADER, HEADER, 0x04, 0x07, 0x01, version_l, FOOTER};
            SerialBT.write(return_version, sizeof(return_version));
          }
          else if (arm_id == 2)
          {
            uint8_t return_version[7] = {HEADER, HEADER, 0x04, 0x07, 0x02, version_r, FOOTER};
            SerialBT.write(return_version, sizeof(return_version));
          }
        }
        break;

        default:
        {
          uint8_t return_version[6] = {0xFE, 0XFE, 0X03, 0XFF, 0XFF, 0XFA};
          SerialBT.write(return_version, sizeof(return_version));
          continue;
        }
        }
        //SerialBT.flush();
      }
      else
      {
        uint8_t return_version[6] = {0xFE, 0XFE, 0X03, 0XFF, 0XFF, 0XFA};
        SerialBT.write(return_version, sizeof(return_version));
        //SerialBT.flush();
        continue;
      }
    }
    vTaskDelay(1);
  }
  Serial.print("loss connected");
  deviceconnected = false;
  // Serial.print("N");
}

void CloseBT()
{
  SerialBT.disconnect();
  // Serial.print("C");
}