#include <Controller.h>

Controller::Controller(OutputCalculator* outputCalculator,
                AxisData<ServoOutput*> outputServos,
                ServoInputReader* servoInputs,
                Switch* pidSwitch,
                ThrottleOutput* throttleOutput,
                SpeedReader* speedInput,
                int frequency) {
    this->outputCalculator = outputCalculator;
    this->outputServos = outputServos;
    this->servoInputs = servoInputs;
    this->pidSwitch = pidSwitch;
    this->speedInput = speedInput;
    this->throttleOutput = throttleOutput;
    this->cycleDuration = 1000 / frequency; 
}

#if defined(ESP8266) || defined(ESP32)
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
#endif


void Controller::control() {
    this->outputCalculator->setCalculate(this->pidSwitch->getBoolean());

    RotationData servoInput = this->servoInputs->readInput();
    log_d("Input\t\t\tx:%5d, y:%5d, z:%5d", servoInput.x, servoInput.y, servoInput.z);

    RotationData output = this->outputCalculator->calculateOutput(servoInput, this->servoInputs->getResolution());

    this->writeOutputs(output);

    this->matchFrequency();
}

void Controller::controlWithThrottle() {
    this->outputCalculator->setCalculate(this->pidSwitch->getBoolean());

    RotationData servoInput = this->servoInputs->readInput();
    int throttleSignal = this->speedInput->getSpeed();
    log_d("Input\t\tx:%5d, y:%5d, z:%5d, t:%5d", servoInput.x, servoInput.y, servoInput.z, throttleSignal);

    RotationData output = this->outputCalculator->calculateOutput(servoInput,
                                                                    this->servoInputs->getResolution(),
                                                                    throttleSignal);

    this->writeOutputs(output);

    this->matchFrequency();
}

#if defined(ESP8266) || defined(ESP32)
void Controller::begin() {
    TaskFunction_t control = this->speedInput == nullptr ? controlTask : controlTaskThrottle;
    xTaskCreatePinnedToCore(control, "controlTask", 10000, this, 0, &this->pidLoopHandle, 0);
}

void Controller::stop() {
    vTaskDelete(this->pidLoopHandle);
}
#endif

void Controller::writeOutputs(RotationData output) {
    for (int i = 0; i < 3; i++) this->outputServos[i]->write(output[i]);
}

void Controller::matchFrequency() {
    unsigned long newTimestamp = millis();
    int delayTime = this->cycleDuration - (newTimestamp - oldTimestamp);
    this->oldTimestamp = newTimestamp;
    log_v("delay for %d milliseconds", delayTime);
    delay(delayTime > 0 ? delayTime : 0);
}
