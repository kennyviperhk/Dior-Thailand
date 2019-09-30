// Needed for painless library
void receivedCallback( uint32_t from, String &msg ) {
 // mesh.sendBroadcast("mesh " + String(from) + " : " + MESH_ID);
  Serial.printf("mesh: Received from %u : %s\n", from, msg.c_str());
  Serial.println(from == 572610572);
  if(from == 572610572){
    lastMsg = msg;
    }  
}

void newConnectionCallback(uint32_t nodeId) {
  Serial.printf("--> startHere: New Connection, nodeId = %u\n", nodeId);
}

void changedConnectionCallback() {
  Serial.printf("Changed connections\n");
}

void nodeTimeAdjustedCallback(int32_t offset) {
  Serial.printf("Adjusted time %u. Offset = %d\n", mesh.getNodeTime(), offset);
}
