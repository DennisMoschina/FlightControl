#include <FlightController.h>

FlightController::FlightController(AxisData<RotationRateOutput*> rotationOutputs,
                SteeringInputReader* steeringInputs,
                SpeedReader* speedInput,
                int frequency) {
    this->rotationOutputs = rotationOutputs;
    this->steeringInputs = steeringInputs;
    this->speedInput = speedInput;
    this->cycleDuration = 1000 / frequency; 
}

#if defined(ESP8266) || defined(ESP32)
void controlTask(void * parameter) {
    for (;;) {
        ((FlightController*) parameter)->control();
    }
}

void FlightController::begin() {
    xTaskCreatePinnedToCore(controlTask, "controlTask", 10000, this, 0, &this->pidLoopHandle, 0);
    log_v("created task for flightcontroller");
}

void FlightController::stop() {
    vTaskDelete(this->pidLoopHandle);
}
#endif

void FlightController::control() {
    RotationData servoInput = this->steeringInputs->readInput();
    log_d("Input\t\t\tx:%5d, y:%5d, z:%5d", servoInput.x, servoInput.y, servoInput.z);

    RotationData output = this->calculateOutputs(servoInput);

    this->writeOutputs(output);

    this->matchFrequency();
}

void FlightController::writeOutputs(RotationData output) {
    for (int i = 0; i < 3; i++) this->rotationOutputs[i]->write(output[i]);
}

void FlightController::matchFrequency() {
    unsigned long newTimestamp = millis();
    int delayTime = this->cycleDuration - (newTimestamp - oldTimestamp);
    this->oldTimestamp = newTimestamp;
    log_v("delay for %d milliseconds", delayTime);
    delay(delayTime > 0 ? delayTime : 0);
}
