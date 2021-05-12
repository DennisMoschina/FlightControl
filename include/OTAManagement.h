#ifndef _OTA_MANAGEMENT_H
#define _OTA_MANAGEMENT_H

#include <Arduino.h>

#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#include <WiFiResources.h>

#define OTA_LOG "ota"

TaskHandle_t otaHandler;

void handleOTA(void * parameter) {
    for (;;) {
        ArduinoOTA.handle();
        delay(100);
    }
}

void setupOTA(void * parameter) {
    ESP_LOGI("Booting");
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    while (WiFi.waitForConnectResult() != WL_CONNECTED) {
        ESP_LOGE(OTA_LOG, "Connection Failed! Rebooting...");
        delay(1000);
        ESP.restart();
    }

    ArduinoOTA
    .onStart([]() {
        String type = ArduinoOTA.getCommand() == U_FLASH ? "sketch" : "filesystem";

        // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
        ESP_LOGD(OTA_LOG, "Start updating %s", type);
    })
    .onEnd([]() {
        ESP_LOGI(OTA_LOG, "\nEnd");
    })
    .onProgress([] (unsigned int progress, unsigned int total) {
        ESP_LOGI(OTA_LOG, "Progress: %u%%\r", (progress / (total / 100)));
    })
    .onError([](ota_error_t error) {
        ESP_LOGE(OTA_LOG, "Error[%u]: ", error);

        const char* errorMsg;
        if (error == OTA_AUTH_ERROR)            errorMsg = "Auth Failed";
        else if (error == OTA_BEGIN_ERROR)      errorMsg = "Begin Failed";
        else if (error == OTA_CONNECT_ERROR)    errorMsg = "Connect Failed";
        else if (error == OTA_RECEIVE_ERROR)    errorMsg = "Receive Failed";
        else if (error == OTA_END_ERROR)        errorMsg = "End Failed";

        ESP_LOGE(OTA_LOG, "%s", errorMsg);
    });

    ArduinoOTA.begin();

    ESP_LOGD(OTA_LOG, "Ready");
    ESP_LOGI(OTA_LOG, "IP address: %s", WiFi.localIP().toString().c_str());

    vTaskDelete(NULL);
}

void startOTA() {
    TaskHandle_t otaSetupHandle;

    //todo use correct stack size
    xTaskCreatePinnedToCore(setupOTA,
        "setup OTA",
        10000,
        NULL,
        0,
        &otaSetupHandle,
        0);

    xTaskCreatePinnedToCore(
      handleOTA, /* Function to implement the task */
      "otaHandler", /* Name of the task */
      10000,  /* Stack size in words */
      NULL,  /* Task input parameter */
      0,  /* Priority of the task */
      &otaHandler,  /* Task handle. */
      0); /* Core where the task should run */
}

#endif
