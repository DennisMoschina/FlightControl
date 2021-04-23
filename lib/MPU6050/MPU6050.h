#ifndef _MPU6050_H
#define _MPU6050_H

#include <Arduino.h>

#include <Wire.h>

#define MPU_ADDR 0x68
#define POWER_MANAGEMENT_REGISTER 0x6B
#define GYRO_CONFIG_REGISTER 0x1B
#define ACCELEROMETER_CONFIG_REGISTER 0x1C

#define GYRO_READING_REGISTER 0x43
#define ACCEL_READING_REGISTER 0x3B

#define AXIS_DATA_REGISTER_SIZE 6

typedef struct {
    int16_t x = 0;
    int16_t y = 0;
    int16_t z = 0;
} AxisData;

class MPU6050 {
public:
    MPU6050(byte sda = 21, byte scl = 22);
    void begin();

    AxisData readGyro();

    AxisData readAccel();

    void setGyroXOffset(int offset);
    void setGyroYOffset(int offset);
    void setGyroZOffset(int offset);

    void setAccelXOffset(int offset);
    void setAccelYOffset(int offset);
    void setAccelZOffset(int offset);

private:
    AxisData gyroOffset;
    AxisData accelOffset;

    AxisData readAxisData(int registerPos);

    AxisData calculateAxisOffset(int registerPos, int numberOfReadings = 50);
};

#endif
