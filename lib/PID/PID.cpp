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

RotationData PID::loop(RotationData setpoint, RotationData processVariable) {
    const RotationData error = setpoint - processVariable;
    RotationData termP = this->gainP * error;
}
