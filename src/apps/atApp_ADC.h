/**
@file

*/
/*
  Application example t

  Library::

  This version is

  Copyright:: 2021 nguyentrinhtuan1996@gmail.com
*/

#ifndef _Application_atApp_ADC_
#define _Application_atApp_ADC_
/* _____PROJECT INCLUDES____________________________________________________ */
#include "App.h"
#include "../services/atService_ADS1115.h"
#include "../src/obj/atObj_Param.h"
#include "../src/obj/atObj_Value.h"
/* _____DEFINITIONS__________________________________________________________ */

/* _____GLOBAL VARIABLES_____________________________________________________ */
TaskHandle_t Task_atApp_ADC;
void atApp_ADC_Task_Func(void *parameter);
///////////////////////////////////////////////Testing part//
/* _____GLOBAL FUNCTION______________________________________________________ */

/* _____CLASS DEFINITION_____________________________________________________ */

/**
 * This Application class is the application to manage the
 */
class App_ADC : public Application
{
public:
	App_ADC();
	~App_ADC();

	static bool ads1115InitOke; // this variable will be set to true when the ADS1115 is initialized successfully

protected:
private:
	static void App_ADC_Pend();
	static void App_ADC_Start();
	static void App_ADC_Restart();
	static void App_ADC_Execute();
	static void App_ADC_Suspend();
	static void App_ADC_Resume();
	static void App_ADC_End();
} atApp_ADC;

bool App_ADC::ads1115InitOke = false; // Initialize the ADS1115 status to false
/**
 * This function will be automaticaly called when a object is created by this class
 */
App_ADC::App_ADC(/* args */)
{
	_Pend_User = *App_ADC_Pend;
	_Start_User = *App_ADC_Start;
	_Restart_User = *App_ADC_Restart;
	_Execute_User = *App_ADC_Execute;
	_Suspend_User = *App_ADC_Suspend;
	_Resume_User = *App_ADC_Resume;
	_End_User = *App_ADC_End;

	// change the ID of application
	ID_Application = 1;
	// change the application name
	Name_Application = (char *)"ADC Application	";
	// change the ID of SNM
}
/**
 * This function will be automaticaly called when the object of class is delete
 */
App_ADC::~App_ADC()
{
}
/**
 * Pend to start is the first task of this application it will do prerequisite condition. In the debit mode, task will send information of application to terminal to start the application.
 */
void App_ADC::App_ADC_Pend()
{
	// atService_ADS1115.Debug();
}
/**
 * This start function will init some critical function
 */
void App_ADC::App_ADC_Start()
{
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
	ads1115InitOke = Service_ADS1115::ADS1115_Init(GAIN_TWOTHIRDS, RATE_ADS1115_8SPS);
	if (ads1115InitOke)
	{
		if (atApp_ADC.User_Mode == APP_USER_MODE_DEBUG)
		{
			Serial.println("ADS1115 init success!");
		}
	}
	else
	{
		if (atApp_ADC.User_Mode == APP_USER_MODE_DEBUG)
		{
			Serial.println("ADS1115 init failed!");
		}
		for (int i = 0; i < 5; i++)
		{
			vTaskDelay(2000 / portTICK_PERIOD_MS); // Delay to allow the user to see the error message
			ads1115InitOke = Service_ADS1115::ADS1115_Init(GAIN_TWOTHIRDS, RATE_ADS1115_8SPS);
			if (atApp_ADC.User_Mode == APP_USER_MODE_DEBUG)
			{
				Serial.println("Retry ADS1115 init...");
			}
			if (!ads1115InitOke)
			{
				Serial.println("ADS1115 init failed!");
			}
			else
			{
				if (atApp_ADC.User_Mode == APP_USER_MODE_DEBUG)
				{
					Serial.println("ADS1115 reinitialize success!");
				}
				break; // Exit the retry loop if initialization is successful
			}
		}
		if (!ads1115InitOke)
		{
			if (atApp_ADC.User_Mode == APP_USER_MODE_DEBUG)
			{
				Serial.println("Suspending ADC task due to repeated initialization failure.");
			}
			vTaskSuspend(NULL); // Suspend the task if ADS1115 initialization fails again
		}
	}
}
/**
 * Restart function of SNM  app
 */
