#include "musical_notes.h"
#include <IRremote.h>

const int RECV_PIN = 13;
IRrecv irrecv(RECV_PIN);
decode_results results;

int speakerPin = 7; // speaker connected to digital pin 9 

// servo start
#define IN1  8
#define IN2  9
#define IN3  10
#define IN4  11

int Steps = 0;
boolean Direction = true;// gre
unsigned long last_time;
unsigned long currentMillis ;
int steps_left=4095;
long time;
// servo end

// motor start

// Motor 1
int dir1PinA = 2;
int dir2PinA = 3;

// Motor 2
int dir1PinB = 4;
int dir2PinB = 5;
// motor end

void setup()    
{   
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  
  pinMode(speakerPin, OUTPUT); // sets the speakerPin to be an output 

  // stepper
  pinMode(IN1, OUTPUT); 
  pinMode(IN2, OUTPUT); 
  pinMode(IN3, OUTPUT); 
  pinMode(IN4, OUTPUT);

  // motor 1
  pinMode(dir1PinA,OUTPUT);
  pinMode(dir2PinA,OUTPUT);
  
  // motor 2
  pinMode(dir1PinB,OUTPUT);
  pinMode(dir2PinB,OUTPUT);
  
}    
      
void loop()
{ 
  if (irrecv.decode(&results)) 
  {
    Serial.println(results.value, HEX);

    playSound(results.value);
    
    irrecv.resume(); // Receive the next value
  }
}

void playSound(int button)
{
  switch(button)
  {
    case 0xFF6897: //1
      squeak();
      break;
    case 0xFF9867: //2
      r2D2();
      break;
    case 0xFFB04F: //3
      ohhh();
      break;
    case 0xFF30CF: //4
      laugh();
      break;
    case 0xFF18E7: //5
      uhoh();
      break;
    case 0xFF7A85: //6
      laugh2();
      break;
    case 0xFF10EF: //7
      waka();
      break;
    case 0xFF38C7: //8
      catcall();
      break;
    case 0xFF5AA5: //9
      ariel();
      break;
    case 0xFF4AB5: //0
      scale();
      break;
    case 0xFF42BD: //*
      lookLeft();  
      break;
    case 0xFF52AD: //#
      lookRight();
      break;
    case 0xFF22DD: //L
      left();
      break;
    case 0xFFC23D: //R
      right();
      break;
    case 0xFF629D: //U
      forward();
      break;
    case 0xFFA857: //D
      back();
      break;
    case 0xFF02FD: //OK
      break;
  }
}

void forward()
{
  Motor1(1);
  Motor2(1);
  delay(750);
  Motor1(0);
  Motor2(0);
}

void back()
{
  Motor1(-1);
  Motor2(-1);
  delay(750);
  Motor1(0);
  Motor2(0);
}

void left()
{
  // turn left
  Motor1(-1);
  Motor2(1);
  delay(750);
  Motor1(0);
  Motor2(0);
}

void right()
{
  // turn left
  Motor1(1);
  Motor2(-1);
  delay(750);
  Motor1(0);
  Motor2(0);
}

void Motor1(int dir)
{
  switch(dir)
  {
    case 1: // Motor 1 Forward
      digitalWrite(dir1PinA, LOW);
      digitalWrite(dir2PinA, HIGH);
      Serial.println("Motor 1 Forward");
      Serial.println("   ");
      break;
    
    case 0: // Motor 1 Stop (Freespin)
      digitalWrite(dir1PinA, LOW);
      digitalWrite(dir2PinA, LOW);
      Serial.println("Motor 1 Stop");
      Serial.println("   ");
      break;
    
    case -1: // Motor 1 Reverse
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
      digitalWrite(dir1PinB, LOW);
      digitalWrite(dir2PinB, HIGH);
      Serial.println("Motor 2 Forward");
      Serial.println("   ");
      break;
    
    case 0: // Motor 1 Stop (Freespin)
      digitalWrite(dir1PinB, LOW);
      digitalWrite(dir2PinB, LOW);
      Serial.println("Motor 2 Stop");
      Serial.println("   ");
      break;
    
    case -1: // Motor 2 Reverse
      digitalWrite(dir1PinB, HIGH);
      digitalWrite(dir2PinB, LOW);
      Serial.println("Motor 2 Reverse");
      Serial.println("   ");
      break;
  }
}

