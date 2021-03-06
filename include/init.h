#ifndef _INIT_H
#define _INIT_H

#include <ServoInput.h>
#include <MPU6050.h>
#include <PID.h>

#include <ESP32Servo.h>

#include <OutputCalculator.h>
#include <Controller.h>

#include <Switch.h>

#include <RotationRateOuput.h>
#include <SingleServoOutput.h>
#include <ServoOutput.h>

#include <ServoThrottleReader.h>
#include <ServoThrottleOutput.h>

#include <EWMA.h>
#include <FilteredGyro.h>

#include <init.h>

#define THROTTLE_INPUT_PIN 5
#define THROTTLE_OUTPUT_PIN 2

#define GEAR_INPUT_PIN 27

#define RUDDER_INPUT_PIN 14
#define RUDDER_OUTPUT_PIN 15

#define AILE_INPUT_PIN 13
#define AILE_OUTPUT_PIN 18

#define ELEVATOR_INPUT_PIN 12
#define ELEVATOR_OUTPUT_PIN 19


#define SERVO_MIN 1000
#define SERVO_MAX 2000


extern int16_t MAX_YAW_RATE;
extern int16_t MAX_PITCH_RATE;
extern int16_t MAX_ROLL_RATE;

extern RotationData maxRates;

extern ServoInputSignal* throttleInput;
extern ThrottleReader* throttleInputReader;

extern Servo throttleServo;
extern ThrottleOutput* throttleOutput;

extern ServoInputSignal* gearInput;

extern ServoInputSignal* rudderInput;
extern ServoInputSignal* elevatorInput;
extern ServoInputSignal* aileInput;
extern ServoInputReader* servoInputs;

extern Servo rudderServo;
extern Servo aileServo;
extern Servo elevatorServo;
extern ServoOutput* rudderOutput;
extern ServoOutput* aileOutput;
extern ServoOutput* elevatorOutput;
extern AxisData<ServoOutput*> rateOutputs;

extern MPU6050* mpu;
extern PID* pid;
extern Filter<int, 3>* filter;
extern FilteredGyro* gyro;

extern OutputCalculator* outputCalculator;

class PIDSwitch : public Switch {
public:
    PIDSwitch(ServoInputSignal* switchServo) {
        this->switchServo = switchServo;
    }

    boolean getBoolean() {
        return this->switchServo->getBoolean();
    }

private:
    ServoInputSignal* switchServo;
};

extern PIDSwitch* pidSwitch;

extern Controller* controller;

/**
 * @brief Assign the values to the previously declared variables.
 */
void assign();
/**
 * @brief Configure the gyro, the stabilizer, the inputs and the outputs.
 */
void configure();
/**
 * @brief Start the communication with the receiver;
 */
void startReceiver();
/**
 * @brief Start the servos.
 */
void startServos();
/**
 * @brief Start the Gyro.
 */
void startGyro();

#endif