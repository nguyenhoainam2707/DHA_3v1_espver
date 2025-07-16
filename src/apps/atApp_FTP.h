#ifndef _Application_atApp_FTP_
#define _Application_atApp_FTP_
/* _____PROJECT INCLUDES____________________________________________________ */
#include "App.h"
#include "../services/atService_EG800K.h"
#include "../src/obj/atObj_Param.h"
#include "../src/obj/atObj_Data.h"
/* _____DEFINITIONS__________________________________________________________ */

/* _____GLOBAL VARIABLES_____________________________________________________ */
TaskHandle_t Task_atApp_FTP;  
void atApp_FTP_Task_Func(void *parameter);
///////////////////////////////////////////////Testing part//
/* _____GLOBAL FUNCTION______________________________________________________ */

/* _____CLASS DEFINITION_____________________________________________________ */

/**
 * This Application class is the application to manage the 
 */
class App_FTP : public Application
{
public:
  	App_FTP();
 	~App_FTP();
protected:
private:
  	static void  App_FTP_Pend();
	static void  App_FTP_Start();
	static void  App_FTP_Restart();
	static void  App_FTP_Execute();
	static void  App_FTP_Suspend();
	static void  App_FTP_Resume();	  
	static void  App_FTP_End();
} atApp_FTP ;
/**
 * This function will be automaticaly called when a object is created by this class
 */
App_FTP::App_FTP(/* args */)
{
  	_Pend_User 	     = *App_FTP_Pend;
	_Start_User 	 = *App_FTP_Start;
	_Restart_User 	 = *App_FTP_Restart;
	_Execute_User 	 = *App_FTP_Execute;
	_Suspend_User	 = *App_FTP_Suspend;
	_Resume_User	 = *App_FTP_Resume;
	_End_User	     = *App_FTP_End;

	// change the ID of application
	ID_Application = 1;
	// change the application name
	Name_Application = (char*)"FTP Application	";
	// change the ID of SNM
}
/**
 * This function will be automaticaly called when the object of class is delete
 */
App_FTP::~App_FTP()
{
	
}
/**
 * Pend to start is the first task of this application it will do prerequisite condition. In the debit mode, task will send information of application to terminal to start the application.
 */
void  App_FTP::App_FTP_Pend()
{
    // atService_EG800K.Debug();
}
/**
 * This start function will init some critical function 
 */
void  App_FTP::App_FTP_Start()
{
	// init atEG800K Service in the fist running time
	// atService_EG800K.Run_Service();
	Service_EG800K::configEG800K();
	Service_EG800K::configFTP();
}  
/**
 * Restart function of SNM  app
 */
void  App_FTP::App_FTP_Restart()
{

}
/**
 * Execute fuction of SNM app
 */
void  App_FTP::App_FTP_Execute()
{	
	// Service_EG800K::sendFTPfile("testNHNVN.txt", "This is a test file content by NHN2707.");
    // if(atApp_FTP.User_Mode == APP_USER_MODE_DEBUG)
    // {
    // }   
}
void  App_FTP::App_FTP_Suspend(){}
void  App_FTP::App_FTP_Resume(){}	  
void  App_FTP::App_FTP_End(){}
void atApp_FTP_Task_Func(void *parameter)
{
  while (1)
  {
    atApp_FTP.Run_Application(APP_RUN_MODE_AUTO);
    vTaskDelay(1000/ portTICK_PERIOD_MS);
  }
}
#endif