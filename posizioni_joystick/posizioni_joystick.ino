int bottone = 7;
int pos_x = 0;
int pos_y = 1;


void setup() {
  // put your setup code here, to run once:
  pinMode(bottone, INPUT);
  digitalWrite(bottone, HIGH);
  Serial.begin(9600);
}

void loop() {
  Serial.print("X: ");
  Serial.print(analogRead(pos_x));
  Serial.print("   Y: ");
  Serial.print(analogRead(pos_y));
  Serial.print("   Z: ");
  Serial.println(digitalRead(bottone));
  delay(250);

}
