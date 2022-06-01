/* Bibliothèques */
#include <SimpleTimer.h>// Bibliothèque utilisée pour exécuter une fonction à intervalle de temps régulier ( lien pour télécharger la bibliothèque : https://github.com/jfturcot/SimpleTimer )
#include <ArduinoJson.h>// Bibliothèque nécessaire pour lire les données au format Json.

int ledPin = 13;                // choisi le pin pour la LED
int inputPin = 7;               // choisi l'entrée du pin (pour le capteur PIR)
int pirState = LOW;             // on initialise le capteur qu'il y a aucune présence
int val = 0;                    // variable pour lire le statut du pin

///////////////////////// Ultrasonic Sensor ///////////////////////
// définie le branchement des pins
const int trigPin = 9;
const int echoPin = 10;
// defini les variables
long duration;
float distance;
String detection = "initialisation";


String inputString = "";  // variable de type chaine de caratères qui contiendra les caractères de commande reçue sur le port serie

SimpleTimer timer;// objet timer permet d'exécuter une fonction à intervalle de temps régulier > on l'utilisera pour la fonction EnvoiDonnees
int periode = 1000; // periode des mesures en ms


// Initialisation
void setup() {

 ///////////////////////// Motion Sensor ///////////////////////
  pinMode(ledPin, OUTPUT);      // on déclare la sortie de la led
  pinMode(inputPin, INPUT);     // déclare le capteur PIR comme entrée
 
  Serial.begin(9600);
  ///////////////////////// Ultrasonic Sensor ///////////////////////
  pinMode(trigPin, OUTPUT);     // intialise le trigPin comme sortie
  pinMode(echoPin, INPUT);      // intialise l'echoPin comme sortie
  Serial.begin(9600);           // demarre la série de communication


  timer.setInterval(periode, EnvoiDonnees); // définit un timer qui va exécuter la fonction EnvoiDonnees toutes les periodes

}

// Boucle d'exécution
void loop() {
   ///////////////////////// Motion Sensor ///////////////////////
  val = digitalRead(inputPin);                // lit l'entrée de la valeur
  if (val == HIGH) {                          // verifie si l'entrée est HIGH
    digitalWrite(ledPin, HIGH);               // allume les leds
    if (pirState == LOW) {                    
      detection = "on";
      //Serial.println("Motion detected!");
      pirState = HIGH;
    }
  } else {
    digitalWrite(ledPin, LOW);                // eteint les leds
    if (pirState == HIGH){                    // we have just turned of
      detection = "off";
      //Serial.println("Motion ended!");      
      pirState = LOW;
    }
  }
  ///////////////////////// Ultrasonic Sensor ///////////////////////
  // Clears the trigPin
 digitalWrite(trigPin, LOW);
 delayMicroseconds(2);                  // met le trigPin sur l'état HIGH pdt 10s 
 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin, LOW);            // lis l'echoPin, retourne l'onde sonore en microseconde
 duration = pulseIn(echoPin, HIGH);     // calcul la distance
 distance= duration*0.034/2;            // affichela distance dans le moniteur
 //Serial.print("Distance: ");
 //Serial.println(distance);
 delay(500);
 
  timer.run();// exécute en permanence le timer  > lecture des données toutes les périodes
 
}
