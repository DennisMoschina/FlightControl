#include <Arduino.h>

#include <map>
#include <Wire.h>

#include <ServoInput.h>
#include <MPU6050.h>
#include <PID.h>

#include <ESP32Servo.h>

#define RUDDER_INPUT_PIN 4
#define RUDDER_MIN 1000 //1068
#define RUDDER_MAX 2000 //1871
#define RUDDER_OUTPUT_PIN 14
#define RUDDER_DIRECTION 0

int16_t MAX_YAW_RATE = 360;
int16_t MAX_PITCH_RATE  =360;
int16_t MAX_ROLL_RATE = 720;


ServoInputPin<RUDDER_INPUT_PIN> rudderInput(RUDDER_MIN, RUDDER_MAX);
MPU6050 mpu = MPU6050();
PID pid;

Servo rudderServo;

void setup() {
    Serial.begin(115200);

    mpu.begin();

    while (!ServoInput.available()) {  // wait for all signals to be ready
		log_i("Waiting for servo signals...");
		delay(500);
	}

    ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);
	rudderServo.setPeriodHertz(50);
	rudderServo.attach(RUDDER_OUTPUT_PIN, RUDDER_MIN, RUDDER_MAX);
}

void loop() {
    RotationData setpoint;
    float angle = rudderInput.getAngle();
    log_d("Angle: %.2f", angle);
    setpoint[RUDDER_DIRECTION] = map(angle, 0, 180, -MAX_YAW_RATE, MAX_YAW_RATE);

    RotationData gyroReadings = mpu.getRotation();
    RotationData output = pid.loop(setpoint, gyroReadings);
    output[RUDDER_DIRECTION] = map(output[RUDDER_DIRECTION], -MAX_YAW_RATE, MAX_YAW_RATE, 0, 180);

    log_d("Gyro\t\tx:%7.2f, y:%7.2f, z:%7.2f", gyroReadings.x, gyroReadings.y, gyroReadings.z);
    log_d("Setpoint\tx:%7.2f, y:%7.2f, z:%7.2f", setpoint.x, setpoint.y, setpoint.z);
    log_d("Output\t\tx:%7.2f, y:%7.2f, z:%7.2f\n", output.x, output.y, output.z);

    rudderServo.write(output[RUDDER_DIRECTION]);

    delay(20);
}
