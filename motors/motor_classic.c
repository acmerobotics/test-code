#pragma config(Hubs,  S1, HTServo,  HTMotor,  none,     none)
#pragma config(Sensor, S4,     ,               sensorTouch)
#pragma config(Motor,  mtr_S1_C2_1,     leftMotor,     tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     rightMotor,    tmotorTetrix, PIDControl, encoder)
#pragma config(Servo,  srvo_S1_C1_1,    servo1,               tServoStandard)
#pragma config(Servo,  srvo_S1_C1_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"

task main()
{
	bFloatDuringInactiveMotorPWM = false;

	int leftRight, forwardBack;
	bool down = false;

	servo[servo1] = 135;
	while (true)
	{
		getJoystickSettings(joystick);
		//servo
		if (!down && SensorValue[S4] == 1) {
			down = true;
		} else if (joy1Btn(6) == 1) {
			down = false;
		}
		if (down)
		{
			servo[servo1] = 17;
		}
		else
		{
			servo[servo1] = 135;
		}
		//motors
		leftRight = joystick.joy1_x2 * 80/128;
		forwardBack = -joystick.joy1_y1 * 80/128;
		if (abs(forwardBack) > 15 || abs(leftRight) > 15)
		{
			motor[leftMotor] = -(forwardBack+leftRight);
			motor[rightMotor] = -(forwardBack-leftRight);
		}
		else
		{
			motor[leftMotor] = 0;
			motor[rightMotor] = 0;
		}
		motor[leftMotor] = -motor[leftMotor];
		motor[rightMotor] = -motor[rightMotor];
	}
}
