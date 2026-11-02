
#include <WiFi.h>
#include <WebServer.h>

// Wi-Fi details
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

// LED pins
const int led1 = 12;
const int led2 = 14;

// Create web server on port 80
WebServer server(80);

// Create webpage
String webpage() {
  String html = "<html><body>";
  html += "<h2>ESP32 LED Control</h2>";

  html += "<h3>LED 1</h3>";
  html += "<a href='/12/on'><button>LED 1 ON</button></a>";
  html += "<a href='/12/off'><button>LED 1 OFF</button></a>";

  html += "<h3>LED 2</h3>";
  html += "<a href='/14/on'><button>LED 2 ON</button></a>";
  html += "<a href='/14/off'><button>LED 2 OFF</button></a>";

  html += "</body></html>";
  return html;
}

void setup() {
  Serial.begin(115200);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);

  Serial.println("Connecting to Wi-Fi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWi-Fi Connected");
  Serial.println(WiFi.localIP());

  // Display webpage
  server.on("/", []() {
    server.send(200, "text/html", webpage());
  });

  // LED 1 control
  server.on("/12/on", []() {
    digitalWrite(led1, HIGH);
    server.send(200, "text/html", webpage());
  });

  server.on("/12/off", []() {
    digitalWrite(led1, LOW);
    server.send(200, "text/html", webpage());
  });

  // LED 2 control
  server.on("/14/on", []() {
    digitalWrite(led2, HIGH);
    server.send(200, "text/html", webpage());
  });

  server.on("/14/off", []() {
    digitalWrite(led2, LOW);
    server.send(200, "text/html", webpage());
  });

  server.begin();
  Serial.println("Web server started");
}

void loop() {
  server.handleClient();
}
