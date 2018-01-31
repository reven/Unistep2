/*
  UniStep2.h - Non-blocking Library for unipolar steppers.
  Created by Robert Sanchez, January 28, 2018.
  Based on Unistep by Matthew Jones.
  Released into the public domain.

  This library tracks the phase and step of unipolar 5 wire stepper motors
  (28BYJ-48) in a non blocking way.
*/

#ifndef Unistep2_h
#define Unistep2_h

#include "Arduino.h"

class Unistep2
{
  public:
    // Constructor. We define pins for In1, In2, In3 and In4 on a ULN2003AN driver
    // plus the number of steps per rev (which is usually 4096) and the delay
    // between steps (900 works well).
    Unistep2(int _p1, int _p2, int _p3, int _p4, int _steps, unsigned long _stepdelay);

    // Poll the motor and step it if a step is due, must call this as
    // frequently as possible, but at least once per minimum step interval,
    // preferably in your main loop.
    // return true if the motor is at the target position. (if not does it return false???????)
    boolean run();

    // Move function. We define the number of steps (int) and set stepstogo
    // accordingly. Direction is implicit in the sign (>0 is clockwise, <0 is
    // counterclockwise).
    void move(int steps);

    // Move-to function. We define the absolute position (between 0 and _steps)
    // and set stepstogo to get there. Will choose shortest path, so direction
    // will depend on current position.
    void moveTo(unsigned int pos);

    // Return the current step of the motor.
    int currentPosition();

    // Return the number of steps between the current position to the target
    // position. Positive is clockwise. If 0 the motor is not moving.
    int stepsToGo();

    // Sets a new target position that causes the stepper to stop as quickly as
    // possible and pulls pins low.
    void stop();

  private:
    int phase; //the curret phase setp
    int p1; //output pin
    int p2; //output pin
    int p3; //output pin
    int p4; //output pin
    int stepsperrev; //the number of steps in one ref zero indexed.
    int currentstep; //the current step number, zero indexed.
    int stepstogo;   //the remaining steps to complete the curret movement.
    unsigned long steptime; //the delay time between steps
    unsigned long _lastStepTime; //the last step time in microseconds
    void nextStep();   //Called if there are stepstogo (!= 0)
    void stepCW();
    void stepCCW();
    void goto1();
    void goto2();
    void goto3();
    void goto4();
    void goto5();
    void goto6();
    void goto7();
    void goto0();
    void powerUp(); //powers pins at current step to get ready for move
};

#endif
