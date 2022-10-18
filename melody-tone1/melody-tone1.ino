#include <MelodyUtils.h>
#include <pitches.h>
#include <pitches2.h>

const int speakerPin = 7;

void setup()
{
  MelodyUtils mel(speakerPin);
  mel.Glis(NOTE_C3, NOTE_C4, 5);
  delay(1000);
  mel.Trem(NOTE_C3, 1000, 30);

  r2D2();
}

void loop()
{
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


