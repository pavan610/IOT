#include <TinyGPS++.h>
#include <SoftwareSerial.h>

static const int GPSRXPin = 12, GPSTXPin = 13;
static const uint32_t Baud = 9600;
TinyGPSPlus gps;
SoftwareSerial GPS( GPSRXPin, GPSTXPin );

void setup(){
  Serial.begin(9600);
  Serial.println("GPS Searching .... ");
  GPS.begin(Baud);
//  getLocation();
//  Serial.println(GPS.available());
  while(!GPS.available()){
    Serial.println("GPS Unavailable.....Trying Again");
    delay(1000);
  }
  getLocation();
}

void loop(){
}

String getLocation(){
  while(true){
   String url ="";
   float la,lo;
   int flag = 0;
    gps.encode(GPS.read());
      if (gps.location.isUpdated()){
        Serial.print("Latitude= "); 
        Serial.print(gps.location.lat(), 6);
        la = gps.location.lat();
        Serial.print(" Longitude= "); 
        Serial.println(gps.location.lng(), 6);
        lo = gps.location.lng();
        url = "https://www.google.com/maps/search/?api=1&query=" + String(la) + "," + String(lo);
        Serial.println(url);
        return url;
     } 
    url = "https://www.google.com/maps/search/?api=1&query=" + String(la) + "," + String(lo);
  }
}
