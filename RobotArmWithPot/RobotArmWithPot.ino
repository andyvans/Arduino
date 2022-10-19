//add servo library
#include <Servo.h>

//define our servos
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

//define our potentiometers
int pot1 = A0;
int pot2 = A1;
int pot3 = A2;
int pot4 = A3;

//variable to read the values from the analog pin (potentiometers)
int currentServo1;
int currentServo2;
int currentServo3;
int currentServo4;

int servoDelay = 8;

void setup()
{
  Serial.begin(9600);
  //attaches our servos on pins PWM 11-10-9-6 to the servos
  servo1.attach(11);
  servo2.attach(10);
  servo3.attach(9);
  servo4.attach(6);
  
  Serial.println("Robot arm started");
}

void loop()
{
  int changes = 0;
  //reads the value of potentiometers (value between 0 and 1023)
  int valPot1 = analogRead(pot1);
  valPot1 = map (valPot1, 0, 1023, 1, 179);
  valPot1 = min(max(valPot1, 20), 170);
  if (valPot1 != currentServo1 && valPot1 % 2 == 0) 
  {
    servo1.write(valPot1);
    delay(abs(currentServo1 - valPot1) * servoDelay);
    currentServo1 = valPot1;
    changes++;
  }

  int valPot2 = analogRead(pot2);
  valPot2 = map (valPot2, 0, 1023, 1, 179);
  valPot2 = min(max(valPot2, 120), 180);
  if (valPot2 != currentServo2 && valPot2 % 2 == 0) 
  {
    servo2.write(valPot2);
    delay(abs(currentServo2 - valPot2) * servoDelay);
    currentServo2 = valPot2;
    changes++;
  }

  int valPot3 = analogRead(pot3);
  valPot3 = map (valPot3, 0, 1023, 1, 179);
  valPot3 = min(max(valPot3, 20), 110);
  if (valPot3 != currentServo3 && valPot3 % 2 == 0) 
  {
    servo3.write(valPot3);
    delay(abs(currentServo3 - valPot3) * servoDelay);
    currentServo3 = valPot3;
    changes++;
  }

  int valPot4 = analogRead(pot4);
  valPot4 = map (valPot4, 0, 1023, 1, 179);
  valPot4 = min(max(valPot4, 40), 160);
  if (valPot4 != currentServo4 && valPot4 % 2 == 0) 
  {
    servo4.write(valPot4);
    delay(abs(currentServo4 - valPot4) * servoDelay);
    currentServo4 = valPot4;
    changes++;
  }

  if (changes > 0)
  {
    Serial.print("POT: ");
    Serial.print(currentServo1);
    Serial.print(", ");
    Serial.print(currentServo2);
    Serial.print(", ");
    Serial.print(currentServo3);
    Serial.print(", ");
    Serial.print(currentServo4);
    Serial.println();
  }
  else
  {
    delay(servoDelay);
  }
}
