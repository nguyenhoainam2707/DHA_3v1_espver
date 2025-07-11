/**
@file

*/
/*
  Application example t

  Library::

  This version is

  Copyright:: 2021 nguyentrinhtuan1996@gmail.com
*/

#ifndef _Application_atApp_PWM_
#define _Application_atApp_PWM_
/* _____PROJECT INCLUDES____________________________________________________ */
#include "App.h"
#include "../src/obj/atObj_Param.h"
/* _____DEFINITIONS__________________________________________________________ */
#define P1_PWM 39
#define P2_PWM 2
#define P3_PWM 37
#define P4_PWM 38
/* _____GLOBAL VARIABLES_____________________________________________________ */
TaskHandle_t Task_atApp_PWM;
void atApp_PWM_Task_Func(void *parameter);
///////////////////////////////////////////////Testing part//
/* _____GLOBAL FUNCTION______________________________________________________ */

/* _____CLASS DEFINITION_____________________________________________________ */

/**
 * This Application class is the application to manage the
 */
class App_PWM : public Application
{
public:
	App_PWM();
	~App_PWM();

protected:
private:
	static void App_PWM_Pend();
	static void App_PWM_Start();
	static void App_PWM_Restart();
	static void App_PWM_Execute();
	static void App_PWM_Suspend();
	static void App_PWM_Resume();
	static void App_PWM_End();
} atApp_PWM;
/**
 * This function will be automaticaly called when a object is created by this class
 */
App_PWM::App_PWM(/* args */)
{
	_Pend_User = *App_PWM_Pend;
	_Start_User = *App_PWM_Start;
	_Restart_User = *App_PWM_Restart;
	_Execute_User = *App_PWM_Execute;
	_Suspend_User = *App_PWM_Suspend;
	_Resume_User = *App_PWM_Resume;
	_End_User = *App_PWM_End;

	// change the ID of application
	ID_Application = 1;
	// change the application name
	Name_Application = (char *)"PWM Application	";
	// change the ID of SNM
}
/**
 * This function will be automaticaly called when the object of class is delete
 */
App_PWM::~App_PWM()
{
}
/**
 * Pend to start is the first task of this application it will do prerequisite condition. In the debit mode, task will send information of application to terminal to start the application.
 */
void App_PWM::App_PWM_Pend()
{
	// atService_XYZ.Debug();
}
/**
 * This start function will init some critical function
 */
