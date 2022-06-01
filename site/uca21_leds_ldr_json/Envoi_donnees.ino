// données envoyées au format JSON (pour MQTT) sur le port série

void EnvoiDonnees() {// fonction qui envoie les valeurs de l'éclairement et du temps  {"E_Lux":E_Lux,"temps":leTemps})
  
  // mesure du temps en secondes
  unsigned long CurrentTime = millis(); //(long > 32 bits, int > 16 bits, byte > 8bits ,float > 32 bits)

  //calcul Eclairement en Lux
  E_Lux = lectureLum();
  float leTemps = CurrentTime/1000;
  // envoi des données au format JSON
  String chaine = "{\"E_Lux\":";   // il faut toujours initialiser la chaine avant de concaténer à la ligne suivante
  Serial.println(chaine + E_Lux + ",\"temps\":"+leTemps+"}");

}


// lecture luminosité
float lectureLum(){
  // This sketch uses the LTR303's built-in integration timer.
  //int ms = 1000;  
  //delay(ms);
  double lux;    // Resulting lux value
  boolean good;  // True if neither sensor is saturated
  // Once integration is complete, we'll retrieve the data.
  
  // There are two light sensors on the device, one for visible light
  // and one for infrared. Both sensors are needed for lux calculations.
  
  // Retrieve the data from the device:

  unsigned int data0, data1;
  
  if (light.getData(data0,data1)) {
    // getData() returned true, communication was successful
    
    //Serial.print("data0: ");
    //Serial.println(data0);
    //Serial.print("data1: ");
    //Serial.println(data1);
  
    // To calculate lux, pass all your settings and readings
    // to the getLux() function.
    
    // The getLux() function will return 1 if the calculation
    // was successful, or 0 if one or both of the sensors was
    // saturated (too much light). If this happens, you can
    // reduce the integration time and/or gain.
  
   
    
    // Perform lux calculation:

    good = light.getLux(gain,integrationTime,data0,data1,lux);
    
    // Print out the results:
  
    //Serial.print(" lux: ");
    //Serial.println(lux);
    //if (good) Serial.println(" (good)"); 
    //else Serial.println(" (BAD)");
    
  }
  else {
    // getData() returned false because of an I2C error, inform the user.

    byte error = light.getError();
    lux =-1;
 
  }
  return (lux);
}
