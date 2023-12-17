#include <SoftwareSerial.h>

SoftwareSerial BTSerial(2, 3); // RX, TX pins on Arduino

#define outputPin1 8
#define outputPin2 9
#define outputPin3 10
#define outputPin4 11
#define outputPin5 12
#define outputPin6 13

void setup() {
  BTSerial.begin(38400);

  BTSerial.println("Receiver Arduino is ready");
  pinMode(outputPin1, OUTPUT);
  pinMode(outputPin2, OUTPUT);
  pinMode(outputPin3, OUTPUT);
  pinMode(outputPin4, OUTPUT);
  pinMode(outputPin5, OUTPUT);
  pinMode(outputPin6, OUTPUT);
  // Set pull-down resistors for the output pins
}

void loop() {
  // Turn off all outputs
  // Read data from Bluetooth module
  if (BTSerial.available()) {
    char c = BTSerial.read();
    switch (c) {
      case 'a':
        digitalWrite(outputPin1, HIGH);
        break;
      case 'b':
        digitalWrite(outputPin2, HIGH);
        break;
      case 'c':
        digitalWrite(outputPin3, HIGH);
        break;
      case 'd':
        digitalWrite(outputPin4, HIGH);
        break;
      case 'f':
        digitalWrite(outputPin5, HIGH);
        break;
      case 'g':
        digitalWrite(outputPin6, HIGH);
        break;
    }
  }
  else {
     digitalWrite(outputPin1, LOW);
     digitalWrite(outputPin2, LOW);
     digitalWrite(outputPin3, LOW);
     digitalWrite(outputPin4, LOW);
     digitalWrite(outputPin5, LOW);
     digitalWrite(outputPin6, LOW);
    }
  
}
