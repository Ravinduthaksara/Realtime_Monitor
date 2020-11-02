#include <SimpleTimer.h>
#include <Wire.h>
#define BLYNK_PRINT Serial // Comment this out to disable prints and save space
#include <SPI.h>;
#include <ESP8266WiFi.h>;
#include <BlynkSimpleEsp8266.h>;
#include <DHT.h>;


//Analog pin to read the incoming analog value from different sensors.
#define analogpin         A0


int watersensor = D1;
int motor;
// You should get Autfine Blh Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "";
char pass[] = "";

#define DHTPIN 2 // What digital pin we're connected to

// Uncomment whatever type you're using!
#define DHTTYPE DHT11 // DHT 11
const int IN_A0 = A0;

DHT dht(DHTPIN, DHTTYPE);
SimpleTimer timer;

// This function sends Arduino's up time every second to Virtual Pin (5, 6, 7 &amp;amp;amp;amp;amp;amp; 8).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void sendSensor()
{
 float h = dht.readHumidity();
 float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

 if (isnan(h) || isnan(t)) {
 Serial.println("Failed to read from DHT sensor!");
 return;
 }
 // You can send any value at any time.
 // Please don't send more that 10 values per second.
 Blynk.virtualWrite(V5, h); // Humidity for gauge
 Blynk.virtualWrite(V6, t); // Temperature for gauge

}

void setup()
{
 Serial.begin(115200); // See the connection status in Serial Monitor
 Blynk.begin(auth, ssid, pass);

 dht.begin();

  pinMode(A0, INPUT);

 // Setup a function to be called every second
 timer.setInterval(1000L, sendSensor);
}

void loop()
{
 Blynk.run(); // Initiates Blynk
 timer.run(); // Initiates SimpleTimer
}
