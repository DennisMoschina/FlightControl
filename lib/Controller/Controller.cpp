#include <Controller.h>

Controller::Controller(OutputCalculator* outputCalculator,
                AxisData<Servo*> outputServos,
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

    RotationData output = this->outputCalculator->calculateOutput(servoInput);

    this->outputServos.x->write(output.yaw);
    this->outputServos.roll->write(output.roll);
    this->outputServos.pitch->write(output.pitch);

    delay(20);
}

void Controller::begin() {
    xTaskCreatePinnedToCore(controlTask, "controlTask", 10000, this, 0, &this->pidLoopHandle, 0);
}

void Controller::stop() {
    vTaskDelete(this->pidLoopHandle);
}