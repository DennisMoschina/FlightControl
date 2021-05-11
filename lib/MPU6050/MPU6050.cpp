#include <MPU6050.h>

MPU6050::MPU6050(byte sda, byte scl) {
    Wire.begin(sda, scl);
    for (int i = 0; i < 3; i++) this->remapAxis(i, i);
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
    Wire.requestFrom(MPU_ADDR, AXIS_DATA_REGISTER_SIZE);

    while (Wire.available() < AXIS_DATA_REGISTER_SIZE);
    data[this->axisMap.x] = Wire.read() << 8 | Wire.read();
    data[this->axisMap.y] = Wire.read() << 8 | Wire.read();
    data[this->axisMap.z] = Wire.read() << 8 | Wire.read();

    return data;
}

RotationData MPU6050::getRotation() {
    RawAxisData gyroData = this->readGyro();
    RotationData rotation;
    rotation.x = ROTATION_DATA_TYPE(gyroData.x) / DEGREE_PER_SECOND;
    rotation.y = ROTATION_DATA_TYPE(gyroData.y) / DEGREE_PER_SECOND;
    rotation.z = ROTATION_DATA_TYPE(gyroData.z) / DEGREE_PER_SECOND;

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
