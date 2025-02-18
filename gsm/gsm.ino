#include <SoftwareSerial.h>

int sim900aRX=8,sim900aTX=9;

SoftwareSerial SIM900A(sim900aRX,sim900aTX);
String phoneNumber = "+918328626141";
char c = ' ';
void setup() 
{
  Serial.begin(9600);
  while(!Serial);
  Serial.println("Arduino is ready");
  SIM900A.begin(9600);
//  while(!sendCommand("AT",5,"OK")){}
  Serial.println("SIM900A started at BaudRate 9600");
  delay(1000);
  Serial.println("Setup Complete! SIM900A is Ready!");
}
void loop()
{
  // Keep reading from SIM800 and send to Arduino Serial Monitor
  if (SIM900A.available())
  { c = SIM900A.read();
  Serial.write(c);}
  // Keep reading from Arduino Serial Monitor and send to SIM900A
  if (Serial.available())
  { c = Serial.read();
  SIM900A.write(c); 
  }
}
 void SendMessage()
{
  Serial.println ("Sending Message");
  SIM900A.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);
  Serial.println ("Setting SMS Number");
  SIM900A.println("AT+CMGS=\"" + phoneNumber + "\"\r"); //Mobile phone number to send message
  delay(1000);
  Serial.println ("Setting SMS Content");
  SIM900A.println("Emergency...\nLocation : ");// Messsage content
  delay(100);
  Serial.println ("Finish");
  SIM900A.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
  Serial.println ("Message has been sent.");
}


bool sendCommand(String command, int maxTime, char readReplay[]) {
  bool found = false;
  int countTimeCommand = 0;
  while(countTimeCommand < (maxTime*1))
  {
    SIM900A.println(command);//at+cipsend
    Serial.write(".");
    if(SIM900A.find(readReplay))//ok
    {
      found = true;
      break;
    }
  
    countTimeCommand++;
  }
  
  if(found == true)
  {
    Serial.println(" OK");
  }else{
    Serial.println(" Fail");
  }
  return found;
 }
