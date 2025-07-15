
#ifndef _Application_atApp_DI_
#define _Application_atApp_DI_
/* _____PROJECT INCLUDES____________________________________________________ */
#include "App.h"
#include "../services/atService_PCF8574.h"
/* _____DEFINITIONS__________________________________________________________ */

/* _____GLOBAL VARIABLES_____________________________________________________ */
TaskHandle_t Task_atApp_DI;
void atApp_DI_Task_Func(void *parameter);
///////////////////////////////////////////////Testing part//
/* _____GLOBAL FUNCTION______________________________________________________ */

/* _____CLASS DEFINITION_____________________________________________________ */

/**
 * This Application class is the application to manage the
 */
class App_DI : public Application
{
public:
	App_DI();
	~App_DI();

protected:
private:
	static void App_DI_Pend();
	static void App_DI_Start();
	static void App_DI_Restart();
	static void App_DI_Execute();
	static void App_DI_Suspend();
	static void App_DI_Resume();
	static void App_DI_End();
} atApp_DI;
/**
 * This function will be automaticaly called when a object is created by this class
 */
App_DI::App_DI(/* args */)
{
	_Pend_User = *App_DI_Pend;
	_Start_User = *App_DI_Start;
	_Restart_User = *App_DI_Restart;
	_Execute_User = *App_DI_Execute;
	_Suspend_User = *App_DI_Suspend;
	_Resume_User = *App_DI_Resume;
	_End_User = *App_DI_End;

	// change the ID of application
	ID_Application = 1;
	// change the application name
	Name_Application = (char *)"DI Application	";
	// change the ID of SNM
}
/**
 * This function will be automaticaly called when the object of class is delete
 */
App_DI::~App_DI()
{
}
/**
 * Pend to start is the first task of this application it will do prerequisite condition. In the debit mode, task will send information of application to terminal to start the application.
 */
void App_DI::App_DI_Pend()
{
	// atService_PCF8574.Debug();
}
/**
 * This start function will init some critical function
 */
void App_DI::App_DI_Start()
{
	// init atPCF8574 Service in the fist running time
	atService_I2C.Run_Service();
	atService_PCF8574.Run_Service();
}
/**
 * Restart function of SNM  app
 */
void App_DI::App_DI_Restart()
{
}
/**
 * Execute fuction of SNM app
 */
void App_DI::App_DI_Execute()
{
	// Read DI channels
	if (atObject_Param.enCh1DI)
	{
		bool state = atService_PCF8574.pcfDigitalRead(1);
		if (atApp_DI.User_Mode == APP_USER_MODE_DEBUG)
		{
			Serial.print("DI Channel 1 state: ");
			Serial.println(state);
		}
	}
	if (atObject_Param.enCh2DI)
	{
		bool state = atService_PCF8574.pcfDigitalRead(2);
		if (atApp_DI.User_Mode == APP_USER_MODE_DEBUG)
		{
			Serial.print("DI Channel 2 state: ");
			Serial.println(state);
		}
	}
	if (atObject_Param.enCh3DI)
	{
		bool state = atService_PCF8574.pcfDigitalRead(3);
		if (atApp_DI.User_Mode == APP_USER_MODE_DEBUG)
		{
			Serial.print("DI Channel 3 state: ");
			Serial.println(state);
		}
	}
	if (atObject_Param.enCh4DI)
	{
		bool state = atService_PCF8574.pcfDigitalRead(4);
		if (atApp_DI.User_Mode == APP_USER_MODE_DEBUG)
		{
			Serial.print("DI Channel 4 state: ");
			Serial.println(state);
		}
	}
	if (atApp_DI.User_Mode == APP_USER_MODE_DEBUG)
	{
		if (atObject_Param.enCh1DI || atObject_Param.enCh2DI || atObject_Param.enCh3DI || atObject_Param.enCh4DI)
		{
			Serial.println("--------------------------------------------------");
		}
	}
}
void App_DI::App_DI_Suspend() {}
void App_DI::App_DI_Resume() {}
void App_DI::App_DI_End() {}
void atApp_DI_Task_Func(void *parameter)
{
	while (1)
	{
		atApp_DI.Run_Application(APP_RUN_MODE_AUTO);
		vTaskDelay(atObject_Param.delayDI / portTICK_PERIOD_MS);
	}
}
#endif