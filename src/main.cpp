#include <Arduino.h>
/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/

// Import required libraries
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"
#include "Secrets.h"    //all the secret stuff goes here such as ssid, passwords, etc.

#include <U8x8lib.h> // for the Heltec WiFi LoRa 32 builtin OLED
// the OLED used
U8X8_SSD1306_128X64_NONAME_SW_I2C u8x8(/* clock=*/SCL_OLED, /* data=*/SDA_OLED, /* reset=*/RST_OLED); //! this needs to be changed to enable Hardware I2C

// Replace with your network credentials
const char* ssid = SSID;
const char* password = PASSWORD;

// Set LED GPIO
const int ledPin = LED_BUILTIN;                //LED on pin 5 for the Wemos, pin 13 on the Feather.
// Stores LED state
String ledState;

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

// Replaces placeholder with LED state value
String processor(const String& var){
  Serial.println(var);
  if(var == "STATE"){
    if(digitalRead(ledPin)){
      ledState = "ON";
    }
    else{
      ledState = "OFF";
    }
    Serial.print(ledState);
    return ledState;
  }
  return String();
}
 
void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);

  u8x8.begin();                              // start the builtin OLED

  // Initialize SPIFFS
  if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.printf("Connecting to %s ..", ssid);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());

//   // Print ESP32 Local IP Address on OLED
  String WiFilocalIP = WiFi.localIP().toString();
//   //u8x8.setFont(u8x8_font_courB24_3x4_n);
//   u8x8.clearDisplay();
//   u8x8.draw1x2String(0, 0, (char *)WiFilocalIP.c_str()); // display the ip address assigned by the DHCP server on the OLED

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  
  // Route to load style.css file
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/style.css", "text/css");
  });

  // Route to set GPIO to HIGH
  server.on("/on", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(ledPin, HIGH);    
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  
  // Route to set GPIO to LOW
  server.on("/off", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(ledPin, LOW);    
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  // Start server
  server.begin();
}
 
void loop(){
  
}