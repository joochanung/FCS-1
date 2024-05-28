#include<SoftwareSerial.h> 

SoftwareSerial btserial(3,2);
//(아두이노의 RX는 블루투스의 TX에, 아두이노의 TX는 블루투스의 RX에 연결

#define led 7 
#define led2 6

void setup() {
  btserial.begin(9600); //아두이노와 블루투스끼리의 통신속도를 9600으로 지정
  Serial.begin(9600); //아두이노와 컴퓨터와의 통신속도도 9600으로 지정
  pinMode(led,OUTPUT); 
  pinMode(led2, OUTPUT);
}

void loop() {
  //만약 블루투스가 통신가능한 상태라면 아래 코드들을 실행, 아니라면 아무것도 하지 않음
  if(btserial.available()){     
    //문자 형식의 cmd라는 변수를 생성하고 블루투스로부터 들어오는 값을 저장
    char cmd = (char)btserial.read(); 
    //블루투스로부터 들어오는 값을 시리얼모니터에 출력
    Serial.println(cmd); 
    if(cmd == 'a'){ 
      digitalWrite(led,HIGH);
    }    
    else if(cmd == 'b'){ 
      digitalWrite(led2,HIGH); 
    }
    else if(cmd == 'c'){
      digitalWrite(led, LOW);
      digitalWrite(led2, LOW);
    }
  }
}