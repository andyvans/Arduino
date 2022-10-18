
/*
 * IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */
#include <IRremote.h>
#include <PitchesTwo.h>

const int RECV_PIN = 11;
const int speakerPin = 7;

IRrecv irrecv(RECV_PIN);

decode_results results;
 
void setup()
{
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  if (irrecv.decode(&results)) 
  {
    //Serial.println(results.value, HEX);

    r2D2();
    //playSound(results.value);
    
    irrecv.resume(); // Receive the next value
  }
}

void playSound(int button)
{
  switch(button)
  {
    case 0xFF6897:
      analogWrite(5, 255);
      delay(100);
      analogWrite(5, 0);
      Serial.println("karl 5 on/off");
      break;
    case 0xFF9867:
      analogWrite(6, 255);
      delay(100);
      analogWrite(6, 0);
      Serial.println("mila 6 on/off");
      break;
    case 0xFFB04F:
      analogWrite(7, 255);
      delay(100);
      analogWrite(7, 0);
      Serial.println("clara 7 on/off");
      break;
  }
}

void r2D2(){
  beep(speakerPin, note_A7,100); //A
  beep(speakerPin, note_G7,100); //G
  beep(speakerPin, note_E7,100); //E
  beep(speakerPin, note_C7,100); //C
  beep(speakerPin, note_D7,100); //D
  beep(speakerPin, note_B7,100); //B
  beep(speakerPin, note_F7,100); //F
  beep(speakerPin, note_C8,100); //C
  beep(speakerPin, note_A7,100); //A
  beep(speakerPin, note_G7,100); //G
  beep(speakerPin, note_E7,100); //E
  beep(speakerPin, note_C7,100); //C
  beep(speakerPin, note_D7,100); //D
  beep(speakerPin, note_B7,100); //B
  beep(speakerPin, note_F7,100); //F
  beep(speakerPin, note_C8,100); //C
}

void beep (int speakerPin, float noteFrequency, long noteDuration)
{
  int x;
  // Convert the frequency to microseconds
  float microsecondsPerWave = 1000000/noteFrequency;
  // Calculate how many milliseconds there are per HIGH/LOW cycles.
  float millisecondsPerCycle = 1000/(microsecondsPerWave * 2);
  // Multiply noteDuration * number or cycles per millisecond
  float loopTime = noteDuration * millisecondsPerCycle;
  // Play the note for the calculated loopTime.
  for (x=0;x<loopTime;x++)
  {
    digitalWrite(speakerPin,HIGH);
    delayMicroseconds(microsecondsPerWave);
    digitalWrite(speakerPin,LOW);
    delayMicroseconds(microsecondsPerWave);
  }
}

