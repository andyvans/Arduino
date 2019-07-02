// Pong

#include "TouchScreen.h"
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library

#define DEBUG

#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4

#define powerPin 53 //will turn on to power sensor(s)
#define sensorPin A14 // sensor one
#define sensor2Pin A15 // sensor two
#define piezoPin 30 // piezo

// These are the pins for the shield!
#define YP A3  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 9   // can be a digital pin
#define XP 8   // can be a digital pin

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define GREY      0xCE79
#define LIGHTGREY 0xDEDB

Adafruit_TFTLCD display(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 364);
const int WIDTH = 320;
const int HEIGHT = 240;
const int BORDER_TOP = 0;
const int BORDER_BOTTOM = HEIGHT - 1;
const int BORDER_LEFT = 0;
const int BORDER_RIGHT = WIDTH - 1;

// Pong
const unsigned long PADDLE_RATE = 8;
const unsigned long BALL_RATE = 12;
const uint8_t PADDLE_HEIGHT = 35;
int MAX_SCORE = 8;

int CPU_SCORE = 0;
int PLAYER_SCORE = 0;
#define UP_BUTTON 22
#define DOWN_BUTTON 42

// Declarations
void drawCourt();

unsigned long ball_update;
unsigned long paddle_update;

const int CPU_X = 12;
const int PLAYER_X = WIDTH - 12;

int cpu_y = HEIGHT / 2 - PADDLE_HEIGHT / 2;
int player_y = HEIGHT / 2 - PADDLE_HEIGHT / 2;
int ball_x = WIDTH;
int ball_y = HEIGHT / 2;
int ball_dir_x = 1;
int ball_dir_y = 1;

boolean gameIsRunning = true;
boolean resetBall = false;

static const unsigned char pong []PROGMEM = {
  0xff, 0xe0, 0x0, 0x3f, 0x80, 0x7, 0xe0, 0x7, 0xc0, 0x3, 0xfc, 0x0,
  0xff, 0xf8, 0x1, 0xff, 0xe0, 0x7, 0xf0, 0x7, 0xc0, 0x1f, 0xff, 0x0,
  0xff, 0xfc, 0x3, 0xff, 0xf0, 0x7, 0xf0, 0x7, 0xc0, 0x3f, 0xff, 0x0,
  0xff, 0xfe, 0x7, 0xff, 0xf8, 0x7, 0xf8, 0x7, 0xc0, 0xff, 0xff, 0x0,
  0xf8, 0x7f, 0xf, 0xff, 0xfc, 0x7, 0xfc, 0x7, 0xc0, 0xff, 0xff, 0x0,
  0xf8, 0x3f, 0xf, 0xe0, 0xfe, 0x7, 0xfc, 0x7, 0xc1, 0xfc, 0x7, 0x0,
  0xf8, 0x1f, 0x1f, 0x80, 0x7e, 0x7, 0xfe, 0x7, 0xc3, 0xf8, 0x1, 0x0,
  0xf8, 0x1f, 0x1f, 0x0, 0x3e, 0x7, 0xfe, 0x7, 0xc3, 0xf0, 0x0, 0x0,
  0xf8, 0x1f, 0x3f, 0x0, 0x3f, 0x7, 0xdf, 0x7, 0xc7, 0xe0, 0x0, 0x0,
  0xf8, 0x1f, 0x3e, 0x0, 0x1f, 0x7, 0xdf, 0x87, 0xc7, 0xc0, 0x0, 0x0,
  0xf8, 0x3f, 0x3e, 0x0, 0x1f, 0x7, 0xcf, 0x87, 0xc7, 0xc1, 0xff, 0x80,
  0xf8, 0x7e, 0x3e, 0x0, 0x1f, 0x7, 0xc7, 0xc7, 0xc7, 0xc1, 0xff, 0x80,
  0xff, 0xfe, 0x3e, 0x0, 0x1f, 0x7, 0xc7, 0xe7, 0xc7, 0xc1, 0xff, 0x80,
  0xff, 0xfc, 0x3e, 0x0, 0x1f, 0x7, 0xc3, 0xe7, 0xc7, 0xc1, 0xff, 0x80,
  0xff, 0xf8, 0x3e, 0x0, 0x1f, 0x7, 0xc1, 0xf7, 0xc7, 0xc0, 0xf, 0x80,
  0xff, 0xe0, 0x3f, 0x0, 0x3f, 0x7, 0xc1, 0xf7, 0xc7, 0xe0, 0xf, 0x80,
  0xf8, 0x0, 0x1f, 0x0, 0x3e, 0x7, 0xc0, 0xff, 0xc3, 0xe0, 0xf, 0x80,
  0xf8, 0x0, 0x1f, 0x80, 0x7e, 0x7, 0xc0, 0x7f, 0xc3, 0xf0, 0xf, 0x80,
  0xf8, 0x0, 0x1f, 0xc0, 0xfc, 0x7, 0xc0, 0x7f, 0xc3, 0xfc, 0xf, 0x80,
  0xf8, 0x0, 0xf, 0xff, 0xfc, 0x7, 0xc0, 0x3f, 0xc1, 0xff, 0xff, 0x80,
  0xf8, 0x0, 0x7, 0xff, 0xf8, 0x7, 0xc0, 0x3f, 0xc0, 0xff, 0xff, 0x80,
  0xf8, 0x0, 0x3, 0xff, 0xf0, 0x7, 0xc0, 0x1f, 0xc0, 0x7f, 0xff, 0x80,
  0xf8, 0x0, 0x1, 0xff, 0xe0, 0x7, 0xc0, 0xf, 0xc0, 0x3f, 0xff, 0x0,
  0xf8, 0x0, 0x0, 0x7f, 0x0, 0x7, 0xc0, 0xf, 0xc0, 0x7, 0xf8, 0x0
};

