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

    // Enable AI channels
    bool enCh1AI = true;
    bool enCh2AI = true;
    bool enCh3AI = true;
    bool enCh4AI = true;
    bool enRawAI = true;
    bool enVolAI = true;
    // Enable DI channels
    bool enCh1DI = true;
    bool enCh2DI = true;
    bool enCh3DI = true;
    bool enCh4DI = true;
    uint32_t delayDI = 100; // Default delay for DI channels in milliseconds
    //Enable PWM channels
    bool enCh1PWM = true;
    bool enCh2PWM = true;
    bool enCh3PWM = true;
    bool enCh4PWM = true;
    uint32_t freqCh1PWM = 5000; // Default frequency for PWM channels in Hz
    uint32_t freqCh2PWM = 5000; // Default frequency for PWM channels in Hz
    uint32_t freqCh3PWM = 5000; // Default frequency for PWM channels in Hz
    uint32_t freqCh4PWM = 5000; // Default frequency for PWM channels in Hz
    uint8_t resolutionCh1PWM = 8; // Default resolution for PWM channels
    uint8_t resolutionCh2PWM = 8; // Default resolution for PWM channels
    uint8_t resolutionCh3PWM = 8; // Default resolution for PWM channels
    uint8_t resolutionCh4PWM = 8; // Default resolution for PWM channels
    float dutyCycleCh1PWM = 50.00; // Default duty cycle for PWM channels (50%)
    float dutyCycleCh2PWM = 50.00; // Default duty cycle for PWM channels (50%)
    float dutyCycleCh3PWM = 50.00; // Default duty cycle for PWM channels (50%)
    float dutyCycleCh4PWM = 50.00; // Default duty cycle for PWM channels (50%)

    Object_Param(/* args */);
    ~Object_Param();

protected:
private:
    /* data */
} atObject_Param;
// Parameters for AI channels
// bool Object_Param::enCh1AI = true;
bool Object_Param::enCh2AI = true;
bool Object_Param::enCh3AI = true;
bool Object_Param::enCh4AI = true;
bool Object_Param::enRawAI = true;
bool Object_Param::enVolAI = true;
// Parameters for DI channels
bool Object_Param::enCh1DI = true;
bool Object_Param::enCh2DI = true;
bool Object_Param::enCh3DI = true;
bool Object_Param::enCh4DI = true;
uint32_t Object_Param::delayDI = 100; // Default delay for DI channels in milliseconds
// Parameters for PWM channels
bool Object_Param::enCh1PWM = true;
bool Object_Param::enCh2PWM = true;
bool Object_Param::enCh3PWM = true;
bool Object_Param::enCh4PWM = true;
uint32_t Object_Param::freqCh1PWM = 5000; // Default frequency for PWM channels in Hz
uint32_t Object_Param::freqCh2PWM = 5000; // Default frequency for PWM channels in Hz
uint32_t Object_Param::freqCh3PWM = 5000; // Default frequency for PWM channels in Hz
uint32_t Object_Param::freqCh4PWM = 5000; // Default frequency for PWM channels in Hz
uint8_t Object_Param::resolutionCh1PWM = 8; // Default resolution for PWM channels
uint8_t Object_Param::resolutionCh2PWM = 8; // Default resolution for PWM channels
uint8_t Object_Param::resolutionCh3PWM = 8; // Default resolution for PWM channels
uint8_t Object_Param::resolutionCh4PWM = 8; // Default resolution for PWM channels
float Object_Param::dutyCycleCh1PWM = 50.00; // Default duty cycle for PWM channels (50%)
float Object_Param::dutyCycleCh2PWM = 50.00; // Default duty cycle for PWM channels (50%)
float Object_Param::dutyCycleCh3PWM = 50.00; // Default duty cycle for PWM channels (50%)
float Object_Param::dutyCycleCh4PWM = 50.00; // Default duty cycle for PWM channels (50%)

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