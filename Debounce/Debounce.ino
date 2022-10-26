

// constants won't change. They're used here to set pin numbers:
const int buttonPin = 25;    // the number of the pushbutton pin
const int ledPin = 5;      // the number of the LED pin


int ledState = 1;         // the current state of the output pin
//int buttonState = HIGH;             // the current reading from the input pin
int lastButtonState = HIGH;   // the previous reading from the input pin



unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

void setup() {  
  
  Serial.begin(115200);
  pinMode(25,INPUT_PULLUP);
  pinMode(5, OUTPUT);
  
  // set initial LED state
//  digitalWrite(ledPin, ledState);
}

void loop(){
  
  int reading = digitalRead(25);
  
 
//  if (reading != lastButtonState)
   if (reading == 0){
    // บอกว่า state ใหม่ ไม่เท่ากับ state เก่า แปลว่ามีกดปุ่ม
    // reset the debouncing timer
    lastDebounceTime = millis();  // เวลาตอนกดปุ่มเป๊ะ ๆ 
  } 

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // ให้รอจนมากกว่า debounceDelay ค่อยเปิด/ปิด หลอด LED
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading ==1 && lastButtonState==0) {   
        if(ledState == 0 ){
           digitalWrite(ledPin,HIGH);
           ledState = 1;
        }      
        else{
           digitalWrite(ledPin,LOW);
           ledState = 0;
           }
      }
    }
  

  // set the LED:
//  digitalWrite(ledPin,ledState);

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;
}
