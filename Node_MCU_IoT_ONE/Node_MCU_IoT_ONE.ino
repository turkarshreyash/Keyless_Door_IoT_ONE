
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>

#include <BlynkSimpleEsp8266.h>

#define lock 4
#define unlock 5

char auth[] = "cfd9615056d745f79d394bc6962f701d";
char ssid[] = "TESLA";
char pass[] = "MFLOPS45";




void UNLOCK(){
  digitalWrite(lock,LOW);
  digitalWrite(unlock, HIGH);
  delay(50);
  digitalWrite(unlock,LOW);
  digitalWrite(lock,LOW);
}

void LOCK(){
  digitalWrite(lock,HIGH);
  digitalWrite(unlock,LOW);
  delay(50);
  digitalWrite(unlock,LOW);
  digitalWrite(lock,LOW);
}

void setup()
{
  
  Blynk.begin(auth, ssid, pass);
  pinMode(lock,OUTPUT);
  pinMode(unlock,OUTPUT);
  UNLOCK();
}
void loop()
{ 

  Blynk.run(); 
}
BLYNK_WRITE(V0)  // Button Widget in SWITCH mode 
{   
  int value = param.asInt(); // Get value as integer
  if(value){
    LOCK();
  }
}
BLYNK_WRITE(V1)  // Button Widget in SWITCH mode 
{   
  int value = param.asInt(); // Get value as integer

  if(value){
    UNLOCK();
  }
}