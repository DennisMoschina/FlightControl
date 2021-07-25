#ifndef _OTA_H
#define _OTA_H

#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#include <NetworkCredentials.h>

void startOTA() {
    log_i("Booting");
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    while (WiFi.waitForConnectResult() != WL_CONNECTED) {
        log_e("Connection Failed! Rebooting...");
        delay(5000);
        ESP.restart();
    }

    ArduinoOTA
        .onStart([]() {
            String type = ArduinoOTA.getCommand() == U_FLASH ? "sketch" : "filesystem";
            log_i("Start updating %s", type);
        })
        .onEnd([]() {
            log_i("\nEnd");
        })
        .onProgress([](unsigned int progress, unsigned int total) {
            log_i("Progress: %u%%\r", (progress / (total / 100)));
        })
        .onError([](ota_error_t error) {
            log_e("Error[%u]: ", error);
            if (error == OTA_AUTH_ERROR) log_e("Auth Failed");
            else if (error == OTA_BEGIN_ERROR) log_e("Begin Failed");
            else if (error == OTA_CONNECT_ERROR) log_e("Connect Failed");
            else if (error == OTA_RECEIVE_ERROR) log_e("Receive Failed");
            else if (error == OTA_END_ERROR) log_e("End Failed");
        });

    ArduinoOTA.begin();

    log_i("Ready");
    log_i("IP address: ");
    Serial.println(WiFi.localIP());
}

#endif