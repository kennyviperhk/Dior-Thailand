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
}
