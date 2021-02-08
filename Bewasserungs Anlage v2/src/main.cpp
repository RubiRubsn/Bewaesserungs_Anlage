#include <Arduino.h>
#include <FS.h> 
#include"mess_server.h"

#include <EEPROM.h>


Kalibrierung kalibrierung;
kali_dat dat;
mess_server Mess_server;

void setup(){
  EEPROM.begin(5);
  dat=kalibrierung.laden();
  Serial.begin(115200);
  Mess_server.server_init(kalibrierung, dat);
}



void loop(){

}
