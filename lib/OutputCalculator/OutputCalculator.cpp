#include <OutputCalculator.h>

#include <MPU6050.h>

OutputCalculator::OutputCalculator(RotationData maxRates, RotationReader* rotationReader, PID* pid) {
    this->maxRates = maxRates;
    this->rotationReader = rotationReader;
    this->pid = pid;
}

RotationData OutputCalculator::calculateOutput(RotationData servoInput) {
    if (!this->shouldCalculate) return servoInput;

    RotationData setpoint;
    setpoint.yaw = map(servoInput.yaw, 0, 180, this->maxRates.yaw, -this->maxRates.yaw);
    setpoint.pitch = map(servoInput.pitch, 0, 180, this->maxRates.pitch, -this->maxRates.pitch);
    setpoint.roll = map(servoInput.roll, 0, 180, -this->maxRates.roll, this->maxRates.z);


    RotationData gyroReadings = rotationReader->getRotation();
    RotationData output = pid->loop(setpoint, gyroReadings);
    output.yaw = map(output.yaw, -this->maxRates.yaw, this->maxRates.yaw, 0, 180);
    output.pitch = map(output.pitch, -this->maxRates.pitch, this->maxRates.pitch, 0, 180);
    output.roll = map(output.roll, -this->maxRates.roll, this->maxRates.roll, 0, 180);

    log_d("Gyro\t\tx:%7.2f, y:%7.2f, z:%7.2f", gyroReadings.x, gyroReadings.y, gyroReadings.z);
    log_d("Setpoint\tx:%7.2f, y:%7.2f, z:%7.2f", setpoint.x, setpoint.y, setpoint.z);
    log_d("Output\t\tx:%7.2f, y:%7.2f, z:%7.2f\n", output.x, output.y, output.z);


    return output;
}


void OutputCalculator::setCalculate(boolean shouldCalculate) {
    this->shouldCalculate = shouldCalculate;
}
