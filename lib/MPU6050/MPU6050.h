#ifndef _MPU6050_H
#define _MPU6050_H

#include <Arduino.h>

#include <Wire.h>

#include <RotationReader.h>

#define MPU_ADDR 0x68
#define POWER_MANAGEMENT_REGISTER 0x6B
#define GYRO_CONFIG_REGISTER 0x1B
#define ACCELEROMETER_CONFIG_REGISTER 0x1C

#define GYRO_READING_REGISTER 0x43
#define ACCEL_READING_REGISTER 0x3B

#define AXIS_DATA_REGISTER_SIZE 6

#define DEGREE_PER_SECOND 131

/**
 * @brief Read data from the MPU6050 sensor easily.
 * @author Dennis Moschina
 * @version 1.0
 */
class MPU6050 : public virtual RotationReader {
public:
    MPU6050(byte sda = 21, byte scl = 22);

    /**
     * @brief Initialize the MPU6050.
     * @details Configure the MPU to make the most detailed data available and calibrate it.
     */
    void begin();

    /**
     * Read the raw gyro data of the MPU6050 sensor with the offsets removed.
     * @return the gyro data with corrected offsets
     */
    RawAxisData readGyro();
    /**
     * Read the raw accelerometer data of the MPU6050 sensor with the offsets removed.
     * @return the accelerometer data with corrected offsets
     */
    RawAxisData readAccel();

    /**
     * Get the rotation rate in degrees per second.
     * @return rotation rate in deg/sec
     */
    RotationData getRotation();

    void setGyroOffset(RawAxisData offset);

    void setGyroXOffset(RAW_DATA_TYPE offset);
    void setGyroYOffset(RAW_DATA_TYPE offset);
    void setGyroZOffset(RAW_DATA_TYPE offset);

    void setAccelOffset(RawAxisData offset);

    void setAccelXOffset(RAW_DATA_TYPE offset);
    void setAccelYOffset(RAW_DATA_TYPE offset);
    void setAccelZOffset(RAW_DATA_TYPE offset);

    /**
     * @brief Change the orientation of the axes.
     * @param from the previous axis
     * @param to the new axis
     */
    void remapAxis(byte from, byte to);
    /**
     * @brief Change the orientation of the axes.
     * @param to the new orientations of the axes
     */
    void remapAxis(AxisData<byte> to);


private:
    RawAxisData gyroOffset;
    RawAxisData accelOffset;

    RawAxisData readAxisData(int registerPos);

    RawAxisData calculateAxisOffset(int registerPos, int numberOfReadings = 50);

    AxisData<byte> axisMap;

    AxisData<boolean> invertOutput;
};

#endif
