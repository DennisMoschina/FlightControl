#include <MPU6050.h>

MPU6050::MPU6050(byte sda, byte scl) {
    Wire.begin(sda, scl);
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

    this->gyroOffset = this->calculateAxisOffset(GYRO_READING_REGISTER);
    this->accelOffset = this->calculateAxisOffset(ACCEL_READING_REGISTER);

    Serial.println("=======================Offsets=======================");
    Serial.printf("Gyro\tx: %d, y: %d, z: %d\n", this->gyroOffset.x, this->gyroOffset.y, this->gyroOffset.z);
    Serial.printf("Accel\tx: %d, y: %d, z: %d\n", this->accelOffset.x, this->accelOffset.y, this->accelOffset.z);
    Serial.println("=====================================================");
    Serial.println("=====================================================");
}

AxisData MPU6050::readGyro() {
    AxisData gyroReadings = this->readAxisData(GYRO_READING_REGISTER);
    gyroReadings.x -= this->gyroOffset.x;
    gyroReadings.y -= this->gyroOffset.y;
    gyroReadings.z -= this->gyroOffset.z;

    return gyroReadings;
}

AxisData MPU6050::readAccel() {
    AxisData accelReadings = this->readAxisData(ACCEL_READING_REGISTER);
    accelReadings.x -= this->accelOffset.x;
    accelReadings.y -= this->accelOffset.y;
    accelReadings.z -= this->accelOffset.z;

    return accelReadings;
}

AxisData MPU6050::readAxisData(int registerPos) {
    AxisData data;
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(registerPos);
    Wire.endTransmission();
    Wire.requestFrom(MPU_ADDR, AXIS_DATA_REGISTER_SIZE);

    while (Wire.available() < AXIS_DATA_REGISTER_SIZE);
    data.x = Wire.read() << 8 | Wire.read();
    data.y = Wire.read() << 8 | Wire.read();
    data.z = Wire.read() << 8 | Wire.read();

    return data;
}


void MPU6050::setGyroXOffset(int offset) {
    this->gyroOffset.x = offset;
}

void MPU6050::setGyroYOffset(int offset) {
    this->gyroOffset.y = offset;
}

void MPU6050::setGyroZOffset(int offset) {
    this->gyroOffset.z = offset;
}

void MPU6050::setAccelXOffset(int offset) {
    this->accelOffset.x = offset;
}

void MPU6050::setAccelYOffset(int offset) {
    this->accelOffset.y = offset;
}

void MPU6050::setAccelZOffset(int offset) {
    this->accelOffset.z = offset;
}



AxisData MPU6050::calculateAxisOffset(int registerPos, int duration, int interval) {
    unsigned long startTime = millis();
    AxisData offset;
    int readings = 0;
    while(millis() < startTime + duration) {
        AxisData data = this->readAxisData(registerPos);
        readings++;
        offset.x += data.x;
        offset.y += data.y;
        offset.z += data.z;

        delay(interval);
    }

    if (readings > 0) {
        offset.x = offset.x / readings;
        offset.y = offset.y / readings;
        offset.z = offset.z / readings;
    }

    return offset;
}