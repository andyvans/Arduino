#include <Stepper.h>
 
const int stepsPerRevolution = 20; 
 
//Connection pins:
Stepper myStepperX(stepsPerRevolution, 2,3,4,5);
Stepper myStepperY(stepsPerRevolution, 6,7,8,9); 
 
void setup() {
 
 myStepperX.setSpeed(100);
 myStepperY.setSpeed(100);
 
 //max 250 steps for dvd/cd stepper motors 
 myStepperX.step(240);
 myStepperY.step(240);
 //delay(1000);
 myStepperX.step(-240);
 myStepperY.step(-240);
}
 
void loop() {
}
