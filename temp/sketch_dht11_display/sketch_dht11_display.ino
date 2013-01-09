#include <LiquidCrystal.h>
#include <Wire.h>
#include <dht11.h>


#define REDLITE 3
#define GREENLITE 5
#define BLUELITE 6
 
//LiquidCrystal lcd(6, 7, 8,  9,  4,  5);
LiquidCrystal lcd(42, 43, 44, 45,  40, 41);

 
dht11 DHT11;
float temperatura = 0;
float umidade = 0;


//FADE
int FADE_LED = 9;           // the pin that the LED is attached to
int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by


/**
 * Start the serial communication and LCD
 */
void setup() {
  Serial.begin(9600);
   
  // FADE
  pinMode(FADE_LED, OUTPUT);
   
  // set up the LCD's number of rows and columns: 
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("Starting....");   
  delay(1200);

  
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


boolean hasToDisplayTemperature() {
  boolean has = false;
  if (brightness == 0 || brightness == 255) {
    has = true;
  }
  return has;
}

/**
 * Display temp and hum
 */
void displayTemperature() {
  
  if (hasToDisplayTemperature()) {
    getdata(49);  
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
}



void fadeLED() {
  analogWrite(FADE_LED, brightness);    

  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade: 
  if (brightness == 0 || brightness == 255) {
    fadeAmount = -fadeAmount ; 
  }     
  Serial.print("FADE ... ");
  Serial.print("brightness: "); Serial.print(brightness);
  Serial.print(" fadeAmount: "); Serial.print(fadeAmount);
  Serial.println("");
  
  // wait for 30 milliseconds to see the dimming effect    
  if (brightness > 0) {
    delay(30);
  } else {
    digitalWrite(FADE_LED, LOW);
    delay(1000);
  }

}


void loop() {  
  displayTemperature();
  fadeLED();
//  delay(2000);
}
