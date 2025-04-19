#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 (or 0x3F depending on your module) and size 16x2
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Ultrasonic sensor pins
const int trigPin = 9;
const int echoPin = 10;
const int ledPin = 7;
const int buzzerPin = 8;

long duration;
int distance;

void setup() {
  // Initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Blind Spot Detector");

  // Ultrasonic sensor setup
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // LED and Buzzer setup
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  delay(2000);
  lcd.clear();
}

void loop() {
  // Trigger the ultrasonic pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echo time
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  // Display distance on LCD
  lcd.setCursor(0, 0);
  lcd.print("Distance: ");
  lcd.print(distance);
  lcd.print(" cm    ");

  // Condition 1: High-Pitched Rapid Beep (distance ≤ 20 cm)
  if (distance > 0 && distance <= 20) {
    digitalWrite(ledPin, HIGH);
    tone(buzzerPin, 6000);  // High frequency
      delay(100);               // Short beep duration
    noTone(buzzerPin);      
      delay(100);               // Short pause
    lcd.setCursor(0, 1);
    lcd.print("Danger! Too Close");
  } 
  // Condition 2: Slow Beep (distance > 20 cm and ≤ 30 cm)
  else if (distance > 20 && distance <= 30) {
    digitalWrite(ledPin, HIGH);
    tone(buzzerPin, 3000);  // Medium frequency
    delay(200);             // Longer beep duration
    noTone(buzzerPin);
    delay(200);             // Longer pause
    lcd.setCursor(0, 1);
    lcd.print("Object Nearby   ");
  } 
  // No Object Detected
  else {
    digitalWrite(ledPin, LOW);
    noTone(buzzerPin);
    lcd.setCursor(0, 1);
    lcd.print("Clear           ");
  }

  delay(100);
}
