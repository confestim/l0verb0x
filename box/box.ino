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
    tft.drawString("l0verb0x 0.1", 50, 120);
    delay(2000);
    tft.fillScreen(TFT_BLACK); 
    tft.setFreeFont(&FreeSansBoldOblique9pt7b);
    tft.drawString("Checking for new messages", 30, 120);

    pinMode(WIO_BUZZER, OUTPUT);
 
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(2000);
 
    WiFi.begin(ssid, password);
 
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println("Connecting to WiFi..");
    }

    tft.drawString("Connected to the Network [ok]", 0, 120);
    tft.fillScreen(TFT_BLACK); 
    Serial.println("Connected to the WiFi network");
    Serial.print("IP Address: ");
    Serial.println (WiFi.localIP()); // prints out the device's IP address
    
}
 
 
void loop() {
    const uint16_t port = 1337; // Default port
    const char* host = "192.168.5.104";  // Target Server IP Address

    tft.drawString("Connecting to server", 0, 120);
    tft.fillScreen(TFT_BLACK); 
    Serial.print("Connecting to ");
    Serial.println(host);
 
 WiFiClient client;
 
    if (!client.connect(host, port)) {
        tft.drawString("Connection failed, retrying...",0, 120);
        tft.fillScreen(TFT_BLACK); 
        Serial.println("Connection failed.");
        Serial.println("Waiting 20 seconds before retrying...");
        delay(20000);
        return;
    }
 client.print("Requesting message C: "); 
    tft.setFreeFont(&FreeSansBoldOblique18pt7b);
    tft.fillScreen(TFT_BLACK); 
    
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
        analogWrite(WIO_BUZZER, 4);
        tft.drawString("New Message!",0, 120);
        delay(2000);
        tft.fillScreen(TFT_BLACK); 
        analogWrite(WIO_BUZZER, 0);
        delay(1000);
        tft.drawString(line,0,120);
        delay(180000);

    } else {
        tft.drawString("No messages :C",0,120);
        tft.drawString("Check later ;)",0,180);
        delay(60000);
    }
 
    Serial.println("Closing connection.");
    client.stop();
  
    delay(3600000);
}
