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

void controlTask(void * parameter) {
    for (;;) {
        ((Controller*) parameter)->control();
    }
}

void Controller::control() {
    this->outputCalculator->setCalculate(this->pidSwitch->getBoolean());

    RotationData servoInput = this->servoInputs->readInput();
    log_d("Input\t\t\tx:%5d, y:%5d, z:%5d", servoInput.x, servoInput.y, servoInput.z);

    RotationData output = this->outputCalculator->calculateOutput(servoInput, this->servoInputs->getResolution());

    this->outputServos.x->write(output.x);
    this->outputServos.y->write(output.y);
    this->outputServos.z->write(output.z);

    delay(20);
}

void Controller::begin() {
    xTaskCreatePinnedToCore(controlTask, "controlTask", 10000, this, 0, &this->pidLoopHandle, 0);
}

void Controller::stop() {
    vTaskDelete(this->pidLoopHandle);
}