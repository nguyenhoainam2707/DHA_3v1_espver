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
    //Data of ADC channels
    static float ch1Voltage;
    static float ch2Voltage;
    static float ch3Voltage;
    static float ch4Voltage;
    static uint16_t ch1RawValue;
    static uint16_t ch2RawValue;
    static uint16_t ch3RawValue;
    static uint16_t ch4RawValue;
    //Data of DI channels
    static bool ch1DI;
    static bool ch2DI;
    static bool ch3DI;
    static bool ch4DI;


    Object_Value(/* args */);
    ~Object_Value();

protected:
private:
    /* data */
} atObject_Value;

float Object_Value::ch1Voltage = 0.0f;
float Object_Value::ch2Voltage = 0.0f;
float Object_Value::ch3Voltage = 0.0f;
float Object_Value::ch4Voltage = 0.0f;
uint16_t Object_Value::ch1RawValue = 0;
uint16_t Object_Value::ch2RawValue = 0;
uint16_t Object_Value::ch3RawValue = 0;
uint16_t Object_Value::ch4RawValue = 0;

bool Object_Value::ch1DI = false;
bool Object_Value::ch2DI = false;
bool Object_Value::ch3DI = false;
bool Object_Value::ch4DI = false;
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