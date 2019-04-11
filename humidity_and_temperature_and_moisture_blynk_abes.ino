#define BLYNK_PRINT Serial
#include <ESP8266_Lib.h>//for wifi module
#include <BlynkSimpleShieldEsp8266.h>//for blynk api
#include <SimpleTimer.h>;//for interupts 
#include <DHT.h>;


char auth[] = "bf34529893f04cbbbe961ede047d2816";//generated from bylnk , for this project 
char ssid[] = "sid v11";//wifi credentials
char pass[] = "sidking007";
int moisture=0;//in int so that analog values can be typecasted
float h,t;//data will be given through datapins so float value

#define mois A0//moisture data rendered from a0 pin to variable mois
#define DHTPIN 2 //2nd pin of arduino data stored in dhtpin variable
#define DHTTYPE DHT11//dht11 type variable is dhttype
DHT dht(DHTPIN, DHTTYPE);//passing values to dht method that data is coming from pin 2 and type of data is dht11

SimpleTimer timer;//object of sleeptimer class 
//baud rate. A number related to the speed of data transmission in a system.
//The rate indicates the number of electrical oscillations per second that occurs within a data transmission. The higher the baud rate, the more bits per second that are transferred.
#define ESP8266_BAUD 115200 //default speed of transmission is 115200

ESP8266 wifi(&Serial);//giving address of serial to wifi method 

int moisture1=0;//temp variable for storing moisture

void setup()
{
 Serial.begin(ESP8266_BAUD);
 delay(10);
 Blynk.begin(auth, wifi, ssid, pass);
 timer.setInterval(1000L, sendSensor);/////////////////interrupt
}

void loop()
{
  
 Blynk.run();
 timer.run(); // Initiates SimpleTimer
 //delay(500);
} 



void sendSensor()
{
 moisture=analogRead(mois);//typecast analog reading to int
 moisture=1023-moisture;//the value fetched are in reverse range thus converting them 
 moisture1=moisture/10.2;//to give moisture in a percent range from 1 to 100
 h = dht.readHumidity();
 t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
 if (isnan(h) || isnan(t)) //isnan means is null
 {
  Serial.println("Failed to read from DHT sensor!");
  return;
 }
 Blynk.virtualWrite(V5, h); // Humidity for gauge
 Blynk.virtualWrite(V6, t); // Temperature for gauge
 Blynk.virtualWrite(V7, moisture1); // Temperature for gauge 
}
