/**
@file

*/
/*
  Application example t

  Library:: 

  This version is

  Copyright:: 2021 nguyentrinhtuan1996@gmail.com
*/

#ifndef _Application_atApp_GPS_
#define _Application_atApp_GPS_
/* _____PROJECT INCLUDES____________________________________________________ */
#include "App.h"
#include "../services/atService_EG800K.h"
/* _____DEFINITIONS__________________________________________________________ */

/* _____GLOBAL VARIABLES_____________________________________________________ */
TaskHandle_t Task_atApp_GPS;  
void atApp_GPS_Task_Func(void *parameter);
///////////////////////////////////////////////Testing part//
/* _____GLOBAL FUNCTION______________________________________________________ */

/* _____CLASS DEFINITION_____________________________________________________ */

/**
 * This Application class is the application to manage the 
 */
class App_GPS : public Application
{
public:
  	App_GPS();
 	~App_GPS();
protected:
private:
  	static void  App_GPS_Pend();
	static void  App_GPS_Start();
	static void  App_GPS_Restart();
	static void  App_GPS_Execute();
	static void  App_GPS_Suspend();
	static void  App_GPS_Resume();	  
	static void  App_GPS_End();
} atApp_GPS ;
/**
 * This function will be automaticaly called when a object is created by this class
 */
App_GPS::App_GPS(/* args */)
{
  	_Pend_User 	     = *App_GPS_Pend;
	_Start_User 	 = *App_GPS_Start;
	_Restart_User 	 = *App_GPS_Restart;
	_Execute_User 	 = *App_GPS_Execute;
	_Suspend_User	 = *App_GPS_Suspend;
	_Resume_User	 = *App_GPS_Resume;
	_End_User	     = *App_GPS_End;

	// change the ID of application
	ID_Application = 1;
	// change the application name
	Name_Application = (char*)"GPS Application	";
	// change the ID of SNM
}
/**
 * This function will be automaticaly called when the object of class is delete
 */
App_GPS::~App_GPS()
{
	
}
/**
 * Pend to start is the first task of this application it will do prerequisite condition. In the debit mode, task will send information of application to terminal to start the application.
 */
void  App_GPS::App_GPS_Pend()
{
    // atService_EG800K.Debug();
}
/**
 * This start function will init some critical function 
 */
void  App_GPS::App_GPS_Start()
{
	// init atEG800K Service in the fist running time
	// atService_EG800K.Run_Service();
}  
/**
 * Restart function of SNM  app
 */
void  App_GPS::App_GPS_Restart()
{

}
/**
 * Execute fuction of SNM app
 */
void  App_GPS::App_GPS_Execute()
{	
	// atService_EG800K.Run_Service();
    if(atApp_GPS.User_Mode == APP_USER_MODE_DEBUG)
    {
		
    }   
}
void  App_GPS::App_GPS_Suspend(){}
void  App_GPS::App_GPS_Resume(){}	  
void  App_GPS::App_GPS_End(){}
void atApp_GPS_Task_Func(void *parameter)
{
  while (1)
  {
    atApp_GPS.Run_Application(APP_RUN_MODE_AUTO);
    vTaskDelay(1000/ portTICK_PERIOD_MS);
  }
}
#endif