#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
 
// Set these to run example.
#define FIREBASE_HOST "m-project-153545896388.firebaseio.com"
#define FIREBASE_AUTH "o1gefWJBrUvsyOJ45uy3HDUbYUoRaFp9lMhZxc"
#define WIFI_SSID "XXX"
#define WIFI_PASSWORD "XXXX4"



#define AC D1
#define WINDOW D2
#define ALARM D3
#define Battery D5
#define Fuel D6
#define Temp A0


String ac,window,alarm; 
int battery,fuel,temp;




void setup() {
Serial.begin(9600);
pinMode(AC, OUTPUT);
pinMode(WINDOW, OUTPUT);
pinMode(ALARM, OUTPUT);
pinMode(Battery, INPUT);
pinMode(Fuel, INPUT);
pinMode(Temp, INPUT);



// connect to wifi.
WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
Serial.print("connecting");
while (WiFi.status() != WL_CONNECTED) {
Serial.print(".");
delay(500);
}
Serial.println();
Serial.print("connected: ");
Serial.println(WiFi.localIP());
Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
//Firebase.set("LED_STATUS", 0);
}

void loop() {
// get value
ac = Firebase.getString("8689922709/123/AC");
window = Firebase.getString("8689922709/123/Window");
alarm = Firebase.getString("8689922709/123/Alarm");



Sensors();
//////////////////////////////
Ac();
///////////////////////////////
Window();
///////////////////////////////
Alarm();
////////////////////////////////
delay(10);  
}


void Ac(){
    if (ac == "ON") {
    Serial.println("AC ON");
    digitalWrite(AC,HIGH);
    }
    else if(ac == "OFF") {
    Serial.println("AC OFF");
    digitalWrite(AC,LOW);
    }
    Sensors();

 }

void Window(){
    if(window == "OPEN") {
    Serial.println("WINDOW OPEN");
    digitalWrite(WINDOW,HIGH);
    }
    else if(window == "CLOSED") {
    Serial.println("WINDOW CLOSED");
    digitalWrite(WINDOW,LOW);
    }
    Sensors();

 }

  void Alarm(){
    if(alarm == "ON") {
    Serial.println("ALARM ON");
    digitalWrite(ALARM,HIGH);
    }
    else if(alarm == "OFF") {
    Serial.println("ALARM OFF");
    digitalWrite(ALARM,LOW);
    }
    Sensors();

 }

 void Sensors(){
   Firebase.set("8689922709/123/Temp", analogRead(Temp));  
 }
