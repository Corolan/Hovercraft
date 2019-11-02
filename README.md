# MGR

## Pomysły i uwagi
* Pojazd na poduszcze powietrznej
  * Lekka rama -> balsa
    * Dwa poziomy: pokład głownu i podpokład z elektroniką - ciąg powietrza zapewni chłodzenie
  * Poduszka -> materiałowa? Stara ortalionowa kurtka?
  * Jeden/Dwa silniki do napełnienie poduszki -> Kanały sterownika (dwie dmuchawy sterowane jednym sygnałem?)
  * Silnik napędowy
    * Zamocowany na seromechaniźmie
  * czy dodawać fotorezystory?
  * Dodać LED 5V wskazujący uruchomienie?
  * Woltomierz mierżacy napięcie na AKU dopięty do złącza ARK 12V płytki zasilającej.
  

## Liczba potrzebnych pinów sterujących mikrokontrolera:
  * Silniki: 2 silniki x 3 piny = 6 pinów (4 cyfrowe + 2 PWM) (dmuchawy sterowane jednym sygnałem)
  * Serwo: 1 pin PWM
  * Moduł Bluetooth: 2 piny cyfrowe
  * LED: 1 pin cyfrowy
  * Czujnik HC-SR04: 2 piny cyfrowe
  * Krańcówki: 4 piny cyfrowe
  * Opcjonalnie: RFID: 4 piny cyfrowe
    * Razem: 3 piny PWM oraz 13 pinów cyfrowych - WYSTARCZY

## Do zrobienia
- [ ] Określić ramy czasowe
- [x] Lista części
- [x] Wstępny schemat
  - [x] Projekt obwodu zasilania
  - [x] Projekt obwodu czujników
- [ ] Zakup części
- [ ] Projekt konstrukcji głównej
  - [ ] Zaplanować rozłożenie rzeczywiste elementów konstrukcji 
  -  [ ] Zapewnić prawidłowe wyważenie konstrukcji
- [ ] Napisać oprogramowanie sterujące pojazdem
  - [ ] Przygotować aplikację Androidową kontrolującą pojazd


