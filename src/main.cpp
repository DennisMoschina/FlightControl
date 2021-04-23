#include <Arduino.h>

#include <map>
#include <Wire.h>

#include <MPU6050.h>

MPU6050 mpu = MPU6050();

void setup() {
    Serial.begin(115200);

    mpu.begin();
}

void loop() {
    // RawAxisData gyroReadings = mpu.readGyro();
    RotationData gyroReadings = mpu.getRotation();
    RawAxisData accelReadings = mpu.readAccel();
    // Serial.printf("Gyro\tx: %d, y: %d, z: %d\n", gyroReadings.x, gyroReadings.y, gyroReadings.z);
    Serial.printf("Gyro\tx: %f, y: %f, z: %f\n", gyroReadings.x, gyroReadings.y, gyroReadings.z);
    Serial.printf("Accel\tx: %d, y: %d, z: %d\n", accelReadings.x, accelReadings.y, accelReadings.z);
    Serial.println("=====================================================");
    delay(500);
}
