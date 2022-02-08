#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <AltSoftSerial.h>
//#include <Servo.h>

//TX-pin9, RX-pin8, pin10 - no PWM
AltSoftSerial hc05;
LiquidCrystal_I2C lcd(0x27, 20, 4); // set the LCD address to 0x27 for a 16 chars and 4 line display -- zmienić na wyswietlacz 16/4
//Servo headlight_servo;

const int data_to_receive_size {2}; //liczba danych do odebrania
int data_to_receive[data_to_receive_size + 3]; //"+3" - dochodzą znaki początku i końca ramki oraz checksuma

const int data_to_send_size {6}; //liczba pól do wysłania
int data_to_send[data_to_send_size + 3];//"+3" - dochodzą znaki początku i końca ramki oraz suma kontrolna

int checksum_send{0};

#define PS_VOLTAGE A0 //pin A0 - odczyt napięcia zasilania
#define OBSTCL_LEFT 3
#define OBSTCL_RIGHT 2
#define ENG_VERTICAL 4 //silnik pionowy ( dmchaw[a/y] )
#define trigPin 12
#define echoPin 13
#define headlight_pin 11

//byte testvar{0};

//deklaracje zmiennych
bool LED_REFLEKTOR{false};
bool vertical_engine{false};

//deklaracje funkcji
int read_voltage();
int check_obstacles(int pin);
int read_distance();

void prepare_data_to_send();
void show_data_to_send();
void send_data_to_phone();

void headlight_LED(bool state);
void control_vertical_engines(bool state);

void setup() {
  //Serial.begin(9600);
  pinMode(headlight_pin, OUTPUT);
  hc05.begin(9600);
  //headlight_servo.attach(6);
  //headlight_servo.write(0);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(OBSTCL_LEFT, INPUT);
  pinMode(OBSTCL_RIGHT, INPUT);
  pinMode(ENG_VERTICAL, OUTPUT); digitalWrite(ENG_VERTICAL, LOW);
  lcd.init(); 
  lcd.backlight();
  lcd.clear(); 
  lcd.setCursor(0, 0); lcd.print(F("Start_123"));
}

void loop() {
  prepare_data_to_send();
  show_data_to_send();
  send_data_to_phone();
  //headlight_servo.write(255);
  delay(200);

}

int read_voltage() {
  //lcd.setCursor(15, 0); lcd.print(voltage / 4);
  return analogRead(PS_VOLTAGE);
}

void headlight_LED(bool state) { //dodać definicję pinu headlight
  if (state) {
    digitalWrite(headlight_pin, HIGH);
    //Serial.println("Reflektor: ON");
  } else {
    digitalWrite(headlight_pin, LOW);
    //Serial.println("Reflektor: OFF");
  }
}

int check_obstacles(int pin) {
  if (digitalRead(pin) == LOW) {
    return 1;
  } else {
    return 0;
  }
}

void control_vertical_engines(bool state) {
  if (state == true) {
    digitalWrite(ENG_VERTICAL, HIGH);
    //Serial.println("Silniki pionowe: ON");
  }
  else if (state == false) {
    digitalWrite(ENG_VERTICAL, LOW);
    //Serial.println("Silniki pionowe: OFF");
  }
}

int read_distance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  int dist{(int)pulseIn(echoPin, HIGH) / 58};
  if (dist >= 400) { //max range = 400 cm
    dist = 400;
  }
  // Serial.print("D: ");
  //Serial.println(dist);
  return dist;
}

void prepare_data_to_send(){
  //Przygotowanie danych do wysłania
  data_to_send[1] = read_voltage()/4; //1. pomiar napięcia zasilania - czynnik "4" wynika z tego, że muszę zmieścić się w jednym bajcie
  data_to_send[2] = check_obstacles(OBSTCL_LEFT);
  data_to_send[3] = check_obstacles(OBSTCL_RIGHT);
  data_to_send[4] = read_distance()/4; //czynnik "4" wynika z tego, że muszę zmieścić się w jednym bajcie
  data_to_send[5] = 0; //zarezerwowane
  data_to_send[6] = 0; //zarezerwowane
  checksum_send = 0;
  for (byte j=1; j <= data_to_send_size; j++){
    checksum_send += data_to_send[j];
  }
  data_to_send[data_to_send_size + 1] = checksum_send % 255;//checksum
  data_to_send[data_to_send_size + 2] = 35; //'#';
}

