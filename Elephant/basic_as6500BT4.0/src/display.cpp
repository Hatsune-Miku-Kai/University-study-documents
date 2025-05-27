#include "display.h"
#include <WiFi.h>
extern SemaphoreHandle_t xMutex_latom; // 互斥锁句柄
extern SemaphoreHandle_t xMutex_ratom; // 互斥锁句柄
extern SemaphoreHandle_t xMutex_lgd;   // 互斥锁句柄
extern SemaphoreHandle_t xMutex_rgd;   // 互斥锁句柄

short int angle, encode, value;

void printText(uint16_t c, uint16_t b, int16_t x, int16_t y, uint8_t s, const char *text)
{
  M5.Lcd.setTextColor(c, b);
  M5.Lcd.setCursor(x, y);
  M5.Lcd.setTextSize(s);
  M5.Lcd.println(text);
}

void print_left_Angle(uint16_t c, uint16_t b, int16_t x, int16_t y, uint8_t id)
{
  if (xSemaphoreTake(xMutex_lgd, portMAX_DELAY))
  {
    encode = (left_encode_array[id - 1][0] << 8) | left_encode_array[id - 1][1];
    xSemaphoreGive(xMutex_lgd);
  }
  if (encode == 2048)
  {
    angle = 0;
  }
  else if (encode < 2048)
  {
    angle = -180 * (2048 - encode) / 2048;
  }
  else
  {
    angle = 180 * (encode - 2048) / 2048;
  }
  M5.Lcd.setTextColor(c, b);
  M5.Lcd.setTextPadding(M5.Lcd.width() / 5.5);
  M5.Lcd.drawNumber(angle, x, y);
}

void print_right_Angle(uint16_t c, uint16_t b, int16_t x, int16_t y, uint8_t id)
{
  if (xSemaphoreTake(xMutex_rgd, portMAX_DELAY))
  {
    encode = (right_encode_array[id - 1][0] << 8) | right_encode_array[id - 1][1];
    xSemaphoreGive(xMutex_rgd);
  }
  if (encode == 2048)
  {
    angle = 0;
  }
  else if (encode < 2048)
  {
    angle = -180 * (2048 - encode) / 2048;
  }
  else
  {
    angle = 180 * (encode - 2048) / 2048;
  }
  M5.Lcd.setTextColor(c, b);
  M5.Lcd.setTextPadding(M5.Lcd.width() / 5.5);
  M5.Lcd.drawNumber(angle, x, y);
}

