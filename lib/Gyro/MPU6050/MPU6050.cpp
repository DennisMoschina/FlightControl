#include "MPU6050.h"

MPU6050::MPU6050(byte sda, byte scl) {
    Wire.begin(sda, scl);
    for (int i = 0; i < 3; i++) this->remapAxis(i, i);
}

void MPU6050::setGyroRange(mpu6050_gyr_range gyroRange) {
    this->writeRegister(GYRO_CONFIG_REGISTER, gyroRange<<3);
    this->gyroRange = gyroRange;
}

void MPU6050::setAccelRange(mpu6050_acc_range accelRange) {
    this->writeRegister(ACCELEROMETER_CONFIG_REGISTER, accelRange<<3);
    this->accelRange = accelRange;
}

void MPU6050::begin() {
    log_i("start the MPU6050");

    log_v("waking up MPU");
    this->writeRegister(POWER_MANAGEMENT_REGISTER, 0);  //wake up MPU-6050
    log_v("woke up MPU");
    
    this->setAccelRange(MPU6050_ACC_RANGE_2G);
    this->setGyroRange(MPU6050_GYR_RANGE_2000);

    delay(1000);

    this->gyroOffset = this->calculateAxisOffset(GYRO_READING_REGISTER);

    log_v("\n=======================Offsets=======================");
    log_v("Gyro\tx:%7d, y:%7d, z:%7d", this->gyroOffset.x, this->gyroOffset.y, this->gyroOffset.z);
    log_v("Accel\tx:%7d, y:%7d, z:%7d", this->accelOffset.x, this->accelOffset.y, this->accelOffset.z);
    log_v("=====================================================\n");
}

RawAxisData MPU6050::readGyro() {
    RawAxisData gyroReadings = this->readAxisData(GYRO_READING_REGISTER);
    gyroReadings -= this->gyroOffset;
    return gyroReadings;
}

RawAxisData MPU6050::readAccel() {
    RawAxisData accelReadings = this->readAxisData(ACCEL_READING_REGISTER);
    accelReadings -= this->accelOffset;
    return accelReadings;
}

RawAxisData MPU6050::readAxisData(int registerPos) {
    RawAxisData data;
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(registerPos);
    Wire.endTransmission();
    log_v("requested data from register %d", registerPos);
    Wire.requestFrom(MPU_ADDR, AXIS_DATA_REGISTER_SIZE);

    unsigned long startTime = millis();
    int available = Wire.available();
    while (available < AXIS_DATA_REGISTER_SIZE) {
        if (startTime + this->timeout > millis()) throw "timeout when reading axisData";
        log_v("only %d bytes available, but %d expected", available, AXIS_DATA_REGISTER_SIZE);
        available = Wire.available();
    }
    data[this->axisMap.x] = Wire.read() << 8 | Wire.read();
    data[this->axisMap.y] = Wire.read() << 8 | Wire.read();
    data[this->axisMap.z] = Wire.read() << 8 | Wire.read();

    return data;
}

RotationData MPU6050::getRotation() {
    RawAxisData gyroData = this->readGyro();
    RotationData rotation;
    log_d("Raw values:\tx:%6d\ty:%6d\tz:%6d", gyroData.x, gyroData.y, gyroData.z);
    log_d("gyroRange:\t%6d", this->gyroRangeValues[this->gyroRange]);

    int rangeFactor = this->gyroRangeValues[this->gyroRange] / this->gyroRangeValues[0];
    for (int i = 0; i < 3; i++) {
        int helperValue = gyroData[i] / MIN_RANGE_RESOLUTION_GYRO;
        log_d("raw value / 131: axis %d:\t%6d", i, helperValue);
        log_d("calculated value:\t%6d", rangeFactor * helperValue);
        rotation[i] = rangeFactor * helperValue;
    }

    log_d("final values::\tx:%6d\ty:%6d\tz:%6d\n", gyroData.x, gyroData.y, gyroData.z);

    return rotation;
}

void MPU6050::setGyroOffset(RawAxisData offset) {
    this->gyroOffset = offset;
}

void MPU6050::setGyroXOffset(RAW_DATA_TYPE offset) {
    this->gyroOffset.x = offset;
}

void MPU6050::setGyroYOffset(RAW_DATA_TYPE offset) {
    this->gyroOffset.y = offset;
}

void MPU6050::setGyroZOffset(RAW_DATA_TYPE offset) {
    this->gyroOffset.z = offset;
}

void MPU6050::setAccelOffset(RawAxisData offset) {
    this->accelOffset = offset;
}

void MPU6050::setAccelXOffset(RAW_DATA_TYPE offset) {
    this->accelOffset.x = offset;
}

void MPU6050::setAccelYOffset(RAW_DATA_TYPE offset) {
    this->accelOffset.y = offset;
}

void MPU6050::setAccelZOffset(RAW_DATA_TYPE offset) {
    this->accelOffset.z = offset;
}


void MPU6050::remapAxis(byte from, byte to) {
    this->axisMap[from] = to;
}

void MPU6050::remapAxis(AxisData<byte> to) {
    this->axisMap = to;
}

void MPU6050::setTimeout(int timeout) {
    this->timeout = timeout;
}


RawAxisData MPU6050::calculateAxisOffset(int registerPos, int numberOfReadings) {
    RAW_DATA_TYPE x[numberOfReadings];
    RAW_DATA_TYPE y[numberOfReadings];
    RAW_DATA_TYPE z[numberOfReadings];

    for (int i = 0; i < numberOfReadings; i++) {
        RawAxisData data = this->readAxisData(registerPos);
        x[i] = data.x;
        y[i] = data.y;
        z[i] = data.z;
    }

    std::sort(x, x + numberOfReadings);
    std::sort(y, y + numberOfReadings);
    std::sort(z, z + numberOfReadings);

    const int middle = numberOfReadings / 2;

    RawAxisData offset;
    offset.x = x[middle];
    offset.y = y[middle];
    offset.z = z[middle];

    return offset;
}

void MPU6050::writeRegister(uint16_t reg, byte value) {
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(reg); 
    Wire.write(value); 
    Wire.endTransmission(true);
}
