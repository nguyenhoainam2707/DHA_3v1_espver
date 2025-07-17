#ifndef _Application_atApp_PWM_
#define _Application_atApp_PWM_
/* _____PROJECT INCLUDES____________________________________________________ */
#include "App.h"
#include "../src/obj/atObj_Param.h"
#include "../src/apps/atApp_Database.h"
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

	static void setPWMChannel(uint8_t channel);
	// static bool prevEnCh1PWM;
	// static bool prevEnCh2PWM;
	// static bool prevEnCh3PWM;
	// static bool prevEnCh4PWM;
	// static uint32_t prevFreqCh1PWM;
	// static uint32_t prevFreqCh2PWM;
	// static uint32_t prevFreqCh3PWM;
	// static uint32_t prevFreqCh4PWM;
	// static uint8_t prevResolutionCh1PWM;
	// static uint8_t prevResolutionCh2PWM;
	// static uint8_t prevResolutionCh3PWM;
	// static uint8_t prevResolutionCh4PWM;
	// static float prevDutyCycleCh1PWM;
	// static float prevDutyCycleCh2PWM;
	// static float prevDutyCycleCh3PWM;
	// static float prevDutyCycleCh4PWM;

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

// bool App_PWM::prevEnCh1PWM = atObject_Param.enCh1PWM;
// bool App_PWM::prevEnCh2PWM = atObject_Param.enCh2PWM;
// bool App_PWM::prevEnCh3PWM = atObject_Param.enCh3PWM;
// bool App_PWM::prevEnCh4PWM = atObject_Param.enCh4PWM;
// uint32_t App_PWM::prevFreqCh1PWM = atObject_Param.freqCh1PWM;
// uint32_t App_PWM::prevFreqCh2PWM = atObject_Param.freqCh2PWM;
// uint32_t App_PWM::prevFreqCh3PWM = atObject_Param.freqCh3PWM;
// uint32_t App_PWM::prevFreqCh4PWM = atObject_Param.freqCh4PWM;
// uint8_t App_PWM::prevResolutionCh1PWM = atObject_Param.resolutionCh1PWM;
// uint8_t App_PWM::prevResolutionCh2PWM = atObject_Param.resolutionCh2PWM;
// uint8_t App_PWM::prevResolutionCh3PWM = atObject_Param.resolutionCh3PWM;
// uint8_t App_PWM::prevResolutionCh4PWM = atObject_Param.resolutionCh4PWM;
// float App_PWM::prevDutyCycleCh1PWM = atObject_Param.dutyCycleCh1PWM;
// float App_PWM::prevDutyCycleCh2PWM = atObject_Param.dutyCycleCh2PWM;
// float App_PWM::prevDutyCycleCh3PWM = atObject_Param.dutyCycleCh3PWM;
// float App_PWM::prevDutyCycleCh4PWM = atObject_Param.dutyCycleCh4PWM;
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
	if (atObject_Param.enCh1PWM)
	{
		setPWMChannel(1);
	}
	if (atObject_Param.enCh2PWM)
	{
		setPWMChannel(2);
	}
	if (atObject_Param.enCh3PWM)
	{
		setPWMChannel(3);
	}
	if (atObject_Param.enCh4PWM)
	{
		setPWMChannel(4);
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
void App_PWM::setPWMChannel(uint8_t channel)
{
	switch (channel)
	{
	case 1:
		if (atObject_Param.freqCh1PWM < 1 || atObject_Param.freqCh1PWM > 20000)
		{
			if (atApp_PWM.User_Mode == APP_USER_MODE_DEBUG)
			{
				Serial.print("Invalid frequency for Channel 1 PWM: ");
				Serial.print(atObject_Param.freqCh1PWM);
				Serial.println(" Hz. Setting to default 5000 Hz. Frequency must be between 1 and 20000 Hz.");
			}
			atObject_Param.freqCh1PWM = 5000;
		}
		if (atObject_Param.resolutionCh1PWM < 1 || atObject_Param.resolutionCh1PWM > 14)
		{
			if (atApp_PWM.User_Mode == APP_USER_MODE_DEBUG)
			{
				Serial.print("Invalid resolution for Channel 1 PWM: ");
				Serial.print(atObject_Param.resolutionCh1PWM);
				Serial.println(" bits. Setting to default 8 bits. Resolution must be between 1 and 14 bits.");
			}
			atObject_Param.resolutionCh1PWM = 8;
		}
		ledcSetup(0, atObject_Param.freqCh1PWM, atObject_Param.resolutionCh1PWM);
		ledcAttachPin(P1_PWM, 0);
		ledcWrite(0, (uint32_t)(atObject_Param.dutyCycleCh1PWM * ((1 << atObject_Param.resolutionCh1PWM) - 1) / 100));
		if (atApp_PWM.User_Mode == APP_USER_MODE_DEBUG)
		{
			Serial.print("Channel 1 PWM started with frequency: ");
			Serial.print(atObject_Param.freqCh1PWM);
			Serial.print(" Hz, resolution: ");
			Serial.print(atObject_Param.resolutionCh1PWM);
			Serial.println(" bits.");
		}
		break;
	case 2:
		if (atObject_Param.freqCh2PWM < 1 || atObject_Param.freqCh2PWM > 20000)
		{
			if (atApp_PWM.User_Mode == APP_USER_MODE_DEBUG)
			{
				Serial.print("Invalid frequency for Channel 2 PWM: ");
				Serial.print(atObject_Param.freqCh2PWM);
				Serial.println(" Hz. Setting to default 5000 Hz. Frequency must be between 1 and 20000 Hz.");
			}
			atObject_Param.freqCh2PWM = 5000;
		}
		if (atObject_Param.resolutionCh2PWM < 1 || atObject_Param.resolutionCh2PWM > 14)
		{
			if (atApp_PWM.User_Mode == APP_USER_MODE_DEBUG)
			{
				Serial.print("Invalid resolution for Channel 2 PWM: ");
				Serial.print(atObject_Param.resolutionCh2PWM);
				Serial.println(" bits. Setting to default 8 bits. Resolution must be between 1 and 14 bits.");
			}
			atObject_Param.resolutionCh2PWM = 8;
		}
		ledcSetup(1, atObject_Param.freqCh2PWM, atObject_Param.resolutionCh2PWM);
		ledcAttachPin(P2_PWM, 1);
		ledcWrite(1, (uint32_t)(atObject_Param.dutyCycleCh2PWM * ((1 << atObject_Param.resolutionCh2PWM) - 1) / 100));
		if (atApp_PWM.User_Mode == APP_USER_MODE_DEBUG)
		{
			Serial.print("Channel 2 PWM started with frequency: ");
			Serial.print(atObject_Param.freqCh2PWM);
			Serial.print(" Hz, resolution: ");
			Serial.print(atObject_Param.resolutionCh2PWM);
			Serial.println(" bits.");
		}
		break;
	case 3:
		if (atObject_Param.freqCh3PWM < 1 || atObject_Param.freqCh3PWM > 20000)
		{
			if (atApp_PWM.User_Mode == APP_USER_MODE_DEBUG)
			{
				Serial.print("Invalid frequency for Channel 3 PWM: ");
				Serial.print(atObject_Param.freqCh3PWM);
				Serial.println(" Hz. Setting to default 5000 Hz. Frequency must be between 1 and 20000 Hz.");
			}
			atObject_Param.freqCh3PWM = 5000;
		}
		if (atObject_Param.resolutionCh3PWM < 1 || atObject_Param.resolutionCh3PWM > 14)
		{
			if (atApp_PWM.User_Mode == APP_USER_MODE_DEBUG)
			{
				Serial.print("Invalid resolution for Channel 3 PWM: ");
				Serial.print(atObject_Param.resolutionCh3PWM);
				Serial.println(" bits. Setting to default 8 bits. Resolution must be between 1 and 14 bits.");
			}
			atObject_Param.resolutionCh3PWM = 8;
		}
		ledcSetup(2, atObject_Param.freqCh3PWM, atObject_Param.resolutionCh3PWM);
		ledcAttachPin(P3_PWM, 2);
		ledcWrite(2, (uint32_t)(atObject_Param.dutyCycleCh3PWM * ((1 << atObject_Param.resolutionCh3PWM) - 1) / 100));
		if (atApp_PWM.User_Mode == APP_USER_MODE_DEBUG)
		{
			Serial.print("Channel 3 PWM started with frequency: ");
			Serial.print(atObject_Param.freqCh3PWM);
			Serial.print(" Hz, resolution: ");
			Serial.print(atObject_Param.resolutionCh3PWM);
			Serial.println(" bits.");
		}
		break;
	case 4:
		if (atObject_Param.freqCh4PWM < 1 || atObject_Param.freqCh4PWM > 20000)
		{
			if (atApp_PWM.User_Mode == APP_USER_MODE_DEBUG)
			{
				Serial.print("Invalid frequency for Channel 4 PWM: ");
				Serial.print(atObject_Param.freqCh4PWM);
				Serial.println(" Hz. Setting to default 5000 Hz. Frequency must be between 1 and 20000 Hz.");
			}
			atObject_Param.freqCh4PWM = 5000;
		}
		if (atObject_Param.resolutionCh4PWM < 1 || atObject_Param.resolutionCh4PWM > 14)
		{
			if (atApp_PWM.User_Mode == APP_USER_MODE_DEBUG)
			{
				Serial.print("Invalid resolution for Channel 4 PWM: ");
				Serial.print(atObject_Param.resolutionCh4PWM);
				Serial.println(" bits. Setting to default 8 bits. Resolution must be between 1 and 14 bits.");
			}
			atObject_Param.resolutionCh4PWM = 8;
		}
		ledcSetup(3, atObject_Param.freqCh4PWM, atObject_Param.resolutionCh4PWM);
		ledcAttachPin(P4_PWM, 3);
		ledcWrite(3, (uint32_t)(atObject_Param.dutyCycleCh4PWM * ((1 << atObject_Param.resolutionCh4PWM) - 1) / 100));
		if (atApp_PWM.User_Mode == APP_USER_MODE_DEBUG)
		{
			Serial.print("Channel 4 PWM started with frequency: ");
			Serial.print(atObject_Param.freqCh4PWM);
			Serial.print(" Hz, resolution: ");
			Serial.print(atObject_Param.resolutionCh4PWM);
			Serial.println(" bits.");
		}
		break;
	default:
		if (atApp_PWM.User_Mode == APP_USER_MODE_DEBUG)
		{
			Serial.println("Invalid PWM channel. Please select a channel between 1 and 4.");
		}
	}
}
void atApp_PWM_Task_Func(void *parameter)
{
	while (1)
	{
		atApp_PWM.Run_Application(APP_RUN_MODE_AUTO);
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}
#endif