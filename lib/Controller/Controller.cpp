#include <Controller.h>

Controller::Controller(OutputCalculator* outputCalculator,
                AxisData<ServoOutput*> outputServos,
                ServoInputReader* servoInputs,
                Switch* pidSwitch) {
    this->outputCalculator = outputCalculator;
    this->outputServos = outputServos;
    this->servoInputs = servoInputs;
    this->pidSwitch = pidSwitch;
}

Controller::Controller(OutputCalculator* outputCalculator,
                AxisData<ServoOutput*> outputServos,
                ThrottleOutput* throttleOutput,
                ServoInputReader* servoInputs,
                SpeedReader* throttleInput,
                Switch* pidSwitch) : Controller(outputCalculator, outputServos, servoInputs, pidSwitch) {
    this->throttleInput = throttleInput;
    this->throttleOutput = throttleOutput;
}

void controlTask(void * parameter) {
    for (;;) {
        ((Controller*) parameter)->control();
    }
}

void controlTaskThrottle(void * parameter) {
    for (;;) {
        ((Controller*) parameter)->controlWithThrottle();
    }
}

void Controller::control() {
    this->outputCalculator->setCalculate(this->pidSwitch->getBoolean());

    RotationData servoInput = this->servoInputs->readInput();
    log_d("Input\t\t\tx:%5d, y:%5d, z:%5d", servoInput.x, servoInput.y, servoInput.z);

    RotationData output = this->outputCalculator->calculateOutput(servoInput, this->servoInputs->getResolution());

    this->writeOutputs(output);

    delay(20);
}

void Controller::controlWithThrottle() {
    this->outputCalculator->setCalculate(this->pidSwitch->getBoolean());

    RotationData servoInput = this->servoInputs->readInput();
    int throttleSignal = this->throttleInput->getSpeed();
    log_d("Input\t\tx:%5d, y:%5d, z:%5d, t:%5d", servoInput.x, servoInput.y, servoInput.z, throttleSignal);

    RotationData output = this->outputCalculator->calculateOutput(servoInput,
                                                                    this->servoInputs->getResolution(),
                                                                    throttleSignal);

    this->writeOutputs(output);
    this->throttleOutput->write(this->throttleInput->getRawSpeed());

    delay(20);
}

void Controller::begin() {
    TaskFunction_t control = this->throttleInput == nullptr ? controlTask : controlTaskThrottle;    
    xTaskCreatePinnedToCore(control, "controlTask", 10000, this, 0, &this->pidLoopHandle, 0);
}

void Controller::stop() {
    vTaskDelete(this->pidLoopHandle);
}

void Controller::writeOutputs(RotationData output) {
    for (int i = 0; i < 3; i++) this->outputServos[i]->write(output[i]);
}
