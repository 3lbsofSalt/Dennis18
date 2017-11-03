/** @file opcontrol.c
 * @brief File for operator control code
 *
 * This file should contain the user operatorControl() function and any functions related to it.
 *
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"
#include "userFuncs.h"
/*
 * Runs the user operator control code. This function will be started in its own task with the
 * default priority and stack size whenever the robot is enabled via the Field Management System
 * or the VEX Competition Switch in the operator control mode. If the robot is disabled or
 * communications is lost, the operator control task will be stopped by the kernel. Re-enabling
 * the robot will restart the task, not resume it from where it left off.
 *
 * If no VEX Competition Switch or Field Management system is plugged in, the VEX Cortex will
 * run the operator control task. Be warned that this will also occur if the VEX Cortex is
 * tethered directly to a computer via the USB A to A cable without any VEX Joystick attached.
 *
 * Code running in this task can take almost any action, as the VEX Joystick is available and
 * the scheduler is operational. However, proper use of delay() or taskDelayUntil() is highly
 * recommended to give other tasks (including system tasks such as updating LCDs) time to run.
 *
 * This task should never exit; it should end with some kind of infinite loop, even if empty.
 */
int xAxisDrive;
int yAxisDrive;
int yAxisLift;
int deadzone = 20;



void operatorControl() {
	while (1) {
		delay(20);
		xAxisDrive = joystickGetAnalog(1, 4);
		yAxisDrive = joystickGetAnalog(1, 3);
		/* DRIVE */
		if(abs(xAxisDrive) > deadzone || abs(yAxisDrive) > deadzone) {
			motorSet(leftDrive, xAxisDrive - yAxisDrive);
			motorSet(rightDrive, xAxisDrive + yAxisDrive);
		} else {
			motorSet(leftDrive, 0);
			motorSet(rightDrive, 0);
		}

		/* MOBILE GOAL INTAKE */
		if(joystickGetDigital(1, 8, JOY_DOWN)){
			//Move the intake into the robot
			motorSet(leftMobileGoalIntake, 127);
			motorSet(rightMobileGoalIntake, -127);
		} else if(joystickGetDigital(1, 8, JOY_RIGHT)) {
			//Move the intake away from the robot
			motorSet(leftMobileGoalIntake, -127);
			motorSet(rightMobileGoalIntake, 127);
		} else {
			//Stop the intake if no button is pressed
			motorSet(leftMobileGoalIntake, 0);
			motorSet(rightMobileGoalIntake, 0);
		}

		//Sets the mobile goal down softly
		if(joystickGetDigital(1, 8, JOY_UP)) {
		  mobileGoal(2000, 127);
		  delay(300);
		  mobileGoal(3500, 40);
		}

		/* LIFT */
		yAxisLift = joystickGetAnalog(1, 2);
		if(abs(yAxisLift) > deadzone) {
			motorSet(liftBottomLeft, yAxisLift);
			motorSet(liftBottomRight, -yAxisLift);
			motorSet(liftTopLeft, -yAxisLift);
			motorSet(liftTopRight, yAxisLift);
		} else {
			motorSet(liftBottomLeft, 0);
			motorSet(liftBottomRight, 0);
			motorSet(liftTopRight, 0);
			motorSet(liftTopLeft, 0);
		}

		/* INTAKE ARM */
		if(joystickGetDigital(1, 5, JOY_DOWN)){ //Move toward robot
			motorSet(intakeArm, 127);
		} else if(joystickGetDigital(1, 5, JOY_UP)){ //Move away from robot
			motorSet(intakeArm, -127);
		} else {
			motorSet(intakeArm, 0);
		}

		/* INTAKE GRABBER */
		if(joystickGetDigital(1, 6, JOY_UP)) {
			//Intake
			motorSet(intakeGrabber, 127);
		} else if(joystickGetDigital(1, 6, JOY_DOWN)){
			//Outtake
			motorSet(intakeGrabber, -127);
		} else {
			motorSet(intakeGrabber, 0);
		}

		/* LCD SCREEN */
		lcdPrint(uart1, 1, "MobilePot: %d", analogRead(mobileLiftPot));
		lcdPrint(uart1, 2, "ArmPot: %d", analogRead(armPot));
		/* BUTTONS */
		if(joystickGetDigital(1, 7, JOY_DOWN)){
			if(joystickGetDigital(1, 7, JOY_RIGHT)) {
				autonomous();
			}
		}
	}
}
