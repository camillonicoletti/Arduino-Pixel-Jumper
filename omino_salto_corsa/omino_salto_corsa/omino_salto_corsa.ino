#include <LiquidCrystal.h>
/*
* LCD VSS (pin 1)
* LCD VDD (pin 2)
* LCD V0 (pin 3)
connesso a terra (gnd)
connesso all'alimentazione di 5 volt
connesso al polo intermedio di un potenziometro da 10 kohm i cui estremi
sono collegati, rispettivamente, a terra ed all'alimentazione da 5 volt
connesso alla porta 12 di Arduino
connesso a terra (gnd)
* LCD RS (pin 4)
* LCD R/W (pin 5)
* LCD Enable (pin 6) connesso alla porta 11
 * LCD D4 (pin 11)
 * LCD D5 (pin 12)
 * LCD D6 (pin 13)
 * LCD D7 (pin 14)
 * LCD BL-A (pin 15)  connesso all'alimentazione da 5 volt (o ad un interruttore collegato
                      all'alimentazione da 5 volt)
 * LCD BL-K (pin 16) connesso a terra (gnd)
 */

int bottone = 7;
int pos_x = 0;
int pos_y = 1;
int cont = 0;
//CORPO BRACCIA IN SU PIEDI IN SU 
byte customChar[10] = {
  B01110,
  B01010,
  B01110,
  B00100,
  B11111,
  B00100,
  B01010,
  B10001
};
//CORPO BRACCIA IN GIU PIEDI IN GIU
byte customChar2[10] = {
  B01110,
  B01010,
  B01110,
  B00100,
  B01110,
  B10101,
  B01010,
  B01010
};
//MODALITA JUMP TESTA + CORPO
byte customChar3[] = {
  B01110,
  B01010,
  B01110,
  B00101,
  B11111,
  B10100,
  B01010,
  B10010
};
//corpo senza testa
byte customChar4[] = {
  B00100,
  B00101,
  B11111,
  B10100,
  B01010,
  B10010,
  B00000,
  B00000
};
//testa
byte customChar5[] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B01110,
  B01010,
  B01110
};



LiquidCrystal lcd(11, 10, 5, 4, 3, 2); //iniziallizziamo i pin sulle porte scelte
int i;

void setup() {
  lcd.begin(16, 2); //definisce il numero di caratteri per riga ed il numero di righe da gestire
  Serial.begin(9600);

}
// problema fa saltare l'omino dopo un tot secondi
void loop() {

  for(i =0; i < 10000; i++){ // primo ciclo lo faccio muovere quindi faccio switchare le due immagini ogmi 400 ms
    lcd.createChar(0, customChar);
    lcd.setCursor(0,1);
    lcd.write(byte(0));
    lcd.createChar(1, customChar2);
    delay(400);
    lcd.setCursor(0,1);
    lcd.write(byte(1));
    delay(400);
    cont++;
    if(cont == 6){ //passati 6 secondi lo faccio saltare
      lcd.createChar(2, customChar3);
      lcd.setCursor(0,1);
      lcd.write(byte(2)); //cambio l'immagine con quella del salto
      delay(200);
      lcd.createChar(3, customChar4); //metto meta corpo giu
      lcd.setCursor(0,1);
      lcd.write(byte(3));
      lcd.createChar(4, customChar5); //metto la testa riga di sopra stessa colonna
      lcd.setCursor(0,0);
      lcd.write(byte(4));
      delay(200);
      lcd.createChar(2, customChar3);//stampo immagine totale del salto sulla riga di giu
      lcd.setCursor(0,0);
      lcd.write(byte(2));
      delay(100);
      lcd.createChar(2, customChar3); //stampo immaggine del salto sulla riga di su
      lcd.setCursor(0,0);
      lcd.write(byte(2));
      delay(100);
      for(i = 0; i < 30; i++){ //lo faccio correre ancora
        lcd.clear();
        lcd.createChar(0, customChar);
        lcd.setCursor(0,0);
        lcd.write(byte(0));
        lcd.createChar(1, customChar2);
        delay(400);
        lcd.setCursor(0,0);
        lcd.write(byte(1));
        delay(400);
        cont = 0;
      }
    }
  }
}
