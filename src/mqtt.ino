#include <PubSubClient.h>



WiFiClient espClient;
PubSubClient client(espClient);
int triesCount;

int setup_mqtt() {
    client.setServer(mqtt_server, mqtt_port);
    client.setCallback(callback);
    // client is now ready for use
    return 0;
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected() && triesCount <= 20) {
    Serial.print("Attempting MQTT connection...");
    triesCount++;
    // Attempt to connect
    if (client.connect(host)) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("outTopic", "hello world");
      // ... and resubscribe
      client.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
  if(triesCount == 20){
    Serial.printf("%s\n", "Failed permanently, 20 tries...");
  }
}

void loop_mqtt(){
  if (!client.connected()) {
    triesCount = 0;
    reconnect();
  }
  if (client.connected()){
    //Process incoming and maintain conenction:
    client.loop();
  }else {
    Serial.println("Completed loop_mqtt without any connection...");
  }
}
