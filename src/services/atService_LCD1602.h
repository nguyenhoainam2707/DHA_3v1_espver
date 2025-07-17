#ifndef _Service_atService_LCD1602_
#define _Service_atService_LCD1602_
/* _____PROJECT INCLUDES____________________________________________________ */
#include "Service.h"
#include <LiquidCrystal_I2C.h>
#include "../src/services/protocols/atService_I2C.h"
/* _____DEFINETIONS__________________________________________________________ */

/* _____GLOBAL VARIABLES_____________________________________________________ */
// Khởi tạo LCD với địa chỉ I2C 0x27, 16 ký tự, 2 dòng
LiquidCrystal_I2C lcd(0x27, 16, 2);
/* _____GLOBAL FUNCTION______________________________________________________ */

/* _____CLASS DEFINITION_____________________________________________________ */
/**
 * This Service class is the Service to manage the
 */
class Service_LCD1602 : public Service
{
public:
    Service_LCD1602();
    ~Service_LCD1602();

protected:
private:
    static void Service_LCD1602_Start();
    static void Service_LCD1602_Execute();
    static void Service_LCD1602_End();
} atService_LCD1602;
/**
 * This function will be automaticaly called when a object is created by this class
 */
Service_LCD1602::Service_LCD1602(/* args */)
{
    _Start_User = *Service_LCD1602_Start;
    _Execute_User = *Service_LCD1602_Execute;
    _End_User = *Service_LCD1602_End;

    // change the ID of Service
    ID_Service = 1;
    // change the Service name
    Name_Service = (char *)"LCD1602 Service";
    // change the ID of SNM
}
/**
 * This function will be automaticaly called when the object of class is delete
 */
Service_LCD1602::~Service_LCD1602()
{
}
/**
 * This start function will init some critical function
 */
void Service_LCD1602::Service_LCD1602_Start()
{
    atService_I2C.Run_Service();
    atService_I2C.checkIn();
    // Khởi động giao tiếp I2C
    Wire.begin(SDA_PIN, SCL_PIN);

    // Khởi động LCD
    lcd.init();
    if(atObject_Param.enLCDBacklight){
        lcd.backlight();
    }
    else{
        lcd.noBacklight();
    }
    // Hiển thị thông báo khởi động
    lcd.setCursor(0, 0);
    lcd.print("     DHA-3");
    lcd.setCursor(0, 1);
    lcd.print("   Khoi dong...");
    atService_I2C.checkOut();
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    atService_I2C.checkIn();
    lcd.clear();
    atService_I2C.checkOut();
}

/**
 * Execute fuction of SNM app
 */
void Service_LCD1602::Service_LCD1602_Execute()
{
    if (atService_LCD1602.User_Mode == SER_USER_MODE_DEBUG)
    {
    }
    
}

void Service_LCD1602::Service_LCD1602_End() {}

#endif
