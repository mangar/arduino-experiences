#include <LiquidCrystal.h>
#include <Wire.h>
#include <dht11.h>


#define REDLITE 3
#define GREENLITE 5
#define BLUELITE 6
 
LiquidCrystal lcd(6, 7, 8,  9,  4,  5);
 
dht11 DHT11;
float temperatura = 0;
float umidade = 0;

/**
 * Start the serial communication and LCD
 */
void setup() {
  Serial.begin(9600);
   
  // set up the LCD's number of rows and columns: 
  lcd.begin(16, 2);
  
  pinMode(REDLITE, OUTPUT);
  pinMode(GREENLITE, OUTPUT);
  pinMode(BLUELITE, OUTPUT);  
}


/**
 * Read temperature and humidity from the sensor DHT11
 */
void getdata(int iPuerto) {
  int chk = DHT11.read(iPuerto);

  Serial.print("Sensor "); Serial.print(iPuerto); Serial.print(" ");
  switch (chk) {
    case 0:   
    
      umidade = (float)DHT11.humidity;
      Serial.print(umidade, 1);
      Serial.print(" % ");
      
      temperatura = (float)DHT11.temperature;
      Serial.print(temperatura, 2);
      Serial.println(" o C");
      
      break;
    case -1: Serial.println(" Checksum error"); break;
    case -2: Serial.println(" Time out error"); break;
    default: Serial.println(" Unknown error"); break;
  }
}

/**
 * Display temp and hum
 */
void displayTemperature() {
  getdata(2);  
  // set up the LCD's number of rows and columns: 
//  lcd.begin(16, 2);

  lcd.setCursor(0,0);
  lcd.print("Temp.:");
  lcd.print(temperatura, 1);
  lcd.print("o C"); 
  
  lcd.setCursor(0,1);
  lcd.print("Umidade:");
  lcd.print(umidade, 1);  
  lcd.print("%");  
}



void loop() {  
  displayTemperature();
  delay(2000);
}
