#ifndef _Application_atApp_LCD_
#define _Application_atApp_LCD_
/* _____PROJECT INCLUDES____________________________________________________ */
#include "App.h"
#include "../services/atService_LCD1602.h"
#include "../src/obj/atObj_Param.h"
#include "../src/obj/atObj_Data.h"
/* _____DEFINITIONS__________________________________________________________ */

/* _____GLOBAL VARIABLES_____________________________________________________ */
TaskHandle_t Task_atApp_LCD;  
void atApp_LCD_Task_Func(void *parameter);
///////////////////////////////////////////////Testing part//
/* _____GLOBAL FUNCTION______________________________________________________ */

/* _____CLASS DEFINITION_____________________________________________________ */

/**
 * This Application class is the application to manage the 
 */
class App_LCD : public Application
{
public:
  	App_LCD();
 	~App_LCD();
protected:
private:
  	static void  App_LCD_Pend();
	static void  App_LCD_Start();
	static void  App_LCD_Restart();
	static void  App_LCD_Execute();
	static void  App_LCD_Suspend();
	static void  App_LCD_Resume();	  
	static void  App_LCD_End();
} atApp_LCD ;
/**
 * This function will be automaticaly called when a object is created by this class
 */
App_LCD::App_LCD(/* args */)
{
  	_Pend_User 	     = *App_LCD_Pend;
	_Start_User 	 = *App_LCD_Start;
	_Restart_User 	 = *App_LCD_Restart;
	_Execute_User 	 = *App_LCD_Execute;
	_Suspend_User	 = *App_LCD_Suspend;
	_Resume_User	 = *App_LCD_Resume;
	_End_User	     = *App_LCD_End;

	// change the ID of application
	ID_Application = 1;
	// change the application name
	Name_Application = (char*)"LCD Application	";
	// change the ID of SNM
}
/**
 * This function will be automaticaly called when the object of class is delete
 */
App_LCD::~App_LCD()
{
	
}
/**
 * Pend to start is the first task of this application it will do prerequisite condition. In the debit mode, task will send information of application to terminal to start the application.
 */
void  App_LCD::App_LCD_Pend()
{
    // atService_LCD1602.Debug();
}
/**
 * This start function will init some critical function 
 */
void  App_LCD::App_LCD_Start()
{
	// init atLCD1602 Service in the fist running time
	// atService_LCD1602.Run_Service();
}  
/**
 * Restart function of SNM  app
 */
void  App_LCD::App_LCD_Restart()
{

}
/**
 * Execute fuction of SNM app
 */
void  App_LCD::App_LCD_Execute()
{	
	// atService_LCD1602.Run_Service();
    if(atApp_LCD.User_Mode == APP_USER_MODE_DEBUG)
    {
		
    }   
}
void  App_LCD::App_LCD_Suspend(){}
void  App_LCD::App_LCD_Resume(){}	  
void  App_LCD::App_LCD_End(){}
void atApp_LCD_Task_Func(void *parameter)
{
  while (1)
  {
    atApp_LCD.Run_Application(APP_RUN_MODE_AUTO);
    vTaskDelay(1000/ portTICK_PERIOD_MS);
  }
}
#endif