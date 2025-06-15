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
#define EG800K_RX 44 //UART0
#define EG800K_TX 43 //UART0
#define EG800K_BAUD 115200
#define DEFAULT_TIMEOUT 1500

#define MQTT_BROKER "broker.emqx.io"
#define MQTT_PORT "1883"
#define MQTT_CLIENT_ID "esp32s3-client"
#define MQTT_TOPIC "esp32s3/adc"

enum SER_EG800K_State : uint8_t
{
    EG800K_STATE_INIT,
    EG800K_STATE_NORMAL,
    EG800K_STATE_ERROR
};
enum SER_MQTT_State : uint8_t
{
    MQTT_STATE_NORMAL,
    MQTT_STATE_PUBLISHING,
    MQTT_STATE_SUBSCRIBING,
};
HardwareSerial EGSerial(0); // UART0 cho EG800K
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
    static void configFTP();
    static void sendFTPfile(const String &filename, const String &content);

    SER_EG800K_State EG800K_State = EG800K_STATE_INIT; // Trạng thái của EG800K
    SER_MQTT_State MQTT_State = MQTT_STATE_NORMAL;     // Trạng thái của MQTT
    static bool EG800K_configuring;                    // Biến để kiểm tra xem EG800K đang được cấu hình hay không
    static bool EG800K_configured;                     // Biến để kiểm tra xem EG800K đã được cấu hình hay chưa
    static bool MQTT_configuring;                      // Biến để kiểm tra xem MQTT đang được cấu hình hay không
    static bool MQTT_configured;                       // Biến để kiểm tra xem MQTT đã được cấu hình hay chưa
protected:
private:
    static void Service_EG800K_Start();
    static void Service_EG800K_Execute();
    static void Service_EG800K_End();
} atService_EG800K;

// Gán giá trị ban đầu cho biến EG800K_configured
bool Service_EG800K::EG800K_configuring = false; // Biến để kiểm tra xem EG800K đang được cấu hình hay không
bool Service_EG800K::EG800K_configured = false;  // Biến để kiểm tra xem EG800K đã được cấu hình hay chưa
bool Service_EG800K::MQTT_configuring = false;   // Biến để kiểm tra xem MQTT đang được cấu hình hay không
bool Service_EG800K::MQTT_configured = false;    // Biến để kiểm tra xem MQTT đã được cấu hình hay chưa
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
    EG800K_configuring = true; // Đặt biến EG800K_configuring là true để đánh dấu EG800K đang được cấu hình
    atService_EG800K.EG800K_State = EG800K_STATE_INIT;
    atService_EG800K.MQTT_State = MQTT_STATE_NORMAL;
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
    atService_EG800K.EG800K_State = EG800K_STATE_NORMAL;               // Đặt trạng thái EG800K là bình thường sau khi cấu hình
    EG800K_configuring = false;                                        // Đặt biến EG800K_configuring là false để đánh dấu EG800K đã được cấu hình
    EG800K_configured = true;                                          // Đặt biến EG800K_configured là true để đánh dấu EG800K đã được cấu hình
}
void Service_EG800K::configMQTT()
{
    // MQTT init
    MQTT_configuring = true; // Đặt biến MQTT_configuring là true để đánh dấu MQTT đang được cấu hình
    atService_EG800K.EG800K_State = EG800K_STATE_INIT;
    atService_EG800K.MQTT_State = MQTT_STATE_NORMAL;

    if (atService_EG800K.User_Mode == SER_USER_MODE_DEBUG)
    {
        Serial.println("Configuring MQTT...");
    }

    sendAT("AT+QMTOPEN=0,\"" + String(MQTT_BROKER) + "\"," + String(MQTT_PORT), DEFAULT_TIMEOUT);
    vTaskDelay(3000 / portTICK_PERIOD_MS);
    sendAT("AT+QMTCONN=0,\"" + String(MQTT_CLIENT_ID) + "\"", DEFAULT_TIMEOUT);
    vTaskDelay(3000 / portTICK_PERIOD_MS);
    atService_EG800K.EG800K_State = EG800K_STATE_NORMAL; // Đặt trạng thái EG800K là bình thường sau khi cấu hình MQTT
    MQTT_configuring = false;                             // Đặt biến MQTT_configuring là false để đánh dấu MQTT đã được cấu hình
    MQTT_configured = true;                              // Đặt biến MQTT_configured là true để đánh dấu MQTT đã được cấu hình
}
/**
 * This function will send data to MQTT broker
 */
