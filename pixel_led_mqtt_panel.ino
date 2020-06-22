#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#include <MD_MAX72xx.h>
#include <MD_Parola.h>
#include "wLedFont.h"

#include <PubSubClient.h>

///////////////////////////////
////    Settings block    /////
///////////////////////////////
  // Wifi settings //
const char* WIFI_ssid       = "your_wifi_network_name";
const char* WIFI_password   = "change_me";
  // OTA updates settings //
const char* OTA_hostname    = "wLed-panel-01";
const char* OTA_password    = "change_me";
  // MQTT settings //
const char* mqtt_server = "192.168.1.250";
const char* mqtt_user = "mqtt_user";
const char* mqtt_password = "change_me";
  // MQTT TOPIC PREFIX //
String TOPIC_PREFIX = "wled";

  // Parola display settings //
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW // type of device hardware https://majicdesigns.github.io/MD_MAX72XX/page_hardware.html
#define MAX_DEVICES  8                    // number of device segments
  // Display pinout //
#define DATA_PIN  D7                      // WeMos D1 mini GPIO13
#define CS_PIN    D6                      // WeMos D1 mini GPIO12
#define CLK_PIN   D5                      // WeMos D1 mini GPIO14

MD_Parola P = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

uint8_t scrollSpeed = 35;                   // default frame delay value
textEffect_t scrollEffect = PA_SCROLL_DOWN;
textPosition_t scrollAlign = PA_CENTER;
uint16_t scrollPause = 2000;                // in milliseconds

WiFiClient espClient;
PubSubClient client(espClient);

char zone0_Message[] = { "wLed" };
char zone1_Message[] = {"i"};               // logo from custom font
bool zone0_newMessageAvailable = false;
bool zone1_newMessageAvailable = false;

int i = 0;

void welcome_message(void) {
  if (i == 1) {
    if (client.connected()) {
      String T_STATUS = TOPIC_PREFIX + "/status";

      Serial.println("MQTT connected");
      client.publish((char*) T_STATUS.c_str(), "up");
      i++;
    }
  }

  if (i == 0) {
    Serial.println("welcome message...");
    strcpy(zone0_Message, "Welcome!");
    zone0_newMessageAvailable = true;
    strcpy(zone1_Message, "i");
    zone1_newMessageAvailable = true;
    i++;
  }
}

void setup_serial() {
  Serial.begin(115200);
  Serial.println("Booting...");
}

void setup_wifi() {
  delay(100);
  Serial.print("Connecting to ");
  Serial.println(WIFI_ssid);
//    WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_ssid, WIFI_password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
//  randomSeed(micros());
  Serial.println("");
  Serial.println("WiFi ready");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  setup_serial();

  P.begin(2);
  P.setZone(0, 0, 6);
  P.setZone(1, 7, 7);
  P.setFont(1, wLedFont);
  P.displayZoneText(0, zone0_Message, scrollAlign, scrollSpeed, scrollPause, PA_FADE, PA_FADE);
  P.displayZoneText(1, zone1_Message, scrollAlign, scrollSpeed, scrollPause, PA_FADE, PA_NO_EFFECT);

  setup_wifi();
  setup_ota();

  client.setServer(mqtt_server, 1883);
  client.setCallback(MQTTCallback);
}

void loop() {
  ArduinoOTA.handle();         // OTAupdates

  if (!client.connected()) {   // MQTT reconnect
    reconnect();
  }

  client.loop();               // MQTT work
  delay(1);

  if (P.displayAnimate()) {    // Display animation

    if (P.getZoneStatus(0)) {
      if ( i < 2 ) {
        welcome_message();  
      }

      if (zone0_newMessageAvailable) {
        zone0_newMessageAvailable = false;
        P.displayReset(0);
      }
    }

    if (P.getZoneStatus(1)) {
      if (zone1_newMessageAvailable) {
        zone1_newMessageAvailable = false;
        P.displayReset(1);
       }
    }

    if ( i == 2 ) {     // after welcome message set display effects without exit animation
       P.setTextEffect(0, PA_SCROLL_DOWN, PA_NO_EFFECT);
       P.setTextEffect(1, PA_SCROLL_DOWN, PA_NO_EFFECT);  
       i++;
     }
  }
}
