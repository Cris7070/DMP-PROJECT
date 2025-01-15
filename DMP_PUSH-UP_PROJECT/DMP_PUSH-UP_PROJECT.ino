#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const int proximityPin = A0; // Potentiometer 
const int buttonPin = 2;   

const int holdThreshold = 2000; 
bool buttonHeld = false;       
unsigned long pressStartTime = 0;
unsigned long lastPressTime = 0;
int pressCount = 0;

int pushupCount = 0;
bool counting = false;

int lastValue = 0;  // For smoothing
const int upperThreshold = 800; 
const int lowerThreshold = 200; 
bool atBottom = false; 

void setup() {
  pinMode(proximityPin, INPUT);
  pinMode(buttonPin, INPUT_PULLUP); // Button with pull-up resistor

 
  if (!display.begin(SSD1306_WHITE, 0x3C)) { 
    while (true); 
  }

  
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Push-up Counter");
  display.display();
  delay(1000);
}

void loop() {
  // Smooth the proximity sensor readings
  int rawValue = analogRead(proximityPin);
  int smoothedValue = (rawValue + lastValue) / 2;
  lastValue = smoothedValue;

  // Handle push-up detection
  if (counting) {
    if (smoothedValue > upperThreshold && !atBottom) {
      // Reached bottom of the push-up
      atBottom = true;
    } else if (smoothedValue < lowerThreshold && atBottom) {
      // Reached top of the push-up
      pushupCount++;
      atBottom = false;
      updateDisplay();
    }
  }

  // Handle button presses
  int buttonState = digitalRead(buttonPin);
  handleButton(buttonState);
}

void handleButton(int state) {
  if (state == LOW) { // Button is pressed
    if (!buttonHeld) {
      buttonHeld = true;               
      pressStartTime = millis();      
      if (millis() - lastPressTime < 500) { // Check for double press
        pressCount++;
      } else {
        pressCount = 1; 
      }
      lastPressTime = millis();
    } else if (millis() - pressStartTime > holdThreshold) {
      handleHoldAction();
    }
  } else { 
    if (buttonHeld) {
      buttonHeld = false;             
      unsigned long holdTime = millis() - pressStartTime;
      if (holdTime < holdThreshold) {  
        if (pressCount == 1) {
          handleShortPressAction();    
        } else if (pressCount == 2) {
          handleDoublePressAction();  
        }
      }
    }
  }
}

void handleShortPressAction() {
  counting = !counting; 
  display.clearDisplay();
  display.setCursor(0, 0);
  if (counting) {
    display.println("Counting Started");
  } else {
    display.println("Counting Stopped");
  }
  display.display();
  delay(200); 
}

void handleDoublePressAction() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Counter Reset");
  display.display();

  pushupCount = 0; 
  delay(200); 
}

void handleHoldAction() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Release the button to continue.");
  display.display();
}

void updateDisplay() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Push-ups: ");
  display.println(pushupCount);
  display.display();
}