//sensor
#define target_pin 11
#define echo_pin 12

//segment
#define led_start_pin 2

int segement_array[10][7] = {
  {1,1,1,1,1,1,0},
  {0,1,1,0,0,0,0},
  {1,1,0,1,1,0,1},
  {1,1,1,1,0,0,1},
  {0,1,1,0,0,1,1},
  {1,0,1,1,0,1,1},
  {1,0,1,1,1,1,1},
  {1,1,1,0,0,0,0},
  {1,1,1,1,1,1,1},
  {1,1,1,1,0,1,1}
};

void segement_off(){
  for(int i = 0; i < 7; i++)
    digitalWrite(led_start_pin+i,LOW);
}
void show_number(int a){
  for(int i = 0; i < 7; i++){
    if(segement_array[a][i] == 1)
      digitalWrite(led_start_pin+i,HIGH);
  }
}

void setup() {
  for(int i = 0; i < 7; i++)
      pinMode(led_start_pin + i,OUTPUT);
  pinMode(target_pin,OUTPUT);
  pinMode(echo_pin,INPUT);  
  Serial.begin(9600);
}

int past_state = 0;
int clock = 0;

void loop() {
  //read from sensor
  digitalWrite(target_pin,LOW);
  delayMicroseconds(2);
  digitalWrite(target_pin,HIGH);
  delayMicroseconds(10);
  digitalWrite(target_pin,LOW);

  //calculate  distance
  long distime = pulseIn(echo_pin,HIGH);
  if(distime == 0) return;

  int distance = distime/58.2 ;
  int segement_out = (distance/10);

  if(segement_out > 9) segement_out = 9;
  else segement_out %= 10;
  int time = segement_out*50;
  
  //segment management
  if(past_state != segement_out) clock = 0;

  if(clock < time/2)show_number(segement_out);
  else segement_off();

  past_state = segement_out;
  clock++;
  clock %= time;
  Serial.println(distance);
  delay(10);
}
