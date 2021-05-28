#ifndef _MENU_H
#define _MENU_H

#include <Controller.h>
#include <AxisData.h>
#include <ServoOutput.h>

class Menu {
public:
    Menu(Controller* controller);
    Menu(Controller* controller, AxisData<ServoOutput*> servoOutputs, ServoInputReader* inputReader);

    void startController();
    void trimServos(AxisData<ServoOutput*> servoOutputs, ServoInputReader* inputReader);
    void endTrimming();

    friend void trim(void * parameter);

private:
    Controller* controller;

    TaskHandle_t trimHandle;

    ServoInputReader* inputs;
    AxisData<ServoOutput*> servos;

};

#endif