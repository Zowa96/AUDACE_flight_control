#include <SD.h>
#include <SPI.h>
#include <Wire.h>
#include <NewPing.h>    //libreria per Ultrasuoni

#include "MemorySD.h"
#include "Ultrasound.h"

unsigned long myTime;


void setup() {

  Serial.begin(9600);
  
  //inizializzo la memoria, se la memoria è inizializzata il LED si accende
  pinMode(LED_BUILTIN, OUTPUT);
  
  bool SDstatus = initializeSDCARD(chip_select);
  if (SDstatus = true){
    Serial.println("memory: OK");
  }
  else{
    Serial.println("memory: NOT OK");
  }

  bool SONAR_status = sonar_setup();
  if (SONAR_status = true){
    Serial.println("sonar: OK");
  }
  else{
    Serial.println("sonar: NOT OK");
  }

}

void loop() {

  //campiono il tempo, dall'inizio dell'esecuzione
  myTime = millis();


  //test per la memoria

  String prova = "marco";
  sdcard_save(prova + String(myTime));

  
}
