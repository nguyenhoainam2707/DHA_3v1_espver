/**
@file
Object Template.
*/
/*
  Object_ADC.h - Arduino library for control with ESP32
  Library:: Object_ADC
  This version is
  Copyright:: 2021 nguyentrinhtuan1996@gmail.com
*/
#ifndef Object_ADC_h
#define Object_ADC_h

/* _____PROJECT INCLUDES____________________________________________________ */
#include "Arduino.h"
#include "Object.h"
/* _____DEFINITIONS__________________________________________________________ */

// enum Example
// {
//     default_1,
//     default2,
//     default3
// };

/* _____GLOBAL VARIABLES_____________________________________________________ */

/* _____GLOBAL FUNCTION______________________________________________________ */

/* _____CLASS DEFINITION_____________________________________________________ */
/**
 * This class is the application to manage the
 */

class Object_ADC : public Object
{
public:
  static void Object_ADC_Start();
  static void Object_ADC_Execute();
  static void Object_ADC_End();

  static float voltage;
  static uint16_t adcRawValue;
  Object_ADC(/* args */);
  ~Object_ADC();

protected:
private:
  /* data */
} atObject_ADC;

float Object_ADC::voltage = 0.0f;
uint16_t Object_ADC::adcRawValue = 0;
/**
 * @brief This function code is executed one time when class is init
 *
 */
Object_ADC::Object_ADC(/* args */)
{
  _Start_User = *Object_ADC_Start;
  _Execute_User = *Object_ADC_Execute;
  _End_User = *Object_ADC_End;
}
/**
 * @brief This function code is executed one time when class is deinit
 *
 */
Object_ADC::~Object_ADC()
{
}
/**
 * This start function will init some critical function
 */
void Object_ADC::Object_ADC_Start()
{
}
/**
 * Execute fuction of SNM app
 */
void Object_ADC::Object_ADC_Execute()
{
}
void Object_ADC::Object_ADC_End() {}

#endif