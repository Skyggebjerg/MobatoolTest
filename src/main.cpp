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

const int stepsPerRev = 200;    // Steps per revolution - may need to be adjusted

MoToStepper stepper1( stepsPerRev, STEPDIR );  // create a stepper instance

void setup() {
  pinMode(en_pin, OUTPUT);
  digitalWrite(en_pin, LOW); // enable driver
  stepper1.attach( stepPin, dirPin );
  stepper1.setSpeed( 300 );              // 30 rev/min (if stepsPerRev is set correctly)
  stepper1.setRampLen( stepsPerRev / 2); // Ramp length is 1/2 revolution
  stepper1.rotate(1);                    // start turning, 1=vorward, -1=backwards                    
}

void loop() {
}