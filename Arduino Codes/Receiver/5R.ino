#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define Relay 10
String TEXT="";
int counter=0;
char on[] = "Hello World";
char off[] = "Bye Dude";

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";

void setup() {
  //Serial.begin(9600);     // initialize serial monitor at 9,600 baud
  //delay(1000);            // pause
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {

  if (radio.available()) {
    char text[32] = "";
    radio.read(&text, sizeof(text));
    TEXT = text;
    //Serial.println(TEXT);
    int result = strcmp(text, on);
    //Serial.println(result);
    if(result==0){
      //digitalWrite(Relay, HIGH);
      counter-=1;
    }
    else{
      //digitalWrite(Relay, LOW);
      counter+=1;
    }
    
  }
  //Serial.println(counter);
  if (counter<0){
    counter = 0;
  }
  
  if (counter > 0){
    digitalWrite(Relay, LOW);
  }
  else{
  digitalWrite(Relay, HIGH);
  }
  //Serial.println(counter);
}
