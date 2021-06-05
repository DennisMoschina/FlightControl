#include <PID.h>

#define DEFAULT_P_GAIN 0.25
#define DEFAULT_I_GAIN 0.05
#define DEFAULT_D_GAIN 0.15

#define DEFAULT_FEED_FORWARD 0.138

#define DEFAULT_I_RELAX 0.99

#define DEFAULT_P_GAIN_YAW 0.17
#define DEFAULT_P_GAIN_PITCH 0.25
#define DEFAULT_P_GAIN_ROLL 0.06

#define DEFAULT_I_GAIN_YAW 0//.03
#define DEFAULT_I_GAIN_ROLL 0//.0075

#define DEFAULT_D_GAIN_ROLL 0//.1

#define DEFAULT_ANTI_WINDUP 100

PID::PID() {
    this->setPGain(0, DEFAULT_P_GAIN_YAW);
    this->setPGain(1, DEFAULT_P_GAIN_PITCH);
    this->setPGain(2, DEFAULT_P_GAIN_ROLL);

    this->setIGain(0, DEFAULT_I_GAIN_YAW);
    this->setIGain(1, DEFAULT_I_GAIN);
    this->setIGain(2, DEFAULT_I_GAIN_ROLL);

    this->gainD.roll = DEFAULT_D_GAIN_ROLL;

    this->gainD = DEFAULT_D_GAIN;

    this->relaxI = DEFAULT_I_RELAX;
    this->setAntiWindup(DEFAULT_ANTI_WINDUP);

    this->axisInvert = true;

    this->setFeedForward(DEFAULT_FEED_FORWARD);
}

RotationData PID::loop(RotationData setpoint, RotationData rotationRate) {
    return this->calculateOutput(setpoint, rotationRate, this->gainP, this->gainI, this->gainD);
}


RotationData PID::loop(RotationData setpoint,
                        RotationData rotationRate,
                        int throttleSignal,
                        int throttleResolution) {

    CorrectionData pGain = this->gainCreator(throttleSignal,
                                            throttleResolution,
                                            this->minThrottleGainP,
                                            this->gainP);

    CorrectionData iGain = this->gainCreator(throttleSignal,
                                            throttleResolution,
                                            this->minThrottleGainI,
                                            this->gainI);

    CorrectionData dGain = this->gainCreator(throttleSignal,
                                            throttleResolution,
                                            this->minThrottleGainD,
                                            this->gainD);

    return this->calculateOutput(setpoint, rotationRate, pGain, iGain, dGain);
}



void PID::setPGain(byte axis, float gain) {
    this->gainP[axis] = gain * (this->resolution / 100);
}

void PID::setIGain(byte axis, float gain) {
    this->gainI[axis] = gain * (this->resolution / 100);
}

void PID::setDGain(byte axis, float gain) {
    this->gainD[axis] = gain * (this->resolution / 100);
}

void PID::setPGain(CorrectionData pGain) {
    this->gainP = pGain * (this->resolution / 100);
}

void PID::setIGain(CorrectionData iGain) {
    this->gainI = iGain * (this->resolution / 100);
}

void PID::setDGain(CorrectionData dGain) {
    this->gainD = dGain * (this->resolution / 100);
}


void PID::setAxisInvert(byte axis, boolean invert) {
    this->axisInvert[axis] = invert;
}

void PID::setAxisInvert(AxisData<boolean> invert) {
    this->axisInvert = invert;
}

void PID::setFeedForward(byte axis, float feedForward) {
    this->feedForward[axis] = feedForward * (this->resolution / 100);
}

void PID::setRelaxI(byte axis, float relaxI) {
    this->relaxI[axis] = relaxI;
}

void PID::setFeedForward(CorrectionData feedForward) {
    this->feedForward = feedForward * (this->resolution / 100);
}
void PID::setAntiWindup(int antiWindup) {
    this->antiWindup = antiWindup * (this->resolution / 100);
}
void PID::setRelaxI(CorrectionData relaxI) {
    this->relaxI = relaxI;
}

