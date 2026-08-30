int pirPin = 2;
int ledPin = 3;

int val = 0;
int pirState = LOW;

// Keep LED on for 7 seconds after motion stops
unsigned long lastMotionTime = 0;
const unsigned long lightDuration = 3000; // 4 seconds

void setup() {
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  val = digitalRead(pirPin);

  if (val == HIGH) {
    digitalWrite(ledPin, HIGH);
    lastMotionTime = millis();  // Reset timer whenever motion is detected

    if (pirState == LOW) {
      Serial.println("Motion detected!");
      pirState = HIGH;
    }

  } else {
    // Keep LED on for 7 seconds after last motion
    if (millis() - lastMotionTime < lightDuration) {
      digitalWrite(ledPin, HIGH);
    } else {
      digitalWrite(ledPin, LOW);

      if (pirState == HIGH) {
        Serial.println("Motion ended!");
        pirState = LOW;
      }
    }
  }
}
