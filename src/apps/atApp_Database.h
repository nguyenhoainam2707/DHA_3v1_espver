#ifndef _Application_atApp_Database_
#define _Application_atApp_Database_
/* _____PROJECT INCLUDES____________________________________________________ */
#include "App.h"
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

	bool beginFlash(const char *namespace_ = "cfg");
	void saveInt(const char *key, int32_t value);
	int32_t loadInt(const char *key, int32_t defaultValue = 0);
	void saveFloat(const char *key, float value);
	float loadFloat(const char *key, float defaultValue = 0.0f);
	void saveString(const char *key, const String &value);
	String loadString(const char *key, const char *defaultValue = "");
	void clear();

	bool beginSD();
	bool writeData(const char *sensorType, const String &dataLine);
	String readData(const char *sensorType, const char *date);

protected:
private:
	static void App_Database_Pend();
	static void App_Database_Start();
	static void App_Database_Restart();
	static void App_Database_Execute();
	static void App_Database_Suspend();
	static void App_Database_Resume();
	static void App_Database_End();

	Preferences prefs;
	
	String getDirectory(const char* sensorType);
    String getFilePath(const char* sensorType, const char* date);

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
	// atService_XYZ.Run_Service();
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
	if (atApp_Database.User_Mode == APP_USER_MODE_DEBUG)
	{
	}
}
void App_Database::App_Database_Suspend() {}
void App_Database::App_Database_Resume() {}
void App_Database::App_Database_End() {}
bool App_Database::beginFlash(const char *namespace_)
{
	return prefs.begin(namespace_, false);
}

void App_Database::saveInt(const char *key, int32_t value)
{
	prefs.putInt(key, value);
}

int32_t App_Database::loadInt(const char *key, int32_t defaultValue)
{
	return prefs.getInt(key, defaultValue);
}

void App_Database::saveFloat(const char *key, float value)
{
	prefs.putFloat(key, value);
}

float App_Database::loadFloat(const char *key, float defaultValue)
{
	return prefs.getFloat(key, defaultValue);
}

void App_Database::saveString(const char *key, const String &value)
{
	prefs.putString(key, value);
}

String App_Database::loadString(const char *key, const char *defaultValue)
{
	return prefs.getString(key, defaultValue);
}

void App_Database::clear()
{
	prefs.clear();
}

// For SD card operations
bool App_Database::beginSD()
{
	// Configure SDIO pins explicitly
	SD_MMC.setPins(SD_CLK_PIN, SD_CMD_PIN, SD_D0_PIN, SD_D1_PIN, SD_D2_PIN, SD_D3_PIN);

	if (!SD_MMC.begin("/sdcard", true))
	{
		Serial.println("SD_MMC Mount Failed");
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
	String path = getFilePath(sensorType, buf);
	File file = SD_MMC.open(path, FILE_APPEND);
	if (!file)
	{
		Serial.println("Failed to open file for appending: " + path);
		return false;
	}
	file.println(dataLine);
	file.close();
	return true;
}

String App_Database::readData(const char *sensorType, const char *date)
{
	String path = getFilePath(sensorType, date);
	File file = SD_MMC.open(path);
	if (!file)
	{
		Serial.println("Failed to open file for reading: " + path);
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

void atApp_Database_Task_Func(void *parameter)
{
	while (1)
	{
		atApp_Database.Run_Application(APP_RUN_MODE_AUTO);
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}
#endif