void PID::reset() {
    this->termIInterval = 0;
    this->oldRotationRate = 0;
}


void PID::setPGain(float pGain) {
    for (int i = 0; i < 3; i++) {
        this->setPGain(i, pGain);
    }
}
void PID::setIGain(float iGain) {
    for (int i = 0; i < 3; i++) {
        this->setIGain(i, iGain);
    }
}
void PID::setDGain(float dGain) {
    for (int i = 0; i < 3; i++) {
        this->setDGain(i, dGain);
    }
}

void PID::setFeedForward(float feedForward) {
    for (int i = 0; i < 3; i++) {
        this->setFeedForward(i, feedForward);
    }
}
void PID::setRelaxI(float relaxI) {
    for (int i = 0; i < 3; i++) {
        this->setRelaxI(i, relaxI);
    }
}





void PID::setMinThrottlePGain(float pGain) {
    this->minThrottleGainP = pGain * (this->resolution / 100);
}
void PID::setMinThrottleIGain(float iGain) {
    this->minThrottleGainI = iGain * (this->resolution / 100);
}
void PID::setMinThrottleDGain(float dGain) {
    this->minThrottleGainD = dGain * (this->resolution / 100);
}

void PID::setMinThrottlePGain(byte axis, float gain) {
    this->minThrottleGainP[axis] = gain;
}
void PID::setMinThrottleIGain(byte axis, float gain) {
    this->minThrottleGainI[axis] = gain;
}
void PID::setMinThrottleDGain(byte axis, float gain) {
    this->minThrottleGainD[axis] = gain;
}


void PID::setMinThrottlePGain(CorrectionData pGain) {
    this->minThrottleGainP = pGain;
}
void PID::setMinThrottleIGain(CorrectionData iGain) {
    this->minThrottleGainI = iGain;
}
void PID::setMinThrottleDGain(CorrectionData dGain) {
    this->minThrottleGainD = dGain;
}



CorrectionData PID::gainCreator(int throttle,
                                int throttleRes,
                                CorrectionData minThrottleGain,
                                CorrectionData maxThrottleGain) {
    CorrectionData gain;
    for (int i = 0; i < 3; i++) {
        gain[i] = this->gainCalculator(minThrottleGain[i], maxThrottleGain[i], throttle, throttleRes);
    }

    return gain;
}

RotationData PID::calculateOutput(RotationData setpoint,
                                RotationData rotationRate,
                                CorrectionData pGain,
                                CorrectionData iGain,
                                CorrectionData dGain) {
    setpoint.roll = -setpoint.roll;
    const RotationData error = setpoint - rotationRate;
    
    RotationData termP = error * pGain;
    this->termIInterval = (this->termIInterval + error) * this->relaxI;
    RotationData termI = this->termIInterval * iGain;
    RotationData termD = (rotationRate - this->oldRotationRate) * dGain;

    this->oldRotationRate = rotationRate;

    for (int i = 0; i < 3; i++) {
        if (termI[i] > this->antiWindup) {
            termI[i] = this->antiWindup;
            this->termIInterval[i] = termI[i] / gainI[i];
        } else if (termI[i] < -this->antiWindup) {
            termI[i] = -this->antiWindup;
            this->termIInterval[i] = termI[i] / gainI[i];
        }
    }

    RotationData output = termP + termI + termD + setpoint * this->feedForward;
    log_v("termP\t\t\tx:%5d, y:%5d, z:%5d", termP.x, termP.y, termP.z);
    log_v("termI\t\t\tx:%5d, y:%5d, z:%5d", termI.x, termI.y, termI.z);
    log_v("termD\t\t\tx:%5d, y:%5d, z:%5d", termD.x, termD.y, termD.z);

    log_v("Output pre cap\t\t\tx:%5d, y:%5d, z:%5d", output.x, output.y, output.z);

    for (int i = 0; i < 3; i++) {
        output[i] *= this->axisInvert[i] ? -1 : 1;
        if (output[i] > this->resolution) output[i] = this->resolution;
        else if (output[i] < -this->resolution) output[i] = -this->resolution;
    }
    return output;
}