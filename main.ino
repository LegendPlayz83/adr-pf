#Code
const int buttonPins[4] = {6, 7, 0, 1};
const int ledPins[4] = {26, 27, 28, 29};

unsigned long pressStart[4] = {0, 0, 0, 0};
bool isPressed[4] = {false, false, false, false};
int ledBrightness[4] = {0, 0, 0, 0};

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  unsigned long now = millis();

  for (int i = 0; i < 4; i++) {
    bool currentPressed = (digitalRead(buttonPins[i]) == LOW);

    if (currentPressed && !isPressed[i]) {
      pressStart[i] = now;
      isPressed[i] = true;
    }

    if (!currentPressed && isPressed[i]) {
      isPressed[i] = false;
    }

    if (isPressed[i]) {
      unsigned long heldTime = now - pressStart[i];
      ledBrightness[i] = constrain(heldTime / 4, 0, 255);  // slower rise
    } else {
      if (ledBrightness[i] > 0) {
        ledBrightness[i] -= 5;  // fade out speed
        if (ledBrightness[i] < 0) ledBrightness[i] = 0;
      }
    }

    analogWrite(ledPins[i], ledBrightness[i]);
  }

  delay(10);  // smooth update
}
