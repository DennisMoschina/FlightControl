#ifndef _MENU_H
#define _MENU_H

#include <Controller.h>
#include <AxisData.h>
#include <ServoOutput.h>

/**
 * @brief Configure the settings for the controller.
 * @author Dennis Moschina
 * @version 1.0
 */
class Menu {
public:
    Menu(Controller* controller);
    Menu(Controller* controller, AxisData<ServoOutput*> servoOutputs, ServoInputReader* inputReader);

    /**
     * @brief Start the controller.
     * @details The steering signals are processed.
     */
    void startController();
    /**
     * @brief Stop the controller.
     * @details Interrupt the processing of the steering signals.
     */
    void stopController();
    /**
     * @brief Trim the servos.
     * @details Use the steering inputs to set the new middle for the servos.
     * @param servoOutputs the servos to trim
     * @param inputReader the reader for the steering signals
     */
    void trimServos(AxisData<ServoOutput*> servoOutputs, ServoInputReader* inputReader);
    /**
     * @brief Trim the servos.
     * @details Use the steering inputs to set the new middle for the servos.
     */
    void trimServos();
    /**
     * @brief Stop the trimming of the servos.
     */
    void endTrimming();

private:
    Controller* controller;

    TaskHandle_t trimHandle;

    ServoInputReader* inputs;
    AxisData<ServoOutput*> servos;

    friend void trim(void * parameter);
};

#endif