static const unsigned char game []PROGMEM = {
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0xff, 0x80,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xc3, 0xff, 0x80,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf, 0xc3, 0xff, 0x80,
  0x0, 0x0, 0x0, 0x0, 0x3, 0xe0, 0xf, 0xc3, 0xe0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x7, 0xf0, 0x1f, 0xc1, 0xe0, 0x0,
  0x0, 0x0, 0x0, 0xf8, 0x7, 0xf0, 0x1f, 0xc1, 0xe0, 0x0,
  0x0, 0xfc, 0x1, 0xfc, 0x7, 0xf8, 0x1f, 0xc1, 0xe0, 0x0,
  0x7, 0xfc, 0x1, 0xfc, 0x3, 0xf8, 0x1f, 0xe1, 0xff, 0x80,
  0x1f, 0xfc, 0x1, 0xde, 0x3, 0xbc, 0x3d, 0xe1, 0xff, 0x80,
  0x3f, 0xfe, 0x1, 0xde, 0x3, 0xbc, 0x39, 0xe1, 0xff, 0x80,
  0x7e, 0x0, 0x3, 0xdf, 0x3, 0xde, 0x39, 0xe1, 0xfc, 0x0,
  0x7c, 0x0, 0x3, 0xcf, 0x3, 0xde, 0x39, 0xe1, 0xe0, 0x0,
  0xf8, 0x0, 0x3, 0xcf, 0x3, 0xcf, 0x39, 0xe1, 0xf0, 0x0,
  0xf8, 0x0, 0x3, 0x87, 0x83, 0xcf, 0x79, 0xe0, 0xf0, 0x0,
  0xf0, 0x7f, 0x7, 0x87, 0x83, 0xc7, 0xf1, 0xe0, 0xf0, 0xe0,
  0xf0, 0xff, 0x7, 0x83, 0xc3, 0xc7, 0xf1, 0xe0, 0xff, 0xe0,
  0xf0, 0xff, 0x7, 0xff, 0xc1, 0xc3, 0xf1, 0xf0, 0xff, 0xe0,
  0xf0, 0xff, 0x7, 0xff, 0xe1, 0xc3, 0xf0, 0xf0, 0xff, 0xe0,
  0xf8, 0xf, 0xf, 0xff, 0xe1, 0xc1, 0xe0, 0xf0, 0xe0, 0x0,
  0xf8, 0xf, 0x8f, 0x1, 0xf1, 0xe1, 0xe0, 0xf0, 0x0, 0x0,
  0x7c, 0xf, 0x8f, 0x0, 0xf1, 0xe1, 0xe0, 0x0, 0x0, 0x0,
  0x7f, 0x1f, 0x8f, 0x0, 0xf9, 0xc0, 0x0, 0x0, 0x0, 0x0,
  0x3f, 0xff, 0x9f, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x1f, 0xff, 0x1f, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x7, 0xfc, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0
};

