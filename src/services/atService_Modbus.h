/**
@file
*/
/*
  Service_atService_Modbus.h

  This version is

  Copyright:: 2021 nguyentrinhtuan1996@gmail.com
*/

#ifndef _Service_atService_Modbus_
#define _Service_atService_Modbus_
/* _____PROJECT INCLUDES____________________________________________________ */
#include "Service.h"
/* _____DEFINETIONS__________________________________________________________ */

/* _____GLOBAL VARIABLES_____________________________________________________ */

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
    
protected:
     
private:
    static void  Service_Modbus_Start();
    static void  Service_Modbus_Execute();    
    static void  Service_Modbus_End();
} atService_Modbus ;
/**
 * This function will be automaticaly called when a object is created by this class
 */
Service_Modbus::Service_Modbus(/* args */)
{
    _Start_User      = *Service_Modbus_Start;
    _Execute_User    = *Service_Modbus_Execute;
    _End_User        = *Service_Modbus_End;

    // change the ID of Service
    ID_Service = 1;
    // change the Service name
    Name_Service = (char*)"Modbus Service";
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
void  Service_Modbus::Service_Modbus_Start()
{
    
}  

/**
 * Execute fuction of SNM app
 */
void  Service_Modbus::Service_Modbus_Execute()
{   
    if(atService_Modbus.User_Mode == SER_USER_MODE_DEBUG)
    {
        
    }   
}    
void  Service_Modbus::Service_Modbus_End(){}

#endif


