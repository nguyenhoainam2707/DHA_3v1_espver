/**
@file
*/
/*
  Service_atService_LED.h

  This version is

  Copyright:: 2021 nguyentrinhtuan1996@gmail.com
*/

#ifndef _Service_atService_LED_
#define _Service_atService_LED_
/* _____PROJECT INCLUDES____________________________________________________ */
#include "Service.h"
/* _____DEFINETIONS__________________________________________________________ */

/* _____GLOBAL VARIABLES_____________________________________________________ */

/* _____GLOBAL FUNCTION______________________________________________________ */

/* _____CLASS DEFINITION_____________________________________________________ */
/**
 * This Service class is the Service to manage the 
 */
class Service_LED : public Service
{
public:
    Service_LED();
    ~Service_LED();
    
protected:
     
private:
    static void  Service_LED_Start();
    static void  Service_LED_Execute();    
    static void  Service_LED_End();
} atService_LED ;
/**
 * This function will be automaticaly called when a object is created by this class
 */
Service_LED::Service_LED(/* args */)
{
    _Start_User      = *Service_LED_Start;
    _Execute_User    = *Service_LED_Execute;
    _End_User        = *Service_LED_End;

    // change the ID of Service
    ID_Service = 1;
    // change the Service name
    Name_Service = (char*)"LED Service";
    // change the ID of SNM
}
/**
 * This function will be automaticaly called when the object of class is delete
 */
Service_LED::~Service_LED()
{
    
}
/**
 * This start function will init some critical function 
 */
void  Service_LED::Service_LED_Start()
{
    
}  

/**
 * Execute fuction of SNM app
 */
void  Service_LED::Service_LED_Execute()
{   
    if(atService_LED.User_Mode == SER_USER_MODE_DEBUG)
    {
        
    }   
}    
void  Service_LED::Service_LED_End(){}

#endif


