/*
 * Sends UDP packets to a server running on the kindle. Protocol is
 * dead simple: 
 *  "f" <- forward
 *  "b" <- backward
 *  
 *  For v1, will need the setup AP mode as in this link:https://github.com/chriscook8/esp-arduino-apboot/blob/master/ESP-wifiboot.ino
*/
 
#include <EEPROM.h>
#include <WiFiClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <WiFiManager.h>

const int udp_server_port = 8000;
IPAddress udp_server_ip(192, 168, 86, 111);

const int fPin = 13;
const int bPin = 4;
const int ledPin =  5;

WiFiUDP Udp;
unsigned long lastMillis = 0;

void setup() {
  Serial.begin(115200);
  delay(10);

  WiFiManager wifi;
  wifi.autoConnect("AutoConnectAP");
  
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  pinMode(ledPin, OUTPUT);
  pinMode(fPin, INPUT);
  pinMode(bPin, INPUT);
}

void sendUDPMesg(char msg) {
  unsigned long curr = millis();
  if ((curr - lastMillis) > 750) {
    Serial.print("Sending UDP packet: ");
    Serial.print(msg);
    Serial.print("\n");
    Udp.beginPacket(udp_server_ip, udp_server_port);
    Udp.write(msg);
    Udp.endPacket();
    lastMillis = curr;
  } else {
    Serial.print("Squashing keypress: ");
    Serial.print(msg);
    Serial.print("\n");
  }
}

void loop() {
  delay(100);
  
  int fwdButtonState = digitalRead(fPin);
  int backButtonState = digitalRead(bPin);
  
  int buttonState = fwdButtonState || backButtonState;

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
    digitalWrite(ledPin, HIGH);
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
  }  
  yield();

  if (1 == fwdButtonState) {
    sendUDPMesg('f');
  }
  
  if (1 == backButtonState) {
    sendUDPMesg('b');
  }
}

