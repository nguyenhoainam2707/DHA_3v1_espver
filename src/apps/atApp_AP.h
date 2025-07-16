#ifndef _Application_atApp_AP_
#define _Application_atApp_AP_
/* _____PROJECT INCLUDES____________________________________________________ */
#include "App.h"
#include <WiFi.h>
#include <WebServer.h>
#include <Preferences.h>
#include "../src/obj/atObj_Param.h"
#include "../src/obj/atObj_Data.h"
/* _____DEFINITIONS__________________________________________________________ */

/* _____GLOBAL VARIABLES_____________________________________________________ */
TaskHandle_t Task_atApp_AP;
void atApp_AP_Task_Func(void *parameter);
WebServer server(80);
Preferences preferences;
///////////////////////////////////////////////Testing part//
/* _____GLOBAL FUNCTION______________________________________________________ */

/* _____CLASS DEFINITION_____________________________________________________ */

/**
 * This Application class is the application to manage the
 */
class App_AP : public Application
{
public:
	App_AP();
	~App_AP();

	static void setDefaultConfig();
	static void loadConfig();
	static void handleRoot();
	static void handleSave();
	static void saveConfig();

protected:
private:
	static void App_AP_Pend();
	static void App_AP_Start();
	static void App_AP_Restart();
	static void App_AP_Execute();
	static void App_AP_Suspend();
	static void App_AP_Resume();
	static void App_AP_End();
} atApp_AP;
/**
 * This function will be automaticaly called when a object is created by this class
 */
App_AP::App_AP(/* args */)
{
	_Pend_User = *App_AP_Pend;
	_Start_User = *App_AP_Start;
	_Restart_User = *App_AP_Restart;
	_Execute_User = *App_AP_Execute;
	_Suspend_User = *App_AP_Suspend;
	_Resume_User = *App_AP_Resume;
	_End_User = *App_AP_End;

	// change the ID of application
	ID_Application = 1;
	// change the application name
	Name_Application = (char *)"AP Application	";
	// change the ID of SNM
}
/**
 * This function will be automaticaly called when the object of class is delete
 */
App_AP::~App_AP()
{
}

void App_AP::setDefaultConfig()
{
	// AI channels
	atObject_Param.enCh1AI = true;
	atObject_Param.enCh2AI = true;
	atObject_Param.enCh3AI = true;
	atObject_Param.enCh4AI = true;
	atObject_Param.enRawAI = true;
	atObject_Param.enCurAI = true;
	atObject_Param.refreshRateAI = 1000;

	// DI channels
	atObject_Param.enCh1DI = false;
	atObject_Param.enCh2DI = false;
	atObject_Param.enCh3DI = false;
	atObject_Param.enCh4DI = false;
	atObject_Param.refreshRateDI = 1000;

	// PWM channels
	atObject_Param.enCh1PWM = false;
	atObject_Param.enCh2PWM = false;
	atObject_Param.enCh3PWM = false;
	atObject_Param.enCh4PWM = false;
	atObject_Param.freqCh1PWM = 5000;
	atObject_Param.freqCh2PWM = 5000;
	atObject_Param.freqCh3PWM = 5000;
	atObject_Param.freqCh4PWM = 5000;
	atObject_Param.resolutionCh1PWM = 8;
	atObject_Param.resolutionCh2PWM = 8;
	atObject_Param.resolutionCh3PWM = 8;
	atObject_Param.resolutionCh4PWM = 8;
	atObject_Param.dutyCycleCh1PWM = 50.00;
	atObject_Param.dutyCycleCh2PWM = 50.00;
	atObject_Param.dutyCycleCh3PWM = 50.00;
	atObject_Param.dutyCycleCh4PWM = 50.00;

	// LCD
	atObject_Param.enLCD = false;
	atObject_Param.enLCDBacklight = true;
	atObject_Param.refreshRateLCD = 500;

	// Modbus RTU
	atObject_Param.enMB1 = false;
	atObject_Param.enMB2 = false;
	atObject_Param.baudRateMB1 = 9600;
	atObject_Param.baudRateMB2 = 9600;
	atObject_Param.slaveIDMB1 = 1;
	atObject_Param.slaveIDMB2 = 1;
	atObject_Param.functionCodeMB1 = 3;
	atObject_Param.functionCodeMB2 = 3;
	atObject_Param.startAddressMB1 = 0;
	atObject_Param.startAddressMB2 = 0;
	atObject_Param.numRegistersMB1 = 1;
	atObject_Param.numRegistersMB2 = 1;
	atObject_Param.sensorNameMB1 = "Sensor 1";
	atObject_Param.sensorNameMB2 = "Sensor 2";
	atObject_Param.refreshRateMB1 = 1000;
	atObject_Param.refreshRateMB2 = 1000;

	// MQTT_PUB
	atObject_Param.enMQTTPUB = true;
	atObject_Param.refreshRateMQTTPUB = 5000;
	atObject_Param.mqttBroker = "broker.emqx.io";
	atObject_Param.mqttPort = 1883;
	atObject_Param.mqttClientID = "esp32s3-client";
	atObject_Param.mqttPubTopic = "esp32s3/data";

	// MQTT_SUB
	atObject_Param.enMQTTSUB = false;
	atObject_Param.refreshRateMQTTSUB = 5000;
	atObject_Param.mqttSubTopic = "esp32s3/command";
}

