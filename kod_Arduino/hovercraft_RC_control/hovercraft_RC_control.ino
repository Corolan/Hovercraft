#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <AltSoftSerial.h>

//TX-pin9, RX-pin8, pin10 - no PWM
AltSoftSerial hc05;
LiquidCrystal_I2C lcd(0x27, 20, 4); // set the LCD address to 0x27 for a 16 chars and 4 line display -- zmienić na wyswietlacz 16/4

const int received_data_size {2}; //jak na razie przesyłam dwa bajty użytecznych danych
int received_data[received_data_size + 3]; //"+2" - dochodzą znaki początku i końca ramki oraz checksuma

const int to_send_data_size {
  4
};
int data_to_send[to_send_data_size + 3];//"+3" - dochodzą znaki początku i końca ramki oraz suma kontrolna
//int checksum{0}; // policzyć sumę kontrolną

#define LED_VOLTAGE A0 //pin A0 - odczyt napięcia zasilania
#define OBSTCL_LEFT 3
#define OBSTCL_RIGHT 2
#define ENG_VERTICAL 4 //silnik pionowy ( dmchaw[a/y] )
#define trigPin A4
#define echoPin A5
#define headlight_pin 11

byte testvar{0};

//deklaracje zmiennych
bool LED_REFLEKTOR{false};
bool vertical_engine{false};

//deklaracje funkcji
int read_voltage();
int check_obstacles(int pin);
//int read_distance();

void headlight_LED(bool state);
void control_vertical_engines(bool state);

void setup() {
  //Serial.begin(9600);
  pinMode(headlight_pin, OUTPUT);
  pinMode(13, OUTPUT); digitalWrite(13, LOW); //DEBUG
  hc05.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(OBSTCL_LEFT, INPUT);
  pinMode(OBSTCL_RIGHT, INPUT);
  pinMode(ENG_VERTICAL, OUTPUT); digitalWrite(ENG_VERTICAL, LOW);
  lcd.init(); 
  lcd.backlight();
  //lcd.clear(); 
  lcd.setCursor(0, 0); lcd.print("Start_123");
}

void loop() {
  lcd.setCursor(0, 0); lcd.print(testvar);
  testvar++;
  //pobieranie rozkazów z aplikacji
  if ( hc05.available() < received_data_size + 3) { //oczekuje na rozkazy z aplikacji
    //jeżeli brak rozkazów -- wyłączyć silniki!!!!
    //Serial.println("No data!");
    digitalWrite(ENG_VERTICAL, LOW);
    //lcd.clear(); lcd.setCursor(0, 0); lcd.print("No data");
  } else { //pojawiły się rozkazy!
    //Serial.println("Są!");

    received_data[0] = 1;//wpisuję złą wartość    
    while (received_data[0] != 64) {
      received_data[0] = hc05.read();
    }

    //Serial.print("Data-receiv: ");
    //Serial.print(received_data[0]); Serial.print("|");
    lcd.clear(); lcd.setCursor(0, 0); lcd.print("Received: ");lcd.print(received_data[0]); 
    for (int i = 1; i < received_data_size + 3; i++) {
      received_data[i] = hc05.read();
      lcd.print(received_data[i]); 
      lcd.print("|");
    }
    //Serial.print(" ");
    
    if (received_data[0] == 64 && received_data[received_data_size + 2] == 35) { // Sprawdzenie kompletności odebranych danych, '@'=64, '#'=35
      //pełna ramka odebrana, tutaj będzie procesowanie rozkazów
      //liczyć sumę kontrolną!
      //Serial.print("Data correct");
      LED_REFLEKTOR = received_data[1];
      vertical_engine = received_data[2];
    } else {
      //Serial.println("---Wrong data---");
    }

    //Serial.println("Sending...");
    //Wysyłanie danych do aplikacji --- czy przenieść to do sekcji w drugim if-ie? Tak żeby próba nadania danych następowala tylko gdy po drugiej stronie jest aplikacja
    data_to_send[0] = 64; //'@';

    //Przygotowanie danych do wysłania
    data_to_send[1] = read_voltage() / 4; //1. pomiar napięcia zasilania - czynnik "4" wynika z tego, że muszę zmieścić się w jednym bajcie
    data_to_send[2] = check_obstacles(OBSTCL_LEFT);
    data_to_send[3] = check_obstacles(OBSTCL_RIGHT);
    data_to_send[4] = read_distance() / 4; //czynnik "4" wynika z tego, że muszę zmieścić się w jednym bajcie
    data_to_send[to_send_data_size + 1] = 0;//checksum
    data_to_send[to_send_data_size + 2] = 35; //'#';

    lcd.setCursor(0, 1); lcd.print(" Sent: ");
    for (int j{0}; j < to_send_data_size + 3; j++) {//"+3" bo checksum-a
      hc05.write(data_to_send[j]);
      lcd.print(data_to_send[j]);
      lcd.print("|");
    }
    //Serial.println();
  
    //Wykonanie rozkazów na podstawie otrzymanych danych
  headlight_LED(LED_REFLEKTOR);
  control_vertical_engines(vertical_engine);
  
  }


  //czy delay konieczny? zamienić go na millis?
  //delay(200);
}

int read_voltage() {
  //lcd.setCursor(15, 0); lcd.print(voltage / 4);
  return analogRead(LED_VOLTAGE);
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
