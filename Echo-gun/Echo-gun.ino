/*
  HC-SR04 Ping distance sensor]
  VCC to arduino 5v GND to arduino GND
  Echo to Arduino pin 13 Trig to Arduino pin 12
*/
#include <MaxMatrix.h>
#include <avr/pgmspace.h>
#include "CharacterDefinitions.h"

const int trigPin = 13;
const int echoPin = 12;
const int piezoPin = 3;
const int buttonPin = 4;

// led matrix
const int DIN = 7;   // DIN pin of MAX7219 module
const int CLK = 6;   // CLK pin of MAX7219 module
const int CS = 5;    // CS pin of MAX7219 module
const int maxInUse = 1;

const int maxDistance = 200;
bool hasGraphData = false;
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

  pinMode(buttonPin, INPUT);
}

void loop() {

  int distance = readDistance();
  playTone(distance); 
  
  bool isValidMeasurement = distance < maxDistance && distance > 0;
  
  if (!isValidMeasurement) {
    Serial.println("Out of range ");
  }
  else {
    String text = String(distance) + " cm";
    Serial.println(text);
  }
  
  int buttonState = digitalRead(buttonPin);
  bool showGraph = buttonState == LOW;
  Serial.println("Button " + String(buttonState == HIGH));
  
  if (showGraph) {
    // Show graph
    hasGraphData = true;
    m.shiftLeft();
    int graphMax = 100;
    int height = distance * 8 / graphMax;
    height = abs(min(7, height) - 7);  
    m.setDot(7, height, 255);
  }
  else {
    if (hasGraphData) {
      m.clear();
      hasGraphData = false;
    }
    String text;
    if (isValidMeasurement) {
      text = String(distance) + ":";
    }
    else {
      text = String("!");
    }
    
    Serial.println(text);
    char textBuffer[text.length()+1];
    text.toCharArray(textBuffer, text.length() + 1);
    printStringWithShift(textBuffer, 75);    
  }
  
  delay(200);
}

int readDistance(){
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  int distance = (duration / 2) / 29.1;
  return distance;
}

void playTone(int distance)
{
  int toneFreq = distance * 50;
  toneFreq = max(200, min(8000, toneFreq));
  tone(piezoPin, toneFreq, 10);
}

void printCharWithShift(char c, int shift_speed) {
  // Display=the extracted characters with scrolling
  if (c < 32) return;
  c -= 32;
  int offset = 8 * maxInUse;
  memcpy_P(buffer, CH + 7 * c, 7);
  m.writeSprite(offset, 0, buffer);
  m.setColumn(offset + buffer[0], 0);

  for (int i = 0; i < buffer[0] + 1; i++)
  {
    delay(shift_speed);
    m.shiftLeft(false, false);
  }
}

// Extract the characters from the text string
void printStringWithShift(char* s, int shift_speed) {
  while (*s != 0) {
    printCharWithShift(*s, shift_speed);
    s++;
  }
}
