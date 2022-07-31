#ifndef _VARIABLES_H
#define _VARIABLES_H

#include <FlightController.h>
#include <AxisData.h>
#include <SteeringInputReader.h>
#include <Gyro.h>

extern Gyro* gyro;
extern SteeringInputReader* steeringInput;
extern AxisData<RotationRateOutput*> rotationOutputs;
extern FlightController* flightController;

#endif