#ifndef _Application_atApp_MB2_
#define _Application_atApp_MB2_
/* _____PROJECT INCLUDES____________________________________________________ */
#include "App.h"
#include "../services/atService_Modbus.h"
#include "../src/obj/atObj_Param.h"
#include "../src/obj/atObj_Data.h"
#include "../src/apps/atApp_Database.h"
/* _____DEFINITIONS__________________________________________________________ */

/* _____GLOBAL VARIABLES_____________________________________________________ */
TaskHandle_t Task_atApp_MB2;  
void atApp_MB2_Task_Func(void *parameter);
///////////////////////////////////////////////Testing part//
/* _____GLOBAL FUNCTION______________________________________________________ */

/* _____CLASS DEFINITION_____________________________________________________ */

/**
 * This Application class is the application to manage the 
 */
class App_MB2 : public Application
{
public:
  	App_MB2();
 	~App_MB2();
protected:
private:
  	static void  App_MB2_Pend();
	static void  App_MB2_Start();
	static void  App_MB2_Restart();
	static void  App_MB2_Execute();
	static void  App_MB2_Suspend();
	static void  App_MB2_Resume();	  
	static void  App_MB2_End();
} atApp_MB2 ;
/**
 * This function will be automaticaly called when a object is created by this class
 */
App_MB2::App_MB2(/* args */)
{
  	_Pend_User 	     = *App_MB2_Pend;
	_Start_User 	 = *App_MB2_Start;
	_Restart_User 	 = *App_MB2_Restart;
	_Execute_User 	 = *App_MB2_Execute;
	_Suspend_User	 = *App_MB2_Suspend;
	_Resume_User	 = *App_MB2_Resume;
	_End_User	     = *App_MB2_End;

	// change the ID of application
	ID_Application = 1;
	// change the application name
	Name_Application = (char*)"MB2 Application	";
	// change the ID of SNM
}
/**
 * This function will be automaticaly called when the object of class is delete
 */
App_MB2::~App_MB2()
{
	
}
/**
 * Pend to start is the first task of this application it will do prerequisite condition. In the debit mode, task will send information of application to terminal to start the application.
 */
void  App_MB2::App_MB2_Pend()
{
    // atService_Modbus.Debug();
}
/**
 * This start function will init some critical function 
 */
void  App_MB2::App_MB2_Start()
{
	// init atModbus Service in the fist running time
	atService_Modbus.Run_Service();
	atService_Modbus.mb2Init();
}  
/**
 * Restart function of SNM  app
 */
void  App_MB2::App_MB2_Restart()
{

}
/**
 * Execute fuction of SNM app
 */
void  App_MB2::App_MB2_Execute()
{	
	atObject_Data.rs485Ch2= atService_Modbus.mb2ReadHoldingRegisters(atObject_Param.startAddressMB2);
	if (atApp_MB2.User_Mode == APP_USER_MODE_DEBUG)
	{
		Serial.print(atObject_Param.sensorNameMB2 + ": ");
		Serial.println(atObject_Data.rs485Ch2);
	}
}
void  App_MB2::App_MB2_Suspend(){}
void  App_MB2::App_MB2_Resume(){}	  
void  App_MB2::App_MB2_End(){}
void atApp_MB2_Task_Func(void *parameter)
{
  while (1)
  {
    atApp_MB2.Run_Application(APP_RUN_MODE_AUTO);
    vTaskDelay(atObject_Param.refreshRateMB2 / portTICK_PERIOD_MS);
  }
}
#endif