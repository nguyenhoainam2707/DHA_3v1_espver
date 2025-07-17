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
// 	if (atObject_Param.enMQTTPUB)
// 	{
// 		xTaskCreatePinnedToCore(atApp_MQTT_PUB_Task_Func, "atApp_MQTT_PUB_Application", 2048, NULL, 1, &Task_atApp_MQTT_PUB, 1);
// 	}
// 	if (atObject_Param.enMQTTSUB)
// 	{
// 		xTaskCreatePinnedToCore(atApp_MQTT_SUB_Task_Func, "atApp_MQTT_SUB_Application", 2048, NULL, 1, &Task_atApp_MQTT_SUB, 1);
// 	}
// 	// xTaskCreatePinnedToCore(atApp_AP_Task_Func,       "atApp_AP_Application",       10000,  NULL, 1, &Task_atApp_AP,        0);
// 	if (atObject_Param.enCh1AI || atObject_Param.enCh2AI || atObject_Param.enCh3AI || atObject_Param.enCh4AI)
// 	{
// 		xTaskCreatePinnedToCore(atApp_AI_Task_Func, "atApp_AI_Application", 2048, NULL, 1, &Task_atApp_AI, 1);
// 	}
// 	if (atObject_Param.enCh1DI || atObject_Param.enCh2DI || atObject_Param.enCh3DI || atObject_Param.enCh4DI)
// 	{
// 		xTaskCreatePinnedToCore(atApp_DI_Task_Func, "atApp_DI_Application", 2048, NULL, 1, &Task_atApp_DI, 1);
// 	}
// 	if (atObject_Param.enLCD)
// 	{
// 		xTaskCreatePinnedToCore(atApp_LCD_Task_Func, "atApp_LCD_Application", 2048, NULL, 1, &Task_atApp_LCD, 1);
// 	}
// 	if (atObject_Param.enMB1)
// 	{
// 		xTaskCreatePinnedToCore(atApp_MB1_Task_Func, "atApp_MB1_Application", 2048, NULL, 1, &Task_atApp_MB1, 1);
// 	}
// 	if (atObject_Param.enMB2)
// 	{
// 	xTaskCreatePinnedToCore(atApp_MB2_Task_Func, "atApp_MB2_Application", 2048, NULL, 1, &Task_atApp_MB2, 1);
// 	}
// 	if (atObject_Param.enCh1PWM || atObject_Param.enCh2PWM || atObject_Param.enCh3PWM || atObject_Param.enCh4PWM)
// 	{
// 		xTaskCreatePinnedToCore(atApp_PWM_Task_Func, "atApp_PWM_Application", 2048, NULL, 1, &Task_atApp_PWM, 1);
// 	}
// 	xTaskCreatePinnedToCore(atApp_LED_Task_Func, "atApp_LED_Application", 2048, NULL, 1, &Task_atApp_LED, 1);
	// xTaskCreatePinnedToCore(atApp_GPS_Task_Func,      "atApp_GPS_Application",      2048,   NULL, 1, &Task_atApp_GPS,       1);
	// xTaskCreatePinnedToCore(atApp_FTP_Task_Func,      "atApp_FTP_Application",      2048,   NULL, 1, &Task_atApp_FTP,       1);
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
	// atService_XYZ.Run_Service();
	// if(atApp_CP.User_Mode == APP_USER_MODE_DEBUG)
	// {

	// }
}
void App_CP::App_CP_Suspend() {}
void App_CP::App_CP_Resume() {}
void App_CP::App_CP_End() {}
void atApp_CP_Task_Func(void *parameter)
{
	while (1)
	{
		atApp_CP.Run_Application(APP_RUN_MODE_AUTO);
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}
#endif