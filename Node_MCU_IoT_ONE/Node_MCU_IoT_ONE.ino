
 
#include"Battery_Charge.h"

#include <BlynkSimpleEsp8266.h>

#define BLYNK_PRINT Serial
#define lock 4
#define unlock 5

char auth[] = "cfd9615056d745f79d394bc6962f701d";
char ssid[] = "TESLA";
char pass[] = "MFLOPS45";
int battery_pin = A0;
int power_supply = 2;
int charge_enable = 12;
int indi_led = 14;

void UNLOCK(){
  digitalWrite(lock,LOW);
  digitalWrite(unlock, HIGH);
  delay(500);
  digitalWrite(unlock,LOW);
  digitalWrite(lock,LOW);
}

void LOCK(){
  digitalWrite(lock,HIGH);
  digitalWrite(unlock,LOW);
  delay(500);
  digitalWrite(unlock,LOW);
  digitalWrite(lock,LOW);
}


Battery battery(battery_pin,charge_enable,power_supply);

void setup() {
  Blynk.begin(auth, ssid, pass);
  pinMode(lock,OUTPUT);
  pinMode(unlock,OUTPUT);
  pinMode(power_supply,INPUT);
  pinMode(charge_enable,OUTPUT);
  pinMode(indi_led,OUTPUT);
  delay(10);
  
}
 
void loop() {
  delay(500);
  digitalWrite(indi_led,HIGH);
  battery.charge_check();
  Blynk.run();
  delay(500);   
  digitalWrite(indi_led,LOW);
 
}



BLYNK_WRITE(V0)  // Button Widget in SWITCH mode 
{   
  int value = param.asInt(); // Get value as integer
  if(value){
    LOCK();
    Blynk.virtualWrite(V0,LOW);
  }
}
BLYNK_WRITE(V1)  // Button Widget in SWITCH mode 
{   
  int value = param.asInt(); // Get value as integer

  if(value){
    UNLOCK();
    Blynk.virtualWrite(V1, LOW);
  }
  }
