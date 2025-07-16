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
    bool enCurAI = true;
    uint32_t refreshRateAI = 500; // Default refresh rate for AI channels in milliseconds
    // Enable DI channels
    bool enCh1DI = false;
    bool enCh2DI = false;
    bool enCh3DI = false;
    bool enCh4DI = false;
    uint32_t refreshRateDI = 1000; // Default refresh rate for DI channels in milliseconds
    //Enable PWM channels
    bool enCh1PWM = false;
    bool enCh2PWM = false;
    bool enCh3PWM = false;
    bool enCh4PWM = false;
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

    //Parameters for LCD
    bool enLCD = false; // Enable LCD
    bool enLCDBacklight = true; // Enable LCD backlight
    uint32_t refreshRateLCD = 500; // Default refresh rate for LCD in milliseconds

    // Enable Modbus RTU
    bool enMB1 = false;
    bool enMB2 = false;
    uint32_t baudRateMB1 = 9600; // Default baud rate for Modbus RTU
    uint32_t baudRateMB2 = 9600;
    uint8_t slaveIDMB1 = 1; // Default slave ID for Modbus RTU
    uint8_t slaveIDMB2 = 1; // Default slave ID for Modbus RTU
    uint8_t functionCodeMB1 = 3; // Default function code for Modbus RTU
    uint8_t functionCodeMB2 = 3;
    uint16_t startAddressMB1 = 0; // Default start address for Modbus RTU
    uint16_t startAddressMB2 = 0;
    uint16_t numRegistersMB1 = 1; // Default number of registers for Modbus RTU
    uint16_t numRegistersMB2 = 1; // Default number of registers for Modbus RTU
    String sensorNameMB1 = "Sensor 1"; // Default sensor name
    String sensorNameMB2 = "Sensor 2"; // Default sensor name
    uint32_t refreshRateMB1 = 1000; // Default refresh rate for Modbus RTU in milliseconds
    uint32_t refreshRateMB2 = 1000; // Default refresh rate for Modbus RTU in milliseconds

    //Parameters for MQTT_PUB
    bool enMQTTPUB = true;
    uint32_t refreshRateMQTTPUB = 5000; // Default refresh rate for MQTT_PUB in milliseconds
    String mqttBroker = "broker.emqx.io"; // Default MQTT server
    uint16_t mqttPort = 1883; // Default MQTT port
    String mqttClientID = "esp32s3-client"; // Default MQTT client ID
    String mqttPubTopic = "esp32s3/data";

    //Parameters for MQTT_SUB
    bool enMQTTSUB = false;
    uint32_t refreshRateMQTTSUB = 5000; // Default refresh rate for MQTT_SUB in milliseconds
    String mqttSubTopic = "esp32s3/command";

    Object_Param(/* args */);
    ~Object_Param();

protected:
private:
    /* data */
} atObject_Param;

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