#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <AltSoftSerial.h>

//TX-pin9, RX-pin8, pin10 - no PWM
AltSoftSerial hc05;
LiquidCrystal_I2C lcd(0x27, 16, 4); // set the LCD address to 0x27 for a 16 chars and 4 line display -- zmienić na wyswietlacz 16/4

const int received_data_size{3};
int received_data[received_data_size];

// DEBUG
bool DEBUG = true;

void setup() {
  if (DEBUG == true) {
    lcd.init(); // initialize the lcd
    lcd.backlight();
    lcd.print("------!LCD on!------");
    lcd.setCursor(0, 2);
    lcd.print("----LET'S START!----");
    Serial.begin(9600);
    pinMode(10, OUTPUT);
  }
  hc05.begin(9600);
}

void loop() {
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
    if (received_data[0] == '@' && received_data[received_data_size-1] == '#'){
      //pełna ramka odebrana
      lcd.setCursor(0, 3); lcd.print("Data detected");
    }

  }

  //digitalWrite(13, HIGH);

  delay(100);
}
