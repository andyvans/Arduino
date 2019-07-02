#include <CustomStepper.h>

//Full constructor, just the first 4 parameters are necessary, they are the pins connected to the motor,
//the others are optional, and default to the following below
//the 5th paramater is the steps sequence, where the 1st element of the array is the number of steps
//it can have a maximum of 8 steps
//the 6th parameter is the SPR (Steps Per Rotation)
//the 7th parameter is the RPM
//the 8th parameter is the rotation orientation
CustomStepper stepper(2, 3, 4, 5, (byte[]){8, B1000, B1100, B0100, B0110, B0010, B0011, B0001, B1001}, 4075.7728395, 12, CW);

int lastTime = 0;
int lastAngle = 180;

void setup()
{
  setup_stepper();
  setup_edm();
  
  Serial.begin(9600);
}

void setup_stepper()
{
  //sets the RPM
  stepper.setRPM(12);
  //sets the Steps Per Rotation, in this case it is 64 * the 283712/4455 annoying ger ratio
  //for my motor (it works with float to be able to deal with these non-integer gear ratios)
  stepper.setSPR(4075.7728395);
}

// edm
#define trigPin 13
#define echoPin 12

void setup_edm()
{
  // distance
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop()
{
  double distance, max, ratio;
  max = 60;
  int currentMillis, angle, diff;

  diff = 0;
  
  currentMillis = millis();
  if(stepper.isDone() && (lastTime == 0 || currentMillis - lastTime >= 500))
  {
    lastTime = currentMillis;      
    distance = calculateDistance();
  
    if (distance > 0) {
      ratio = (double)distance / max;
      angle = ratio * 360;
      if (angle > 360) {
        angle = 360;
      }
     
      diff = lastAngle - angle;
      lastAngle = angle;
      
      Serial.print("Moving diff ");
      Serial.println(diff);
    }
  }
   
  if (stepper.isDone() && diff < 0)
  {
    Serial.println("CCW");
    stepper.setDirection(CCW);
    stepper.rotateDegrees(-diff);
  }
  if (stepper.isDone() && diff > 0)
  {
    Serial.println("CW");
    stepper.setDirection(CW);
    stepper.rotateDegrees(diff);
  }
  //if (stepper.isDone())
  //{
    //stepper.setDirection(STOP);
  //}
  // always run stepper loop
  stepper.run();
}

void setStepper(double angle)
{
  if (stepper.isDone() && angle < 0)
  {
    Serial.println("Stepper stop");
    stepper.setDirection(STOP);
  }
  if (stepper.isDone() && angle > 0)
  {
    if (lastAngle < angle)
    {
      Serial.println("Stepper CCW");
      stepper.setDirection(CCW);
    }
    else
    {
      Serial.println("Stepper CW");
      stepper.setDirection(CW);
    }
    stepper.rotateDegrees(angle);
    lastAngle = angle;
  }
}

long calculateDistance()
{
  long duration, distance, returnValue;

  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  
  if (distance > 200) {
    returnValue = -1;
  }
  else {
    returnValue = distance;
  }
  Serial.print(returnValue);  
  Serial.println(" cm");  
  return returnValue;
}

