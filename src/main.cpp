#include <Arduino.h>

#include <map>
#include <Wire.h>

#include <MPU6050.h>
#include <PID.h>

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
    log_d("Gyro\tx:%7.2f, y:%7.2f, z:%7.2f", gyroReadings.x, gyroReadings.y, gyroReadings.z);
    log_d("Accel\tx:%7d, y:%7d, z:%7d\n", accelReadings.x, accelReadings.y, accelReadings.z);
    delay(500);
}