void App_AP::loadConfig()
{
	preferences.begin("config", true); // true: read-only

	// AI channels
	atObject_Param.enCh1AI = preferences.getBool("enCh1AI", atObject_Param.enCh1AI);
	atObject_Param.enCh2AI = preferences.getBool("enCh2AI", atObject_Param.enCh2AI);
	atObject_Param.enCh3AI = preferences.getBool("enCh3AI", atObject_Param.enCh3AI);
	atObject_Param.enCh4AI = preferences.getBool("enCh4AI", atObject_Param.enCh4AI);
	atObject_Param.enRawAI = preferences.getBool("enRawAI", atObject_Param.enRawAI);
	atObject_Param.enCurAI = preferences.getBool("enCurAI", atObject_Param.enCurAI);
	atObject_Param.refreshRateAI = preferences.getUInt("refreshRateAI", atObject_Param.refreshRateAI);

	// DI channels
	atObject_Param.enCh1DI = preferences.getBool("enCh1DI", atObject_Param.enCh1DI);
	atObject_Param.enCh2DI = preferences.getBool("enCh2DI", atObject_Param.enCh2DI);
	atObject_Param.enCh3DI = preferences.getBool("enCh3DI", atObject_Param.enCh3DI);
	atObject_Param.enCh4DI = preferences.getBool("enCh4DI", atObject_Param.enCh4DI);
	atObject_Param.refreshRateDI = preferences.getUInt("refreshRateDI", atObject_Param.refreshRateDI);

	// PWM channels
	atObject_Param.enCh1PWM = preferences.getBool("enCh1PWM", atObject_Param.enCh1PWM);
	atObject_Param.enCh2PWM = preferences.getBool("enCh2PWM", atObject_Param.enCh2PWM);
	atObject_Param.enCh3PWM = preferences.getBool("enCh3PWM", atObject_Param.enCh3PWM);
	atObject_Param.enCh4PWM = preferences.getBool("enCh4PWM", atObject_Param.enCh4PWM);
	atObject_Param.freqCh1PWM = preferences.getUInt("freqCh1PWM", atObject_Param.freqCh1PWM);
	atObject_Param.freqCh2PWM = preferences.getUInt("freqCh2PWM", atObject_Param.freqCh2PWM);
	atObject_Param.freqCh3PWM = preferences.getUInt("freqCh3PWM", atObject_Param.freqCh3PWM);
	atObject_Param.freqCh4PWM = preferences.getUInt("freqCh4PWM", atObject_Param.freqCh4PWM);
	atObject_Param.resolutionCh1PWM = preferences.getUChar("resCh1PWM", atObject_Param.resolutionCh1PWM);
	atObject_Param.resolutionCh2PWM = preferences.getUChar("resCh2PWM", atObject_Param.resolutionCh2PWM);
	atObject_Param.resolutionCh3PWM = preferences.getUChar("resCh3PWM", atObject_Param.resolutionCh3PWM);
	atObject_Param.resolutionCh4PWM = preferences.getUChar("resCh4PWM", atObject_Param.resolutionCh4PWM);
	atObject_Param.dutyCycleCh1PWM = preferences.getFloat("dutyCh1PWM", atObject_Param.dutyCycleCh1PWM);
	atObject_Param.dutyCycleCh2PWM = preferences.getFloat("dutyCh2PWM", atObject_Param.dutyCycleCh2PWM);
	atObject_Param.dutyCycleCh3PWM = preferences.getFloat("dutyCh3PWM", atObject_Param.dutyCycleCh3PWM);
	atObject_Param.dutyCycleCh4PWM = preferences.getFloat("dutyCh4PWM", atObject_Param.dutyCycleCh4PWM);

	// LCD
	atObject_Param.enLCD = preferences.getBool("enLCD", atObject_Param.enLCD);
	atObject_Param.enLCDBacklight = preferences.getBool("enLCDBack", atObject_Param.enLCDBacklight);
	atObject_Param.refreshRateLCD = preferences.getUInt("refreshLCD", atObject_Param.refreshRateLCD);

	// Modbus RTU
	atObject_Param.enMB1 = preferences.getBool("enMB1", atObject_Param.enMB1);
	atObject_Param.enMB2 = preferences.getBool("enMB2", atObject_Param.enMB2);
	atObject_Param.baudRateMB1 = preferences.getUInt("baudMB1", atObject_Param.baudRateMB1);
	atObject_Param.baudRateMB2 = preferences.getUInt("baudMB2", atObject_Param.baudRateMB2);
	atObject_Param.slaveIDMB1 = preferences.getUChar("slaveID1", atObject_Param.slaveIDMB1);
	atObject_Param.slaveIDMB2 = preferences.getUChar("slaveID2", atObject_Param.slaveIDMB2);
	atObject_Param.functionCodeMB1 = preferences.getUChar("funcCode1", atObject_Param.functionCodeMB1);
	atObject_Param.functionCodeMB2 = preferences.getUChar("funcCode2", atObject_Param.functionCodeMB2);
	atObject_Param.startAddressMB1 = preferences.getUShort("startAddr1", atObject_Param.startAddressMB1);
	atObject_Param.startAddressMB2 = preferences.getUShort("startAddr2", atObject_Param.startAddressMB2);
	atObject_Param.numRegistersMB1 = preferences.getUShort("numReg1", atObject_Param.numRegistersMB1);
	atObject_Param.numRegistersMB2 = preferences.getUShort("numReg2", atObject_Param.numRegistersMB2);
	atObject_Param.sensorNameMB1 = preferences.getString("sensor1", atObject_Param.sensorNameMB1);
	atObject_Param.sensorNameMB2 = preferences.getString("sensor2", atObject_Param.sensorNameMB2);
	atObject_Param.refreshRateMB1 = preferences.getUInt("refreshMB1", atObject_Param.refreshRateMB1);
	atObject_Param.refreshRateMB2 = preferences.getUInt("refreshMB2", atObject_Param.refreshRateMB2);

	// MQTT_PUB
	atObject_Param.enMQTTPUB = preferences.getBool("enMQTTPUB", atObject_Param.enMQTTPUB);
	atObject_Param.refreshRateMQTTPUB = preferences.getUInt("refreshMQTTPUB", atObject_Param.refreshRateMQTTPUB);
	atObject_Param.mqttBroker = preferences.getString("mqttBroker", atObject_Param.mqttBroker);
	atObject_Param.mqttPort = preferences.getUShort("mqttPort", atObject_Param.mqttPort);
	atObject_Param.mqttClientID = preferences.getString("mqttClientID", atObject_Param.mqttClientID);
	atObject_Param.mqttPubTopic = preferences.getString("mqttPubTopic", atObject_Param.mqttPubTopic);

	// MQTT_SUB
	atObject_Param.enMQTTSUB = preferences.getBool("enMQTTSUB", atObject_Param.enMQTTSUB);
	atObject_Param.refreshRateMQTTSUB = preferences.getUInt("refreshMQTTSUB", atObject_Param.refreshRateMQTTSUB);
	atObject_Param.mqttSubTopic = preferences.getString("mqttSubTopic", atObject_Param.mqttSubTopic);

	preferences.end();
	Serial.println("Configuration loaded");
}

