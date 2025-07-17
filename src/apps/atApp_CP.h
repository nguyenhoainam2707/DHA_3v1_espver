#ifndef _Application_atApp_CP_
#define _Application_atApp_CP_
/* _____PROJECT INCLUDES____________________________________________________ */
#include "App.h"
#include "../src/obj/atObj_Param.h"
#include "../src/obj/atObj_Data.h"
#include "../src/apps/atApp_Database.h"
#include "../src/apps/atApp_MQTT_PUB.h"
#include "../src/apps/atApp_MQTT_SUB.h"
#include "../src/apps/atApp_AI.h"
#include "../src/apps/atApp_AP.h"
#include "../src/apps/atApp_DI.h"
#include "../src/apps/atApp_LED.h"
#include "../src/apps/atApp_LCD.h"
#include "../src/apps/atApp_MB1.h"
#include "../src/apps/atApp_MB2.h"
#include "../src/apps/atApp_PWM.h"
/* _____DEFINITIONS__________________________________________________________ */
#define BUTTON_PIN 41
/* _____GLOBAL VARIABLES_____________________________________________________ */
TaskHandle_t Task_atApp_CP;
void atApp_CP_Task_Func(void *parameter);
///////////////////////////////////////////////Testing part//
/* _____GLOBAL FUNCTION______________________________________________________ */

/* _____CLASS DEFINITION_____________________________________________________ */

/**
 * This Application class is the application to manage the
 */
class App_CP : public Application
{
public:
	App_CP();
	~App_CP();

	const TickType_t debounceDelay = pdMS_TO_TICKS(50);	  // Thời gian debounce
	const TickType_t holdThreshold = pdMS_TO_TICKS(5000); // 5 giây
	TickType_t pressStartTime = 0;
	bool buttonPressed = false;

protected:
private:
	static void App_CP_Pend();
	static void App_CP_Start();
	static void App_CP_Restart();
	static void App_CP_Execute();
	static void App_CP_Suspend();
	static void App_CP_Resume();
	static void App_CP_End();
} atApp_CP;
/**
 * This function will be automaticaly called when a object is created by this class
 */
App_CP::App_CP(/* args */)
{
	_Pend_User = *App_CP_Pend;
	_Start_User = *App_CP_Start;
	_Restart_User = *App_CP_Restart;
	_Execute_User = *App_CP_Execute;
	_Suspend_User = *App_CP_Suspend;
	_Resume_User = *App_CP_Resume;
	_End_User = *App_CP_End;

	// change the ID of application
	ID_Application = 1;
	// change the application name
	Name_Application = (char *)"CP Application	";
	// change the ID of SNM
}
/**
 * This function will be automaticaly called when the object of class is delete
 */
App_CP::~App_CP()
{
}
/**
 * Pend to start is the first task of this application it will do prerequisite condition. In the debit mode, task will send information of application to terminal to start the application.
 */
void App_CP::App_CP_Pend()
{
	// atService_XYZ.Debug();
}
/**
 * This start function will init some critical function
 */
void App_CP::App_CP_Start()
{
	pinMode(BUTTON_PIN, INPUT_PULLUP);
}
/**
 * Restart function of SNM  app
 */
void App_CP::App_CP_Restart()
{
}
/**
 * Execute fuction of SNM app
 */
void App_CP::App_CP_Execute()
{
	if (digitalRead(BUTTON_PIN) == LOW)
	{ // Nút được nhấn (kích xuống GND)
		if (!atApp_CP.buttonPressed)
		{
			// Ghi nhận thời điểm bắt đầu nhấn
			atApp_CP.pressStartTime = xTaskGetTickCount();
			atApp_CP.buttonPressed = true;
		}
		// Kiểm tra thời gian giữ nút
		if ((xTaskGetTickCount() - atApp_CP.pressStartTime) >= atApp_CP.holdThreshold)
		{
			if (atApp_CP.User_Mode == APP_USER_MODE_DEBUG)
			{
				Serial.println("Button pressed for 5 seconds, switching mode...");
			}

			// Chờ đến khi nút được thả ra
			while (digitalRead(BUTTON_PIN) == LOW)
			{
				vTaskDelay(pdMS_TO_TICKS(100));
			}
			atApp_CP.buttonPressed = false;
		}
	}
	else
{
		atApp_CP.buttonPressed = false;
	}
	vTaskDelay(atApp_CP.debounceDelay); // Chờ debounce
}
void App_CP::App_CP_Suspend() {}
void App_CP::App_CP_Resume() {}
void App_CP::App_CP_End() {}
void atApp_CP_Task_Func(void *parameter)
{
	while (1)
	{
		atApp_CP.Run_Application(APP_RUN_MODE_AUTO);
		// vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}
#endif