void drawLCD()
{
  if (wifiStatus == false && deviceconnected == false && bleStatus == true)
  {
    // Serial.print("device is disconnect");
    M5.Lcd.drawFastVLine(159, 29, 255, TFT_GREEN);
    M5.Lcd.drawFastHLine(0, 29, 400, GREEN);
    printText(YELLOW, BLACK, 10, 10, 2, "BT:");

    M5.Lcd.setTextColor(RED, BLACK);
    M5.Lcd.setCursor(50, 10);
    M5.Lcd.setTextSize(2);
    M5.Lcd.fillRect(50, 0, M5.Lcd.width() / 2, 28, BLACK); // 清除显示区域，背景色为黑色
    M5.Lcd.println("DISconnected");
    M5.Lcd.setTextPadding(M5.Lcd.width() / 3);
    printText(YELLOW, BLACK, 210, 10, 2, "Name:");
    printText(RED, BLACK, 280, 10, 2, "BT");
  }

  if (wifiStatus == false && deviceconnected == true && bleStatus ==true)
  {
    // Serial.print("device is connect");
    M5.Lcd.drawFastVLine(159, 29, 255, TFT_GREEN);
    M5.Lcd.drawFastHLine(0, 29, 400, GREEN);
    printText(YELLOW, BLACK, 10, 10, 2, "BT:");

    M5.Lcd.setTextColor(RED, BLACK);
    M5.Lcd.setCursor(50, 10);
    M5.Lcd.setTextSize(2);
    M5.Lcd.fillRect(50, 0, M5.Lcd.width() / 2, 28, BLACK); // 清除显示区域，背景色为黑色
    M5.Lcd.println("Connected");
    printText(YELLOW, BLACK, 210, 10, 2, "Name:");
    printText(RED, BLACK, 280, 10, 2, "BT");
  }

  if (wifiStatus == false && bleStatus == false)
  {
    M5.Lcd.drawFastVLine(159, 29, 255, TFT_GREEN);
    M5.Lcd.drawFastHLine(0, 29, 400, GREEN);
    printText(YELLOW, BLACK, 10, 10, 2, "IP:");

    M5.Lcd.setTextColor(RED, BLACK);
    M5.Lcd.setCursor(50, 10);
    M5.Lcd.setTextSize(2);
    M5.Lcd.fillRect(50, 0, M5.Lcd.width() / 2, 28, BLACK); // 清除显示区域，背景色为黑色
    M5.Lcd.println(WiFi.softAPIP());
    printText(YELLOW, BLACK, 210, 10, 2, "Port:");
    printText(RED, BLACK, 280, 10, 2, "80");
    printText(RED, BLACK, 304, 10, 2, " ");
    M5.Lcd.setTextPadding(M5.Lcd.width() / 3);
  }

  // if (WiFi.status() != WL_CONNECTED)
  // {
  //   M5.Lcd.println("disconnected!");
  // }
  // else
  // {
  //   M5.Lcd.println(WiFi.localIP());
  // }

  printText(BLUE, BLACK, 170, 35, 2, "left_1:");
  print_left_Angle(WHITE, BLACK, 270, 35, 1);
  printText(BLUE, BLACK, 170, 55, 2, "left_2:");
  print_left_Angle(WHITE, BLACK, 270, 55, 2);
  printText(BLUE, BLACK, 170, 75, 2, "left_3:");
  print_left_Angle(WHITE, BLACK, 270, 75, 3);
  printText(BLUE, BLACK, 170, 95, 2, "left_4:");
  print_left_Angle(WHITE, BLACK, 270, 95, 4);
  printText(BLUE, BLACK, 170, 115, 2, "left_5:");
  print_left_Angle(WHITE, BLACK, 270, 115, 5);
  printText(BLUE, BLACK, 170, 135, 2, "left_6:");
  print_left_Angle(WHITE, BLACK, 270, 135, 6);
  printText(BLUE, BLACK, 170, 155, 2, "left_7:");
  print_left_Angle(WHITE, BLACK, 270, 155, 7);
  printText(BLUE, BLACK, 170, 175, 2, "button_1:");
  M5.Lcd.setTextColor(WHITE, BLACK);
  M5.Lcd.setTextPadding(M5.Lcd.width() / 9);
  if (xSemaphoreTake(xMutex_latom, portMAX_DELAY))
  {
    M5.Lcd.drawNumber((left_atom_value_array[0] & 0x04) >> 2, 280, 175);
    printText(BLUE, BLACK, 170, 195, 2, "button_2:");
    M5.Lcd.setTextColor(WHITE, BLACK);
    M5.Lcd.drawNumber((left_atom_value_array[0] & 0x02) >> 1, 280, 195);
    printText(BLUE, BLACK, 170, 215, 2, "x:");
    M5.Lcd.setTextColor(WHITE, BLACK);
    M5.Lcd.drawNumber(left_atom_value_array[1], 200, 215);
    printText(BLUE, BLACK, 250, 215, 2, "y:");
    M5.Lcd.setTextColor(WHITE, BLACK);
    M5.Lcd.drawNumber(left_atom_value_array[2], 280, 215);
    xSemaphoreGive(xMutex_latom);
  }

  printText(BLUE, BLACK, 10, 35, 2, "right_1:");
  print_right_Angle(WHITE, BLACK, 100, 35, 1);
  printText(BLUE, BLACK, 10, 55, 2, "right_2:");
  print_right_Angle(WHITE, BLACK, 100, 55, 2);
  printText(BLUE, BLACK, 10, 75, 2, "right_3:");
  print_right_Angle(WHITE, BLACK, 100, 75, 3);
  printText(BLUE, BLACK, 10, 95, 2, "right_4:");
  print_right_Angle(WHITE, BLACK, 100, 95, 4);
  printText(BLUE, BLACK, 10, 115, 2, "right_5:");
  print_right_Angle(WHITE, BLACK, 100, 115, 5);
  printText(BLUE, BLACK, 10, 135, 2, "right_6:");
  print_right_Angle(WHITE, BLACK, 100, 135, 6);
  printText(BLUE, BLACK, 10, 155, 2, "right_7:");
  print_right_Angle(WHITE, BLACK, 100, 155, 7);
  printText(BLUE, BLACK, 10, 175, 2, "button_1:");
  M5.Lcd.setTextColor(WHITE, BLACK);
  M5.Lcd.setTextPadding(M5.Lcd.width() / 9);
  if (xSemaphoreTake(xMutex_ratom, portMAX_DELAY))
  {
    M5.Lcd.drawNumber((right_atom_value_array[0] & 0x04) >> 2, 120, 175);
    printText(BLUE, BLACK, 10, 195, 2, "button_2:");
    M5.Lcd.setTextColor(WHITE, BLACK);
    M5.Lcd.drawNumber((right_atom_value_array[0] & 0x02) >> 1, 120, 195);
    printText(BLUE, BLACK, 10, 215, 2, "x:");
    M5.Lcd.setTextColor(WHITE, BLACK);
    M5.Lcd.drawNumber(right_atom_value_array[1], 40, 215);
    printText(BLUE, BLACK, 90, 215, 2, "y:");
    M5.Lcd.setTextColor(WHITE, BLACK);
    M5.Lcd.drawNumber(right_atom_value_array[2], 120, 215);
    xSemaphoreGive(xMutex_ratom);
  }
}