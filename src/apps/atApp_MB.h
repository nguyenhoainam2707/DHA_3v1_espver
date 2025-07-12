/**
@file

*/
/*
  Application example t

  Library:: 

  This version is

  Copyright:: 2021 nguyentrinhtuan1996@gmail.com
*/

#ifndef _Application_atApp_MB_
#define _Application_atApp_MB_
/* _____PROJECT INCLUDES____________________________________________________ */
#include "App.h"
#include "../services/atService_Modbus.h"
/* _____DEFINITIONS__________________________________________________________ */

/* _____GLOBAL VARIABLES_____________________________________________________ */
TaskHandle_t Task_atApp_MB;  
void atApp_MB_Task_Func(void *parameter);
///////////////////////////////////////////////Testing part//
/* _____GLOBAL FUNCTION______________________________________________________ */

/* _____CLASS DEFINITION_____________________________________________________ */

/**
 * This Application class is the application to manage the 
 */
class App_MB : public Application
{
public:
  	App_MB();
 	~App_MB();
protected:
private:
  	static void  App_MB_Pend();
	static void  App_MB_Start();
	static void  App_MB_Restart();
	static void  App_MB_Execute();
	static void  App_MB_Suspend();
	static void  App_MB_Resume();	  
	static void  App_MB_End();
} atApp_MB ;
/**
 * This function will be automaticaly called when a object is created by this class
 */
App_MB::App_MB(/* args */)
{
  	_Pend_User 	     = *App_MB_Pend;
	_Start_User 	 = *App_MB_Start;
	_Restart_User 	 = *App_MB_Restart;
	_Execute_User 	 = *App_MB_Execute;
	_Suspend_User	 = *App_MB_Suspend;
	_Resume_User	 = *App_MB_Resume;
	_End_User	     = *App_MB_End;

	// change the ID of application
	ID_Application = 1;
	// change the application name
	Name_Application = (char*)"MB Application	";
	// change the ID of SNM
}
/**
 * This function will be automaticaly called when the object of class is delete
 */
App_MB::~App_MB()
{
	
}
/**
 * Pend to start is the first task of this application it will do prerequisite condition. In the debit mode, task will send information of application to terminal to start the application.
 */
void  App_MB::App_MB_Pend()
{
    // atService_Modbus.Debug();
}
/**
 * This start function will init some critical function 
 */
void  App_MB::App_MB_Start()
{
	// init atModbus Service in the fist running time
	// atService_Modbus.Run_Service();
}  
/**
 * Restart function of SNM  app
 */
void  App_MB::App_MB_Restart()
{

}
/**
 * Execute fuction of SNM app
 */
void  App_MB::App_MB_Execute()
{	
	// atService_Modbus.Run_Service();
    if(atApp_MB.User_Mode == APP_USER_MODE_DEBUG)
    {
		
    }   
}
void  App_MB::App_MB_Suspend(){}
void  App_MB::App_MB_Resume(){}	  
void  App_MB::App_MB_End(){}
void atApp_MB_Task_Func(void *parameter)
{
  while (1)
  {
    atApp_MB.Run_Application(APP_RUN_MODE_AUTO);
    vTaskDelay(1000/ portTICK_PERIOD_MS);
  }
}
#endif