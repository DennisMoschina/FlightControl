#ifndef _THROTTLE_READER_H
#define _THROTTLE_READER_H

#include <Arduino.h>

#include <SpeedReader.h>
#include <ThrottleOutput.h>

/**
 * @brief This class reads the throttle signal as a speed signal and writes it to an {@link ThrottleOutput}.
 */
class ThrottleReader: public SpeedReader {
public:
    ThrottleReader(int throttleResolution = 1024, ThrottleOutput* throttleOutput = nullptr);

    /**
     * @brief Get the setpoint of the speed and write it to the {@link ThrottleOutput}.
     * 
     * @return the setpoint of the speed
     */
    int getSpeed();

protected:
    virtual int getRawSpeed() = 0;

private:
    ThrottleOutput* throttleOutput;
};

#endif