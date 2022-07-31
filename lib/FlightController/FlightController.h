#ifndef _FLIGHT_CONTROLLER_H
#define _FLIGHT_CONTROLLER_H

#include <SteeringInputReader.h>
#include <RotationRateOutput.h>
#include <SpeedReader.h>

/**
 * @brief Manage the calculation of the output based on the steering signals.
 * @author Dennis Moschina
 * @version 1.0
 */
class FlightController {
public:
    FlightController(AxisData<RotationRateOutput*> rotationOutputs,
                SteeringInputReader* steeringInputs,
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
    
    /**
     * @brief Write to the outputs for this period based on the steering signal.
     */
    void control();

protected:
    AxisData<RotationRateOutput*> rotationOutputs;
    SteeringInputReader* steeringInputs;
    SpeedReader* speedInput;
    int cycleDuration;

    unsigned long oldTimestamp;

#if defined(ESP8266) || defined(ESP32)
    TaskHandle_t pidLoopHandle;

    friend void controlTask(void * parameter);
#endif

    /**
     * @brief Calculate the outputs to write in order to follow the steering inputs.
     * 
     * @details This method should be overriden in the implementing class to change the behaviour of the FlightController.
     * 
     * @param steeringInput the steering signal in percent of the maximum rates
     * @return the outputs to write in order to follow the steering inputs
     */
    virtual RotationData calculateOutputs(RotationData steeringInput) = 0;

    void writeOutputs(RotationData output);

    void matchFrequency();
};

#endif