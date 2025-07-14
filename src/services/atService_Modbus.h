#ifndef _Service_atService_Modbus_
#define _Service_atService_Modbus_
/* _____PROJECT INCLUDES____________________________________________________ */
#include "Service.h"
#include <ModbusMaster.h>
/* _____DEFINETIONS__________________________________________________________ */
#define RS485_RX_PIN 17 // RO  ← RX1
#define RS485_TX_PIN 18 // DI  → TX1
/* _____GLOBAL VARIABLES_____________________________________________________ */
ModbusMaster node;
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

    uint16_t mbReadHoldingRegisters(uint16_t u16ReadAddress, uint16_t u16ReadQty);

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
void Service_Modbus::Service_Modbus_Start()
{
    Serial1.begin(9600, SERIAL_8N1, RS485_RX_PIN, RS485_TX_PIN);
    node.begin(1, Serial1);
    if (atService_Modbus.User_Mode == SER_USER_MODE_DEBUG)
    {
        Serial.println("Modbus RTU 1 over RS-485 ready!");
    }
}

/**
 * Execute fuction of SNM app
 */
void Service_Modbus::Service_Modbus_Execute()
{
    if (atService_Modbus.User_Mode == SER_USER_MODE_DEBUG)
    {
    }
}
void Service_Modbus::Service_Modbus_End() {}
uint16_t Service_Modbus::mbReadHoldingRegisters(uint16_t u16ReadAddress, uint16_t u16ReadQty)
{
    uint16_t data[u16ReadQty];
    uint8_t result = node.readHoldingRegisters(u16ReadAddress, u16ReadQty);
    if (result == node.ku8MBSuccess)
    {
        data[0] = node.getResponseBuffer(0);
        if (atService_Modbus.User_Mode == SER_USER_MODE_DEBUG)
        {
            Serial.print("Register [4] = ");
            Serial.println(data[0]);
        }
        return data[0];
    }
    else
    {
        if (atService_Modbus.User_Mode == SER_USER_MODE_DEBUG)
        {
            Serial.print("Modbus error code: ");
            Serial.println(result, DEC);
        }
    }
    return -1; // Return -1 if there is an error
}

#endif
