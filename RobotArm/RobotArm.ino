#include <Servo.h>
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

void setup()
{
  Serial.begin(9600);

  servo1.attach(4);
  servo2.attach(5);
  //servo3.attach(6);
  //servo4.attach(7);
}

int readPot(int analogPotIndex)
{
  int newPotPos = analogRead(analogPotIndex);
  int newMapPos = map(newPotPos, 0, 912, 0, 180);

  Serial.print("Pot: " + String(analogPotIndex) + " analog: " + String(newPotPos) + " map: " + String(newMapPos) + "\n");

  servo1.write(newMapPos);
  return newMapPos;
}

void loop()
{
  int newPot1Pos = readPot(0);
  int newPot2Pos = readPot(1);
  //int newPot3Pos = readPot(2);
  //int newPot4Pos = readPot(3);

  //Serial.print("NewPotPos: " + String(newPot1Pos));
  servo1.write(newPot1Pos);
  //servo2.write(newPot2Pos);
  //servo3.write(newPot3Pos);
  //servo4.write(newPot4Pos);
  /*
  if (newPot1Pos != pot1Pos && newPot1Pos >= 0 && newPot1Pos <= 180)
  {
    pot1Pos = newPot1Pos;
    servo1.write(pot1Pos);
  }
  if (pot2Pos > 0 && pot2Pos < 180)
  {
    //servo2.write(pot2Pos);
  }
  if (pot3Pos > 0 && pot3Pos < 180)
  {
    //servo3.write(pot3Pos);
  }
  if (pot4Pos > 0 && pot4Pos < 180)
  {
    //servo4.write(pot4Pos);
  }
  */

  delay(200);
}
