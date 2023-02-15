#include "src/Artila-Matrix310.h"
#include "src/index.h"
#include <WiFi.h>
#include <WebServer.h>
#include <ESPAsyncWebServer.h>
byte mac[] = { 0x98, 0xf4, 0xab, 0x17, 0x24, 0xc4 };
byte ip[] = {192, 168, 1, 125};
const char *ssid = "Artila";
const char *password = "CF25B34315";
const char *apName = "Matrix-310";
const char *apPwd = "00000000";
WebServer server(80);
bool isStaOn = true;
bool isApOn = false;
void setupRouting() {
  server.on("/", handleRoot);
  server.on("/wifi", HTTP_POST, []() {
    handleAp(server.arg("buttonText"));
  });
  server.on("/ap", HTTP_POST, []() {
    handleAp(server.arg("buttonText"));
  });
  server.begin();
}
void handleRoot() {
  String s = MAIN_page;              // Read HTML contents
  server.send(200, "text/html", s);  // Send web page
}
void handleWifi(String message) {
  Serial.printf("msg\n: %s", message);
  if (message == "ON") {
    isStaOn = false;
  } else if (message == "OFF") {
    isStaOn = true;
  }
  String msg = "wifi " + message;
  server.send(200, "text/plain", msg);  // Send web page
}

void handleAp(String message) {
  Serial.printf("msg: %s", message);
  // String buttonText = server.arg("buttonText");
  if (message == "ON") {
    isApOn = false;
  } else if (message == "OFF") {
    isApOn = true;
  }
  wifiAP();
  String msg = "wifi ap" + message;
  server.send(200, "text/plain", msg);
}

void wifiSTA() {
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  // Set Wifi mode
  WiFi.begin(ssid, password);

  unsigned long startTime = millis();
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (WiFi.status() == WL_CONNECTED) {
      break;
    }
    if (millis() - startTime > 6000) {
      Serial.println("\nwifi connect fail");
      return;
    }
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
void wifiAP() {
  if (isApOn) {
    Serial.println();
    Serial.println();
    Serial.print("AP name: ");
    Serial.println(apName);
    IPAddress IP = WiFi.softAP(apName, apPwd);
    Serial.print("AP IP address: ");
    Serial.println(IP);
    Serial.println("AP started");
  } else {
    WiFi.softAPdisconnect();
    Serial.println("AP stopped");
  }
}
void eth(){
  Ethernet.init(LAN_CS); // pin 5
  Serial.println("Initialize Ethernet with static IP:");
  //Matrix310 tries connecting the internet with static ip
  Ethernet.begin(mac, ip);
  // Matrix-310 already connect to the internet
  Serial.print("  Static IP ");
  Serial.println(Ethernet.localIP());
  // give the Ethernet shield a second to initialize:
  delay(1000);
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
