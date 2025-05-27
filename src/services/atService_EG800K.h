/**
@file
*/
/*
  Service_atService_EG800K.h

  This version is

  Copyright:: 2021 nguyentrinhtuan1996@gmail.com
*/

#ifndef _Service_atService_EG800K_
#define _Service_atService_EG800K_
/* _____PROJECT INCLUDES____________________________________________________ */
#include "Service.h"
#include "../src/obj/atObj_ADC.h"
/* _____DEFINETIONS__________________________________________________________ */
#define EG800K_RX 18
#define EG800K_TX 17
#define EG800K_BAUD 115200
#define DEFAULT_TIMEOUT 3000

#define MQTT_BROKER "broker.emqx.io"
#define MQTT_PORT "1883"
#define MQTT_CLIENT_ID "esp32s3-client"
#define MQTT_TOPIC "esp32s3/adc"

enum SER_EG800K_State : uint8_t
{
    EG800K_STATE_NORMAL,
    EG800K_STATE_ERROR
};

HardwareSerial EGSerial(2); // UART2 cho EG800K
/* _____GLOBAL VARIABLES_____________________________________________________ */

/* _____GLOBAL FUNCTION______________________________________________________ */

/* _____CLASS DEFINITION_____________________________________________________ */
/**
 * This Service class is the Service to manage the
 */
class Service_EG800K : public Service
{
public:
    Service_EG800K();
    ~Service_EG800K();
    static void sendAT(const String &cmd, uint16_t timeout);
    static void configEG800K();
    static void configMQTT();
    static void publishMQTTData(String payload);
    static void subscribeMQTTTopic(const String &topic);
    static void handleMQTTMessage();

    SER_EG800K_State EG800K_State = EG800K_STATE_NORMAL;

protected:
private:
    static void Service_EG800K_Start();
    static void Service_EG800K_Execute();
    static void Service_EG800K_End();
} atService_EG800K;
/**
 * This function will be automaticaly called when a object is created by this class
 */
Service_EG800K::Service_EG800K(/* args */)
{
    _Start_User = *Service_EG800K_Start;
    _Execute_User = *Service_EG800K_Execute;
    _End_User = *Service_EG800K_End;

    // change the ID of Service
    ID_Service = 2;
    // change the Service name
    Name_Service = (char *)"EG800K Service";
    // change the ID of SNM
}
/**
 * This function will be automaticaly called when the object of class is delete
 */
Service_EG800K::~Service_EG800K()
{
}
/**
 * This function will send AT command to EG800K
 */
void Service_EG800K::sendAT(const String &cmd, uint16_t timeout)
{
    EGSerial.println(cmd);
    uint32_t start = millis();
    String response = "";
    while (millis() - start < timeout)
    {
        while (EGSerial.available())
        {
            char c = EGSerial.read();
            response += c;
        }
    }
    if (atService_EG800K.User_Mode == SER_USER_MODE_DEBUG)
    {
        Serial.print(">> Command:");
        Serial.println(cmd);
        Serial.print("<< Response:");
        Serial.println(response);
    }
    if (response.indexOf("ERROR") != -1)
    {
        atService_EG800K.EG800K_State = EG800K_STATE_ERROR;
    }
}
/**
 * This function will setup the EG800K
 */
