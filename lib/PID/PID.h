#ifndef _PID_H
#define _PID_H

#include <Arduino.h>

#include <AxisData.h>

#include <Stabilizer.h>

#include <functional>

typedef AxisData<float> CorrectionData;

class PID: public Stabilizer {
public:
    PID();

    /**
     * Calculate the angular rate to output to counteract the error.
     * @param setpoint the desired angular rate
     * @param rotationRate the current angular rate
     * @return the ratio of the maximum output (from -#resolution to resolution)
     */
    RotationData loop(RotationData setpoint, RotationData rotationRate);

    /**
     * Calculate the angular rate to output to counteract the error.
     * @param setpoint the desired angular rate
     * @param rotationRate the current angular rate
     * @param throttleSignal the signal for the throttle
     * @param throttleResolution the maximum value for the throttle
     * @return the ratio of the maximum output (from -#resolution to #resolution)
     */
    RotationData loop(RotationData setpoint, RotationData rotationRate, int throttleSignal, int throttleResolution);

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

    void setFeedForward(float feedForward);
    void setRelaxI(float relaxI);


    void setMinThrottlePGain(float pGain);
    void setMinThrottleIGain(float iGain);
    void setMinThrottleDGain(float dGain);

    void setMinThrottlePGain(byte axis, float gain);
    void setMinThrottleIGain(byte axis, float gain);
    void setMinThrottleDGain(byte axis, float gain);

    void setMinThrottlePGain(CorrectionData pGain);
    void setMinThrottleIGain(CorrectionData iGain);
    void setMinThrottleDGain(CorrectionData dGain);

    void setFeedForward(byte axis, float feedForward);
    void setRelaxI(byte axis, float relaxI);

    void setFeedForward(CorrectionData feedForward);
    void setRelaxI(CorrectionData relaxI);

    void setPGain(float pGain);
    void setIGain(float iGain);
    void setDGain(float dGain);

 

    void setAntiWindup(int antiWindup);

    void setAxisInvert(byte axis, boolean invert);
    void setAxisInvert(AxisData<boolean> invert);

    void reset();

private:
    CorrectionData gainP;
    CorrectionData gainI;
    CorrectionData gainD;

    CorrectionData minThrottleGainP;
    CorrectionData minThrottleGainI;
    CorrectionData minThrottleGainD;

    CorrectionData feedForward;

    CorrectionData relaxI;

    int antiWindup;

    RotationData termIInterval;

    RotationData oldRotationRate;

    AxisData<boolean> axisInvert;

    /**
     * @param minThrottleGain the gain for the minimal throttle
     * @param maxThrottleGain the gain for the maximal throttle
     * @param throttle the current throttle
     * @param throttleRes the maximum throttle
     */
    std::function<float (float, float, int, int)> gainCalculator
        = [](float minThrottleGain, float maxThrottleGain, int throttle, int throttleRes) {
                return map(throttle, 0, throttleRes, minThrottleGain, maxThrottleGain);
            };

    CorrectionData gainCreator(int throttle,
                                int throttleRes,
                                CorrectionData minThrottleGain,
                                CorrectionData maxThrottleGain);

    RotationData calculateOutput(RotationData setpoint,
                                RotationData rotationRate,
                                CorrectionData pGain,
                                CorrectionData iGain,
                                CorrectionData dGain);
};

#endif
