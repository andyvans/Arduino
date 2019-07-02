const int SW_pin = 5; // digital pin connected to switch output
const int X_pin = 0; // analog pin connected to X output
const int Y_pin = 1; // analog pin connected to Y output

const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;

const int joyStickMax = 910;

//uncomment this line if using a Common Anode LED
#define COMMON_ANODE

void setup()
{
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  Serial.begin(9600);

}
 
void loop()
{
  int button = digitalRead(SW_pin);
  int xAxis = analogRead(X_pin);
  int yAxis = analogRead(Y_pin);
  
  Serial.print(String("Switch ") + button + "\n"); 
  Serial.print(String("X-axis ") + xAxis + "\n");
  Serial.print(String("Y-axis ") + yAxis + "\n");
  
  int red = 255;
  int green = 255;
  int blue = 255;
  
  // red
  if (yAxis < joyStickMax/2)
  {
    red = yAxis / 2;
  }
  
  // green
  int g = max(xAxis, yAxis);
  if (g > joyStickMax/2)
  {
    green = abs(g - joyStickMax) / 2;
  }

  // blue
  int b = min(xAxis, abs(yAxis - joyStickMax));
  if (b < joyStickMax/2)
  {
    blue = b / 2;
  }
  
  Serial.print(String("R")+ red + " G" + green + " B" + blue + "\n");

  if (button == 0)
  {
    red = abs(red - 255);
    green = abs(green - 255);
    blue = abs(blue -  255);
  }
  setColour(red, green, blue);

  delay(100);
}

void setColour(int red, int green, int blue)
{
  #ifdef COMMON_ANODE
    red = 255 - red;
    green = 255 - green;
    blue = 255 - blue;
  #endif
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);  
}

