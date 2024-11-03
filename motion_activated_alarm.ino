// Define pins
const int pirPin = 2;     // PIR sensor output pin
const int buzzerPin = 8;  // Buzzer pin

void setup() {
  pinMode(pirPin, INPUT);      // Set PIR sensor as input
  pinMode(buzzerPin, OUTPUT);  // Set buzzer as output

  Serial.begin(9600);          // Initialize Serial Monitor
}

void loop() {
  int motionState = digitalRead(pirPin);  // Read PIR sensor state

  if (motionState == HIGH) {              // If motion is detected
    digitalWrite(buzzerPin, HIGH);        // Turn on the buzzer
    Serial.print("Motion detected at: ");
    Serial.println(millis() / 1000);      // Log timestamp in seconds since start
    delay(1000);                          // Buzzer delay for 1 second
  } else {
    digitalWrite(buzzerPin, LOW);         // Turn off the buzzer if no motion
  }
}