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

    void setPGain(float pGain);
    void setIGain(float iGain);
    void setDGain(float dGain);

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

    CorrectionData getPGain();
    CorrectionData getIGain();
    CorrectionData getDGain();

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

    CorrectionData feedForward;

    CorrectionData relaxI;

    int antiWindup;

    RotationData termIInterval;

    RotationData oldRotationRate;

    AxisData<boolean> axisInvert;

    RotationData calculateOutput(RotationData setpoint,
                                RotationData rotationRate,
                                CorrectionData pGain,
                                CorrectionData iGain,
                                CorrectionData dGain);
};

#endif