void Service_EG800K::configEG800K()
{
    EGSerial.begin(EG800K_BAUD, SERIAL_8N1, EG800K_RX, EG800K_TX);
    vTaskDelay(3000 / portTICK_PERIOD_MS);

    if (atService_EG800K.User_Mode == SER_USER_MODE_DEBUG)
    {
        Serial.println("Configuring EG800K...");
    }
    sendAT("AT", DEFAULT_TIMEOUT);                                     // Kiểm tra kết nối
    sendAT("ATE0", DEFAULT_TIMEOUT);                                   // Tắt chế độ phản hồi
    sendAT("AT+CMEE=2", DEFAULT_TIMEOUT);                              // Bật chế độ báo lỗi dạng nội dung với CMEE=2, CMEE=1 là dạng mã số lỗi, CMEE=0 là không báo lỗi
    sendAT("AT+CPIN?", DEFAULT_TIMEOUT);                               // Kiểm tra SIM
    sendAT("AT+CREG?", DEFAULT_TIMEOUT);                               // Kiểm tra đăng ký mạng
    sendAT("AT+CGATT?", DEFAULT_TIMEOUT);                              // Gắn kết dịch vụ dữ liệu
    sendAT("AT+QICSGP=1,1,\"internet\",\"\",\"\",1", DEFAULT_TIMEOUT); // APN, sửa "internet" nếu cần
    sendAT("AT+QIACT=1", DEFAULT_TIMEOUT);                             // Kích hoạt PDP
    sendAT("AT+QIACT?", DEFAULT_TIMEOUT);                              // Kiểm tra IP
}
void Service_EG800K::configMQTT()
{
    // MQTT init
    if (atService_EG800K.User_Mode == SER_USER_MODE_DEBUG)
    {
        Serial.println("Configuring MQTT...");
    }
    sendAT("AT+QMTOPEN=0,\"" + String(MQTT_BROKER) + "\"," + String(MQTT_PORT), DEFAULT_TIMEOUT);
    vTaskDelay(3000 / portTICK_PERIOD_MS);
    sendAT("AT+QMTCONN=0,\"" + String(MQTT_CLIENT_ID) + "\"", DEFAULT_TIMEOUT);
    vTaskDelay(3000 / portTICK_PERIOD_MS);
}
/**
 * This function will send data to MQTT broker
 */
void Service_EG800K::publishMQTTData(String payload)
{
    String cmd = "AT+QMTPUB=0,0,0,0,\"" + String(MQTT_TOPIC) + "\"";
    sendAT(cmd, DEFAULT_TIMEOUT);
    EGSerial.print(payload);
    EGSerial.write(0x1A); // Gửi ký tự kết thúc (Ctrl+Z)
    vTaskDelay(1000 / portTICK_PERIOD_MS);
}z
void Service_EG800K::subscribeMQTTTopic(const String &topic)
{
    // Đăng ký (subscribe) topic
    String cmd = "AT+QMTSUB=0,1,\"" + topic + "\",2"; // 0: client_idx, 1: msg_id, QoS=2
    sendAT(cmd, 1500);
}

// Hàm này nên được gọi thường xuyên trong vòng lặp/task để kiểm tra dữ liệu đến
void Service_EG800K::handleMQTTMessage()
{
    static bool receiving = false;
    static String recvLine = "";

    while (EGSerial.available())
    {
        char c = EGSerial.read();
        if (!receiving)
        {
            // Tìm bắt đầu chuỗi +QMTRECV:
            if (c == '+')
            {
                recvLine = c;
                receiving = true;
            }
        }
        else
        {
            recvLine += c;
            if (c == '}')
            {
                if (recvLine.startsWith("+QMTRECV:"))
                {
                    uint16_t openingBrace = recvLine.indexOf('{');
                    uint8_t firstQuote = recvLine.indexOf('"');
                    uint8_t secondQuote = recvLine.indexOf('"', firstQuote + 1);
                    String topic = recvLine.substring(firstQuote + 1, secondQuote);
                    String payload = recvLine.substring(openingBrace);
                    if (atService_EG800K.User_Mode == SER_USER_MODE_DEBUG)
                    {
                        Serial.print("[MQTT] Topic: ");
                        Serial.println(topic);
                        Serial.println("[MQTT] Payload: ");
                        Serial.println(payload);
                    }
                    // Reset để nhận bản tin tiếp theo
                    receiving = false;
                    recvLine = "";
                }
            }
        }
    }
}
/**
 * This start function will init some critical function
 */
void Service_EG800K::Service_EG800K_Start() {}
/**
 * Execute fuction of SNM app
 */
void Service_EG800K::Service_EG800K_Execute()
{
    // if (atService_EG800K.User_Mode == SER_USER_MODE_DEBUG)
    // {
    // }
}
void Service_EG800K::Service_EG800K_End() {}

#endif
