#include <FirebaseArduino.h>
#include <ESP8266WiFi.h>
#include "DHT.h" 
#include <Servo.h>
//--------------------------------------------------------
//setup de dht
#define DHTTYPE DHT11
#define dht_dpin 2
DHT dht(dht_dpin, DHTTYPE); 
//--------------------------------------------------------
//setup de firebase
#define WIFI_SSID ""
#define WIFI_PASSWORD ""
#define FIREBASE_HOST "" //ya lo debemos tener guardado
#define FIREBASE_AUTH "" //que previamente ya habíamos guardado

//--------------------------------------------------------
//delcaro las variables que estaré usando
int Red_LED = 14; //pin d8 es mi luz que estará funcionando con el botón
#define turn_On 0
#define turn_Off 1

int Status = 12;  // Digital pin D6 es el led correspondiente al sensor
int sensor = 13;  // Digital pin D7 es mi sensor de movilidad

void setup() {
//hago el setup de mi servo
servo.attach(2); //D4
servo.write(0);
delay(2000);
  //declaro la informacion que estare recibiendo de mi sensor
   pinMode(sensor, INPUT);   // declare sensor as input
 //declaro el pin de los leds que estare usando
  pinMode(Status, OUTPUT);  // declare LED as output
  pinMode(Red_LED, OUTPUT);
//--------------------------------------------------------
//empezar el stup del dht
  dht.begin();
  Serial.begin(9600);
  Serial.println("Humidity and temperature\n\n");
//--------------------------------------------------------
//setup de firebase
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

void loop() {}
//--------------------------------------------------------
//nuestro led que se actualizara con el boton
  int ledStatus = Firebase.getInt("ledStatus");
  Serial.println(ledStatus);
      if(ledStatus == 1){
        Serial.println("hola");
          digitalWrite(Red_LED, turn_On);
     } else {
      digitalWrite(Red_LED, turn_Off);     
    }
//--------------------------------------------------------
//nuestro servo que se estara moviendo con el boton
  int ledStatus = Firebase.getInt("grados");
  Serial.println("grados:");
  Serial.println(grados);
      if(grados == 90){              
              servo.write(0); 
      } else {
              servo.write(90);  
    }
//--------------------------------------------------------
// nuestra informacion de temperatura y humedad
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
//--------------------------------------------------------
       //nuestra informacion del sensor PIR
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

