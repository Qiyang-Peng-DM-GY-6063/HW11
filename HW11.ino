const int pins[] = {4, 5, 6, 7, 8, 3}; 
const int numPins = 6;

int currentLED = 0;  
unsigned long startTime = 0;
const unsigned long lightInterval = 10000;  
const unsigned long period = 60000;

void setup() {
  Serial.begin(9600); 
  
  for (int i = 0; i < numPins; i++) {
    pinMode(pins[i], OUTPUT);
    analogWrite(pins[i], 0); 
  }
  startTime = millis();
  currentLED = 0;
}

void loop() {
  unsigned long now = millis(); 

  // Restart after the period ends
  if (now - startTime >= period) {
    restart();
    currentLED = 0;
    startTime = now; 
  }

  if (now >= startTime + currentLED * lightInterval) {
    for (int brightness = 0; brightness <= 255; brightness++) {
      analogWrite(pins[currentLED], brightness);
      delay(lightInterval / 256);

      Serial.print("currentLED: ");
      Serial.println(currentLED);
      Serial.print("current pin: ");
      Serial.println(pins[currentLED]);

    }
    currentLED++;                      
  }

}

// Restart the 1-minute clock
void restart() {
  for (int i = 0; i < numPins; i++) {
    analogWrite(pins[i], 0);
  }
}
