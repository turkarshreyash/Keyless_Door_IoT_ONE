
 
#include"Battery_Charge.h"

#include <BlynkSimpleEsp8266.h>

#define BLYNK_PRINT Serial
#define lock 4
#define unlock 5

char auth[] = "cfd9615056d745f79d394bc6962f701d";
char ssid[] = "TESLA";
char pass[] = "MFLOPS45";
int battery_pin = A0;
int charge_enable = 14;
int indi_led = 12;

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


Battery battery(battery_pin,charge_enable);

void setup() {
  Blynk.begin(auth, ssid, pass);
  pinMode(lock,OUTPUT);
  pinMode(unlock,OUTPUT);
  pinMode(charge_enable,OUTPUT);
  pinMode(indi_led,OUTPUT);
  delay(10);
  
}
 
void loop() {
  delay(50);
  digitalWrite(indi_led,HIGH);
  battery.charge_check();
  Blynk.run();
  delay(50);   
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
 BLYNK_READ(V2){
  Blynk.virtualWrite(V2,battery.check_voltage());
 
 }

 BLYNK_WRITE(V3) // Button Widget in SWITCH mode
 {
   int value = param.asInt(); // Get value as integer
   if (value)
   {
     battery.start_charging();
   }else{
     battery.stop_charging();
   }
 }
 BLYNK_READ(V4)
 {
   if(battery.ischarging()){
     Blynk.virtualWrite(V3, HIGH);
     Blynk.virtualWrite(V4, battery.charging_since()/60000);
   }else{
     Blynk.virtualWrite(V4, -1);
     Blynk.virtualWrite(V3, LOW);
   }
   
 }
