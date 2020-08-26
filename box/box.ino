#include"TFT_eSPI.h"
TFT_eSPI tft;
#include <AtWiFi.h>

 
const char* ssid = "yet another wifi";
const char* password =  "iskam da polzvam tazi bezjichna mreja vednaga";

void setup() {
    tft.begin();
    tft.setRotation(3);
    tft.fillScreen(TFT_BLACK); 
    tft.setFreeFont(&FreeSansBoldOblique18pt7b);

    
    pinMode(WIO_BUZZER, OUTPUT);
 
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(2000);
 
    WiFi.begin(ssid, password);
 
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println("Connecting to WiFi..");
    }
    
    Serial.println("Connected to the WiFi network");
    Serial.print("IP Address: ");
    Serial.println (WiFi.localIP()); // prints out the device's IP address
    
}
 
 
void loop() {
    const uint16_t port = 1337; // Default port
    const char* host = "192.168.5.104";  // Target Server IP Address
 
    Serial.print("Connecting to ");
    Serial.println(host);
 
 WiFiClient client;
 
    if (!client.connect(host, port)) {
        Serial.println("Connection failed.");
        Serial.println("Waiting 5 seconds before retrying...");
        delay(5000);
        return;
    }
 client.print("gei"); 
 
    int maxloops = 0;
 
    while (!client.available() && maxloops < 1000) {
        maxloops++;
        delay(1); //delay 1 msec
    }
    if (client.available() > 0) {
        //read back one line from the server
        String line = client.readString();
        // Proceed various line-endings
        line.replace("\r\n", "\n");
        line.replace('\r', '\n');
        line.replace("\n", "\r\n");
        Serial.println(line);
        tft.drawString(line,0,120);

    } else {
        tft.drawString("No new messages",0,120);
    }
 
    Serial.println("Closing connection.");
    client.stop();
  
    delay(3600000);
}
