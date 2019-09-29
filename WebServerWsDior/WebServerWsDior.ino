#ifdef ESP8266
#include "Hash.h"
#include <ESPAsyncTCP.h>
#else
#include <AsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>


#include "painlessMesh.h"

#include "config.h"

// WebServer
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");
AsyncEventSource events("/events");

//flag to use from web update to reboot the ESP
bool shouldReboot = false;

// painlessMesh
painlessMesh  mesh;

void setup(){

  Serial.begin(115200);
  Serial.setDebugOutput(true);
 
  wsSetup();
}

void loop(){

   wsLoop();
   meshLoop();

}