void App_AP::saveConfig()
{
	preferences.begin("config", false); // false: read-write // true: read only // namespace: "config"

	// AI channels
	preferences.putBool("enCh1AI", atObject_Param.enCh1AI);
	preferences.putBool("enCh2AI", atObject_Param.enCh2AI);
	preferences.putBool("enCh3AI", atObject_Param.enCh3AI);
	preferences.putBool("enCh4AI", atObject_Param.enCh4AI);
	preferences.putBool("enRawAI", atObject_Param.enRawAI);
	preferences.putBool("enCurAI", atObject_Param.enCurAI);
	preferences.putUInt("refreshRateAI", atObject_Param.refreshRateAI);

	// DI channels
	preferences.putBool("enCh1DI", atObject_Param.enCh1DI);
	preferences.putBool("enCh2DI", atObject_Param.enCh2DI);
	preferences.putBool("enCh3DI", atObject_Param.enCh3DI);
	preferences.putBool("enCh4DI", atObject_Param.enCh4DI);
	preferences.putUInt("refreshRateDI", atObject_Param.refreshRateDI);

	// PWM channels
	preferences.putBool("enCh1PWM", atObject_Param.enCh1PWM);
	preferences.putBool("enCh2PWM", atObject_Param.enCh2PWM);
	preferences.putBool("enCh3PWM", atObject_Param.enCh3PWM);
	preferences.putBool("enCh4PWM", atObject_Param.enCh4PWM);
	preferences.putUInt("freqCh1PWM", atObject_Param.freqCh1PWM);
	preferences.putUInt("freqCh2PWM", atObject_Param.freqCh2PWM);
	preferences.putUInt("freqCh3PWM", atObject_Param.freqCh3PWM);
	preferences.putUInt("freqCh4PWM", atObject_Param.freqCh4PWM);
	preferences.putUChar("resCh1PWM", atObject_Param.resolutionCh1PWM);
	preferences.putUChar("resCh2PWM", atObject_Param.resolutionCh2PWM);
	preferences.putUChar("resCh3PWM", atObject_Param.resolutionCh3PWM);
	preferences.putUChar("resCh4PWM", atObject_Param.resolutionCh4PWM);
	preferences.putFloat("dutyCh1PWM", atObject_Param.dutyCycleCh1PWM);
	preferences.putFloat("dutyCh2PWM", atObject_Param.dutyCycleCh2PWM);
	preferences.putFloat("dutyCh3PWM", atObject_Param.dutyCycleCh3PWM);
	preferences.putFloat("dutyCh4PWM", atObject_Param.dutyCycleCh4PWM);

	// LCD
	preferences.putBool("enLCD", atObject_Param.enLCD);
	preferences.putBool("enLCDBack", atObject_Param.enLCDBacklight);
	preferences.putUInt("refreshLCD", atObject_Param.refreshRateLCD);

	// Modbus RTU
	preferences.putBool("enMB1", atObject_Param.enMB1);
	preferences.putBool("enMB2", atObject_Param.enMB2);
	preferences.putUInt("baudMB1", atObject_Param.baudRateMB1);
	preferences.putUInt("baudMB2", atObject_Param.baudRateMB2);
	preferences.putUChar("slaveID1", atObject_Param.slaveIDMB1);
	preferences.putUChar("slaveID2", atObject_Param.slaveIDMB2);
	preferences.putUChar("funcCode1", atObject_Param.functionCodeMB1);
	preferences.putUChar("funcCode2", atObject_Param.functionCodeMB2);
	preferences.putUShort("startAddr1", atObject_Param.startAddressMB1);
	preferences.putUShort("startAddr2", atObject_Param.startAddressMB2);
	preferences.putUShort("numReg1", atObject_Param.numRegistersMB1);
	preferences.putUShort("numReg2", atObject_Param.numRegistersMB2);
	preferences.putString("sensor1", atObject_Param.sensorNameMB1);
	preferences.putString("sensor2", atObject_Param.sensorNameMB2);
	preferences.putUInt("refreshMB1", atObject_Param.refreshRateMB1);
	preferences.putUInt("refreshMB2", atObject_Param.refreshRateMB2);

	// MQTT_PUB
	preferences.putBool("enMQTTPUB", atObject_Param.enMQTTPUB);
	preferences.putUInt("refreshMQTTPUB", atObject_Param.refreshRateMQTTPUB);
	preferences.putString("mqttBroker", atObject_Param.mqttBroker);
	preferences.putUShort("mqttPort", atObject_Param.mqttPort);
	preferences.putString("mqttClientID", atObject_Param.mqttClientID);
	preferences.putString("mqttPubTopic", atObject_Param.mqttPubTopic);

	// MQTT_SUB
	preferences.putBool("enMQTTSUB", atObject_Param.enMQTTSUB);
	preferences.putUInt("refreshMQTTSUB", atObject_Param.refreshRateMQTTSUB);
	preferences.putString("mqttSubTopic", atObject_Param.mqttSubTopic);

	preferences.end();
	Serial.println("Configuration saved");
}

