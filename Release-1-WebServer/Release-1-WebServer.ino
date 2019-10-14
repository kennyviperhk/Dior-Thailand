#include "ESPAsyncTCP.h"
#include "ESPAsyncWebServer.h"


#include "painlessMesh.h"

#include "config.h"

AsyncWebServer server(80);
AsyncWebSocket ws("/ws"); // access at ws://[esp ip]/ws
AsyncEventSource events("/events"); // event source (Server-Sent events)

IPAddress myAPIP(0,0,0,0);

painlessMesh  mesh;

// prototypes
void receivedCallback( uint32_t from, String &msg );


//flag to use from web update to reboot the ESP
bool shouldReboot = false;






int switchPin = D8;
int switchState = LOW;
unsigned long previousMillis = 0;        // will store last time LED was updated

long interval = 1000;           // interval at which to blink (milliseconds)




void setup(){
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
}

void loop(){
  if(shouldReboot){
    Serial.println("Rebooting...");
    delay(100);
    ESP.restart();
  }
  
  static char temp[128];
  sprintf(temp, "Seconds since boot: %u", millis()/1000);
  events.send(temp, "time"); //send event "time"

  mesh.update();






  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (switchState == LOW) {
      switchState = HIGH;
    } else {
      switchState = LOW;
    }

    // set the LED with the ledState of the variable:
    digitalWrite(switchPin, switchState);
    digitalWrite(LED_BUILTIN, !switchState);
    if(switchState){
     // mesh.sendBroadcast("n : " + mesh.getNodeId());
      mesh.sendBroadcast("on");
      }else{
        mesh.sendBroadcast("off");
        }
    
  }

}
