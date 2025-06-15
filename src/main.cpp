// Template_Application_ESP32_V2.0
#include "../src/apps/atApp_MQTT_PUB.h"
#include "../src/apps/atApp_MQTT_SUB.h"
#include "../src/apps/atApp_FTP.h"
#include "../src/apps/atApp_ADC.h"
// #include "../src/apps/atApp_LED.h"

void setup()
{
  Serial.begin(115200);
  vTaskDelay(100 / portTICK_PERIOD_MS);
  Serial.printf("Flash size : %f\n", ESP.getFlashChipSize());

  // Uncomment to put the app in debug mode
  // atApp_MQTT.Debug();
  // atApp_ADC.Debug();
  // Uncomment to put the service in debug mode
  atService_EG800K.Debug();
  atService_ADS1115.Debug();

  // --------------------------------------------Tasks table--------------------------------------------//
  // ---------------------------------------------------------------------------------------------------//
  // || Creation  ||  Task function ||  PC name ||  Heap size ||  Parameter ||  Priority  ||  Task handle ||  CoreID  ||
  xTaskCreatePinnedToCore(atApp_ADC_Task_Func, "atApp_ADC_Application", 2048, NULL, 1, &Task_atApp_ADC, 1);
  xTaskCreatePinnedToCore(atApp_MQTT_PUB_Task_Func, "atApp_MQTT_PUB_Application", 2048, NULL, 1, &Task_atApp_MQTT_PUB, 1);
  // xTaskCreatePinnedToCore(atApp_MQTT_SUB_Task_Func, "atApp_MQTT_SUB_Application", 2048, NULL, 1, &Task_atApp_MQTT_SUB, 1);
  // xTaskCreatePinnedToCore(atApp_FTP_Task_Func, "atApp_FTP_Application", 2048, NULL, 1, &Task_atApp_FTP, 1);
  // xTaskCreatePinnedToCore(atApp_LED_Task_Func, "atApp_LED_Application", 2048, NULL, 1, &Task_atApp_LED, 1);

  //------------------------------------------------------------------------------------------------------------------------------------------------------------------//

  // Some tasks will be suspended after initiating
  // vTaskSuspend(Task_atApp_ABC);
}
void loop()
{
  vTaskSuspend(NULL); // suspend the main loop
}
