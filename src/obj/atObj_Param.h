#ifndef Object_Param_h
#define Object_Param_h

/* _____PROJECT INCLUDES____________________________________________________ */
#include "Arduino.h"
#include "Object.h"
/* _____DEFINITIONS__________________________________________________________ */

/* _____GLOBAL VARIABLES_____________________________________________________ */

/* _____GLOBAL FUNCTION______________________________________________________ */

/* _____CLASS DEFINITION_____________________________________________________ */
/**
 * This class is the application to manage the
 */

class Object_Param : public Object
{
public:
    static void Object_Param_Start();
    static void Object_Param_Execute();
    static void Object_Param_End();

    // Enable ADC channels
    static bool enCh1ADC;
    static bool enCh2ADC;
    static bool enCh3ADC;
    static bool enCh4ADC;
    static bool enRawADC;
    static bool enVolADC;
    // Enable DI channels
    static bool enCh1DI;
    static bool enCh2DI;
    static bool enCh3DI;
    static bool enCh4DI;
    static uint32_t delayDI;

    Object_Param(/* args */);
    ~Object_Param();

protected:
private:
    /* data */
} atObject_Param;
// Parameters for ADC channels
bool Object_Param::enCh1ADC = true;
bool Object_Param::enCh2ADC = true;
bool Object_Param::enCh3ADC = true;
bool Object_Param::enCh4ADC = true;
bool Object_Param::enRawADC = true;
bool Object_Param::enVolADC = true;
// Parameters for DI channels
bool Object_Param::enCh1DI = true;
bool Object_Param::enCh2DI = true;
bool Object_Param::enCh3DI = true;
bool Object_Param::enCh4DI = true;
uint32_t Object_Param::delayDI = 100; // Default delay for DI channels in milliseconds
/**
 * @brief This function code is executed one time when class is init
 *
 */
Object_Param::Object_Param(/* args */)
{
    _Start_User = *Object_Param_Start;
    _Execute_User = *Object_Param_Execute;
    _End_User = *Object_Param_End;
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
void Object_Param::Object_Param_Start()
{
}
/**
 * Execute fuction of SNM app
 */
void Object_Param::Object_Param_Execute()
{
}
void Object_Param::Object_Param_End() {}

#endif