// Code
void setup()
{
#ifdef DEBUG
  Serial.begin(9600);
#endif // DEBUG

  pinMode(powerPin, OUTPUT);
  digitalWrite(powerPin, HIGH); // turn sensor power on
  pinMode(UP_BUTTON, INPUT_PULLUP);
  pinMode(DOWN_BUTTON, INPUT_PULLUP);

  display.reset();

  uint16_t identifier = display.readID();

  display.begin(identifier);

  display.fillScreen(BLACK);
  display.setRotation(1);
  display.setCursor(30, 100);
  display.setTextColor(RED);  display.setTextSize(2);
  display.println("LCD driver chip: ");
  display.setCursor(100, 150);
  display.setTextColor(BLUE);
  display.println(identifier, HEX);
  delay(1000);

  display.fillScreen(BLACK);
  display.drawBitmap(WIDTH / 2 - 45, HEIGHT / 2 - 12, pong, 89, 24, GREEN);
  display.drawBitmap(WIDTH / 2 - 37, HEIGHT / 2 + 13, game, 75, 26, RED);
  while (digitalRead(UP_BUTTON) == HIGH && digitalRead(DOWN_BUTTON) == HIGH)
  {
    delay(100);
  }

  unsigned long start = millis();

  display.fillScreen(BLACK);
  drawCourt();

  while (millis() - start < 2000);
  ball_update = millis();
  paddle_update = ball_update;
  ball_x = WIDTH / 2;
  ball_y = random(50, HEIGHT - 50);
}

//////////////////////////////////////////////////////////////////////////////////
void loop()
{
  unsigned long time = millis();
  static bool up_state = false;
  static bool down_state = false;

  up_state |= (digitalRead(UP_BUTTON) == LOW);
  down_state |= (digitalRead(DOWN_BUTTON) == LOW);

  if (resetBall)
  {
    ball_x = random(100, WIDTH - 100);
    ball_y = random(10, HEIGHT - 10);
    do
    {
      ball_dir_x = random(-1, 2);
    } while (ball_dir_x == 0);

    do
    {
      ball_dir_y = random(-1, 2);
    } while (ball_dir_y == 0);

    resetBall = false;
  }

  if (time > ball_update && gameIsRunning)
  {
    int new_x = ball_x + ball_dir_x;
    int new_y = ball_y + ball_dir_y;

    // Check if we hit the vertical walls
    if (new_x == 0) //Player Gets a Point
    {
      tone(piezoPin, 1000, 500);      
      PLAYER_SCORE++;
      if (PLAYER_SCORE == MAX_SCORE)
      {
        gameOver();
      }
      else
      {
        showScore();
      }
    }

    // Check if we hit the vertical walls
    if (new_x == BORDER_RIGHT) //CPU Gets a Point
    {
      tone(piezoPin, 1000, 500);
      CPU_SCORE++;
      if (CPU_SCORE == MAX_SCORE)
      {
        gameOver();
      } else
      {
        showScore();
      }
    }

    // Check if we hit the horizontal walls.
    if (new_y == BORDER_TOP || new_y == BORDER_BOTTOM) 
    {
      tone(piezoPin, 3000, 200);
      ball_dir_y = -ball_dir_y;
      new_y += ball_dir_y + ball_dir_y;
    }

    // Check if we hit the CPU paddle
    if (new_x == CPU_X && new_y >= cpu_y && new_y <= cpu_y + PADDLE_HEIGHT) 
    {
      tone(piezoPin, 2000, 200);
      ball_dir_x = -ball_dir_x;
      new_x += ball_dir_x + ball_dir_x;
    }

    // Check if we hit the player paddle
    if (new_x == PLAYER_X && new_y >= player_y && new_y <= player_y + PADDLE_HEIGHT)
    {
      tone(piezoPin, 2000, 200);
      ball_dir_x = -ball_dir_x;
      new_x += ball_dir_x + ball_dir_x;
    }

    display.drawFastVLine(ball_x, ball_y, 2, BLACK);
    display.drawFastVLine(ball_x, ball_y, 2, BLACK);

    display.drawFastVLine(new_x, new_y, 2, WHITE);
    display.drawFastVLine(new_x, new_y, 2, WHITE);

    ball_x = new_x;
    ball_y = new_y;

    ball_update += BALL_RATE;
  }

  if (time > paddle_update && gameIsRunning)
  {
    paddle_update += PADDLE_RATE;

    // CPU paddle
    display.drawFastVLine(CPU_X, cpu_y, PADDLE_HEIGHT, BLACK);
    display.drawFastVLine(CPU_X - 1, cpu_y, PADDLE_HEIGHT, BLACK);
    const int half_paddle = PADDLE_HEIGHT / 2;
    if (cpu_y + half_paddle > ball_y) {
      cpu_y -= 1;
    }
    if (cpu_y + half_paddle < ball_y) {
      cpu_y += 1;
    }
    if (cpu_y < 1) cpu_y = 1;
    if (cpu_y + PADDLE_HEIGHT > BORDER_BOTTOM) cpu_y = BORDER_BOTTOM - PADDLE_HEIGHT;
    display.drawFastVLine(CPU_X, cpu_y, PADDLE_HEIGHT, RED);
    display.drawFastVLine(CPU_X - 1, cpu_y, PADDLE_HEIGHT, RED);

    // Player paddle
    display.drawFastVLine(PLAYER_X, player_y, PADDLE_HEIGHT, BLACK);
    display.drawFastVLine(PLAYER_X + 1, player_y, PADDLE_HEIGHT, BLACK);
    if (up_state) {
      player_y -= 1;
    }
    if (down_state) {
      player_y += 1;
    }
    up_state = down_state = false;
    if (player_y < 1) player_y = 1;
    if (player_y + PADDLE_HEIGHT > BORDER_BOTTOM) player_y = BORDER_BOTTOM - PADDLE_HEIGHT;
    display.drawFastVLine(PLAYER_X, player_y, PADDLE_HEIGHT, GREEN);
    display.drawFastVLine(PLAYER_X + 1, player_y, PADDLE_HEIGHT, GREEN);
  }
}

