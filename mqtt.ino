void MQTTCallback(char* topic, byte* payload, unsigned int length) {
  String PayloadString = "";
  for (int i = 0; i < length; i++) { PayloadString = PayloadString + (char)payload[i]; }

  Serial.println("New message arrived");  
  Serial.println(topic);  
  Serial.println(PayloadString);  
  
  if(strcmp(topic, "wled/zone0_text") == 0) {  
    Serial.println("zone0 set new Text");
    strcpy(zone0_Message, PayloadString.c_str());
    zone0_newMessageAvailable = true; 
  } 

  if(strcmp(topic, "wled/zone1_text") == 0) {  
    Serial.println("zone1 set new Text");
    strcpy(zone1_Message, PayloadString.c_str());
    zone1_newMessageAvailable = true; 
  } 
 
  if(strcmp(topic, "wled/intensity") == 0) { 
    Serial.println("set new Intensity");
    P.setIntensity(PayloadString.toInt());      
  }  
  
  if(strcmp(topic, "wled/scrolleffect") == 0) { 
    Serial.println("set new scrolleffect");
    uint8_t  inFX, outFX;
    textEffect_t  effect[] =
    {
      PA_RANDOM, // 1
      PA_PRINT,
      PA_SCAN_HORIZ,
      PA_SCROLL_LEFT,
      PA_WIPE,
      //PA_ROCKET,
      PA_SCAN_VERTX,
      PA_SCROLL_UP_LEFT,
      PA_SCROLL_UP,
      PA_FADE, //8
      PA_OPENING_CURSOR,
      PA_GROW_UP,
      PA_SCROLL_UP_RIGHT,
      PA_BLINDS, //12
      PA_CLOSING,
      PA_GROW_DOWN,
     // PA_PACMAN2,
      PA_SCAN_VERT, //15
      PA_SCROLL_DOWN_LEFT,
      PA_WIPE_CURSOR,
      PA_SCAN_HORIZX,
      PA_DISSOLVE,
      PA_MESH, //20
      PA_OPENING,
      PA_CLOSING_CURSOR,
      PA_SCROLL_DOWN_RIGHT,
      PA_SCROLL_RIGHT,
      PA_SLICE,
      PA_SCROLL_DOWN,
      //PA_PACMAN1,
    };

    outFX = PayloadString.toInt() % ARRAY_SIZE(effect);
    inFX = PayloadString.toInt() % ARRAY_SIZE(effect);
    P.setTextEffect(0, effect[inFX], effect[outFX]);      
  }

  if(strcmp(topic, "wled/scrolleffect_without_exit") == 0) { 
    Serial.println("set new scrolleffect");
    uint8_t  inFX, outFX;
    textEffect_t  effect[] =
    {
      PA_RANDOM,
      PA_PRINT,
      PA_SCAN_HORIZ,
      PA_SCROLL_LEFT,
      PA_WIPE,
      //PA_ROCKET,
      PA_SCAN_VERTX,
      PA_SCROLL_UP_LEFT,
      PA_SCROLL_UP,
      PA_FADE, //8
      PA_OPENING_CURSOR,
      PA_GROW_UP,
      PA_SCROLL_UP_RIGHT,
      PA_BLINDS, //12
      PA_CLOSING,
      PA_GROW_DOWN,
     // PA_PACMAN2,
      PA_SCAN_VERT, //15
      PA_SCROLL_DOWN_LEFT,
      PA_WIPE_CURSOR,
      PA_SCAN_HORIZX,
      PA_DISSOLVE,
      PA_MESH, //20
      PA_OPENING,
      PA_CLOSING_CURSOR,
      PA_SCROLL_DOWN_RIGHT,
      PA_SCROLL_RIGHT,
      PA_SLICE,
      PA_SCROLL_DOWN,
      //PA_PACMAN1,
    };
    
    outFX = PayloadString.toInt() % ARRAY_SIZE(effect);
    inFX = PayloadString.toInt() % ARRAY_SIZE(effect);

    P.setTextEffect(0, effect[inFX], PA_NO_EFFECT);      
  }
}

void reconnect() {
  while (!client.connected()) {
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);

    // Attempt to connect
    if (client.connect(clientId.c_str(),mqtt_user,mqtt_password)) {
      Serial.println("subscribe objects"); 
      client.subscribe("wled/zone0_text");  
      client.subscribe("wled/zone1_text");  
      client.subscribe("wled/intensity");  
      client.subscribe("wled/scrolleffect"); 
      client.subscribe("wled/scrolleffect_without_exit");      
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
     
      delay(5000);
    }
  }
}