void App_AP::handleRoot()
{
	String html = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>DHA-3 Configuration</title>
    <style>
        :root {
            --primary: #2c3e50;
            --secondary: #3498db;
            --accent: #e74c3c;
            --light: #ecf0f1;
            --dark: #34495e;
        }
        
        * {
            box-sizing: border-box;
            margin: 0;
            padding: 0;
        }
        
        body {
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
            line-height: 1.6;
            color: #333;
            background-color: #f5f7fa;
            padding: 20px;
            max-width: 1200px;
            margin: 0 auto;
        }
        
        header {
            background: linear-gradient(135deg, var(--primary), var(--dark));
            color: white;
            padding: 1.5rem;
            border-radius: 10px 10px 0 0;
            text-align: center;
            box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);
            margin-bottom: 25px;
        }
        
        h1 {
            font-size: 2.2rem;
            margin-bottom: 0.5rem;
        }
        
        .container {
            display: grid;
            grid-template-columns: repeat(auto-fit, minmax(350px, 1fr));
            gap: 25px;
        }
        
        .section {
            background: white;
            border-radius: 10px;
            padding: 25px;
            box-shadow: 0 4px 15px rgba(0, 0, 0, 0.08);
            transition: transform 0.3s ease;
        }
        
        .section:hover {
            transform: translateY(-5px);
        }
        
        h2 {
            color: var(--secondary);
            border-bottom: 2px solid var(--secondary);
            padding-bottom: 10px;
            margin-bottom: 20px;
            font-size: 1.6rem;
        }
        
        .form-group {
            margin-bottom: 20px;
            padding: 15px;
            border-radius: 8px;
            background-color: #f8f9fa;
        }
        
        label {
            display: block;
            margin-bottom: 8px;
            font-weight: 600;
            color: var(--dark);
        }
        
        input[type="checkbox"] {
            transform: scale(1.3);
            margin-right: 10px;
        }
        
        input[type="number"],
        input[type="text"] {
            width: 100%;
            padding: 12px;
            border: 1px solid #ddd;
            border-radius: 6px;
            font-size: 16px;
            transition: border 0.3s;
        }
        
        input:focus {
            border-color: var(--secondary);
            outline: none;
            box-shadow: 0 0 0 3px rgba(52, 152, 219, 0.2);
        }
        
        .checkbox-group {
            display: flex;
            align-items: center;
            margin-bottom: 12px;
        }
        
        .grid-2, .grid-4 {
            display: grid;
            gap: 15px;
        }
        
        .grid-2 {
            grid-template-columns: 1fr 1fr;
        }
        
        .grid-4 {
            grid-template-columns: repeat(4, 1fr);
        }
        
        .btn-save {
            display: block;
            width: 200px;
            margin: 30px auto;
            padding: 15px;
            background: linear-gradient(135deg, var(--secondary), var(--primary));
            color: white;
            border: none;
            border-radius: 50px;
            font-size: 18px;
            font-weight: 600;
            cursor: pointer;
            transition: all 0.3s ease;
            box-shadow: 0 4px 10px rgba(0, 0, 0, 0.15);
        }
        
        .btn-save:hover {
            transform: scale(1.05);
            box-shadow: 0 6px 15px rgba(0, 0, 0, 0.2);
        }
        
        @media (max-width: 768px) {
            .container {
                grid-template-columns: 1fr;
            }
            
            .grid-2, .grid-4 {
                grid-template-columns: 1fr;
            }
        }
    </style>
