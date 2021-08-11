#ifndef _MPU6050_H
#define _MPU6050_H

#include <Arduino.h>
#include <Wire.h>
#include <Gyro.h>

#define MPU_ADDR 0x68
#define POWER_MANAGEMENT_REGISTER 0x6B
#define GYRO_CONFIG_REGISTER 0x1B
#define ACCELEROMETER_CONFIG_REGISTER 0x1C

#define GYRO_READING_REGISTER 0x43
#define ACCEL_READING_REGISTER 0x3B

#define AXIS_DATA_REGISTER_SIZE 6

#define MIN_RANGE_RESOLUTION_GYRO 131

/**
 * @brief Read data from the MPU6050 sensor easily.
 * @author Dennis Moschina
 * @version 1.0
 */
class MPU6050 : public Gyro {
public:
    typedef enum {
        MPU6050_ACC_RANGE_2G,  // +/- 2g (default)
        MPU6050_ACC_RANGE_4G,  // +/- 4g
        MPU6050_ACC_RANGE_8G,  // +/- 8g
        MPU6050_ACC_RANGE_16G // +/- 16g
    } mpu6050_acc_range;
    typedef enum {
        MPU6050_GYR_RANGE_250,  // +/- 250 deg/s (default)
        MPU6050_GYR_RANGE_500,  // +/- 500 deg/s
        MPU6050_GYR_RANGE_1000, // +/- 1000 deg/s
        MPU6050_GYR_RANGE_2000  // +/- 2000 deg/s
    } mpu6050_gyr_range;

    MPU6050(byte sda = 21, byte scl = 22);

    /**
     * @brief Set the range for the Gyro.
     * @param gyroRange the new range for the gyro
     */
    void setGyroRange(mpu6050_gyr_range gyroRange);

    /**
     * @brief Set the range for the Accelerometer.
     * @param accelRange the new range for the accelerometer
     */
    void setAccelRange(mpu6050_acc_range accelRange);

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
    AxisData<byte> axisMap;
    AxisData<boolean> invertOutput;

    mpu6050_gyr_range gyroRange;
    mpu6050_acc_range accelRange;

    int gyroRangeValues[4] = {250, 500, 1000, 2000};
    int accelRangeValues[4] = {2, 4, 8, 16};

    RawAxisData readAxisData(int registerPos);
    RawAxisData calculateAxisOffset(int registerPos, int numberOfReadings = 50);
    void writeRegister(uint16_t reg, byte value);
};

#endif
