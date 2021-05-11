#include <PID.h>

#define DEFAULT_P_GAIN 0.25
#define DEFAULT_I_GAIN 0.025
#define DEFAULT_D_GAIN 0.15

#define DEFAULT_FEED_FORWARD 0.25

#define DEFAULT_I_RELAX 0.995

#define DEFAULT_ANTI_WINDUP 500

PID::PID() {
    this->gainP = DEFAULT_P_GAIN;
    this->gainI = DEFAULT_I_GAIN;
    this->gainD = DEFAULT_D_GAIN;
    this->relaxI = DEFAULT_I_RELAX;
    this->antiWindup = DEFAULT_ANTI_WINDUP;

    this->axisInvert = true;
}

RotationData PID::loop(RotationData setpoint, RotationData rotationRate) {
    const RotationData error = setpoint - rotationRate;

    RotationData termP = this->gainP * error;
    this->termIInterval = (this->termIInterval + error) * this->relaxI;
    RotationData termI = this->termIInterval * this->gainI;
    RotationData termD = (rotationRate - this->oldRotationRate) * this->gainD;

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
    for (int i = 0; i < 3; i++) output[i] *= this->axisInvert[i] ? -1 : 1;
    return output;
}


void PID::setPGain(byte axis, float gain) {
    this->gainP[axis] = gain;
}

void PID::setIGain(byte axis, float gain) {
    this->gainI[axis] = gain;
}

void PID::setDGain(byte axis, float gain) {
    this->gainD[axis] = gain;
}

void PID::setPGain(CorrectionData pGain) {
    this->gainP = pGain;
}

void PID::setIGain(CorrectionData iGain) {
    this->gainI = iGain;
}

void PID::setDGain(CorrectionData dGain) {
    this->gainD = dGain;
}


void PID::setAxisInvert(byte axis, boolean invert) {
    this->axisInvert[axis] = invert;
}

void PID::setAxisInvert(AxisData<boolean> invert) {
    this->axisInvert = invert;
}

void PID::setFeedForward(byte axis, float feedForward) {
    this->feedForward[axis] = feedForward;
}

void PID::setRelaxI(byte axis, float relaxI) {
    this->relaxI[axis] = relaxI;
}

void PID::setFeedForward(CorrectionData feedForward) {
    this->feedForward = feedForward;
}
void PID::setAntiWindup(int antiWindup) {
    this->antiWindup = antiWindup;
}
void PID::setRelaxI(CorrectionData relaxI) {
    this->relaxI = relaxI;
}
