#include <Arduino.h>

#include <map>
#include <Wire.h>

#include <RCReceiverReader.h>
#include <MPU6050.h>
#include <PID.h>

#define RUDDER_PIN 2
#define RUDDER_MIN 1068
#define RUDDER_MAX 1871

RCReceiverReader<RUDDER_PIN> rudder(RUDDER_MIN, RUDDER_MAX);
MPU6050 mpu = MPU6050();
PID pid;

void setup() {
    Serial.begin(115200);

    mpu.begin();
}

void loop() {
    // RotationData setpoint;
    // for (int i = 0; i < 3; i++) {
    //     setpoint[i] = 0;
    // }
    // RotationData gyroReadings = mpu.getRotation();
    // RotationData output = pid.loop(setpoint, gyroReadings);
    // log_d("Gyro\t\tx:%7.2f, y:%7.2f, z:%7.2f", gyroReadings.x, gyroReadings.y, gyroReadings.z);
    // log_d("Setpoint\tx:%7.2f, y:%7.2f, z:%7.2f", setpoint.x, setpoint.y, setpoint.z);
    // log_d("Output\t\tx:%7.2f, y:%7.2f, z:%7.2f\n", output.x, output.y, output.z);
    int16_t rudderValue = rudder.getPosition();
    float rudderAngle = rudder.getAngle();

    log_d("Rudder:\tposition:%5d, angle:%7.2f", rudderValue, rudderAngle);
    delay(100);
}
