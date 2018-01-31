# Unistep2

A non-blocking Arduino library for controlling 28BYJ-48 stepper motors
[Project web](https://en.reven.org/2018/01/29/unistep2/)

## Rationale
28BYJ-48's are little inexpensive 5v geared stepper motors that are particularly pesky in terms of what's needed to drive them. They are halfstep steppers and require an 8 step control signal to drive them efficiently. They usually come with (equally inexpensive) ULN2003 driver boards that make connecting them to the Arduino much easier.

I had no success driving them with the standard stepper libraries ([Stepper](https://www.arduino.cc/en/Reference/Stepper) or [AccelStepper](http://www.airspayce.com/mikem/arduino/AccelStepper/)). There was always resistance and stutter, resulting in increased heat and noise. I finally came across two libraries that worked: Tyler Henry's [CheapStepper](https://github.com/tyhenry/CheapStepper), which I couldn't get to drive two steppers simultaneously without issues; and Matthew Jones's [Unistep](https://www.crazy-logic.co.uk/projects/computing/arduino-unistep), which drove two or more steppers perfectly but in a blocking fashion.

So I decided to create a non-blocking version based on Unistep and added some extra functionality, but I wanted to recognize the contributions made by others.

## Features
- Non-blocking
- Can manage 2 or more steppers
- Extra functions to control state of steppers
- More energy efficient
- Precise timing avoids noise, heat, stutter, stalling, etc.

## Installation
Download the zip in *Releases* and use the library manager to add it to your libraries. Alternatively you can install manually into your Arduino library folder.

## Use
Just call `#include <Unistep2.h>` at the begining of your sketch and construct the stepper objects with the following call in your setup() function:
```c++
Unistep2 stepper(p1, p2, p3, p4, stepsPerRev, stepDelay);
```
where *p1* to *p4* are the pins you've connected your ULN2003 to, *stepsPerRev* are the steps that your stepper takes to do one revolution (4096-ish in the 28BYJ-48's) and *stepDelay* is the delay between each step in microseconds (900 is the fastest that seems to work without issues).

Then you must call `stepper.run()` in your loop. Delaying functions will interfere with the stepper movement.

## Function descriptions
- `move(int steps)`: Moves the stepper the indicated amount of steps. If *steps* is negative movement will be counter-clockwise.

- `moveTo(unsigned int pos)`: Moves the stepper to an absolute position between 0 and *stepsPerRev*.

- `currentPosition()`: Returns the current absolute position of the stepper.

- `stepsToGo()`: Returns the amount of steps remaining for the stepper to complete the assigned movement. Negative will mean counter-clockwise.

- `stop()`: Stops the current movement and powers down the pins to save energy and avoid heat generation. Is called automatically after each movement, but is available to be called by the user.

## To-do
- ~~Create examples~~
- ~~Add metadata and library info~~
- ~~Repackage as plugin zip~~

## Tip jar
If you find this useful in any way, feel free to leave a tip in my bitcoin address if you feel so inclined:
`bc1qn7zrnkk47fzwkf5uqyaqu9dzl7mtyrh5h2ef33`

## License
This library is released into the public domain.
