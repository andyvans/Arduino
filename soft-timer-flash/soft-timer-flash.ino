#include <SoftTimer.h>


// -- taskOn will be launched on every 2 seconds.
Task taskOn(300, turnOn);
// -- taskOff will be launched on every 1111 milliseconds.
Task taskOff(500, turnOff);

void setup() {
  // -- Mark pin 13 as an output pin.
  pinMode(13, OUTPUT);

  // -- Register the tasks to the timer manager. Both tasks will start immediately.
  SoftTimer.add(&taskOn);
  SoftTimer.add(&taskOff);
}

/**
 * Turn ON Arduino's LED on pin 13.
 */
void turnOn(Task* me) {
  digitalWrite(13, HIGH);
}

/**
 * Turn OFF Arduino's LED on pin 13.
 */
void turnOff(Task* me) {
  digitalWrite(13, LOW);
}
