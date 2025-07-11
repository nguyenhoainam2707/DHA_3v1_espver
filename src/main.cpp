// #define RX0_EG800K 44
// #define TX0_EG800K 43
// #define RX1_MB1 18
// #define TX1_MB1 17
// #define RX2_MB2 4
// #define TX2_MB2 5
// #define SDA_PIN 48
// #define SCL_PIN 45


#include <Wire.h>
#include "../src/apps/atApp_MQTT_PUB.h"
#include "../src/apps/atApp_MQTT_SUB.h"
#include "../src/apps/atApp_FTP.h"
#include "../src/apps/atApp_ADC.h"
#include "../src/apps/atApp_AP.h"
#include "../src/apps/atApp_CP.h"
#include "../src/apps/atApp_Database.h"
#include "../src/apps/atApp_DI.h"
#include "../src/apps/atApp_GPS.h"
#include "../src/apps/atApp_LED.h"
#include "../src/apps/atApp_MB.h"
#include "../src/apps/atApp_PWM.h"

void setup()
{
  Serial.begin(115200);
  vTaskDelay(2000 / portTICK_PERIOD_MS);
  Serial.printf("Flash size : %f\n", ESP.getFlashChipSize());

  // Uncomment to put the app in debug mode
  // atApp_MQTT_PUB.Debug();
  // atApp_MQTT_SUB.Debug();
  // atApp_FTP.Debug();
  // atApp_ADC.Debug();
  // atApp_AP.Debug();
  // atApp_CP.Debug();
  // atApp_Database.Debug();
  atApp_DI.Debug();
  // atApp_GPS.Debug();
  // atApp_LED.Debug();
  // atApp_MB.Debug();
  // atApp_PWM.Debug();
  // Uncomment to put the service in debug mode
  // atService_EG800K.Debug();
  // atService_ADS1115.Debug();
  atService_PCF8574.Debug();
  // atService_Modbus.Debug();

  // --------------------------------------------Tasks table--------------------------------------------//
  // ---------------------------------------------------------------------------------------------------//
  // || Creation  ||  Task function ||  PC name ||  Heap size ||  Parameter ||  Priority  ||  Task handle ||  CoreID  ||
  // xTaskCreatePinnedToCore(atApp_CP_Task_Func, "atApp_CP_Application", 2048, NULL, 1, &Task_atApp_CP, 1);
  // xTaskCreatePinnedToCore(atApp_MQTT_PUB_Task_Func, "atApp_MQTT_PUB_Application", 2048, NULL, 1, &Task_atApp_MQTT_PUB, 1);
  // xTaskCreatePinnedToCore(atApp_MQTT_SUB_Task_Func, "atApp_MQTT_SUB_Application", 2048, NULL, 1, &Task_atApp_MQTT_SUB, 1);
  // xTaskCreatePinnedToCore(atApp_FTP_Task_Func, "atApp_FTP_Application", 2048, NULL, 1, &Task_atApp_FTP, 1);
  // xTaskCreatePinnedToCore(atApp_AP_Task_Func, "atApp_AP_Application", 2048, NULL, 1, &Task_atApp_AP, 1);
  // xTaskCreatePinnedToCore(atApp_ADC_Task_Func, "atApp_ADC_Application", 2048, NULL, 1, &Task_atApp_ADC, 1);
  // xTaskCreatePinnedToCore(atApp_Database_Task_Func, "atApp_Database_Application", 2048, NULL, 1, &Task_atApp_Database, 1);
  xTaskCreatePinnedToCore(atApp_DI_Task_Func, "atApp_DI_Application", 2048, NULL, 1, &Task_atApp_DI, 1);
  // xTaskCreatePinnedToCore(atApp_GPS_Task_Func, "atApp_GPS_Application", 2048, NULL, 1, &Task_atApp_GPS, 1);
  // xTaskCreatePinnedToCore(atApp_LED_Task_Func, "atApp_LED_Application", 2048, NULL, 1, &Task_atApp_LED, 1);
  // xTaskCreatePinnedToCore(atApp_MB_Task_Func, "atApp_MB_Application", 2048, NULL, 1, &Task_atApp_MB, 1);
  // xTaskCreatePinnedToCore(atApp_PWM_Task_Func, "atApp_PWM_Application", 2048, NULL, 1, &Task_atApp_PWM, 1);

  //------------------------------------------------------------------------------------------------------------------------------------------------------------------//

  // Some tasks will be suspended after initiating
  // vTaskSuspend(Task_atApp_ABC);
}
void loop()
{
  vTaskDelete(NULL); // Delete the main loop
}
