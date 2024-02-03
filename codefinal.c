#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// define pour la sonde 
 
// Data wires are connected to the Arduino digital pins 4 and 3
#define ONE_WIRE_BUS 4
#define ONE_WIRE_BUS2 3


// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);
OneWire oneWire2(ONE_WIRE_BUS2);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);
DallasTemperature sensors2(&oneWire2);

const int nombrePointsGraphique = 50; // Nombre de points dans le graphique
int valeursCapteur[nombrePointsGraphique];
int valeursCapteur2[nombrePointsGraphique];
int indexGraphique = 0;
int valeurMin = 0;  // Valeur minimale possible
int valeurMax = 100; // Valeur maximale possible
const int RELAY_PIN = 5;  // the Arduino pin, which connects to the IN pin of relay
const int AirValue = 600;   //you need to replace this value with Value_1
const int WaterValue = 210;  //you need to replace this value with Value_2
const int humid1 = A0;
const int humid2= A1;
int soilMoistureValue1 ;
int soilMoistureValue2 ;
int soilmoisturepercent1;
int soilmoisturepercent2;
#define pompePIN 7 // pin du relay pour controler la pompe
#define pompePIN2 8 // pin du relay pour controler la pompe

// plaque chauffante 
int pin_bouton=10;
//int RELAY_PIN = 5;  // the Arduino pin, which connects to the IN pin of relay
bool etat = true ; 
void setup() {
  pinMode(pompePIN, OUTPUT);
  pinMode(pin_bouton, INPUT_PULLUP);

  pinMode(RELAY_PIN, OUTPUT);

  Serial.begin(9600); // open serial port, set the baud rate to 9600 bps
  // Start up the library
  sensors.begin();
  sensors2.begin();


}


void loop() {

   if(!digitalRead(pin_bouton)){
    if(etat)
    etat=false;
    else 
    etat=true;
  }
  digitalWrite(RELAY_PIN, etat);
  //digitalWrite(RELAY_PIN, LOW); // turn on heating element 5 seconds
  //Serial.print(millis()); // Envoie le temps écoulé depuis le démarrage du programme

soilMoistureValue1 = analogRead(A0);
soilMoistureValue2 = analogRead(A1);

soilmoisturepercent1 = map(soilMoistureValue1, AirValue, WaterValue, 0, 100);
  //put Sensor insert into soil
soilmoisturepercent2 = map(soilMoistureValue2, AirValue, WaterValue, 0, 100);

Serial.print("capteur humid 1 nord:");

Serial.println(soilMoistureValue1);
Serial.print("capteur humid 2 sud:");

Serial.println(soilMoistureValue2);
if(soilmoisturepercent1 >= 100)
{
  Serial.println("100 %");
}
else if(soilmoisturepercent1 <=0)
{
  Serial.println("0 %");
}
else if(soilmoisturepercent1 >0 && soilmoisturepercent1 < 100)
{
  Serial.print("humidite au nord  :");
Serial.print(soilmoisturepercent1);
 Serial.println("%");
  if(soilmoisturepercent1<50){
    digitalWrite(pompePIN,HIGH);
    Serial.println("il faut irriguer au NORD!");
  }
  else {
    digitalWrite(pompePIN,LOW);
    Serial.println("le sol est humide au nord !");
}
}
if(soilmoisturepercent2 >= 100)
{
  Serial.println("100 %");
}
else if(soilmoisturepercent2 <=0)
{
  Serial.println("0 %");
}
else if(soilmoisturepercent2 >0 && soilmoisturepercent2 < 100)
{
  Serial.print("humidite au sud  :");
Serial.print(soilmoisturepercent2);
 Serial.println("%");
  if(soilmoisturepercent2<50){
    digitalWrite(pompePIN2,LOW);
    Serial.println("il faut irriguer au SUD!");
  }
  else {
    digitalWrite(pompePIN2,HIGH);
    Serial.println("le sol est humide au Sud !");
}
}
 delay(500);
// loop pour la sonde temperture 
// Call sensors.requestTemperatures() to issue a global temperature and Requests to all devices on the bus
  sensors.requestTemperatures(); 

  Serial.print("temperature au nord : ");
  // Why "byIndex"? You can have more than one IC on the same bus. 0 refers to the first IC on the wire
  Serial.println(sensors.getTempCByIndex(0)); 
 // Serial.print(" - Fahrenheit temperature: ");
 // Serial.println(sensors.getTempFByIndex(0));
  //delay(1000);
  // Ajoute un autre onglet avant le delay
  //Serial.print("\t");
 

  // Calculer l'échelle du graphique


  delay(500);
  sensors2.requestTemperatures(); 

  Serial.print("temperature au sud ");
  // Why "byIndex"? You can have more than one IC on the same bus. 0 refers to the first IC on the wire
  Serial.println(sensors2.getTempCByIndex(0)); 
  delay(500);
  //delay(250);
}

