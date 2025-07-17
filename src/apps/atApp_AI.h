#ifndef _Application_atApp_AI_
#define _Application_atApp_AI_
/* _____PROJECT INCLUDES____________________________________________________ */
#include "App.h"
#include "../services/atService_ADS1115.h"
#include "../src/obj/atObj_Param.h"
#include "../src/obj/atObj_Data.h"
#include "../src/apps/atApp_Database.h"
/* _____DEFINITIONS__________________________________________________________ */

/* _____GLOBAL VARIABLES_____________________________________________________ */
TaskHandle_t Task_atApp_AI;
void atApp_AI_Task_Func(void *parameter);
///////////////////////////////////////////////Testing part//
/* _____GLOBAL FUNCTION______________________________________________________ */

/* _____CLASS DEFINITION_____________________________________________________ */

/**
 * This Application class is the application to manage the
 */
class App_AI : public Application
{
public:
	App_AI();
	~App_AI();

	static bool ads1115InitOke; // this variable will be set to true when the ADS1115 is initialized successfully

protected:
private:
	static void App_AI_Pend();
	static void App_AI_Start();
	static void App_AI_Restart();
	static void App_AI_Execute();
	static void App_AI_Suspend();
	static void App_AI_Resume();
	static void App_AI_End();
} atApp_AI;

bool App_AI::ads1115InitOke = false; // Initialize the ADS1115 status to false
/**
 * This function will be automaticaly called when a object is created by this class
 */
App_AI::App_AI(/* args */)
{
	_Pend_User = *App_AI_Pend;
	_Start_User = *App_AI_Start;
	_Restart_User = *App_AI_Restart;
	_Execute_User = *App_AI_Execute;
	_Suspend_User = *App_AI_Suspend;
	_Resume_User = *App_AI_Resume;
	_End_User = *App_AI_End;

	// change the ID of application
	ID_Application = 1;
	// change the application name
	Name_Application = (char *)"AI Application	";
	// change the ID of SNM
}
/**
 * This function will be automaticaly called when the object of class is delete
 */
App_AI::~App_AI()
{
}
/**
 * Pend to start is the first task of this application it will do prerequisite condition. In the debit mode, task will send information of application to terminal to start the application.
 */
void App_AI::App_AI_Pend()
{
	// atService_ADS1115.Debug();
}
/**
 * This start function will init some critical function
 */
void App_AI::App_AI_Start()
{
	atService_ADS1115.Run_Service();
	/*
	|      Gain       |        Voltage Range       |        	  Data rate                 |
	|-----------------|----------------------------|----------------------------------------|
	| GAIN_TWOTHIRDS  | -6.144V to +6.144V         | RATE_ADS1115_8SPS   :  8 samples/sec   |
	| GAIN_ONE        | -4.096V to +4.096V         | RATE_ADS1115_16SPS  : 16 samples/sec   |
	| GAIN_TWO        | -2.048V to +2.048V         | RATE_ADS1115_32SPS  : 32 samples/sec   |
	| GAIN_FOUR       | -1.024V to +1.024V         | RATE_ADS1115_64SPS  : 64 samples/sec   |
	| GAIN_EIGHT      | -0.512V to +0.512V         | RATE_ADS1115_128SPS : 128 samples/sec  |
	| GAIN_SIXTEEN    | -0.256V to +0.256V         | RATE_ADS1115_250SPS : 250 samples/sec  |
	|                 |                            | RATE_ADS1115_475SPS : 475 samples/sec  |
	|                 |                            | RATE_ADS1115_860SPS : 860 samples/sec  |
	*/
	ads1115InitOke = Service_ADS1115::ADS1115_Init(GAIN_TWO, RATE_ADS1115_8SPS);
	if (ads1115InitOke)
	{
		if (atApp_AI.User_Mode == APP_USER_MODE_DEBUG)
		{
			Serial.println("ADS1115 init success!");
		}
	}
	else
	{
		if (atApp_AI.User_Mode == APP_USER_MODE_DEBUG)
		{
			Serial.println("ADS1115 init failed!");
		}
		for (int i = 0; i < 5; i++)
		{
			vTaskDelay(2000 / portTICK_PERIOD_MS); // Delay to allow the user to see the error message
			ads1115InitOke = Service_ADS1115::ADS1115_Init(GAIN_TWOTHIRDS, RATE_ADS1115_8SPS);
			if (atApp_AI.User_Mode == APP_USER_MODE_DEBUG)
			{
				Serial.println("Retry ADS1115 init...");
			}
			if (!ads1115InitOke)
			{
				Serial.println("ADS1115 init failed!");
			}
			else
			{
				if (atApp_AI.User_Mode == APP_USER_MODE_DEBUG)
				{
					Serial.println("ADS1115 reinitialize success!");
				}
				break; // Exit the retry loop if initialization is successful
			}
		}
		if (!ads1115InitOke)
		{
			if (atApp_AI.User_Mode == APP_USER_MODE_DEBUG)
			{
				Serial.println("Suspending AI task due to repeated initialization failure.");
			}
			vTaskSuspend(NULL); // Suspend the task if ADS1115 initialization fails again
		}
	}
}
/**
 * Restart function of SNM  app
 */
