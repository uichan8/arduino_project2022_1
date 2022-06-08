int led_pin = 7;
int button_pin = 8;

int count = 0;
int past_state = 0;
int present_state = 0;
int led = 0;

void setup() {
  pinMode(led_pin,OUTPUT);
  pinMode(button_pin,INPUT);
  Serial.begin(9600);
}

void loop() {
  present_state = digitalRead(button_pin);

  if(count == 5 && led == 0) {digitalWrite(led_pin,HIGH); count = 0; led = 1;}
  if(count == 2 && led == 1) {digitalWrite(led_pin,LOW);count = 0; led = 0;}

  Serial.println(count);

  past_state = present_state;
}
