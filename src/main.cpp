#include <Arduino.h>

#include <map>
#include <Wire.h>

#include <MPU6050.h>

MPU6050 mpu = MPU6050();

String mapToString(AxisData map) {
    String output;
    AxisData::iterator iterator = map.begin();
    while (iterator != map.end()) {
        output += iterator->first;
        output += ": ";
        output += iterator->second;
        output += " ";
        iterator++;
    }
    output += "\n";
    return output;
}

void setup() {
    Serial.begin(115200);

    mpu.begin();
}

void loop() {
    AxisData gyroReadings = mpu.readGyro();
    Serial.print(mapToString(gyroReadings));
    delay(500);
}
