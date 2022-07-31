#include <init.h>

#include <SpeedBasedOutputCalculator.h>

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
AxisData<RotationRateOutput*> rateOutputs;
MPU6050* mpu;
PID* pid;
Filter<int, 3>* filter;
FilteredGyro* filteredGyro;
AbstractOutputCalculator* outputCalculators[FLIGHT_MODES];
ServoSignalSwitch* flightModeSwitch;
FlightController* controller;
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

    flightModeSwitch = new ServoSignalSwitch(2, gearInput);

    mpu = new MPU6050();
    mpu->setTimeout(15);
    pid = new PID();
    filter = new EWMA<int, 3>(0.6);
    filteredGyro = new FilteredGyro(mpu, filter);

    gainCalculator = new PIDGainCalculator(pid);

    outputCalculators[0] = new SpeedBasedOutputCalculator(new OutputCalculator(servoInputs->getResolution(),
                                                                               aileOutput->getResolution(),
                                                                               maxRates,
                                                                               filteredGyro,
                                                                               pid),
                                                          throttleInputReader,
                                                          gainCalculator);
    outputCalculators[1] = new IdleOutputCalculator(servoInputs->getResolution(), aileOutput->getResolution());

    controller = new MultiModeFlightController<FLIGHT_MODES>(outputCalculators, rateOutputs, servoInputs, flightModeSwitch, throttleInputReader);    
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
    log_v("allocated timers");

	rudderServo.setPeriodHertz(50);
    rudderServo.attach(RUDDER_OUTPUT_PIN, SERVO_MIN, SERVO_MAX);
    log_v("attached rudderServo to pin %d", RUDDER_OUTPUT_PIN);

    aileServo.setPeriodHertz(50);
    aileServo.attach(AILE_OUTPUT_PIN, SERVO_MIN, SERVO_MAX);
    log_v("attached aileServo to pin %d", AILE_OUTPUT_PIN);

    elevatorServo.setPeriodHertz(50);
    elevatorServo.attach(ELEVATOR_OUTPUT_PIN, SERVO_MIN, SERVO_MAX);
    log_v("attached elevatorServo to pin %d", ELEVATOR_OUTPUT_PIN);

    throttleServo.setPeriodHertz(50);
    throttleServo.attach(THROTTLE_OUTPUT_PIN);
    log_v("attached throttleServo to pin %d", THROTTLE_OUTPUT_PIN);
}

void startGyro() {
    log_v("Starting the gyro");
    try {
        mpu->begin();
    } catch (const char* e) {
        log_e("%s", e);
    }
}