void Service_EG800K::publishMQTTData(String payload)
{
    atService_EG800K.MQTT_State = MQTT_STATE_PUBLISHING;
    String cmd = "AT+QMTPUB=0,0,0,0,\"" + String(MQTT_TOPIC) + "\"";
    sendAT(cmd, DEFAULT_TIMEOUT);
    EGSerial.print(payload);
    EGSerial.write(0x1A); // Gửi ký tự kết thúc (Ctrl+Z)
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    atService_EG800K.MQTT_State = MQTT_STATE_NORMAL; // Đặt trạng thái MQTT là bình thường sau khi gửi dữ liệu
}
void Service_EG800K::subscribeMQTTTopic(const String &topic)
{
    atService_EG800K.MQTT_State = MQTT_STATE_SUBSCRIBING;
    // Đăng ký (subscribe) topic
    String cmd = "AT+QMTSUB=0,1,\"" + topic + "\",2"; // 0: client_idx, 1: msg_id, QoS=2
    sendAT(cmd, 1500);
    atService_EG800K.MQTT_State = MQTT_STATE_NORMAL;
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
            atService_EG800K.MQTT_State = MQTT_STATE_SUBSCRIBING; // Đặt trạng thái MQTT là đang nhận dữ liệu
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
                    atService_EG800K.MQTT_State = MQTT_STATE_NORMAL; // Đặt lại trạng thái MQTT sau khi nhận dữ liệu
                }
            }
        }
    }
}

void Service_EG800K::configFTP()
{
    atService_EG800K.EG800K_State = EG800K_STATE_INIT;
    if (atService_EG800K.User_Mode == SER_USER_MODE_DEBUG)
    {
        Serial.println("Configuring FTP...");
    }
    // Thiết lập cấu hình FTP server
    sendAT("AT+QFTPCFG=\"contextid\",1", DEFAULT_TIMEOUT);   // Sử dụng PDP context 1
    
    // Thiết lập thông tin server FTP
    // sendAT("AT+QFTPOPEN=\"103.149.86.230\",21,\"demo\",\"password\"", 10000); // Thay ftp_user/ftp_pass nếu cần
    // set user and password
    sendAT("AT+QFTPCFG=\"account\",\"ftpuser\",\"ftppassword\"", DEFAULT_TIMEOUT); // Thay đổi theo server FTP của bạn
    sendAT("AT+QFTPCFG=\"filetype\",0", DEFAULT_TIMEOUT);    // Chế độ ASCII (0) hoặc Binary (1)
    sendAT("AT+QFTPCFG=\"transmode\",0", DEFAULT_TIMEOUT);   // Chế độ truyền thường
    sendAT("AT+QFTPCFG=\"rsptimeout\",90", DEFAULT_TIMEOUT); // Timeout 90s
    // login
    sendAT("AT+QFTPOPEN=\"103.149.86.230\",21", 10000); // Thay ftp_user/ftp_pass nếu cần
    // Mở kết nối FTP
    sendAT("AT+QFTPOPEN=0", DEFAULT_TIMEOUT); // Mở kết nối FTP với context ID 0
    // set working directorury
    sendAT("AT+QFTPCWD=\"/\"", DEFAULT_TIMEOUT); 
    // read the current woring directory
    sendAT("AT+QFTPCWD=?", DEFAULT_TIMEOUT); // Kiểm tra thư mục làm việc hiện tại
    // query the current working directory
    sendAT("AT+QFTPPWD", 10000); // Kiểm tra thư mục làm việc hiện tại
    // create a Folder with name "DHA_TEST_FTP"
    sendAT("AT+QFTPMKDIR=\"DHA_TEST_FTP\"", 10000); // Tạo thư mục mới
    // rename the folder "DHA_TEST_FTP" to "DHA_TEST_FTP_RENAMED"
    sendAT("AT+QFTPRENAME=\"DHA_TEST_FTP\",\"DHA_TEST_FTP_RENAME\"", DEFAULT_TIMEOUT);

    vTaskDelay(3000 / portTICK_PERIOD_MS);

    if (atService_EG800K.User_Mode == SER_USER_MODE_DEBUG)
    {
        Serial.println("FTP configured.");
    }
    atService_EG800K.EG800K_State = EG800K_STATE_NORMAL;
}

void Service_EG800K::sendFTPfile(const String &filename, const String &content)
{
    // Gửi tệp tin qua FTP
    if (atService_EG800K.User_Mode == SER_USER_MODE_DEBUG)
    {
        Serial.print("[FTP] Sending file: ");
        Serial.println(filename);
    }
    String cmd = "AT+QFTPSEND=0,\"" + filename + "\",\"" + content + "\"";
    sendAT(cmd, DEFAULT_TIMEOUT);
    if (atService_EG800K.User_Mode == SER_USER_MODE_DEBUG)
    {
        Serial.println("[FTP] File sent successfully.");
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