</head>
<body>
    <header>
        <h1>DHA-3 Configuration</h1>
        <p>Configure device parameters</p>
    </header>
    
    <form action="/save" method="post">
        <div class="container">
            <!-- AI Channels Section -->
            <div class="section">
                <h2>AI Channels</h2>
                <div class="form-group">
                    <div class="checkbox-group">
                        <input type="checkbox" id="enCh1AI" name="enCh1AI" %enCh1AI%>
                        <label for="enCh1AI">Enable Channel 1</label>
                    </div>
                    <div class="checkbox-group">
                        <input type="checkbox" id="enCh2AI" name="enCh2AI" %enCh2AI%>
                        <label for="enCh2AI">Enable Channel 2</label>
                    </div>
                    <div class="checkbox-group">
                        <input type="checkbox" id="enCh3AI" name="enCh3AI" %enCh3AI%>
                        <label for="enCh3AI">Enable Channel 3</label>
                    </div>
                    <div class="checkbox-group">
                        <input type="checkbox" id="enCh4AI" name="enCh4AI" %enCh4AI%>
                        <label for="enCh4AI">Enable Channel 4</label>
                    </div>
                    <div class="checkbox-group">
                        <input type="checkbox" id="enRawAI" name="enRawAI" %enRawAI%>
                        <label for="enRawAI">Enable Raw AI</label>
                    </div>
                    <div class="checkbox-group">
                        <input type="checkbox" id="enCurAI" name="enCurAI" %enCurAI%>
                        <label for="enCurAI">Enable Current AI</label>
                    </div>
                </div>
                <div class="form-group">
                    <label for="refreshRateAI">Refresh Rate (ms)</label>
                    <input type="number" id="refreshRateAI" name="refreshRateAI" value="%refreshRateAI%" min="100" step="100">
                </div>
            </div>
            
            <!-- DI Channels Section -->
            <div class="section">
                <h2>DI Channels</h2>
                <div class="form-group">
                    <div class="checkbox-group">
                        <input type="checkbox" id="enCh1DI" name="enCh1DI" %enCh1DI%>
                        <label for="enCh1DI">Enable Channel 1</label>
                    </div>
                    <div class="checkbox-group">
                        <input type="checkbox" id="enCh2DI" name="enCh2DI" %enCh2DI%>
                        <label for="enCh2DI">Enable Channel 2</label>
                    </div>
                    <div class="checkbox-group">
                        <input type="checkbox" id="enCh3DI" name="enCh3DI" %enCh3DI%>
                        <label for="enCh3DI">Enable Channel 3</label>
                    </div>
                    <div class="checkbox-group">
                        <input type="checkbox" id="enCh4DI" name="enCh4DI" %enCh4DI%>
                        <label for="enCh4DI">Enable Channel 4</label>
                    </div>
                </div>
                    <div class="form-group">
                        <label for="refreshRateDI">Refresh Rate (ms)</label>
                        <input type="number" id="refreshRateDI" name="refreshRateDI" value="%refreshRateDI%" min="100" step="100">
                    </div>
            </div>
            
            <!-- PWM Section -->
            <div class="section">
                <h2>PWM Configuration</h2>
                <div class="form-group">
                    <div class="checkbox-group">
                        <input type="checkbox" id="enCh1PWM" name="enCh1PWM" %enCh1PWM%>
                        <label for="enCh1PWM">Enable Channel 1</label>
                    </div>
                    <div class="checkbox-group">
                        <input type="checkbox" id="enCh2PWM" name="enCh2PWM" %enCh2PWM%>
                        <label for="enCh2PWM">Enable Channel 2</label>
                    </div>
                    <div class="checkbox-group">
                        <input type="checkbox" id="enCh3PWM" name="enCh3PWM" %enCh3PWM%>
                        <label for="enCh3PWM">Enable Channel 3</label>
                    </div>
                    <div class="checkbox-group">
                        <input type="checkbox" id="enCh4PWM" name="enCh4PWM" %enCh4PWM%>
                        <label for="enCh4PWM">Enable Channel 4</label>
                    </div>
                </div>
                <h3>Channel 1</h3>
                <div class="grid-2">
                    <div class="form-group">
                        <label for="freqCh1PWM">Frequency (Hz)</label>
                        <input type="number" id="freqCh1PWM" name="freqCh1PWM" value="%freqCh1PWM%" min="1" max="40000">
                    </div>
                    <div class="form-group">
                        <label for="dutyCycleCh1PWM">Duty Cycle (%)</label>
                        <input type="number" id="dutyCycleCh1PWM" name="dutyCycleCh1PWM" value="%dutyCycleCh1PWM%" min="0" max="100" step="0.01">
                    </div>
                </div>
                <div class="form-group">
                    <label for="resolutionCh1PWM">Resolution (bits)</label>
                    <input type="number" id="resolutionCh1PWM" name="resolutionCh1PWM" value="%resolutionCh1PWM%" min="1" max="16">
                </div>
                <h3>Channel 2</h3>
                <div class="grid-2">
                    <div class="form-group">
                        <label for="freqCh2PWM">Frequency (Hz)</label>
                        <input type="number" id="freqCh2PWM" name="freqCh2PWM" value="%freqCh2PWM%" min="1" max="40000">
                    </div>
                    <div class="form-group">
                        <label for="dutyCycleCh2PWM">Duty Cycle (%)</label>
                        <input type="number" id="dutyCycleCh2PWM" name="dutyCycleCh2PWM" value="%dutyCycleCh2PWM%" min="0" max="100" step="0.01">
                    </div>
                </div>
                <div class="form-group">
                    <label for="resolutionCh2PWM">Resolution (bits)</label>
                    <input type="number" id="resolutionCh2PWM" name="resolutionCh2PWM" value="%resolutionCh2PWM%" min="1" max="16">
                </div>
                <h3>Channel 3</h3>
                <div class="grid-2">
                    <div class="form-group">
                        <label for="freqCh3PWM">Frequency (Hz)</label>
                        <input type="number" id="freqCh3PWM" name="freqCh3PWM" value="%freqCh3PWM%" min="1" max="40000">
                    </div>
                    <div class="form-group">
                        <label for="dutyCycleCh3PWM">Duty Cycle (%)</label>
                        <input type="number" id="dutyCycleCh3PWM" name="dutyCycleCh3PWM" value="%dutyCycleCh3PWM%" min="0" max="100" step="0.01">
                    </div>
                </div>
                <div class="form-group">
                    <label for="resolutionCh3PWM">Resolution (bits)</label>
                    <input type="number" id="resolutionCh3PWM" name="resolutionCh3PWM" value="%resolutionCh3PWM%" min="1" max="16">
                </div>
                <h3>Channel 4</h3>
                <div class="grid-2">
                    <div class="form-group">
                        <label for="freqCh4PWM">Frequency (Hz)</label>
                        <input type="number" id="freqCh4PWM" name="freqCh4PWM" value="%freqCh4PWM%" min="1" max="40000">
                    </div>
                    <div class="form-group">
                        <label for="dutyCycleCh4PWM">Duty Cycle (%)</label>
                        <input type="number" id="dutyCycleCh4PWM" name="dutyCycleCh4PWM" value="%dutyCycleCh4PWM%" min="0" max="100" step="0.01">
                    </div>
                </div>
                <div class="form-group">
                    <label for="resolutionCh4PWM">Resolution (bits)</label>
                    <input type="number" id="resolutionCh4PWM" name="resolutionCh4PWM" value="%resolutionCh4PWM%" min="1" max="16">
                </div>
            </div>
            
            <!-- LCD Section -->
            <div class="section">
                <h2>LCD Configuration</h2>
                <div class="form-group">
                    <div class="checkbox-group">
                        <input type="checkbox" id="enLCD" name="enLCD" %enLCD%>
                        <label for="enLCD">Enable LCD</label>
                    </div>
                    <div class="checkbox-group">
                        <input type="checkbox" id="enLCDBacklight" name="enLCDBacklight" %enLCDBacklight%>
                        <label for="enLCDBacklight">Enable Backlight</label>
                    </div>
                </div>
                <div class="form-group">
                    <label for="refreshRateLCD">Refresh Rate (ms)</label>
                    <input type="number" id="refreshRateLCD" name="refreshRateLCD" value="%refreshRateLCD%" min="100" step="100">
                </div>
            </div>
            
            <!-- Modbus Section -->
            <div class="section">
                <h2>Modbus RTU 1</h2>
                <div class="form-group">
                    <div class="checkbox-group">
                        <input type="checkbox" id="enMB1" name="enMB1" %enMB1%>
                        <label for="enMB1">Enable Modbus 1</label>
                    </div>
                </div>
                <div class="grid-2">
                    <div class="form-group">
                        <label for="baudRateMB1">Baud Rate</label>
                        <input type="number" id="baudRateMB1" name="baudRateMB1" value="%baudRateMB1%">
                    </div>
                    <div class="form-group">
                        <label for="slaveIDMB1">Slave ID</label>
                        <input type="number" id="slaveIDMB1" name="slaveIDMB1" value="%slaveIDMB1%" min="1" max="247">
                    </div>
                </div>
                <div class="grid-2">
                    <div class="form-group">
                        <label for="functionCodeMB1">Function Code</label>
                        <input type="number" id="functionCodeMB1" name="functionCodeMB1" value="%functionCodeMB1%" min="1" max="4">
                    </div>
                    <div class="form-group">
                        <label for="refreshRateMB1">Refresh Rate (ms)</label>
                        <input type="number" id="refreshRateMB1" name="refreshRateMB1" value="%refreshRateMB1%" min="100" step="100">
                    </div>
                </div>
                <div class="grid-2">
                    <div class="form-group">
                        <label for="startAddressMB1">Start Address</label>
                        <input type="number" id="startAddressMB1" name="startAddressMB1" value="%startAddressMB1%">
                    </div>
                    <div class="form-group">
                        <label for="numRegistersMB1">Number of Registers</label>
                        <input type="number" id="numRegistersMB1" name="numRegistersMB1" value="%numRegistersMB1%" min="1">
                    </div>
                </div>
                <div class="form-group">
                    <label for="sensorNameMB1">Sensor Name</label>
                    <input type="text" id="sensorNameMB1" name="sensorNameMB1" value="%sensorNameMB1%">
                </div>
            </div>
            
            <div class="section">
                <h2>Modbus RTU 2</h2>
                <div class="form-group">
                    <div class="checkbox-group">
                        <input type="checkbox" id="enMB2" name="enMB2" %enMB2%>
                        <label for="enMB2">Enable Modbus 2</label>
                    </div>
                </div>
                <div class="grid-2">
                    <div class="form-group">
                        <label for="baudRateMB2">Baud Rate</label>
                        <input type="number" id="baudRateMB2" name="baudRateMB2" value="%baudRateMB2%">
                    </div>
                    <div class="form-group">
                        <label for="slaveIDMB2">Slave ID</label>
                        <input type="number" id="slaveIDMB2" name="slaveIDMB2" value="%slaveIDMB2%" min="1" max="247">
                    </div>
                </div>
                <div class="grid-2">
                    <div class="form-group">
                        <label for="functionCodeMB2">Function Code</label>
                        <input type="number" id="functionCodeMB2" name="functionCodeMB2" value="%functionCodeMB2%" min="1" max="4">
                    </div>
                    <div class="form-group">
                        <label for="refreshRateMB2">Refresh Rate (ms)</label>
                        <input type="number" id="refreshRateMB2" name="refreshRateMB2" value="%refreshRateMB2%" min="100" step="100">
                    </div>
                </div>
                <div class="grid-2">
                    <div class="form-group">
                        <label for="startAddressMB2">Start Address</label>
                        <input type="number" id="startAddressMB2" name="startAddressMB2" value="%startAddressMB2%">
                    </div>
                    <div class="form-group">
                        <label for="numRegistersMB2">Number of Registers</label>
                        <input type="number" id="numRegistersMB2" name="numRegistersMB2" value="%numRegistersMB2%" min="1">
                    </div>
                </div>
                <div class="form-group">
                    <label for="sensorNameMB2">Sensor Name</label>
                    <input type="text" id="sensorNameMB2" name="sensorNameMB2" value="%sensorNameMB2%">
                </div>
            </div>
            
            <!-- MQTT PUB Section -->
            <div class="section">
                <h2>MQTT Publisher</h2>
                <div class="form-group">
                    <div class="checkbox-group">
                        <input type="checkbox" id="enMQTTPUB" name="enMQTTPUB" %enMQTTPUB%>
                        <label for="enMQTTPUB">Enable MQTT Publisher</label>
                    </div>
                </div>
                <div class="form-group">
                    <label for="mqttBroker">Broker Address</label>
                    <input type="text" id="mqttBroker" name="mqttBroker" value="%mqttBroker%">
                </div>
                <div class="grid-2">
                    <div class="form-group">
                        <label for="mqttPort">Port</label>
                        <input type="number" id="mqttPort" name="mqttPort" value="%mqttPort%">
                    </div>
                    <div class="form-group">
                        <label for="refreshRateMQTTPUB">Refresh Rate (ms)</label>
                        <input type="number" id="refreshRateMQTTPUB" name="refreshRateMQTTPUB" value="%refreshRateMQTTPUB%" min="1000">
                    </div>
                </div>
                <div class="form-group">
                    <label for="mqttClientID">Client ID</label>
                    <input type="text" id="mqttClientID" name="mqttClientID" value="%mqttClientID%">
                </div>
                <div class="form-group">
                    <label for="mqttPubTopic">Publish Topic</label>
                    <input type="text" id="mqttPubTopic" name="mqttPubTopic" value="%mqttPubTopic%">
                </div>
            </div>
            
            <!-- MQTT SUB Section -->
            <div class="section">
                <h2>MQTT Subscriber</h2>
                <div class="form-group">
                    <div class="checkbox-group">
                        <input type="checkbox" id="enMQTTSUB" name="enMQTTSUB" %enMQTTSUB%>
                        <label for="enMQTTSUB">Enable MQTT Subscriber</label>
                    </div>
                </div>
                <div class="form-group">
                    <label for="refreshRateMQTTSUB">Refresh Rate (ms)</label>
                    <input type="number" id="refreshRateMQTTSUB" name="refreshRateMQTTSUB" value="%refreshRateMQTTSUB%" min="1000">
                </div>
                <div class="form-group">
                    <label for="mqttSubTopic">Subscribe Topic</label>
                    <input type="text" id="mqttSubTopic" name="mqttSubTopic" value="%mqttSubTopic%">
                </div>
            </div>
        </div>
        
        <button type="submit" class="btn-save">Save Configuration</button>
    </form>
