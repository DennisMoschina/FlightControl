#ifndef _PID_H
#define _PID_H

#include <Arduino.h>

#include <AxisData.h>

#include <Stabilizer.h>

typedef AxisData<float> CorrectionData;

class PID: public Stabilizer {
public:
    PID();
    /**
     * Calculate the angular rate to output to counteract the error.
     * @param setpoint the desired angular rate
     * @param rotationRate the current angular rate
     * @return the percent of the maximum output
     */
    RotationData loop(RotationData setpoint, RotationData rotationRate);

    void setPGain(byte axis, float gain);
    void setIGain(byte axis, float gain);
    void setDGain(byte axis, float gain);

    void setPGain(CorrectionData pGain);
    void setIGain(CorrectionData iGain);
    void setDGain(CorrectionData dGain);

    void setFeedForward(byte axis, float feedForward);
    void setRelaxI(byte axis, float relaxI);

    void setFeedForward(CorrectionData feedForward);
    void setRelaxI(CorrectionData relaxI);

    void setAntiWindup(int antiWindup);

    void setAxisInvert(byte axis, boolean invert);
    void setAxisInvert(AxisData<boolean> invert);

private:
    CorrectionData gainP;
    CorrectionData gainI;
    CorrectionData gainD;

    CorrectionData feedForward;

    CorrectionData relaxI;

    int antiWindup;

    RotationData termIInterval;

    RotationData oldRotationRate;

    AxisData<boolean> axisInvert;
};

#endif
