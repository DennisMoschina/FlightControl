#ifndef _MULTI_MODE_FLIGHT_CONTROLLER_H
#define _MULTI_MODE_FLIGHT_CONTROLLER_H

#include <FlightController.h>
#include <AbstractOutputCalculator.h>
#include <Switch.h>

/**
 * @brief Manage the calculation of the output based on the steering signals.
 * @author Dennis Moschina
 * @version 1.0
 */
template<int FLIGHT_MODES>
class MultiModeFlightController: public FlightController {
public:
    MultiModeFlightController(AbstractOutputCalculator* outputCalculators[FLIGHT_MODES],
                AxisData<RotationRateOutput*> rotationOutputs,
                SteeringInputReader* steeringInputs,
                Switch* modeSwitch,
                SpeedReader* speedInput = nullptr,
                int frequency = 50);

protected:
    RotationData calculateOutputs(RotationData steeringInput);

private:
    AbstractOutputCalculator* outputCalculators[FLIGHT_MODES];
    Switch* modeSwitch;
};

#endif

template<int FLIGHT_MODES>
MultiModeFlightController<FLIGHT_MODES>::MultiModeFlightController(AbstractOutputCalculator* outputCalculators[],
                                                                    AxisData<RotationRateOutput*> rotationOutputs,
                                                                    SteeringInputReader* steeringInputs,
                                                                    Switch* modeSwitch,
                                                                    SpeedReader* speedInput,
                                                                    int frequency):
                                                                    FlightController(rotationOutputs,
                                                                                    steeringInputs,
                                                                                    speedInput,
                                                                                    frequency) {
    for (int i = 0; i < FLIGHT_MODES; i++) this->outputCalculators[i] = outputCalculators[i];
    this->modeSwitch = modeSwitch;
}

template<int FLIGHT_MODES>
RotationData MultiModeFlightController<FLIGHT_MODES>::calculateOutputs(RotationData steeringInput) {
    return this->outputCalculators[this->modeSwitch->getPosition()]
                            ->calculateOutput(steeringInput);
}