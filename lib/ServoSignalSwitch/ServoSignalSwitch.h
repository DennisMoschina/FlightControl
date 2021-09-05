#ifndef _SERVO_SIGNAL_SWITCH_H
#define _SERVO_SIGNAL_SWITCH_H

#include <ServoInput.h>
#include <Switch.h>

class ServoSignalSwitch: public Switch {
public:
    ServoSignalSwitch(int positions, ServoInputSignal* servoInput);
    
    int getPosition();
private:
    ServoInputSignal* servoInput;
};

#endif