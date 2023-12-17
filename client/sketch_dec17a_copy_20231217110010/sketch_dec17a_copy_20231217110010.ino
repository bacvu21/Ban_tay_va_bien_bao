#define outputPin1 4

void setup() {
  Serial.begin(9600); // Serial monitor
  pinMode(outputPin1, OUTPUT);
  Serial.println("Arduino is ready");
}

void loop() {
  // Read data from the Serial Monitor
  if (Serial.available()) {
    char data = Serial.read();
    Serial.write(data); // Send data to Serial Monitor

    // Control output based on received data
    switch (data) {
      case 'a':
        digitalWrite(outputPin1, HIGH);
        break;
      case 'b':
        digitalWrite(outputPin1, LOW);
        break;
    }
  }
}
