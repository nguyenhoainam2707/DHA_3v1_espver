#ifndef _Application_atApp_MB1_
#define _Application_atApp_MB1_
/* _____PROJECT INCLUDES____________________________________________________ */
#include "App.h"
#include "../services/atService_Modbus.h"
#include "../src/obj/atObj_Param.h"
#include "../src/obj/atObj_Data.h"
/* _____DEFINITIONS__________________________________________________________ */

/* _____GLOBAL VARIABLES_____________________________________________________ */
TaskHandle_t Task_atApp_MB1;
void atApp_MB1_Task_Func(void *parameter);
///////////////////////////////////////////////Testing part//
/* _____GLOBAL FUNCTION______________________________________________________ */

/* _____CLASS DEFINITION_____________________________________________________ */

/**
 * This Application class is the application to manage the
 */
class App_MB1 : public Application
{
public:
	App_MB1();
	~App_MB1();

protected:
private:
	static void App_MB1_Pend();
	static void App_MB1_Start();
	static void App_MB1_Restart();
	static void App_MB1_Execute();
	static void App_MB1_Suspend();
	static void App_MB1_Resume();
	static void App_MB1_End();
} atApp_MB1;
/**
 * This function will be automaticaly called when a object is created by this class
 */
App_MB1::App_MB1(/* args */)
{
	_Pend_User = *App_MB1_Pend;
	_Start_User = *App_MB1_Start;
	_Restart_User = *App_MB1_Restart;
	_Execute_User = *App_MB1_Execute;
	_Suspend_User = *App_MB1_Suspend;
	_Resume_User = *App_MB1_Resume;
	_End_User = *App_MB1_End;

	// change the ID of application
	ID_Application = 1;
	// change the application name
	Name_Application = (char *)"MB1 Application	";
	// change the ID of SNM
}
/**
 * This function will be automaticaly called when the object of class is delete
 */
App_MB1::~App_MB1()
{
}
/**
 * Pend to start is the first task of this application it will do prerequisite condition. In the debit mode, task will send information of application to terminal to start the application.
 */
void App_MB1::App_MB1_Pend()
{
	// atService_Modbus.Debug();
}
/**
 * This start function will init some critical function
 */
void App_MB1::App_MB1_Start()
{
	// init atModbus Service in the fist running time
	atService_Modbus.Run_Service();
}
/**
 * Restart function of SNM  app
 */
void App_MB1::App_MB1_Restart()
{
}
/**
 * Execute fuction of SNM app
 */
void App_MB1::App_MB1_Execute()
{
	atObject_Data.rs485Ch1 = atService_Modbus.mb1ReadHoldingRegisters(atObject_Param.startAddressMB1);
	if (atApp_MB1.User_Mode == APP_USER_MODE_DEBUG)
	{
		Serial.print(atObject_Param.sensorNameMB1 + ": ");
		Serial.println(atObject_Data.rs485Ch1 + " mm");
	}
}
void App_MB1::App_MB1_Suspend() {}
void App_MB1::App_MB1_Resume() {}
void App_MB1::App_MB1_End() {}
void atApp_MB1_Task_Func(void *parameter)
{
	while (1)
	{
		atApp_MB1.Run_Application(APP_RUN_MODE_AUTO);
		vTaskDelay(atObject_Param.refreshRateMB1 / portTICK_PERIOD_MS);
	}
}
#endif