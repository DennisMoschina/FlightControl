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

#define DEGREE_PER_SECOND 131

#define RAW_DATA_TYPE int16_t
#define ROTATION_DATA_TYPE float

template<typename T> struct AxisData {
    T x = 0;
    T y = 0;
    T z = 0;
};

typedef AxisData<RAW_DATA_TYPE> RawAxisData;
typedef AxisData<ROTATION_DATA_TYPE> RotationData;

class MPU6050 {
public:
    MPU6050(byte sda = 21, byte scl = 22);
    void begin();

    RawAxisData readGyro();
    RawAxisData readAccel();

    RotationData getRotation();

    void setGyroXOffset(RAW_DATA_TYPE offset);
    void setGyroYOffset(RAW_DATA_TYPE offset);
    void setGyroZOffset(RAW_DATA_TYPE offset);

    void setAccelXOffset(RAW_DATA_TYPE offset);
    void setAccelYOffset(RAW_DATA_TYPE offset);
    void setAccelZOffset(RAW_DATA_TYPE offset);

private:
    RawAxisData gyroOffset;
    RawAxisData accelOffset;

    RawAxisData readAxisData(int registerPos);

    RawAxisData calculateAxisOffset(int registerPos, int numberOfReadings = 50);
};

#endif
