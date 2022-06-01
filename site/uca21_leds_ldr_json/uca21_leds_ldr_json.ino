/* Bibliothèques */
#include <FastLED.h>

#define LED_PIN     4
#define NUM_LEDS    21
#define BRIGHTNESS  64
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#include <LTR303.h>
#include <Wire.h>

// Create an LTR303 object, here called "light":

LTR303 light;

// Global variables pour capteur luminositéLDR
unsigned char gain;     // Gain setting, values = 0-7 
unsigned char integrationTime;  // Integration ("shutter") time in milliseconds
unsigned char measurementRate;  // Interval between DATA_REGISTERS update

#include <SimpleTimer.h>// Bibliothèque utilisée pour exécuter une fonction à intervalle de temps régulier ( lien pour télécharger la bibliothèque : https://github.com/jfturcot/SimpleTimer )
#include <ArduinoJson.h>// Bibliothèque nécessaire pour lire les données au format Json.

// UCA21 D (pwm) = 2,3,5,6,7,8,9,10
// UCA21 analog input A0,A1,A2,A3
// brochage : https://github.com/FabienFerrero/UCA21 


byte valLedR = 0;// valeurs des intensités des led
byte valLedV = 0;
byte valLedB = 0;

String inputString = "";  // variable de type chaine de caratères qui contiendra les caractères de commande reçue sur le port serie

SimpleTimer timer;// objet timer permet d'exécuter une fonction à intervalle de temps régulier > on l'utilisera pour la fonction EnvoiDonnees
int periode = 2000; // periode des mesures en ms

float E_Lux = -1; // eclairement

// Initialisation
void setup() {

  // initialise la communication avec le port série à la vitesse de 9600 bits par seconde
  Serial.begin(9600);

   // configuration de la chaine de 21 leds
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );
  // éteint toutes les leds
  fill_solid( leds, NUM_LEDS, CRGB::Black);
  FastLED.show();

  setuplr303();// initialise le capteur de luminosité
  delay(1000);
  E_Lux = lectureLum();// car la première lecture renvoie 0 !
  timer.setInterval(periode, EnvoiDonnees); // définit un timer qui va exécuter la fonction EnvoiDonnees toutes les periodes

}

// Boucle d'exécution
void loop() {
  timer.run();// exécute en permanence le timer  > lecture des données toutes les périodes
 
}

// fonction qui allume toutes les leds avec la couleur RVB
void couleurRGB(int redValue, int greenValue, int blueValue) {

  fill_solid( leds, NUM_LEDS, CRGB( (int) redValue*0.9,(int) greenValue*.9, (int) blueValue*0.9));
  FastLED.show();
}

// initialisation cateur lumière
void setuplr303(){
// Initialize the LTR303 library
  // 100ms  initial startup time required
  delay(100);

  // You can pass nothing to light.begin() for the default I2C address (0x29)
  light.begin();

  // Get factory ID from sensor:
  // (Just for fun, you don't need to do this to operate the sensor)

  unsigned char ID;
  
  if (light.getPartID(ID)) {
    Serial.print("Got Sensor Part ID: 0X");
    Serial.print(ID,HEX);
  }
  // Most library commands will return true if communications was successful,
  // and false if there was a problem. You can ignore this returned value,
  // or check whether a command worked correctly and retrieve an error code:
  else {
    byte error = light.getError();
    Serial.println(error);
  }

  // The light sensor has a default integration time of 100ms,
  // and a default gain of low (1X).
  
  // If you would like to change either of these, you can
  // do so using the setControl() and setMeasurementRate() command.
  
  // Gain can take any value from 0-7, except 4 & 5
  // If gain = 0, device is set to 1X gain (default)
  // If gain = 1, device is set to 2X gain
  // If gain = 2, device is set to 4X gain
  // If gain = 3, device is set to 8X gain
  // If gain = 4, invalid
  // If gain = 5, invalid
  // If gain = 6, device is set to 48X gain
  // If gain = 7, device is set to 96X gain
  gain = 0;
  Serial.println("Setting Gain...");
  light.setControl(gain, false, false);

  // If integrationTime = 0, integrationTime will be 100ms (default)
  // If integrationTime = 1, integrationTime will be 50ms
  // If integrationTime = 2, integrationTime will be 200ms
  // If integrationTime = 3, integrationTime will be 400ms
  // If integrationTime = 4, integrationTime will be 150ms
  // If integrationTime = 5, integrationTime will be 250ms
  // If integrationTime = 6, integrationTime will be 300ms
  // If integrationTime = 7, integrationTime will be 350ms

  unsigned char time = 1;

  // If integrationTime = 0, integrationTime will be 100ms (default)
  // If integrationTime = 1, integrationTime will be 50ms
  // If integrationTime = 2, integrationTime will be 200ms
  // If integrationTime = 3, integrationTime will be 400ms
  // If integrationTime = 4, integrationTime will be 150ms
  // If integrationTime = 5, integrationTime will be 250ms
  // If integrationTime = 6, integrationTime will be 300ms
  // If integrationTime = 7, integrationTime will be 350ms
  
  Serial.println("Set timing...");
  light.setMeasurementRate(time,3);

  // To start taking measurements, power up the sensor:
  
  Serial.println("Powerup...");
  light.setPowerUp();
  
  // The sensor will now gather light during the integration time.
  // After the specified time, you can retrieve the result from the sensor.
  // Once a measurement occurs, another integration period will start.
  

}
