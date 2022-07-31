#ifndef FLIGHTCONTROL_SPEEDBASEDOUTPUTCALCULATOR_H
#define FLIGHTCONTROL_SPEEDBASEDOUTPUTCALCULATOR_H

#include "AbstractOutputCalculator.h"
#include "SpeedReader.h"
#include "GainCalculator.h"

/**
 * @brief This class implements an {@link AbstractOutputCalculator},
 * which controls the output based on the current speed.
 */
class SpeedBasedOutputCalculator: public AbstractOutputCalculator {
public:
    SpeedBasedOutputCalculator(AbstractOutputCalculator* outputCalculator,
                               SpeedReader* speedReader,
                               GainCalculator* gainCalculator);

    RotationData calculateOutput(RotationData servoInput);

    void reset();

    int getSteeringInputResolution();
    int getOutputResolution();

private:
    GainCalculator* gainCalculator;
    SpeedReader* speedReader;
    AbstractOutputCalculator* outputCalculator;
};


#endif