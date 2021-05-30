#include <PID.h>

#define DEFAULT_P_GAIN 0.25
#define DEFAULT_I_GAIN 0.05
#define DEFAULT_D_GAIN 0.15

#define DEFAULT_FEED_FORWARD 0.138

#define DEFAULT_I_RELAX 0.99

#define DEFAULT_P_GAIN_YAW 0.17
#define DEFAULT_P_GAIN_PITCH 0.25
#define DEFAULT_P_GAIN_ROLL 0.06

#define DEFAULT_I_GAIN_YAW 0.03
#define DEFAULT_I_GAIN_ROLL 0.0075
#define DEFAULT_D_GAIN_ROLL 0.1

#define DEFAULT_ANTI_WINDUP 1024

PID::PID() {
    //this->gainP = DEFAULT_P_GAIN;
    this->gainI = DEFAULT_I_GAIN;

    this->gainP.yaw = DEFAULT_P_GAIN_YAW;
    this->gainP.pitch = DEFAULT_P_GAIN_PITCH;
    this->gainP.roll = DEFAULT_P_GAIN_ROLL;

    this->gainI.yaw = DEFAULT_I_GAIN_YAW;
    this->gainI.roll = DEFAULT_I_GAIN_ROLL;
    this->gainD.roll = DEFAULT_D_GAIN_ROLL;

    this->gainD = DEFAULT_D_GAIN;
    this->relaxI = DEFAULT_I_RELAX;
    this->antiWindup = DEFAULT_ANTI_WINDUP;

    this->axisInvert = true;

    this->feedForward = DEFAULT_FEED_FORWARD;
}

RotationData PID::loop(RotationData setpoint, RotationData rotationRate) {
    setpoint.roll = -setpoint.roll;
    const RotationData error = setpoint - rotationRate;
    
    RotationData termP = error * this->gainP;
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
    log_v("termP\t\t\tx:%5d, y:%5d, z:%5d", termP.x, termP.y, termP.z);
    log_v("termI\t\t\tx:%5d, y:%5d, z:%5d", termI.x, termI.y, termI.z);
    log_v("termD\t\t\tx:%5d, y:%5d, z:%5d", termD.x, termD.y, termD.z);

    log_v("Output pre cap\t\t\tx:%5d, y:%5d, z:%5d", output.x, output.y, output.z);

    for (int i = 0; i < 3; i++) {
        output[i] *= this->axisInvert[i] ? -1 : 1;
        if (output[i] > 1024) output[i] = 1024;
        else if (output[i] < -1024) output[i] = -1024;
    }
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

void PID::reset() {
    this->termIInterval = 0;
    this->oldRotationRate = 0;
}