#ifndef _PID_H
#define _PID_H

#include <Arduino.h>

#include <AxisData.h>

typedef AxisData<float> CorrectionData;

class PID {
public:
    PID();
    /**
     * Calculate the angular rate to output to counteract the error.
     * @param setpoint the desired angular rate
     * @param processVariable the current angular rate
     * @return the angular rate to counteract the error
     */
    RotationData loop(RotationData setpoint, RotationData rotationRate);

    void setPGain(float x, float y, float z);
    void setIGain(float x, float y, float z);
    void setDGain(float x, float y, float z);

private:
    CorrectionData gainP;
    CorrectionData gainI;
    CorrectionData gainD;

    CorrectionData relaxI;

    RotationData termIInterval;

    RotationData oldRotationRate;
};

#endif
