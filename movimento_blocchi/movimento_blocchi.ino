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
int randNumber;
int randNumber2;
int randNumber3;
  // randomSeed() will then shuffle the random function.

int bottone = 7;
int pos_x = 0;
int pos_y = 1;
int cont = 0;
int i = 0;
int j = 15;
int k = 15;
int l = 15;
int contA = 0;
int contB = 0;
int contC = 0;

//blocco
byte customChar[] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};

LiquidCrystal lcd(11, 10, 5, 4, 3, 2); //iniziallizziamo i pin sulle porte scelte


void setup() {
  lcd.begin(16, 2); //definisce il numero di caratteri per riga ed il numero di righe da gestire
  Serial.begin(9600);
  randomSeed(millis());

}




void loop(){
  
   
  randNumber = random(1, 5);
  randNumber2 = random(1, 5);
  randNumber3 = random(1, 5);
  Serial.println(randNumber);
  Serial.println(randNumber2);
  Serial.println(randNumber3);
  movimentoblocchi(randNumber, randNumber2, randNumber3);
  lcd.clear();
  delay(300);



}


void movimentoblocchi(int a, int b, int c){
    lcd.createChar(1, customChar);
    j = 15;
    k = 15;
    l = 15;
    contB = 0;
    contC = 0;
    while(k!= 0-c){
        if(j != -1 -a){
          lcd.setCursor(j,1);
          lcd.write(byte(1));
          lcd.setCursor(j+a, 1);
          lcd.write(" ");
          j--;
        }
        contB++;
        if(contB >= a+5){
            if(l != -1 - b){
              lcd.setCursor(l,1);
              lcd.write(byte(1));
              lcd.setCursor(l+b, 1);
              lcd.write(" ");
              l--; 
            }
        }
        contC++;
        if(contC >= a+14){
            if(k != 0 - c){
              lcd.setCursor(k,1);
              lcd.write(byte(1));
              lcd.setCursor(k+c, 1);
              lcd.write(" ");
              k--; 
            }
        }
        delay(350);
    }  
}

































