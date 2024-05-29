#include<SoftwareSerial.h> 

SoftwareSerial btserial(3,2);
//(아두이노의 RX는 블루투스의 TX에, 아두이노의 TX는 블루투스의 RX에 연결

// 핀 정의
const int enaPin = 6; // 모터 A 속도 제어 핀 (PWM)
const int in1Pin = 5; // 모터 A 방향 제어 핀 1
const int in2Pin = 4;  // 모터 A 방향 제어 핀 2

const int in3Pin = 7;  // 모터 B 방향 제어 핀 1
const int in4Pin = 8;  // 모터 B 방향 제어 핀 2
const int enbPin = 9;  // 모터 B 속도 제어 핀 (PWM)

void setup() {
  btserial.begin(9600); //아두이노와 블루투스끼리의 통신속도를 9600으로 지정
  Serial.begin(9600); //아두이노와 컴퓨터와의 통신속도도 9600으로 지정

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
  //만약 블루투스가 통신가능한 상태라면 아래 코드들을 실행, 아니라면 아무것도 하지 않음
  if(btserial.available()){     
    //문자 형식의 cmd라는 변수를 생성하고 블루투스로부터 들어오는 값을 저장
    char cmd = (char)btserial.read(); 
    //블루투스로부터 들어오는 값을 시리얼모니터에 출력
    Serial.println(cmd); 
    if(cmd == 'a'){ 
      digitalWrite(in1Pin, HIGH);
      digitalWrite(in2Pin, LOW);
      analogWrite(enaPin, 255); // 모터 A 최대 속도
  
      digitalWrite(in3Pin, HIGH);
      digitalWrite(in4Pin, LOW);
      analogWrite(enbPin, 255); // 모터 B 최대 속도
    }    
    else if(cmd == 'b'){ 
      analogWrite(enaPin, 0);
      digitalWrite(in1Pin, LOW);
      digitalWrite(in2Pin, LOW);
  
      analogWrite(enbPin, 0);
      digitalWrite(in3Pin, LOW);
      digitalWrite(in4Pin, LOW);
    }
    else if(cmd == 'c'){
      delay(1000);
    }
  }
}
