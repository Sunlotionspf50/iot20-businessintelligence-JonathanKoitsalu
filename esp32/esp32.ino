#include <WiFi.h>

#include <AzureIoTHub.h>
#include <AzureIoTProtocol_MQTT.h>
#include <AzureIoTUtility.h>
#include <DHT.h>
#include <ArduinoJson.h> //Bibliotek Nedgraderat till 5.13.5

#define DHT_TYPE DHT11
#define DHT_PIN 14

//instanser initieras:

DHT dht(DHT_PIN, DHT_TYPE);
IOTHUB_CLIENT_LL_HANDLE deviceClient;


char *ssid = "MORMOR";
char *pass = "skansbergsvagen";
char *conn= "HostName=iot20-JonathanKoitsalu.azure-devices.net;DeviceId=esp32;SharedAccessKey=ArpwI7AH3RW87FZiJV9x4VjhelUu2TxP/TytU6NhsN4=";

bool messagePending = false;

float latestTemperature = 0;
float latestHumidity = 0;

int interval = 1000;
unsigned long prevMillis = 0;
time_t epochTime;

void setup() {
  initSerial();
  initWifi();
  initEpochTime();
  initDHT();
  initDevice();
  

}

void loop() {

//Bygga ihop meddelandet om meddelande inte skickas just nu.

  unsigned long currentMillis = millis();
  
  if(!messagePending){
    if((currentMillis - prevMillis) >= interval){
      prevMillis = currentMillis;

      epochTime = time(NULL);                         //Ger epochTime med time-funktionen som initialiserades med initEpochTime.
      
      //Serial.printf("Current time: %lu - ", epochTime);

      //skapa json-meddelandet.
                
      float temperature = dht.readTemperature();
      float humidity = dht.readHumidity();
      
      if(!std::isnan(temperature) && !std::isnan(humidity) && (abs(temperature-latestTemperature)>1 || abs(humidity-latestHumidity)>1)){ //kolla så att datat inte är nan samt att data hunnit ändra sig med en grad eller humidity.

        latestTemperature = temperature;
        latestHumidity = humidity;
        
        char payload[256];
        
        StaticJsonBuffer<sizeof(payload)> buf;
        JsonObject &root = buf.createObject();
        root["deviceId"] = "esp32";
        root["ts"] = epochTime;
        root["temp"] = temperature;
        root["hum"] = humidity;
        root.printTo(payload, sizeof(payload));
                    
        sendMessage(payload);      
      }


    }

  }

  IoTHubClient_LL_DoWork(deviceClient);
  delay(10);
}
