#include <OutputCalculator.h>

OutputCalculator::OutputCalculator(int steeringInputResolution,
                        int outputResolution,
                        RotationData maxRates,
                        Gyro* rotationReader,
                        Stabilizer* stabilizer,
                        GainCalculator* gainCalculator): AbstractOutputCalculator(steeringInputResolution, outputResolution) {
    this->maxRates = maxRates;
    this->rotationReader = rotationReader;
    this->stabilizer = stabilizer;
    this->gainCalculator = gainCalculator;
}

RotationData OutputCalculator::calculateOutput(RotationData servoInput) {
    RotationData setpoint = this->calculateSetpoint(servoInput);

    RotationData gyroReadings = rotationReader->getRotation();
    RotationData output;
    try {
        output = stabilizer->loop(setpoint, gyroReadings);
    } catch (const char* e) {
        log_e("%s", e);
        output = servoInput;
        this->stabilizer->reset();
    }

    log_d("Input\t\tx:%5d, y:%5d, z:%5d", servoInput.x, servoInput.y, servoInput.z);
    log_d("Gyro\t\tx:%5d, y:%5d, z:%5d", gyroReadings.x, gyroReadings.y, gyroReadings.z);
    log_d("Setpoint\tx:%5d, y:%5d, z:%5d", setpoint.x, setpoint.y, setpoint.z);
    log_d("Output\t\tx:%5d, y:%5d, z:%5d\n", output.x, output.y, output.z);

    return this->adjustOutput(output, this->stabilizer->getResolution());
}

RotationData OutputCalculator::calculateOutput(RotationData servoInput,
                                int speed) {
    RotationData setpoint = this->calculateSetpoint(servoInput);

    RotationData gyroReadings = rotationReader->getRotation();
    this->gainCalculator->calculateGains(speed);
    RotationData output = stabilizer->loop(setpoint, gyroReadings);

    log_d("Input\t\tx:%5d, y:%5d, z:%5d", servoInput.x, servoInput.y, servoInput.z);
    log_d("Gyro\t\tx:%5d, y:%5d, z:%5d", gyroReadings.x, gyroReadings.y, gyroReadings.z);
    log_d("Setpoint\tx:%5d, y:%5d, z:%5d", setpoint.x, setpoint.y, setpoint.z);
    log_d("Output\t\tx:%5d, y:%5d, z:%5d\n", output.x, output.y, output.z);

    return this->adjustOutput(output, this->stabilizer->getResolution());
}

RotationData OutputCalculator::calculateSetpoint(RotationData input) {
    int resolution = this->getSteeringInputResolution();
    RotationData setpoint;
    setpoint.yaw = map(input.yaw, -resolution, resolution, -this->maxRates.yaw, this->maxRates.yaw);
    setpoint.pitch = map(input.pitch, -resolution, resolution, -this->maxRates.pitch, this->maxRates.pitch);
    setpoint.roll = map(input.roll, -resolution, resolution, -this->maxRates.roll, this->maxRates.z);
    return setpoint;
}

void OutputCalculator::reset() {
    this->stabilizer->reset();
}