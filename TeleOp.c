#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Motor,  mtr_S1_C1_1,     motorD,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     motorE,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     motorF,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     motorG,        tmotorTetrix, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"

//----------------------------- Initialization ------------------------------

int motorSlow = 1;
bool toogleArm = false;
bool toogleSpool = false;
int motorSpeedD = 0;
int motorSpeedE = 0;
int motorSpeedF = 0;
int motorSpeedG = 0;

void initializeRobot() { //Initialize, setting all motors to a speed of 0.
	motor[motorD] = 0;
	motor[motorE] = 0;
}

//--------------------  Joystick 1 (Driver) Controls --------------------------

int getJoy1y1() { //Get the left side movement.
	return joystick.joy1_y1;
}
int getJoy1y2() {  //Get the right side movement.
	return joystick.joy1_y2;
}

int getMotorSlow() { //Returns which speed to go at
  if (joy1Btn(1) == 1) //X position
	  return 1; //fast
	else if (joy1Btn(2) == 1) //A position
    return 2; //medium
	else if (joy1Btn(3) == 1) //B position
		return 4; //slow
	else {
		return 0;
	}
}

void joy1Controls() {
	getJoystickSettings(joystick);
	motorSpeedD = getJoy1y1();
	motorSpeedE = getJoy1y2();
	if(getMotorSlow() != 0)	{
		motorSlow = getMotorSlow();
	}
  motor[motorD] = motorSpeedD / motorSlow;
  motor[motorE] = motorSpeedE / motorSlow;
}

// ------------------- Joystick 2 (Gunner) Controls ------------------------

int getArmMovement() {  //Gets Arm movement
	if (joy2Btn(7) == 1) {
		return 50;
	}
	else if(joy2Btn(8) == 1) {
		return -20;
	}
	else return 0;
}

int getSpoolMovement() {  //Gets Spool Movement
	return joystick.joy2_y1;
}

int getClawMovement() { //Gets Claw Movement
	return joystick.joy2_y2;
}

int getToggleSpool() {  //Gets sniper mode for spooling
	toggleArm = (joy2Btn(2) == 1) ? true : false;
}

int getToggleArm() {  //Gets sniper mode for moving the arm up and down
	toggleArm = (joy2Btn(3) == 1) ? true : false;
}

void joy2Controls() {
	motorSpeedF = getArmMovement();
	motorSpeedG = getSpoolMovement();

	getToggleSpool();
	getToggleArm();

	motor[motorF] = (toggleArm) ? motorSpeedF : motorSpeedF - 20;
	motor[motorG] = (toggleSpool) ? motorSpeedG : motorSpeedG - 20;

	//This motor controls the arm, moving it up and down.
}

//--------------------------------- Main --------------------------------

task main() {
    initializeRobot();
    waitForStart();

    while(true) {
	    joy1Controls();
	    joy2Controls();
    }
}
