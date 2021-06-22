#include <Arduino.h>

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

#include <Menu.h>
#include <SerialMonitorInterface.h>

#include <ServoThrottleReader.h>
#include <ServoThrottleOutput.h>

#define THROTTLE_INPUT_PIN 1
#define THROTTLE_OUTPUT_PIN 1

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

ServoInputSignal* throttleInput = new ServoInputPin<THROTTLE_INPUT_PIN>(SERVO_MIN, SERVO_MAX);
ThrottleReader* throttleInputReader = new ServoThrottleReader(throttleInput);

Servo throttleServo;
ThrottleOutput* throttleOutput = new ServoThrottleOutput(&throttleServo);

ServoInputSignal* gearInput = new ServoInputPin<GEAR_INPUT_PIN>(SERVO_MIN, SERVO_MAX);

ServoInputSignal* rudderInput = new ServoInputPin<RUDDER_INPUT_PIN>(SERVO_MIN, SERVO_MAX);
ServoInputSignal* elevatorInput = new ServoInputPin<ELEVATOR_INPUT_PIN>(SERVO_MIN, SERVO_MAX);
ServoInputSignal* aileInput = new ServoInputPin<AILE_INPUT_PIN>(SERVO_MIN, SERVO_MAX);
ServoInputReader servoInputs(AxisData<ServoInputSignal*> { rudderInput, elevatorInput, aileInput });

Servo rudderServo;
Servo aileServo;
Servo elevatorServo;
ServoOutput* rudderOutput = new SingleServoOutput(&rudderServo);
ServoOutput* aileOutput = new SingleServoOutput(&aileServo);
ServoOutput* elevatorOutput = new SingleServoOutput(&elevatorServo);
AxisData<ServoOutput*> rateOutputs { rudderOutput, elevatorOutput, aileOutput };

MPU6050 mpu = MPU6050();
PID pid = PID();

OutputCalculator outputCalculator(maxRates, &mpu, &pid);

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

PIDSwitch pidSwitch = PIDSwitch(gearInput);

Controller controller(&outputCalculator, rateOutputs, throttleOutput, &servoInputs, throttleInputReader, &pidSwitch);

Menu menu(&controller, rateOutputs, &servoInputs);

UserInterface* userInterface = new SerialMonitorInterface(&menu);

void setup() {
    Serial.begin(115200);

    mpu.remapAxis(0, 1);
    mpu.remapAxis(1, 0);

    pid.setAxisInvert( { false, false, true } );
    servoInputs.setInvert( { false, false, false } );

    mpu.begin();

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

    controller.begin();
}

void loop() {
    userInterface->handle();
    delay(100);
}
