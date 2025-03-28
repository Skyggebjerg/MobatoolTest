#include <Arduino.h>
#include "M5Atom.h"
//#include "Unit_Encoder.h"
//#include <M5Atom.h>
//#include "StepperDriver.h"
#include "FastLED.h"

/* ====== minimumStepper =======================================
 *  Bare minimum to get a stepper with step/dir driver turning
 */
#include <MobaTools.h>
// Stepper connections - Please adapt to your own needs.
int en_pin = 22; // enable pin
const byte stepPin = 19;
const byte dirPin = 23;

const int stepsPerRev = 200*32;    // Steps per revolution - 1/32 microstepping

MoToStepper stepper1( stepsPerRev, STEPDIR );  // create a stepper instance

void setup() {
  pinMode(en_pin, OUTPUT);
  pinMode(26, INPUT_PULLUP); // X-axis optical fork
  pinMode(32, OUTPUT); // signal to tell the Y MCU to wait for the X MCU to finish the homing process
  digitalWrite(32, HIGH); // set signal to HIGH to tell the Y MCU to wait for the X MCU to finish the homing process
  digitalWrite(en_pin, LOW); // enable driver
  stepper1.attach( stepPin, dirPin );
  stepper1.setSpeed( 1200 );              // 30 rev/min (if stepsPerRev is set correctly)
  stepper1.setRampLen( stepsPerRev / 4); // Ramp length is 1/2 revolution

}

void loop() {

// --------------------------------******* X AXIS ********--------------------------------
  if(digitalRead(26) == HIGH){ // if the XY-stage is already in or beyond the home position (the optical fork is blocked = HIGH)
    stepper1.rotate(-1); //  start turning backwards, 1=vorward, -1=backwards
    while (digitalRead(26) == HIGH){ } // keep moving until the optical fork is not blocked anymore
      stepper1.stop(); // stop turning
      stepper1.doSteps(-320); // move a bit more away
      delay(1000); // wait for 1 second
  }

  if(digitalRead(26) == LOW){
    stepper1.rotate(1); //  start turning forwards toward home position
    while (digitalRead(26) == LOW){ } // keep moving until the optical fork is blocked
    stepper1.stop(); // stop turning
    delay(100);

    stepper1.doSteps(32); // move a bit more to the home position to make sure the optical fork is blocked (tolerance)
    delay(1000);

    stepper1.rotate(-1); //  start turning backwards, 1=vorward, -1=backwards
    while (digitalRead(26) == HIGH){ } // keep moving until the optical fork is not blocked anymore
    stepper1.stop(); // stop turning
    delay(100); // wait for 1 second

    stepper1.doSteps(32); // move a bit more to the home position to make sure the optical fork is blocked (tolerance)
    delay(1000);

    digitalWrite(32, LOW); // set signal to LOW to tell the Y MCU to start the homing process
    while(1){} // wait for the Y MCU to finish the homing process

  } 

}