#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <SPI.h>
#include <LiquidCrystal.h>

// define pour la sonde 
// Data wires are connected to the Arduino digital pins 4 and 3
#define ONE_WIRE_BUS 6
#define ONE_WIRE_BUS2 7
// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);
OneWire oneWire2(ONE_WIRE_BUS2);
// Pass our oneWire reference to Dallas Temperature sensor 
Adafruit_SSD1306 srituhobby = Adafruit_SSD1306(128, 64, &Wire);

DallasTemperature sensors(&oneWire);
DallasTemperature sensors2(&oneWire2);
const int RELAY_PIN = 9;  // the Arduino pin, which connects to the IN pin of relay
const int RELAY_PIN2 = 5;  // the Arduino pin, which connects to the IN pin of relay
// ECRAN LCD 
//const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
//LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
//LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const int AirValue = 600;   //you need to replace this value with Value_1
const int WaterValue = 210;  //you need to replace this value with Value_2
const int humid1 = A0;
const int humid2= A1;
int soilMoistureValue1 ;
int soilMoistureValue2 ;
int soilmoisturepercent1;
int soilmoisturepercent2;
int pompePIN= 4 ;// pin du relay pour controler la pompe
// plaque chauffante 
int pin_bouton=0;
int pin_bouton2=1;
//int RELAY_PIN = 5;  // the Arduino pin, which connects to the IN pin of relay
bool etat = true ;
bool etat2=true; 
int sX = 0;
int sY = 60;
int x = 0;
