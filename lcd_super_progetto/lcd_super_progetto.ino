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
int stop = 0;

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
//le prime due sono le standard


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

//blocco
byte customChar6[] = {
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
int i;
int randNumber;
int randNumber2;
int randNumber3;
int j = 15;
int k = 15;
int l = 15;
int contA = 0;
int contB = 0;
int contC = 0;
int cont_salto = 0;
int temp = 0;
int cont_discesa = 0;
int block_1 = 0;
int block_2 = 0;
int cont_discesa_sbagliata = 0;
int temp2 = 0;
int score = 0;
int primo = 0;

void setup() {
  lcd.begin(16, 2); //definisce il numero di caratteri per riga ed il numero di righe da gestire
  Serial.begin(9600);
  randomSeed(millis());

}

void loop() {

//valuto il primo caso
  if(primo == 0){
    lcd.setCursor(5,0);
    lcd.print("START");
    delay(2000);
    lcd.clear();
     lcd.setCursor(8,0);
        lcd.print("SCORE"),
        lcd.setCursor(14,0);
        lcd.print(0);

  }
  //do i numeri random e faccio a botta di tre blocchi
  randNumber = random(1, 6);
  randNumber2 = random(1, 8);
  randNumber3 = random(1, 7);
  Serial.println(randNumber);
  Serial.println(randNumber2);
  Serial.println(randNumber3);
  movimentoblocchi(randNumber, randNumber2, randNumber3);
  //se uno ha perso stoppo il gioco
  if(stop == 1){
    delay(10000);
    lcd.noDisplay();
  }
}


void movimentoblocchi(int a, int b, int c){
    lcd.createChar(6, customChar6);
    j = 15;
    k = 15;
    l = 15;
    contB = 0;
    contC = 0;
    block_1 = 0;
    block_2 = 0;
    
    
    while(k!= -1-c){ // valuto il ciclo finche il terzo blocco si esaurisce di scorrere poi avro altti tre numeri in ingresso
      if(j == -1-a){
        j = -1-a-2;
      }
      if(l == -1 -b){
        l = -1-b-2;
      }
      
      cont_salto = 0;
      if((j == -1 || l == -1 || k == -1) && cont_salto == 0 && temp == 0){ //valuto la posizione se è uguale a quella dell'omino blocco il gioco
      stop = 1;
      lcd.clear();
      lcd.setCursor(3,1);
      lcd.print("SCORE: ");
      lcd.setCursor(10,1);
      lcd.print(score);
      lcd.setCursor(3, 0);
      lcd.print("GAME OVER");
      break;
        
      }
      
      if(analogRead(pos_y) > 0 && analogRead(pos_y) < 200){ //vedo se l'utente salta 
      cont_salto = salto();
      }
      if(cont_salto == 1){
        corsa_su();
        temp++;
        temp2++;
        
        if(j != -1 -a){ //mando avanti primo blocco
          lcd.setCursor(j,1);
          lcd.write(byte(6));
          lcd.setCursor(j+a, 1);
          lcd.write(" ");
          j--;
        }
        contB++;
        if(contB >= a+5){ //secondo blocco
            if(l != -1 - b){
              lcd.setCursor(l,1);
              lcd.write(byte(6));
              lcd.setCursor(l+b, 1);
              lcd.write(" ");
              l--; 
            }
        }
        contC++;
        if(contC >= a+14){ //terzo blocco
            if(k != -1 - c){
              lcd.setCursor(k,1);
              lcd.write(byte(6));
              lcd.setCursor(k+c, 1);
              lcd.write(" ");
              k--; 
            }
            }
            
        
        if(j > -1){ //vedo se l'utente salta prima del previsto
              cont_discesa_sbagliata = 1;
        }
        else if( l > -1 ){
              cont_discesa_sbagliata = 1 ;
        }
        else if(k > -1){
              cont_discesa_sbagliata = 1;

      }
      }
      else if (cont_discesa_sbagliata == 1 && j > -1 && l > -1 && k > -1 ){ //se salta prima del previsto ributto giu l'omino
        discesa();
        lcd.setCursor(0,0);
        lcd.write(" ");
        movimento_standard();
         if(j != -1 -a){
          lcd.setCursor(j,1);
          lcd.write(byte(6));
          lcd.setCursor(j+a, 1);
          lcd.write(" ");
          j--;
        }
        contB++;
        if(contB >= a+5){
            if(l != -1 - b){
              lcd.setCursor(l,1);
              lcd.write(byte(6));
              lcd.setCursor(l+b, 1);
              lcd.write(" ");
              l--; 
            }
        }
        contC++;
        if(contC >= a+14){
            if(k != -1 - c){
              lcd.setCursor(k,1);
              lcd.write(byte(6));
              lcd.setCursor(k+c, 1);
              lcd.write(" ");
              k--; 
            }
        }
        cont_discesa_sbagliata = 0;
        temp = 0;
        temp2 = 0;

      }
      else if(cont_salto == 0  &&temp != 0 && cont_discesa == 0){ //se salta bene lo lascio correre sui blocchi in riga 0
        corsa_su();
        if(j != -1 -a){
          lcd.setCursor(j,1);
          lcd.write(byte(6));
          lcd.setCursor(j+a, 1);
          lcd.write(" ");
          j--;
        }
        contB++;
        if(contB >= a+5){
            if(l != -1 - b){
              lcd.setCursor(l,1);
              lcd.write(byte(6));
              lcd.setCursor(l+b, 1);
              lcd.write(" ");
              l--; 
            }
        }
        contC++;
        if(contC >= a){
            if(k != -1 - c){
              lcd.setCursor(k,1);
              lcd.write(byte(6));
              lcd.setCursor(k+c, 1);
              lcd.write(" ");
              k--; 
            }
        }
        if(j == -1-a || l ==-1-b || k ==-1-c){
          cont_discesa = 1;
        }
        
        
      }
      
      else if(cont_discesa == 1){ //una volta che mando avanti i blocci calcolo con cont_discesa la fine del blocco e lo faccio scendere
        temp = 0;
        discesa();
        movimento_standard();
        if(j != -1 -a){
          lcd.setCursor(j,1);
          lcd.write(byte(6));
          lcd.setCursor(j+a, 1);
          lcd.write(" ");
          j--;
        }
        contB++;
        if(contB >= a+5){
            if(l != -1 - b){
              lcd.setCursor(l,1);
              lcd.write(byte(6));
              lcd.setCursor(l+b, 1);
              lcd.write(" ");
              l--; 
            }
        }
        contC++;
        if(contC >= a+14){
            if(k != -1 - c){
              lcd.setCursor(k,1);
              lcd.write(byte(6));
              lcd.setCursor(k+c, 1);
              lcd.write(" ");
              k--; 
            }
        }
        cont_discesa = 0;
        score++;//una volta che pè sceso posso aumentare lo score
        lcd.setCursor(8,0);
        lcd.print("SCORE"),
        lcd.setCursor(14,0);
        lcd.print(score);
        primo = 1;

      }
      else{
        temp = 0; // quesato è il caso piu easy perche mando avanti blocco e faccio muovere omino
        movimento_standard();
        if(j != -1 -a){
          lcd.setCursor(j,1);
          lcd.write(byte(6));
          lcd.setCursor(j+a, 1);
          lcd.write(" ");
          j--;
        }
        contB++;
        if(contB >= a+5){
            if(l != -1 - b){
              lcd.setCursor(l,1);
              lcd.write(byte(6));
              lcd.setCursor(l+b, 1);
              lcd.write(" ");
              l--; 
            }
        }
        contC++;
        if(contC >= a+14){
            if(k != -1 - c){
              lcd.setCursor(k,1);
              lcd.write(byte(6));
              lcd.setCursor(k+c, 1);
              lcd.write(" ");
              k--; 
            }
        }
      }
      
        
        
    }  
}

int salto(){
  //if(analogRead(pos_y) > 0 && analogRead(pos_y) < 200){  //salto
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
      lcd.setCursor(0,1);
      lcd.write(" ");
      delay(400);
      return 1;
      
    }

//}



void movimento_standard(){ // movimento standard pvver quello che da l'idea che corre
  if(analogRead(pos_x) > 400 && analogRead(pos_x) < 650 && analogRead(pos_y) > 400 && analogRead(pos_y)< 650 ){//corsa giu
      lcd.createChar(0, customChar);
      lcd.setCursor(0,1);
      lcd.write(byte(0));
      lcd.createChar(1, customChar2);
      delay(300);
      lcd.setCursor(0,1);
      lcd.write(byte(1));
      delay(150);

    }
}


void discesa(){
  //inizio discesa
  lcd.createChar(4, customChar5);
  lcd.setCursor(0,0);
  lcd.write(byte(4));//metto testa su
  lcd.createChar(3, customChar4);
  lcd.setCursor(0,1);//corpo giu senza testa
  lcd.write(byte(3));
  delay(200);
  lcd.createChar(2, customChar3);
  lcd.setCursor(0,1);
  lcd.write(byte(2));
  delay(200);
  lcd.setCursor(0,1);
  lcd.createChar(0, customChar);
  lcd.write(byte(0));
  lcd.setCursor(0,0);
  lcd.write(" ");

}


void corsa_su(){ //movimento standard pero nella prima riga di sopra
  lcd.createChar(0, customChar);
  lcd.setCursor(0,0);
  lcd.write(byte(0));
  lcd.createChar(1, customChar2);
  delay(300);
  lcd.setCursor(0,0);
  lcd.write(byte(1));
  delay(150);
}