</body>
</html>
)rawliteral";

	// Thay thế tất cả các placeholder
	// AI
	html.replace("%enCh1AI%", atObject_Param.enCh1AI ? "checked" : "");
	html.replace("%enCh2AI%", atObject_Param.enCh2AI ? "checked" : "");
	html.replace("%enCh3AI%", atObject_Param.enCh3AI ? "checked" : "");
	html.replace("%enCh4AI%", atObject_Param.enCh4AI ? "checked" : "");
	html.replace("%enRawAI%", atObject_Param.enRawAI ? "checked" : "");
	html.replace("%enCurAI%", atObject_Param.enCurAI ? "checked" : "");
	html.replace("%refreshRateAI%", String(atObject_Param.refreshRateAI));

	// DI
	html.replace("%enCh1DI%", atObject_Param.enCh1DI ? "checked" : "");
	html.replace("%enCh2DI%", atObject_Param.enCh2DI ? "checked" : "");
	html.replace("%enCh3DI%", atObject_Param.enCh3DI ? "checked" : "");
	html.replace("%enCh4DI%", atObject_Param.enCh4DI ? "checked" : "");
	html.replace("%refreshRateDI%", String(atObject_Param.refreshRateDI));

	// PWM
	html.replace("%enCh1PWM%", atObject_Param.enCh1PWM ? "checked" : "");
	html.replace("%enCh2PWM%", atObject_Param.enCh2PWM ? "checked" : "");
	html.replace("%enCh3PWM%", atObject_Param.enCh3PWM ? "checked" : "");
	html.replace("%enCh4PWM%", atObject_Param.enCh4PWM ? "checked" : "");
	html.replace("%freqCh1PWM%", String(atObject_Param.freqCh1PWM));
	html.replace("%freqCh2PWM%", String(atObject_Param.freqCh2PWM));
	html.replace("%freqCh3PWM%", String(atObject_Param.freqCh3PWM));
	html.replace("%freqCh4PWM%", String(atObject_Param.freqCh4PWM));
	html.replace("%resolutionCh1PWM%", String(atObject_Param.resolutionCh1PWM));
	html.replace("%resolutionCh2PWM%", String(atObject_Param.resolutionCh2PWM));
	html.replace("%resolutionCh3PWM%", String(atObject_Param.resolutionCh3PWM));
	html.replace("%resolutionCh4PWM%", String(atObject_Param.resolutionCh4PWM));
	html.replace("%dutyCycleCh1PWM%", String(atObject_Param.dutyCycleCh1PWM, 2));
	html.replace("%dutyCycleCh2PWM%", String(atObject_Param.dutyCycleCh2PWM, 2));
	html.replace("%dutyCycleCh3PWM%", String(atObject_Param.dutyCycleCh3PWM, 2));
	html.replace("%dutyCycleCh4PWM%", String(atObject_Param.dutyCycleCh4PWM, 2));

	// LCD
	html.replace("%enLCD%", atObject_Param.enLCD ? "checked" : "");
	html.replace("%enLCDBacklight%", atObject_Param.enLCDBacklight ? "checked" : "");
	html.replace("%refreshRateLCD%", String(atObject_Param.refreshRateLCD));

	// Modbus 1
	html.replace("%enMB1%", atObject_Param.enMB1 ? "checked" : "");
	html.replace("%baudRateMB1%", String(atObject_Param.baudRateMB1));
	html.replace("%slaveIDMB1%", String(atObject_Param.slaveIDMB1));
	html.replace("%functionCodeMB1%", String(atObject_Param.functionCodeMB1));
	html.replace("%startAddressMB1%", String(atObject_Param.startAddressMB1));
	html.replace("%numRegistersMB1%", String(atObject_Param.numRegistersMB1));
	html.replace("%sensorNameMB1%", atObject_Param.sensorNameMB1);
	html.replace("%refreshRateMB1%", String(atObject_Param.refreshRateMB1));

	// Modbus 2
	html.replace("%enMB2%", atObject_Param.enMB2 ? "checked" : "");
	html.replace("%baudRateMB2%", String(atObject_Param.baudRateMB2));
	html.replace("%slaveIDMB2%", String(atObject_Param.slaveIDMB2));
	html.replace("%functionCodeMB2%", String(atObject_Param.functionCodeMB2));
	html.replace("%startAddressMB2%", String(atObject_Param.startAddressMB2));
	html.replace("%numRegistersMB2%", String(atObject_Param.numRegistersMB2));
	html.replace("%sensorNameMB2%", atObject_Param.sensorNameMB2);
	html.replace("%refreshRateMB2%", String(atObject_Param.refreshRateMB2));

	// MQTT PUB
	html.replace("%enMQTTPUB%", atObject_Param.enMQTTPUB ? "checked" : "");
	html.replace("%refreshRateMQTTPUB%", String(atObject_Param.refreshRateMQTTPUB));
	html.replace("%mqttBroker%", atObject_Param.mqttBroker);
	html.replace("%mqttPort%", String(atObject_Param.mqttPort));
	html.replace("%mqttClientID%", atObject_Param.mqttClientID);
	html.replace("%mqttPubTopic%", atObject_Param.mqttPubTopic);

	// MQTT SUB
	html.replace("%enMQTTSUB%", atObject_Param.enMQTTSUB ? "checked" : "");
	html.replace("%refreshRateMQTTSUB%", String(atObject_Param.refreshRateMQTTSUB));
	html.replace("%mqttSubTopic%", atObject_Param.mqttSubTopic);

	server.send(200, "text/html", html);
}

