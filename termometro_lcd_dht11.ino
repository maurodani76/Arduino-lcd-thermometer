#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SimpleDHT.h>

// lcd library:
// https://bitbucket.org/fmalpartida/new-liquidcrystal 
// wiring pin lcd:
// GND, VCC, SCL=A5, SDA=A4 (analogic pins)
// wiring pin DHT11:
// GND, VCC, DATA=D2 (digital pins)

#define I2C_ADDR 0x3F
#define BACKLIGHT_PIN 3
#define En_pin 2
#define Rw_pin 1
#define Rs_pin 0
#define D4_pin 4
#define D5_pin 5
#define D6_pin 6
#define D7_pin 7

#define DHTPIN 2 // define digital pin for DHT11 signal
SimpleDHT11 dht11;

LiquidCrystal_I2C lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

void setup() {
  lcd.begin(16,2);
  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  lcd.setBacklight(HIGH);

  byte deg[8] = {  // define "°" character
  0b01100,
  0b10010,
  0b10010,
  0b01100,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};

  lcd.createChar(1, deg);
  
  lcd.home ();
  lcd.print("Waiting for");
  lcd.setCursor(0,1);
  lcd.print("DHT11 sensor");
  delay(4000); // waiting time for DHT11 startup
  lcd.clear();
}

void loop() {  

  byte temp = 0;
  byte umid = 0;
  int err = SimpleDHTErrSuccess;  //checking DHT11 sensor
  if ((err = dht11.read(DHTPIN, &temp, &umid, NULL)) != SimpleDHTErrSuccess) {   // checking DHT11 sensor
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Read DHT11 failed, err="); 
    lcd.setCursor(0,1);
    lcd.print(err);
    delay(1000);
    return;
  }

// code below is for printing results in °C and % humidity
  
  lcd.setCursor(0,0);
  lcd.print((int)temp); lcd.setCursor(3,0); lcd.write(1); lcd.setCursor(4,0); lcd.print("C"); 
  lcd.setCursor(0,1);
  lcd.print((int)umid); lcd.setCursor(2,1); lcd.print("% Humidity");
  
  // DHT11 sampling rate is 1HZ.
  delay(4000); // waiting time before new measurement; according to 1HZ sampling do not drop below 1000ms delay
  
}
