// TOPICS
String T_ZONE0_TEXT = TOPIC_PREFIX + "/zone0_text";
String T_ZONE1_TEXT = TOPIC_PREFIX + "/zone1_text";
String T_INTENSITY = TOPIC_PREFIX + "/intensity";
String T_EFFECT = TOPIC_PREFIX + "/scrolleffect";
String T_EFFECT_WITHOUT_EXIT = TOPIC_PREFIX + "/scrolleffect_without_exit";

void MQTTCallback(char* topic, byte* payload, unsigned int length) {
  String PayloadString = "";
  for (int i = 0; i < length; i++) { PayloadString = PayloadString + (char)payload[i]; }

  Serial.println("New message arrived");  
  Serial.println(topic);  
  Serial.println(PayloadString);  
  
  if(strcmp(topic, (char*) T_ZONE0_TEXT.c_str()) == 0) {
    Serial.println("zone0 set new Text");
    strcpy(zone0_Message, PayloadString.c_str());
    zone0_newMessageAvailable = true; 
  } 

  if(strcmp(topic, (char*) T_ZONE1_TEXT.c_str()) == 0) {
    Serial.println("zone1 set new Text");
    strcpy(zone1_Message, PayloadString.c_str());
    zone1_newMessageAvailable = true; 
  } 
 
  if(strcmp(topic, (char*) T_INTENSITY.c_str()) == 0) {
    Serial.println("set new Intensity");
    P.setIntensity(PayloadString.toInt());      
  }  
  
  if(strcmp(topic,  (char*) T_EFFECT.c_str()) == 0) {
    Serial.println("set new scrolleffect");

    if(PayloadString == "PA_RANDOM") {
          P.setTextEffect(0, PA_RANDOM, PA_RANDOM);
    }

    if(PayloadString == "PA_PRINT") {
          P.setTextEffect(0, PA_PRINT, PA_PRINT);
    }

    if(PayloadString == "PA_SCAN_HORIZ") {
          P.setTextEffect(0, PA_SCAN_HORIZ, PA_SCAN_HORIZ);
    }

    if(PayloadString == "PA_SCROLL_LEFT") {
          P.setTextEffect(0, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
    }

    if(PayloadString == "PA_WIPE") {
          P.setTextEffect(0, PA_WIPE, PA_WIPE);
    }

    if(PayloadString == "PA_SCAN_VERTX") {
          P.setTextEffect(0, PA_SCAN_VERTX, PA_SCAN_VERTX);
    }

    if(PayloadString == "PA_SCROLL_UP_LEFT") {
          P.setTextEffect(0, PA_SCROLL_UP_LEFT, PA_SCROLL_UP_LEFT);
    }

    if(PayloadString == "PA_SCROLL_UP") {
          P.setTextEffect(0, PA_SCROLL_UP, PA_SCROLL_UP);
    }

    if(PayloadString == "PA_FADE") {
          P.setTextEffect(0, PA_FADE, PA_FADE);
    }

    if(PayloadString == "PA_OPENING_CURSOR") {
          P.setTextEffect(0, PA_OPENING_CURSOR, PA_OPENING_CURSOR);
    }

    if(PayloadString == "PA_GROW_UP") {
          P.setTextEffect(0, PA_GROW_UP, PA_GROW_UP);
    }

    if(PayloadString == "PA_SCROLL_UP_RIGHT") {
          P.setTextEffect(0, PA_SCROLL_UP_RIGHT, PA_SCROLL_UP_RIGHT);
    }

    if(PayloadString == "PA_BLINDS") {
          P.setTextEffect(0, PA_BLINDS, PA_BLINDS);
    }

    if(PayloadString == "PA_CLOSING") {
          P.setTextEffect(0, PA_CLOSING, PA_CLOSING);
    }

    if(PayloadString == "PA_GROW_DOWN") {
          P.setTextEffect(0, PA_GROW_DOWN, PA_GROW_DOWN);
    }

    if(PayloadString == "PA_SCAN_VERT") {
          P.setTextEffect(0, PA_SCAN_VERT, PA_SCAN_VERT);
    }

    if(PayloadString == "PA_SCROLL_DOWN_LEFT") {
          P.setTextEffect(0, PA_SCROLL_DOWN_LEFT, PA_SCROLL_DOWN_LEFT);
    }

    if(PayloadString == "PA_WIPE_CURSOR") {
          P.setTextEffect(0, PA_WIPE_CURSOR, PA_WIPE_CURSOR);
    }

    if(PayloadString == "PA_SCAN_HORIZX") {
          P.setTextEffect(0, PA_SCAN_HORIZX, PA_SCAN_HORIZX);
    }
    if(PayloadString == "PA_DISSOLVE") {
          P.setTextEffect(0, PA_DISSOLVE, PA_DISSOLVE);
    }

    if(PayloadString == "PA_MESH") {
          P.setTextEffect(0, PA_MESH, PA_MESH);
    }

    if(PayloadString == "PA_OPENING") {
          P.setTextEffect(0, PA_OPENING, PA_OPENING);
    }

    if(PayloadString == "PA_CLOSING_CURSOR") {
          P.setTextEffect(0, PA_CLOSING_CURSOR, PA_CLOSING_CURSOR);
    }

    if(PayloadString == "PA_SCROLL_DOWN_RIGHT") {
          P.setTextEffect(0, PA_SCROLL_DOWN_RIGHT, PA_SCROLL_DOWN_RIGHT);
    }

    if(PayloadString == "PA_SCROLL_RIGHT") {
          P.setTextEffect(0, PA_SCROLL_RIGHT, PA_SCROLL_RIGHT);
    }

    if(PayloadString == "PA_SLICE") {
          P.setTextEffect(0, PA_SLICE, PA_SLICE);
    }

    if(PayloadString == "PA_SCROLL_DOWN") {
          P.setTextEffect(0, PA_SCROLL_DOWN, PA_SCROLL_DOWN);
    }

// CUSTOM ANIMATIONS

    if(PayloadString == "PACMAN") {
          P.setSpriteData(pacman1, W_PMAN1, F_PMAN1, pacman2, W_PMAN2, F_PMAN2);
          P.setTextEffect(0, PA_SPRITE, PA_SPRITE);
    }

    if(PayloadString == "WAVE") {
          P.setSpriteData(wave, W_WAVE, F_WAVE, wave, W_WAVE, F_WAVE);
          P.setTextEffect(0, PA_SPRITE, PA_SPRITE);
    }

    if(PayloadString == "ROLL") {
          P.setSpriteData(roll1, W_ROLL1, F_ROLL1, roll2, W_ROLL2, F_ROLL2);
          P.setTextEffect(0, PA_SPRITE, PA_SPRITE);
    }

    if(PayloadString == "LINES") {
          P.setSpriteData(lines, W_LINES, F_LINES, lines, W_LINES, F_LINES);
          P.setTextEffect(0, PA_SPRITE, PA_SPRITE);
    }

    if(PayloadString == "ARROW") {
          P.setSpriteData(arrow1, W_ARROW1, F_ARROW1, arrow2, W_ARROW2, F_ARROW2);
          P.setTextEffect(0, PA_SPRITE, PA_SPRITE);
    }

    if(PayloadString == "SAILBOAT") {
          P.setSpriteData(sailboat, W_SAILBOAT, F_SAILBOAT, sailboat, W_SAILBOAT, F_SAILBOAT);
          P.setTextEffect(0, PA_SPRITE, PA_SPRITE);
    }

    if(PayloadString == "STEAMBOAT") {
          P.setSpriteData(steamboat, W_STEAMBOAT, F_STEAMBOAT, steamboat, W_STEAMBOAT, F_STEAMBOAT);
          P.setTextEffect(0, PA_SPRITE, PA_SPRITE);
    }

    if(PayloadString == "HEART") {
          P.setSpriteData(heart, W_HEART, F_HEART, heart, W_HEART, F_HEART);
          P.setTextEffect(0, PA_SPRITE, PA_SPRITE);
    }

    if(PayloadString == "INVADER") {
          P.setSpriteData(invader, W_INVADER, F_INVADER, invader, W_INVADER, F_INVADER);
          P.setTextEffect(0, PA_SPRITE, PA_SPRITE);
    }

    if(PayloadString == "ROCKET") {
          P.setSpriteData(rocket, W_ROCKET, F_ROCKET, rocket, W_ROCKET, F_ROCKET);
          P.setTextEffect(0, PA_SPRITE, PA_SPRITE);
    }

    if(PayloadString == "FBALL") {
          P.setSpriteData(fireball, W_FBALL, F_FBALL, fireball, W_FBALL, F_FBALL);
          P.setTextEffect(0, PA_SPRITE, PA_SPRITE);
    }

    if(PayloadString == "CHEVRON") {
          P.setSpriteData(chevron, W_CHEVRON, F_CHEVRON, chevron, W_CHEVRON, F_CHEVRON);
          P.setTextEffect(0, PA_SPRITE, PA_SPRITE);
    }

    if(PayloadString == "WALKER") {
          P.setSpriteData(walker, W_WALKER, F_WALKER, walker, W_WALKER, F_WALKER);
          P.setTextEffect(0, PA_SPRITE, PA_SPRITE);
    }
  }

  if(strcmp(topic, (char*) T_EFFECT_WITHOUT_EXIT.c_str() ) == 0) {
    Serial.println("set new scrolleffect");

    if(PayloadString == "PA_RANDOM") {
          P.setTextEffect(0, PA_RANDOM, PA_NO_EFFECT);
    }

    if(PayloadString == "PA_PRINT") {
          P.setTextEffect(0, PA_PRINT, PA_NO_EFFECT);
    }

    if(PayloadString == "PA_SCAN_HORIZ") {
          P.setTextEffect(0, PA_SCAN_HORIZ, PA_NO_EFFECT);
    }

    if(PayloadString == "PA_SCROLL_LEFT") {
          P.setTextEffect(0, PA_SCROLL_LEFT, PA_NO_EFFECT);
    }

    if(PayloadString == "PA_WIPE") {
          P.setTextEffect(0, PA_WIPE, PA_NO_EFFECT);
    }

    if(PayloadString == "PA_SCAN_VERTX") {
          P.setTextEffect(0, PA_SCAN_VERTX, PA_NO_EFFECT);
    }

    if(PayloadString == "PA_SCROLL_UP_LEFT") {
          P.setTextEffect(0, PA_SCROLL_UP_LEFT, PA_NO_EFFECT);
    }

    if(PayloadString == "PA_SCROLL_UP") {
          P.setTextEffect(0, PA_SCROLL_UP, PA_NO_EFFECT);
    }

    if(PayloadString == "PA_FADE") {
          P.setTextEffect(0, PA_FADE, PA_NO_EFFECT);
    }

    if(PayloadString == "PA_OPENING_CURSOR") {
          P.setTextEffect(0, PA_OPENING_CURSOR, PA_NO_EFFECT);
    }

    if(PayloadString == "PA_GROW_UP") {
          P.setTextEffect(0, PA_GROW_UP, PA_NO_EFFECT);
    }

    if(PayloadString == "PA_SCROLL_UP_RIGHT") {
          P.setTextEffect(0, PA_SCROLL_UP_RIGHT, PA_NO_EFFECT);
    }

    if(PayloadString == "PA_BLINDS") {
          P.setTextEffect(0, PA_BLINDS, PA_NO_EFFECT);
    }

    if(PayloadString == "PA_CLOSING") {
          P.setTextEffect(0, PA_CLOSING, PA_NO_EFFECT);
    }

    if(PayloadString == "PA_GROW_DOWN") {
          P.setTextEffect(0, PA_GROW_DOWN, PA_NO_EFFECT);
    }

    if(PayloadString == "PA_SCAN_VERT") {
          P.setTextEffect(0, PA_SCAN_VERT, PA_NO_EFFECT);
    }

    if(PayloadString == "PA_SCROLL_DOWN_LEFT") {
          P.setTextEffect(0, PA_SCROLL_DOWN_LEFT, PA_NO_EFFECT);
    }

    if(PayloadString == "PA_WIPE_CURSOR") {
          P.setTextEffect(0, PA_WIPE_CURSOR, PA_NO_EFFECT);
    }

    if(PayloadString == "PA_SCAN_HORIZX") {
          P.setTextEffect(0, PA_SCAN_HORIZX, PA_NO_EFFECT);
    }
    if(PayloadString == "PA_DISSOLVE") {
          P.setTextEffect(0, PA_DISSOLVE, PA_NO_EFFECT);
    }

    if(PayloadString == "PA_MESH") {
          P.setTextEffect(0, PA_MESH, PA_NO_EFFECT);
    }

    if(PayloadString == "PA_OPENING") {
          P.setTextEffect(0, PA_OPENING, PA_NO_EFFECT);
    }

    if(PayloadString == "PA_CLOSING_CURSOR") {
          P.setTextEffect(0, PA_CLOSING_CURSOR, PA_NO_EFFECT);
    }

    if(PayloadString == "PA_SCROLL_DOWN_RIGHT") {
          P.setTextEffect(0, PA_SCROLL_DOWN_RIGHT, PA_NO_EFFECT);
    }

    if(PayloadString == "PA_SCROLL_RIGHT") {
          P.setTextEffect(0, PA_SCROLL_RIGHT, PA_NO_EFFECT);
    }

    if(PayloadString == "PA_SLICE") {
          P.setTextEffect(0, PA_SLICE, PA_NO_EFFECT);
    }

    if(PayloadString == "PA_SCROLL_DOWN") {
          P.setTextEffect(0, PA_SCROLL_DOWN, PA_NO_EFFECT);
    }

// CUSTOM ANIMATIONS

    if(PayloadString == "PACMAN") {
          P.setSpriteData(pacman1, W_PMAN1, F_PMAN1, pacman2, W_PMAN2, F_PMAN2);
          P.setTextEffect(0, PA_SPRITE, PA_NO_EFFECT);
    }

    if(PayloadString == "WAVE") {
          P.setSpriteData(wave, W_WAVE, F_WAVE, wave, W_WAVE, F_WAVE);
          P.setTextEffect(0, PA_SPRITE, PA_NO_EFFECT);
    }

    if(PayloadString == "ROLL") {
          P.setSpriteData(roll1, W_ROLL1, F_ROLL1, roll2, W_ROLL2, F_ROLL2);
          P.setTextEffect(0, PA_SPRITE, PA_NO_EFFECT);
    }

    if(PayloadString == "LINES") {
          P.setSpriteData(lines, W_LINES, F_LINES, lines, W_LINES, F_LINES);
          P.setTextEffect(0, PA_SPRITE, PA_NO_EFFECT);
    }

    if(PayloadString == "ARROW") {
          P.setSpriteData(arrow1, W_ARROW1, F_ARROW1, arrow2, W_ARROW2, F_ARROW2);
          P.setTextEffect(0, PA_SPRITE, PA_NO_EFFECT);
    }

    if(PayloadString == "SAILBOAT") {
          P.setSpriteData(sailboat, W_SAILBOAT, F_SAILBOAT, sailboat, W_SAILBOAT, F_SAILBOAT);
          P.setTextEffect(0, PA_SPRITE, PA_NO_EFFECT);
    }

    if(PayloadString == "STEAMBOAT") {
          P.setSpriteData(steamboat, W_STEAMBOAT, F_STEAMBOAT, steamboat, W_STEAMBOAT, F_STEAMBOAT);
          P.setTextEffect(0, PA_SPRITE, PA_NO_EFFECT);
    }

    if(PayloadString == "HEART") {
          P.setSpriteData(heart, W_HEART, F_HEART, heart, W_HEART, F_HEART);
          P.setTextEffect(0, PA_SPRITE, PA_NO_EFFECT);
    }

    if(PayloadString == "INVADER") {
          P.setSpriteData(invader, W_INVADER, F_INVADER, invader, W_INVADER, F_INVADER);
          P.setTextEffect(0, PA_SPRITE, PA_NO_EFFECT);
    }

    if(PayloadString == "ROCKET") {
          P.setSpriteData(rocket, W_ROCKET, F_ROCKET, rocket, W_ROCKET, F_ROCKET);
          P.setTextEffect(0, PA_SPRITE, PA_NO_EFFECT);
    }

    if(PayloadString == "FBALL") {
          P.setSpriteData(fireball, W_FBALL, F_FBALL, fireball, W_FBALL, F_FBALL);
          P.setTextEffect(0, PA_SPRITE, PA_NO_EFFECT);
    }

    if(PayloadString == "CHEVRON") {
          P.setSpriteData(chevron, W_CHEVRON, F_CHEVRON, chevron, W_CHEVRON, F_CHEVRON);
          P.setTextEffect(0, PA_SPRITE, PA_NO_EFFECT);
    }

    if(PayloadString == "WALKER") {
          P.setSpriteData(walker, W_WALKER, F_WALKER, walker, W_WALKER, F_WALKER);
          P.setTextEffect(0, PA_SPRITE, PA_NO_EFFECT);
    }
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
      client.subscribe((char*) T_ZONE0_TEXT.c_str());
      client.subscribe((char*) T_ZONE1_TEXT.c_str());
      client.subscribe((char*) T_INTENSITY.c_str());
      client.subscribe((char*) T_EFFECT.c_str());
      client.subscribe((char*) T_EFFECT_WITHOUT_EXIT.c_str());
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