void lookLeft()
{
  Serial.println("look left");
  Direction=false;
  steps_left=800;
    
  while(steps_left>0){
    currentMillis = micros();
    if(currentMillis-last_time>=1000){
      stepper(1); 
      time=time+micros()-last_time;
      last_time=micros();
      steps_left--;
    }
  }
  Serial.println(time);
  Serial.println("Wait...!");
}

void lookRight()
{
  Serial.println("look left");
  Direction=true;
  steps_left=800;
    
  while(steps_left>0){
    currentMillis = micros();
    if(currentMillis-last_time>=1000){
      stepper(1); 
      time=time+micros()-last_time;
      last_time=micros();
      steps_left--;
    }
  }
  Serial.println(time);
  Serial.println("Wait...!");
}

void stepper(int xw){
  for (int x=0;x<xw;x++){
    switch(Steps){
       case 0:
         digitalWrite(IN1, LOW); 
         digitalWrite(IN2, LOW);
         digitalWrite(IN3, LOW);
         digitalWrite(IN4, HIGH);
         break; 
       case 1:
         digitalWrite(IN1, LOW); 
         digitalWrite(IN2, LOW);
         digitalWrite(IN3, HIGH);
         digitalWrite(IN4, HIGH);
         break; 
       case 2:
         digitalWrite(IN1, LOW); 
         digitalWrite(IN2, LOW);
         digitalWrite(IN3, HIGH);
         digitalWrite(IN4, LOW);
         break; 
       case 3:
         digitalWrite(IN1, LOW); 
         digitalWrite(IN2, HIGH);
         digitalWrite(IN3, HIGH);
         digitalWrite(IN4, LOW);
         break; 
       case 4:
         digitalWrite(IN1, LOW); 
         digitalWrite(IN2, HIGH);
         digitalWrite(IN3, LOW);
         digitalWrite(IN4, LOW);
         break; 
       case 5:
         digitalWrite(IN1, HIGH); 
         digitalWrite(IN2, HIGH);
         digitalWrite(IN3, LOW);
         digitalWrite(IN4, LOW);
         break; 
       case 6:
         digitalWrite(IN1, HIGH); 
         digitalWrite(IN2, LOW);
         digitalWrite(IN3, LOW);
         digitalWrite(IN4, LOW);
         break; 
       case 7:
         digitalWrite(IN1, HIGH); 
         digitalWrite(IN2, LOW);
         digitalWrite(IN3, LOW);
         digitalWrite(IN4, HIGH);
         break; 
       default:
         digitalWrite(IN1, LOW); 
         digitalWrite(IN2, LOW);
         digitalWrite(IN3, LOW);
         digitalWrite(IN4, LOW);
         break; 
    }
    SetDirection();
  }
} 

void SetDirection(){
  if(Direction==1){ Steps++;}
  if(Direction==0){ Steps--; }
  if(Steps>7){Steps=0;}
  if(Steps<0){Steps=7; }
}


void playAllSounds()
{
      squeak();
      delay(500);
      catcall();
      delay(500);
      ohhh();
      delay(500);
      laugh();
      delay(500);
      closeEncounters();
      delay(500);
      laugh2();
      delay(500);
      waka();
      delay(500);  
      r2D2();
      delay(500);
      ariel();
      delay(500);
      scale();
      delay(50);
      uhoh();
      delay(3000);
}     
     
void beep (int speakerPin, float noteFrequency, long noteDuration)
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
     
