#include "wifi_module.h"
#include "WiFi.h"
#include "serial_comm.h"
#include <SCServo.h>

String name, password;
WiFiServer server(80); // 使用TCP端口80创建一个WiFi服务器
extern SMS_STS smR;
extern SMS_STS smL;

// const char *ssid = "ElephantWiFi-AP";   // wifi名
// const char *wifi_password = "Aria6666"; // wifi密码
byte read_buffer[5];

const char *ssid = "elephant1";         // wifi名
const char *wifi_password = "elephant"; // wifi密码
byte return_wifi_data[] = {HEADER, HEADER, 3, 0, 1, FOOTER};

// 初始化配置
// WiFi.softAP(ssid, wifi_password); //
// server.begin();
// WiFi.begin(ssid, wifi_password); // 连接网络

void wifi_init()
{
    // WiFi.begin(ssid, wifi_password); // 连接网络
    WiFi.mode(WIFI_AP);
    WiFi.softAP(ssid, wifi_password);
    server.begin();
}

void wifi_close()
{
    // 关闭 Wi-Fi AP 和 Web 服务器
    WiFi.softAPdisconnect(true);
    server.end();
    WiFi.mode(WIFI_OFF);
}

void wifi_connect()
{
    uint8_t flag = 0;
    Serial.println("please input Wifi Name:");
    for (byte num = 0; num < 30; num++)
    {
        if (Serial.available())
        {
            name = Serial.readString();
            Serial.print("Wifi Name: ");
            Serial.println(name);
            flag = 1;
            break;
        }
        usleep(1000000);
    }
    if (flag)
    {
        Serial.println("please input Wifi password:");
        for (byte num = 0; num < 30; num++)
        {
            if (Serial.available())
            {
                password = Serial.readString();
                Serial.print("Wifi password: ");
                Serial.println(password);
                WiFi.begin(name, password); // 连接网络
                unsigned long startAttemptTime = millis();
                // 等待网络连接成功，设置超时时间为10秒
                while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 10000)
                {
                    delay(500);
                    Serial.print(".");
                }
                if (WiFi.status() == WL_CONNECTED)
                {
                    Serial.println("WiFi connected!");
                    Serial.println("IP address: ");
                    Serial.println(WiFi.localIP()); // 打印模块IP
                    server.begin();                 // 开启服务器
                }
                else
                {
                    Serial.println("Failed to connect to WiFi");
                }
                break;
            }
            usleep(1000000);
            if (num == 29)
            {
                Serial.println("input Wifi password Timeout");
            }
        }
    }
    else
    {
        Serial.println("input Wifi Name Timeout");
    }
}

void wifi_read()
{
    WiFiClient client = server.available(); // 检查是否有新的客户机连接
    if (client)
    {
        // Serial.println("New Client Connected");
        // if(client.connected()){
        while (client.connected())
        {
            if (client.available())
            {
                // 读取单数据判断帧头1
                uint8_t start1 = client.read();
                // 判断是否帧头
                if (start1 != 0xfe)
                    continue;
                // 读取单数据判断帧头2
                uint8_t start2 = client.read();
                // 判断是否帧头
                if (start2 != 0xfe)
                    continue;

                if (client.available() < 1)
                    continue;
                    
                // 读取数据长度
                uint8_t data_len = client.read();

                if (client.available() < 1)
                    continue;

                byte read_buffer[data_len];
                // 读取数据包并判断帧尾
                if (client.readBytes(read_buffer, data_len) == data_len && read_buffer[data_len - 1] == 0xfa)
                {
                    // 读取数据包中的令
                    u_int8_t command_data = read_buffer[0];
                    // 判断id和指令是否一致
                    if (command_data == 0x01)
                    {
                        // 读双臂所有数据
                        uint8_t send_buffer[63];
                        all_data(send_buffer);
                        client.write(send_buffer, sizeof(send_buffer));
                    }
                    else if (command_data == 0x02)
                    {
                        // 读单臂所有数据
                        uint8_t send_buffer[34];
                        uint8_t arm_id = read_buffer[1];
                        arm_all_data(arm_id, send_buffer);
                        client.write(send_buffer, sizeof(send_buffer));
                    }
                    else if (command_data == 0x03)
                    {
                        // 读单臂单关节数据
                        uint8_t send_buffer[7];
                        uint8_t arm_id = read_buffer[1];
                        uint8_t id = read_buffer[2];
                        arm_data(arm_id, id, send_buffer);
                        client.write(send_buffer, sizeof(send_buffer));
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
                        return_wifi_data[3] = command_data;
                        client.write(return_wifi_data, sizeof(return_wifi_data) / sizeof(return_wifi_data[0]));
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
                        return_wifi_data[3] = command_data;
                        client.write(return_wifi_data, sizeof(return_wifi_data) / sizeof(return_wifi_data[0]));
                    }
                    else if (command_data == 0x06)
                    {
                        byte return_data[] = {HEADER, HEADER, 3, 0x06, SYSTEM_VERSION, FOOTER};
                        client.write(return_data, 6);
                    }

                    else if (command_data == 0x07)
                    {
                        uint8_t arm_id = read_buffer[1];
                        if (arm_id == 1)
                        {
                            uint8_t return_version[7] = {0xfe, 0xfe, 0x04, 0x07,0x01, version_l, 0xfa};
                            client.write(return_version, sizeof(return_version));
                        }
                        else if (arm_id == 2)
                        {
                            uint8_t return_version[7] = {0xfe, 0xfe, 0x04, 0x07, 0x02, version_r, 0xfa};
                            client.write(return_version, sizeof(return_version));
                        }
                    }
                }
            }
            vTaskDelay(1);
        }
        // 关闭连接
        client.stop();
        // Serial.println("Client Disconnected");
    }
}