
#include "PinDefinitionsAndMore.h"
#include <IRremote.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(4, 5); // RX, TX

String voice="";
#define fan 8
#define light 7
#define curtains 10
#define AC 9
#define TV 12
#define Motor_Int1 2
#define Motor_Int2 6
/*=========================================Setup====================================================*/
void setup() {
// Open serial communications and wait for port to open:
Serial.begin(115200);
while (!Serial) {
    ; // wait for serial port to connect. Needed for Native USB only
  }

Serial.print(F("Ready to send IR signals at pin "));
Serial.println(IR_SEND_PIN);
IrSender.enableIROut(38);

mySerial.begin(9600);

pinMode(fan, OUTPUT);
pinMode(light, OUTPUT);
pinMode(curtains, OUTPUT);
pinMode(AC, OUTPUT);
pinMode(TV, OUTPUT);
pinMode(Motor_Int1, OUTPUT);
pinMode(Motor_Int2, OUTPUT);
}
/*===========================================================================*/


/*======================Channel Plus=============================*/
void ChannelPl(){
Serial.flush();
IrSender.sendNEC(0x00,0xE, 0);
delay(1000); 
}
/*======================Channel Minus=============================*/
 void ChannelMin(){
Serial.flush();
IrSender.sendNEC(0x00,0x1A, 0);
delay(1000);  
}
/*======================Volume Up=============================*/
 void VolUp(){
Serial.flush();
IrSender.sendNEC(0x00,0x1E, 0);
delay(1000); 
}
/*=======================Volume Down=============================*/
 void VolDwn(){
Serial.flush();
IrSender.sendNEC(0x00,0xA, 0);
delay(1000);  
}
/*======================Tv On==============================*/
void TvOn(){
Serial.flush();
IrSender.sendNEC(0x00,0x9, 0);
digitalWrite (TV, HIGH);
delay(1000);  
}
/*=====================Tv off===============================*/
void TvOff(){
Serial.flush();
IrSender.sendNEC(0x00,0x9, 0);
digitalWrite (TV, LOW);
delay(1000);  
}

/*==================================================*/
void AcOn(){
IrSender.sendNEC(0x00,0x3, 10);
digitalWrite (AC, HIGH);
}
void AcOff(){
IrSender.sendNEC(0x00,0x3, 10);
digitalWrite (AC, LOW);
}

/*==================================================*/
void allon() {
digitalWrite (fan, HIGH);
digitalWrite (light, HIGH);
digitalWrite (curtains, HIGH);
digitalWrite (AC, HIGH);
TvOn();
AcOn();
}
void alloff() {
digitalWrite (fan, LOW);
digitalWrite (light, LOW);
digitalWrite (curtains, LOW);
digitalWrite (AC, LOW);
TvOff();
AcOff();
}


void fanOn(){
digitalWrite (fan, HIGH);
}
void fanOff(){
digitalWrite (fan, LOW);
}
void lightOn(){
digitalWrite (light, HIGH);
}
void lightOff(){
digitalWrite (light, LOW);
}

void curtainsOn(){
digitalWrite (curtains, HIGH);
digitalWrite (Motor_Int1, LOW);
digitalWrite (Motor_Int2, HIGH);
delay(6000);
digitalWrite(Motor_Int1,LOW);
digitalWrite(Motor_Int2,LOW);
}

void curtainsOff(){
digitalWrite (curtains, LOW);
digitalWrite (Motor_Int1, HIGH);
digitalWrite (Motor_Int2, LOW);
delay(6000);
digitalWrite(Motor_Int1,LOW);
digitalWrite(Motor_Int2,LOW);
}


/*==============================================Loop==================================================*/
void loop() {    

  while (mySerial.available()){  //Check if there is an available byte to read
  delay(10);                   //Delay added to make thing stable
  char c = mySerial.read();      //Conduct a serial read
  if (c == '#') {break;}       //Exit the loop when the # is detected after the word
  voice += c; //Shorthand for voice = voice + c
  } 
  if (voice.length() > 0) {
    Serial.println(voice);
 
    if(voice =="channel forward" || voice =="channel Plus" || voice =="next channel" || voice =="channel up"){
        ChannelPl();
    }
    else if(voice =="channel backward" || voice =="channel -" || voice =="previous channel" || voice =="channel down"){
        ChannelMin();
    }
    else if(voice =="Volume Plus" || voice =="volume up"){
        VolUp();
    }
    else if(voice =="volume -" || voice =="volume down"){
        VolDwn();
    }
    else if(voice =="TV on"){
        TvOn();
    }
    else if(voice =="TV off"){
        TvOff();
    }
    
    
    if (voice == "on" || voice == "all on" || voice == "turn on everything")
    {
      allon() ;
    }
    else if (voice == "off" || voice == "all of" || voice == "turn off everything" )
    {
      alloff() ;
    }
    else if(voice =="fan" || voice =="fan on" || voice == "turn on the fan"){
      fanOn();
    }
    else if(voice =="fan off" || voice == "turn off the fan"){
      fanOff();
    }
    else if(voice == "light" || voice =="light on" || voice == "turn on the lights"){
      lightOn();
    }
    else if( voice == "light off" || voice == "turn off the lights"){
      lightOff();
    }
    else if(voice == "curtain" || voice =="open the curtain"){
      curtainsOn();
    }
    else if(voice == "close the curtain"){
      curtainsOff();
    }

    else if(voice == "turn on the AC" || voice == "AC on"){
     AcOn();
    }
    else if(voice =="   turn off the AC" || voice =="AC off"){
      AcOff (); 
    }
    
    voice=""; //Reset the variable after initiating
    
  }
}
