#ifndef _MPU6050_H
#define _MPU6050_H

#include <Arduino.h>

#include <Wire.h>
#include <map>

#define MPU_ADDR 0x68
#define POWER_MANAGEMENT_REGISTER 0x6B
#define GYRO_CONFIG_REGISTER 0x1B
#define ACCELEROMETER_CONFIG_REGISTER 0x1C

#define GYRO_READING_REGISTER 0x43
#define GYRO_REGISTER_SIZE 6

#define X 0
#define Y 1
#define Z 2

using AxisData = std::map<int, int>;

class MPU6050 {
public:
    MPU6050(byte sda = 21, byte scl = 22);
    void begin();

    AxisData readGyro();

    void setGyroOffset(int offset, int axis);

private:
    AxisData gyroOffset;
};

#endif
