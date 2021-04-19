#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <AltSoftSerial.h>


//SoftwareSerial hc05(5, 6); // RX, TX
AltSoftSerial hc05;

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

#define pinTrig 12 //piny HC-SR04
#define pinEcho 13 //piny HC-SR04
#define voltage A0 //pin dzielnika napięcia
#define pinObsL 3 //stan czujnika IR
#define pinObsR 4 //stan czujnika IR
#define pinObsL_R 10 //stan krańcówki
#define pinObsR_R 11 //stan krańcówki
#define ledEngines A1

// DEBUG
bool DEBUG = false;
int data = 0;
int corr = 0;

// Dane wysyłane do APP
int dist = 0;
int volt = 0;
int obsR = 0;
int obsL = 0;
int obsR_R = 0;
int obsL_R = 0;

// Dane odebrane z APP
const int received_data_size = 12;
int data_buffer = 0;
int received_data[received_data_size];
bool data_received_correct = false;
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
  //delay(50);//aby zapobiec interferencjom z poprzednich pomiarów
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

void enginesVertical(int state) {
  if (state) {
    digitalWrite(ledEngines, HIGH);
  } else {
    digitalWrite(ledEngines, LOW);
  }
}

void setup() {
  if (DEBUG == true) {
    lcd.init(); // initialize the lcd
    lcd.backlight();
    lcd.print("----!LCD on!----");
    lcd.setCursor(0, 1);
    lcd.print("--LET'S START!--");
  }
  hc05.begin(9600);
  if (DEBUG == true) Serial.begin(9600);
  pinMode(pinTrig, OUTPUT);
  pinMode(ledEngines, OUTPUT);//DEBUG
  digitalWrite(ledEngines, LOW);
  pinMode(pinEcho, INPUT);
  pinMode(pinObsL, INPUT);
  pinMode(pinObsL, INPUT);
  pinMode(pinObsL_R, INPUT_PULLUP);
  pinMode(pinObsR_R, INPUT_PULLUP);
  
}

void loop() {
  if (DEBUG == true) lcd.clear();
  //----ODBIERANIE DANYCH----
  data_received_correct = false;
  if (hc05.available() >= received_data_size) {
    if (hc05.read() == '@' ) {
      //lcd.clear(); lcd.setCursor(0, 0); lcd.print("--DATA AVA--");
      for (int j = 0; j < received_data_size; j++) {
        received_data[j] = hc05.read();
      }
    } 
    if (received_data[received_data_size - 1] == '#') {
      data_received_correct = true; // zaimplementować sumę kontrolną - zaokrąglać do int'a
    }
  }
  if (data_received_correct) {
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

    if (DEBUG) {
      Serial.print("@@");
      for (int j = 0; j < received_data_size - 1; j++) {
        Serial.print(received_data[j]);
        Serial.print("|");
      }
      Serial.println();
    }
  }

  //----DANE ODEBRANE----

  //------STEROWANIE------
  if (ENGINES) {
    enginesVertical(1);
  } else {
    enginesVertical(0);
  }
  
  //------KONIEC STEROWANIA------


  //-------------------------------------------------------------WYSYŁANIE DANYCH----------------------------------------------------------------
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

  delay(10);
}
