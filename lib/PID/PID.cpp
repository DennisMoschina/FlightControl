#include <PID.h>

#define DEFAULT_P_GAIN 0.25
#define DEFAULT_I_GAIN 0.025
#define DEFAULT_D_GAIN 0.15

#define DEFAULT_I_RELAX 0.995

PID::PID() {
    this->gainP = DEFAULT_P_GAIN;
    this->gainI = DEFAULT_I_GAIN;
    this->gainD = DEFAULT_D_GAIN;
    this->relaxI = DEFAULT_I_RELAX;
}

RotationData PID::loop(RotationData setpoint, RotationData rotationRate) {
    const RotationData error = setpoint - rotationRate;

    RotationData termP = this->gainP * error;
    this->termIInterval = (this->termIInterval + error) * this->relaxI;
    RotationData termI = this->termIInterval * this->gainI;
    RotationData termD = (rotationRate - this->oldRotationRate) * this->gainD;

    this->oldRotationRate = rotationRate;

    for (int i = 0; i < 3; i++) {
        if (termI[i] > 100) {
            termI[i] = 100;
            this->termIInterval[i] = termI[i] / gainI[i];
        } else if (termI[i] < -100) {
            termI[i] = -100;
            this->termIInterval[i] = termI[i] / gainI[i];
        }
    }

    RotationData output = (termP + termI + termD) * (float) -1;
    return output;
}
