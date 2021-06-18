#ifndef _PID_H
#define _PID_H

#include <Arduino.h>

#include <AxisData.h>

#include <Stabilizer.h>

#include <functional>

typedef AxisData<float> CorrectionData;

/**
 * @brief A PID stabilizer.
 * @author Dennis Moschina
 * @version 1.0
 */
class PID: public Stabilizer {
public:
    PID();

    /**
     * @brief Calculate the angular rate to output to counteract the error.
     * @param setpoint the desired angular rate
     * @param rotationRate the current angular rate
     * @return the ratio of the maximum output (from -#resolution to resolution)
     */
    RotationData loop(RotationData setpoint, RotationData rotationRate);

    /**
     * @brief Calculate the angular rate to output to counteract the error.
     * @param setpoint the desired angular rate
     * @param rotationRate the current angular rate
     * @param throttleSignal the signal for the throttle
     * @param throttleResolution the maximum value for the throttle
     * @return the ratio of the maximum output (from -#resolution to #resolution)
     */
    RotationData loop(RotationData setpoint, RotationData rotationRate, int throttleSignal, int throttleResolution);

    /**
     * @brief Set the P gain (for the maximum throttle).
     * @param axis the index of the axis (between 0 to 2)
     * @param gain the gain
     */
    void setPGain(byte axis, float gain);
    /**
     * @brief Set the I gain (for the maximum throttle).
     * @param axis the index of the axis (between 0 to 2)
     * @param gain the gain
     */
    void setIGain(byte axis, float gain);
    /**
     * @brief Set the D gain (for the maximum throttle).
     * @param axis the index of the axis (between 0 to 2)
     * @param gain the gain
     */
    void setDGain(byte axis, float gain);

    /**
     * @brief Set the P gain (for the maximum throttle).
     * @param gain the gain
     */
    void setPGain(CorrectionData pGain);
    /**
     * @brief Set the I gain (for the maximum throttle).
     * @param gain the gain
     */
    void setIGain(CorrectionData iGain);
    /**
     * @brief Set the D gain (for the maximum throttle).
     * @param gain the gain
     */
    void setDGain(CorrectionData dGain);

    /**
     * @brief Set the feed forward.
     * @param axis the index of the axis (between 0 to 2)
     * @param feedForward the feed forward
     */
    void setFeedForward(byte axis, float feedForward);
    /**
     * @brief Set the factor by which the interval is reduced each iteration.
     * @param axis the index of the axis (between 0 to 2)
     * @param relaxI the factor by which the interval is reduced
     */
    void setRelaxI(byte axis, float relaxI);

    /**
     * @brief Set the feed forward.
     * @param feedForward the feed forward
     */
    void setFeedForward(CorrectionData feedForward);
    /**
     * @brief Set the factor by which the interval is reduced each iteration.
     * @param relaxI the factor by which the interval is reduced
     */
    void setRelaxI(CorrectionData relaxI);

    /**
     * @brief Set the feed forward.
     * @param feedForward the feed forward
     */
    void setFeedForward(float feedForward);
    /**
     * @brief Set the factor by which the interval is reduced each iteration.
     * @param relaxI the factor by which the interval is reduced
     */
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

    void setPGain(float pGain);
    void setIGain(float iGain);
    void setDGain(float dGain);

 
    /**
     * @brief Set the border for the interval.
     * @param antiWindup the new boarder for the interval
     */
    void setAntiWindup(int antiWindup);

    /**
     * @brief Invert the output of the PID loop.
     * @param axis the index of the axis (between 0 to 2)
     * @param invert the output should be inverted
     */
    void setAxisInvert(byte axis, boolean invert);
    /**
     * @brief Invert the output of the PID loop.
     * @param invert the output should be inverted
     */
    void setAxisInvert(AxisData<boolean> invert);

    /**
     * @brief Reset the stored data in the loop. All settings are kept.
     */
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
