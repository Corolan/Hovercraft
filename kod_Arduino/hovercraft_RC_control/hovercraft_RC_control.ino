#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <AltSoftSerial.h>

//TX-pin9, RX-pin8, pin10 - no PWM
AltSoftSerial hc05;
LiquidCrystal_I2C lcd(0x27, 20, 4); // set the LCD address to 0x27 for a 16 chars and 4 line display -- zmienić na wyswietlacz 16/4

const int received_data_size {1}; //jak na razie przesyłam jeden bajt użytecznych danych
int received_data[received_data_size + 2]; //"+2" - dochodzą znaki początku i końca ramki

const int to_send_data_size{1};//jak na razie przesyłam jeden bajt użytecznych danych
int data_to_send[to_send_data_size + 2];//"+2" - dochodzą znaki początku i końca ramki

//pin A0 - odczyt napięcia zasilania
float ps_voltage{0};//power supply voltage

// DEBUG
bool DEBUG = true;
byte test_variable{0};

//deklaracje zmiennych sterujących
bool LED_REFLEKTOR{false};

void headlight_LED(bool state);

void setup() {
  if (DEBUG == true) {
    lcd.init(); // initialize the lcd
    lcd.backlight();
    lcd.print("------!LCD on!------");
    lcd.setCursor(0, 2);
    lcd.print("----LET'S START!----");
    Serial.begin(9600);
    pinMode(11, OUTPUT);//DEBUG
    pinMode(13, OUTPUT); digitalWrite(13, LOW); //DEBUG
  }
  hc05.begin(9600);
}

void loop() {
  //pobieranie rozkazów z aplikacji
  if ( hc05.available() < received_data_size) { //oczekuje na rozkazy z aplikacji
    lcd.clear(); lcd.setCursor(0, 0); lcd.print("No data");
  } else { //pojawiły się rozkazy!
    lcd.clear(); lcd.setCursor(0, 0); lcd.print("Data arrived");
    lcd.setCursor(0, 1);
    int i{0};
    while ( hc05.available() > 0) {
      received_data[i] = hc05.read();
      lcd.print(received_data[i]); lcd.print("-");
      i++;
    }
    if (received_data[0] == 64 && received_data[received_data_size + 1] == 35) { // Sprawdzenie kompletności odebranych danych, '@'=64, '#'=35
      //pełna ramka odebrana, tutaj będzie procesowanie rozkazów
      lcd.setCursor(0, 3); lcd.print("Data detected");
      lcd.setCursor(0, 2); lcd.print(received_data[1]);
      LED_REFLEKTOR = received_data[1];
    }

  }

  //Wyonanie rozkazów na podstawie otrzymanych danych
  headlight_LED(LED_REFLEKTOR);

  //Przygotowanie danych do wysłania
  //1. pomiar napięcia zasilania
  ps_voltage = read_voltage();

  //Wysyłanie danych do aplikacji
  data_to_send[0] = '@';
  data_to_send[to_send_data_size + 1] = '#';
  //data_to_send[1] = ps_voltage
  data_to_send[1] = test_variable; test_variable++;

  for (int j{0}; j < to_send_data_size + 2; j++) {
    hc05.print(data_to_send[j]);
  }

  
  
  
  //czy delay konieczny?
  delay(100);
}

float read_voltage(){
  //po odjeciu lcd przerobić to na pojedynczy return
  float voltage = analogRead(A0)*5/1023.0;//przeliczenie na wolty
  lcd.setCursor(15, 0); lcd.print(voltage);
  return voltage*5; // czynnik "5" wynika z zastosowanego dzielnika napięcia
}

void headlight_LED(bool state) {
  if (state) {
    digitalWrite(11, HIGH);
  } else {
    digitalWrite(11, LOW);
  }
}
