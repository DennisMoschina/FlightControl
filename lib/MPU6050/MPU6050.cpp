#include <MPU6050.h>

MPU6050::MPU6050(byte sda, byte scl) {
    Wire.begin(sda, scl);

    // this->gyroOffset[X] = -64420;
    // this->gyroOffset[Y] = -80;
    // this->gyroOffset[Z] = -65240;
}

void MPU6050::begin() {
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(POWER_MANAGEMENT_REGISTER);
    Wire.write(0);                              //wake up MPU-6050
    Wire.endTransmission(true);

    Wire.beginTransmission(MPU_ADDR);
    Wire.write(GYRO_CONFIG_REGISTER);
    Wire.write(0);                              //set gyro to full scale
    Wire.endTransmission(true);

    Wire.beginTransmission(MPU_ADDR);
    Wire.write(ACCELEROMETER_CONFIG_REGISTER);
    Wire.write(0);                              //set accelerometer to +/- 2g
    Wire.endTransmission(true);
}

AxisData MPU6050::readGyro() {
    AxisData gyroReadings;
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(GYRO_READING_REGISTER);
    Wire.endTransmission();
    Wire.requestFrom(MPU_ADDR, GYRO_REGISTER_SIZE);

    while (Wire.available() < 6);
    gyroReadings[X] = Wire.read() << 8 | Wire.read();
    gyroReadings[Y] = Wire.read() << 8 | Wire.read();
    gyroReadings[Z] = Wire.read() << 8 | Wire.read();

    AxisData::iterator iterator = gyroReadings.begin();
    while (iterator != gyroReadings.end()) {
        iterator->second += this->gyroOffset[iterator->first];
        iterator++;
    }

    return gyroReadings;
}
