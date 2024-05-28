#include <SPI.h>

volatile bool newAngleReceived = false;
volatile int receivedAngle = 0;

void setup() {
  DDRB |= (1 << MISO);       // MISO 핀을 출력으로 설정
  SPCR |= (1 << SPE);            // SPI 활성화
  SPCR |= (1 << SPIE);           // SPI 인터럽트 활성화

  Serial.begin(9600);
  Serial.println("Slave ready");
}

void loop() {
  if (newAngleReceived) {
    Serial.print("Received angle: ");
    Serial.println(receivedAngle);
    newAngleReceived = false;  // 플래그 초기화
  }
}

ISR(SPI_STC_vect) {
  static byte highByte = 0;
  static bool highByteReceived = false;

  if (!highByteReceived) {
    highByte = SPDR;             // 상위 바이트 읽기
    highByteReceived = true;
  } 
  else {
    byte lowByte = SPDR;         // 하위 바이트 읽기
    receivedAngle = (highByte << 8) | lowByte; // 상위 바이트와 하위 바이트 결합
    highByteReceived = false;
    newAngleReceived = true;     // 데이터 수신 완료 플래그 설정
  }
}
