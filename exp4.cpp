
#include <WiFi.h>
#include <WebServer.h>

// Wi-Fi details
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

// Potentiometer pin
const int potPin = 34;

// Create web server
WebServer server(80);

// Function to display sensor value
void handleRoot() {

  int potValue = analogRead(potPin);

  String webpage = "<html><body>";
  webpage += "<h2>ESP32 Sensor Monitoring</h2>";
  webpage += "<h3>Potentiometer Value: ";
  webpage += String(potValue);
  webpage += "</h3>";
  webpage += "<p>Rotate the potentiometer to change the value.</p>";
  webpage += "</body></html>";

  server.send(200, "text/html", webpage);
}

void setup() {

  Serial.begin(115200);

  pinMode(potPin, INPUT);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);

  Serial.println("Connecting to Wi-Fi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWi-Fi Connected");

  // Display IP address
  Serial.println(WiFi.localIP());

  // Set webpage route
  server.on("/", HTTP_GET, handleRoot);

  // Start web server
  server.begin();

  Serial.println("Web server started");
}

void loop() {

  server.handleClient();

  delay(100);
}
