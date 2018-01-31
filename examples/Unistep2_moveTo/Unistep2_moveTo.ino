/*
 * Unistep2 example: moveTo
 *
 * Example of stepper enumeration and movement via moveTo(position).
 *
 * Gets user input via Serial monitor.
 *
 * Moves the stepper to the absolute position indicated. Position is a number
 * between 0 and the number of steps per rev (generally, 4096).
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
// pins for IN1, IN2, IN3, IN4, steps per rev, step delay(in micros)
Unistep2 stepper(2, 3, 4, 5, 4096, 1000);

void setup()
{
  // Your setup code here
  // The library initializes the pins for you

  Serial.begin(9600);
  Serial.println(F(" *** Unistep2 library example ***"));
  Serial.println(F(" Enter absolute position between 0 and 4096"));

}

void loop()
{
  // We need to call run() frequently, so we place it in the loop()
  stepper.run();

  // Get user input via Serial monitor
  while ( Serial.available() > 0 && stepper.stepsToGo() == 0 ) {

    int stepPos = Serial.parseInt();

    if (Serial.read() == '\n') {
      Serial.print("Movement command: ");
      // currentPosition() gives us stepper position
      Serial.print(stepper.currentPosition());
      Serial.print(" --> ");
      Serial.println(stepPos);

      // moveTo() chooses the shortest path between the two positions.
      stepper.moveTo(stepPos);
    }
  }
  // Other code

}
