#include <PIDGainCalculator.h>


PIDGainCalculator::PIDGainCalculator(PID* pid, int speedResolution) {
    this->pid = pid;
    this->speedResolution = speedResolution;
}

void PIDGainCalculator::calculateGains(int speed) {
    this->pid->setPGain(this->gainCreator(speed, this->minSpeedGainP, this->gainP));
    this->pid->setIGain(this->gainCreator(speed, this->minSpeedGainI, this->gainI));
    this->pid->setDGain(this->gainCreator(speed, this->minSpeedGainD, this->gainD));
}


CorrectionData PIDGainCalculator::gainCreator(int speed, CorrectionData minSpeedGain, CorrectionData maxSpeedGain) {
    CorrectionData gain;
    for (int i = 0; i < 3; i++) {
        gain[i] = this->gainCalculator(minSpeedGain[i], maxSpeedGain[i], speed);
    }

    return gain;
}



float PIDGainCalculator::gainCalculator(float minSpeedGain, float maxSpeedGain, int speed) {
    return (float)(speed) * (minSpeedGain - maxSpeedGain) / (float)(this->speedResolution) + maxSpeedGain;
}


void PIDGainCalculator::setPGain(byte axis, float gain) {
    this->gainP[axis] = gain;
    log_d("axis %d: \t gainTo %7.2f, \t gainIs %7.2f", axis, gain, this->gainP[axis]);
}

void PIDGainCalculator::setIGain(byte axis, float gain) {
    this->gainI[axis] = gain;
    log_d("axis %d: \t gainTo %7.2f, \t gainIs %7.2f", axis, gain, this->gainI[axis]);
}

void PIDGainCalculator::setDGain(byte axis, float gain) {
    this->gainD[axis] = gain;
    log_d("axis %d: \t gainTo %7.2f, \t gainIs %7.2f", axis, gain, this->gainD[axis]);
}

void PIDGainCalculator::setPGain(CorrectionData pGain) {
    this->gainP = pGain;
}

void PIDGainCalculator::setIGain(CorrectionData iGain) {
    this->gainI = iGain;
}

void PIDGainCalculator::setDGain(CorrectionData dGain) {
    this->gainD = dGain;
}


void PIDGainCalculator::setMinSpeedPGain(float pGain) {
    this->minSpeedGainP = pGain;
}
void PIDGainCalculator::setMinSpeedIGain(float iGain) {
    this->minSpeedGainI = iGain;
}
void PIDGainCalculator::setMinSpeedDGain(float dGain) {
    this->minSpeedGainD = dGain;
}

void PIDGainCalculator::setMinSpeedPGain(byte axis, float gain) {
    this->minSpeedGainP[axis] = gain;
}
void PIDGainCalculator::setMinSpeedIGain(byte axis, float gain) {
    this->minSpeedGainI[axis] = gain;
}
void PIDGainCalculator::setMinSpeedDGain(byte axis, float gain) {
    this->minSpeedGainD[axis] = gain;
}


void PIDGainCalculator::setMinSpeedPGain(CorrectionData pGain) {
    this->minSpeedGainP = pGain;
}
void PIDGainCalculator::setMinSpeedIGain(CorrectionData iGain) {
    this->minSpeedGainI = iGain;
}
void PIDGainCalculator::setMinSpeedDGain(CorrectionData dGain) {
    this->minSpeedGainD = dGain;
}