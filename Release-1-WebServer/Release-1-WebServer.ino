#include "ESPAsyncTCP.h"
#include "ESPAsyncWebServer.h"


#include "painlessMesh.h"

#include "config.h"

AsyncWebServer server(80);
AsyncWebSocket ws("/ws"); // access at ws://[esp ip]/ws
AsyncEventSource events("/events"); // event source (Server-Sent events)

IPAddress myAPIP(0, 0, 0, 0);

painlessMesh  mesh;

// prototypes
void receivedCallback( uint32_t from, String &msg );


//flag to use from web update to reboot the ESP
bool shouldReboot = false;

int switchPin = D7;
int switchPin2 = D8;

unsigned long previousMillis = 0;        // will store last time LED was updated
int i = 0;

int switchState = HIGH;
/*============= config here ===============*/
//in seconds
//long interval[] = {2, 5, 3, 1};
long interval[] = {20, 5, 30, 10};
//High Low high low .....
/*============  config here =================*/




void setup() {
  Serial.begin(115200);

  meshSetup();
  serverSetup();
  /*
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.printf("WiFi Failed!\n");
    return;
    }
  */
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(switchPin, OUTPUT);
  pinMode(switchPin2, OUTPUT);
}

void loop() {
  if (shouldReboot) {
    Serial.println("Rebooting...");
    delay(100);
    ESP.restart();
  }

  static char temp[128];
  sprintf(temp, "Seconds since boot: %u", millis() / 1000);
  events.send(temp, "time"); //send event "time"

  mesh.update();

  unsigned long currentMillis = millis();
  /*
    if (currentMillis % 1000 == 1) {
    Serial.println("sizeof(interval) / sizeof(interval[0])");
    Serial.println(sizeof(interval) / sizeof(interval[0]));
    }
  */
  if (currentMillis - previousMillis >= (interval[i] * 1000)) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (switchState == LOW) {
      switchState = HIGH;
      Serial.println("HIGH");
    } else {
      switchState = LOW;
      Serial.println("LOW");
    }

    // set the LED with the ledState of the variable:
    digitalWrite(switchPin, switchState);
    digitalWrite(switchPin2, switchState);
    digitalWrite(LED_BUILTIN, !switchState);
    if (switchState) {
      // mesh.sendBroadcast("n : " + mesh.getNodeId());
      mesh.sendBroadcast("on");
    } else {
      mesh.sendBroadcast("off");
    }
    i++;
  }
  if ( i >= (sizeof(interval) / sizeof(interval[0]))) {
    i = 0;
  }
}
