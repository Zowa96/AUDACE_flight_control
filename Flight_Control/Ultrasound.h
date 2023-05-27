#ifndef distancePing
#define distancePing

#include <NewPing.h>
#include <Wire.h>

//oggetti per AJ-SR04M ultrasuoni


#define TRIGGER_PIN 12      //Dgital pin 12
#define ECHO_PIN 11         //Dgital pin 11
#define MAX_DISTANCE 450    //massima distanza misurabile in cm

//creo un ogetto sonar 
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

//Setup ultrasuoni

bool sonar_setup(){
  pinMode(TRIGGER_PIN, OUTPUT); 
  pinMode(ECHO_PIN, INPUT);
  bool status = true;
  return status;  
}

//Metodo per misurare la distanza acqua scafo

unsigned int sonar_measure(){
 
  unsigned int sonar_read = sonar.ping_cm();

  return sonar_read;

}
#endif