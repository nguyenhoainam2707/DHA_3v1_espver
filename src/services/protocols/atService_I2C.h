#ifndef _Service_atService_I2C_
#define _Service_atService_I2C_
/* _____PROJECT INCLUDES____________________________________________________ */
#include "../src/services/Service.h"
#include <Wire.h>
/* _____DEFINETIONS__________________________________________________________ */
#define SDA_PIN 48
#define SCL_PIN 45
/* _____GLOBAL VARIABLES_____________________________________________________ */
SemaphoreHandle_t i2c_mutex = NULL; // Mutex for I2C bus access
/* _____GLOBAL FUNCTION______________________________________________________ */

/* _____CLASS DEFINITION_____________________________________________________ */
/**
 * This Service class is the Service to manage the 
 */
class Service_I2C : public Service
{
public:
    Service_I2C();
    ~Service_I2C();

    void checkIn();
    void checkOut();

protected:
     
private:
    static void  Service_I2C_Start();
    static void  Service_I2C_Execute();    
    static void  Service_I2C_End();
} atService_I2C ;
/**
 * This function will be automaticaly called when a object is created by this class
 */
Service_I2C::Service_I2C(/* args */)
{
    _Start_User      = *Service_I2C_Start;
    _Execute_User    = *Service_I2C_Execute;
    _End_User        = *Service_I2C_End;

    // change the ID of Service
    ID_Service = 1;
    // change the Service name
    Name_Service = (char*)"I2C Service";
    // change the ID of SNM
}
/**
 * This function will be automaticaly called when the object of class is delete
 */
Service_I2C::~Service_I2C()
{
    
}
/**
 * This start function will init some critical function 
 */
void  Service_I2C::Service_I2C_Start()
{
    // Initialize I2C bus
    if(i2c_mutex == NULL){
        i2c_mutex = xSemaphoreCreateMutex();
    }
}

/**
 * Execute fuction of SNM app
 */
void  Service_I2C::Service_I2C_Execute()
{   
    // if(atService_I2C.User_Mode == SER_USER_MODE_DEBUG)
    // {
        
    // }   
}    
void  Service_I2C::Service_I2C_End(){}

void Service_I2C::checkIn()
{
    xSemaphoreTake(i2c_mutex, portMAX_DELAY); // Take the mutex to access I2C bus
}

void Service_I2C::checkOut()
{
    xSemaphoreGive(i2c_mutex); // Release the mutex
}

#endif


