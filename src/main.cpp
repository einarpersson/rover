#include <Arduino.h>
#include <WiFi.h>
#include <SPIFFS.h>
#include <ESPAsyncWebServer.h>

// WiFi config
const char *ssid = "Rover";
const char *password = "gogogogo";
IPAddress local_ip(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

// Web Server
AsyncWebServer server(80);

// void rootHandler() {
//   String str = "";
//   Serial.println("Got visitors!");

//   File file = SPIFFS.open("/index.html");
//   if (!file) {
//     Serial.println("Failed to open file");
//     return;
//   }

//   while(file.available()){
//     str = str + file.read();
//   }
//   file.close();

//   server.send(200, "text/html", str);
// }

bool ledOn = false;

void toggleLED(AsyncWebServerRequest *request) {
  ledOn = !ledOn;
  if (ledOn) {
    Serial.println("ON");
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    Serial.println("OFF");
    digitalWrite(LED_BUILTIN, LOW);
  }

  request->send(200);
}

void setup()
{
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  if (!SPIFFS.begin())
  {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  WiFi.config(local_ip, gateway, subnet);

  delay(100);

  Serial.println(WiFi.status());

  // server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
  //   request->send(SPIFFS, "/index.html", "text/html");
  // });

  server.on("/toggle", HTTP_GET, toggleLED);
  server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");

  server.begin();
  Serial.println("Server started, I hope...");

  // Diagnostics
  // Serial.begin(9600);
  // digitalWrite(LED_BUILTIN, HIGH);
  // delay(200);
  // digitalWrite(LED_BUILTIN, LOW);
  // delay(200);
  // digitalWrite(LED_BUILTIN, HIGH);
  // delay(200);
  // digitalWrite(LED_BUILTIN, LOW);
  // delay(200);

  // Serial.write("Starting up...");

  // // Motor
  // pinMode(3, OUTPUT);
  // pinMode(4, OUTPUT);

  // // On/Off
  // pinMode(0, INPUT_PULLUP);
}

void loop()
{

  // digitalWrite(LED_BUILTIN, HIGH);
  // delay(200);
  // digitalWrite(LED_BUILTIN, LOW);
  // delay(200);

  // if (0 == digitalRead(0))
  // {
  //   Serial.println("FORWARD");
  //   digitalWrite(3, LOW);
  //   digitalWrite(4, HIGH);
  // }
  // else
  // {
  //   // Serial.println("STOP");
  //   digitalWrite(3, LOW);
  //   digitalWrite(4, LOW);
  // }
  // delay(3000);

  // Serial.println("STOP");
  // digitalWrite(3, LOW);
  // digitalWrite(4, LOW);

  // delay(3000);

  // Serial.println("BACKWARD");
  // digitalWrite(3, HIGH);
  // digitalWrite(4, LOW);

  // delay(3000);

  // Serial.println("STOP");
  // digitalWrite(3, LOW);
  // digitalWrite(4, LOW);

  // delay(3000);
}
