#ifndef _Application_atApp_LED_
#define _Application_atApp_LED_
/* _____PROJECT INCLUDES____________________________________________________ */
#include "App.h"
#include "../services/atService_PCF8574.h"
/* _____DEFINITIONS__________________________________________________________ */

/* _____GLOBAL VARIABLES_____________________________________________________ */
TaskHandle_t Task_atApp_LED;  
void atApp_LED_Task_Func(void *parameter);
///////////////////////////////////////////////Testing part//
/* _____GLOBAL FUNCTION______________________________________________________ */

/* _____CLASS DEFINITION_____________________________________________________ */

/**
 * This Application class is the application to manage the 
 */
class App_LED : public Application
{
public:
  	App_LED();
 	~App_LED();
protected:
private:
  	static void  App_LED_Pend();
	static void  App_LED_Start();
	static void  App_LED_Restart();
	static void  App_LED_Execute();
	static void  App_LED_Suspend();
	static void  App_LED_Resume();	  
	static void  App_LED_End();
} atApp_LED ;
/**
 * This function will be automaticaly called when a object is created by this class
 */
App_LED::App_LED(/* args */)
{
  	_Pend_User 	     = *App_LED_Pend;
	_Start_User 	 = *App_LED_Start;
	_Restart_User 	 = *App_LED_Restart;
	_Execute_User 	 = *App_LED_Execute;
	_Suspend_User	 = *App_LED_Suspend;
	_Resume_User	 = *App_LED_Resume;
	_End_User	     = *App_LED_End;

	// change the ID of application
	ID_Application = 1;
	// change the application name
	Name_Application = (char*)"LED Application	";
	// change the ID of SNM
}
/**
 * This function will be automaticaly called when the object of class is delete
 */
App_LED::~App_LED()
{
	
}
/**
 * Pend to start is the first task of this application it will do prerequisite condition. In the debit mode, task will send information of application to terminal to start the application.
 */
void  App_LED::App_LED_Pend()
{
    // atService_PCF8574.Debug();
}
/**
 * This start function will init some critical function 
 */
void  App_LED::App_LED_Start()
{
	// init atPCF8574 Service in the fist running time
	// atService_PCF8574.Run_Service();
}  
/**
 * Restart function of SNM  app
 */
void  App_LED::App_LED_Restart()
{

}
/**
 * Execute fuction of SNM app
 */
void  App_LED::App_LED_Execute()
{	
	// atService_PCF8574.Run_Service();
    if(atApp_LED.User_Mode == APP_USER_MODE_DEBUG)
    {
		
    }   
}
void  App_LED::App_LED_Suspend(){}
void  App_LED::App_LED_Resume(){}	  
void  App_LED::App_LED_End(){}
void atApp_LED_Task_Func(void *parameter)
{
  while (1)
  {
    atApp_LED.Run_Application(APP_RUN_MODE_AUTO);
    vTaskDelay(1000/ portTICK_PERIOD_MS);
  }
}
#endif