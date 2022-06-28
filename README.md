# arduino_project2022_1
## 요약
2022년 1학기 양철관 교수님 창업연계공학설계 수업의 기말과제 내용입니다.  
주어진 과제는 다음 이미지과 같습니다.  
![assignment](https://github.com/uichan8/arduino_project2022_1/blob/main/pictures/assignment.png)

## 기능 소개
### 회로 구성
![circuit](https://github.com/uichan8/arduino_project2022_1/blob/main/pictures/circuit.png)  
  
### 초기 설정
1. 먼저 <I2C_searching.ino> 파일을 실행하여 시리얼 모니터로 lcd 장치의 주소를 가져옵니다.
2. <clock.ino>파일에서 위에서 얻은 주소로 바꿔줍니다.
3. button_pin 변수에서 구성된 회로에 버튼의 핀번호를 입력해줍니다.(기본 3,4,5,6,7)

### 시계
기본적인 시간을 나타냅니다. 왼쪽의 상태바는 10초마다 한개씩 차며, 60초마다 리셋됩니다.
![clock](https://github.com/uichan8/arduino_project2022_1/blob/main/pictures/clock.png) 

__버튼__  
버튼 1: 시계의 초를 조정합니다.  
버튼 2: 시계의 분을 조정합니다.  
버튼 3: 시계의 시간을 조정합니다.  
버튼 4: 시계의 위 3개의 버튼의 기능을 증가시킬 것인지 감소시킬 것인지를 정합니다.  
버튼 5: 모드를 전환시킵니다.  


### 스톱워치
기본적인 스탑워치의 기능을 합니다. 
![stopwatch](https://github.com/uichan8/arduino_project2022_1/blob/main/pictures/stopwatch.png)

__버튼__  
버튼 1: start/stop  
버튼 2: 순간적인 시간을 기록합니다.  
버튼 3: reset  
버튼 4:  
버튼 5: 모드를 전환시킵니다. 
