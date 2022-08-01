#include "ThrottleManagingFlightController.h"

ThrottleManagingFlightController::ThrottleManagingFlightController(ThrottleReader* throttleReader,
                                                                   FlightController* flightController):
                                                                   FlightController(AxisData<RotationRateOutput*>(), nullptr) {
    this->throttleReader = throttleReader;
}

void ThrottleManagingFlightController::control() {
    this->throttleReader->getSpeed();
    this->flightController->control();
}

RotationData ThrottleManagingFlightController::calculateOutputs(RotationData steeringInput) {
    return steeringInput;
}