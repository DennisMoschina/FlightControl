#ifndef _THROTTLE_MANAGING_FC_H_
#define _THROTTLE_MANAGING_FC_H_

#include "FlightController.h"
#include <ThrottleReader/ThrottleReader.h>

class ThrottleManagingFlightController: public FlightController {
public:
    ThrottleManagingFlightController(ThrottleReader* throttleReader, FlightController* flightController);

    /**
     * @brief Write to the outputs for this period based on the steering signal. Does also include the throttle.
     */
    void control();

private:
    ThrottleReader* throttleReader;
    FlightController* flightController;

    RotationData calculateOutputs(RotationData steeringInput);
};

#endif