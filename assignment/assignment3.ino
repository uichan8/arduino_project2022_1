#include<Servo.h> // Servo 라이브러리를 추가
Servo servo;      // Servo 클래스로 servo객체 생성

void setup() {
  servo.attach(9);    // servo 서보모터 9번 핀에 연결
  pinMode(7,INPUT);   // 원근센서 7번핀
  Serial.begin(9600); // 변수들을 보기 위해 시리얼 번호를 설정
}

void loop() {
  //센서와 가변저항 인식
  int detect       = digitalRead(7);  // 적외선 센서 입력 0,1
  int analog_input = analogRead(A0);  // 가변저항 입력 0~1023 인데 잡음때문에 1의 자리수가 왔다갔다함
  Serial.print("detect : ");          // 시리얼 화면 출력
  Serial.print(detect);
  Serial.print(" analog_in : ");
  Serial.print(analog_input);

  //가변저항 0 ~ 180 사이에 오게 하기
  analog_input /= 10;                            // 10으로 나눠주면 1에자리에서 왔다 갔다하는 것을 막아주겠죠
  analog_input = map(analog_input,0,102,0,180);  // 0부터 180까지로 매핑시켜줍니다.
  Serial.print(" switch_angle : ");              //값 출력
  Serial.print(analog_input);

  //센서 물체가 있으면 1 없으면 0으로 하게 하기
  //이부분이 제가 아까 반대로 결과가 나왔던거 같은데 확인해 보시고 주석을 지우세요
  //if(detect == 1) detect = 0;         // 1과 0을 서로 바꿔주는 과정
  //else            detect = 1;
  //Serial.print(" detector_input : "); // 화면 출력
  //Serial.print(detect);

  //모터의 회전
  int angle = 0;                             // 모터 회전 각도
  if(analog_input > 5) angle = analog_input; // 가변저항이 일정 크기 이상 돌아가게 된다면 각도는 가변저항에 맞게 변합니다.
  else                 angle = detect * 180; // 가변저항이 안돌아가 있으면 탐지되면 180 탐지안되면 0
  servo.write(angle);                        // 모터 회전
  Serial.print(" moter_angle_angle : ");     // 값 출력
  Serial.println(angle);
}