#include "esp_camera.h"
#include <WiFi.h>
#include <WebServer.h>

// ================= CAMERA PINS =================

#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27

#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5

#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22

// ================= WIFI =================

const char* ssid = "Vivo";
const char* password = "123456789";

WebServer server(80);

// ================= CAMERA =================

void startCamera()
{
  camera_config_t config;

  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;

  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;

  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;

  config.pin_sccb_sda = SIOD_GPIO_NUM;
  config.pin_sccb_scl = SIOC_GPIO_NUM;

  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;

  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;

  config.frame_size = FRAMESIZE_QVGA;
  config.jpeg_quality = 12;
  config.fb_count = 1;

  Serial.println("Starting camera...");

  esp_err_t err = esp_camera_init(&config);

  if (err != ESP_OK)
  {
    Serial.printf("CAMERA FAILED: 0x%x\n", err);
    while (true)
    {
      delay(1000);
    }
  }

  Serial.println("CAMERA OK!");
}

// ================= WEB PAGE =================

void handleRoot()
{
  String html = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>ESP32-CAM</title>

<style>
body {
  font-family: Arial;
  text-align: center;
  background: #222;
  color: white;
}

h1 {
  margin-top: 20px;
}

img {
  width: 320px;
  height: 240px;
  border: 3px solid white;
}

button {
  margin-top: 20px;
  padding: 12px 25px;
  font-size: 18px;
}
</style>

</head>

<body>

<h1>ESP32-CAM</h1>

<img id="camera" src="/capture">

<br>

<button onclick="refreshImage()">Capture Photo</button>

<script>

function refreshImage()
{
  document.getElementById("camera").src =
  "/capture?t=" + new Date().getTime();
}

setInterval(refreshImage, 500);

</script>

</body>
</html>
)rawliteral";

  server.send(200, "text/html", html);
}

// ================= CAPTURE =================

void handleCapture()
{
  camera_fb_t *fb = esp_camera_fb_get();

  if (!fb)
  {
    Serial.println("CAPTURE FAILED!");

    server.send(500, "text/plain", "Camera capture failed");

    return;
  }

  Serial.printf("Photo captured: %d bytes\n", fb->len);

  server.send_P(
    200,
    "image/jpeg",
    (const char *)fb->buf,
    fb->len
  );

  esp_camera_fb_return(fb);
}

// ================= SETUP =================

void setup()
{
  Serial.begin(115200);

  delay(2000);

  Serial.println();
  Serial.println("==============================");
  Serial.println("ESP32-CAM STARTING");
  Serial.println("==============================");

  // Start camera
  startCamera();

  // Start WiFi
  Serial.println();
  Serial.println("Connecting to WiFi...");

  WiFi.begin(ssid, password);

  int count = 0;

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);

    Serial.print(".");

    count++;

    if (count > 30)
    {
      Serial.println();
      Serial.println("WiFi connection failed!");
      Serial.println("Check SSID and password.");

      return;
    }
  }

  Serial.println();
  Serial.println("==============================");
  Serial.println("WIFI CONNECTED!");
  Serial.println("==============================");

  Serial.print("IP ADDRESS: ");
  Serial.println(WiFi.localIP());

  Serial.println("==============================");

  // Web server
  server.on("/", handleRoot);
  server.on("/capture", handleCapture);

  server.begin();

  Serial.println("Web server started!");
  Serial.println();
  Serial.println("Open the IP address shown above");
  Serial.println("in Chrome.");
}

// ================= LOOP =================

void loop()
{
  server.handleClient();
}