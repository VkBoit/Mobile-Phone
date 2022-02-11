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
  delay(2000);
  mySerial.println("AT+CMGF=1");     // Configure Text Mode
  //updateSerial();
  //mySerial.println("AT+CMGS=\"+2547222000000\"");    // Number to be texted
  //updateSerial();
  //mySerial.print("Yoo, I exist, I am sentient!");  // check whether SIM is registered
  //updateSerial();
  //mySerial.write(26);
  updateSerial();
  mySerial.println("AT+CNMI=1,2,0,0,0");   // DECIDES HOW NEWLY RECEIVED sms MESSAGES SHOULD BE HANDLED
  updateSerial();
}

void loop() {
  // put your main code here, to run repeatedly:
  updateSerial();
}
