#include <Arduino.h>
#include <init.h>

void setup() {
    Serial.begin(115200);

    assign();
    configure();
    startGyro();
    startReceiver();
    startServos();
    controller->begin();
}

void loop() {}
