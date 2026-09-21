#include <WiFi.h>
#include <esp_now.h>

// ===== RECEIVER MAC =====
//uint8_t receiverMAC[] = {0xCC, 0xDB, 0xA7, 0x4A, 0x46, 0x74};
uint8_t receiverMAC[] = {0xD4, 0xE9, 0xF4, 0x79, 0x29, 0x18};


// ===== JOYSTICK =====
#define JOY_FWD 34  
#define JOY_TURN 35
#define MODE_BTN 4

// ===== CLEANING BUTTON =====
#define CLEAN_BTN 25

// ===== LEAD SCREW =====
#define LEAD_FWD 14
#define LEAD_REV 27

// ===== DATA STRUCT =====
typedef struct {
  int forward;
  int turn;
  int mode;

  int cleaningMode;   // 0=STOP,1=FWD

  bool leadForward;
  bool leadReverse;

} Data;

Data data;

// ===== VARIABLES =====
int speedMode = 2;
bool lastBtn = HIGH;

void setup() {
  Serial.begin(115200);

  pinMode(MODE_BTN, INPUT_PULLUP);
  pinMode(CLEAN_BTN, INPUT_PULLUP);
  pinMode(LEAD_FWD, INPUT_PULLUP);
  pinMode(LEAD_REV, INPUT_PULLUP);

  WiFi.mode(WIFI_STA);
  esp_now_init();

  esp_now_peer_info_t peer = {};
  memcpy(peer.peer_addr, receiverMAC, 6);
  peer.channel = 0;
  peer.encrypt = false;
  peer.ifidx = WIFI_IF_STA;

  esp_now_add_peer(&peer);

  Serial.println("🚀 COMBINED TRANSMITTER READY");
}

void loop() {

  // ===== TRACKED =====
  data.forward = analogRead(JOY_FWD);
  data.turn    = analogRead(JOY_TURN);

  // Speed mode button
  bool btn = digitalRead(MODE_BTN);
  if (lastBtn == HIGH && btn == LOW) {
    speedMode++;
    if (speedMode > 3) speedMode = 1;
    delay(300);
  }
  lastBtn = btn;
  data.mode = speedMode;

  // ===== CLEANING =====
  data.cleaningMode = (digitalRead(CLEAN_BTN) == LOW) ? 1 : 0;

  // ===== LEAD SCREW =====
  data.leadForward = (digitalRead(LEAD_FWD) == LOW);
  data.leadReverse = (digitalRead(LEAD_REV) == LOW);

  // ===== SEND =====
  esp_now_send(receiverMAC, (uint8_t *)&data, sizeof(data));

  // DEBUG
  Serial.print("FWD:");
  Serial.print(data.forward);
  Serial.print(" TURN:");
  Serial.print(data.turn);
  Serial.print(" MODE:");
  Serial.print(speedMode);
  Serial.print(" CLEAN:");
  Serial.print(data.cleaningMode);
  Serial.print(" LF:");
  Serial.print(data.leadForward);
  Serial.print(" LR:");
  Serial.println(data.leadReverse);

  delay(50);
}