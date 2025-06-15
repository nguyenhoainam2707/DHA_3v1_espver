#ifndef Object_Value_h
#define Object_Value_h

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

class Object_Value : public Object
{
public:
    static void Object_Value_Start();
    static void Object_Value_Execute();
    static void Object_Value_End();

    static float voltage;
    static uint16_t adcRawValue;

    Object_Value(/* args */);
    ~Object_Value();

protected:
private:
    /* data */
} atObject_Value;

float Object_Value::voltage = 0.0f;
uint16_t Object_Value::adcRawValue = 0;
/**
 * @brief This function code is executed one time when class is init
 *
 */
Object_Value::Object_Value(/* args */)
{
    _Start_User = *Object_Value_Start;
    _Execute_User = *Object_Value_Execute;
    _End_User = *Object_Value_End;
}
/**
 * @brief This function code is executed one time when class is deinit
 *
 */
Object_Value::~Object_Value()
{
}
/**
 * This start function will init some critical function
 */
void Object_Value::Object_Value_Start()
{
}
/**
 * Execute fuction of SNM app
 */
void Object_Value::Object_Value_Execute()
{
}
void Object_Value::Object_Value_End() {}

#endif