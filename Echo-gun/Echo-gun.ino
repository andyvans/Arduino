/*
  HC-SR04 Ping distance sensor]
  VCC to arduino 5v GND to arduino GND
  Echo to Arduino pin 13 Trig to Arduino pin 12
*/
#include <MaxMatrix.h>
#include <avr/pgmspace.h>

// echo
#define trigPin 13
#define echoPin 12

// sound
#define piezoPin 3 // piezo

int distance = 0;

// led matrix
int DIN = 7;   // DIN pin of MAX7219 module
int CLK = 6;   // CLK pin of MAX7219 module
int CS = 5;    // CS pin of MAX7219 module
int maxInUse = 1;

MaxMatrix m(DIN, CS, CLK, maxInUse);

byte buffer[10];

void setup() {
  Serial.begin (9600);

  // init echo
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // init matrix
  m.init(); // module initialize
  m.setIntensity(15); // dot matix intensity 0-15
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;

  playTone();
  m.shiftRight();

  int maxDistance = 200;
  if (distance >= maxDistance || distance <= 0) {
    Serial.println("Out of range ");
  }
  else {
    Serial.print(distance);
    Serial.println(" cm");

    int graphMax = 100;
    int height = distance * 8 / graphMax;
    height = min(7, height);  
    m.setDot(0, height, 255);
  }
  delay(150);
}

void playTone()
{
  int toneFreq = distance * 50;
  toneFreq = max(200, min(8000, toneFreq));
  tone(piezoPin, toneFreq, 10);
}
