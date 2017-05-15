#define UART_BAUD 115200
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

const char *ssid = "OrchestriX";
const char *pw = "123456789";
IPAddress ip(192, 168, 0, 1);
IPAddress netmask(255, 255, 255, 0);
const int port = 80;

WiFiServer server(port);
WiFiClient client;

int askForDistance(char request[]){
  Serial.print(request);
  while(!Serial.available()) delay(10);
  return Serial.parseInt();
}

int askForLED(char request[]){
  Serial.print(request);
}

void setup() {

  delay(500);
  
  Serial.begin(UART_BAUD);

  WiFi.softAPConfig(ip, ip, netmask); 
  WiFi.softAP(ssid, pw);
  
  server.begin(); // start TCP server  
}


void loop() {

  if(!client.connected()) {
    client = server.available();
    return;
  }

  int numOfBytes = client.available();
  if(numOfBytes == 0) return;
  
  char request[numOfBytes + 1];
  for(int i = 0; i < numOfBytes; i++){
    request[i] = (char)client.read();
  }
  request[numOfBytes] = '\0';

  if(request[0] == '0') client.println(askForDistance(request));
  else askForLED(request);
}
