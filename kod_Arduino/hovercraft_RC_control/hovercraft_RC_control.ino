#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <AltSoftSerial.h>

//wyrzucić wszystko poza łącznością
//najpierw zając się obsługą silników!

//SoftwareSerial hc05(5, 6); // RX, TX
AltSoftSerial hc05;

LiquidCrystal_I2C lcd(0x27, 16, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display -- zmienić na wywitlacz 16/4



// DEBUG
bool DEBUG = false;

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



void setup() {
  if (DEBUG == true) {
    lcd.init(); // initialize the lcd
    lcd.backlight();
    lcd.print("----!LCD on!----");
    lcd.setCursor(0, 1);
    lcd.print("--LET'S START!--");
    Serial.begin(9600);
  }
  hc05.begin(9600);//co jeśli nie wystartuje?
}

void loop() {
  if (DEBUG == true ) lcd.clear();
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
  
  //------KONIEC STEROWANIA------


  //-------------------------------------------------------------WYSYŁANIE DANYCH----------------------------------------------------------------
  // Przygotowanie danych do wysłania

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
