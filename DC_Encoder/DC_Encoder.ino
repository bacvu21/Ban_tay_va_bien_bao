#define runEvery(t) for (unsigned long _lasttime;(uint16_t)((uint16_t)millis() - _lasttime) >= (t);_lasttime += (t))
#include <analogWrite.h>
#include <ESP32Servo.h>
#include "BluetoothSerial.h"
#include "esp_bt_device.h"
#define ena 14
#define in1 26
#define in2 25
#define in3 33
#define in4 32
#define enb 27
#define TRIG_PIN 16
#define ECHO_PIN 17

const byte Encoder1 = 35;  // Motor Phai in1 in2
const byte Encoder2 = 34;  // Motor Trai in3 in4

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

/*void printDeviceAddress() {
 
  const uint8_t* point = esp_bt_dev_get_address();
 
  for (int i = 0; i < 6; i++) {
 
    char str[3];
 
    sprintf(str, "%02X", (int)point[i]);
    Serial.print(str);
 
    if (i < 5){
      Serial.print(":");
    }
 
  }
}*/

int Khoangcach()
{
  float duration, distanceCm;
   
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  duration = pulseIn(ECHO_PIN, HIGH);

  distanceCm = duration / 29.1 / 2;
  
  return (int)distanceCm;
}
volatile unsigned int counter1;
volatile unsigned int counter2;
void ISR_count1()  
{
  counter1++; // Xung
} 
 
// Motor B pulse count ISR
void ISR_count2()  
{
  counter2++;
}
void st()
{
  digitalWrite (in1, LOW); 
  digitalWrite (in2, LOW); 
  digitalWrite (in3, LOW); 
  digitalWrite (in4, LOW);
}

void Dithang(int steps, int mspeed) 
{
   counter1 = 0;  //  reset counter A to zero
   counter2 = 0;  //  reset counter B to zero
   
   // Set Motor R forward
   digitalWrite(in2, HIGH);
   digitalWrite(in1, LOW);
 
   // Set Motor L forward
   digitalWrite(in4, HIGH);
   digitalWrite(in3, LOW);
   
   // Go forward until step value is reached
   while (steps > counter1 || steps > counter2) {
   
    if (steps > counter1) {
    analogWrite(ena, mspeed);
    } else {
    analogWrite(ena, 0);
    }
    if (steps > counter2) {
    analogWrite(enb, mspeed);
    } else {
    analogWrite(enb, 0);
    }
   }
  analogWrite(ena, 0);
  analogWrite(enb, 0);
  counter1 = 0;  //  reset counter A to zero
  counter2 = 0;  //  reset counter B to zero 
}

void Dilui(int steps, int mspeed) 
{
   counter1 = 0;  //  reset counter A to zero
   counter2 = 0;  //  reset counter B to zero
   
   // Set Motor R forward
   digitalWrite(in1, HIGH);
   digitalWrite(in2, LOW);
 
   // Set Motor L forward
   digitalWrite(in3, HIGH);
   digitalWrite(in4, LOW);
   
   // Go forward until step value is reached
   while (steps > counter1 || steps > counter2) {
   
    if (steps > counter1) {
    analogWrite(ena, mspeed);
    } else {
    analogWrite(ena, 0);
    }
    if (steps > counter2) {
    analogWrite(enb, mspeed);
    } else {
    analogWrite(enb, 0);
    }
   }
  counter1 = 0;  //  reset counter A to zero
  counter2 = 0;  //  reset counter B to zero 
}

void Quaydau(int steps, int mspeed) 
{
   counter1 = 0;  //  reset counter A to zero
   counter2 = 0;  //  reset counter B to zero
   
   // Set Motor R forward
   digitalWrite(in2, HIGH);
   digitalWrite(in1, LOW);
 
   // Set Motor L forward
   digitalWrite(in3, HIGH);
   digitalWrite(in4, LOW);
   analogWrite(enb, 0);
   // Go forward until step value is reached
   while (steps > counter1) {
   
    if (steps > counter1) {
    analogWrite(ena, mspeed);
    } else {
    analogWrite(ena, 0);
    }
    /*if (steps > counter2) {
    analogWrite(enb, mspeed);
    } else {
    analogWrite(enb, 0);
    }*/
   }
  analogWrite(ena, 0);
  analogWrite(enb, 0);
  counter1 = 0;  //  reset counter A to zero
  counter2 = 0;  //  reset counter B to zero 
}

void Retrai(int steps, int mspeed)
{
   counter1 = 0;  //  reset counter A to zero
   counter2 = 0;  //  reset counter B to zero
   
   // Set Motor R forward
   digitalWrite(in2, HIGH);
   digitalWrite(in1, LOW);
 
   // Set Motor L forward
     digitalWrite(in4, LOW);
     digitalWrite(in3, LOW);
   
   // Go forward until step value is reached
   while (steps > counter1) {
   
    if (steps > counter1) {
    analogWrite(ena, mspeed);
    } else {
    analogWrite(ena, 0);
    }
   }
    analogWrite(ena, 0);
    analogWrite(enb, 0);
  counter1 = 0;  //  reset counter A to zero
  counter2 = 0;  //  reset counter B to zero 
}

