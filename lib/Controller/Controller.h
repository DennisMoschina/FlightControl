#ifndef _CONTROLLER_H
#define _CONTROLLER_H

#include <OutputCalculator.h>
#include <ESP32Servo.h>
#include <ServoInputReader.h>
#include <Switch.h>
#include <ServoOutput.h>
#include <ThrottleReader.h>
#include <ThrottleOutput.h>

#include <functional>

/**
 * @brief Manage the calculation of the output based on the steering signals.
 * @author Dennis Moschina
 * @version 1.0
 */
class Controller {
public:
    Controller(OutputCalculator* outputCalculator,
                AxisData<ServoOutput*> outputServos,
                ServoInputReader* servoInputs,
                Switch* pidSwitch);

    Controller(OutputCalculator* outputCalculator,
                AxisData<ServoOutput*> outputServos,
                ThrottleOutput* throttleOutput,
                ServoInputReader* servoInputs,
                ThrottleReader* throttleInput,
                Switch* pidSwitch);

    /**
     * @brief Create the task for the controller to process the inputs.
     */
    void begin();

    /**
     * @brief Stop the task of the Controller putting out the data.
     */
    void stop();

private:
    OutputCalculator* outputCalculator;
    AxisData<ServoOutput*> outputServos;
    ThrottleOutput* throttleOutput;
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