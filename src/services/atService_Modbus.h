#ifndef _Service_atService_Modbus_
#define _Service_atService_Modbus_
/* _____PROJECT INCLUDES____________________________________________________ */
#include "Service.h"
#include <ModbusMaster.h>
/* _____DEFINETIONS__________________________________________________________ */
#define MB1_RX_PIN 17 // RO  ← RX1
#define MB1_TX_PIN 18 // DI  → TX1
#define MB2_RX_PIN 5  // RO  ← RX2
#define MB2_TX_PIN 4  // DI  → TX2
/* _____GLOBAL VARIABLES_____________________________________________________ */
ModbusMaster mb1;
ModbusMaster mb2;
/* _____GLOBAL FUNCTION______________________________________________________ */

/* _____CLASS DEFINITION_____________________________________________________ */
/**
 * This Service class is the Service to manage the
 */
class Service_Modbus : public Service
{
public:
    Service_Modbus();
    ~Service_Modbus();

    static void mb1Init();
    static void mb2Init();
    static uint16_t mb1ReadHoldingRegisters(uint16_t u16ReadAddress);
    static uint16_t mb2ReadHoldingRegisters(uint16_t u16ReadAddress);

protected:
private:
    static void Service_Modbus_Start();
    static void Service_Modbus_Execute();
    static void Service_Modbus_End();
} atService_Modbus;
/**
 * This function will be automaticaly called when a object is created by this class
 */
Service_Modbus::Service_Modbus(/* args */)
{
    _Start_User = *Service_Modbus_Start;
    _Execute_User = *Service_Modbus_Execute;
    _End_User = *Service_Modbus_End;

    // change the ID of Service
    ID_Service = 1;
    // change the Service name
    Name_Service = (char *)"Modbus Service";
    // change the ID of SNM
}
/**
 * This function will be automaticaly called when the object of class is delete
 */
Service_Modbus::~Service_Modbus()
{
}
/**
 * This start function will init some critical function
 */
void Service_Modbus::Service_Modbus_Start() {}

/**
 * Execute fuction of SNM app
 */
void Service_Modbus::Service_Modbus_Execute()
{
    // if (atService_Modbus.User_Mode == SER_USER_MODE_DEBUG)
    // {
    // }
}
void Service_Modbus::Service_Modbus_End() {}

void Service_Modbus::mb1Init()
{
    Serial1.begin(atObject_Param.baudRateMB1, SERIAL_8N1, MB1_RX_PIN, MB1_TX_PIN);
    vTaskDelay(100 / portTICK_PERIOD_MS); // wait for serial to be ready
    mb1.begin(atObject_Param.slaveIDMB1, Serial1);
    if (atService_Modbus.User_Mode == SER_USER_MODE_DEBUG)
    {
        Serial.printf("Modbus RTU 1 over RS-485 ready!\nBaud rate: %d\n", atObject_Param.baudRateMB1);
    }
}

void Service_Modbus::mb2Init()
{
    Serial2.begin(atObject_Param.baudRateMB2, SERIAL_8N1, MB2_RX_PIN, MB2_TX_PIN);
    vTaskDelay(100 / portTICK_PERIOD_MS); // wait for serial to be ready
    mb2.begin(atObject_Param.slaveIDMB2, Serial2);
    if (atService_Modbus.User_Mode == SER_USER_MODE_DEBUG)
    {
        Serial.printf("Modbus RTU 2 over RS-485 ready!\nBaud rate: %d\n", atObject_Param.baudRateMB2);
    }
}

uint16_t Service_Modbus::mb1ReadHoldingRegisters(uint16_t u16ReadAddress)
{
    uint16_t data;
    uint8_t result = mb1.readHoldingRegisters(u16ReadAddress, 1);
    if (result == mb1.ku8MBSuccess)
    {
        data = mb1.getResponseBuffer(0);
        if (atService_Modbus.User_Mode == SER_USER_MODE_DEBUG)
        {
            Serial.printf("MB1: Register [%d] = %d", u16ReadAddress, data);
        }
        return data;
    }
    else
    {
        if (atService_Modbus.User_Mode == SER_USER_MODE_DEBUG)
        {
            Serial.print("MB1: Modbus error code: ");
            Serial.println(result, DEC);
        }
    }
    return 0xFFFF; // Return 0xFFFF if there is an error
}
uint16_t Service_Modbus::mb2ReadHoldingRegisters(uint16_t u16ReadAddress)
{
    uint16_t data;
    uint8_t result = mb2.readHoldingRegisters(u16ReadAddress, 1);
    if (result == mb2.ku8MBSuccess)
    {
        data = mb2.getResponseBuffer(0);
        if (atService_Modbus.User_Mode == SER_USER_MODE_DEBUG)
        {
            Serial.printf("MB2: Register [%d] = %d", u16ReadAddress, data);
        }
        return data;
    }
    else
    {
        if (atService_Modbus.User_Mode == SER_USER_MODE_DEBUG)
        {
            Serial.print("MB2: Modbus error code: ");
            Serial.println(result, DEC);
        }
    }
    return 0xFFFF; // Return 0xFFFF if there is an error
}

#endif
