int pirPin = 2;     
int ledPin = 3;     
int ldrPin = A0;    // LDR on analog pin

int val = 0;        
int pirState = LOW; 

// Duration string lights stays on
unsigned long lastMotionTime = 0;
unsigned long lightDuration = 2000; // 3 seconds (adjust this)

//int threshold = 100; // Real
bool isDark = false;

// Stops flickering if light is too close to threshold
//int thresholdLow = 90;
//int thresholdHigh = 150;

// Real ^^

// int threshold = 900; // Class Test

// Stops flickering if light is too close to threshold
int thresholdLow = 890;
int thresholdHigh = 950;
// Class Test


void setup() {
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int lightLevel = analogRead(ldrPin); // read LDR
  val = digitalRead(pirPin);

  Serial.print("Light: ");
  Serial.println(lightLevel);

  // Only update ambient light state when LEDs are OFF
if (digitalRead(ledPin) == LOW) {
  if (!isDark && lightLevel < thresholdLow) {
    isDark = true;
  }

  if (isDark && lightLevel > thresholdHigh) {
    isDark = false;
  }
}


  // ONLY run PIR if it's dark
  if (isDark) {

  if (val == HIGH) {
    digitalWrite(ledPin, HIGH);
    lastMotionTime = millis(); // reset timer

    if (pirState == LOW) {
      Serial.println("Motion detected!");
      pirState = HIGH;
    }

  } else {
    // No motion → check if we should still keep lights on
    if (millis() - lastMotionTime < lightDuration) {
      digitalWrite(ledPin, HIGH); // keep lights on
    } else {
      digitalWrite(ledPin, LOW); // turn off after time

      if (pirState == HIGH) {
        Serial.println("Motion ended!");
        pirState = LOW;
      }
    }
  }

} else {
  digitalWrite(ledPin, LOW);
  Serial.println("Too bright, deactivated sensor!");
}
}