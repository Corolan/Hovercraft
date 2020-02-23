#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

SoftwareSerial hc05(5, 6); // RX, TX
LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

#define pinTrig 12 //piny HC-SR04
#define pinEcho 13 //piny HC-SR04
#define voltage A0 //pin dzielnika napięcia
#define pinObsL 3 //stan czujnika IR
#define pinObsR 4 //stan czujnika IR
#define pinObsL_R 9 //stan krańcówki
#define pinObsR_R 10 //stan krańcówki

// DEBUG
bool DEBUG = true;

// Dane wysyłane do APP
int dist = 0;
int volt = 0;
int obsR = 0;
int obsL = 0;
int obsR_R = 0;
int obsL_R = 0;

// Dane odebrane z APP
int received_data[11];
int FORWARD = 0;
int BACKWARD = 0;
int STOP = 0;
int LEFT = 0;
int RIGHT = 0;
int LIGHT = 0;
int SCOUT = 0;
byte SCOUT_PS = 0;
byte VELOCITY = 0;
int ENGINES = 0;
byte CHECKSUM_REC = 0;

//---POMIAR ODLEGŁOŚCI---OK!
int distanceMeasure() {
  digitalWrite(pinTrig, LOW);
  delayMicroseconds(2);
  digitalWrite(pinTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrig, LOW);
  int distance = pulseIn(pinEcho, HIGH) / 58;
  if (distance > 400) distance = 400;
  distance = map(distance, 0, 400, 0, 255);
  return distance;
}

//---POMIAR NAPIĘCIA--- OK!
int voltageMeasure() {
  int vol = analogRead(voltage);
  vol = map(vol, 0, 1023, 0, 255);
  return vol;
}

//---SPRAWDZENIE PRZESZKOD---
void obstaclesCheck() { // odczytanie stanu czujników IR
  if (digitalRead(pinObsL) == 0) {
    obsL = 1;
  } else obsL = 0;

  if (digitalRead(pinObsR) == 0) {
    obsR = 1;
  } else obsR = 0;

  if (digitalRead(pinObsL_R) == 0) {
    obsL_R = 1;
  } else obsL_R = 0;

  if (digitalRead(pinObsR_R) == 0) {
    obsR_R = 1;
  } else obsR_R = 0;
}



void setup() {

  lcd.init(); // initialize the lcd
  lcd.backlight();
  lcd.print("---LCD on!---");
  lcd.setCursor(0, 1);
  lcd.print("Rozpoczynam");
  hc05.begin(9600);
  if (DEBUG == true) Serial.begin(9600);
  pinMode(pinTrig, OUTPUT);
  pinMode(pinEcho, INPUT);
  pinMode(pinObsL, INPUT);
  pinMode(pinObsL, INPUT);
  pinMode(pinObsL_R, INPUT_PULLUP);
  pinMode(pinObsR_R, INPUT_PULLUP);
}

void loop() {
  lcd.clear();
//----ODBIERANIE DANYCH----
  if ((hc05.available() > 0) && (hc05.read() == "@")) { // Czy dane są dostępne i czy zaczynają się od właściwego bajtu
    bool received_data_correct = false;
    for (int j = 0; j <= 11; j++) {
      received_data[j] = hc05.read();
    }
    //Obliczam sumę kontrolną
    for (int j = 0; j <= 11; j++) {
      CHECKSUM_REC = CHECKSUM_REC + received_data[j];
    }
    CHECKSUM_REC = CHECKSUM_REC % 255;
    if (CHECKSUM_REC == received_data[10]) received_data_correct = true;
    if (received_data_correct == true) {
      FORWARD = received_data[0];
      BACKWARD = received_data[1];
      STOP = received_data[2];
      LEFT = received_data[3];
      RIGHT = received_data[4];
      LIGHT = received_data[5];
      SCOUT = received_data[6];
      SCOUT_PS = received_data[7];
      VELOCITY = received_data[8];
      ENGINES = received_data[9];
      lcd.setCursor(0, 1);
      lcd.print("OD:");
      for (int j = 0; j <= 9; j++) {
        lcd.print(received_data[j]);
      }

    }
  }
  //----DANE ODEBRANE----

  //------STEROWANIE------
  //------KONIEC STEROWANIA------

  
  //----WYSYŁANIE DANYCH----
  // Przygotowanie danych do wysłania
  dist = distanceMeasure();
  volt = voltageMeasure();
  obstaclesCheck();
  int checksum = (dist + volt + obsL + obsR + obsL_R + obsR_R) % 255;
  byte data_to_send[] = {dist, volt, obsL, obsR, obsL_R, obsR_R, checksum};


  hc05.print('@'); //poczatek danych
  if (DEBUG == true) Serial.print('@'); //poczatek danych
  for (int i = 0; i < sizeof(data_to_send) / sizeof(data_to_send[0]); i++) {
    if (DEBUG == true) {
      Serial.print(data_to_send[i]);
      Serial.print('|');
    }
    hc05.print(data_to_send[i]);
    hc05.print('|');
  }
  if (DEBUG == true) Serial.println();
  //----DANE WYSŁANE----

  delay(100);
}
