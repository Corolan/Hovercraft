
#include <SoftwareSerial.h>

#define LED 8
#define SCOUT_LED 10
#define LIGHT_LED 11
#define VOLTAGE A0
#define RX 2 //piny modułu hc06
#define TX 3

SoftwareSerial hc06(2, 3);

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  pinMode(SCOUT_LED, OUTPUT);
  pinMode(LIGHT_LED, OUTPUT);
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




int distanceMeasure(){
  return 7; 
}
int voltageMeasure(){
  int measured_voltage = analogRead(VOLTAGE);

  measured_voltage = map(measured_voltage, 0, 1023, 0, 255);
  return measured_voltage; //pamiętać by wysyłać co najwyżej 255!!!!! 1023/4 może?
}
int checkObstacles(int obstacles[], int number_of_IR_sensors){
  obstacles[0]= 1;
  obstacles[1]= 1;
}

void loop() {

  dist_hcsr04 = distanceMeasure();
  aku_voltage = voltageMeasure();
  int checkObstacles(sensorsIR, 2);
  //byte data_to_send[] = {dist_hcsr04, aku_voltage, sensorsIR[0], sensorsIR[1]};
  byte data_to_send[] = {dist_hcsr04, aku_voltage, obs_R, obs_L};
  int data_to_send_size = sizeof(data_to_send);
  
  int data_received[9];
  int dane_bufor = 0;

  
  if (hc06.available() > 0) { //przesyłam dane partiami po 9 bajtów
    //Serial.write(hc06.read());
    //Serial.print("Odebrano bajty: ");
    Serial.print("<");
    for (int i = 0; i < 9; i++) {
      dane_bufor = hc06.read();
     // if (dane_bufor != -1) 
     {
        data_received[i] = dane_bufor;
        //i++;
        
        //Serial.print(i);
        //Serial.print(": ");
        Serial.print(data_received[i]);
        Serial.print("-");
      }
    }
    Serial.println(">");
    
  }

//STEROWANIE
  if (data_received[0] == 1 ) {
    digitalWrite(LED, HIGH);
  } else {
    digitalWrite(LED, LOW);
  }

  if (data_received[6] == 1 ) {
    digitalWrite(SCOUT_LED, HIGH);
  } else {
    digitalWrite(SCOUT_LED, LOW);
  }
  if (data_received[5] == 1 ) {
    digitalWrite(LIGHT_LED, HIGH);
  } else {
    digitalWrite(LIGHT_LED, LOW);
  }  
//WYSYŁANIE
  Serial.print("SEND: <");
  for (int j = 0; j <  data_to_send_size; j++) {
    hc06.write(data_to_send[j]);
    Serial.print(data_to_send[j]);
    Serial.print("-");
  }
  Serial.print(">");
//  //Write from Serial Monitor to HC06
//  if (Serial.available()) {
//    hc06.write(Serial.read());
//  }
  delay(50);
}
