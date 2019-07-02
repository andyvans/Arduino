#include <TimerFreeTone.h>

#include <musical_notes.h>

int speakerPin = 8;

namespace ssTone
{
  typedef struct
  {
    int note;
    int duration;
  } mTone;
  
  mTone r2d2Melody[] = 
  {
    {note_A7,100},
    {note_G7,100},
    {note_E7,100}, 
    {note_C7,100},
    {note_D7,100}, 
    {note_B7,100}, 
    {note_F7,100}, 
    {note_C8,100}, 
    {note_A7,100}, 
    {note_G7,100}, 
    {note_E7,100}, 
    {note_C7,100},
    {note_D7,100}, 
    {note_B7,100}, 
    {note_F7,100}, 
    {note_C8,100}
  };

  void playTones(mTone mTones[])
  {
    int number = sizeof(mTones)/sizeof(mTone);
    Serial.print("playing tones : ");
    Serial.println(number);
    int i = 0;
    for (i = 0; i < number; ++i)
    {
      TimerFreeTone(speakerPin, mTones[i].note, mTones[i].duration);
      
    }
  }
}

void setup() 
{
  Serial.begin(9600);
  ssTone:playTones(ssTone::r2d2Melody);
}

void loop() 
{
  ssTone:playTones(ssTone::r2d2Melody);
  
  delay(3000);

  //r2D2();

  //delay(2000);

}



void r2D2()
{
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

void beep(int speakerPin, float noteFrequency, long noteDuration)
{    
  int x;
  // Convert the frequency to microseconds
  float microsecondsPerWave = 1000000/noteFrequency;
  // Calculate how many HIGH/LOW cycles there are per millisecond
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
