#include <init.h>

int16_t MAX_YAW_RATE = 360;
int16_t MAX_PITCH_RATE = 360;
int16_t MAX_ROLL_RATE = 720;

RotationData maxRates { MAX_YAW_RATE, MAX_PITCH_RATE, MAX_ROLL_RATE };

ServoInputSignal* throttleInput;
SpeedReader* throttleInputReader;
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
Filter<int, 3>* filter;
FilteredGyro* filteredGyro;
OutputCalculator* outputCalculator;
PIDSwitch* pidSwitch;
Controller* controller;
GainCalculator* gainCalculator;

void assign() {
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

    throttleOutput = new ServoThrottleOutput(&throttleServo);
    throttleInput = new ServoInputPin<THROTTLE_INPUT_PIN>(SERVO_MIN, SERVO_MAX);
    throttleInputReader = new ServoThrottleReader(throttleInput, 1024, throttleOutput);

    pidSwitch = new PIDSwitch(gearInput);

    mpu = new MPU6050();
    pid = new PID();
    filter = new EWMA<int, 3>(0.6);
    filteredGyro = new FilteredGyro(mpu, filter);

    gainCalculator = new PIDGainCalculator(pid);

    outputCalculator = new OutputCalculator(maxRates, filteredGyro, pid, gainCalculator);

    controller = new Controller(outputCalculator, rateOutputs, servoInputs, pidSwitch, throttleOutput, throttleInputReader);    
}

void configure() {
    mpu->remapAxis(AxisData<int>::X, AxisData<int>::Y);
    mpu->remapAxis(AxisData<int>::Y, AxisData<int>::X);

    pid->setAxisInvert( { false, false, true } );
    servoInputs->setInvert( { false, false, false } );

    aileOutput->setMiddle(1420);
    elevatorOutput->setMiddle(1600);
}

void startReceiver() {
    log_v("Starting the receiver");

    while (!ServoInput.available()) {  // wait for all signals to be ready
		log_i("Waiting for servo signals...");
		delay(500);
	}
}

void startServos() {
    log_v("Starting the servos");

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
}

void startGyro() {
    log_v("Starting the gyro");
    mpu->begin();
}