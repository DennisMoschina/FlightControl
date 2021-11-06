#ifndef _MULTI_MODE_FLIGHT_CONTROLLER_H
#define _MULTI_MODE_FLIGHT_CONTROLLER_H

#include <FlightController.h>

/**
 * @brief Manage the calculation of the output based on the steering signals.
 * @author Dennis Moschina
 * @version 1.0
 */
template<int FLIGHT_MODES>
class MultiModeFlightController: public FlightController {
public:
    MultiModeFlightController(AbstractOutputCalculator* outputCalculators[FLIGHT_MODES],
                AxisData<ServoOutput*> outputServos,
                ServoInputReader* servoInputs,
                Switch* modeSwitch,
                SpeedReader* speedInput = nullptr,
                int frequency = 50);

private:
    AbstractOutputCalculator* outputCalculators[FLIGHT_MODES];
    Switch* modeSwitch;

    void control();
    void controlWithThrottle();
};

#endif

template<int FLIGHT_MODES>
MultiModeFlightController<FLIGHT_MODES>::MultiModeFlightController(AbstractOutputCalculator* outputCalculators[],
                                                                    AxisData<ServoOutput*> outputServos,
                                                                    ServoInputReader* servoInputs,
                                                                    Switch* modeSwitch,
                                                                    SpeedReader* speedInput,
                                                                    int frequency):
                                                                    FlightController(outputServos,
                                                                                    servoInputs,
                                                                                    speedInput,
                                                                                    frequency) {
    for (int i = 0; i < FLIGHT_MODES; i++) this->outputCalculators[i] = outputCalculators[i];
    this->modeSwitch = modeSwitch;
}

template<int FLIGHT_MODES>
void MultiModeFlightController<FLIGHT_MODES>::control() {
    RotationData servoInput = this->servoInputs->readInput();
    log_d("Input\t\t\tx:%5d, y:%5d, z:%5d", servoInput.x, servoInput.y, servoInput.z);

    RotationData output = this->outputCalculators[this->modeSwitch->getPosition()]
                            ->calculateOutput(servoInput);

    this->writeOutputs(output);

    this->matchFrequency();
}

template<int FLIGHT_MODES>
void MultiModeFlightController<FLIGHT_MODES>::controlWithThrottle() {
    RotationData servoInput = this->servoInputs->readInput();
    log_v("read steering inputs");
    int throttleSignal = this->speedInput->getSpeed();
    log_d("Input\t\tx:%5d, y:%5d, z:%5d, t:%5d", servoInput.x, servoInput.y, servoInput.z, throttleSignal);

    RotationData output = this->outputCalculators[this->modeSwitch->getPosition()]
                            ->calculateOutput(servoInput, throttleSignal);

    this->writeOutputs(output);

    this->matchFrequency();
}