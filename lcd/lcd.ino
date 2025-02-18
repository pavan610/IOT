#include <LiquidCrystal.h>

//  The circuit:
// * LCD RS pin to digital pin 12
// * LCD Enable pin to digital pin 11
// * LCD D4 pin to digital pin 5
// * LCD D5 pin to digital pin 4
// * LCD D6 pin to digital pin 3
// * LCD D7 pin to digital pin 2
// * LCD R/W pin to ground
// * LCD VSS pin to ground
// * LCD VCC pin to 5V
// * 10K resistor:
// * ends to +5V and ground
// * wiper to LCD VO pin (pin 3)

LiquidCrystal lcd(0, 1, 5, 4, 3, 2);

int contrast = 75;
void setup() {
  analogWrite(6,contrast);
  lcd.begin(16, 2);
  writeLcd("Helloworld");
  delay(1000);
  writeLcd("World");

}

void loop() {

}

void writeLcd(String message){
  
  lcd.clear();
  lcd.setCursor(0,0);
  
  for( int i=0 ; i < message.length() && i < 32 ; i++ ){
    lcd.write(message[i]);
    if(i==15){
     lcd.setCursor(0,1); 
    }
  }
  
}
