#include <Stepper.h>

// Stepper setup (example pins)
const int stepsPerRevolution = 2048;
Stepper stepperMotor(stepsPerRevolution, 8, 10, 9, 11);

const int buttonPin = 2;
int buzzpin = 5;
bool buttonPressed = false; // Tracks the *edge* of a press

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
  stepperMotor.setSpeed(10);
}

// A small debounce technique
unsigned long lastPressTime = 0;
const unsigned long debounceDelay = 50;  // 50ms

void loop() {
  // ------------------
  // 1) Check button in a non-blocking way
  // ------------------
  bool buttonState = (digitalRead(buttonPin) == LOW); // LOW = pressed, due to INPUT_PULLUP
  unsigned long currentTime = millis();
  
  if (buttonState && !buttonPressed && (currentTime - lastPressTime > debounceDelay)) {
    // Button was *just* pressed
    buttonPressed = true;
    lastPressTime = currentTime;
    
    // Send a message to Python immediately
    Serial.println("P");
    
    // (Don't block here; just note that we sent it.)
    
  } else if (!buttonState && buttonPressed) {
    // Button was just released
    buttonPressed = false;
    // We can do something else upon release if we want.
  }
  
  // ------------------
  // 2) Always check if Python sent a command
  // ------------------
  // Use a *while* loop to read everything in the buffer
  while (Serial.available() > 0) {
    // Read a line from Serial
    String command = Serial.readStringUntil('\n');
    
    if (command == "O") {
      // "Open" command from Python
      rotateMotor();
    } else if (command == "R") {
      // "Retry" or "error" command
      //Serial.println("R");
    }

    else if (command == "F"){
      tone(buzzpin, 1000);
      delay(500);
      noTone(buzzpin);
    }
  }

  // ... normal loop continues without blocking ...
}

void rotateMotor() {
  // Rotate forward one revolution
  
  stepperMotor.step(stepsPerRevolution/4);
  delay(5000);
  stepperMotor.step(-stepsPerRevolution/4);
}


