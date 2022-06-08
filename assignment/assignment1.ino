int led_start_pin = 2;
int button_pin = 10;

int count = 0;
int number = 0;
int past_state = 0;
int present_state = 0;

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
  pinMode(button_pin,INPUT);
  Serial.begin(9600);
}

void loop() {
  past_state = present_state;
  present_state = digitalRead(button_pin);
  if(past_state == 0 && present_state == 1) count++;

  number = count % 10;
  segement_off();
  show_number(number);

  Serial.print(number);
  Serial.println();
}
