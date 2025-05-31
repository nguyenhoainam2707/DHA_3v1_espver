/**
@file

*/
/*
  Application example t

  Library::

  This version is

  Copyright:: 2021 nguyentrinhtuan1996@gmail.com
*/

#ifndef _Application_atApp_LED_
#define _Application_atApp_LED_
/* _____PROJECT INCLUDES____________________________________________________ */
#include "App.h"
#include "../services/atService_LED.h"
/* _____DEFINITIONS__________________________________________________________ */
#define EG800K_STATE_LED_PIN 6
#define PUBLISH_LED_PIN 5
#define SUBSCRIBE_LED_PIN 4

struct LED_State
{
	bool state = false; // true for ON, false for OFF
	uint32_t startTime = 0;
	uint16_t duration = 500; // Duration for blinking in milliseconds
};
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
	static void toggleLED(uint8_t ledPin, LED_State &ledState);
	static LED_State egStateLED, publishLED, subscribeLED;
protected:
private:
	static void App_LED_Pend();
	static void App_LED_Start();
	static void App_LED_Restart();
	static void App_LED_Execute();
	static void App_LED_Suspend();
	static void App_LED_Resume();
	static void App_LED_End();
} atApp_LED;
/**
 * This function will be automaticaly called when a object is created by this class
 */
App_LED::App_LED(/* args */)
{
	_Pend_User = *App_LED_Pend;
	_Start_User = *App_LED_Start;
	_Restart_User = *App_LED_Restart;
	_Execute_User = *App_LED_Execute;
	_Suspend_User = *App_LED_Suspend;
	_Resume_User = *App_LED_Resume;
	_End_User = *App_LED_End;

	// change the ID of application
	ID_Application = 1;
	// change the application name
	Name_Application = (char *)"LED Application	";
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
void App_LED::App_LED_Pend()
{
	// atService_LED.Debug();
}
/**
 * This start function will init some critical function
 */
void App_LED::App_LED_Start()
{
	// init atLED Service in the fist running time
	// atService_LED.Run_Service();
	pinMode(EG800K_STATE_LED_PIN, OUTPUT);   // Set pin for LED state
	pinMode(PUBLISH_LED_PIN, OUTPUT);	   // Set pin for publish LED state
	pinMode(SUBSCRIBE_LED_PIN, OUTPUT);	   // Set pin for subscribe LED state
	digitalWrite(EG800K_STATE_LED_PIN, LOW); // Turn off LED state pin
	digitalWrite(PUBLISH_LED_PIN, LOW);	   // Turn off publish LED pin
	digitalWrite(SUBSCRIBE_LED_PIN, LOW);  // Turn off subscribe LED pin
}
/**
 * Restart function of SNM  app
 */
void App_LED::App_LED_Restart()
{
}
/**
 * Execute fuction of SNM app
 */
void App_LED::App_LED_Execute()
{
	switch (atService_EG800K.EG800K_State)
	{
	case EG800K_STATE_INIT:
		toggleLED(EG800K_STATE_LED_PIN, egStateLED); // Toggle LED for EG800K state
		break;
	case EG800K_STATE_NORMAL:
		break;
	case EG800K_STATE_ERROR:
		// Blink the LED to indicate an error
		blinkLED(EG800K_STATE_LED_PIN, 1000); // Blink for 1 second
		break;
	default:
		break;
	}
	if (atApp_LED.User_Mode == APP_USER_MODE_DEBUG)
	{
	}
}
void App_LED::App_LED_Suspend() {}
void App_LED::App_LED_Resume() {}
void App_LED::App_LED_End() {}
void App_LED::toggleLED(uint8_t ledPin, LED_State &ledState)
{
	uint32_t currentTime = millis();
	// Check if the LED is currently on and if the duration has passed
	if (currentTime - ledState.startTime >= ledState.duration)
	{
		if (ledState.state)
		{
			digitalWrite(ledPin, LOW); // Turn off the LED
			ledState.state = false;	   // Update state
		}
		else
		{
			digitalWrite(ledPin, HIGH); // Turn on the LED
			ledState.state = true;		// Update state
		}
		ledState.startTime = currentTime; // Reset start time
	}
}
void atApp_LED_Task_Func(void *parameter)
{
	while (1)
	{
		atApp_LED.Run_Application(APP_RUN_MODE_AUTO);
		vTaskDelay(100 / portTICK_PERIOD_MS);
	}
}
#endif