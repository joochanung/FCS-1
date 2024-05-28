#include <SPI.h>
#include <Servo.h>

Servo servo;

const int slaveSelectPin = 10;

void setup() {
  pinMode(slaveSelectPin, OUTPUT);
  digitalWrite(slaveSelectPin, HIGH); // SS를 비활성화 상태로 시작
  SPI.begin();
  Serial.begin(9600);
  servo.attach(9);
  servo.write(0);
}

void loop() {
  // 여기에 모터의 각도를 측정하는 코드를 작성합니다.
  // 예를 들어, 각도 값을 읽어오는 함수가 있다고 가정합니다.
  int motorAngle = getMotorAngle(90); // 모터 각도를 읽어오는 함수
  // 슬레이브에게 각도 데이터를 전송
  sendAngleToSlave(motorAngle);
  delay(1000); // 1초에 한 번씩 전송

  motorAngle = getMotorAngle(0);
  sendAngleToSlave(motorAngle);
  delay(1000);
}

int getMotorAngle(int angle) {
  // 모터 각도를 측정하는 코드를 여기에 작성합니다.
  // 예제에서는 임의의 각도를 반환합니다.
  servo.write(angle);
  return angle; // 0도에서 360도 사이의 임의의 값
}

void sendAngleToSlave(int angle) {
  byte highByte = (angle >> 8) & 0xFF; // 상위 8비트
  byte lowByte = angle & 0xFF;         // 하위 8비트

  digitalWrite(slaveSelectPin, LOW);   // 슬레이브 선택
  SPI.transfer(highByte);              // 상위 바이트 전송
  SPI.transfer(lowByte);               // 하위 바이트 전송
  digitalWrite(slaveSelectPin, HIGH);  // 슬레이브 비선택

  Serial.print("Sent angle: ");
  Serial.println(angle);
}