## Części
* Mechanika:
  * Konstrukcja kadłuba
    * [Balsa - ABC](https://abc-rc.pl/product-pol-2139-Balsa-Modelarska-3-0-mm-srednia-I-klasa.html)
  * Dystanse
    * [Tuleje dystansowe - ABC](https://abc-rc.pl/product-pol-7191-Zestaw-180-sztuk-Srub-i-Tulei-Dystansowych-M3-6-8-10-12-15-20-mm-Poliamid.html)
* Napęd:    
  * Silniki poduszki powietrznej:
    * [Dmuchawa wentylatorowa 12V 4,2W - BOTLAND](https://botland.com.pl/pl/pompy/8875-dmuchawa-wentylatorowa-12v-42w-97x97x33mm.html?search_query=Dmuchawa+wentylatorowa+12V+4%2C2W&results=1)
  * Silnik napędowy:
    * [Silnik GPX Extreme Swift 500 12V 11700RPM - BOTLAND](https://botland.com.pl/pl/silniki-dc-bez-przekladni/7304-silnik-gpx-extreme-swift-500-12v-11700rpm.html)
  * Piasta śmigła napędowego
    * [Piasta śmigła Gemfan 3,17/M5 - samozaciskowa - CW - prawa - ABC](https://abc-rc.pl/product-pol-4299-Piasta-smigla-Gemfan-3-17-M5-samozaciskowa-CW-prawa.html)
  * Śmigło napędowe:
    * [Śmigło 6x4E - black - HIGH Speed - śmigło 6040E - ABC](https://abc-rc.pl/product-pol-12265-Smiglo-6x4E-black-HIGH-Speed-smiglo-6040E.html)
  * Mocowanie silnika napędowego:
    * [Gimbal - jedno serwo? - ABC](https://abc-rc.pl/product-pol-1549-Gimbal-Nylon-30x30-Pan-Tilt-do-kamery-Cmos.html)
  * Sterownik silnika napędowego i dmuchawy:
    * [L298N - dwukanałowy sterownik silników - moduł 12V/2A - BOTLAND](https://botland.com.pl/pl/sterowniki-silnikow-moduly/3164-l298n-dwukanalowy-sterownik-silnikow-modul-12v2a.html?search_query=L298N+-+dwukanalowy+sterownik+silnikow+-+modul+12V%2F2&results=2)
* Łączność:
  * [Moduł Bluetooth HC-05 - ABC](https://abc-rc.pl/product-pol-6189-Bluetooth-HC-05-master-slave-modul-do-APM-i-AlexMos-Arduino.html)
  * [Konwerter poziomów logicznych -ABC](https://abc-rc.pl/product-pol-6191-Konwerter-poziomow-3-3-5V-4-kanaly-stanow-logicznych-SPI-UART-Arduino.html)
* Wytrawianie płytek pcb:
  * [Zestaw płytek - ABC](https://abc-rc.pl/product-pol-9595-Zestaw-laminatow-0-35kg-rozne-wymiary-do-budowy-plytek-PCB.html) 
  * [Marker do rysowania ścieżek - ABC](https://abc-rc.pl/product-pol-9594-Marker-do-rysowania-sciezek-0-3mm-czarny.html?rec=101801302)
  * [Nadsiarczan sodowy - ABC](https://abc-rc.pl/product-pol-10124-Wytrawiacz-do-plytek-drukowanych-B327-Nadsiarczan-sodowy.html)
  * [Trzecia Ręka z Lupą - ABC](https://abc-rc.pl/product-pol-6275-Trzecia-Reka-z-Lupa-podswietlenie-LED-ZD-10MB.html)
* Zasilanie:
  * Akumulator Li-Pol:
    * [Akumulator Tattu 1300mAh 3S 75C - ABC](https://abc-rc.pl/product-pol-6659-Akumulator-Tattu-1300mAh-3S-75C-Li-pol-Gens-Ace-11-1V.html)
  * Złącze do akumulatora 
    * [Złącze XT60](https://abc-rc.pl/product-pol-1571-Wtyki-XT60-Konektor-wtyk-i-gniazdo-wysoko-pradowe.html)
  * Ładowarka Li-Pol
    * [Ładowarka modelarska IMAX B3 - 2S/3S - ABC](https://abc-rc.pl/product-pol-3961-Ladowarka-modelarska-IMAX-B3-2S-3S-li-pol-zasilanie-230V.html?rec=101002101)
  * Włącznik:
    * [Przełącznik kołyskowy - ABC](https://abc-rc.pl/product-pol-12025-Przelacznik-kolyskowy-MRS102-A-C3R-15x21mm-3PIN-ON-OFF-bistabilny.html)
  * Rozprowadzenie napięcia
    * [Płytka zasilająca - ABC](https://abc-rc.pl/product-pol-4741-Plytka-zasilajaca-ESC-100A-CRIUS-v1-0-plytka-dystrybucji-pradu-do-drona.html)
  * Stabilizatory 5V 9V 3.3V
    * [9V - BOTLAND](https://botland.com.pl/pl/regulatory-napiecia/1902-stabilizator-9v-l7809cv-tht-to220.html)
    * [5V - BOTLAND](https://botland.com.pl/pl/regulatory-napiecia/3092-stabilizator-5v-l7805cv-tht-to220.html)
    * [3.3V -BOTLAND](https://botland.com.pl/pl/regulatory-napiecia/7685-stabilizator-ldo-33v-ld1117v33-tht-to220.html)
    * [Radiatory - BOTLAND](https://botland.com.pl/pl/radiatory/1338-radiator-rad04-9x9x5-mm.html)
  * Przewody:
    * [Przewód silikonowy miedziany ocynowany - czerwony - ABC](https://abc-rc.pl/product-pol-4851-Przewod-silikonowy-miedziany-ocynowany-20AWG-100-zyl-0-5mm2-czerwony-elastyczny.html)
    * [Przewód silikonowy miedziany ocynowany - czarny - ABC](https://abc-rc.pl/product-pol-4852-Przewod-silikonowy-miedziany-ocynowany-20AWG-100-zyl-0-5mm2-czarny-elastyczny.html)
 * Dioda oświetleniowa
   * [Lampa LED 12V 1,5W - ABC](https://abc-rc.pl/product-pol-7335-Lampa-LED-12V-1-5W-samoprzylepna-lampa-do-dronow.html)
   * [Moduł przekaźnika - ABC](https://abc-rc.pl/product-pol-12107-Modul-przekaznika-1-kanal-5V-10A-250V-modul-przekaznikowy.html)
 * Czujniki i akcesoria do czujników:
   * [Uchwyt czujnika HC-SR04 - ABC](https://abc-rc.pl/product-pol-7320-Uchwyt-czujnika-HC-SR04-mocowanie-czujnika-SR04.html)
   * [Woltomierz - ABC](https://abc-rc.pl/product-pol-6306-Woltomierz-DC-3-30V-0-36-LED-czerwony-bez-obudowy.html)
   * [Wyłącznik krańcowy WK615 - dźwignia 55mm - ABC](https://abc-rc.pl/product-pol-9842-Wylacznik-krancowy-WK615-dzwignia-55mm.html)
   * [Uchwyt serwa - ABC](https://abc-rc.pl/product-pol-7542-Mocowanie-serwa-9g-SG90-ramka-plexi-36x35-srubki.html)

* Narzędzia
  * [Pistolet do kleju na gorąco - ABC](https://abc-rc.pl/product-pol-11945-Pistolet-do-kleju-na-goraco-110-240V-40W-Glue-Gun.html)
  * [Klej - ABC](https://abc-rc.pl/product-pol-11946-Klej-do-pistoletu-na-goraco-16x1-1cm-klej-do-klejenia-na-goraco-przezroczysty.html)
  
* INNE:  
  * [Złącza ARK 2 pin - ABC](https://abc-rc.pl/product-pol-11824-Zlacze-ARK-2PIN-raster-5mm-do-zalutowania-druku-10szt.html)
  * [Złącze kołkowe 4 piny - ABC](https://abc-rc.pl/product-pol-5430-Gniazdo-kolkowe-2-54mm-4-piny-10-szt-zenskie-do-ukladow-elektronicznych.html?rec=101002206)
  * [Złącze kołkowe 2 piny - ABC](https://abc-rc.pl/product-pol-5428-Gniazdo-kolkowe-2-54mm-2-piny-10-szt-zenskie-do-ukladow-elektronicznych.html?rec=101002203)
  * []()
  * [Płytka stykowa 830 - ABC](https://abc-rc.pl/product-pol-6204-Plytka-stykowa-830-do-Arduino-MB-102-prototypowa.html)
  * [Płytka stykowa 170 - ABC](https://abc-rc.pl/product-pol-6296-Plytka-stykowa-170-pol-SYB-170-1-szt-budowa-prototypow-Arduino.html)
  * [Płytka stykowa 400 - ABC](https://abc-rc.pl/product-pol-6203-Plytka-stykowa-400-pol-MR200-001-uniwersalna-plytka-stykowa.html)
  * [Podstawka plexi pod Arduino UNO - ABC](https://abc-rc.pl/product-pol-8100-Podstawka-plexi-pod-Arduino-UNO-R3-budowa-prototypow.html)
  * [Przewody kable zworki 40 szt 20cm - żeńsko-żeńskie - ABC](https://abc-rc.pl/product-pol-8808-Przewody-kable-zworki-40-szt-20cm-zensko-zenskie.html)
  * [Przewody kable zworki 40 szt 20cm - męsko-żeńskie - ABC](https://abc-rc.pl/product-pol-8761-Przewody-kable-zworki-40-szt-20cm-mesko-zenskie.html)
  * [Podstawka do LCD - ABC](https://abc-rc.pl/product-pol-9790-Podstawka-do-wyswietlacza-LCD-1602-uchwyt-obudowa.html)
  * [Karta survivalowa - ABC](https://abc-rc.pl/product-pol-8201-Karta-przezycia-SURVIVAL-CARD.html)
  * [Moduł RFID](https://abc-rc.pl/product-pol-6410-Modul-czytnika-RFID-RC522-13-56MHz-karta-brelok-Arduino.html)
  * [Listwa goldpin prosta - ABC](https://abc-rc.pl/product-pol-6349-Listwa-kolkowa-2-54mm-40-pinow-10-szt-goldpin-do-ukladow-elektronicznych.html)
  * [Listwa goldpin kątowa - ABC](https://abc-rc.pl/product-pol-5433-Listwa-kolkowa-2-54mm-katowa-20-pinow-10-szt-goldpin-do-ukladow-elektronicznych.html)



