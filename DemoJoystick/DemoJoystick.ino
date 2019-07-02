#include <Servo.h>

const int SW_pin = 5; // digital pin connected to switch output
const int X_pin = 0; // analog pin connected to X output
const int Y_pin = 1; // analog pin connected to Y output

const int penServoPin = 11;
Servo penServo;
int lastAngle = 0;

void setup() {
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  Serial.begin(9600);

  penServo.attach(penServoPin);
  /*
  delay(1000);
  penServo.write(0);
  delay(1000);
  penServo.write(90);
  delay(1000);
  penServo.write(180);
  delay(1000);
  penServo.write(270);
  */
}

void loop() {
  
  Serial.print("Switch:  ");
  Serial.print(digitalRead(SW_pin));
  Serial.print("\n");
  
  Serial.print("X-axis: ");
  int xAxis = analogRead(X_pin);
  Serial.print(xAxis);
  Serial.print("\n");
  
  Serial.print("Y-axis: ");
  Serial.println(analogRead(Y_pin));
  Serial.print("\n\n");
  
  int angle = map(xAxis, 0, 1023, 60, 120);  
  if (angle != lastAngle)
  {
    lastAngle = angle;
    Serial.print("Angle: ");
    Serial.print(lastAngle);
    Serial.print("\n");
    //penServo.attach(penServoPin);
    //delay(50);
    penServo.write(lastAngle);
    //delay(50);
    //penServo.detach();
    delay(50);
  } 
}