void App_AP::handleSave()
{
	// AI channels
	atObject_Param.enCh1AI = server.hasArg("enCh1AI");
	atObject_Param.enCh2AI = server.hasArg("enCh2AI");
	atObject_Param.enCh3AI = server.hasArg("enCh3AI");
	atObject_Param.enCh4AI = server.hasArg("enCh4AI");
	atObject_Param.enRawAI = server.hasArg("enRawAI");
	atObject_Param.enCurAI = server.hasArg("enCurAI");
	atObject_Param.refreshRateAI = server.arg("refreshRateAI").toInt();

	// DI channels
	atObject_Param.enCh1DI = server.hasArg("enCh1DI");
	atObject_Param.enCh2DI = server.hasArg("enCh2DI");
	atObject_Param.enCh3DI = server.hasArg("enCh3DI");
	atObject_Param.enCh4DI = server.hasArg("enCh4DI");
	atObject_Param.refreshRateDI = server.arg("refreshRateDI").toInt();

	// PWM channels
	atObject_Param.enCh1PWM = server.hasArg("enCh1PWM");
	atObject_Param.enCh2PWM = server.hasArg("enCh2PWM");
	atObject_Param.enCh3PWM = server.hasArg("enCh3PWM");
	atObject_Param.enCh4PWM = server.hasArg("enCh4PWM");
	atObject_Param.freqCh1PWM = server.arg("freqCh1PWM").toInt();
	atObject_Param.freqCh2PWM = server.arg("freqCh2PWM").toInt();
	atObject_Param.freqCh3PWM = server.arg("freqCh3PWM").toInt();
	atObject_Param.freqCh4PWM = server.arg("freqCh4PWM").toInt();
	atObject_Param.resolutionCh1PWM = server.arg("resolutionCh1PWM").toInt();
	atObject_Param.resolutionCh2PWM = server.arg("resolutionCh2PWM").toInt();
	atObject_Param.resolutionCh3PWM = server.arg("resolutionCh3PWM").toInt();
	atObject_Param.resolutionCh4PWM = server.arg("resolutionCh4PWM").toInt();
	atObject_Param.dutyCycleCh1PWM = server.arg("dutyCycleCh1PWM").toFloat();
	atObject_Param.dutyCycleCh2PWM = server.arg("dutyCycleCh2PWM").toFloat();
	atObject_Param.dutyCycleCh3PWM = server.arg("dutyCycleCh3PWM").toFloat();
	atObject_Param.dutyCycleCh4PWM = server.arg("dutyCycleCh4PWM").toFloat();

	// LCD
	atObject_Param.enLCD = server.hasArg("enLCD");
	atObject_Param.enLCDBacklight = server.hasArg("enLCDBacklight");
	atObject_Param.refreshRateLCD = server.arg("refreshRateLCD").toInt();

	// Modbus RTU
	atObject_Param.enMB1 = server.hasArg("enMB1");
	atObject_Param.enMB2 = server.hasArg("enMB2");
	atObject_Param.baudRateMB1 = server.arg("baudRateMB1").toInt();
	atObject_Param.baudRateMB2 = server.arg("baudRateMB2").toInt();
	atObject_Param.slaveIDMB1 = server.arg("slaveIDMB1").toInt();
	atObject_Param.slaveIDMB2 = server.arg("slaveIDMB2").toInt();
	atObject_Param.functionCodeMB1 = server.arg("functionCodeMB1").toInt();
	atObject_Param.functionCodeMB2 = server.arg("functionCodeMB2").toInt();
	atObject_Param.startAddressMB1 = server.arg("startAddressMB1").toInt();
	atObject_Param.startAddressMB2 = server.arg("startAddressMB2").toInt();
	atObject_Param.numRegistersMB1 = server.arg("numRegistersMB1").toInt();
	atObject_Param.numRegistersMB2 = server.arg("numRegistersMB2").toInt();
	atObject_Param.sensorNameMB1 = server.arg("sensorNameMB1");
	atObject_Param.sensorNameMB2 = server.arg("sensorNameMB2");
	atObject_Param.refreshRateMB1 = server.arg("refreshRateMB1").toInt();
	atObject_Param.refreshRateMB2 = server.arg("refreshRateMB2").toInt();

	// MQTT_PUB
	atObject_Param.enMQTTPUB = server.hasArg("enMQTTPUB");
	atObject_Param.refreshRateMQTTPUB = server.arg("refreshRateMQTTPUB").toInt();
	atObject_Param.mqttBroker = server.arg("mqttBroker");
	atObject_Param.mqttPort = server.arg("mqttPort").toInt();
	atObject_Param.mqttClientID = server.arg("mqttClientID");
	atObject_Param.mqttPubTopic = server.arg("mqttPubTopic");

	// MQTT_SUB
	atObject_Param.enMQTTSUB = server.hasArg("enMQTTSUB");
	atObject_Param.refreshRateMQTTSUB = server.arg("refreshRateMQTTSUB").toInt();
	atObject_Param.mqttSubTopic = server.arg("mqttSubTopic");

	// Lưu cấu hình
	atApp_AP.saveConfig();

	// Trả về thông báo
	server.send(200, "text/plain", "Configuration saved successfully. Device will restart in 2 seconds.");
	vTaskDelay(2000 / portTICK_PERIOD_MS);
	ESP.restart();
}
/**
 * Pend to start is the first task of this application it will do prerequisite condition. In the debit mode, task will send information of application to terminal to start the application.
 */
