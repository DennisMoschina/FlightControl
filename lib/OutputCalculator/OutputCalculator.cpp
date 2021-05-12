#include <OutputCalculator.h>

#include <MPU6050.h>

#define DEFAULT_SERVO_MIDDLE 1500
#define DEFAULT_SERVO_RANGE 1000

OutputCalculator::OutputCalculator(RotationData maxRates, RotationReader* rotationReader, PID* pid) {
    this->maxRates = maxRates;
    this->rotationReader = rotationReader;
    this->pid = pid;

    this->servoMiddle = DEFAULT_SERVO_MIDDLE;
    this->servoRange = DEFAULT_SERVO_RANGE;
}

RotationData OutputCalculator::calculateOutput(RotationData servoInput) {
    if (!this->shouldCalculate) return this->remapOutput(servoInput);

    RotationData setpoint;
    setpoint.yaw = map(servoInput.yaw, -100, 100, -this->maxRates.yaw, this->maxRates.yaw);
    setpoint.pitch = map(servoInput.pitch, -100, 100, -this->maxRates.pitch, this->maxRates.pitch);
    setpoint.roll = map(servoInput.roll, -100, 100, -this->maxRates.roll, this->maxRates.z);


    RotationData gyroReadings = rotationReader->getRotation();
    RotationData output = pid->loop(setpoint, gyroReadings);

    output = this->remapOutput(output);

    log_d("Input\t\tx:%7.2f, y:%7.2f, z:%7.2f", servoInput.x, servoInput.y, servoInput.z);
    log_d("Gyro\t\tx:%7.2f, y:%7.2f, z:%7.2f", gyroReadings.x, gyroReadings.y, gyroReadings.z);
    log_d("Setpoint\tx:%7.2f, y:%7.2f, z:%7.2f", setpoint.x, setpoint.y, setpoint.z);
    log_d("Output\t\tx:%7.2f, y:%7.2f, z:%7.2f\n", output.x, output.y, output.z);


    return output;
}


void OutputCalculator::setCalculate(boolean shouldCalculate) {
    this->shouldCalculate = shouldCalculate;
}

void OutputCalculator::setServoMiddle(AxisData<int> servoMiddle) {
    this->servoMiddle = servoMiddle;
}

void OutputCalculator::setServoMiddle(byte axis, int servoMiddle) {
    this->servoMiddle[axis] = servoMiddle;
}

RotationData OutputCalculator::remapOutput(RotationData output) {
    for (int i = 0; i < 3; i++) {
        const int servoRadius = this->servoRange[i] / 2;
        output[i] = map(output[i], -100, 100, this->servoMiddle[i] - servoRadius, this->servoMiddle[i] + servoRadius);
    }
    return output;
}