void show_data_to_send(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("V: "); lcd.print(data_to_send[1]); lcd.print(" O: "); lcd.print(data_to_send[2]);lcd.print(" ");lcd.print(data_to_send[3]);
  lcd.setCursor(0, 1);
  lcd.print("DST: "); lcd.print(data_to_send[4]);
  lcd.setCursor(0, 2);
  lcd.print("R1: "); lcd.print(data_to_send[5]); lcd.print(" R2: "); lcd.print(data_to_send[6]);
  lcd.setCursor(0, 3);
  lcd.print("CSM: "); lcd.print(data_to_send[data_to_send_size + 1]);
  
}

void send_data_to_phone(){

  hc05.write("$"); //ascii 36
  if(hc05.available() > 0){
    if (hc05.read() == "!") { //ascii 33
        for (int j{0}; j < data_to_send_size + 3; j++) {//"+3" bo checksum-a
      hc05.write(data_to_send[j]);
    }
    }
  }
}
/*
void loop() {

  //pobieranie rozkazów z aplikacji
  if ( hc05.available() < data_to_receive_size + 3) { //oczekuje na rozkazy z aplikacji
    //jeżeli brak rozkazów -- wyłączyć silniki!!!!
   
    control_vertical_engines(false);
   
  } else { //pojawiły się rozkazy!

    data_to_receive[0] = 1;//wpisuję złą wartość    
    while (data_to_receive[0] != 64) { //"64"="@"
      data_to_receive[0] = hc05.read(); //oczekuję na początek ramki ("@")
    }

    for (int i = 1; i < data_to_receive_size + 3; i++) {//od "1" bo już mam początek ramki
      data_to_receive[i] = hc05.read();
    }
    
    if (data_to_receive[0] == 64 && data_to_receive[data_to_receive_size + 2] == 35) { // Sprawdzenie kompletności odebranych danych, '@'=64, '#'=35
      //pełna ramka odebrana, tutaj będzie procesowanie rozkazów
      //liczyć sumę kontrolną!
      int local_checksum{0};
      if (local_checksum == data_to_receive[data_to_receive_size + 1] ){//jeśli checksuma się zgadza
        LED_REFLEKTOR = data_to_receive[1];
        vertical_engine = data_to_receive[2];
      }
    } else {
      //Serial.println("---Wrong data---");
    }


    //Wysyłanie danych do aplikacji 
    data_to_send[0] = 64; //'@';

    //Przygotowanie danych do wysłania
    data_to_send[1] = read_voltage() / 4; //1. pomiar napięcia zasilania - czynnik "4" wynika z tego, że muszę zmieścić się w jednym bajcie
    data_to_send[2] = check_obstacles(OBSTCL_LEFT);
    data_to_send[3] = check_obstacles(OBSTCL_RIGHT);
    data_to_send[4] = read_distance() / 4; //czynnik "4" wynika z tego, że muszę zmieścić się w jednym bajcie
    data_to_send[data_to_send_size + 1] = 0;//checksum
    data_to_send[data_to_send_size + 2] = 35; //'#';

    lcd.setCursor(0, 1); lcd.print(" Sent: ");
    for (int j{0}; j < data_to_send_size + 3; j++) {//"+3" bo checksum-a
      hc05.write(data_to_send[j]);

    }
    //Serial.println();
  
    //Wykonanie rozkazów na podstawie otrzymanych danych
  headlight_LED(LED_REFLEKTOR);
  control_vertical_engines(vertical_engine);
  
  }


  //czy delay konieczny? zamienić go na millis?
  //delay(200);
}
*/
