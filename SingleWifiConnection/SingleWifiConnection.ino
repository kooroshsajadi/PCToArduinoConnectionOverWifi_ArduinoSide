#include <ESP8266WiFi.h>        // Include the Wi-Fi library

const char* ssid = "Test";
//DARANDE
//Kourosh         
const char* password = "Abc1234@$";
//-Sepahan 100%
//Abc1234@$
WiFiServer wifiServer(8080);   

void setup() {
  Serial.begin(115200);         
  delay(10);
  Serial.println('\n');
  
  WiFi.begin(ssid, password);            
  Serial.print("Connecting to ");
  Serial.print(ssid);
  Serial.println(" ...");
 
  int i = 0;
  while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
    delay(1000);
    Serial.print(++i); Serial.print(' ');
  }

  Serial.println('\n');
  Serial.println("Connection established!");  
  Serial.print("IP address:");
  Serial.print('\n');
  Serial.println(WiFi.localIP());// Send the IP address of the ESP8266 to the computer
  wifiServer.begin();
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  pinMode(14, OUTPUT);
  digitalWrite(14, LOW);
  pinMode(D1, OUTPUT);
  digitalWrite(D1, LOW);
}

void loop() {
  Serial.println(WiFi.localIP());
  WiFiClient client = wifiServer.available();
 
  if (client) {
    while (client.connected()) {
      String command;
      while (client.available() > 0) {
        char c = client.read();
        command += c;
      }
      if(command == "1on"){
        digitalWrite(LED_BUILTIN, LOW);
      }
      else if(command == "1off"){
        digitalWrite(LED_BUILTIN, HIGH);
      }
      else if(command == "2on"){
        digitalWrite(14, HIGH);
      }
      else if(command == "2off"){
        digitalWrite(14, LOW);
      }
      else if(command == "3on"){
        digitalWrite(D1, HIGH);
      }
      else if(command == "3off"){
        digitalWrite(D1, LOW);
      }
      
      delay(10);
    }
 
    client.stop();
    Serial.println("Client disconnected");
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(14, LOW);
    digitalWrite(D1, LOW);
  }  
}
