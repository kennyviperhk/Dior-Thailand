void meshSetup(){
    mesh.setDebugMsgTypes( ERROR | STARTUP | CONNECTION );  // set before init() so that you can see startup messages


  // Channel set to 6. Make sure to use the same channel for your mesh and for you other
  // network (STATION_SSID)
  mesh.init( MESH_PREFIX, MESH_PASSWORD, MESH_PORT, WIFI_AP_STA, 6 );

  mesh.stationManual(STATION_SSID, STATION_PASSWORD);
  mesh.setHostname(HOSTNAME);

  // Bridge node, should (in most cases) be a root node. See [the wiki](https://gitlab.com/painlessMesh/painlessMesh/wikis/Possible-challenges-in-mesh-formation) for some background
  mesh.setRoot(true);
  // This node and all other nodes should ideally know the mesh contains a root, so call this on all nodes
  mesh.setContainsRoot(true);

  myAPIP = IPAddress(mesh.getAPIP());


  mesh.onReceive(&receivedCallback);
}




void receivedCallback( uint32_t from, String &msg ) {
  Serial.printf("bridge: Received from %u msg=%s\n", from, msg.c_str());
    if (msg == "on") {

     // mesh.sendBroadcast("n : " + mesh.getNodeId());
  } else if (msg == "off") {

    //  mesh.sendBroadcast("f : " + mesh.getNodeId());
  }
  ws.textAll("Mesh Node : " + String(from) + " : " + msg);
}


IPAddress getlocalIP() {
  return IPAddress(mesh.getStationIP());
}
