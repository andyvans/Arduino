// NB: ALL NOTES DEFINED WITH STANDARD ENGLISH NAMES, EXCEPT FROM "A" 
//THAT IS CALLED WITH THE ITALIAN NAME "LA" BECAUSE A0,A1...ARE THE ANALOG PINS ON ARDUINO.
// (Ab IS CALLED Ab AND NOT LAb)
#define	note_C0 16.35
#define	note_Db0	17.32
#define	note_D0	18.35
#define	note_Eb0	19.45
#define	note_E0	20.60
#define	note_F0	21.83
#define	note_Gb0	23.12
#define	note_G0	24.50
#define	note_Ab0	25.96
#define	note_LA0	27.50
#define	note_Bb0	29.14
#define	note_B0	30.87
#define	note_C1	32.70
#define	note_Db1	34.65
#define	note_D1	36.71
#define	note_Eb1	38.89
#define	note_E1	41.20
#define	note_F1	43.65
#define	note_Gb1	46.25
#define	note_G1	49.00
#define	note_Ab1	51.91
#define	note_LA1	55.00
#define	note_Bb1	58.27
#define	note_B1	61.74
#define	note_C2	65.41
#define	note_Db2	69.30
#define	note_D2	73.42
#define	note_Eb2	77.78
#define	note_E2	82.41
#define	note_F2	87.31
#define	note_Gb2	92.50
#define	note_G2	98.00
#define	note_Ab2	103.83
#define	note_LA2	110.00
#define	note_Bb2	116.54
#define	note_B2	123.47
#define	note_C3	130.81
#define	note_Db3	138.59
#define	note_D3	146.83
#define	note_Eb3	155.56
#define	note_E3	164.81
#define	note_F3	174.61
#define	note_Gb3	185.00
#define	note_G3	196.00
#define	note_Ab3	207.65
#define	note_LA3	220.00
#define	note_Bb3	233.08
#define	note_B3	246.94
#define	note_C4	261.63
#define	note_Db4	277.18
#define	note_D4	293.66
#define	note_Eb4	311.13
#define	note_E4	329.63
#define	note_F4	349.23
#define	note_Gb4	369.99
#define	note_G4	392.00
#define	note_Ab4	415.30
#define	note_LA4	440.00
#define	note_Bb4	466.16
#define	note_B4	493.88
#define	note_C5	523.25
#define	note_Db5	554.37
#define	note_D5	587.33
#define	note_Eb5	622.25
#define	note_E5	659.26
#define	note_F5	698.46
#define	note_Gb5	739.99
#define	note_G5	783.99
#define	note_Ab5	830.61
#define	note_LA5	880.00
#define	note_Bb5	932.33
#define	note_B5	987.77
#define	note_C6	1046.50
#define	note_Db6	1108.73
#define	note_D6	1174.66
#define	note_Eb6	1244.51
#define	note_E6	1318.51
#define	note_F6	1396.91
#define	note_Gb6	1479.98
#define	note_G6	1567.98
#define	note_Ab6	1661.22
#define	note_LA6	1760.00
#define	note_Bb6	1864.66
#define	note_B6	1975.53
#define	note_C7	2093.00
#define	note_Db7	2217.46
#define	note_D7	2349.32
#define	note_Eb7	2489.02
#define	note_E7	2637.02
#define	note_F7	2793.83
#define	note_Gb7	2959.96
#define	note_G7	3135.96
#define	note_Ab7	3322.44
#define	note_LA7	3520.01
#define	note_Bb7	3729.31
#define	note_B7	3951.07
#define	note_C8	4186.01
#define	note_Db8	4434.92
#define	note_D8	4698.64
#define	note_Eb8	4978.03
// DURATION OF THE NOTES 
#define BPM 120    //  you can change this value changing all the others
#define H 2*Q //half 2/4
#define Q 60000/BPM //quarter 1/4 
#define E Q/2   //eighth 1/8
#define S Q/4 // sixteenth 1/16
#define W 4*Q // whole 4/4

int speakerPin = 8;

void setup() {     
pinMode(8, OUTPUT);   
pinMode(9, OUTPUT);       
digitalWrite(9,LOW);

//r2D2();
closeEncounters();
//ohhh();
//uhoh();
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
 void loop()
 {
   
 }
 
void r2D2(){
beep(speakerPin, note_LA7,100); //A
beep(speakerPin, note_G7,100); //G
beep(speakerPin, note_E7,100); //E
beep(speakerPin, note_C7,100); //C
beep(speakerPin, note_D7,100); //D
beep(speakerPin, note_B7,100); //B
beep(speakerPin, note_F7,100); //F
beep(speakerPin, note_C8,100); //C
beep(speakerPin, note_LA7,100); //A
beep(speakerPin, note_G7,100); //G
beep(speakerPin, note_E7,100); //E
beep(speakerPin, note_C7,100); //C
beep(speakerPin, note_D7,100); //D
beep(speakerPin, note_B7,100); //B
beep(speakerPin, note_F7,100); //F
beep(speakerPin, note_C8,100); //C
}

void closeEncounters() {
beep(speakerPin, note_Bb5,300); //B b
delay(50);
beep(speakerPin, note_C6,300); //C
delay(50);
beep(speakerPin, note_Ab5,300); //A b
delay(50);
beep(speakerPin, note_Ab4,300); //A b
delay(50);
beep(speakerPin, note_Eb5,500); //E b
delay(500);
beep(speakerPin, note_Bb4,300); //B b
delay(100);
beep(speakerPin, note_C5,300); //C
delay(100);
beep(speakerPin, note_Ab4,300); //A b
delay(100);
beep(speakerPin, note_Ab3,300); //A b
delay(100);
beep(speakerPin, note_Eb4,500); //E b
delay(500);
beep(speakerPin, note_Bb3,300); //B b
delay(200);
beep(speakerPin, note_C4,300); //C
delay(200);
beep(speakerPin, note_Ab3,300); //A b
delay(500);
beep(speakerPin, note_Ab2,300); //A b
delay(550);
beep(speakerPin, note_Eb3,500); //E b
}

void ohhh() {
for (int i=1000; i<2000; i=i*1.02) { beep(speakerPin,i,10); } for (int i=2000; i>1000; i=i*.98) {
beep(speakerPin,i,10);
}
}


void uhoh() {
for (int i=1000; i<1244; i=i*1.01) { beep(speakerPin,i,30); } delay(200); for (int i=1244; i>1108; i=i*.99) {
beep(speakerPin,i,30);
}
}
