#include <Servo.h> //include Servo library

const int dangerThresh = 10; //threshold for obstacles (in cm)
int leftDistance, rightDistance; //distances on either side
Servo panMotor;  
long duration; //time it takes to recieve PING))) signal

#define trigPin 13
#define echoPin 12


// Motor 1
int dir1PinA = 2;
int dir2PinA = 3;
int speedPinA = 9; // Needs to be a PWM pin to be able to control motor speed

// Motor 2
int dir1PinB = 4;
int dir2PinB = 5;
int speedPinB = 10; // Needs to be a PWM pin to be able to control motor speed

void setup() 
{  
  Serial.begin(9600);

  //Define L298N Dual H-Bridge Motor Controller Pins
  pinMode(dir1PinA,OUTPUT);
  pinMode(dir2PinA,OUTPUT);
  pinMode(speedPinA,OUTPUT);
  pinMode(dir1PinB,OUTPUT);
  pinMode(dir2PinB,OUTPUT);
  pinMode(speedPinB,OUTPUT);
  panMotor.attach(6); //attach motors to proper pins
  panMotor.write(90); //set PING))) pan to center
  
  setup_edm();
}

void setup_edm()
{
  // distance
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  Motor1(1);
  Motor2(1);
}

void loop()
{
  int distanceFwd = Ping();
  if (distanceFwd == -1 || distanceFwd > dangerThresh) //if path is clear
  {
    //move forward
    Motor1(1);
    Motor2(1);
  }
  else //if path is blocked
  {
    // stop
    Motor1(0);
    Motor2(0); 
    panMotor.write(0); 
    delay(500);
    rightDistance = Ping(); //scan to the right
    delay(500);
    panMotor.write(180);
    delay(700);
    leftDistance = Ping(); //scan to the left
    delay(500);
    panMotor.write(90); //return to center
    delay(100);
    compareDistance();
  }
}
  
void compareDistance()
{
  if (leftDistance > rightDistance) //if left is less obstructed 
  {
    // turn left
    Motor1(-1);
    Motor2(1);
    delay(500); 
  }
  else if (rightDistance>leftDistance) //if right is less obstructed
  {
    // turn right
    Motor1(1);
    Motor2(-1);
    delay(500);
  }
   else //if they are equally obstructed
  {
    // turn 180
    Motor1(1);
    Motor2(-1);
    delay(1000);
  }
}

void Motor1(int dir)
{
  switch(dir)
  {
    case 1: // Motor 1 Forward
      analogWrite(speedPinA, 255);
      digitalWrite(dir1PinA, LOW);
      digitalWrite(dir2PinA, HIGH);
      Serial.println("Motor 1 Forward");
      Serial.println("   ");
      break;
    
    case 0: // Motor 1 Stop (Freespin)
      analogWrite(speedPinA, 0);
      digitalWrite(dir1PinA, LOW);
      digitalWrite(dir2PinA, LOW);
      Serial.println("Motor 1 Stop");
      Serial.println("   ");
      break;
    
    case -1: // Motor 1 Reverse
      analogWrite(speedPinA, 255);
      digitalWrite(dir1PinA, HIGH);
      digitalWrite(dir2PinA, LOW);
      Serial.println("Motor 1 Reverse");
      Serial.println("   ");
      break;
  }
}

void Motor2(int dir)
{
  switch(dir)
  {
    case 1: // Motor 2 Forward
      analogWrite(speedPinB, 255);
      digitalWrite(dir1PinB, LOW);
      digitalWrite(dir2PinB, HIGH);
      Serial.println("Motor 2 Forward");
      Serial.println("   ");
      break;
    
    case 0: // Motor 1 Stop (Freespin)
      analogWrite(speedPinB, 0);
      digitalWrite(dir1PinB, LOW);
      digitalWrite(dir2PinB, LOW);
      Serial.println("Motor 2 Stop");
      Serial.println("   ");
      break;
    
    case -1: // Motor 2 Reverse
      analogWrite(speedPinB, 255);
      digitalWrite(dir1PinB, HIGH);
      digitalWrite(dir2PinB, LOW);
      Serial.println("Motor 2 Reverse");
      Serial.println("   ");
      break;
  }
}

long Ping()
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

