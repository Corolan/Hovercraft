Szanowny Panie Doktorze,
Pomysł z poduszkowcem jakoś szczególnie utkwił mi w głowie i zacząłem się nad tym głebiej zastanawiać.
Poniżej zamieszczam efekty tych przemyśleń. Wybrałem wstępną listę części, które, wydaje mi się, byłyby odpowiednie do tego projektu. Mam kilka przemyśleń na temat konstrukcji mechanicznej oraz elektrycznej modułu. Załączam również wstępny schemat urządzeń (bardzo wstępny, nie uwzględniłem na nim póki co chociażby kondensatorów przy stabilizatorach).

Czy taki projekt ma rację bytu?

## Pomysły i uwagi
  * Wstępny pomysł: użycie Arduino jako kontrolera - stosunkowa prostota, jedyne ograniczenie to brak możliwości użycia kamery. Arduino już trochę znam i byłoby prościej zmontować konstrukcję w oparciu o właśnie ten kontroler
  * Lekka rama -> drewno balsa
    * Dwa poziomy: pokład głowny i podpokład z elektroniką - ciąg powietrza zapewni chłodzenie
  * Fartuch z lekkiego i nieprzewiewnego materiału 
  * Dwa silniki do napełnienie poduszki -> Kanały sterownika (dwie dmuchawy sterowane jednym sygnałem - prądowo bez problemu)
  * Silnik napędowy
    * Zamocowany na seromechaniźmie -> ster kierunku
  * Woltomierz przy akumulatorach -> kontrola rozładowania ogniw
  * Łączność za pomocą modułu Bluetooth - łatwość nadawania/odbierania danych, względna prostota zbudowania aplikacji mobilnej do zdalnego sterowania
  * Do głownej linii zasilania podłączyć woltomierz by na bierząco sprawdzać napięcie na akumulatorze -> zapobieganie nadmiernemu rozładowaniu
  * Dołozyć wyświetlacz tekstowy LCD -> do debugu lub wyświetlania danych?


## Komentarz
  * W fazie prototypu układ będzie oczywiście złożony na płytce prototypowej, ale do realizacji myślę że warto byłoby przygotować płytki PCB (ponieważ będą to stosunkowo proste układy, mógłbym wytrawić płytki własnoręcznie)
  * Można by dodać fotorezystory na dwóch stronach pojazdu -> funkcja podążania za światłem?
  * Dodać wskaźnik załączenia prądu (LED 5V przy zasilaniu?).
  * Czy wybrane śmigło zapewni wystarczający ciąg poziomy?
  * Czy dmuchawy zapewnią wystarczający ciąg pionowy?
  * Bardziej skupić się na autonomiczności (czujniki, algorytmy poruszania się), czy na zdalnym sterowaniu - kamera, streaming obrazu-> zmiana kontrolera na Raspberry PI


## Proponowane części

* Mechanika:
  * Konstrukcja kadłuba
    * [Balsa - ABC](https://abc-rc.pl/product-pol-2139-Balsa-Modelarska-3-0-mm-srednia-I-klasa.html)

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

* Zasilanie:
  * Akumulator Li-Pol:
    * [Akumulator Tattu 1300mAh 3S 75C - ABC](https://abc-rc.pl/product-pol-6659-Akumulator-Tattu-1300mAh-3S-75C-Li-pol-Gens-Ace-11-1V.html)
  * Rozprowadzenie napięcia
    * [Płytka zasilająca - ABC](https://abc-rc.pl/product-pol-4741-Plytka-zasilajaca-ESC-100A-CRIUS-v1-0-plytka-dystrybucji-pradu-do-drona.html)
  * Stabilizatory 5V 9V 3.3V
    * [9V - BOTLAND](https://botland.com.pl/pl/regulatory-napiecia/1902-stabilizator-9v-l7809cv-tht-to220.html)
    * [5V - BOTLAND](https://botland.com.pl/pl/regulatory-napiecia/3092-stabilizator-5v-l7805cv-tht-to220.html)
    * [3.3V -BOTLAND](https://botland.com.pl/pl/regulatory-napiecia/7685-stabilizator-ldo-33v-ld1117v33-tht-to220.html)
 * Dioda oświetleniowa
   * [Lampa LED 12V 1,5W - ABC](https://abc-rc.pl/product-pol-7335-Lampa-LED-12V-1-5W-samoprzylepna-lampa-do-dronow.html)
   * [Moduł przekaźnika - ABC](https://abc-rc.pl/product-pol-12107-Modul-przekaznika-1-kanal-5V-10A-250V-modul-przekaznikowy.html)
 
* Czujniki i akcesoria do czujników:
   * [Czujnik HC-SR04 - ultradźwiękowy pomiar odległości](https://abc-rc.pl/product-pol-6231-Czujnik-HC-SR04-ultradzwiekowy-pomiar-odleglosci-2-400-cm.html)
   * [Uchwyt czujnika HC-SR04 - ABC](https://abc-rc.pl/product-pol-7320-Uchwyt-czujnika-HC-SR04-mocowanie-czujnika-SR04.html)
   * [Woltomierz - ABC](https://abc-rc.pl/product-pol-6306-Woltomierz-DC-3-30V-0-36-LED-czerwony-bez-obudowy.html)
   * [Wyłącznik krańcowy WK615 - dźwignia 55mm - ABC](https://abc-rc.pl/product-pol-9842-Wylacznik-krancowy-WK615-dzwignia-55mm.html)

  




