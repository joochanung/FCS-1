// 모터 A: 탱크 하부 4개의 DC 모터
// 모터 B: Shooting 장치이지만, 이것을 과감히 없애고 비율 예정

// 핀 정의
const int enaPin = 11; // 모터 A 속도 제어 핀 (PWM)
const int in1Pin = 10; // 모터 A 방향 제어 핀 1
const int in2Pin = 9;  // 모터 A 방향 제어 핀 2

const int enbPin = 6;  // 모터 B 속도 제어 핀 (PWM)
const int in3Pin = 8;  // 모터 B 방향 제어 핀 1
const int in4Pin = 7;  // 모터 B 방향 제어 핀 2

void setup() {
  // 핀 모드 설정
  pinMode(enaPin, OUTPUT);
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);

  pinMode(enbPin, OUTPUT);
  pinMode(in3Pin, OUTPUT);
  pinMode(in4Pin, OUTPUT);
  
  // 초기 상태 설정 (모터 정지)
  analogWrite(enaPin, 0);
  digitalWrite(in1Pin, LOW);
  digitalWrite(in2Pin, LOW);

  analogWrite(enbPin, 0);
  digitalWrite(in3Pin, LOW);
  digitalWrite(in4Pin, LOW);
}

void loop() {
  digitalWrite(in1Pin, LOW);
  digitalWrite(in2Pin, HIGH);
  analogWrite(enaPin, 255); //모터 A 속도 조절
  digitalWrite(in3Pin, HIGH);
  digitalWrite(in4Pin, LOW);
  analogWrite(enbPin, 100); 
}

// PS: 레지스터 비트로 변환 필요
