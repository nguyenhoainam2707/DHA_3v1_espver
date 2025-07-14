#ifndef Object_Data_h
#define Object_Data_h

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

class Object_Data : public Object
{
public:
    static void Object_Data_Start();
    static void Object_Data_Execute();
    static void Object_Data_End();
    //Data of ADC channels
    float ch1Voltage = 0.0f;
    float ch2Voltage = 0.0f;
    float ch3Voltage = 0.0f;
    float ch4Voltage = 0.0f;
    uint16_t ch1RawData = 0;
    uint16_t ch2RawData = 0;
    uint16_t ch3RawData = 0;
    uint16_t ch4RawData = 0;
    //Data of DI channels
    bool ch1DI = false;
    bool ch2DI = false;
    bool ch3DI = false;
    bool ch4DI = false;

    uint16_t waterLevel = 0; // Water level data


    Object_Data(/* args */);
    ~Object_Data();

protected:
private:
    /* data */
} atObject_Data;
/**
 * @brief This function code is executed one time when class is init
 *
 */
Object_Data::Object_Data(/* args */)
{
    _Start_User = *Object_Data_Start;
    _Execute_User = *Object_Data_Execute;
    _End_User = *Object_Data_End;
}
/**
 * @brief This function code is executed one time when class is deinit
 *
 */
Object_Data::~Object_Data()
{
}
/**
 * This start function will init some critical function
 */
void Object_Data::Object_Data_Start()
{
}
/**
 * Execute fuction of SNM app
 */
void Object_Data::Object_Data_Execute()
{
}
void Object_Data::Object_Data_End() {}

#endif