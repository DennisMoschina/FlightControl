#ifndef _CONTROLLER_H
#define _CONTROLLER_H

#include <OutputCalculator.h>
#include <ESP32Servo.h>
#include <ServoInputReader.h>
#include <Switch.h>
#include <ServoOutput.h>

#include <functional>

class Controller {
public:
    Controller(OutputCalculator* outputCalculator,
                AxisData<ServoOutput*> outputServos,
                ServoInputReader* servoInputs,
                Switch* pidSwitch);

    /**
     * Create the task for the controller to process the inputs.
     */
    void begin();

    /**
     * Stop the task of the Controller putting out the data.
     */
    void stop();

private:
    OutputCalculator* outputCalculator;
    AxisData<ServoOutput*> outputServos;
    ServoInputReader* servoInputs;
    Switch* pidSwitch;

    TaskHandle_t pidLoopHandle;

    friend void controlTask(void * parameter);

    void control();
};

#endif