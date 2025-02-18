//switch one pin connected to ground and other to the switchPin
const int switchPin = 10;
const int buzzerPin = 7;

void setup(){
    pinMode( buzzerPin, OUTPUT );
    pinMode( switchPin, INPUT_PULLUP );
    Serial.begin( 9600 );
}

void loop(){
    int value;
    
    value = digitalRead( switchPin );
    Serial.println( value );
    if(value == 1){
      turnOnBuzzer();
    }else if(value == 0){
      turnOffBuzzer(); 
    }
    delay( 1000 );
}

void turnOnBuzzer(){
  digitalWrite( buzzerPin, HIGH );
}

void turnOffBuzzer(){
  digitalWrite( buzzerPin, LOW );
}
