// Define constants for pin assignments
const int pirPin = 2;      // PIR sensor pin
const int ledPin = 11;     // LED pin for motion detection
const int trigPin = 3;     // Ultrasonic sensor trigger pin
const int echoPin = 4;     // Ultrasonic sensor echo pin
const int newLedPin = 12;  // New LED pin for distance measurement

volatile bool motionDetected = false; // Flag to indicate motion detection

void setup() {
  // Initialize pin modes
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(newLedPin, OUTPUT);
  
  // Initialize serial communication
  Serial.begin(9600);

  // Attach interrupt to PIR sensor pin for motion detection
  attachInterrupt(digitalPinToInterrupt(pirPin), motionDetectedISR, CHANGE);
}

void loop() {
  // Ultrasonic sensor measurement
  long duration, distance;
  
  // Send a pulse to trigger the ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Measure the duration of the echo pulse
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate distance based on the duration
  distance = (duration / 2) / 29.1; // Distance in centimeters
  
  // Check if distance is less than 100cm
  if (distance < 100) {
    digitalWrite(newLedPin, HIGH); // Turn on new LED if distance is less than 100cm
  } else {
    digitalWrite(newLedPin, LOW);  // Turn off new LED if distance is 100cm or more
  }
}

void motionDetectedISR() {
  // Handle motion detection interrupt
  if (digitalRead(pirPin) == HIGH) {
    // Motion detected
    Serial.println("Motion Detected!");
    digitalWrite(ledPin, HIGH); // Turn on LED
  } else {
    // Motion ended
    Serial.println("Motion Ended!");
    digitalWrite(ledPin, LOW); // Turn off LED
  }
}
