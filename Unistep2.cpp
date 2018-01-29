/*
  UniStep2.h - Non-blocking Library for unipolar steppers.
  Created by Robert Sanchez, January 28, 2018.
  Based on Unistep by Matthew Jones.
  Released into the public domain.

  This library tracks the phase and step of unipolar 5 wire stepper motors
  in a non blocking way.
*/

#include "Arduino.h"
#include "Unistep2.h"

//lets define the setup function
//Unistep2(p1,p2,p3,p4,steps per rev, step delay)
Unistep2::Unistep2(int _p1,int _p2, int _p3, int _p4, int _steps, int _stepdelay)
{
  p1=_p1;
  p2=_p2;
  p3=_p3;
  p4=_p4;
  pinMode(p1, OUTPUT);
  pinMode(p2, OUTPUT);
  pinMode(p3, OUTPUT);
  pinMode(p4, OUTPUT);
  phase = 0;
  steptime = _stepdelay;
  stepsperrev = _steps;
  currentstep = 0;
}

void Unistep2::moves(int steps, int dir)
{
  if (dir==1)
  {//forward
    for(int x=0;x<steps;x++)
      {
      step1();
      delayMicroseconds(steptime);
      }
  }
  else
  {//reverse or default.
    for(int x=0;x<steps;x++)
      {
      step0();
      delayMicroseconds(steptime);
      }
  }
}

void Unistep2::step1()
{
  switch(phase)//gofromthisphase
  {
   case 0:
     goto1();
   break;
   case 1:
     goto2();
   break;
   case 2:
     goto3();
   break;
   case 3:
     goto4();
   break;
   case 4:
     goto5();
   break;
   case 5:
     goto6();
   break;
     case 6:
     goto7();
   break;
   case 7:
     goto0();
   break;
   default:
     goto0();
   break;
  }

  if (currentstep==stepsperrev-1)
    {currentstep=0;}
  else
    {currentstep = currentstep+1;}
}

void Unistep2::step0()
{
  switch(phase)//gofromthisphase
  {
   case 0:
     goto7();
   break;
   case 1:
     goto0();
   break;
   case 2:
     goto1();
   break;
   case 3:
     goto2();
   break;
   case 4:
     goto3();
   break;
   case 5:
     goto4();
   break;
     case 6:
     goto5();
   break;
   case 7:
     goto6();
   break;
   default:
     goto0();
   break;
  }

  if (currentstep==0)
    {currentstep=stepsperrev-1;}
  else
    {currentstep = currentstep-1;}

}


//individual steps
void Unistep2::goto1()
{
  digitalWrite(p1, LOW);
  digitalWrite(p2, LOW);
  digitalWrite(p3, LOW);
  digitalWrite(p4, HIGH);
  phase=1;
}
void Unistep2::goto2()
{
     digitalWrite(p1, LOW);
     digitalWrite(p2, LOW);
     digitalWrite(p3, HIGH);
     digitalWrite(p4, HIGH);
     phase=2;
}
void Unistep2::goto3()
{
     digitalWrite(p1, LOW);
     digitalWrite(p2, LOW);
     digitalWrite(p3, HIGH);
     digitalWrite(p4, LOW);
     phase=3;
}
void Unistep2::goto4()
{
     digitalWrite(p1, LOW);
     digitalWrite(p2, HIGH);
     digitalWrite(p3, HIGH);
     digitalWrite(p4, LOW);
     phase=4;
}
void Unistep2::goto5()
{
     digitalWrite(p1, LOW);
     digitalWrite(p2, HIGH);
     digitalWrite(p3, LOW);
     digitalWrite(p4, LOW);
     phase=5;
}
void Unistep2::goto6()
{
     digitalWrite(p1, HIGH);
     digitalWrite(p2, HIGH);
     digitalWrite(p3, LOW);
     digitalWrite(p4, LOW);
     phase=6;
}
void Unistep2::goto7()
{
     digitalWrite(p1, HIGH);
     digitalWrite(p2, LOW);
     digitalWrite(p3, LOW);
     digitalWrite(p4, LOW);
     phase=7;
}
void Unistep2::goto0()
{
     digitalWrite(p1, HIGH);
     digitalWrite(p2, LOW);
     digitalWrite(p3, LOW);
     digitalWrite(p4, HIGH);
     phase=0;
}

int Unistep2::print()
{
    return currentstep;
}
