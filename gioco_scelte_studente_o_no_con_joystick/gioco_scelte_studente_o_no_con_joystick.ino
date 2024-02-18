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
int vittoria = 0;
int perso = 0;



LiquidCrystal lcd(11, 10, 5, 4, 3, 2); //iniziallizziamo i pin sulle porte scelte
int i;

void setup() {
  lcd.begin(16, 2); //definisce il numero di caratteri per riga ed il numero di righe da gestire
  Serial.begin(9600);

}

void loop() {
  lcd.setCursor(3, 0); //le righe e le colonne partono da 0;
  lcd.print("Studente?");
  lcd.setCursor(0,1);
  lcd.print("No");
  lcd.setCursor(14,1);
  lcd.print("Si");
  Serial.println(analogRead(pos_x));
  for(i = 15; i >= 0; i--){
    if(i < 10){
      lcd.setCursor(14,0);
      lcd.print(" ");
      lcd.setCursor(15, 0);
      lcd.print(i);
      
    }else{
      lcd.setCursor(14, 0);
      lcd.print(i);
    }
    if(analogRead(pos_x) > 950 && analogRead(pos_x) < 1023){
      lcd.clear();
      lcd.setCursor(3, 0); //le righe e le colonne partono da 0;
      lcd.print("Studente?");
      lcd.setCursor(4,1);
      lcd.print("Ottimo!");
      delay(3000);
      lcd.clear();
      lcd.setCursor(3, 0); //le righe e le colonne partono da 0;
      lcd.print("Studente?");
      vittoria++;
      break;
  }
  if(analogRead(pos_x) > 0 && analogRead(pos_x) < 200){
      lcd.clear();
      lcd.setCursor(3, 0); //le righe e le colonne partono da 0;
      lcd.print("Studente?");
      lcd.setCursor(4,1);
      lcd.print("Peccato");
      delay(3000);
      lcd.clear();
      lcd.setCursor(3, 0); //le righe e le colonne partono da 0;
      lcd.print("Studente?");
      perso++;
      break;
  }
    delay(1000);
 }
  if(vittoria > 0){
    lcd.clear();
    lcd.setCursor(2,0);
    lcd.print("Complimenti!");
    delay(10000);
    lcd.clear();
    vittoria = 0;
  }
  else if(perso > 0){
    lcd.clear();
    lcd.setCursor(5,0);
    lcd.print("Studia");
    delay(10000);
    lcd.clear();
    perso = 0;
  }
  else{
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("Tempo scaduto!");
    delay(10000);
    lcd.clear();
  }
  
for(i = 0; i < 50; i++){
  lcd.clear(),
  lcd.setCursor(2,0);
  lcd.print("Ricominciamo");
  lcd.setCursor(0,1);
  lcd.print("No");
  lcd.setCursor(14,1);
  lcd.print("Si");
  if(analogRead(pos_x) > 0 && analogRead(pos_x) < 200){
      lcd.clear();
      lcd.setCursor(2,0);
      lcd.print("Ricominciamo");
      lcd.setCursor(7, 1); //le righe e le colonne partono da 0;
      lcd.print("CIA");
      delay(5000);
      lcd.clear();
      lcd.setCursor(4,0);
      lcd.print("Programm");
      lcd.setCursor(3,1);
      lcd.print("By Camillo");
      delay(100000);
      break;
  }
  else if(analogRead(pos_x) > 950 && analogRead(pos_x) < 1023){
    lcd.clear();
    lcd.setCursor(2,0);
    lcd.print("Ricominciamo");
    lcd.setCursor(6, 1); //le righe e le colonne partono da 0;
    lcd.print("NAMO");
    delay(3000);
    lcd.clear();
    break;
  }
  delay(1000);
}

}













