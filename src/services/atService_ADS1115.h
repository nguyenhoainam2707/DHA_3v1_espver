/**
@file
*/
/*
  Service_atService_ADS1115.h

  This version is

  Copyright:: 2021 nguyentrinhtuan1996@gmail.com
*/

#ifndef _Service_atService_ADS1115_
#define _Service_atService_ADS1115_
/* _____PROJECT INCLUDES____________________________________________________ */
#include "Service.h"
#include <Adafruit_ADS1X15.h>
/* _____DEFINETIONS__________________________________________________________ */
#define SDA_PIN 10
#define SCL_PIN 9
/* _____GLOBAL VARIABLES_____________________________________________________ */

/* _____GLOBAL FUNCTION______________________________________________________ */

/* _____CLASS DEFINITION_____________________________________________________ */

Adafruit_ADS1115 ads; // Tạo đối tượng cho ADS1115
/**
 * This Service class is the Service to manage the
 */
class Service_ADS1115 : public Service
{
public:
    Service_ADS1115();
    ~Service_ADS1115();

    static bool ADS1115_Init(adsGain_t gain, uint16_t rate);
    int16_t ADS1115_readADC(uint8_t channel);
    float ADS1115_readADC_Voltage(uint8_t channel);
protected:
private:
    static void Service_ADS1115_Start();
    static void Service_ADS1115_Execute();
    static void Service_ADS1115_End();
} atService_ADS1115;
/**
 * This function will be automaticaly called when a object is created by this class
 */
Service_ADS1115::Service_ADS1115(/* args */)
{
    _Start_User = *Service_ADS1115_Start;
    _Execute_User = *Service_ADS1115_Execute;
    _End_User = *Service_ADS1115_End;

    // change the ID of Service
    ID_Service = 1;
    // change the Service name
    Name_Service = (char *)"ADS1115 Service";
    // change the ID of SNM
}
/**
 * This function will be automaticaly called when the object of class is delete
 */
Service_ADS1115::~Service_ADS1115()
{
}
/**
 * This start function will init some critical function
 */
void Service_ADS1115::Service_ADS1115_Start() {}
/**
 * Execute fuction of SNM app
 */
void Service_ADS1115::Service_ADS1115_Execute() {}

void Service_ADS1115::Service_ADS1115_End() {}

bool Service_ADS1115::ADS1115_Init(adsGain_t gain, uint16_t rate)
{
    Wire.begin(SDA_PIN, SCL_PIN);
    ads.begin(); // Lưu ý hàm này nếu không tìm được thiết bị giao tiếp I2C sẽ bị treo khoảng 2 giây.
    if (!ads.begin())
        return false; // Check if the ADS1115 is connected
    ads.setGain(gain);
    ads.setDataRate(rate);
    return true;
}
int16_t Service_ADS1115::ADS1115_readADC(uint8_t channel)
{
    return ads.readADC_SingleEnded(channel);
}
float Service_ADS1115::ADS1115_readADC_Voltage(uint8_t channel)
{
    return ads.computeVolts(ads.readADC_SingleEnded(channel));
}
#endif
