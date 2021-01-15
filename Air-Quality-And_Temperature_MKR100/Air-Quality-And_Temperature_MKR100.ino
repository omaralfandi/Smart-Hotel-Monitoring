#define _DISABLE_TLS_
// other includes goes here
#include <WiFi101.h>
#include <ThingerWifi101.h>

#define USERNAME "Dapaah"
#define DEVICE_ID "dust"
#define DEVICE_CREDENTIAL "dustsensor"

#define SSID "DESKTOP-A5JGE9M 8393"
#define SSID_PASSWORD "7M7804/z"


// Baud rate for debug serial
#define SERIAL_DEBUG_BAUD   115200


int measurePin = A5;
unsigned int samplingTime = 280;
unsigned int deltaTime = 40;

unsigned int sleepTime = 9680;
float voMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;

float temp;

ThingerWifi101 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);



void setup() {
 Serial.begin(SERIAL_DEBUG_BAUD);
 
  // configure wifi network
  thing.add_wifi(SSID, SSID_PASSWORD);

}

void loop() {


  delayMicroseconds(samplingTime);

  voMeasured = analogRead(measurePin);

  delayMicroseconds(deltaTime);

  delayMicroseconds(sleepTime);

  calcVoltage = voMeasured*(5.0/1024);
  dustDensity = 0.17*calcVoltage-0.1;

  thing["dustDensity"] >> outputValue(dustDensity);

  //Temperature Sensor

  temp = (float)analogRead(A0) * 5.0 / 1024.0; //analogRead will read the voltage a the given pin
  temp = temp - 0.5;
  temp = temp / 0.01;
  /*

    The Arduino UNO stated more trustworthy temperature readings
    in Celsius. Comparing the UNO and MKR values, we found that
    the MKR gives too high temperature readings. To be precise,
    the MKR outputs values ​​that are 41,02476117 degrees Celsius
    higher. Therefore, we had to subtract this value from the
    measured value of the MKR and the TMP36 sensor.
  */
  temp = temp - 41.02476117;
  
  thing["temperature"] >> outputValue(temp);
  thing.handle();

}