void App_AI::App_AI_Restart()
{
}
/**
 * Execute fuction of SNM app
 */
void App_AI::App_AI_Execute()
{
	if (atObject_Param.enCh1AI)
	{
		if (atObject_Param.enRawAI)
		{
			atObject_Data.ch1RawData = atService_ADS1115.ADS1115_readAI(0);
			if (atApp_AI.User_Mode == APP_USER_MODE_DEBUG)
			{
				Serial.println("CH1: AI raw data: " + String(atObject_Data.ch1RawData));
			}
		}
		if (atObject_Param.enCurAI)
		{
			atObject_Data.ch1Current = atService_ADS1115.ADS1115_readAI_Current(0);
			if (atApp_AI.User_Mode == APP_USER_MODE_DEBUG)
			{
				Serial.println("CH1: Current: " + String(atObject_Data.ch1Current, 4) + " mA");
			}
		}
	}
	if (atObject_Param.enCh2AI)
	{
		if (atObject_Param.enRawAI)
		{
			atObject_Data.ch2RawData = atService_ADS1115.ADS1115_readAI(1);
			atApp_Database.writeData("AI", "CH2: " + String(atObject_Data.ch2RawData));
			if (atApp_AI.User_Mode == APP_USER_MODE_DEBUG)
			{
				Serial.println("CH2: AI raw data: " + String(atObject_Data.ch2RawData));
			}
		}
		if (atObject_Param.enCurAI)
		{
			atObject_Data.ch2Current = atService_ADS1115.ADS1115_readAI_Current(1);
			if (atApp_AI.User_Mode == APP_USER_MODE_DEBUG)
			{
				Serial.println("CH2: Current: " + String(atObject_Data.ch2Current, 4) + " mA");
			}
		}
	}
	if (atObject_Param.enCh3AI)
	{
		if (atObject_Param.enRawAI)
		{
			atObject_Data.ch3RawData = atService_ADS1115.ADS1115_readAI(2);
			if (atApp_AI.User_Mode == APP_USER_MODE_DEBUG)
			{
				Serial.println("CH3: AI raw data: " + String(atObject_Data.ch3RawData));
			}
		}
		if (atObject_Param.enCurAI)
		{
			atObject_Data.ch3Current = atService_ADS1115.ADS1115_readAI_Current(2);
			if (atApp_AI.User_Mode == APP_USER_MODE_DEBUG)
			{
				Serial.println("CH3: Current: " + String(atObject_Data.ch3Current, 4) + " mA");
			}
		}
	}
	if (atObject_Param.enCh4AI)
	{
		if (atObject_Param.enRawAI)
		{
			atObject_Data.ch4RawData = atService_ADS1115.ADS1115_readAI(3);
			if (atApp_AI.User_Mode == APP_USER_MODE_DEBUG)
			{
				Serial.println("CH4: AI raw data: " + String(atObject_Data.ch4RawData));
			}
		}
		if (atObject_Param.enCurAI)
		{
			atObject_Data.ch4Current = atService_ADS1115.ADS1115_readAI_Current(3);
			if (atApp_AI.User_Mode == APP_USER_MODE_DEBUG)
			{
				Serial.println("CH4: Current: " + String(atObject_Data.ch4Current, 4) + " mA");
			}
		}
	}
	if (atObject_Param.enCh1AI || atObject_Param.enCh2AI || atObject_Param.enCh3AI || atObject_Param.enCh4AI)
	{
		if (atApp_AI.User_Mode == APP_USER_MODE_DEBUG)
		{
			Serial.println("--------------------------------------------------");
		}
	}
}
void App_AI::App_AI_Suspend() {}
void App_AI::App_AI_Resume() {}
void App_AI::App_AI_End() {}
void atApp_AI_Task_Func(void *parameter)
{
	while (1)
	{
		atApp_AI.Run_Application(APP_RUN_MODE_AUTO);
		vTaskDelay(atObject_Param.refreshRateAI / portTICK_PERIOD_MS);
	}
}
#endif