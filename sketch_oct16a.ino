#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "vivo 2015";
const char* password = "12345678";
const char* mqttServer = "12346a39fgd895ea8ff270d162341db.s1.eu.hivemq.cloud"; 
const int mqttPort = 8883;
const char* mqttUser = "testaddress"; 
const char* mqttPassword = "4st33e4123@"; 
const char* topic = "test/message"; // Topic to publish to

WiFiClientSecure espClient; // Use WiFiClientSecure for SSL
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  
  Serial.println("Connected to WiFi");
  Serial.print("Local IP: ");
  Serial.println(WiFi.localIP());
  
  espClient.setInsecure(); // Use this for testing, but consider using a proper certificate
  client.setServer(mqttServer, mqttPort);
}

void loop() {
    if (!client.connected()) {
        Serial.print("Attempting MQTT connection...");
        String clientId = "ESP8266Client-"; // Use a unique client ID
        clientId += String(random(0xffff), HEX); // Generate a random ID
        if (client.connect(clientId.c_str(), mqttUser, mqttPassword)) {
            Serial.println("connected");
        } else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            delay(2000);
        }
    }

 // Generate a random number and publish it
    int randomNumber = random(0, 100); // Generate a random number between 0 and 99
    String message = String(randomNumber);
    client.publish(topic, message.c_str());
    Serial.print("Published message: ");
    Serial.println(message);
    
    delay(5000); // Delay for 5 seconds before publishing again
    client.loop();
    
    client.loop();
}
