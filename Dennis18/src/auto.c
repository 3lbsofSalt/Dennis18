/** @file auto.c
 * @brief File for autonomous code
 *
 * This file should contain the user autonomous() function and any functions related to it.
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
 * Runs the user autonomous code. This function will be started in its own task with the default
 * priority and stack size whenever the robot is enabled via the Field Management System or the
 * VEX Competition Switch in the autonomous mode. If the robot is disabled or communications is
 * lost,  the autonomous task will be stopped by the kernel. Re-enabling the robot will restart
 * the task, not re-start it from where it left off.
 *
 * Code running in the autonomous task cannot access information from the VEX Joystick. However,
 * the autonomous function can be invoked from another task if a VEX Competition Switch is not
 * available, and it can access joystick information if called in this way.
 *
 * The autonomous task may exit, unlike operatorControl() which should never exit. If it does
 * so, the robot will await a switch to another mode or disable/enable cycle.
 */

void autonomous() {
  //If the limit switch is not pressed, do this autonomous
  if(digitalRead(autoLimit) == HIGH){
    //This autonomous scores the preload on the goal post
    lift(80, 127);
    move(400, 1, 100);
    delay(500);
    grabber(0, 500);
    arm(3850, 127);
    move(400, 0, 100);
  } else {
    //RED SIDE AUTONOMOUS
    if(digitalRead(sideLimit) == HIGH) {
      //This autonomous grabs the mobile goal and scores it
      mobileGoal(3500, 127);
      move(1700, 1, 100);
      mobileGoal(1300, 127);
      delay(500);
      grabber(0, 700);
      //Mobile goal is in robot and cone is scored on the mobile goal
      //move(1300, 0, 100);
      //turn(540, 0, 60);
    } else { //BLUE SIDE AUTONOMOUS
      //This autonomous grabs the moble goal and scores it
      lift(10, 127);
      move(200, 1, 100);
      turn(300, 0, 50);
      //Robot facing toward blue mobile goal on square to the right
      mobileGoal(3300, 127);
      move(1700, 1, 100);

    }
  }
}
