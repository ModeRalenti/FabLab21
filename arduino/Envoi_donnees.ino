// données envoyées au format JSON (pour MQTT) sur le port série

void EnvoiDonnees() {// fonction qui envoie les valeurs de l'éclairement et du temps  {"E_Lux":E_Lux,"temps":leTemps})
  
  // mesure du temps en secondes
  unsigned long CurrentTime = millis(); //(long > 32 bits, int > 16 bits, byte > 8bits ,float > 32 bits)
  float leTemps = CurrentTime/1000;
  
  // On lit la valeur sur l'entrée analogique A0
  //val_A0 = analogRead(LDR);
  
  //calcul de la valeur de la résistance de la LDR : R_LDR (relation du pont diviseur)
  //R_LDR =(1023.0/val_A0-1)*R;  // le 1023.0 avec virgule zéro est important car il signifie que le résultat pour R_LDR sera un réel (float) 
  
  //calcul Eclairement en Lux
  //E_Lux = (pow(R_LDR,(1/A)))/(pow(10,(B/A))); // d'après la relation : log(R_LDR) = A*Log(E_Lux)+B  => E_Lux = (R_LDR)^(1/A) / 10^(B/A)
  
  // envoi des données au format JSON
  String chaine = "{\"distance\":";   // il faut toujours initialiser la chaine avant de concaténer à la ligne suivante
  Serial.println(chaine + distance + ",\"detection\":\""+detection+"\",\"temps\":"+leTemps+"}");
  
}
