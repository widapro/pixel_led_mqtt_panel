# Pixel led MQTT panel (wLed)

wLed panel it's dot matrix display to show information from MQTT topics. It's well integrated with home automation systems like Home-assistant, domoticz and others through MQTT broker.
<p align="center">
  <a href="http://www.youtube.com/watch?feature=player_embedded&v=hIWn9VRI1j4
" target="_blank"><img width="600" height="266" title="wLed demo photo" alt="wLed demo photo" src="https://raw.githubusercontent.com/widapro/pixel_led_mqtt_panel/master/img/wled_panel.jpg"></a>
</p>

<a href="https://youtu.be/hIWn9VRI1j4" target="_blank" >Demo video on youtube.</a>


##### Ingredients:
1. Dot matrix display MAX7219: https://aliexpress.ru/item/32618155357.html
2. WeMos D1 Mini (esp8266): https://aliexpress.ru/item/32651747570.html


## Algoritm of work
The display has booting and connecting to wifi, then the display subscribe to MQTT topics and publishing message "up" in MQTT topic `wled/status`

##### MQTT topics:
* `wled/zone0_text`                - main text for zone0
* `wled/zone1_text`                - sight zone (left segment sun in demo picture ^)
* `wled/intensity`                 - display brightnes [0-15], default 5
* `wled/scrolleffect`              - number of scroll effect for zone0, both effect for entry and exit text _[**send only number**, not effect name]_
* `wled/scrolleffect_without_exit` - number scroll effect for zone 0, only entry effect, the text will not go out and still stay on display until new text coming _[**send only number**, not effect name]_

#### Scroll effect list;
```
      PA_RANDOM,          // 0
      PA_PRINT,
      PA_SCAN_HORIZ,
      PA_SCROLL_LEFT,     // 3
      PA_WIPE,
      PA_SCAN_VERTX,
      PA_SCROLL_UP_LEFT,  // 6
      PA_SCROLL_UP,
      PA_FADE,
      PA_OPENING_CURSOR,  // 9
      PA_GROW_UP,
      PA_SCROLL_UP_RIGHT,
      PA_BLINDS,          // 12
      PA_CLOSING,
      PA_GROW_DOWN,
      PA_SCAN_VERT,       // 15
      PA_SCROLL_DOWN_LEFT,
      PA_WIPE_CURSOR,
      PA_SCAN_HORIZX,     // 18
      PA_DISSOLVE,
      PA_MESH,
      PA_OPENING,         // 21
      PA_CLOSING_CURSOR,
      PA_SCROLL_DOWN_RIGHT,
      PA_SCROLL_RIGHT,    // 24
      PA_SLICE,
      PA_SCROLL_DOWN,     // 26
```

## Icons
For icons, I created a font with several icons to override the regular alphabet. This font applied just only for **zone1**. You can find a mapping card in `wLedFont.h`.
You can paint icons whatever you want using this online tool: https://pjrp.github.io/MDParolaFontEditor

Feel free to add new icons and update the existing `wLedFont.h` in the repository.
<p align="center">
<img width="800" height="259" title="wLed icons map" alt="wLed icons map" src="https://raw.githubusercontent.com/widapro/pixel_led_mqtt_panel/master/img/icons_map.jpg">
</p>

## Flash esp8266 (WeMos D1):

##### Install libraries in Arduino IDE
* PubSubClient https://pubsubclient.knolleary.net/
* MD_MAX72XX https://github.com/MajicDesigns/MD_MAX72XX
* MD_Parola (with dependencies) https://github.com/MajicDesigns/MD_Parola

##### First need to change config section in file `pixel_led_mqtt_panel.ino`:
```
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

  // Parola display settings //
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW // type of device hardware https://majicdesigns.github.io/MD_MAX72XX/page_hardware.html
#define MAX_DEVICES  8                    // number of device segments
  // Display pinout //
#define DATA_PIN  D7                      // WeMos D1 mini GPIO13
#define CS_PIN    D6                      // WeMos D1 mini GPIO12
#define CLK_PIN   D5                      // WeMos D1 mini GPIO14
```
##### _Optional_ 
If you have display with different count of segments you need to change zones in config before flashing
<p align="center">
  <img width="600" height="266" title="wLed demo photo with zones" alt="wLed demo photo with zones" src="https://raw.githubusercontent.com/widapro/pixel_led_mqtt_panel/master/img/wled_pane_zones.jpg">
</p>

In file `pixel_led_mqtt_panel.ino`:
```
#define MAX_DEVICES  8                    // number of device segments
```
```
void setup() {
  setup_serial();

  P.begin(2);
  P.setZone(0, 0, 6);                     // P.setZone(zone_number,start_segmet,end_segment)
  P.setZone(1, 7, 7);                     // P.setZone(zone_number,start_segmet,end_segment)
```


#### Then configure automation in Home Asisstant:
Send sensor value each time when a value has been changed
```
---
- alias: Outside temp change - send new temp to wled panel mqtt
  initial_state: 'on'
  trigger:
    platform: state
    entity_id: sensor.outside_thp_sensor_3
  action:
    - service: mqtt.publish
      data:
        topic: wled/zone0_text
        payload_template: "{{ states('sensor.outside_thp_sensor_3') }} C"
```

First matrix panel start. When matrix panel publish message "up" in wled/status MQTT topic HA sends a message and change scroll effect
```
- alias: wled panel ON mqtt - send outside temp mqtt
  initial_state: 'on'
  trigger:
    platform: mqtt
    topic: wled/status
  action:
    - delay: "00:00:03"
    - service: mqtt.publish
      data:
        topic: wled/scrolleffect
        payload_template: "9"
    - service: mqtt.publish
      data:
        topic: wled/zone0_text
        payload_template: "MQTT ok"
    - delay: "00:00:03"
    - service: mqtt.publish
      data:
        topic: wled/zone0_text
        payload_template: "HA ok"
    - delay: "00:00:03"
    - service: mqtt.publish
      data:
        topic: wled/scrolleffect_without_exit
        payload_template: "26"
    - service: mqtt.publish
      data:
        topic: wled/zone0_text
        payload_template: "{{ states('sensor.outside_thp_sensor_3') }} C"
    - service: mqtt.publish
      data:
        topic: wled/zone1_text
        payload: "s"
```
