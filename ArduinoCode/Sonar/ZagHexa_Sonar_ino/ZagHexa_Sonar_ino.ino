#include <Servo.h>

// Defines Tirg and Echo pins of the Ultrasonic
#define trigPin 4
#define echoPin 5
#define pirSensor 7  //set PIR pin

// Variables for the duration and the distance
long duration;
int distance;
Servo myServo; // Creates a servo object for controlling the servo motor

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(pirSensor, INPUT);
  Serial.begin(9600);
  myServo.attach(12); // Defines on which pin is the servo motor attached
}
void loop() {
 int sensorValue = digitalRead(pirSensor);
  // rotates the servo motor from 0 to 180 degrees
  for(int i=0;i<=180;i++){  
   if (sensorValue == 1) {
    Serial.print(1);
    Serial.print("-");
  }
   else { 
    Serial.print(2);
    Serial.print("-");
    }
  delay(30);
  myServo.write(i);
  delay(30);
  distance = calculateDistance(); // Calculating the distance by the ultrasonic for each degree.
  
  Serial.print(i); // Sends the current degree into the Serial Port
  Serial.print(","); // Sending this character will help me in indexing
  Serial.print(distance); // Sends the distance value into the Serial Port
  Serial.print("."); //  Sending this character will help me in indexing
  
  }
  // Repeats the previous lines from 180 to 0 degrees
  for(int i=180;i>0;i--){  
    if (sensorValue == 1) {
    Serial.print(0);
    Serial.print("-");
  }
   else { 
    Serial.print(1);
    Serial.print("-");
    }
  delay(30);
  myServo.write(i);
  delay(30);
  distance = calculateDistance();
  Serial.print(i);
  Serial.print(",");
  Serial.print(distance);
  Serial.print(".");
  }
}

// Function for calculating the distance by the Ultrasonic
int calculateDistance(){ 
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(10);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  distance= duration*0.034/2;
  return distance;
}
