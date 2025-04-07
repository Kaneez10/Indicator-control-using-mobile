char receivedChar;
int ledPin1 = 8;
int ledPin2 = 9;

bool isBlinking1 = false;
bool isBlinking2 = false;

unsigned long previousMillis = 0;
const long interval = 500;

bool ledState1 = false;
bool ledState2 = false;

void setup() {
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  unsigned long currentMillis = millis();

  // Read serial input
  if (Serial.available()) {
    receivedChar = Serial.read();

    if (receivedChar == '1') {
      // Toggle LED1 blinking, and turn off LED2
      isBlinking1 = !isBlinking1;
      isBlinking2 = false;
      digitalWrite(ledPin2, LOW); // Make sure LED2 is off
      ledState2 = false;

      if (!isBlinking1) {
        digitalWrite(ledPin1, LOW); // Turn off LED1 if stopping
        ledState1 = false;
      }

      delay(200); // debounce
    }

    if (receivedChar == '2') {
      // Toggle LED2 blinking, and turn off LED1
      isBlinking2 = !isBlinking2;
      isBlinking1 = false;
      digitalWrite(ledPin1, LOW); // Make sure LED1 is off
      ledState1 = false;

      if (!isBlinking2) {
        digitalWrite(ledPin2, LOW); // Turn off LED2 if stopping
        ledState2 = false;
      }

      delay(200); // debounce
    }
  }

  // Blink only the active LED
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    if (isBlinking1) {
      ledState1 = !ledState1;
      digitalWrite(ledPin1, ledState1 ? HIGH : LOW);
    }

    if (isBlinking2) {
      ledState2 = !ledState2;
      digitalWrite(ledPin2, ledState2 ? HIGH : LOW);
    }
  }
}
