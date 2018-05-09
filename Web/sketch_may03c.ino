#include <FirebaseArduino.h>
#include <ESP8266WiFi.h>
#include "DHT.h" 
       
#define DHTTYPE DHT11
#define dht_dpin 2
DHT dht(dht_dpin, DHTTYPE); 

#define WIFI_SSID "INFINITUM193E79"
#define WIFI_PASSWORD "FA9B79DF0F"

#define FIREBASE_HOST "ejemploarduino-64e24.firebaseio.com" //ya lo debemos tener guardado
#define FIREBASE_AUTH "wmyOka6X9OGqoOAZ7KDoL7VLHXKwSPpYpoYwefCO" //que previamente ya habíamos guardado

int Red_LED = 14; //pin d8
#define turn_On 0
#define turn_Off 1

int Status = 12;  // Digital pin D6
int sensor = 13;  // Digital pin D7

void setup() {
    pinMode(sensor, INPUT);   // declare sensor as input
  pinMode(Status, OUTPUT);  // declare LED as output
  pinMode(Red_LED, OUTPUT);
  // put your setup code here, to run once:
  dht.begin();
  Serial.begin(9600);
  Serial.println("Humidity and temperature\n\n");
  
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
}

void loop() {

  int ledStatus = Firebase.getInt("ledStatus");
  Serial.println(ledStatus);
      if(ledStatus == 1){
        Serial.println("hola");
          digitalWrite(Red_LED, turn_On);
     } else {
      digitalWrite(Red_LED, turn_Off);     
    }

      float h = dht.readHumidity();
    float t = dht.readTemperature();
    Firebase.setFloat("humedad", h);     
    Firebase.setFloat("temperatura", t);     

    Serial.print("Current humidity = ");
    Serial.print(h);
    Serial.print("%  ");
    Serial.print("temperature = ");
    Serial.print(t); 
    Serial.println("C  ");
     delay(800);

      long state = digitalRead(sensor);
    if(state == HIGH) {
      digitalWrite (Status, HIGH);
      Serial.println("Motion detected!");
     Firebase.setFloat("cerca", 1);     

      delay(1000);
    }
    else {
      digitalWrite (Status, LOW);
      Serial.println("Motion absent!");
           Firebase.setFloat("cerca", 0 );     

      delay(1000);
      }

}

