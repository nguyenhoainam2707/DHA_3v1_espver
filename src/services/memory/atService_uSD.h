#ifndef _Service_atService_uSD_
#define _Service_atService_uSD_
/* _____PROJECT INCLUDES____________________________________________________ */
#include "../src/services/Service.h"
/* _____DEFINETIONS__________________________________________________________ */
/* _____GLOBAL VARIABLES_____________________________________________________ */
SemaphoreHandle_t uSD_mutex = NULL; // Mutex for uSD bus access
/* _____GLOBAL FUNCTION______________________________________________________ */

/* _____CLASS DEFINITION_____________________________________________________ */
/**
 * This Service class is the Service to manage the 
 */
class Service_uSD : public Service
{
public:
    Service_uSD();
    ~Service_uSD();

    void checkIn();
    void checkOut();

protected:
     
private:
    static void  Service_uSD_Start();
    static void  Service_uSD_Execute();    
    static void  Service_uSD_End();
} atService_uSD ;
/**
 * This function will be automaticaly called when a object is created by this class
 */
Service_uSD::Service_uSD(/* args */)
{
    _Start_User      = *Service_uSD_Start;
    _Execute_User    = *Service_uSD_Execute;
    _End_User        = *Service_uSD_End;

    // change the ID of Service
    ID_Service = 1;
    // change the Service name
    Name_Service = (char*)"uSD Service";
    // change the ID of SNM
}
/**
 * This function will be automaticaly called when the object of class is delete
 */
Service_uSD::~Service_uSD()
{
    
}
/**
 * This start function will init some critical function 
 */
void  Service_uSD::Service_uSD_Start()
{
    // Initialize uSD bus
    if(uSD_mutex == NULL){
        uSD_mutex = xSemaphoreCreateMutex();
    }
}

/**
 * Execute fuction of SNM app
 */
void  Service_uSD::Service_uSD_Execute()
{   
    // if(atService_uSD.User_Mode == SER_USER_MODE_DEBUG)
    // {
        
    // }   
}    
void  Service_uSD::Service_uSD_End(){}

void Service_uSD::checkIn()
{
    xSemaphoreTake(uSD_mutex, portMAX_DELAY); // Take the mutex to access uSD bus
}

void Service_uSD::checkOut()
{
    xSemaphoreGive(uSD_mutex); // Release the mutex
}

#endif


