#ifndef _Application_atApp_Database_
#define _Application_atApp_Database_
/* _____PROJECT INCLUDES____________________________________________________ */
#include "App.h"
#include "../src/obj/atObj_Param.h"
#include "../src/obj/atObj_Data.h"
#include "../src/services/memory/atService_Flash.h"
#include "../src/services/memory/atService_uSD.h"
#include <TimeLib.h>
#include <Preferences.h>
#include <FS.h>
#include <SD_MMC.h>
#include <stdint.h>
// #include "../services/atService_XYZ.h"
/* _____DEFINITIONS__________________________________________________________ */
#define SD_CLK_PIN 13 // CLK
#define SD_CMD_PIN 12 // CMD
#define SD_D0_PIN 14  // D0
#define SD_D1_PIN 21  // D1
#define SD_D2_PIN 10  // D2
#define SD_D3_PIN 11  // D3
/* _____GLOBAL VARIABLES_____________________________________________________ */
TaskHandle_t Task_atApp_Database;
void atApp_Database_Task_Func(void *parameter);
///////////////////////////////////////////////Testing part//
/* _____GLOBAL FUNCTION______________________________________________________ */

/* _____CLASS DEFINITION_____________________________________________________ */

/**
 * This Application class is the application to manage the
 */
class App_Database : public Application
{
public:
	App_Database();
	~App_Database();

	// static bool beginFlash(const char *namespace_ = "cfg");
	// static void saveInt(const char *key, int32_t value);
	// static int32_t loadInt(const char *key, int32_t defaultValue = 0);
	// static void saveFloat(const char *key, float value);
	// static float loadFloat(const char *key, float defaultValue = 0.0f);
	// static void saveString(const char *key, const String &value);
	// static String loadString(const char *key, const char *defaultValue = "");
	// static void clear();

	static bool beginSD();
	static bool writeData(const char *sensorType, const String &dataLine);
	static String readData(const char *sensorType, const char *date);

	void loadConfig();
	void saveConfig();

protected:
private:
	static void App_Database_Pend();
	static void App_Database_Start();
	static void App_Database_Restart();
	static void App_Database_Execute();
	static void App_Database_Suspend();
	static void App_Database_Resume();
	static void App_Database_End();

	Preferences preferences;

	String getDirectory(const char *sensorType);
	String getFilePath(const char *sensorType, const char *date);

} atApp_Database;
/**
 * This function will be automaticaly called when a object is created by this class
 */
App_Database::App_Database(/* args */)
{
	_Pend_User = *App_Database_Pend;
	_Start_User = *App_Database_Start;
	_Restart_User = *App_Database_Restart;
	_Execute_User = *App_Database_Execute;
	_Suspend_User = *App_Database_Suspend;
	_Resume_User = *App_Database_Resume;
	_End_User = *App_Database_End;

	// change the ID of application
	ID_Application = 1;
	// change the application name
	Name_Application = (char *)"Database Application	";
	// change the ID of SNM
}
/**
 * This function will be automaticaly called when the object of class is delete
 */
App_Database::~App_Database()
{
}
/**
 * Pend to start is the first task of this application it will do prerequisite condition. In the debit mode, task will send information of application to terminal to start the application.
 */
void App_Database::App_Database_Pend()
{
	// atService_XYZ.Debug();
}
/**
 * This start function will init some critical function
 */
void App_Database::App_Database_Start()
{
	// init atXYZ Service in the fist running time
	// atService_Flash.Run_Service();
	// atService_uSD.Run_Service();
	atApp_Database.loadConfig();
	if (atApp_Database.User_Mode == APP_USER_MODE_DEBUG)
	{
		Serial.println("App_Database started");
	}
}
/**
 * Restart function of SNM  app
 */
void App_Database::App_Database_Restart()
{
}
/**
 * Execute fuction of SNM app
 */
void App_Database::App_Database_Execute()
{
	// atService_XYZ.Run_Service();
	// if (atApp_Database.User_Mode == APP_USER_MODE_DEBUG)
	// {
	// }
}
void App_Database::App_Database_Suspend() {}
void App_Database::App_Database_Resume() {}
void App_Database::App_Database_End() {}

// For SD card operations
bool App_Database::beginSD()
{
	// Configure SDIO pins explicitly
	SD_MMC.setPins(SD_CLK_PIN, SD_CMD_PIN, SD_D0_PIN, SD_D1_PIN, SD_D2_PIN, SD_D3_PIN);

	if (!SD_MMC.begin("/sdcard", true))
	{
		if (atApp_Database.User_Mode == APP_USER_MODE_DEBUG)
		{
			Serial.println("SD_MMC Mount Failed");
		}
		return false;
	}
	return true;
}

String App_Database::getDirectory(const char *sensorType)
{
	String dir = "/" + String(sensorType);
	if (!SD_MMC.exists(dir))
	{
		SD_MMC.mkdir(dir);
	}
	return dir;
}

String App_Database::getFilePath(const char *sensorType, const char *date)
{
	String dir = getDirectory(sensorType);
	String file = String(date) + ".csv";
	return dir + "/" + file;
}

bool App_Database::writeData(const char *sensorType, const String &dataLine)
{
	// Generate date string DD/MM/YYYY
	char buf[9];
	snprintf(buf, sizeof(buf), "%02d%02d%04d", day(), month(), year());
	String path = atApp_Database.getFilePath(sensorType, buf);
	File file = SD_MMC.open(path, FILE_APPEND);
	if (!file)
	{
		if (atApp_Database.User_Mode == APP_USER_MODE_DEBUG)
		{
			Serial.println("Failed to open file for appending: " + path);
		}
		return false;
	}
	file.println(dataLine);
	file.close();
	return true;
}

