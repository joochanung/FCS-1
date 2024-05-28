#include <Pixy2.h>
#include <PIDLoop.h>
#include <Wire.h>
#include "Adafruit_VL53L1X.h"

#define IRQ_PIN 2
#define XSHUT_PIN 3

// Pixy2 객체 생성
Pixy2 pixy;
PIDLoop panLoop(400, 0, 400, true);
PIDLoop tiltLoop(500, 0, 500, true);

// VL53L1X 객체 생성
Adafruit_VL53L1X vl53 = Adafruit_VL53L1X(XSHUT_PIN, IRQ_PIN);

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);
  Serial.println(F("Starting Pixy2 and VL53L1X sensor demo"));

  // Pixy2 초기화
  pixy.init();
  pixy.changeProg("color_connected_components");

  // VL53L1X 초기화
  Wire.begin();
  if (!vl53.begin(0x29, &Wire)) {
    Serial.print(F("Error initializing VL53L1X: "));
    Serial.println(vl53.vl_status);
    while (1) delay(10);
  }
  Serial.println(F("VL53L1X sensor initialized"));

  // 거리 측정 시작
  if (!vl53.startRanging()) {
    Serial.print(F("Couldn't start ranging: "));
    Serial.println(vl53.vl_status);
    while (1) delay(10);
  }
  Serial.println(F("Ranging started"));

  // 타이밍 예산 설정
  vl53.setTimingBudget(50);
  Serial.print(F("Timing budget (ms): "));
  Serial.println(vl53.getTimingBudget());
}

void loop() {
  static int i = 0;
  int32_t panOffset, tiltOffset;
  int16_t distance;

  // Pixy2로부터 블록 데이터를 가져옴
  pixy.ccc.getBlocks();
  
  if (pixy.ccc.numBlocks) {
    i++;
    if (i % 60 == 0) Serial.println(i);

    // 팬 및 틸트 오프셋 계산
    panOffset = (int32_t)pixy.frameWidth / 2 - (int32_t)pixy.ccc.blocks[0].m_x;
    tiltOffset = (int32_t)pixy.ccc.blocks[0].m_y - (int32_t)pixy.frameHeight / 2;

    // PID 루프 업데이트
    panLoop.update(panOffset);
    tiltLoop.update(tiltOffset);

    // 서보 모터 제어
    pixy.setServos(panLoop.m_command, tiltLoop.m_command);

    // VL53L1X 거리 측정
    if (vl53.dataReady()) {
      distance = vl53.distance();
      if (distance == -1) {
        Serial.print(F("Couldn't get distance: "));
        Serial.println(vl53.vl_status);
      } else {
        Serial.print(F("Distance: "));
        Serial.print(distance);
        Serial.println(" mm");
      }
      vl53.clearInterrupt();
    }
  } else {
    // 블록이 인식되지 않으면 팬 및 틸트 루프 리셋
    panLoop.reset();
    tiltLoop.reset();
    pixy.setServos(panLoop.m_command, tiltLoop.m_command);
  }

  // 측정 간격 조절
  delay(100);
}
