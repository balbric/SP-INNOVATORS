 b binclude <WiFi.h>
#include <esp_now.h>

// ===== TRACKED =====
#define AIN1 14
#define AIN2 27
#define PWMA 33

#define BIN1 26
#define BIN2 25
#define PWMB 32

#define STBY_TRACK 13

// ===== CLEANING =====
#define CIN1 23
#define CIN2 22
#define CPWM 21

// ===== LEAD SCREW =====
#define LIN1 19
#define LIN2 18
#define LPWM 5 
#define STBY_LEAD 12

#define LIMIT_SWITCH 4

// ===== DATA STRUCT =====
typedef struct {
  int forward;
  int turn;
  int mode;

  int cleaningMode;

  bool leadForward;
  bool leadReverse;

} Data;

Data data;

// ===== VARIABLES =====
int centerFwd = 1900;
int centerTurn = 1900;
int speedMode = 2;

int currentLeft = 0;
int currentRight = 0;

// ===== CALLBACK =====
void onReceive(const esp_now_recv_info *info, const uint8_t *incomingData, int len) {
  memcpy(&data, incomingData, sizeof(data));
}

// ===== MOTOR FUNCTION =====
void setMotor(int IN1, int IN2, int PWM, int speed) {
  if (speed > 0) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  } else if (speed < 0) {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    speed = -speed;
  } else {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
  }
  ledcWrite(PWM, speed);
}

// ===== TRACK CONTROL =====
void controlTrack() {
  int fwd = data.forward - centerFwd;
  int trn = data.turn - centerTurn;

  if (abs(fwd) < 100) fwd = 0;
  if (abs(trn) < 100) trn = 0;

  int maxSpeed = (data.mode == 1) ? 120 : (data.mode == 2) ? 180 : 255;

  fwd = map(fwd, -2000, 2000, -maxSpeed, maxSpeed);
  trn = map(trn, -2000, 2000, -maxSpeed, maxSpeed);

  int left  = constrain(fwd + trn, -maxSpeed, maxSpeed);
  int right = constrain(fwd - trn, -maxSpeed, maxSpeed);

  currentLeft  += (left - currentLeft) * 0.2;
  currentRight += (right - currentRight) * 0.2;

  setMotor(AIN1, AIN2, PWMA, currentLeft);
  setMotor(BIN1, BIN2, PWMB, currentRight);
}

// ===== CLEANING CONTROL =====
void controlCleaning() {
  if (data.cleaningMode == 1) {
    digitalWrite(CIN1, HIGH);
    digitalWrite(CIN2, LOW);
    ledcWrite(CPWM, 200);
  } else {
    digitalWrite(CIN1, LOW);
    digitalWrite(CIN2, LOW);
    ledcWrite(CPWM, 0);
  }
}

// ===== LEAD SCREW CONTROL =====
void controlLead() {
  bool limitPressed = (digitalRead(LIMIT_SWITCH) == LOW);

  if (data.leadForward && data.leadReverse) {
    stopLead();
  }
  else if (data.leadForward && !limitPressed) {
    digitalWrite(LIN1, HIGH);
    digitalWrite(LIN2, LOW);
    ledcWrite(LPWM, 200);
  }
  else if (data.leadReverse) {
    digitalWrite(LIN1, LOW);
    digitalWrite(LIN2, HIGH);
    ledcWrite(LPWM, 200);
  }
  else {
    stopLead();
  }
}

void stopLead() {
  digitalWrite(LIN1, LOW);
  digitalWrite(LIN2, LOW);
  ledcWrite(LPWM, 0);
}

// ===== SETUP =====
void setup() {
  Serial.begin(115200);

  // Track
  pinMode(AIN1, OUTPUT); pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT); pinMode(BIN2, OUTPUT);
  pinMode(STBY_TRACK, OUTPUT);
  digitalWrite(STBY_TRACK, HIGH);

  // Cleaning
  pinMode(CIN1, OUTPUT); pinMode(CIN2, OUTPUT);

  // Lead
  pinMode(LIN1, OUTPUT); pinMode(LIN2, OUTPUT);
  pinMode(STBY_LEAD, OUTPUT);
  digitalWrite(STBY_LEAD, HIGH);

  pinMode(LIMIT_SWITCH, INPUT_PULLUP);

  // PWM
  ledcAttach(PWMA, 1000, 8);
  ledcAttach(PWMB, 1000, 8);
  ledcAttach(CPWM, 1000, 8);
  ledcAttach(LPWM, 1000, 8);

  WiFi.mode(WIFI_STA);
  esp_now_init();
  esp_now_register_recv_cb(onReceive);

  Serial.println("🚀 FULL SYSTEM READY");
}

// ===== LOOP =====
void loop() {
  controlTrack();
  controlCleaning();
  controlLead();
}