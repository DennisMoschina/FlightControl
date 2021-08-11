#ifndef _PID_GAIN_CALCULATOR_H
#define _PID_GAIN_CALCULATOR_H

#include <PID.h>
#include <GainCalculator.h>

class PIDGainCalculator: public GainCalculator {
public:
    PIDGainCalculator(PID* pid, int speedResolution = 1000);

    void calculateGains(int speed);

    /**
     * @brief Set the P gain (for the maximum speed).
     * @param axis the index of the axis (between 0 to 2)
     * @param gain the gain
     */
    void setPGain(byte axis, float gain);
    /**
     * @brief Set the I gain (for the maximum speed).
     * @param axis the index of the axis (between 0 to 2)
     * @param gain the gain
     */
    void setIGain(byte axis, float gain);
    /**
     * @brief Set the D gain (for the maximum speed).
     * @param axis the index of the axis (between 0 to 2)
     * @param gain the gain
     */
    void setDGain(byte axis, float gain);
    /**
     * @brief Set the P gain (for the maximum speed).
     * @param gain the gain
     */
    void setPGain(CorrectionData pGain);
    /**
     * @brief Set the I gain (for the maximum speed).
     * @param gain the gain
     */
    void setIGain(CorrectionData iGain);
    /**
     * @brief Set the D gain (for the maximum speed).
     * @param gain the gain
     */
    void setDGain(CorrectionData dGain);
    void setPGain(float pGain);
    void setIGain(float iGain);
    void setDGain(float dGain);

    void setMinSpeedPGain(float pGain);
    void setMinSpeedIGain(float iGain);
    void setMinSpeedDGain(float dGain);
    void setMinSpeedPGain(byte axis, float gain);
    void setMinSpeedIGain(byte axis, float gain);
    void setMinSpeedDGain(byte axis, float gain);
    void setMinSpeedPGain(CorrectionData pGain);
    void setMinSpeedIGain(CorrectionData iGain);
    void setMinSpeedDGain(CorrectionData dGain);

private:
    PID* pid;

    CorrectionData gainP;
    CorrectionData gainI;
    CorrectionData gainD;

    CorrectionData minSpeedGainP;
    CorrectionData minSpeedGainI;
    CorrectionData minSpeedGainD;

    /**
     * @param minSpeedGain the gain for the minimal speed
     * @param maxSpeedGain the gain for the maximal speed
     * @param speed the current speed
     */
    float gainCalculator(float minSpeedGain, float maxSpeedGain, int speed);

    CorrectionData gainCreator(int speed, CorrectionData minSpeedGain, CorrectionData maxSpeedGain);
};

#endif