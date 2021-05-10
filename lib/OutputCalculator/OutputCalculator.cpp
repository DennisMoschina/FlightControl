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
    setpoint.x = map(servoInput.x, 0, 180, -this->maxRates.x, this->maxRates.x);
    setpoint.y = map(servoInput.y, 0, 180, -this->maxRates.y, this->maxRates.y);
    setpoint.z = map(servoInput.z, 0, 180, -this->maxRates.z, this->maxRates.z);


    RotationData gyroReadings = rotationReader->getRotation();
    RotationData output = pid->loop(setpoint, gyroReadings);
    output.x = map(output.x, -this->maxRates.x, this->maxRates.x, 0, 180);
    output.y = map(output.y, -this->maxRates.y, this->maxRates.y, 0, 180);
    output.z = map(output.z, -this->maxRates.z, this->maxRates.z, 0, 180);

    log_d("Gyro\t\tx:%7.2f, y:%7.2f, z:%7.2f", gyroReadings.x, gyroReadings.y, gyroReadings.z);
    log_d("Setpoint\tx:%7.2f, y:%7.2f, z:%7.2f", setpoint.x, setpoint.y, setpoint.z);
    log_d("Output\t\tx:%7.2f, y:%7.2f, z:%7.2f\n", output.x, output.y, output.z);


    return output;
}


void OutputCalculator::setCalculate(boolean shouldCalculate) {
    this->shouldCalculate = shouldCalculate;
}
