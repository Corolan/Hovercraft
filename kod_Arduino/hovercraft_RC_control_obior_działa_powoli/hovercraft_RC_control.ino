#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

SoftwareSerial hc05(5, 6); // RX, TX
LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

#define pinTrig 12//piny HC-SR04
#define pinEcho 13//piny HC-SR04
#define voltage A0//pin dzielnika napięcia

#define pinObsL 3
#define pinObsR 4

int dist = 0;
int volt = 0;
int obsR = 0;
int obsL = 0;

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
int voltageMeasure(){
  int vol = analogRead(voltage);
  vol = map(vol, 0, 1023, 0, 255);
  return vol;
}

//---SPRAWDZENIE PRZESZKOD---
void obstaclesCheck() {
  if (digitalRead(pinObsL) == 0) {
    obsL = 1;
  } else obsL = 0;
  
  if (digitalRead(pinObsR) == 0) {
    obsR = 1;
  } else obsR = 0;  
}



void setup() {


  lcd.init(); // initialize the lcd
  lcd.backlight();
  lcd.print("---LCD on!---");
  lcd.setCursor(0, 1);
  lcd.print("Rozpoczynam");
  hc05.begin(9600);
  hc05.print("Nawiązano połączenie");
  Serial.begin(9600);
  Serial.println("Nawiązano połączenie"); 
  pinMode(pinTrig, OUTPUT);
  pinMode(pinEcho, INPUT);
  pinMode(pinObsL, INPUT);
  pinMode(pinObsL, INPUT);
  //hc05.flush();
}

byte c = 0;


void loop() {
  lcd.clear();
  dist = distanceMeasure();
  volt = voltageMeasure();
  obstaclesCheck();
  int checksum = (dist + volt + obsL + obsR)%255;
  byte data_to_send[] = {dist, volt, obsL, obsR, checksum};


  hc05.print('@'); //poczatek danych
  Serial.print('@'); //poczatek danych
  for (int i = 0; i < sizeof(data_to_send)/sizeof(data_to_send[0]); i++){
    //Serial.print(data_to_send[i]);
    Serial.print(data_to_send[i]);
    //if (i != sizeof(data_to_send) - 1) {
      Serial.print('|');  
    //}  
    hc05.print(data_to_send[i]);
    //if (i != sizeof(data_to_send) - 1) {
      hc05.print('|');
    //}
  }
  Serial.println();
  //hc05.write(data_to_send, sizeof(data_to_send)/sizeof(data_to_send[0]));
  //Serial.println('@');
  //hc05.println('@');//koniec danych
  //Serial.write(data_to_send, sizeof(data_to_send));
  //Serial.print("D: ");
  //Serial.print(dist*(400.0/255.0));//TAKA FORMUŁE DO APP INVENTORA!!!
  //Serial.print("--V: ");
  //Serial.println(volt*5.0/255*2.72);//TAKA FORMUŁE DO APP INVENTORA!!! 2.72 wynika z zastosowanego dzielnika (8,1/3)
  
  delay(200);
}
