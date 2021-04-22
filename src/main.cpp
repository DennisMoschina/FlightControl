#include <Arduino.h>

#include <map>
#include <Wire.h>

#define MPU_ADDR 0x68
#define POWER_MANAGEMENT_REGISTER 0x6B
#define GYRO_CONFIG_REGISTER 0x1B
#define ACCELEROMETER_CONFIG_REGISTER 0x1C

#define GYRO_READING_REGISTER 0x43
#define GYRO_REGISTER_SIZE 6

#define X "x"
#define Y "y"
#define Z "z"

using GyroData = std::map<String, int>;

void beginMPU() {
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(POWER_MANAGEMENT_REGISTER);
    Wire.write(0);
    Wire.endTransmission();

    Wire.beginTransmission(MPU_ADDR);
    Wire.write(GYRO_CONFIG_REGISTER);
    Wire.write(0);
    Wire.endTransmission();

    Wire.beginTransmission(MPU_ADDR);
    Wire.write(ACCELEROMETER_CONFIG_REGISTER);
    Wire.write(0);
    Wire.endTransmission();
}

GyroData readGyro() {
    GyroData gyroReadings;
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(GYRO_READING_REGISTER);
    Wire.endTransmission();
    Wire.requestFrom(MPU_ADDR, GYRO_REGISTER_SIZE);

    while (Wire.available() < 6);
    gyroReadings[X] = Wire.read() << 8 | Wire.read();
    gyroReadings[Y] = Wire.read() << 8 | Wire.read();
    gyroReadings[Z] = Wire.read() << 8 | Wire.read();
    return gyroReadings;
}

void setup() {
    Serial.begin(115200);
    Wire.begin(21, 22);

    beginMPU();
}

void loop() {
    GyroData gyroReadings = readGyro();
    String output;
    GyroData::iterator iterator = gyroReadings.begin();
    while (iterator != gyroReadings.end()) {
        output += iterator->first + ":" + iterator->second + " ";
        iterator++;
    }
    output += "\n";
    Serial.print(output);
    delay(500);
}
