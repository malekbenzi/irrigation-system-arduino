#include < PFE.h> 
void setup() {
  Serial.begin(9600); 
  pinMode(pompePIN, OUTPUT);
  pinMode(pin_bouton, INPUT_PULLUP);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(pin_bouton2, INPUT_PULLUP);
  pinMode(RELAY_PIN2, OUTPUT);
  sensors.begin();
  sensors2.begin();
  srituhobby.begin(SSD1306_SWITCHCAPVCC, 0x3C);// Address 0x3C for 128x32
  srituhobby.clearDisplay();
   delay(1000);
}


void loop() {
   if(!digitalRead(pin_bouton)){
    if(etat)
    etat=false;
    else 
    etat=true;
  }
  digitalWrite(RELAY_PIN, etat);
  digitalWrite(RELAY_PIN2, etat);
 
soilMoistureValue1 = analogRead(A0);
soilMoistureValue2 = analogRead(A1);

soilmoisturepercent1 = map(soilMoistureValue1, AirValue, WaterValue, 0, 100);
  //put Sensor insert into soil
soilmoisturepercent2 = map(soilMoistureValue2, AirValue, WaterValue, 0, 100);
int valeur = (soilmoisturepercent1 + soilmoisturepercent2 ) /2 ;
   int y = 90 - valeur ;
   //int y2 = 90 - soilmoisturepercent2;
 if (x > 128) {
    x = 0;
    sX = 0;
    srituhobby.clearDisplay();
  } 
  srituhobby.writeLine(sX, sY, x, y,WHITE);
  sX = x;
  sY = y;
  x++;
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


  if(soilmoisturepercent1<70){
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
 Serial.println("%");}

  if(soilmoisturepercent2<70){
   digitalWrite(pompePIN,HIGH);
    Serial.println("il faut irriguer au SUD!");
  }
  else {
    digitalWrite(pompePIN,LOW);
    Serial.println("le sol est humide au Sud !");
}

sensors.requestTemperatures(); 

  Serial.print("temperature au nord : ");
  
  Serial.println(sensors.getTempCByIndex(0)); 

  sensors2.requestTemperatures(); 

  Serial.print("temperature au sud ");
  Serial.println(sensors2.getTempCByIndex(0)); 

  srituhobby.setCursor(0, 0);
  srituhobby.setTextSize(1);
  srituhobby.setTextColor(SSD1306_WHITE);
  srituhobby.print("Evolution humidite moyenne");
 delay(1000);
}
