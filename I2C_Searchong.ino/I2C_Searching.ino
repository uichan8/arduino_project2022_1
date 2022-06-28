#include <Wire.h>
//27

void setup() {
  Serial.begin(9600);
  Wire.begin();

  while(!Serial);
  Serial.println("\n I2C Scanner");
}

void loop() {
  byte Err, Adr;
  int N_Device;

  Serial.println("Scanning...");

  N_Device = 0;

  for(Adr=1;Adr<127;Adr++) {
    Wire.beginTransmission(Adr);
    Err = Wire.endTransmission();

    if(Err==0){
      Serial.print("I2C device found at address 0x");

      if(Adr<16)
      Serial.print("0");
      Serial.print(Adr, HEX);
      Serial.println(" !");

      N_Device++;
     }
     else if(Err==4) {
      Serial.print("Unknown error at address 0x");
      if(Adr<16)
      Serial.print("0");
      Serial.print(Adr, HEX);
     }
  }
   if(N_Device==0)
   Serial.println("No I2C device found\n");

   delay(5000);
}
