#ifndef _CONTROLLER_H
#define _CONTROLLER_H

#include <OutputCalculator.h>
#include <ESP32Servo.h>
#include <ServoInputReader.h>
#include <Switch.h>
#include <ServoOutput.h>
#include <ThrottleReader.h>

#include <functional>

class Controller {
public:
    Controller(OutputCalculator* outputCalculator,
                AxisData<ServoOutput*> outputServos,
                ServoInputReader* servoInputs,
                Switch* pidSwitch);

    Controller(OutputCalculator* outputCalculator,
                AxisData<ServoOutput*> outputServos,
                ServoOutput* throttleOutput,
                ServoInputReader* servoInputs,
                ThrottleReader* throttleInput,
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
    ServoOutput* throttleOutput;
    ServoInputReader* servoInputs;
    ThrottleReader* throttleInput;
    Switch* pidSwitch;

    TaskHandle_t pidLoopHandle;

    friend void controlTask(void * parameter);
    friend void controlTaskThrottle(void * parameter);

    void control();
    void controlWithThrottle();

    void writeOutputs(RotationData output);
};

#endif