//wifi設const不能改？
//handle wifi ssid cant see
#include "src/Artila-Matrix310.h"
#include "src/index.h"
#include <WiFi.h>
#include <WebServer.h>
// Replace with your network credentials
WebServer server(80);
bool isStaOn = true;
bool isApOn = false;
void setupRouting() {
  server.on("/", handleRoot);
  server.on("/wifi", HTTP_POST, handleWifi);
  server.on("/ap", HTTP_POST, []() {
    handleAp(server.arg("buttonText"));
  });
  server.begin();
}
void handleRoot() {
  String s = MAIN_page;              // Read HTML contents
  server.send(200, "text/html", s);  // Send web page
}
void handleWifi() {
  String ssid_str = server.arg("ssid");
  String pwd_str = server.arg("pwd");
  char ssid[10];
  char pwd[10];
  strcpy(ssid, ssid_str.c_str());
  strcpy(pwd, pwd_str.c_str()); 
  // ssid = server.arg("ssid").c_str();  // 取得SSID值
  // pwd = server.arg("pwd").c_str();    // 取得PWD值

  // 在此可以進一步處理SSID和PWD值，例如儲存到EEPROM或連接WIFI等
  Serial.print("SSID: ");
  Serial.println(ssid);
  Serial.print("PWD: ");
  Serial.println(pwd);
  wifiSTA(ssid, pwd);
  // 回傳回應
  server.send(200, "text/plain", "Connected to WIFI!");
}

void handleAp(String message) {
  Serial.printf("msg: %s\n", message);
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

void wifiSTA(char *ssid, char *pwd) {
  // IPAddress ip(192, 168, 3, 1);
  // IPAddress gateway(192, 168, 3, 254);  // 指定網關
  // IPAddress subnet(255, 255, 255, 0);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  // Set Wifi mode
  WiFi.begin(ssid, pwd);

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
  // WiFi.config(ip, gateway, subnet);
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
void wifiAP() {
  const char *apName = "Matrix-310";
  const char *apPwd = "00000000";
  IPAddress ip(192, 168, 3, 254);
  IPAddress gateway(192, 168, 3, 254);  // 指定網關
  IPAddress subnet(255, 255, 255, 0);
  if (isApOn) {
    Serial.println();
    Serial.println();
    Serial.print("AP name: ");
    Serial.println(apName);
    WiFi.softAP(apName, apPwd);
    WiFi.softAPConfig(ip, gateway, subnet);
    Serial.print("AP IP address: ");
    Serial.println(WiFi.softAPIP());
    Serial.println("AP started");
  } else {
    WiFi.softAPdisconnect();
    Serial.println("AP stopped");
  }
}
void setup() {
  char ssid[] = "Artila";
  char pwd[] = "CF25B34315";
  Serial.begin(115200);
  delay(10);
  WiFi.mode(WIFI_AP_STA);
  wifiSTA(ssid, pwd);
  setupRouting();
}

void loop() {
  server.handleClient();
  delay(1);
}
