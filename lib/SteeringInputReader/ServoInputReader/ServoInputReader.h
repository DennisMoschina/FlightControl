#ifndef _SERVO_INPUT_READER_H
#define _SERVO_INPUT_READER_H

#include <SteeringInputReader.h>
#include <ServoInput.h>
#include <AxisData.h>

/**
 * @brief A reader for the servo signals.
 * @author Dennis Moschina
 * @version 1.0
 */
class ServoInputReader: public SteeringInputReader {
public:
    ServoInputReader(AxisData<ServoInputSignal*> servoInputs);

    RotationData readInput();

    void calibrate();

private:
    AxisData<ServoInputSignal*> servoInputs;
};

#endif