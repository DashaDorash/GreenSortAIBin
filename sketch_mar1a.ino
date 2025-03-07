#include <Stepper.h>


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


unsigned long lastPressTime = 0;
const unsigned long debounceDelay = 50;  // 50ms

void loop() {

  bool buttonState = (digitalRead(buttonPin) == LOW); // LOW = pressed, due to INPUT_PULLUP
  unsigned long currentTime = millis();
  
  if (buttonState && !buttonPressed && (currentTime - lastPressTime > debounceDelay)) {

    buttonPressed = true;
    lastPressTime = currentTime;
    

    Serial.println("P");
    

    
  } else if (!buttonState && buttonPressed) {

    buttonPressed = false;

  }
  
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

}

void rotateMotor() {
  // Rotate forward one revolution
  
  stepperMotor.step(stepsPerRevolution/4);
  delay(5000);
  stepperMotor.step(-stepsPerRevolution/4);
}


