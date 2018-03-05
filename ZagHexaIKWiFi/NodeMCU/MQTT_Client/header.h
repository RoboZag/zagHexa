#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <SoftwareSerial.h>

// Update these with values suitable for your network.

WiFiClient espClient;
PubSubClient client(espClient);
SoftwareSerial ArduinoSerial(13,15);

char* ssid;
char* password;
char* mqtt_server;  
char msg[50];
int value = 0;
