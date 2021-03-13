#include <Adafruit_Sensor.h>
#include <DHT.h>

#define DHT_PIN 14
#define DHT_TYPE DHT11

static DHT dht(DHT_PIN, DHT_TYPE);

void setup(){
  Serial.begin(115200);
  dht.begin();
}

void loop(){
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

Serial.print("Temperature: ");
Serial.print(temperature);
Serial.print(", Humidity: ");
Serial.println(humidity);

delay(500);
}
