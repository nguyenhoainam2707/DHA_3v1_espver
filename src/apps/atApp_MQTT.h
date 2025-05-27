/**
@file

*/
/*
  Application example t

  Library::

  This version is

  Copyright:: 2021 nguyentrinhtuan1996@gmail.com
*/

#ifndef _Application_atApp_MQTT_
#define _Application_atApp_MQTT_
/* _____PROJECT INCLUDES____________________________________________________ */
#include "App.h"
#include "../services/atService_EG800K.h"
#include "../src/obj/atObj_ADC.h"
/* _____DEFINITIONS__________________________________________________________ */

/* _____GLOBAL VARIABLES_____________________________________________________ */
TaskHandle_t Task_atApp_MQTT;
void atApp_MQTT_Task_Func(void *parameter);
///////////////////////////////////////////////Testing part//
/* _____GLOBAL FUNCTION______________________________________________________ */

/* _____CLASS DEFINITION_____________________________________________________ */

/**
 * This Application class is the application to manage the
 */
class App_MQTT : public Application
{
public:
	App_MQTT();
	~App_MQTT();

protected:
private:
	static void App_MQTT_Pend();
	static void App_MQTT_Start();
	static void App_MQTT_Restart();
	static void App_MQTT_Execute();
	static void App_MQTT_Suspend();
	static void App_MQTT_Resume();
	static void App_MQTT_End();
} atApp_MQTT;
/**
 * This function will be automaticaly called when a object is created by this class
 */
App_MQTT::App_MQTT(/* args */)
{
	_Pend_User = *App_MQTT_Pend;
	_Start_User = *App_MQTT_Start;
	_Restart_User = *App_MQTT_Restart;
	_Execute_User = *App_MQTT_Execute;
	_Suspend_User = *App_MQTT_Suspend;
	_Resume_User = *App_MQTT_Resume;
	_End_User = *App_MQTT_End;

	// change the ID of application
	ID_Application = 2;
	// change the application name
	Name_Application = (char *)"MQTT Application	";
	// change the ID of SNM
}
/**
 * This function will be automaticaly called when the object of class is delete
 */
App_MQTT::~App_MQTT()
{
}
/**
 * Pend to start is the first task of this application it will do prerequisite condition. In the debit mode, task will send information of application to terminal to start the application.
 */
void App_MQTT::App_MQTT_Pend()
{
	// atService_EG800K.Debug();
}
/**
 * This start function will init some critical function
 */
void App_MQTT::App_MQTT_Start()
{
	// init atEG800K Service in the fist running time
	atService_EG800K.Run_Service();
	Service_EG800K::configEG800K();
	Service_EG800K::configMQTT();
	Service_EG800K::subscribeMQTTTopic("esp32s3/content");
}
/**
 * Restart function of SNM  app
 */
void App_MQTT::App_MQTT_Restart()
{
}
/**
 * Execute fuction of SNM app
 */
void App_MQTT::App_MQTT_Execute()
{
	String payload = "{";
	payload += "\"ADC_0 Raw Value\":" + String(Object_ADC::adcRawValue) + ",";
	payload += "\"ADC_0 Voltage\":" + String(Object_ADC::voltage, 4) + "}";
	Service_EG800K::publishMQTTData(payload);
	// if (atApp_MQTT.User_Mode == APP_USER_MODE_DEBUG)
	// {
	// }
	Service_EG800K::handleMQTTMessage();
}
void App_MQTT::App_MQTT_Suspend() {}
void App_MQTT::App_MQTT_Resume() {}
void App_MQTT::App_MQTT_End() {}
void atApp_MQTT_Task_Func(void *parameter)
{
	while (1)
	{
		atApp_MQTT.Run_Application(APP_RUN_MODE_AUTO);
		vTaskDelay(300 / portTICK_PERIOD_MS);
	}
}
#endif