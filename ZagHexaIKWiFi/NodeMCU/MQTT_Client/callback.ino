void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  ArduinoSerial.write((char)payload[0]);
  snprintf (msg, 50, "Command Received");
  Serial.println(msg);
  client.publish("OutTopic", msg);
}
