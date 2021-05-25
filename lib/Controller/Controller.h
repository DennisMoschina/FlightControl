#ifndef _CONTROLLER_H
#define _CONTROLLER_H

#include <OutputCalculator.h>
#include <ESP32Servo.h>
#include <ServoInputReader.h>
#include <Switch.h>
#include <RotationRateOuput.h>

#include <functional>

class Controller {
public:
    Controller(OutputCalculator* outputCalculator,
                AxisData<RotationRateOutput*> outputServos,
                ServoInputReader* servoInputs,
                Switch* pidSwitch);

    void begin();
    void stop();
private:
    OutputCalculator* outputCalculator;
    AxisData<RotationRateOutput*> outputServos;
    ServoInputReader* servoInputs;
    Switch* pidSwitch;

    TaskHandle_t pidLoopHandle;

    friend void controlTask(void * parameter);

    void control();
};

#endif