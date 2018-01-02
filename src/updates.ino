/*
  To upload through terminal you can use: curl -F "image=@firmware.bin" esp8266-webupdate.local/update
*/

#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>


ESP8266WebServer httpServer(80);
ESP8266HTTPUpdateServer httpUpdater;

int setup_updates(){
  httpUpdater.setup(&httpServer);
  httpServer.begin();
  Serial.printf("HTTPUpdateServer ready! Open http://%s.local/update in your browser\n", host);
  return 0;
}

void loop_updates(){
  httpServer.handleClient();
}
