#ifndef _Application_atApp_Database_
#define _Application_atApp_Database_
/* _____PROJECT INCLUDES____________________________________________________ */
#include "App.h"
// #include "../services/atService_XYZ.h"
/* _____DEFINITIONS__________________________________________________________ */

/* _____GLOBAL VARIABLES_____________________________________________________ */
TaskHandle_t Task_atApp_Database;  
void atApp_Database_Task_Func(void *parameter);
///////////////////////////////////////////////Testing part//
/* _____GLOBAL FUNCTION______________________________________________________ */

/* _____CLASS DEFINITION_____________________________________________________ */

/**
 * This Application class is the application to manage the 
 */
class App_Database : public Application
{
public:
  	App_Database();
 	~App_Database();
protected:
private:
  	static void  App_Database_Pend();
	static void  App_Database_Start();
	static void  App_Database_Restart();
	static void  App_Database_Execute();
	static void  App_Database_Suspend();
	static void  App_Database_Resume();	  
	static void  App_Database_End();
} atApp_Database ;
/**
 * This function will be automaticaly called when a object is created by this class
 */
App_Database::App_Database(/* args */)
{
  	_Pend_User 	     = *App_Database_Pend;
	_Start_User 	 = *App_Database_Start;
	_Restart_User 	 = *App_Database_Restart;
	_Execute_User 	 = *App_Database_Execute;
	_Suspend_User	 = *App_Database_Suspend;
	_Resume_User	 = *App_Database_Resume;
	_End_User	     = *App_Database_End;

	// change the ID of application
	ID_Application = 1;
	// change the application name
	Name_Application = (char*)"Database Application	";
	// change the ID of SNM
}
/**
 * This function will be automaticaly called when the object of class is delete
 */
App_Database::~App_Database()
{
	
}
/**
 * Pend to start is the first task of this application it will do prerequisite condition. In the debit mode, task will send information of application to terminal to start the application.
 */
void  App_Database::App_Database_Pend()
{
    // atService_XYZ.Debug();
}
/**
 * This start function will init some critical function 
 */
void  App_Database::App_Database_Start()
{
	// init atXYZ Service in the fist running time
	// atService_XYZ.Run_Service();
}  
/**
 * Restart function of SNM  app
 */
void  App_Database::App_Database_Restart()
{

}
/**
 * Execute fuction of SNM app
 */
void  App_Database::App_Database_Execute()
{	
	// atService_XYZ.Run_Service();
    if(atApp_Database.User_Mode == APP_USER_MODE_DEBUG)
    {
		
    }   
}
void  App_Database::App_Database_Suspend(){}
void  App_Database::App_Database_Resume(){}	  
void  App_Database::App_Database_End(){}
void atApp_Database_Task_Func(void *parameter)
{
  while (1)
  {
    atApp_Database.Run_Application(APP_RUN_MODE_AUTO);
    vTaskDelay(1000/ portTICK_PERIOD_MS);
  }
}
#endif