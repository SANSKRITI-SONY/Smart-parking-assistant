#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);
const int greenLED = 4;
const int yellowLED = 5;
const int redLED = 6;

const int trigPin = 2;
const int echoPin = 7;

long duration;
float distance;

const int buzzerPin =3;

void setup()
{
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600);
  
  lcd.begin(16, 2);
  pinMode(buzzerPin,OUTPUT);
}

void loop()
{
  // Send ultrasonic pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  // Measure returning echo
  duration = pulseIn(echoPin, HIGH);

  // Calculate distance in cm
  distance = (duration * 0.0343) / 2;
 
  lcd.setCursor(0, 0);
  lcd.print("Dist: ");
  lcd.print(distance, 1);
  lcd.print(" cm   ");
 
  // Control LEDs, LCD and Buzzer
  if (distance > 50)
  {
    digitalWrite(greenLED, HIGH);
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, LOW);

    lcd.setCursor(0, 1);
    lcd.print("Status: SAFE    ");

    noTone(buzzerPin);
    delay(100);
  }

  else if (distance > 40)
  {
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, HIGH);
    digitalWrite(redLED, LOW);

    lcd.setCursor(0, 1);
    lcd.print("Status: CAUTION ");

    tone(buzzerPin, 800);
    delay(150);
    noTone(buzzerPin);
    delay(600);
  }

  else if (distance > 30)
  {
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, HIGH);
    digitalWrite(redLED, LOW);

    lcd.setCursor(0, 1);
    lcd.print("Status: CAUTION ");

    tone(buzzerPin, 1000);
    delay(150);
    noTone(buzzerPin);
    delay(350);
  }

  else if (distance > 20)
  {
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, HIGH);
    digitalWrite(redLED, LOW);

    lcd.setCursor(0, 1);
    lcd.print("Status: WARNING ");

    tone(buzzerPin, 1200);
    delay(150);
    noTone(buzzerPin);
    delay(150);
  }

  else if (distance > 10)
  {
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, HIGH);

    lcd.setCursor(0, 1);
    lcd.print("Status: STOP    ");

    tone(buzzerPin, 1800);
    delay(100);
    noTone(buzzerPin);
    delay(50);
  }

  else
  {
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, HIGH);

    lcd.setCursor(0, 1);
    lcd.print("Status: DANGER  ");

    tone(buzzerPin, 2000);
  }
}