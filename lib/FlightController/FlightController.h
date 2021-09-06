#ifndef _FLIGHT_CONTROLLER_H
#define _FLIGHT_CONTROLLER_H

#include <AbstractOutputCalculator.h>
#include <ESP32Servo.h>
#include <ServoInputReader.h>
#include <Switch.h>
#include <ServoOutput.h>
#include <SpeedReader.h>

/**
 * @brief Manage the calculation of the output based on the steering signals.
 * @author Dennis Moschina
 * @version 1.0
 */
class FlightController {
public:
    FlightController(AxisData<ServoOutput*> outputServos,
                ServoInputReader* servoInputs,
                SpeedReader* speedInput = nullptr,
                int frequency = 50);

#if defined(ESP8266) || defined(ESP32)
    /**
     * @brief Create the task for the controller to process the inputs.
     */
    void begin();

    /**
     * @brief Stop the task of the FlightController putting out the data.
     */
    void stop();
#endif

protected:
    AxisData<ServoOutput*> outputServos;
    ServoInputReader* servoInputs;
    SpeedReader* speedInput;
    int cycleDuration;

    unsigned long oldTimestamp;

#if defined(ESP8266) || defined(ESP32)
    TaskHandle_t pidLoopHandle;

    friend void controlTask(void * parameter);
    friend void controlTaskThrottle(void * parameter);
#endif

    virtual void control() = 0;
    virtual void controlWithThrottle() = 0;

    void writeOutputs(RotationData output);

    void matchFrequency();
};

#endif