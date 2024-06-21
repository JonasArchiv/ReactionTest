#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD Adress change as needed
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int startButtonPin = 2; // Button that be needed to start
const int stopButtonPin = 3; // Button that the User Press
const int ledPin = 13; // User LED

unsigned long startTime;
unsigned long reactionTime;
bool ledOn = false;
bool timerRunning = false;
bool reactionMeasured = false;

void setup() {
  pinMode(startButtonPin, INPUT_PULLUP);
  pinMode(stopButtonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("ReactionTest");
  lcd.setCursor(0, 1);
  lcd.print("Press Startbutton");
}

void loop() {
  if (digitalRead(startButtonPin) == LOW && !timerRunning) {
    startTest();
  }

  if (digitalRead(stopButtonPin) == LOW && ledOn && !reactionMeasured) {
    stopTest();
  }

  if (timerRunning) {
    updateDisplay();
  }
}

void startTest() {
  // Time in ms how long the difference between she start and the go on of the LED
  // It is a random Time between 5 and 10 seconds
  unsigned long randomDelay = random(5000, 10000);
  delay(randomDelay);

  digitalWrite(ledPin, HIGH);
  ledOn = true;

  startTime = millis();
  timerRunning = true;
  reactionMeasured = false;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Zeit laeuft!");
}

void stopTest() {
  reactionTime = millis() - startTime;
  timerRunning = false;
  ledOn = false;
  reactionMeasured = true;

  digitalWrite(ledPin, LOW);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Reaction Time:");
  lcd.setCursor(0, 1);
  lcd.print(reactionTime);
  lcd.print(" ms");
}

void updateDisplay() {
  lcd.setCursor(0, 1);
  lcd.print(millis() - startTime);
  lcd.print(" ms   ");
}
