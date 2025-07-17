#ifndef _Application_atApp_MQTT_PUB_
#define _Application_atApp_MQTT_PUB_
/* _____PROJECT INCLUDES____________________________________________________ */
#include "App.h"
#include "../services/atService_EG800K.h"
#include "../src/obj/atObj_Param.h"
#include "../src/obj/atObj_Data.h"
#include "../src/apps/atApp_Database.h"
/* _____DEFINITIONS__________________________________________________________ */
#define MQTT_PUB_TOPIC "esp32s3/testTopicDHA" // MQTT topic for publishing water level data
/* _____GLOBAL VARIABLES_____________________________________________________ */
TaskHandle_t Task_atApp_MQTT_PUB;
void atApp_MQTT_PUB_Task_Func(void *parameter);
///////////////////////////////////////////////Testing part//
/* _____GLOBAL FUNCTION______________________________________________________ */

/* _____CLASS DEFINITION_____________________________________________________ */

/**
 * This Application class is the application to manage the
 */
class App_MQTT_PUB : public Application
{
public:
	App_MQTT_PUB();
	~App_MQTT_PUB();

protected:
private:
	static void App_MQTT_PUB_Pend();
	static void App_MQTT_PUB_Start();
	static void App_MQTT_PUB_Restart();
	static void App_MQTT_PUB_Execute();
	static void App_MQTT_PUB_Suspend();
	static void App_MQTT_PUB_Resume();
	static void App_MQTT_PUB_End();
} atApp_MQTT_PUB;
/**
 * This function will be automaticaly called when a object is created by this class
 */
App_MQTT_PUB::App_MQTT_PUB(/* args */)
{
	_Pend_User = *App_MQTT_PUB_Pend;
	_Start_User = *App_MQTT_PUB_Start;
	_Restart_User = *App_MQTT_PUB_Restart;
	_Execute_User = *App_MQTT_PUB_Execute;
	_Suspend_User = *App_MQTT_PUB_Suspend;
	_Resume_User = *App_MQTT_PUB_Resume;
	_End_User = *App_MQTT_PUB_End;

	// change the ID of application
	ID_Application = 2;
	// change the application name
	Name_Application = (char *)"MQTT_PUB Application	";
	// change the ID of SNM
}
/**
 * This function will be automaticaly called when the object of class is delete
 */
App_MQTT_PUB::~App_MQTT_PUB()
{
}
/**
 * Pend to start is the first task of this application it will do prerequisite condition. In the debit mode, task will send information of application to terminal to start the application.
 */
void App_MQTT_PUB::App_MQTT_PUB_Pend()
{
	// atService_EG800K.Debug();
}
/**
 * This start function will init some critical function
 */
void App_MQTT_PUB::App_MQTT_PUB_Start()
{
	// init atEG800K Service in the fist running time
	atService_EG800K.Run_Service();
	Service_EG800K::configEG800K();
	Service_EG800K::configMQTT();
}
/**
 * Restart function of SNM  app
 */
void App_MQTT_PUB::App_MQTT_PUB_Restart()
{
}
/**
 * Execute fuction of SNM app
 */
void App_MQTT_PUB::App_MQTT_PUB_Execute()
{
	String payload = "{";
	if (atObject_Param.enCh1AI)
	{
		if (atObject_Param.enRawAI)
		{
			payload += "\"AI1 Raw Data\":" + String(atObject_Data.ch1RawData) + ",";
		}
		// if (atObject_Param.enCurAI)
		// {
		// 	payload += "\"AI1 Current\":" + String(atObject_Data.ch1Current, 4) + ",";
		// }
	}
	if (atObject_Param.enCh2AI)
	{
		if (atObject_Param.enRawAI)
		{
			payload += "\"AI2 Raw Data\":" + String(atObject_Data.ch2RawData) + ",";
		}
		// if (atObject_Param.enCurAI)
		// {
		// 	payload += "\"AI2 Current\":" + String(atObject_Data.ch2Current, 4) + ",";
		// }
	}
	if (atObject_Param.enCh3AI)
	{
		if (atObject_Param.enRawAI)
		{
			payload += "\"AI3 Raw Data\":" + String(atObject_Data.ch3RawData) + ",";
		}
		// if (atObject_Param.enCurAI)
		// {
		// 	payload += "\"AI3 Current\":" + String(atObject_Data.ch3Current, 4) + ",";
		// }
	}
	if (atObject_Param.enCh4AI)
	{
		if (atObject_Param.enRawAI)
		{
			payload += "\"AI4 Raw Data\":" + String(atObject_Data.ch4RawData) + ",";
		}
		// if (atObject_Param.enCurAI)
		// {
		// 	payload += "\"AI4 Current\":" + String(atObject_Data.ch4Current, 4) + ",";
		// }
	}
	// if (atObject_Param.enMB1)
	// {
	// 	payload += "\"" + atObject_Param.sensorNameMB1 + "\":" + String(atObject_Data.rs485Ch1) + ",";
	// }
	// if (atObject_Param.enMB2)
	// {
	// 	payload += "\"" + atObject_Param.sensorNameMB2 + "\":" + String(atObject_Data.rs485Ch2) + ",";
	// }
	// if (atObject_Param.enCh1DI)
	// {
	// 	payload += "\"DI1:\":" + String(atObject_Data.ch1DI) + ",";
	// }
	// if (atObject_Param.enCh2DI)
	// {
	// 	payload += "\"DI2:\":" + String(atObject_Data.ch2DI) + ",";
	// }
	// if (atObject_Param.enCh3DI)
	// {
	// 	payload += "\"DI3:\":" + String(atObject_Data.ch3DI) + ",";
	// }
	// if (atObject_Param.enCh4DI)
	// {
	// 	payload += "\"DI4:\":" + String(atObject_Data.ch4DI) + ",";
	// }
	// Remove the last comma if it exists
	if (payload.endsWith(","))
	{
		payload.remove(payload.length() - 1);
		payload += "}";
	}
	// payload += "\"" + atObject_Param.sensorName + "\":" + String(atObject_Data.waterLevel) + "}";
	Service_EG800K::publishMQTTData(payload, MQTT_PUB_TOPIC);
}
void App_MQTT_PUB::App_MQTT_PUB_Suspend() {}
void App_MQTT_PUB::App_MQTT_PUB_Resume() {}
void App_MQTT_PUB::App_MQTT_PUB_End() {}
void atApp_MQTT_PUB_Task_Func(void *parameter)
{
	while (1)
	{
		atApp_MQTT_PUB.Run_Application(APP_RUN_MODE_AUTO);
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}
#endif