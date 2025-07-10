/**
@file
*/
/*
  Service_atService_PCF8574.h

  This version is

  Copyright:: 2021 nguyentrinhtuan1996@gmail.com
*/

#ifndef _Service_atService_PCF8574_
#define _Service_atService_PCF8574_
/* _____PROJECT INCLUDES____________________________________________________ */
#include "Service.h"
#include <PCF8574.h>
/* _____DEFINETIONS__________________________________________________________ */
#define PCF_ADDR 0x20 // PCF8574 I2C address
#ifndef SDA_PIN
#define SDA_PIN 48 // Default SDA pin
#endif
#ifndef SCL_PIN
#define SCL_PIN 45 // Default SCL pin
#endif
/* _____GLOBAL VARIABLES_____________________________________________________ */

/* _____GLOBAL FUNCTION______________________________________________________ */

/* _____CLASS DEFINITION_____________________________________________________ */
PCF8574 pcf(0x20);
/**
 * This Service class is the Service to manage the
 */
class Service_PCF8574 : public Service
{
public:
    Service_PCF8574();
    ~Service_PCF8574();

protected:
private:
    static void Service_PCF8574_Start();
    static void Service_PCF8574_Execute();
    static void Service_PCF8574_End();
} atService_PCF8574;
/**
 * This function will be automaticaly called when a object is created by this class
 */
Service_PCF8574::Service_PCF8574(/* args */)
{
    _Start_User = *Service_PCF8574_Start;
    _Execute_User = *Service_PCF8574_Execute;
    _End_User = *Service_PCF8574_End;

    // change the ID of Service
    ID_Service = 1;
    // change the Service name
    Name_Service = (char *)"PCF8574 Service";
    // change the ID of SNM
}
/**
 * This function will be automaticaly called when the object of class is delete
 */
Service_PCF8574::~Service_PCF8574()
{
}
/**
 * This start function will init some critical function
 */
void Service_PCF8574::Service_PCF8574_Start()
{
    Wire.begin(SDA_PIN, SCL_PIN);
    pcf.pinMode(P2, OUTPUT);
    pcf.pinMode(P3, OUTPUT);
    pcf.pinMode(P4, INPUT);
    pcf.pinMode(P5, INPUT);
    pcf.pinMode(P6, INPUT);
    pcf.pinMode(P7, INPUT);
    if (!pcf.begin())
    {
        Serial.println("Không tìm thấy PCF8574!");
    }
}

/**
 * Execute fuction of SNM app
 */
void Service_PCF8574::Service_PCF8574_Execute()
{
    if (atService_PCF8574.User_Mode == SER_USER_MODE_DEBUG)
    {
    }
}
void Service_PCF8574::Service_PCF8574_End() {}

#endif