void drawCourt()
{
  display.drawRect(0, 0, WIDTH, HEIGHT, WHITE);
}

void gameOver()
{
  gameIsRunning = false;
  display.fillScreen(BLACK);
  drawCourt();
  if (PLAYER_SCORE > CPU_SCORE)
  {
    display.setCursor(5, 4);
    display.setTextColor(WHITE);
    display.setTextSize(2);
    display.print("You Won");
  } else
  {
    display.setCursor(5, 4);
    display.setTextColor(WHITE);
    display.setTextSize(2);
    display.print("Arduino WON");
  }

  display.setCursor(20, 30);
  display.setTextColor(RED);
  display.setTextSize(3);
  display.print(String(CPU_SCORE));

  display.setCursor(60, 30);
  display.setTextColor(GREEN);
  display.setTextSize(3);
  display.print(String(PLAYER_SCORE));

  delay(2000);

  while (digitalRead(UP_BUTTON) == HIGH && digitalRead(DOWN_BUTTON) == HIGH)
  {
    delay(100);
  }
  gameIsRunning = true;

  CPU_SCORE = PLAYER_SCORE = 0;

  unsigned long start = millis();
  display.fillScreen(BLACK);
  drawCourt();
  while (millis() - start < 2000);
  ball_update = millis();
  paddle_update = ball_update;
  gameIsRunning = true;
  resetBall = true;
}

void showScore()
{
  gameIsRunning = false;
  display.fillScreen(BLACK);
  drawCourt();

  display.setCursor(15, 4);
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.print("Score");

  display.setCursor(20, 30);
  display.setTextColor(RED);
  display.setTextSize(3);
  display.print(String(CPU_SCORE));

  display.setCursor(60, 30);
  display.setTextColor(GREEN);
  display.setTextSize(3);
  display.print(String(PLAYER_SCORE));

  delay(2000);
  unsigned long start = millis();

  display.fillScreen(BLACK);
  drawCourt();
  while (millis() - start < 2000);
  ball_update = millis();
  paddle_update = ball_update;
  gameIsRunning = true;
  resetBall = true;
}


