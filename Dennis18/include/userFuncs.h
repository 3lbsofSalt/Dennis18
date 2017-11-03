#include "main.h"

#ifndef userFuncs
#define userFuncs


/* function stopAll
 * Makes every motor stop
 */
inline void stopAll(){
  motorSet(leftMobileGoalIntake, 0);
  motorSet(liftTopLeft, 0);
  motorSet(liftBottomLeft, 0);
  motorSet(intakeArm, 0);
  motorSet(leftDrive, 0);
  motorSet(rightDrive, 0);
  motorSet(intakeGrabber, 0);
  motorSet(liftBottomRight, 0);
  motorSet(liftTopRight, 0);
  motorSet(rightMobileGoalIntake, 0);
}

/* function move
 * @param distance is the number of encoder ticks the wheel will move
 * @param dir is the direction it is going. 0=forward 1=backward
 * @param speed is the speed with which the motors should run. From 0-127
 */
inline void move(int distance, int dir, int speed) {
  //Reset Encoders for moving
  encoderReset(lEnc);
  encoderReset(rEnc);

  //Moving Forward
  if(dir == 0) {
    motorSet(leftDrive, -speed);
    motorSet(rightDrive, speed);
    while(abs(encoderGet(lEnc)) < distance && abs(encoderGet(rEnc)) < distance){
      //Runs until the encoders have more ticks than distance has numbers
    }
  } else if(dir == 1){ //Moving Backward
    motorSet(leftDrive, speed);
    motorSet(rightDrive, -speed);
    while(abs(encoderGet(lEnc)) < distance && abs(encoderGet(rEnc)) < distance) {
      //Runs until the encoders are greater than distance
    }
  }
  //Stop Driving
  stopAll();
}

/* function turn
 * @param ditance is the amount of encoder ticks the robot will turn
 * @param dir is the direction the robot will turn; 0=left 1=right
 * @param speed is the speed with which the motors will turn
 */
inline void turn(int distance, int dir, int speed) {
  //Reset Encoders
  encoderReset(lEnc);
  encoderReset(rEnc);

  //Turning Left
  if(dir == 0){
    motorSet(leftDrive, speed);
    motorSet(rightDrive, speed);
    while(abs(encoderGet(lEnc)) < distance && abs(encoderGet(rEnc)) < distance) {
      //Run until encoder is greater than distance
    }
  } else if(dir == 1) { //Turning Right
    motorSet(leftDrive, -speed);
    motorSet(rightDrive, -speed);
    while(abs(encoderGet(lEnc)) < distance && abs(encoderGet(rEnc)) < distance) {
      //Run until encoder is greater than distance
    }
  }
  //Stop driving
  stopAll();
}
/* function mobileGoal
 * @param pot is what you want the mobile goal potentiometer to read
 * When Mobile Goal is in robot     pot = 1100
 * When Mobile Goal is on ground    pot = 3800
 * When Mobile Goal is straight up  pot = 2000-1900
 * @param speed is how fast you want the motors to go; acceptable 1-127
 */
inline void mobileGoal(int pot, int speed) {
  if(pot >= analogRead(mobileLiftPot)){ //The intake needs to move away from the robot.
    motorSet(leftMobileGoalIntake, -speed);
    motorSet(rightMobileGoalIntake, speed);
    while(pot >= analogRead(mobileLiftPot)){
      //Cycles until the lift is in the correct spot
    }
  } else {  // The intake needs to move towards the robot
    motorSet(leftMobileGoalIntake, speed);
    motorSet(rightMobileGoalIntake, -speed);
    while(pot < analogRead(mobileLiftPot)){
      //Cycles until the lift is in the correct spot
    }
  }
  //Stop the mobile goal thing
  stopAll();
}

/* function lift
 * @param lift is where you want the lift to move to
 * @param speed is the speed with which the motors should lift it
 */
inline void lift(int lift, int speed) {
  if(lift <= encoderGet(liftEnc)) { //Lift needs to move down
     motorSet(liftBottomLeft, -speed);
     motorSet(liftBottomRight, speed);
     motorSet(liftTopLeft, speed);
     motorSet(liftTopRight, -speed);
     while(lift <= encoderGet(liftEnc)) {
       //Cycles while lift is moving down
     }
  } else { //Lift needs to move up
    motorSet(liftBottomLeft, speed);
    motorSet(liftBottomRight, -speed);
    motorSet(liftTopLeft, -speed);
    motorSet(liftTopRight, speed);
    while(lift >= encoderGet(liftEnc)) {
      //Cycles while lift is moving up
    }
  }
  //Stop the lift
  stopAll();
}

/* function arm
 * Moves the intake arm into position
 * @param pot is the desired potentiometer reading for the arm
 * When arm is all the way extended out   pot = 3850
 * When arm is straight up                pot = 1800
 * @param speed is the speed with which the motors will move; 1-127 acceptable
 */
inline void arm(int pot, int speed) {
  //Arm needs to move out
  if(pot > analogRead(armPot)) {
    motorSet(intakeArm, -speed);
    while(pot > analogRead(armPot)) {
      //Run until desired pot number is hit
    }
  } else { //Arm needs ot move towards robot`
    motorSet(intakeArm, speed);
    while(pot <= analogRead(armPot)){
      //Run until desired pot number is hit
    }
  }
  stopAll();
}

/* function grabber
 * @param dir direction to intake the cone; 1 = intake, 0 = outtake
 * @param grabTime is how long in milliseconds you want the grabber to run
 */
inline void grabber(int dir, int grabTime) {
  if(dir == 1) {
    //Intake
    motorSet(intakeGrabber, 127);
  } else {
    //Outtake
    motorSet(intakeGrabber, -127);
  }
  delay(grabTime);
  stopAll();
}
#endif
