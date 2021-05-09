#include <Arduino.h>

#include <map>
#include <Wire.h>

#include <ServoInput.h>
#include <MPU6050.h>
#include <PID.h>

#include <ESP32Servo.h>

#include <OTAManagement.h>


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

#define RUDDER_DIRECTION 0
#define AILE_DIRECTION 2
#define ELEV_DIRECTION 1


int16_t MAX_YAW_RATE = 360;
int16_t MAX_PITCH_RATE  =360;
int16_t MAX_ROLL_RATE = 720;


ServoInputPin<RUDDER_INPUT_PIN> rudderInput(SERVO_MIN, SERVO_MAX);
ServoInputPin<ELEVATOR_INPUT_PIN> elevatorInput(SERVO_MIN, SERVO_MAX);
ServoInputPin<AILE_INPUT_PIN> aileInput(SERVO_MIN, SERVO_MAX);

Servo rudderServo;
Servo aileServo;
Servo elevatorServo;

MPU6050 mpu = MPU6050();
PID pid;

void setup() {
    Serial.begin(115200);

    startOTA();

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

    rudderServo.write(0);
    aileServo.write(0);
    elevatorServo.write(0);

    delay(2000);

    rudderServo.write(180);
    aileServo.write(180);
    elevatorServo.write(180);
}

void loop() {
    RotationData setpoint;
    float rudderAngle = rudderInput.getAngle();
    float elevAngle = elevatorInput.getAngle();
    float aileAngle = aileInput.getAngle();

    log_d("Rudder:\t%9.2fº", rudderAngle);
    log_d("Elevator:\t%9.2fº", elevAngle);
    log_d("Aileron:\t%9.2fº", aileAngle);

    setpoint[RUDDER_DIRECTION] = map(rudderAngle, 0, 180, -MAX_YAW_RATE, MAX_YAW_RATE);
    setpoint[ELEV_DIRECTION] = map(elevAngle, 0, 180, -MAX_PITCH_RATE, MAX_PITCH_RATE);
    setpoint[AILE_DIRECTION] = map(aileAngle, 0, 180, -MAX_ROLL_RATE, MAX_ROLL_RATE);

    RotationData gyroReadings = mpu.getRotation();
    RotationData output = pid.loop(setpoint, gyroReadings);
    output[RUDDER_DIRECTION] = map(output[RUDDER_DIRECTION], -MAX_YAW_RATE, MAX_YAW_RATE, 0, 180);
    output[ELEV_DIRECTION] = map(output[ELEV_DIRECTION], -MAX_PITCH_RATE, MAX_PITCH_RATE, 0, 180);
    output[AILE_DIRECTION] = map(output[AILE_DIRECTION], -MAX_ROLL_RATE, MAX_ROLL_RATE, 0, 180);

    log_d("Gyro\t\tx:%7.2f, y:%7.2f, z:%7.2f", gyroReadings.x, gyroReadings.y, gyroReadings.z);
    log_d("Setpoint\tx:%7.2f, y:%7.2f, z:%7.2f", setpoint.x, setpoint.y, setpoint.z);
    log_d("Output\t\tx:%7.2f, y:%7.2f, z:%7.2f\n", output.x, output.y, output.z);

    rudderServo.write(output[RUDDER_DIRECTION]);
    aileServo.write(output[AILE_DIRECTION]);
    elevatorServo.write(output[ELEV_DIRECTION]);

    delay(20);
}
