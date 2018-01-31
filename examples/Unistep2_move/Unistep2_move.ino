/*
 * Unistep2 example: move
 *
 * Simple example of stepper enumeration and movement via move(steps).
 * If steps > 0 clockwise, else counter clockwise. Non-blocking.
 *
 * 30Jan18
 * R Sanchez
 *
 * This code is released to the public domain
 *
 */

// include the library
#include <Unistep2.h>

// Define some steppers and the pins they will use
Unistep2 stepperX(2, 3, 4, 5, 4096, 1000); // pins for IN1, IN2, IN3, IN4, steps per rev, step delay(in micros)
Unistep2 stepperY(6, 7, 8, 9, 4096, 1000);

void setup()
{
  // Your setup code here
  // The library initializes the pins for you
}

void loop()
{
  // We need to call run() frequently during loop()
  stepperX.run();
  stepperY.run();

  // Create random movements for the steppers
  if ( stepperX.stepsToGo() == 0 ){ // If stepsToGo returns 0 the stepper is not moving
    stepperX.move(random(-4000,4000));
  }
  if ( stepperY.stepsToGo() == 0 ){
    stepperY.move(random(-4000,4000));
  }

  // Other code

}
