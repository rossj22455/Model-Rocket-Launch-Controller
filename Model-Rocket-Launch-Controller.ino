//MADE BY JACK ROSS
//NOT FOR PUBLIC USE
//MADE FOR ROCKET LAUNCH SYSTEM


int Version = 1.00;


#include <Arduino_APDS9960.h>
#include <LiquidCrystal_I2C.h>
#include <ezButton.h>
#include "DHT.h"
//Constants
#define LaunchButto 1
#define SafteyButto 2
#define ButtonLef 3
#define ButtonRigh 4
int Buzzer = 5;
#define DHTPIN 6
int LEDGREEN = 7;
int LEDRED = 8;
int RelaySaftey = 9;
int RelayLaunch = 10;

//Tempture Sensor 
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
//LCD screen Settings
const int  en = 2, rw = 1, rs = 0, d4 = 4, d5 = 5, d6 = 6, d7 = 7, bl = 3;
const int i2c_addr = 0x27;
LiquidCrystal_I2C lcd(i2c_addr, en, rw, rs, d4, d5, d6, d7, bl, POSITIVE);
//Button
ezButton LaunchButton(LaunchButto);
ezButton SafteyButton(SafteyButto);
ezButton ButtonLeft(ButtonLef);
ezButton ButtonRight(ButtonRigh);
//Boolean
boolean Saftey = false; 
boolean Launch = false;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(RelaySaftey, OUTPUT);
  pinMode(RelayLaunch, OUTPUT);
  pinMode(LEDRED, OUTPUT);
  pinMode(LEDGREEN, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  dht.begin();
  lcd.begin(16,2);
  delay(10);
  digitalWrite(LEDRED, HIGH);
  digitalWrite(LEDGREEN, LOW);
  digitalWrite(RelaySaftey, LOW);
  digitalWrite(RelayLaunch, LOW);
  if (!APDS.begin()) {
    Serial.println("Error initializing APDS-9960 sensor.");
  }
  delay(4);	
  lcd.setCursor(0,0);
  lcd.print("Booting");
  delay(1000);	
  lcd.clear();
  lcd.print("Booting.");
  delay(1000);	
  lcd.clear();
  lcd.print("Booting..");
  delay(1000);	
  lcd.clear();
  lcd.print("Booting...");
  delay(1000);	
  lcd.clear();
  lcd.print("Booting....");
  delay(1000);	
  lcd.clear();
  lcd.print("Booting.....");
  delay(1000);	
  lcd.clear();
  lcd.print("Booting......");
  delay(1000);	
  lcd.clear();
  lcd.print("Done!");
  digitalWrite(Buzzer, HIGH);
  delay(10);
  digitalWrite(Buzzer, LOW);
  delay(1000);
  lcd.clear();
}

void loop() {
  LaunchButton.loop();
  SafteyButton.loop();
  ButtonLeft.loop();
  ButtonRight.loop();

//Tempeture Module 

  float humidty = dht.readHumidity();
  float tempF = dht.readTemperature(true);

//Saftey Button 

  if(SafteyButton.isPressed()) {
    digitalWrite(Buzzer, HIGH);
    lcd.setCursor(0,0);
    lcd.clear();
    digitalWrite(LEDRED, LOW);
    digitalWrite(LEDGREEN, HIGH);
    lcd.print("ENABLED SAFTEY");
    delay(10);
    Saftey = true;
    digitalWrite(RelaySaftey, HIGH);
    delay(1000);
    lcd.clear();
    digitalWrite(Buzzer, LOW);
  } 

//LAUNCH BUTTON

  if(LaunchButton.isPressed() && SafteyButton.isReleased() && Saftey == false) {
    digitalWrite(RelaySaftey, LOW);
    digitalWrite(RelayLaunch, LOW);
    digitalWrite(LEDRED, HIGH);
    digitalWrite(Buzzer, HIGH);
    lcd.setCursor(0,0);
    lcd.clear();
    lcd.print("Saftey not");
    delay(100);
    digitalWrite(LEDRED, LOW);
    delay(100);
    lcd.setCursor(0,1);
    lcd.print("Enabled");
    digitalWrite(LEDRED, HIGH);
    delay(100);
    digitalWrite(LEDRED, LOW);
    delay(100);
    digitalWrite(LEDRED, HIGH);
    delay(1000);
    digitalWrite(Buzzer, LOW);
    lcd.clear();
  } else if(LaunchButton.isPressed() && SafteyButton.isPressed() && Saftey == true) {
    digitalWrite(Buzzer, HIGH);
    lcd.setCursor(0,0);
    lcd.clear();
    lcd.print("LAUNCHING");
    digitalWrite(RelayLaunch, HIGH);
    delay(5000);
    digitalWrite(Buzzer, LOW);
    digitalWrite(LEDRED, HIGH);
    digitalWrite(LEDGREEN, LOW);
    digitalWrite(RelayLaunch, LOW);
    digitalWrite(RelaySaftey, LOW);
    lcd.clear();
  }

  //MENU 
  
  if (ButtonLeft.isReleased() && ButtonRight.isReleased()) {
    lcd.setCursor(0,0);
    lcd.print("Humidty: ");
    lcd.print(humidty);
    lcd.setCursor(0,1);
    lcd.print("Tempeture: ");
    lcd.print(tempF);
  } else if(ButtonLeft.isPressed()) {
    digitalWrite(Buzzer, HIGH);
    delay(50);
    digitalWrite(Buzzer, LOW);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Saftey: ");
    lcd.print(Saftey);
  } else if(ButtonRight.isPressed()) {
    digitalWrite(Buzzer, HIGH);
    delay(50);
    digitalWrite(Buzzer, LOW);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Made By Jack Ross");
    lcd.setCursor(0,1);
    lcd.print("Version: ");
    lcd.print(Version);
  }


}
