#ifndef _Application_atApp_AP_
#define _Application_atApp_AP_
/* _____PROJECT INCLUDES____________________________________________________ */
#include "App.h"
#include "../services/atService_XYZ.h"
/* _____DEFINITIONS__________________________________________________________ */

/* _____GLOBAL VARIABLES_____________________________________________________ */
TaskHandle_t Task_atApp_AP;  
void atApp_AP_Task_Func(void *parameter);
///////////////////////////////////////////////Testing part//
/* _____GLOBAL FUNCTION______________________________________________________ */

/* _____CLASS DEFINITION_____________________________________________________ */

/**
 * This Application class is the application to manage the 
 */
class App_AP : public Application
{
public:
  	App_AP();
 	~App_AP();
protected:
private:
  	static void  App_AP_Pend();
	static void  App_AP_Start();
	static void  App_AP_Restart();
	static void  App_AP_Execute();
	static void  App_AP_Suspend();
	static void  App_AP_Resume();	  
	static void  App_AP_End();
} atApp_AP ;
/**
 * This function will be automaticaly called when a object is created by this class
 */
App_AP::App_AP(/* args */)
{
  	_Pend_User 	     = *App_AP_Pend;
	_Start_User 	 = *App_AP_Start;
	_Restart_User 	 = *App_AP_Restart;
	_Execute_User 	 = *App_AP_Execute;
	_Suspend_User	 = *App_AP_Suspend;
	_Resume_User	 = *App_AP_Resume;
	_End_User	     = *App_AP_End;

	// change the ID of application
	ID_Application = 1;
	// change the application name
	Name_Application = (char*)"AP Application	";
	// change the ID of SNM
}
/**
 * This function will be automaticaly called when the object of class is delete
 */
App_AP::~App_AP()
{
	
}
/**
 * Pend to start is the first task of this application it will do prerequisite condition. In the debit mode, task will send information of application to terminal to start the application.
 */
void  App_AP::App_AP_Pend()
{
    // atService_XYZ.Debug();
}
/**
 * This start function will init some critical function 
 */
void  App_AP::App_AP_Start()
{
	// init atXYZ Service in the fist running time
	// atService_XYZ.Run_Service();
}  
/**
 * Restart function of SNM  app
 */
void  App_AP::App_AP_Restart()
{

}
/**
 * Execute fuction of SNM app
 */
void  App_AP::App_AP_Execute()
{	
	// atService_XYZ.Run_Service();
    if(atApp_AP.User_Mode == APP_USER_MODE_DEBUG)
    {
		
    }   
}
void  App_AP::App_AP_Suspend(){}
void  App_AP::App_AP_Resume(){}	  
void  App_AP::App_AP_End(){}
void atApp_AP_Task_Func(void *parameter)
{
  while (1)
  {
    atApp_AP.Run_Application(APP_RUN_MODE_AUTO);
    vTaskDelay(1000/ portTICK_PERIOD_MS);
  }
}
#endif