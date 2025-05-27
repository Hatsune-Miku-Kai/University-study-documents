#include "M5Stack.h"
#include "display.h"
// #include "gd32_comm.h"
#include "serial_comm.h"
#include <SCServo.h>
#include "wifi_module.h"
#include "bluetooth_module.h"

extern bool bleStatus;
extern bool wifiStatus;
SMS_STS smR;
SMS_STS smL;

xTaskHandle Task5;
xTaskHandle Task6;

// 数组存储
byte left_atom_value_array[3] = {};
byte right_atom_value_array[3] = {};
byte left_encode_array[7][2] = {};
byte right_encode_array[7][2] = {};
byte version_l, version_r;
const int buttonPinA = 39;          // 按键连接到 GPIO 38
const int buttonPinB = 38;          // 按键连接到 GPIO 39
const int buttonPinC = 37;          // 按键连接到 GPIO 37
bool lastButtonState = HIGH;        // 上次按键状态
bool wifiStatus = false;            // 当前 Wi-Fi 状态，默认关闭
bool bleStatus = false;             // 蓝牙状态,默认关闭
unsigned long lastDebounceTime = 0; // 防抖动时间
unsigned long debounceDelay = 50;   // 防抖动延时（毫秒）

SemaphoreHandle_t xMutex_latom; // 互斥锁句柄
SemaphoreHandle_t xMutex_ratom; // 互斥锁句柄
SemaphoreHandle_t xMutex_lgd;   // 互斥锁句柄
SemaphoreHandle_t xMutex_rgd;   // 互斥锁句柄

void TaskBlink1(void *pvParameters);
void TaskBlink2(void *pvParameters);
void TaskBlink3(void *pvParameters);
// void TaskBlink4(void *pvParameters);
void TaskBlink5(void *pvParameter);
void TaskBlink6(void *pvParameter);

void setup()
{
  M5.begin(true, false, true);
  xMutex_latom = xSemaphoreCreateMutex();
  xMutex_ratom = xSemaphoreCreateMutex();
  xMutex_lgd = xSemaphoreCreateMutex();
  xMutex_rgd = xSemaphoreCreateMutex();

  M5.Lcd.begin();
  M5.Power.begin();
  // 右臂
  Serial1.begin(1000000, SERIAL_8N1, 2, 5);
  smR.pSerial = &Serial1;
  // 左臂
  Serial2.begin(1000000, SERIAL_8N1, 16, 17);
  smL.pSerial = &Serial2;

  Serial.begin(1000000);
  // usleep(500000);
  Serial.onReceive(Callback);

  // 初始化按键引脚
  pinMode(buttonPinA, INPUT_PULLUP);
  pinMode(buttonPinB, INPUT_PULLUP);
  pinMode(buttonPinC, INPUT_PULLUP);


  xTaskCreatePinnedToCore(TaskBlink1, "left_gd", 4096, NULL, 2, NULL, 1);
  xTaskCreatePinnedToCore(TaskBlink2, "right_gd", 4096, NULL, 2, NULL, 1);
  xTaskCreatePinnedToCore(TaskBlink3, "Task LCD", 2048, NULL, 2, NULL, 1);
  // xTaskCreatePinnedToCore(TaskBlink4, "serial", 2048, NULL, 2, NULL, 1);
  xTaskCreatePinnedToCore(TaskBlink5, "WIFI", 4096, NULL, 2, &Task5, 1);
  xTaskCreatePinnedToCore(TaskBlink6, "BLE", 4096, NULL, 2, &Task6, 1);
}

void TaskBlink1(void *pvParameters)
{
  while (1)
  {
    LGD32Data();
  }
}

void TaskBlink2(void *pvParameters)
{
  while (1)
  {
    RGD32Data();
  }
}

void TaskBlink3(void *pvParameters)
{
  while (1)
  {
    drawLCD();
    vTaskDelay(20);
  }
}

void TaskBlink5(void *pvParameters)
{

  // wifi_init();
  while (1)
  {
    int buttonStateA = digitalRead(buttonPinA); // 读取按键状态
    int buttonStateC = digitalRead(buttonPinC); // 读取按键C的状态
    // 按键被按下，切换 Wi-Fi 状态
    if (buttonStateC == LOW && wifiStatus)
    {
      wifi_close();
      wifiStatus = false;
      vTaskPrioritySet(Task6,2);
    }
    if (buttonStateA == LOW && !wifiStatus && bleStatus == false)
    {
      // 启动 Wi-Fi AP 和 Web 服务器
      wifi_init();
      wifiStatus = true;
      vTaskPrioritySet(Task6,3);
    }

    if (wifiStatus)
    {
      wifi_read();
    }
    vTaskDelay(5);
  }
}

void TaskBlink6(void *pvParameters)
{
  while (1)
  {
    int buttonStateC = digitalRead(buttonPinC); // 读取按键C的状态
    int buttonStateB = digitalRead(buttonPinB);
    if (buttonStateB == LOW && !bleStatus && wifiStatus == false) // wlan和ble只能存在一个
    {
      
      if(bleStatus == false)
      {
        CreatBT();
        bleStatus = true;
        vTaskPrioritySet(Task5,2);
      }  
      Serial.print("Serve is creat");
    }

    if (buttonStateC == LOW && bleStatus)
    {
      bleStatus = false;
      CloseBT();
      vTaskPrioritySet(Task5,3);
      Serial.print("Serve is destory");
    }

    if(bleStatus)
    {
      GetBTData();
    }

    vTaskDelay(5);
  }
}

void loop() {}