void App_PWM::App_PWM_Start()
{
	if (atApp_PWM.User_Mode == APP_USER_MODE_DEBUG)
	{
		Serial.println("PWM Application is starting...");
	}
	if (Object_Param::enCh1PWM)
	{
		if (Object_Param::freqCh1PWM < 1 || Object_Param::freqCh1PWM > 20000)
		{
			if (atApp_PWM.User_Mode == APP_USER_MODE_DEBUG)
			{
				Serial.print("Invalid frequency for Channel 1 PWM: ");
				Serial.print(Object_Param::freqCh1PWM);
				Serial.println(" Hz. Setting to default 5000 Hz. Frequency must be between 1 and 20000 Hz.");
			}
			Object_Param::freqCh1PWM = 5000;
		}
		if (Object_Param::resolutionCh1PWM < 1 || Object_Param::resolutionCh1PWM > 14)
		{
			if (atApp_PWM.User_Mode == APP_USER_MODE_DEBUG)
			{
				Serial.print("Invalid resolution for Channel 1 PWM: ");
				Serial.print(Object_Param::resolutionCh1PWM);
				Serial.println(" bits. Setting to default 8 bits. Resolution must be between 1 and 14 bits.");
			}
			Object_Param::resolutionCh1PWM = 8;
		}
		ledcSetup(0, Object_Param::freqCh1PWM, Object_Param::resolutionCh1PWM);
		ledcAttachPin(P1_PWM, 0);
		if (atApp_PWM.User_Mode == APP_USER_MODE_DEBUG)
		{
			Serial.print("Channel 1 PWM started with frequency: ");
			Serial.print(Object_Param::freqCh1PWM);
			Serial.print(" Hz, resolution: ");
			Serial.print(Object_Param::resolutionCh1PWM);
			Serial.println(" bits.");
		}
	}
	if (Object_Param::enCh2PWM)
	{
		if (Object_Param::freqCh2PWM < 1 || Object_Param::freqCh2PWM > 20000)
		{
			if (atApp_PWM.User_Mode == APP_USER_MODE_DEBUG)
			{
				Serial.print("Invalid frequency for Channel 2 PWM: ");
				Serial.print(Object_Param::freqCh2PWM);
				Serial.println(" Hz. Setting to default 5000 Hz. Frequency must be between 1 and 20000 Hz.");
			}
			Object_Param::freqCh2PWM = 5000;
		}
		if (Object_Param::resolutionCh2PWM < 1 || Object_Param::resolutionCh2PWM > 14)
		{
			if (atApp_PWM.User_Mode == APP_USER_MODE_DEBUG)
			{
				Serial.print("Invalid resolution for Channel 2 PWM: ");
				Serial.print(Object_Param::resolutionCh2PWM);
				Serial.println(" bits. Setting to default 8 bits. Resolution must be between 1 and 14 bits.");
			}
			Object_Param::resolutionCh2PWM = 8;
		}
		ledcSetup(1, Object_Param::freqCh2PWM, Object_Param::resolutionCh2PWM);
		ledcAttachPin(P2_PWM, 1);
		if (atApp_PWM.User_Mode == APP_USER_MODE_DEBUG)
		{
			Serial.print("Channel 2 PWM started with frequency: ");
			Serial.print(Object_Param::freqCh2PWM);
			Serial.print(" Hz, resolution: ");
			Serial.print(Object_Param::resolutionCh2PWM);
			Serial.println(" bits.");
		}
	}
	if (Object_Param::enCh3PWM)
	{
		if (Object_Param::freqCh3PWM < 1 || Object_Param::freqCh3PWM > 20000)
		{
			if (atApp_PWM.User_Mode == APP_USER_MODE_DEBUG)
			{
				Serial.print("Invalid frequency for Channel 3 PWM: ");
				Serial.print(Object_Param::freqCh3PWM);
				Serial.println(" Hz. Setting to default 5000 Hz. Frequency must be between 1 and 20000 Hz.");
			}
			Object_Param::freqCh3PWM = 5000;
		}
		if (Object_Param::resolutionCh3PWM < 1 || Object_Param::resolutionCh3PWM > 14)
		{
			if (atApp_PWM.User_Mode == APP_USER_MODE_DEBUG)
			{
				Serial.print("Invalid resolution for Channel 3 PWM: ");
				Serial.print(Object_Param::resolutionCh3PWM);
				Serial.println(" bits. Setting to default 8 bits. Resolution must be between 1 and 14 bits.");
			}
			Object_Param::resolutionCh3PWM = 8;
		}
		ledcSetup(2, Object_Param::freqCh3PWM, Object_Param::resolutionCh3PWM);
		ledcAttachPin(P3_PWM, 2);
		if (atApp_PWM.User_Mode == APP_USER_MODE_DEBUG)
		{
			Serial.print("Channel 3 PWM started with frequency: ");
			Serial.print(Object_Param::freqCh3PWM);
			Serial.print(" Hz, resolution: ");
			Serial.print(Object_Param::resolutionCh3PWM);
			Serial.println(" bits.");
		}
	}
	if (Object_Param::enCh4PWM)
	{
		if (Object_Param::freqCh4PWM < 1 || Object_Param::freqCh4PWM > 20000)
		{
			if (atApp_PWM.User_Mode == APP_USER_MODE_DEBUG)
			{
				Serial.print("Invalid frequency for Channel 4 PWM: ");
				Serial.print(Object_Param::freqCh4PWM);
				Serial.println(" Hz. Setting to default 5000 Hz. Frequency must be between 1 and 20000 Hz.");
			}
			Object_Param::freqCh4PWM = 5000;
		}
		if (Object_Param::resolutionCh4PWM < 1 || Object_Param::resolutionCh4PWM > 14)
		{
			if (atApp_PWM.User_Mode == APP_USER_MODE_DEBUG)
			{
				Serial.print("Invalid resolution for Channel 4 PWM: ");
				Serial.print(Object_Param::resolutionCh4PWM);
				Serial.println(" bits. Setting to default 8 bits. Resolution must be between 1 and 14 bits.");
			}
			Object_Param::resolutionCh4PWM = 8;
		}
		ledcSetup(3, Object_Param::freqCh4PWM, Object_Param::resolutionCh4PWM);
		ledcAttachPin(P4_PWM, 3);
		if (atApp_PWM.User_Mode == APP_USER_MODE_DEBUG)
		{
			Serial.print("Channel 4 PWM started with frequency: ");
			Serial.print(Object_Param::freqCh4PWM);
			Serial.print(" Hz, resolution: ");
			Serial.print(Object_Param::resolutionCh4PWM);
			Serial.println(" bits.");
		}
	}
}
/**
 * Restart function of SNM  app
 */
void App_PWM::App_PWM_Restart()
{
}
/**
 * Execute fuction of SNM app
 */
void App_PWM::App_PWM_Execute()
{
	
}
void App_PWM::App_PWM_Suspend() {}
void App_PWM::App_PWM_Resume() {}
void App_PWM::App_PWM_End() {}
void atApp_PWM_Task_Func(void *parameter)
{
	while (1)
	{
		atApp_PWM.Run_Application(APP_RUN_MODE_AUTO);
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}
#endif