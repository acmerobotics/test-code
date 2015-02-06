#pragma config(Hubs,  S1, HTServo,  HTMotor,  none,     none)
#pragma config(Sensor, S4,     sonarSensor,    sensorSONAR)
#pragma config(Motor,  mtr_S1_C2_1,     leftMotor,     tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     rightMotor,    tmotorTetrix, PIDControl, encoder)
#pragma config(Servo,  srvo_S1_C1_1,    servo1,               tServoStandard)
#pragma config(Servo,  srvo_S1_C1_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "hitechnic-irseeker-v2.h"

tHTIRS2 irSeeker;

const tSensors GyroSensor = (tSensors) S2;

const int offset = SensorValue(GyroSensor);

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                           Autonomous Mode Code Template
//
// This file contains a template for simplified creation of an autonomous program for an TETRIX robot
// competition.
//
// You need to customize two functions with code unique to your specific robot.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.

void driveForward(int feet);
void setDriveMotors(int target);
void turnRight(float degrees);
void stopDriveMotors();

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                    initializeRobot
//
// Prior to the start of autonomous mode, you may want to perform some initialization on your robot.
// Things that might be performed during initialization include:
//   1. Move motors and servos to a preset position.
//   2. Some sensor types take a short while to reach stable values during which time it is best that
//      robot is not moving. For example, gyro sensor needs a few seconds to obtain the background
//      "bias" value.
//
// In many cases, you may not have to add any code to this function and it will remain "empty".
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

void initializeRobot()
{
  // Place code here to sinitialize servos to starting positions.
  // Sensors are automatically configured and setup by ROBOTC. They may need a brief time to stabilize.
	servo[servo1] = 255;
  //playSoundFile("Roadrunner.rso");
  initSensor(&irSeeker, S3);
  return;
}

void driveForward(int feet)
{
	int milliSec = round(1000 * ((float) feet) / PI) - 800;
	setDriveMotors(80);
	wait1Msec(milliSec);
	setDriveMotors(0);
}

void setDriveMotors(int target)
{
	int current = motor[leftMotor];
	int incr;
	if (target > current)
	{
		incr = 1;
	}
	else
	{
		incr = -1;
	}
	for (;abs(target - current) > 0; current += incr)
	{
		motor[leftMotor] = current;
		motor[rightMotor] = current;
		wait1Msec(5);
	}
}

void turnLeft(float degrees)
{
	int i = 0;
	while (degrees > 0)
	{
		nxtDisplayBigTextLine(1, "%d", degrees);
		degrees -= ((float) (SensorValue(GyroSensor)-offset)) * 0.002;
		float motorSpeed = sin(((float) i) * 0.02)/2.0 + 1.0/2.0;
		motor[leftMotor] = -round(motorSpeed * 5);
		motor[rightMotor] = round(motorSpeed * 5);
		i++;
		wait1Msec(2);
	}
	stopDriveMotors();
}

void stopDriveMotors()
{
	motor[leftMotor] = 0;
	motor[rightMotor] = 0;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                         Main Task
//
// The following is the main code for the autonomous robot operation. Customize as appropriate for
// your specific robot.
//
// The types of things you might do during the autonomous phase (for the 2008-9 FTC competition)
// are:
//
//   1. Have the robot follow a line on the game field until it reaches one of the puck storage
//      areas.
//   2. Load pucks into the robot from the storage bin.
//   3. Stop the robot and wait for autonomous phase to end.
//
// This simple template does nothing except play a periodic tone every few seconds.
//
// At the end of the autonomous period, the FMS will autonmatically abort (stop) execution of the program.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

task main()
{
  initializeRobot();

  //waitForStart(); // Wait for the beginning of autonomous phase.

  ///////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////
  ////                                                   ////
  ////    Add your robot specific autonomous code here.  ////
  ////                                                   ////
  ///////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////

	setDriveMotors(-80);
	while ((((float) SensorValue(sonarSensor)) / 2.54) < 52) {
		nxtDisplayTextLine(2, "%d", ((float) SensorValue(sonarSensor)) / 2.54);
	}
	stopDriveMotors();

	readSensor(&irSeeker);
	int irReading = irSeeker.acDirection;
	nxtDisplayTextLine(0, "%d %d", irReading, SensorValue(sonarSensor));

	/* IR Codes
	3 - parallel to IR sensor
	6 - perpendicular to IR sensor
	5 - 45 degree angle to IR sensor
	*/

	if (irReading == 3)
	{
		// do nothing
	}
	else if (irReading == 6 || irReading == 5)
	{
		turnLeft(50);
	}
	else if (irReading == 2)
	{
		turnLeft(30);
	}
	setDriveMotors(-80);
	wait1Msec(1000);
	stopDriveMotors();

	while (true) { }

}