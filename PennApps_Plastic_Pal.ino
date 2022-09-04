
#include "Adafruit_seesaw.h"

Adafruit_seesaw ss;

// set up led pins
int pumpPin = 2;
int serConnectPin = 3;
int pumpLEDPin = 4;
int moistLEDPin = 5;
int x;
int period = 5000;
unsigned long time_now = 0;

void setup() {
  // set up led pins
  pinMode(pumpPin, OUTPUT);
  pinMode(serConnectPin, OUTPUT);
  pinMode(pumpLEDPin, OUTPUT);
  pinMode(moistLEDPin, OUTPUT);
  Serial.begin(115200);
  Serial.setTimeout(1);

  // change to ind LEDs
  if (!ss.begin(0x36)) {
    Serial.println("ERROR! seesaw not found");
    while(1) delay(1);
  }
}

void loop() {
  time_now = millis();
  // read weather to turn on the pump
  x = Serial.readString().toInt();
  
  while (!Serial.available() && ((millis() < time_now + period) || x == 1)) {
    // if there is no connetion dont light up the LED
    digitalWrite(serConnectPin, LOW);
  }
  digitalWrite(serConnectPin, HIGH);
  
  // measeure the temp and moisture from sensor
  float tempC = ss.getTemp();
  uint16_t capread = ss.touchRead(0);
  // indicate the moistor
  int ledBrightness = map(capread, 700, 1100, 0, 255);
  analogWrite(moistLEDPin, ledBrightness);
  Serial.println(capread); // print the wetness for python to read
  // Serial.print(" ");
  // Serial.println(tempC); // print the temp for python to read
  
  
  // if it sends 1 over serial turn LED on
  if (x == 1) {
    digitalWrite(pumpLEDPin, HIGH);
    digitalWrite(pumpPin, HIGH);
  } else {
    digitalWrite(pumpLEDPin, LOW);
    digitalWrite(pumpPin, LOW);
  }
}
