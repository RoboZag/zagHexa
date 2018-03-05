/*
  This code is using a server to handle a MQTT protocol between 
  the user and the Arduino.
  
  It receive the data form user using the Topic ZagHexa then
  send the data to Arduino through Serial interface.

  Responde from the NodeMCU to the user through the Topic
  OutTopic.
*/
#include "header.h"


void setup() {

  configration("ESP", "123456789", "192.168.1.2");
  setup_wifi();
  ArduinoSerial.begin(115200);
  Serial.begin(115200);
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();


}
