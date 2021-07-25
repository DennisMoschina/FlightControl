#include <Arduino.h>

#include <OTA.h>

#include <map>
#include <Wire.h>

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


int16_t MAX_YAW_RATE = 360;
int16_t MAX_PITCH_RATE = 360;
int16_t MAX_ROLL_RATE = 720;

RotationData maxRates { MAX_YAW_RATE, MAX_PITCH_RATE, MAX_ROLL_RATE };

ServoInputSignal* throttleInput;
ThrottleReader* throttleInputReader;

Servo throttleServo;
ThrottleOutput* throttleOutput;

ServoInputSignal* gearInput;

ServoInputSignal* rudderInput;
ServoInputSignal* elevatorInput;
ServoInputSignal* aileInput;
ServoInputReader* servoInputs;

Servo rudderServo;
Servo aileServo;
Servo elevatorServo;
ServoOutput* rudderOutput;
ServoOutput* aileOutput;
ServoOutput* elevatorOutput;
AxisData<ServoOutput*> rateOutputs;

MPU6050* mpu;
PID* pid;
EWMA<int, 3>* filter;
FilteredGyro* gyro;

OutputCalculator* outputCalculator;

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

PIDSwitch* pidSwitch;

Controller* controller;


void init() {
    rudderInput = new ServoInputPin<RUDDER_INPUT_PIN>(SERVO_MIN, SERVO_MAX);
    elevatorInput = new ServoInputPin<ELEVATOR_INPUT_PIN>(SERVO_MIN, SERVO_MAX);
    aileInput = new ServoInputPin<AILE_INPUT_PIN>(SERVO_MIN, SERVO_MAX);
    servoInputs = new ServoInputReader(AxisData<ServoInputSignal*> { rudderInput, elevatorInput, aileInput });

    gearInput = new ServoInputPin<GEAR_INPUT_PIN>(SERVO_MIN, SERVO_MAX);

    rudderOutput = new SingleServoOutput(&rudderServo);
    aileOutput = new SingleServoOutput(&aileServo);
    elevatorOutput = new SingleServoOutput(&elevatorServo);

    rateOutputs.rudder = rudderOutput;
    rateOutputs.elevator = elevatorOutput;
    rateOutputs.aileron = aileOutput;

    throttleInput = new ServoInputPin<THROTTLE_INPUT_PIN>(SERVO_MIN, SERVO_MAX);
    throttleInputReader = new ServoThrottleReader(throttleInput);
    throttleOutput = new ServoThrottleOutput(&throttleServo);

    pidSwitch = new PIDSwitch(gearInput);

    mpu = new MPU6050();
    pid = new PID();
    filter = new EWMA<int, 3>();
    gyro = new FilteredGyro(mpu, filter);


    outputCalculator = new OutputCalculator(maxRates, gyro, pid);

    controller = new Controller(outputCalculator, rateOutputs, throttleOutput, servoInputs, throttleInputReader, pidSwitch);

}

void setup() {
    Serial.begin(115200);
    
    startOTA();

    init();
    
    mpu->remapAxis(0, 1);
    mpu->remapAxis(1, 0);

    pid->setAxisInvert( { false, false, true } );
    servoInputs->setInvert( { false, false, false } );

    mpu->begin();

    log_v("Servo range: %d", rudderInput->getRange());

    while (!ServoInput.available()) {  // wait for all signals to be ready
		log_i("Waiting for servo signals...");
		delay(500);
	}

    ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);
	rudderServo.setPeriodHertz(50);
    rudderServo.attach(RUDDER_OUTPUT_PIN, SERVO_MIN, SERVO_MAX);
    aileServo.setPeriodHertz(50);
    aileServo.attach(AILE_OUTPUT_PIN, SERVO_MIN, SERVO_MAX);
    elevatorServo.setPeriodHertz(50);
    elevatorServo.attach(ELEVATOR_OUTPUT_PIN, SERVO_MIN, SERVO_MAX);
    throttleServo.attach(THROTTLE_OUTPUT_PIN);

    aileOutput->setMiddle(1420);
    elevatorOutput->setMiddle(1600);

    controller->begin();
}

void loop() {}
