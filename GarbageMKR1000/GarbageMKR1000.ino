#define _DISABLE_TLS_
// other includes goes here
#include <WiFi101.h>
#include <ThingerWifi101.h>

#define USERNAME "Dapaah"
#define DEVICE_ID "garbage"
#define DEVICE_CREDENTIAL "garbage"

#define SSID "DESKTOP-A5JGE9M 8393"
#define SSID_PASSWORD "7M7804/z"


// Baud rate for debug serial
#define SERIAL_DEBUG_BAUD   115200

ThingerWifi101 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);


int trigger_pin = 3;

int echo_pin = 2;

int led_pin = 4; 

int time;

int distance; 
int constant=40;
float value;

void setup() {
//Initialize serial and wait for port to open:
  Serial.begin(SERIAL_DEBUG_BAUD);
  

  
  pinMode (trigger_pin, OUTPUT); 

  pinMode (echo_pin, INPUT);

  pinMode (led_pin, OUTPUT);
  
  
  // configure wifi network
  thing.add_wifi(SSID, SSID_PASSWORD);

  

 
}

void loop() {

// ULTRASONIC SENSOR
    digitalWrite (trigger_pin, HIGH);

    delayMicroseconds (10);

    digitalWrite (trigger_pin, LOW);

    time = pulseIn (echo_pin, HIGH);

    distance = (time * 0.034) / 2;

    value = constant / distance;
    thing["distance"] >> outputValue(value);
    

  if (distance <= 10) 

        {

            

        Serial.println (distance);  
      
       

        digitalWrite (led_pin, HIGH);

    

        }

  else if(distance > 10) {

        
        Serial.println (distance); 
      

        digitalWrite (led_pin, LOW);
     

  } 

  
  thing.handle();

}
