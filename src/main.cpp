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

#define GEAR_INPUT_PIN 27

#define RUDDER_INPUT_PIN 14
#define RUDDER_OUTPUT_PIN 15

#define AILE_INPUT_PIN 13
#define AILE_OUTPUT_PIN 18

#define ELEVATOR_INPUT_PIN 12
#define ELEVATOR_OUTPUT_PIN 19


#define SERVO_MIN 1000
#define SERVO_MAX 2000

// #define RUDDER_MIN 1000 //1068
// #define RUDDER_MAX 2000 //1871

int16_t MAX_YAW_RATE = 360;
int16_t MAX_PITCH_RATE = 360;
int16_t MAX_ROLL_RATE = 720;

RotationData maxRates { MAX_YAW_RATE, MAX_PITCH_RATE, MAX_ROLL_RATE };

ServoInputPin<GEAR_INPUT_PIN> gearInput(SERVO_MIN, SERVO_MAX);

ServoInputPin<RUDDER_INPUT_PIN> rudderInput(SERVO_MIN, SERVO_MAX);
ServoInputPin<ELEVATOR_INPUT_PIN> elevatorInput(SERVO_MIN, SERVO_MAX);
ServoInputPin<AILE_INPUT_PIN> aileInput(SERVO_MIN, SERVO_MAX);
ServoInputReader servoInputs(AxisData<ServoInputSignal*> { &rudderInput, &elevatorInput, &aileInput });

Servo rudderServo;
Servo aileServo;
Servo elevatorServo;
AxisData<Servo*> servos { &rudderServo, &elevatorServo, &aileServo };

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

PIDSwitch pidSwitch = PIDSwitch(&gearInput);

Controller controller(&outputCalculator, servos,
                &servoInputs,
                &pidSwitch);

void setup() {
    Serial.begin(115200);

    mpu.remapAxis(0, 1);
    mpu.remapAxis(1, 0);

    pid.setAxisInvert({false, false, true});

    mpu.begin();

    while (!ServoInput.available()) {  // wait for all signals to be ready
		ESP_LOGI("tag","Waiting for servo signals...");
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

    controller.begin();
}

void loop() {}