void scale() 
{    
          beep(speakerPin, note_C7,500); //C: play the note C for 500ms 
          beep(speakerPin, note_D7,500); //D 
          beep(speakerPin, note_E7,500); //E 
          beep(speakerPin, note_F7,500); //F 
          beep(speakerPin, note_G7,500); //G 
          beep(speakerPin, note_A7,500); //A 
          beep(speakerPin, note_B7,500); //B 
          beep(speakerPin, note_C8,500); //C 
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

void ariel() {

          beep(speakerPin, note_C6,300); //C
          delay(50);
          beep(speakerPin, note_D6,300); //D
          delay(50);
          beep(speakerPin, note_Eb6,600); //D#
          delay(250);
          
          beep(speakerPin, note_D6,300); //D
          delay(50);
          beep(speakerPin, note_Eb6,300); //D#
          delay(50);
          beep(speakerPin, note_F6,600); //F
          delay(250);
          
          beep(speakerPin, note_C6,300); //C
          delay(50);
          beep(speakerPin, note_D6,300); //D
          delay(50);
          beep(speakerPin, note_Eb6,500); //D#
          delay(50);          
          beep(speakerPin, note_D6,300); //D
          delay(50);
          beep(speakerPin, note_Eb6,300); //D#
          delay(50);             
          beep(speakerPin, note_D6,300); //D
          delay(50);
          beep(speakerPin, note_Eb6,300); //D#
          delay(50);
          beep(speakerPin, note_F6,600); //F
          delay(50); 

}
 

void laugh2() {
          beep(speakerPin, note_C6,200); //C
          beep(speakerPin, note_E6,200); //E  
          beep(speakerPin, note_G6,200); //G 
          beep(speakerPin, note_C7,200); //C 
          beep(speakerPin, note_C6,200); //C
          delay(50);
          beep(speakerPin, note_C6,200); //C
          beep(speakerPin, note_E6,200); //E  
          beep(speakerPin, note_G6,200); //G 
          beep(speakerPin, note_C7,200); //C 
          beep(speakerPin, note_C6,200); //C
          delay(50);
          beep(speakerPin, note_C6,50); //C
          delay(50);
          beep(speakerPin, note_C6,50); //C
          delay(50);
          beep(speakerPin, note_C6,50); //C
          delay(50);
          beep(speakerPin, note_C6,50); //C
          delay(50);
          beep(speakerPin, note_C6,50); //C
          delay(50);
          beep(speakerPin, note_C6,50); //C
          delay(50);
          beep(speakerPin, note_C6,50); //C
          

          
}
  
void squeak() {
  for (int i=100; i<5000; i=i*1.45) {
    beep(speakerPin,i,60);
  }
  delay(10);
  for (int i=100; i<6000; i=i*1.5) {
    beep(speakerPin,i,20);
  }
}

void waka() {
  for (int i=1000; i<3000; i=i*1.05) {
    beep(speakerPin,i,10);
  }
  delay(100);
  for (int i=2000; i>1000; i=i*.95) {
    beep(speakerPin,i,10);
  }
    for (int i=1000; i<3000; i=i*1.05) {
    beep(speakerPin,i,10);
  }
  delay(100);
  for (int i=2000; i>1000; i=i*.95) {
    beep(speakerPin,i,10);
  }
    for (int i=1000; i<3000; i=i*1.05) {
    beep(speakerPin,i,10);
  }
  delay(100);
  for (int i=2000; i>1000; i=i*.95) {
    beep(speakerPin,i,10);
  }
    for (int i=1000; i<3000; i=i*1.05) {
    beep(speakerPin,i,10);
  }
  delay(100);
  for (int i=2000; i>1000; i=i*.95) {
    beep(speakerPin,i,10);
  }
}

void catcall() {
  for (int i=1000; i<5000; i=i*1.05) {
    beep(speakerPin,i,10);
  }
 delay(300);
 
  for (int i=1000; i<3000; i=i*1.03) {
    beep(speakerPin,i,10);
  }
  for (int i=3000; i>1000; i=i*.97) {
    beep(speakerPin,i,10);
  }
}

void ohhh() {
  for (int i=1000; i<2000; i=i*1.02) {
    beep(speakerPin,i,10);
  }
  for (int i=2000; i>1000; i=i*.98) {
    beep(speakerPin,i,10);
  }
}

void uhoh() {
  for (int i=1000; i<1244; i=i*1.01) {
    beep(speakerPin,i,30);
  }
  delay(200);
  for (int i=1244; i>1108; i=i*.99) {
    beep(speakerPin,i,30);
  }
}

void laugh() {
  for (int i=1000; i<2000; i=i*1.10) {
    beep(speakerPin,i,10);
  }
  delay(50);
  for (int i=1000; i>500; i=i*.90) {
    beep(speakerPin,i,10);
  }
  delay(50);
  for (int i=1000; i<2000; i=i*1.10) {
    beep(speakerPin,i,10);
  }
  delay(50);
  for (int i=1000; i>500; i=i*.90) {
    beep(speakerPin,i,10);
  }
  delay(50);
    for (int i=1000; i<2000; i=i*1.10) {
    beep(speakerPin,i,10);
  }
  delay(50);
  for (int i=1000; i>500; i=i*.90) {
    beep(speakerPin,i,10);
  }
  delay(50);
    for (int i=1000; i<2000; i=i*1.10) {
    beep(speakerPin,i,10);
  }
  delay(50);
  for (int i=1000; i>500; i=i*.90) {
    beep(speakerPin,i,10);
  }
  delay(50);
}
