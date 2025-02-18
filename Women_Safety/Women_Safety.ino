#include <LiquidCrystal.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

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

static const int GPSRXPin = 12, GPSTXPin = 13;
static const uint32_t Baud = 9600;
TinyGPSPlus gps;
SoftwareSerial GPS( GPSRXPin, GPSTXPin );


int sim900aRX=8,sim900aTX=9;
SoftwareSerial SIM900A(sim900aRX,sim900aTX);
String phoneNumber = "+918008918427";

//switch one pin connected to ground and other to the switchPin
const int switchPin = 10;
const int buzzerPin = 7;
const int shockPin = 11;

int switchValue = 0;
int flag = 0;

int contrast = 75;
void setup() {
  
  analogWrite(6,contrast);
  lcd.begin(16, 2);
  writeLcd("Connectiong to GSM Module");
  SIM900A.begin(9600);
  while(!sendCommand("AT",5,"OK")){
  }
  writeLcd("GSM Connected..");
  writeLcd("Searching GPS");
  delay(5000);
  GPS.begin(9600);
//  while(!GPS.available()){
//    writeLcd("GPS Unavailable.....Trying Again");
//    delay(1000);
//  }
   
  writeLcd("Found GPS");
  
  pinMode( buzzerPin, OUTPUT );
  pinMode( switchPin, INPUT_PULLUP );
  pinMode(shockPin,OUTPUT);

}

void loop() {
  
    switchValue = digitalRead( switchPin );
    
    if(switchValue == 1 && flag == 0 ){

      writeLcd("Women in Danger...Emergency.");
      turnShockOn();
      turnOnBuzzer();
      SendMessage();
      flag = 1;
      
    }else if(switchValue == 0){
      writeLcd("Women is Safe..");
      turnShockOff();
      turnOffBuzzer(); 
      flag = 0;
      
    }

}

void turnShockOn(){
    digitalWrite(shockPin,HIGH); 
}

void turnShockOff(){
    digitalWrite(shockPin,LOW); 
}

void turnOnBuzzer(){
  digitalWrite( buzzerPin, HIGH );
}

void turnOffBuzzer(){
  digitalWrite( buzzerPin, LOW );
}

void writeLcd(String message){

  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  
  for( int i=0 ; i < message.length() && i < 32 ; i++ ){
    lcd.write(message[i]);
    if(i==15){
     lcd.setCursor(0,1); 
    }
  }
  
}

String getLocation(){
  return "https://www.google.com/maps/search/?api=1&query=17.421518,78.5949549";
  while(true){
   String url ="";
   float la,lo;
   int flag = 0;
    gps.encode(GPS.read());
      if (gps.location.isUpdated()){
        writeLcd("Getting Location.");
//        Serial.print("Latitude= "); 
//        Serial.print(gps.location.lat(), 6);
        la = gps.location.lat();
//        Serial.print(" Longitude= "); 
//        Serial.println(gps.location.lng(), 6);
        lo = gps.location.lng();
        url = "https://www.google.com/maps/search/?api=1&query=" + String(la) + "," + String(lo);
//        Serial.println(url);
        writeLcd("Location Recieved.");
        return url;
     } 
    url = "https://www.google.com/maps/search/?api=1&query=" + String(la) + "," + String(lo);
  }
}



 void SendMessage()
{
  writeLcd ("Sending Message");
  SIM900A.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);
  writeLcd ("Setting SMS Number");
  SIM900A.println("AT+CMGS=\"" + phoneNumber + "\"\r"); //Mobile phone number to send message
  delay(1000);
  writeLcd ("Setting SMS Content");
  SIM900A.println("Emergency...\nLocation : "+getLocation());// Messsage content
  delay(100);
  writeLcd ("Finish");
  SIM900A.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
  writeLcd ("Message has been sent.");
}


bool sendCommand(String command, int maxTime, char readReplay[]) {
  bool found = false;
  int countTimeCommand = 0;
  while(countTimeCommand < (maxTime*1))
  {
    SIM900A.println(command);//at+cipsend
    if(SIM900A.find(readReplay))//ok
    {
      found = true;
      break;
    }
  
    countTimeCommand++;
  }
  return found;
 }
