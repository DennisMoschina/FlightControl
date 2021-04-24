#ifndef _PID_H
#define _PID_H

#include <Arduino.h>

#include <AxisData.h>

typedef AxisData<float> CorrectionData;

class PID {
public:
    PID();
    RotationData loop(RotationData setpoint, RotationData processVariable);

    void setPGain(float x, float y, float z);
    void setIGain(float x, float y, float z);
    void setDGain(float x, float y, float z);

private:
    CorrectionData gainP;
    CorrectionData gainI;
    CorrectionData gainD;
};

#endif
