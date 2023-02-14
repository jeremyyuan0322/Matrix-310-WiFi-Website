#include "src/Artila-Matrix310.h"
#include "src/index.h"
#include <WiFi.h>
#include <WebServer.h>
// Replace with your network credentials
const char *ssid = "Artila";
const char *password = "CF25B34315";
const char *apName = "Matrix-310";
const char *apPwd = "00000000";
WebServer server(80);
bool isApOn = false;
void setupRouting() {
  server.on("/", handleRoot);
  server.on("/wifi", HTTP_POST, handleWifi);  // To get update of ADC Value only
  server.begin();
}
void handleRoot() {
  String s = MAIN_page;              // Read HTML contents
  server.send(200, "text/html", s);  // Send web page
}
void handleWifi() {
  if (isApOn) {
    // Set the password parameter to NULL, if you want the AP (Access Point) to be open.
    IPAddress IP = WiFi.softAP(ssid, NULL);
    Serial.print("AP IP address: ");
    Serial.println(IP);
  } else {
    WiFi.softAPdisconnect();
  }
  server.send(200, "text/plain", "wifi switch ");  // Send web page
}
void wifiSTA() {
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  // Set Wifi mode
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
void wifiAP() {
  Serial.println();
  Serial.println();
  Serial.print("AP name: ");
  Serial.println(ssid);

  // Set Wifi mode
  WiFi.mode(WIFI_AP);
  // Set the password parameter to NULL, if you want the AP (Access Point) to be open.
  IPAddress IP = WiFi.softAP(ssid, password);
  Serial.print("AP IP address: ");
  Serial.println(IP);
}
void setup() {
  Serial.begin(115200);
  delay(10);
  WiFi.mode(WIFI_AP_STA);
  wifiSTA();
  setupRouting();
}

void loop() {
  server.handleClient();
  delay(1);
}

void processMessage(String message) {
  if (message == "turn_on") {
    isApOn = true;
  } else if (message == "turn_off") {
    isApOn = false;
  }
}
