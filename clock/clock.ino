#include <LiquidCrystal_I2C.h>

int button_pin[5] = {3, 4, 5, 6, 7};
LiquidCrystal_I2C lcd(0x27,16,2);

unsigned long DAY_TO_SEC = 86400; // 24*60*60

unsigned long set_time = 0;

int DetectButton();
void PrintTime(unsigned long a, int x, int y);
void setTime();


//-----------------------------------------------------------------------------------------
//main
void setup() {
 Serial.begin(9600);
 lcd.init();
 lcd.backlight();
 for(int i = 0; i < 5; ++i)
  pinMode(button_pin[i], INPUT);
}

void loop(){
  TimeMode();
  delay(200);
  stopwatch();
  delay(200);
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
//detect button
int DetectButton(){
  // 버튼을 탐지하는 함수입니다.
  for(int i = 0; i < 5; ++i)
    if(digitalRead(button_pin[i])) return i+1;
  return 0;
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
//print time
void PrintTime(unsigned long a, int x, int y){
  //초단위의 시간을 넣으면 시간 문자열을 인쇄(모니터의 x,y 좌표 도 입력)
  char AM_PM[] = {'P','M','\0'};
  if(a < DAY_TO_SEC/2)
    AM_PM[0] = 'A';
  int second = a % 60;
  int minute = a % (60 * 60) / 60;
  int hour = a / (60 * 60)%12;
  if (a >= DAY_TO_SEC/2 && hour == 0) hour = 12;
  // 시리얼 모니터 출력
  //Serial.print(AM_PM);Serial.print(' ');Serial.print(hour);Serial.print(':');Serial.print(minute);Serial.print('/');Serial.println(second);
  // lcd 출력
  lcd.setCursor(y,x);
  lcd.print(AM_PM);lcd.print(' ');
  if(hour < 10) lcd.print(' '); lcd.print(hour);lcd.print(':');
  if(minute < 10) lcd.print('0'); lcd.print(minute);lcd.print(':'); 
  if(second < 10) lcd.print('0'); lcd.print(second);
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
//settime
//변수                                  
int sign_toggle = 1; 
unsigned long last_detect_time = 0;

void setTime(){
  // 누르는 버튼에 따라서 사용자가 시간을 설정하는 함수입니다.
  int button_number = DetectButton();
  if(millis() - last_detect_time < 200) return;
  switch(button_number){
    case 0:
      return;
    
    case 1:
      set_time = (set_time +  sign_toggle + DAY_TO_SEC) % DAY_TO_SEC;
      break;  
        
    case 2:
      set_time = (set_time + 60 * sign_toggle + DAY_TO_SEC) % DAY_TO_SEC;
      break;
        
    case 3:
      set_time = (set_time + 60 * 60 * sign_toggle + DAY_TO_SEC) % DAY_TO_SEC;
      break;
        
    case 4:
      sign_toggle *= -1;
      break;
  }
  last_detect_time = millis();
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
//time mode
//변수
unsigned long checkTime = 0;

void TimeMode(){
  lcd.clear();
  lcd.setCursor(0,0);lcd.print(" CLOCK");
  lcd.print("  [     ]");
  unsigned long current_time = 0;
  unsigned long temp_time = 0;
  while(true){
    setTime();
    if(DetectButton() == 5) return;
    current_time = millis()/1000 + set_time % DAY_TO_SEC;
    if(temp_time != current_time){
      lcd.setCursor(0,1);lcd.print("                ");
      int time_position  = current_time % 10 - 5;
      PrintTime(current_time,1,5-abs(time_position));
      temp_time = current_time;
      int stamp_position = current_time % 60 / 10;
      lcd.setCursor(9,0);lcd.print("     ");
      lcd.setCursor(9,0);
      for(int i = 0; i < stamp_position; i++) lcd.print("#");
      }
     }
   }

//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
//print stop watch time
void PrintStopWatch(unsigned long a, int b, int c){
  a /= 10 ;
  int mili_sec = a%100;
  int sec = a/100 % 60;
  int minuite = a /100/60;
  lcd.setCursor(c,b);
  if(minuite<10) lcd.print('0');
  lcd.print(minuite);lcd.print(':');
  if(sec<10) lcd.print('0');
  lcd.print(sec);lcd.print('.');
  if(mili_sec<10) lcd.print('0');
  lcd.print(mili_sec);
}
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
//stop watch
void stopwatch(){
  bool stop = true;
  unsigned long stopwatch_time = 0;
  unsigned long start_time = 0;
  unsigned long saved_time = 0;
  unsigned long capture = 0;
  unsigned long last_detect_time = 0;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Stop");
  lcd.setCursor(2,1);
  lcd.print("Watch");
  while(true){
    if(millis() - last_detect_time > 200){
      switch(DetectButton()){
        case 0:
          break;
      
        case 1:
          if(!stop) saved_time += millis() - start_time;
          stop = stop?false:true;
          last_detect_time = millis();
          break;  
          
       case 2:
          capture = stopwatch_time;
          last_detect_time = millis();
          break;
        
        case 3:
          stop = true;
          stopwatch_time = 0;
          saved_time = 0;
          capture = 0;
          last_detect_time = millis();
          break;

        case 5:
          return;
    }
    }
    
    if(stop){
      start_time = millis();
    }
    stopwatch_time = millis() - start_time + saved_time;
    PrintStopWatch(stopwatch_time,0,8);
    PrintStopWatch(capture,1,8);
  }
}
//-----------------------------------------------------------------------------------------
