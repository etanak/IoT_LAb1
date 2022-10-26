#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <NTPClient.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
#define OLED_RESET     4 
#define SCREEN_ADDRESS 0x3C 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#define NUMFLAKES     10 
#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16
#define interruptPin  25


static const unsigned char PROGMEM logo_bmp[] =
{ 0b00000000, 0b11000000,
  0b00000001, 0b11000000,
  0b00000001, 0b11000000,
  0b00000011, 0b11100000,
  0b11110011, 0b11100000,
  0b11111110, 0b11111000,
  0b01111110, 0b11111111,
  0b00110011, 0b10011111,
  0b00011111, 0b11111100,
  0b00001101, 0b01110000,
  0b00011011, 0b10100000,
  0b00111111, 0b11100000,
  0b00111111, 0b11110000,
  0b01111100, 0b11110000,
  0b01110000, 0b01110000,
  0b00000000, 0b00110000 };


const int buttonPin1 = 25;
const int buttonPin2 = 26;
const int buttonPin3 = 27;
const int buttonPin4 = 33;
//int state = 0;

byte lastButtonState1;
byte lastButtonState2;
byte lastButtonState3;
byte lastButtonState4;

unsigned long lastTimeButtonStateChanged4 = millis();
unsigned long lastTimeButtonStateChanged3 = millis();
unsigned long lastTimeButtonStateChanged2 = millis();
unsigned long lastTimeButtonStateChanged1 = millis();
unsigned long debounceDuration = 50;

void setup(){
  Serial.begin(115200);
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
  pinMode(buttonPin4, INPUT_PULLUP);
  
//  pinMode(ledPin, OUTPUT);
  lastButtonState1 = digitalRead(buttonPin1);
  lastButtonState2 = digitalRead(buttonPin2);
  lastButtonState3 = digitalRead(buttonPin3);
  lastButtonState4 = digitalRead(buttonPin4);
  
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();

  // Draw a single pixel in white
  display.drawPixel(10, 10, SSD1306_WHITE);
 
  display.display();
  delay(2000);
  display.invertDisplay(true);
  delay(1000);
  display.invertDisplay(false);
  delay(1000);

}

void loop() {
  if (millis() - lastTimeButtonStateChanged1 >= debounceDuration){
    byte buttonState1 = digitalRead(buttonPin1);
    if (buttonState1 != lastButtonState1) {
      lastTimeButtonStateChanged1 = millis();
      lastButtonState1 = buttonState1;
      if (buttonState1 == HIGH) {
        text1();

      }
    } 
  }
   if (millis() - lastTimeButtonStateChanged2 >= debounceDuration){
    byte buttonState2 = digitalRead(buttonPin2);
    if (buttonState2 != lastButtonState2) {
      lastTimeButtonStateChanged2 = millis();
      lastButtonState2 = buttonState2;
      if (buttonState2 == HIGH) {
         text2();

      }
    } 
  }
   if (millis() - lastTimeButtonStateChanged3 >= debounceDuration){
    byte buttonState3 = digitalRead(buttonPin3);
    if (buttonState3 != lastButtonState3) {
      lastTimeButtonStateChanged3 = millis();
      lastButtonState3 = buttonState3;
      if (buttonState3 == HIGH) {
         text3();

      }
    } 
  }
   if (millis() - lastTimeButtonStateChanged4 >= debounceDuration){
    byte buttonState4 = digitalRead(buttonPin4);
    if (buttonState4 != lastButtonState4) {
      lastTimeButtonStateChanged4 = millis();
      lastButtonState4 = buttonState4;
      if (buttonState4 == HIGH) {
         text4();

      }
    } 
  }
}

void text1(void) {
  display.clearDisplay();

  display.setTextSize(1); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(50, 22);
  display.println(F("IoT"));
//  display.setCursor(25, 32);
////  display.println(F());
//  display.println(WiFi.localIP());
  display.setCursor(36, 42);
  display.println(F("2102447"));
  display.display();      // Show initial text
//  delay(1000);
 
}

void text2(void) {
  display.clearDisplay();

  display.setTextSize(1); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(27, 22);
  display.println(F("Electrical CU"));
//  display.setCursor(25, 32);
////  display.println(F());
//  display.println(WiFi.localIP());
//  display.setCursor(45, 42);
//  display.println(F("table 7"));
  display.display();      // Show initial text
//  delay(1000);
 
}

void text3(void) {
  display.clearDisplay();

  display.setTextSize(1); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(36, 22);
  display.println(F("OLED is work"));
//  display.setCursor(25, 32);
////  display.println(F());
//  display.println(WiFi.localIP());
//  display.setCursor(45, 42);
//  display.println(F("table 7"));
  display.display();      // Show initial text
//  delay(1000);
 
}

void text4(void) {
  display.clearDisplay();
  display.setTextSize(1); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(36, 22);
  display.println(F("I love NPT"));
//  display.setCursor(25, 32);
//  display.println(F());
//  display.println(WiFi.localIP());
  display.setCursor(32, 42);
  display.println(F("from table 7"));
  display.display();      // Show initial text
//  delay(1000);
 
}
