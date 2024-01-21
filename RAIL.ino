#include <LiquidCrystal.h>

#define trigPin PA9
#define echoPin PA10
#define motorPin1 PB8
#define motorPin2 PB9
#define enablePinA PB0
#define enablePinB PB1

const int rs = PA0, en = PA1, d4 = PA2, d5 = PA3, d6 = PA4, d7 = PA5; //STM32 Pins to which LCD is connected
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); //Initialize the LCD

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(enablePinA, OUTPUT);
  pinMode(enablePinB, OUTPUT);
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("Robot Starting");
}

void loop() {
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  Serial.print(distance);
  Serial.println(" cm");
  if(distance > 10) { // stop the robot if distance is greater than 30 cm
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);
    analogWrite(enablePinA, 0);
    analogWrite(enablePinB, 0);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("CRACK DETECTED");
    lcd.setCursor(0, 1);
    lcd.print("Robot Stopped");
  } else { // move the robot if distance is less than or equal to 30 cm
    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, HIGH);
    analogWrite(enablePinA, 255);
    analogWrite(enablePinB, 255);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Distance:");
    lcd.print(distance);
    lcd.print("cm");
  }
  delay(500);
}