void App_ADC::App_ADC_Restart()
{
}
/**
 * Execute fuction of SNM app
 */
void App_ADC::App_ADC_Execute()
{
	if (Object_Param::enCh1ADC)
	{
		if (Object_Param::enRawADC)
		{
			Object_Value::ch1RawValue = atService_ADS1115.ADS1115_readADC(0);
			if (atApp_ADC.User_Mode == APP_USER_MODE_DEBUG)
			{
				Serial.println("CH1: ADC raw value: " + String(Object_Value::ch1RawValue));
			}
		}
		if (Object_Param::enVolADC)
		{
			Object_Value::ch1Voltage = atService_ADS1115.ADS1115_readADC_Voltage(0);
			if (atApp_ADC.User_Mode == APP_USER_MODE_DEBUG)
			{
				Serial.println("CH1: Voltage: " + String(Object_Value::ch1Voltage, 4) + " V");
			}
		}
	}
	if (Object_Param::enCh2ADC)
	{
		if (Object_Param::enRawADC)
		{
			Object_Value::ch2RawValue = atService_ADS1115.ADS1115_readADC(1);
			if (atApp_ADC.User_Mode == APP_USER_MODE_DEBUG)
			{
				Serial.println("CH2: ADC raw value: " + String(Object_Value::ch2RawValue));
			}
		}
		if (Object_Param::enVolADC)
		{
			Object_Value::ch2Voltage = atService_ADS1115.ADS1115_readADC_Voltage(1);
			if (atApp_ADC.User_Mode == APP_USER_MODE_DEBUG)
			{
				Serial.println("CH2: Voltage: " + String(Object_Value::ch2Voltage, 4) + " V");
			}
		}
	}
	if (Object_Param::enCh3ADC)
	{
		if (Object_Param::enRawADC)
		{
			Object_Value::ch3RawValue = atService_ADS1115.ADS1115_readADC(2);
			if (atApp_ADC.User_Mode == APP_USER_MODE_DEBUG)
			{
				Serial.println("CH3: ADC raw value: " + String(Object_Value::ch3RawValue));
			}
		}
		if (Object_Param::enVolADC)
		{
			Object_Value::ch3Voltage = atService_ADS1115.ADS1115_readADC_Voltage(2);
			if (atApp_ADC.User_Mode == APP_USER_MODE_DEBUG)
			{
				Serial.println("CH3: Voltage: " + String(Object_Value::ch3Voltage, 4) + " V");
			}
		}
	}
	if (Object_Param::enCh4ADC)
	{
		if (Object_Param::enRawADC)
		{
			Object_Value::ch4RawValue = atService_ADS1115.ADS1115_readADC(3);
			if (atApp_ADC.User_Mode == APP_USER_MODE_DEBUG)
			{
				Serial.println("CH4: ADC raw value: " + String(Object_Value::ch4RawValue));
			}
		}
		if (Object_Param::enVolADC)
		{
			Object_Value::ch4Voltage = atService_ADS1115.ADS1115_readADC_Voltage(3);
			if (atApp_ADC.User_Mode == APP_USER_MODE_DEBUG)
			{
				Serial.println("CH4: Voltage: " + String(Object_Value::ch4Voltage, 4) + " V");
			}
		}
	}
}
void App_ADC::App_ADC_Suspend() {}
void App_ADC::App_ADC_Resume() {}
void App_ADC::App_ADC_End() {}
void atApp_ADC_Task_Func(void *parameter)
{
	while (1)
	{
		atApp_ADC.Run_Application(APP_RUN_MODE_AUTO);
		vTaskDelay(300 / portTICK_PERIOD_MS);
	}
}
#endif