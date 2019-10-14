// Needed for painless library
void receivedCallback( uint32_t from, String &msg ) {
  // mesh.sendBroadcast("mesh " + String(from) + " : " + MESH_ID);
  Serial.printf("mesh: Received from %u : %s\n", from, msg.c_str());
  // Serial.println(from == 572610572);
  // if (from == 572610572) {
  //  lastMsg = msg;
  //}

  if (msg == "on") {
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(D7, HIGH);
    digitalWrite(D8, HIGH);
    mesh.sendBroadcast("n : " + mesh.getNodeId());
  } else if (msg == "off") {
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(D7, LOW);
    digitalWrite(D8, LOW);
    mesh.sendBroadcast("f : " + mesh.getNodeId());
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
