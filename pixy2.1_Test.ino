/* 
준비물: pixy2.1, SG90 tilt용 서보모터, ICSP-pixy2.1 연결 케이블
전기 회로 구성 방법: 1. 아두이노 우노의 ICSP(6핀)랑 pixy2.1(10핀)이랑 연결한다.
                    2. pixy2.1의 6핀은 모터 2개를 연결할 수 있는 부분이다. 그래서 
*/

#include <SPI.h>
#include <Pixy2.h>
#include <Servo.h>

Pixy2 pixy;
Servo servo;

int panPos = 90;  // 초기 서보 위치를 90도로 설정
int servoPin = 9; // 서보 핀을 Arduino의 핀 9로 설정

void setup() {
  pixy.init();
  servo.attach(servoPin);
  servo.write(panPos);
}

void loop() {
  // Pixy2.1이 블록을 감지하는지 확인
  pixy.ccc.getBlocks();
  
  if (pixy.ccc.numBlocks) {
    // 첫 번째 블록의 중심 Y 좌표를 가져옴
    int blockY = pixy.ccc.blocks[0].m_y;
    int centerY = (pixy.frameHeight / 2);  // Pixy2.1의 화면 세로 중심

    // 서보 위치를 제한 범위 내로 유지 (0도 ~ 180도)
    panPos = constrain(panPos, 0, 180);
    
    // 물체가 중앙에서 벗어나 있는 경우 중앙에 위치할 때까지 서보를 움직임
    if (blockY < centerY - 10) {
      while(blockY - centerY <=0){
        panPos += 1; // 물체가 중앙보다 아래에 있으면 서보를 위로 이동
        servo.write(panPos);
        delay(10);
      }
    } 
    else if (blockY > centerY + 10) {
      while(blockY - centerY >= 0){
        panPos -= 1; // 물체가 중앙보다 위에 있으면 서보를 아래로 이동
        servo.write(panPos);
        delay(10);
      }
    }
    delay(10);
  }
  
  delay(20); // 서보 모터의 이동 시간을 위해 딜레이 추가
}
