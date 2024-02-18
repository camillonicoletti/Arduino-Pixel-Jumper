#include <stdio.h>
int ledpin = 13;
char arg = 0;
int def;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("ciao, digita un numero: ");
  pinMode(ledpin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()){
      arg = Serial.read();
      Serial.println(arg);
      if (arg == '3') {
        digitalWrite(ledpin, HIGH);
        delay(10000);
      }
      else{
        digitalWrite(ledpin, LOW);
        
      }
  }

}
