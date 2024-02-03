const int pirPin = 2; // PIR sensor pin
const int ledPin = 11; // LED pin for motion detection
const int trigPin = 3; // Ultrasonic sensor trigger pin
const int echoPin = 4; // Ultrasonic sensor echo pin
const int newLedPin = 12; // New LED pin for distance measurement

volatile bool motionDetected = false;

void setup() {
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(newLedPin, OUTPUT);
  
  Serial.begin(9600);

  attachInterrupt(digitalPinToInterrupt(pirPin), motionDetectedISR, CHANGE);
}

void loop() {
  // Ultrasonic sensor measurement
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1; // Distance in centimeters
  
  // Check if distance is less than 100cm
  if (distance < 100) {
    digitalWrite(newLedPin, HIGH); // Turn on new LED
  } else {
    digitalWrite(newLedPin, LOW); // Turn off new LED
  }
}

void motionDetectedISR() {
  if (digitalRead(pirPin) == HIGH) {
    Serial.println("Motion Detected!");
    digitalWrite(ledPin, HIGH);
  } else {
    Serial.println("Motion Ended!");
    digitalWrite(ledPin, LOW);
  }
}
