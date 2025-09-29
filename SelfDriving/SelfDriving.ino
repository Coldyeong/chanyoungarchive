//출력 핀 설정
const int leftLight = 2;
const int rightLight = 3;
const int leftRelay = 4;
const int rightRelay = 5;
const int buzzer = 6;

//입력 핀 설정
const int leftBlink = 7;     // 좌 깜빡이
const int leftKeep = 8;      // 좌 유지
const int rightBlink = 9;    // 우 깜빡이
const int rightKeep = 10;    // 우 유지
const int hornSwitch = 11;   // 경적 스위치

// 깜빡임 제어용 변수
unsigned long prevMillis = 0;
const int blinkInterval = 500; // 0.5초 간격
bool leftBlinkState = false;
bool rightBlinkState = false;

void setup() {
  // 출력 핀 설정
  pinMode(leftLight, OUTPUT);
  pinMode(rightLight, OUTPUT);
  pinMode(leftRelay, OUTPUT);
  pinMode(rightRelay, OUTPUT);
  pinMode(buzzer, OUTPUT);

  // 입력 핀 설정 
  pinMode(leftBlink, INPUT_PULLUP);
  pinMode(leftKeep, INPUT_PULLUP);
  pinMode(rightBlink, INPUT_PULLUP);
  pinMode(rightKeep, INPUT_PULLUP);
  pinMode(hornSwitch, INPUT_PULLUP);

  // 초기값 OFF
  digitalWrite(leftLight, LOW);
  digitalWrite(rightLight, LOW);
  digitalWrite(leftRelay, LOW);
  digitalWrite(rightRelay, LOW);
  digitalWrite(buzzer, LOW);
}

void loop() {
  unsigned long currentMillis = millis();

  // 입력 읽기 (LOW = 스위치 ON)
  int Lblink = digitalRead(leftBlink);
  int Lkeep = digitalRead(leftKeep);
  int Rblink = digitalRead(rightBlink);
  int Rkeep = digitalRead(rightKeep);
  int Horn = digitalRead(hornSwitch);

  // 좌측 라이트
  if (Lkeep == LOW) {   // 유지 모드
    digitalWrite(leftLight, HIGH);
    digitalWrite(leftRelay, LOW);
  } 
  else if (Lblink == LOW) { // 깜빡이 모드
    if (currentMillis - prevMillis >= blinkInterval) {
      prevMillis = currentMillis;
      leftBlinkState = !leftBlinkState;
      digitalWrite(leftLight, leftBlinkState);
      digitalWrite(leftRelay, leftBlinkState);
    }
  } 
  else { // 끄기
    digitalWrite(leftLight, LOW);
    digitalWrite(leftRelay, LOW);
  }

  // 우측 라이트
  if (Rkeep == LOW) {   // 유지 모드
    digitalWrite(rightLight, HIGH);
    digitalWrite(rightRelay, LOW);
  } 
  else if (Rblink == LOW) { // 깜빡이 모드
    if (currentMillis - prevMillis >= blinkInterval) {
      prevMillis = currentMillis;
      rightBlinkState = !rightBlinkState;
      digitalWrite(rightLight, rightBlinkState);
      digitalWrite(rightRelay, rightBlinkState);
    }
  } 
  else { // 끄기
    digitalWrite(rightLight, LOW);
    digitalWrite(rightRelay, LOW);
  }

  // ===== 경적 =====
  if (Horn == LOW) {
    digitalWrite(buzzer, HIGH);
  } else {
    digitalWrite(buzzer, LOW);
  }
}
