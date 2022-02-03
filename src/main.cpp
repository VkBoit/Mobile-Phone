#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(3,2);  // SIM800L tx and rx pins are connected to 3 and 2

void updateSerial() {
  delay(500);
  while (Serial.available()) {
    mySerial.write(Serial.read());  // forwared info from Serial monitor to SIM serial
  }
  while (mySerial.available()) {
    Serial.write(mySerial.read());    //forward software serial to serial port
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  mySerial.begin(9600);

  Serial.println("Initializing...");
  delay(1000);
  mySerial.println("AT");
  updateSerial();
  mySerial.println("AT+CSQ");     // Signal quality test, from 0-31, 31 is best
  updateSerial();
  mySerial.println("AT+CCID");    // read SIM info to confirm if it's plugged in
  updateSerial();
  mySerial.println("AT+CREG?");  // check whether SIM is registered
  updateSerial();
}

void loop() {
  // put your main code here, to run repeatedly:
  updateSerial();
}