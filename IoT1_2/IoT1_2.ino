#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <NTPClient.h>
// change next line to use with another board/shield
//#include <ESP32WiFi.h>
#include <WiFi.h> // for WiFi shield
//#include <WiFi101.h> // for WiFi 101 shield or MKR1000
#include <WiFiUdp.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define NUMFLAKES     10 // Number of snowflakes in the animation example

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16
#define interruptPin  25


const char *ssid     = "KIK";
const char *password = "12345678";
int flag = 0;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

String formattedDate;
String IP;
String timeStamp;
//Month names
String months[12]={"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

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

void setup() {
  Serial.begin(115200);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin),switching, RISING);  
  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }
  Serial.println("WiFi Connected");
//  IP = WiFi.localIP()
  timeClient.begin();
  timeClient.setTimeOffset(25200);

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

  // Show the display buffer on the screen. You MUST call display() after
  // drawing commands to make them visible on screen!
  display.display();
  delay(2000);
  display.invertDisplay(true);
  delay(1000);
  display.invertDisplay(false);
  delay(1000);
}

void switching(){
  if(flag==0){
    flag = 1;
  }
  else{
    flag  =0;
  }
}
void loop() {
  timeClient.update();
  formattedDate = timeClient.getFormattedTime();
//  Serial.println("Hour:");
  Serial.println(formattedDate);    
  time_t epochTime = timeClient.getEpochTime();  
  
  //Get a time structure
  struct tm *ptm = gmtime ((time_t *)&epochTime); 
  
  int monthDay = ptm->tm_mday;
  int currentMonth = ptm->tm_mon+1;
  String currentMonthName = months[currentMonth-1];
  int currentYear = ptm->tm_year+1900;


  //Print complete date:
  String currentDate = String(monthDay) + "/" + String(currentMonthName) +"/"+ String(currentYear);
  Serial.print("Current date: ");
  Serial.println(currentDate);

//  text(formattedDate,currentDate);
//  Serial.println("");
//  text(formattedDate, currentDate);
//  display.invertDisplay(true);
  if(flag == 0){ 
    text2();
  }
  if(flag == 1){
    text(formattedDate,currentDate);  
  }
//  delay(100);
  
}


void text(String formattedDate,String currentDate) {
  display.clearDisplay();
  display.setTextSize(1); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 22);
  display.print(F("Time is "));
  display.println(formattedDate); 
  display.setCursor(0, 32);
  display.print(F("Date "));
  display.println(currentDate);  
  display.setCursor(45, 42);
  display.println(F("table 7"));

  display.display();      // Show initial text
//  delay(1000);

 
}

void text2(void) {
  display.clearDisplay();

  display.setTextSize(1); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(36, 22);
  display.println(F("My IP is"));
  display.setCursor(25, 32);
//  display.println(F());
  display.println(WiFi.localIP());
  display.setCursor(45, 42);
  display.println(F("table 7"));
  display.display();      // Show initial text
//  delay(1000);
 
}
