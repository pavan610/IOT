int shockPin = 11;
void setup() {
  // put your setup code here, to run once:
  pinMode(shockPin,OUTPUT);
}

void loop() {
  turnShockOn();
  delay(1000);
  turnShockOff();
  delay(3000);
}

void turnShockOn(){
    digitalWrite(shockPin,HIGH); 
}

void turnShockOff(){
    digitalWrite(shockPin,LOW); 
}
