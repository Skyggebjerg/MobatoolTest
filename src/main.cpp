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
  pinMode(32, INPUT_PULLUP);
  digitalWrite(en_pin, LOW); // enable driver
  stepper1.attach( stepPin, dirPin );
  stepper1.setSpeed( 600 );              // 30 rev/min (if stepsPerRev is set correctly)
  stepper1.setRampLen( stepsPerRev / 4); // Ramp length is 1/2 revolution
  //stepper1.rotate(1);                    // start turning, 1=vorward, -1=backwards                    
  //delay(10000);
  //stepper1.stop();                       // stop turning
  //stepper1.rotate(0);                    // stop turning
  //delay(2000);
  stepper1.doSteps( stepsPerRev *4);        // do one revolution
  //delay(10000);
  //stepper1.doSteps( -stepsPerRev );

  //delay(20000);
  //digitalWrite(en_pin, HIGH); // disable driver
}

void loop() {
  if(digitalRead(32) == LOW){ 
    stepper1.stop();
    digitalWrite(en_pin, HIGH); // disable driver
  }
}