void Rephai(int steps, int mspeed) 
{
   counter1 = 0;  //  reset counter A to zero
   counter2 = 0;  //  reset counter B to zero
   
   // Set Motor R forward
   digitalWrite(in2, LOW);
   digitalWrite(in1, LOW);
  
   // Set Motor L forward
   digitalWrite(in4, HIGH);
   digitalWrite(in3, LOW);
   
   // Go forward until step value is reached
   while (steps > counter2) {
    if (steps > counter2) {
    analogWrite(enb, mspeed);
    } else {
    analogWrite(enb, 0);
    }
   }
   analogWrite(ena, 0);
   analogWrite(enb, 0);
  counter1 = 0;  //  reset counter A to zero
  counter2 = 0;  //  reset counter B to zero
}

void Tranhvat1(int steps, int mspeed)
{
   counter1 = 0;  //  reset counter A to zero
   counter2 = 0;  //  reset counter B to zero
   
   // Set Motor R forward
   digitalWrite(in2, HIGH);
   digitalWrite(in1, LOW);
 
   // Set Motor L forward
   digitalWrite(in4, HIGH);
   digitalWrite(in3, LOW);
   
   // Go forward until step value is reached
   while (steps > counter1) {
   
    if (steps > counter1) {
    analogWrite(ena, mspeed);
    analogWrite(enb, mspeed-40);
    } else {
    analogWrite(ena, 0);
    analogWrite(enb, 0);
    }
   }
    analogWrite(ena, 0);
    analogWrite(enb, 0);
  counter1 = 0;  //  reset counter A to zero
  counter2 = 0;  //  reset counter B to zero 
}

void Tranhvat2(int steps, int mspeed)
{
   counter1 = 0;  //  reset counter A to zero
   counter2 = 0;  //  reset counter B to zero
   
   // Set Motor R forward
   digitalWrite(in2, HIGH);
   digitalWrite(in1, LOW);
 
   // Set Motor L forward
   digitalWrite(in4, HIGH);
   digitalWrite(in3, LOW);
   
   // Go forward until step value is reached
   while (steps > counter2) {
   
    if (steps > counter2) {
    analogWrite(ena, mspeed-40);
    analogWrite(enb, mspeed);
    }
    else {
    analogWrite(ena, 0);
    analogWrite(enb, 0);
    }
   }
   analogWrite(ena, 0);
   analogWrite(enb, 0);
  counter1 = 0;  //  reset counter A to zero
  counter2 = 0;  //  reset counter B to zero 
}

void setup() 

{
  Serial.begin(115200);
  pinMode (ena, OUTPUT);
  pinMode (in1, OUTPUT);
  pinMode (in2, OUTPUT);
  pinMode (in3, OUTPUT);
  pinMode (in4, OUTPUT);
  pinMode (enb, OUTPUT);
  SerialBT.begin("Xe_TranDat"); //Bluetooth device name

  pinMode (Encoder1, INPUT);
  pinMode (Encoder2, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt (Encoder1), ISR_count1, RISING);  // Increase counter A when speed sensor pin goes High
  attachInterrupt(digitalPinToInterrupt (Encoder2), ISR_count2, RISING);  // Increase counter B when speed sensor pin goes High
  counter1=0;
  counter2=0;
}

int datafromUser, data_python;
int kt_data = 0;
int kc;
void loop() 
{
  if (kt_data == 0)
  {
     if(SerialBT.available() > 0)
   {
     data_python=SerialBT.read();
     Serial.println(data_python);
     kt_data = data_python;
   }
  }
  
   runEvery(100)
   {
   if(kt_data == '9')
   {
   datafromUser = 0;
   if(SerialBT.available() > 0)
   {
     datafromUser=SerialBT.read();
   }
   if(datafromUser == '1')
      {
        Retrai(18, 100);
        delay(500);
        }
   else if (datafromUser == '2')
      { 
        Rephai(17, 100);
        delay(500);
        }
   else if(datafromUser == '3')
      {
        Quaydau(38, 100);
        delay(500);
        }
   else if(datafromUser == '8')
   {
      Tranhvat1(40, 120);
      delay(500);
      Tranhvat2(40, 120);
      delay(1000);
   }

   else if(datafromUser == '5')
      {
        Retrai(10,100);
        delay(500);
        Dithang(20,80);
        delay(500);
        Rephai(10,100);
        Dithang(100, 65);
      }
    else if(datafromUser == '6')
      {
        st();
        delay(5000);
      }
   
   else
      {
        kc = Khoangcach();
        if(kc <= 20)
        {
          SerialBT.write((byte)'1');
          st();
          delay(500);
        }
        else
        {
        Dithang(6, 80);
        }

      }
   }
   
  }
}
