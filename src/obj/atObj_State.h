#ifndef Object_State_h
#define Object_State_h


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

class Object_State :public Object
{
public:
    static void   Object_State_Start();
    static void   Object_State_Execute();    
    static void   Object_State_End();

    Object_State(/* args */);
    ~Object_State();
protected: 
    
    
private:
    /* data */ 
} atObject_State;
/**
 * @brief This function code is executed one time when class is init
 * 
 */
Object_State::Object_State(/* args */)
{
     _Start_User      = *Object_State_Start;
     _Execute_User    = *Object_State_Execute;
     _End_User        = *Object_State_End;
}
/**
 * @brief This function code is executed one time when class is deinit
 * 
 */
Object_State::~Object_State()
{
}
/**
 * This start function will init some critical function 
 */
void  Object_State::Object_State_Start()
{
  
}
/**
 * Execute fuction of SNM app
 */
void  Object_State:: Object_State_Execute()
{   

}    
void  Object_State:: Object_State_End(){}

#endif