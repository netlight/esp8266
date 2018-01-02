
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266mDNS.h>
#include <SimpleTimer.h>

SimpleTimer timer;

const char* host = "nl_iot_8-webupdate";
const char* ssid = "_";
const char* password = "wifipassword";
const char* mqtt_server = "mymqttserver";
const uint16_t mqtt_port = 1883;


void setup(void){

  Serial.begin(115200);
  Serial.println("Booting Sketch...");
  WiFi.mode(WIFI_AP_STA);
  WiFi.begin(ssid, password);

  while(WiFi.waitForConnectResult() != WL_CONNECTED){
    WiFi.begin(ssid, password);
    Serial.println("WiFi failed, retrying.");
  }

  MDNS.begin(host);
  MDNS.addService("http", "tcp", 80);

  setup_updates();
  setup_mqtt();

  // Custom loops running outside of the main loop:
  //timer.setInterval(5000L, loop_temp);
  timer.setInterval(5000L, loop_mqtt);
}

// Main loop handling updates etc.
void loop(void){
  loop_updates();
  timer.run();

}
