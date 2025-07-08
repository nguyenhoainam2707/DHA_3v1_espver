#ifndef Object_Param_h
#define Object_Param_h


/* _____PROJECT INCLUDES____________________________________________________ */
#include "Arduino.h"
#include "Object.h"
/* _____DEFINITIONS__________________________________________________________ */

enum Example
{
    default_1,
    default2,
    default3
};

/* _____GLOBAL VARIABLES_____________________________________________________ */


/* _____GLOBAL FUNCTION______________________________________________________ */

/* _____CLASS DEFINITION_____________________________________________________ */
/**
 * This class is the application to manage the 
 */

class Object_Param :public Object
{
public:
    static void   Object_Param_Start();
    static void   Object_Param_Execute();    
    static void   Object_Param_End();

    static bool enCh1ADC;
    static bool enCh2ADC;
    static bool enCh3ADC;
    static bool enCh4ADC;
    static bool enRawADC;
    static bool enVolADC;

    Object_Param(/* args */);
    ~Object_Param();
protected: 
    
    
private:
    /* data */ 
} atObject_Param;

bool atObject_Param.enCh1ADC = false;
bool atObject_Param.enCh2ADC = false;
/**
 * @brief This function code is executed one time when class is init
 * 
 */
Object_Param::Object_Param(/* args */)
{
     _Start_User      = *Object_Param_Start;
     _Execute_User    = *Object_Param_Execute;
     _End_User        = *Object_Param_End;
}
/**
 * @brief This function code is executed one time when class is deinit
 * 
 */
Object_Param::~Object_Param()
{
}
/**
 * This start function will init some critical function 
 */
void  Object_Param::Object_Param_Start()
{
  
}
/**
 * Execute fuction of SNM app
 */
void  Object_Param:: Object_Param_Execute()
{   

}    
void  Object_Param:: Object_Param_End(){}

#endif