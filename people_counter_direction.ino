// Define pins for IR sensors
const int irSensor1 = 2;  // IR sensor at entry side
const int irSensor2 = 3;  // IR sensor at exit side

// Define pins for ultrasonic sensor
const int trigPin = 4;
const int echoPin = 5;

// Define pins for 7-segment display segments
const int segmentPins[] = {6, 7, 8, 9, 10, 11, 12};

int peopleCount = 0;

// Segment encoding for displaying numbers on 7-segment (Common Cathode)
const byte digitSegments[10] = {
  B00111111,  // 0
  B00000110,  // 1
  B01011011,  // 2
  B01001111,  // 3
  B01100110,  // 4
  B01101101,  // 5
  B01111101,  // 6
  B00000111,  // 7
  B01111111,  // 8
  B01101111   // 9
};

void setup() {
  Serial.begin(9600);
  
  pinMode(irSensor1, INPUT);
  pinMode(irSensor2, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Set segment pins as output
  for (int i = 0; i < 7; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }
}

void loop() {
  // Check IR sensors
  int ir1State = digitalRead(irSensor1);
  int ir2State = digitalRead(irSensor2);

  if (ir1State == HIGH && ir2State == LOW) { // Entry detected
    if (confirmDirection()) {
      peopleCount++;
      Serial.println("Person entered.");
      displayCount(peopleCount);
    }
    delay(500); // Debounce delay
  } 
  else if (ir1State == LOW && ir2State == HIGH) { // Exit detected
    if (confirmDirection()) {
      if (peopleCount > 0) peopleCount--;
      Serial.println("Person exited.");
      displayCount(peopleCount);
    }
    delay(500); // Debounce delay
  }
}

// Function to confirm direction using ultrasonic sensor
bool confirmDirection() {
  long duration;
  int distance;

  // Send trigger pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read echo pulse
  duration = pulseIn(echoPin, HIGH);

  // Calculate distance in cm
  distance = duration * 0.034 / 2;

  if (distance < 100) { // Confirm object is within 1 meter
    delay(100); // Wait for object to pass through the doorway
    return true;
  }
  return false;
}

// Function to display count on 7-segment display
void displayCount(int count) {
  int displayDigit = count % 10; // Display only units digit for simplicity

  // Light up the segments based on the digit
  for (int i = 0; i < 7; i++) {
    digitalWrite(segmentPins[i], bitRead(digitSegments[displayDigit], i));
  }
}