void App_AP::App_AP_Pend()
{
	// atService_XYZ.Debug();
}
/**
 * This start function will init some critical function
 */
void App_AP::App_AP_Start()
{
	// Khởi tạo giá trị mặc định
	atApp_AP.setDefaultConfig();

	// Khởi tạo AP
	WiFi.softAP("ESP32-S3-Config", "12345678");
	if (atApp_AP.User_Mode == APP_USER_MODE_DEBUG)
	{
		Serial.println("AP Started");
		Serial.print("IP: ");
		Serial.println(WiFi.softAPIP());
	}

	// Load cấu hình từ Flash (nếu có)
	atApp_AP.loadConfig();

	// Xử lý web server
	server.on("/", HTTP_GET, atApp_AP.handleRoot);
	server.on("/save", HTTP_POST, atApp_AP.handleSave);
	server.begin();
	if (atApp_AP.User_Mode == APP_USER_MODE_DEBUG)
	{
		Serial.println("HTTP server started");
	}
}
/**
 * Restart function of SNM  app
 */
void App_AP::App_AP_Restart()
{
}
/**
 * Execute fuction of SNM app
 */
void App_AP::App_AP_Execute()
{
	server.handleClient();
}
void App_AP::App_AP_Suspend() {}
void App_AP::App_AP_Resume() {}
void App_AP::App_AP_End() {}
void atApp_AP_Task_Func(void *parameter)
{
	while (1)
	{
		atApp_AP.Run_Application(APP_RUN_MODE_AUTO);
		// vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}
#endif