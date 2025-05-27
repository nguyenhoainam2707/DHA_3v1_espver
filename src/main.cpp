// Template_Application_ESP32_V2.0
// #include <Arduino.h>
#include "../src/apps/atApp_ABC.h"
#include "../src/apps/atApp_MQTT.h"
#include "../src/apps/atApp_ADC.h"

void setup()
{
  Serial.begin(115200);
  vTaskDelay(100 / portTICK_PERIOD_MS);
  Serial.printf("Flash size : %f\n", ESP.getFlashChipSize());

  // Uncomment to put the app in debug mode
  // atApp_ABC.Debug();
  // atApp_MQTT.Debug();
  atApp_ADC.Debug();
  // Uncomment to put the service in debug mode
  // atService_EG800K.Debug();
  atService_ADS1115.Debug();

  // --------------------------------------------Tasks table--------------------------------------------//
  // ---------------------------------------------------------------------------------------------------//
  // || Creation  ||  Task function ||  PC name ||  Heap size ||  Parameter ||  Priority  ||  Task handle ||  CoreID  ||
  // xTaskCreatePinnedToCore(atApp_ABC_Task_Func, "atApp_ABC_Application", 2048, NULL, 1, &Task_atApp_ABC, 1);
  xTaskCreatePinnedToCore(atApp_MQTT_Task_Func, "atApp_MQTT_Application", 2048, NULL, 1, &Task_atApp_MQTT, 1);
  xTaskCreatePinnedToCore(atApp_ADC_Task_Func, "atApp_ADC_Application", 2048, NULL, 1, &Task_atApp_ADC, 1);
  //------------------------------------------------------------------------------------------------------------------------------------------------------------------//

  // Some tasks will be suspended after initiating
  // vTaskSuspend(Task_atApp_ABC);
}
void loop()
{
  vTaskSuspend(NULL); // suspend the main loop
}
