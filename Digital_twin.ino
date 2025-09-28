#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "P";           // your WiFi SSID
const char* password = "stranger"; // your WiFi password

String serverName = "http://10.127.169.185:5000/update";  // Flask backend

// Button pins
const int btn1 = D1;
const int btn2 = D2;
const int btn3 = D3;
const int btn4 = D4;
const int btn5 = D5;

void setup() {
  Serial.begin(115200);

  // WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" Connected!");

  // Setup buttons
  pinMode(btn1, INPUT_PULLUP);
  pinMode(btn2, INPUT_PULLUP);
  pinMode(btn3, INPUT_PULLUP);
  pinMode(btn4, INPUT_PULLUP);
  pinMode(btn5, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(btn1) == LOW) sendBattery(25);
  if (digitalRead(btn2) == LOW) sendBattery(50);
  if (digitalRead(btn3) == LOW) sendBattery(75);
  if (digitalRead(btn4) == LOW) sendBattery(100);
  if (digitalRead(btn5) == LOW) sendBattery(0);
  delay(200);  // debounce
}

void sendBattery(int level) {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;
    String url = serverName + "?level=" + String(level);
    Serial.println("Sending request to: " + url);

    http.begin(client, url);  // ✅ correct method
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      Serial.println("Battery update sent: " + String(level) + "%, Response: " + http.getString());
    } else {
      Serial.println("❌ Error sending request, code: " + String(httpResponseCode));
    }
    http.end();
  } else {
    Serial.println("⚠️ WiFi not connected");
  }
}
