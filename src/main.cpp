#include <Arduino.h>
#include <WiFi.h>
#include <SPIFFS.h>
#include <ESPAsyncWebServer.h>

// Global variables
bool on = false;

// WiFi config
const char *ssid = "Rover";
const char *password = "gogogogo";
IPAddress local_ip(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

// Web Server
AsyncWebServer server(80);

void forward()
{
  Serial.println("FORWARD");
  digitalWrite(GPIO_NUM_25, HIGH);
  digitalWrite(GPIO_NUM_26, LOW);

  digitalWrite(GPIO_NUM_16, HIGH);
  digitalWrite(GPIO_NUM_17, LOW);
}

void backward()
{
  Serial.println("BACKWARD");
  digitalWrite(GPIO_NUM_25, LOW);
  digitalWrite(GPIO_NUM_26, HIGH);

  digitalWrite(GPIO_NUM_16, LOW);
  digitalWrite(GPIO_NUM_17, HIGH);
}

void stop()
{
  Serial.println("STOP");
  digitalWrite(GPIO_NUM_25, LOW);
  digitalWrite(GPIO_NUM_26, LOW);

  digitalWrite(GPIO_NUM_16, LOW);
  digitalWrite(GPIO_NUM_17, LOW);
}

void led()
{
  on = !on;
  if (on)
  {
    Serial.println("ON");
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else
  {
    Serial.println("OFF");
    digitalWrite(LED_BUILTIN, LOW);
  }
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

  server.on("/forward", HTTP_GET, [](AsyncWebServerRequest *request) {
    forward();
    request->send(200);
  });

  server.on("/backward", HTTP_GET, [](AsyncWebServerRequest *request) {
    backward();
    request->send(200);
  });

  server.on("/stop", HTTP_GET, [](AsyncWebServerRequest *request) {
    stop();
    request->send(200);
  });

  server.on("/led", HTTP_GET, [](AsyncWebServerRequest *request) {
    led();
    request->send(200);
  });

  server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");

  server.begin();
  Serial.println("Server started, I hope...");

  // Motor
  pinMode(GPIO_NUM_25, OUTPUT);
  pinMode(GPIO_NUM_26, OUTPUT);
  pinMode(GPIO_NUM_16, OUTPUT);
  pinMode(GPIO_NUM_17, OUTPUT);

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
