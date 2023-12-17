#include <ESP8266WiFi.h>

const char *ssid = "Vũ Đức02";
const char *password = "0987519778";

WiFiServer server(80);

int outputPin1 = 2;  // Example output pin 1
int outputPin2 = 3;  // Example output pin 2
int outputPin3 = 4;  // Example output pin 3
int outputPin4 = 5;  // Example output pin 4
int outputPin5 = 6;  // Example output pin 5
int outputPin6 = 7;  // Example output pin 6

void setup() {
  Serial.begin(115200);
  delay(10);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  // Set up the server
  server.begin();

  // Set output pins as OUTPUT
  pinMode(outputPin1, OUTPUT);
  pinMode(outputPin2, OUTPUT);
  pinMode(outputPin3, OUTPUT);
  pinMode(outputPin4, OUTPUT);
  pinMode(outputPin5, OUTPUT);
  pinMode(outputPin6, OUTPUT);
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c); // Forward the received data to the Serial port

        // Control output pins based on received data
        switch (c) {
          case '1':
            digitalWrite(outputPin1, HIGH);
            break;
          case '2':
            digitalWrite(outputPin2, HIGH);
            break;
          case '3':
            digitalWrite(outputPin3, HIGH);
            break;
          case '4':
            digitalWrite(outputPin4, HIGH);
            break;
          case '5':
            digitalWrite(outputPin5, HIGH);
            break;
          case '6':
            digitalWrite(outputPin6, HIGH);
            break;
          default:
            // Handle other cases or no action
            break;
        }
      }
    }
    client.stop();

    // After processing the data, reset the output pins
    digitalWrite(outputPin1, LOW);
    digitalWrite(outputPin2, LOW);
    digitalWrite(outputPin3, LOW);
    digitalWrite(outputPin4, LOW);
    digitalWrite(outputPin5, LOW);
    digitalWrite(outputPin6, LOW);
  }

  // Read data from the Serial port
  while (Serial.available()) {
    char serialData = Serial.read();

    // Process the data received from the PC
    if (serialData == '1') {
      // Perform action for finger_count == 1
    } else if (serialData == '2') {
      // Perform action for finger_count == 2
    } else if (serialData == '3') {
      // Perform action for finger_count == 3
    } else if (serialData == '4') {
      // Perform action for finger_count == 4
    } else if (serialData == '5') {
      // Perform action for finger_count == 5
    } else if (serialData == '6') {
      // Perform action for finger_count == 6
    }

    // Reset the output pins after processing the data from Serial
    digitalWrite(outputPin1, LOW);
    digitalWrite(outputPin2, LOW);
    digitalWrite(outputPin3, LOW);
    digitalWrite(outputPin4, LOW);
    digitalWrite(outputPin5, LOW);
    digitalWrite(outputPin6, LOW);
  }
}