String App_Database::readData(const char *sensorType, const char *date)
{
	String path = atApp_Database.getFilePath(sensorType, date);
	File file = SD_MMC.open(path);
	if (!file)
	{
		if( atApp_Database.User_Mode == APP_USER_MODE_DEBUG)
		{
			Serial.println("Failed to open file for reading: " + path);
		}
		return String();
	}
	String content;
	while (file.available())
	{
		content += file.readStringUntil('\n') + "\n";
	}
	file.close();
	return content;
}

void App_Database::loadConfig()
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

void App_Database::saveConfig()
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
void atApp_Database_Task_Func(void *parameter)
{
	while (1)
	{
		atApp_Database.Run_Application(APP_RUN_MODE_AUTO);
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}
#endif
// void App_Database::setDefaultConfig()
// {
// 	// AI channels
// 	atObject_Param.enCh1AI = true;
// 	atObject_Param.enCh2AI = true;
// 	atObject_Param.enCh3AI = true;
// 	atObject_Param.enCh4AI = true;
// 	atObject_Param.enRawAI = true;
// 	atObject_Param.enCurAI = true;
// 	atObject_Param.refreshRateAI = 1000;

// 	// DI channels
// 	atObject_Param.enCh1DI = false;
// 	atObject_Param.enCh2DI = false;
// 	atObject_Param.enCh3DI = false;
// 	atObject_Param.enCh4DI = false;
// 	atObject_Param.refreshRateDI = 1000;

// 	// PWM channels
// 	atObject_Param.enCh1PWM = false;
// 	atObject_Param.enCh2PWM = false;
// 	atObject_Param.enCh3PWM = false;
// 	atObject_Param.enCh4PWM = false;
// 	atObject_Param.freqCh1PWM = 5000;
// 	atObject_Param.freqCh2PWM = 5000;
// 	atObject_Param.freqCh3PWM = 5000;
// 	atObject_Param.freqCh4PWM = 5000;
// 	atObject_Param.resolutionCh1PWM = 8;
// 	atObject_Param.resolutionCh2PWM = 8;
// 	atObject_Param.resolutionCh3PWM = 8;
// 	atObject_Param.resolutionCh4PWM = 8;
// 	atObject_Param.dutyCycleCh1PWM = 50.00;
// 	atObject_Param.dutyCycleCh2PWM = 50.00;
// 	atObject_Param.dutyCycleCh3PWM = 50.00;
// 	atObject_Param.dutyCycleCh4PWM = 50.00;

// 	// LCD
// 	atObject_Param.enLCD = false;
// 	atObject_Param.enLCDBacklight = true;
// 	atObject_Param.refreshRateLCD = 500;

// 	// Modbus RTU
// 	atObject_Param.enMB1 = false;
// 	atObject_Param.enMB2 = false;
// 	atObject_Param.baudRateMB1 = 9600;
// 	atObject_Param.baudRateMB2 = 9600;
// 	atObject_Param.slaveIDMB1 = 1;
// 	atObject_Param.slaveIDMB2 = 1;
// 	atObject_Param.functionCodeMB1 = 3;
// 	atObject_Param.functionCodeMB2 = 3;
// 	atObject_Param.startAddressMB1 = 0;
// 	atObject_Param.startAddressMB2 = 0;
// 	atObject_Param.numRegistersMB1 = 1;
// 	atObject_Param.numRegistersMB2 = 1;
// 	atObject_Param.sensorNameMB1 = "Sensor 1";
// 	atObject_Param.sensorNameMB2 = "Sensor 2";
// 	atObject_Param.refreshRateMB1 = 1000;
// 	atObject_Param.refreshRateMB2 = 1000;

// 	// MQTT_PUB
// 	atObject_Param.enMQTTPUB = true;
// 	atObject_Param.refreshRateMQTTPUB = 5000;
// 	atObject_Param.mqttBroker = "broker.emqx.io";
// 	atObject_Param.mqttPort = 1883;
// 	atObject_Param.mqttClientID = "esp32s3-client";
// 	atObject_Param.mqttPubTopic = "esp32s3/data";

// 	// MQTT_SUB
// 	atObject_Param.enMQTTSUB = false;
// 	atObject_Param.refreshRateMQTTSUB = 5000;
// 	atObject_Param.mqttSubTopic = "esp32s3/command";
// }

// bool App_Database::beginFlash(const char *namespace_)
// {
// 	return prefs.begin(namespace_, false);
// }

// void App_Database::saveInt(const char *key, int32_t value)
// {
// 	prefs.putInt(key, value);
// }

// int32_t App_Database::loadInt(const char *key, int32_t defaultValue)
// {
// 	return prefs.getInt(key, defaultValue);
// }

// void App_Database::saveFloat(const char *key, float value)
// {
// 	prefs.putFloat(key, value);
// }

// float App_Database::loadFloat(const char *key, float defaultValue)
// {
// 	return prefs.getFloat(key, defaultValue);
// }

// void App_Database::saveString(const char *key, const String &value)
// {
// 	prefs.putString(key, value);
// }

// String App_Database::loadString(const char *key, const char *defaultValue)
// {
// 	return prefs.getString(key, defaultValue);
// }

// void App_Database::clear()
// {
// 	prefs.clear();
// }