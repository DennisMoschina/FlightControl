#include <OutputCalculator.h>

#include <RotationReader.h>

OutputCalculator::OutputCalculator(RotationData maxRates, Gyro* rotationReader, Stabilizer* stabilizer) {
    this->maxRates = maxRates;
    this->rotationReader = rotationReader;
    this->stabilizer = stabilizer;
}

RotationData OutputCalculator::calculateOutput(RotationData servoInput, int resolution) {
    if (!this->shouldCalculate) return servoInput;

    RotationData setpoint = this->calculateSetpoint(servoInput, resolution);

    RotationData gyroReadings = rotationReader->getRotation();
    RotationData output = stabilizer->loop(setpoint, gyroReadings);

    log_d("Input\t\tx:%5d, y:%5d, z:%5d", servoInput.x, servoInput.y, servoInput.z);
    log_d("Gyro\t\tx:%5d, y:%5d, z:%5d", gyroReadings.x, gyroReadings.y, gyroReadings.z);
    log_d("Setpoint\tx:%5d, y:%5d, z:%5d", setpoint.x, setpoint.y, setpoint.z);
    log_d("Output\t\tx:%5d, y:%5d, z:%5d\n", output.x, output.y, output.z);

    return output;
}

RotationData OutputCalculator::calculateOutput(RotationData servoInput,
                                int resolution,
                                int throttleInput,
                                int throttleResolution) {
    if (!this->shouldCalculate) return servoInput;

    RotationData setpoint = this->calculateSetpoint(servoInput, resolution);

    RotationData gyroReadings = rotationReader->getRotation();
    RotationData output = stabilizer->loop(setpoint, gyroReadings, throttleInput, throttleResolution);

    log_d("Input\t\tx:%5d, y:%5d, z:%5d", servoInput.x, servoInput.y, servoInput.z);
    log_d("Gyro\t\tx:%5d, y:%5d, z:%5d", gyroReadings.x, gyroReadings.y, gyroReadings.z);
    log_d("Setpoint\tx:%5d, y:%5d, z:%5d", setpoint.x, setpoint.y, setpoint.z);
    log_d("Output\t\tx:%5d, y:%5d, z:%5d\n", output.x, output.y, output.z);

    return output;
}


void OutputCalculator::setCalculate(boolean shouldCalculate) {
    this->shouldCalculate = shouldCalculate;
    this->stabilizer->reset();
}

RotationData OutputCalculator::calculateSetpoint(RotationData input, int resolution) {
    RotationData setpoint;
    setpoint.yaw = map(input.yaw, -resolution, resolution, -this->maxRates.yaw, this->maxRates.yaw);
    setpoint.pitch = map(input.pitch, -resolution, resolution, -this->maxRates.pitch, this->maxRates.pitch);
    setpoint.roll = map(input.roll, -resolution, resolution, -this->maxRates.roll, this->maxRates.z);
    return setpoint;
}