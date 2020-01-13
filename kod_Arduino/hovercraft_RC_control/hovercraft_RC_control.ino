
#include <SoftwareSerial.h>

#define LED 8
#define SCOUT_LED 10
#define LIGHT_LED 11
#define VOLTAGE A0
#define RX 2 //piny modułu hc06 - RX modułu -> 3 pin ARDUINO
#define TX 3 // TX modułu -> 2  pin ARDUINO

#define pinTrig 4//piny HC-SR04
#define pinEcho 7

SoftwareSerial hc06(2, 3);

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  pinMode(SCOUT_LED, OUTPUT);
  pinMode(LIGHT_LED, OUTPUT);
  pinMode(pinTrig, OUTPUT);
  pinMode(pinEcho, INPUT);
  digitalWrite(LED, LOW);
  digitalWrite(SCOUT_LED, LOW);
  digitalWrite(LIGHT_LED, LOW);
  //Initialize Serial Monitor
  Serial.begin(9600);
  //Initialize Bluetooth Serial Port
  hc06.begin(9600);
}
//Dane odbierane z aplikacji mobilnej
bool FORWARD = false;
bool BACKWARDS = false;
bool LEFT = false;
bool RIGHT = false;
bool STOP = false;
bool SCOUT_ON = false;
bool LIGHT_ON = false;
int SCOUT_POS = 0;
int VELOCITY = 0;


//Dane wysyłane do aplikacji mobilnej
int dist_hcsr04 = 0;
int aku_voltage = 4;

int sensorsIR[] = {0,0};

int obs_R = 1;
int obs_L = 8;


//---------------FUNKCE POMOCNICZE-------------------

//---POMIAR ODLEGŁOŚCI---
int distanceMeasure(){
  digitalWrite(pinTrig, LOW);
  delayMicroseconds(2);
  digitalWrite(pinTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrig, LOW);
  return pulseIn(pinEcho, HIGH)/58;  
}

//---POMIAR NAPIĘCIA---
int voltageMeasure(){
  int measured_voltage = analogRead(VOLTAGE);

  measured_voltage = map(measured_voltage, 0, 1023, 0, 255);
  return measured_voltage; //pamiętać by wysyłać co najwyżej 255!!!!! 1023/4 może?
}

//---CZUJNIKI IR---
int checkObstacles(int obstacles[], int number_of_IR_sensors){
  obstacles[0]= 1;
  obstacles[1]= 1;
}

//--------------------------PĘTLA GŁÓWNA---------------------------
void loop() {

//------------------------Odbieranie danych z aplikacji mobilnej--------------------------------------  
  int dane_bufor = 0;
  int data_received[9];
  int data_received_size = 9;
  if (hc06.available() > 0) { //przesyłam dane partiami po 9 bajtów
    Serial.print("REC: <");
    for (int i = 0; i < data_received_size; i++) {
     dane_bufor = hc06.read();
     {
        data_received[i] = dane_bufor;
        Serial.print(data_received[i]);
        if (i != data_received_size - 1) Serial.print("-");
      }
    }
    Serial.print("> ");
    //Oberałem dane. Teraz sprawdzam, czy nie pojawia się tam "-1". Jeżeli tak, nie wpisuje tych danych to zmiennych, jeżeli nie, użyję odebranych danych
    bool data_received_correct = true;
    for (int i = 0; i < data_received_size; i++) {
      if (data_received[i] == -1) data_received_correct = false;
      if(i<7) if(data_received[i] > 1 ) data_received_correct = false;
    }
    //if () data_received_correct = false;
    if (data_received[0] == 1 && data_received[1] == 1) data_received_correct = false;//jednoczesna jazda w przód i tył
    if (data_received[3] == 1 && data_received[4] == 1) data_received_correct = false;//jednoczesna jazda w lewo i prawo
    if (data_received[2] == 1 && (data_received[0] == 1 || data_received[1] == 1 || data_received[3] == 1 || data_received[4] == 1)) data_received_correct = false;//jednoczesna jazda w dowolnym kierunku i STOP
    //Sprawdzanie zakończone  
    if (data_received_correct == true){
      FORWARD = data_received[0];
      BACKWARDS = data_received[1];
      STOP = data_received[2];  
      LEFT = data_received[3];
      RIGHT = data_received[4];
      SCOUT_ON = data_received[5];
      LIGHT_ON = data_received[6];
      SCOUT_POS = data_received[7];
      VELOCITY = data_received[8];
    }
    Serial.print("RCD: <");
      Serial.print(FORWARD);
      Serial.print("-");
      Serial.print(BACKWARDS);
      Serial.print("-");
      Serial.print(STOP);
      Serial.print("-");
      Serial.print(LEFT);
      Serial.print("-");
      Serial.print(RIGHT);
      Serial.print("-");
      Serial.print(SCOUT_ON);
      Serial.print("-");
      Serial.print(LIGHT_ON);
      Serial.print("-");
      Serial.print(SCOUT_POS);
      Serial.print("-");
      Serial.print(VELOCITY);
    Serial.print("> ");
  }
//--------------DANE ODEBRANO----------------------------------


//---STEROWANIE---
  if (FORWARD == 1 ) {
    digitalWrite(LED, HIGH);
  } else if (FORWARD == 0 ) {
    digitalWrite(LED, LOW);
  }

  if (SCOUT_ON == 1 ) {
    digitalWrite(SCOUT_LED, HIGH);
  } else if (SCOUT_ON == 0 ) {
    digitalWrite(SCOUT_LED, LOW);
  }
  if (LIGHT_ON == 1 ) {
    digitalWrite(LIGHT_LED, HIGH);
  } else if (LIGHT_ON == 0 ) {
    digitalWrite(LIGHT_LED, LOW);
  }  
//----------------------------WYSYŁANIE------------------------------------------------------

//Przygotowanie danych do wysłania
  dist_hcsr04 = distanceMeasure();
  aku_voltage = voltageMeasure();
  int checkObstacles(sensorsIR, 2);
  //byte data_to_send[] = {dist_hcsr04, aku_voltage, sensorsIR[0], sensorsIR[1]};
  byte data_to_send[] = {(byte)dist_hcsr04, (byte)aku_voltage, (byte)obs_R, (byte)obs_L};
  int data_to_send_size = 4;

  
  //hc06.print(dist_hcsr04);
  if (hc06.availableForWrite() >= data_to_send_size) hc06.write(data_to_send, data_to_send_size);
  Serial.print("SND: <");
  for (int j = 0; j <  data_to_send_size; j++) {
//    //hc06.write(data_to_send[j]);
    Serial.print(data_to_send[j]);
      //Serial.print(dist_hcsr04);
    if (j != data_to_send_size-1) Serial.print("-");
  }
  Serial.println(">");
//--------------DANE WYSŁANO----------------------------------
  delay(100);
}
