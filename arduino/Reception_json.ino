
// fonction ReceptionChaine 

// pour test tapez dans la console :  {"LEDRouge":255} pour régler l'intensité de la LED Rouge (choisir la bonne vitesse de communicaton et nouvelle ligne dans la console) 
// pour modifier l'éclairement des trois LED à la fois {"LEDRouge":127,"LEDVerte":127,"LEDBleue":127}
 
void ReceptionChaine(String chaine){
  // réservation mémoire (512 octets)
  StaticJsonDocument<512> docR; // document au format JSON pour la Réception 
 
  DeserializationError error = deserializeJson(docR, chaine); // lecture de la chaine et transformation au format Json
  //Serial.println("fonction Réception lancée ! "); 
  JsonObject obj = docR.as<JsonObject>();// Création d'ou objet JSON qui permet certaines opérations : comme vérifier si un champ existe dans le document json docRn 
  
  // Test pour savoir si le décodage de la chaine en json est correct
  if (error) {
      
        Serial.print(F("Erreur deserializeJson() : "));
        Serial.println(error.c_str());
     
  }
  
  bool flag = false; // variable booléenne qui sera mise à vrai si au moins une led a été modifiée
  
  if (obj.containsKey("LEDRouge")) { // si le champ LEDRouge existe dans l'objet Json on modifie l'éclairage de la led Rouge
      //valLedR = docR["LEDRouge"];
      //analogWrite(LEDRouge, valLedR);
      flag = true;
  }
  
  if (obj.containsKey("LEDVerte")) {// si le champ LEDVerte existe dans l'objet Json on modifie l'éclairage de la led Verte
      //valLedV = docR["LEDVerte"];
      //analogWrite(LEDVerte,(int)docR["LEDVerte"]);
      flag = true;
  }
  
  if (obj.containsKey("LEDBleue")) {// si le champ LEDBleue existe dans l'objet Json on modifie l'éclairage de la led Bleue
      //valLedB = docR["LEDBleue"];
      //analogWrite(LEDBleue,valLedB);
      flag =true;
  }

  if (obj.containsKey("EtatsLED")) {// si l'état des leds est demandé on met le flag à true et les valeurs seront renvoyées vers le serveur MQTT
     if ((bool)docR["EtatsLED"]){
         flag =true;
     }    
  }
  
  if (flag){  // si flag  == true > on renvoie l'état des leds au format JSON
    String reponse = "{\"LEDRouge\":"; 
    //reponse = reponse + valLedR+",\"LEDVerte\":"+valLedV+",\"LEDBleue\":"+valLedB+"}";
    //Serial.println(reponse);
  }
}// fin fonction RéceptionChaine
