//creo una classe Memory, con una funzione di scrittura, un'oggetto semplice da implementare nel main
#ifndef memorySD
#define memorySD

#define chip_select 4

/* initializeSDCARD:
input:il cip della scheda SD, OUTPUT: da un risultato negativo se la memoria non è presente. Altrimenti esegue sdcard_clear:
TRUE: SD card è inizializzata
FALSE: non è stato cancellato il file di salvataggio
*/


//non restituisce alcun valore, salva direttamente la stringa sul file: "datalog.txt"

void sdcard_save(String input_data) {

  //apro il file per la scrittura
  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  //TODO manage the scenareo where sdcard is full
  //if system online report to app
  //if system offline start blinking device

  //If the file is available, write to it:
  if (dataFile) {
    dataFile.print(input_data);
    dataFile.print(",");  //This caracter is used to end the clock cycle
    dataFile.close();
  }

  // If the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }
}

/* initializeSDCARD:
input:il cip della scheda SD, OUTPUT: da un risultato negativo se la memoria non è presente. Altrimenti esegue sdcard_clear:
TRUE: SD card è inizializzata
FALSE: non è stato cancellato il file di salvataggio
*/


bool initializeSDCARD(int chipSelect) {
  Serial.print("Initializing SD card...");
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("SDCARD failed, or not present");
    // don't do anything more:
    return false;
  }
  else{
    SD.remove("datalog.txt");
    if (SD.exists("datalog.txt")) {
    Serial.println("SDCARD error deleting datalog.txt");
    return false;
  } else {
    Serial.println("SDCARD initialized.");
    return true;
  }
  }
}
#endif












