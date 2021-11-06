#include <FlightController.h>

FlightController::FlightController(AxisData<ServoOutput*> outputServos,
                ServoInputReader* servoInputs,
                SpeedReader* speedInput,
                int frequency) {
    this->outputServos = outputServos;
    this->servoInputs = servoInputs;
    this->speedInput = speedInput;
    this->cycleDuration = 1000 / frequency; 
}

#if defined(ESP8266) || defined(ESP32)
void controlTask(void * parameter) {
    for (;;) {
        ((FlightController*) parameter)->control();
    }
}

void controlTaskThrottle(void * parameter) {
    for (;;) {
        ((FlightController*) parameter)->controlWithThrottle();
    }
}

void FlightController::begin() {
    TaskFunction_t control = this->speedInput == nullptr ? controlTask : controlTaskThrottle;
    log_v("decided on function for task for flight controller");
    xTaskCreatePinnedToCore(control, "controlTask", 10000, this, 0, &this->pidLoopHandle, 0);
    log_v("created task for flightcontroller");
}

void FlightController::stop() {
    vTaskDelete(this->pidLoopHandle);
}
#endif

void FlightController::writeOutputs(RotationData output) {
    for (int i = 0; i < 3; i++) this->outputServos[i]->write(output[i]);
}

void FlightController::matchFrequency() {
    unsigned long newTimestamp = millis();
    int delayTime = this->cycleDuration - (newTimestamp - oldTimestamp);
    this->oldTimestamp = newTimestamp;
    log_v("delay for %d milliseconds", delayTime);
    delay(delayTime > 0 ? delayTime : 0);
}
