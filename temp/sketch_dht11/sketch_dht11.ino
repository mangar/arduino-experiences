#include <dht11.h>

dht11 DHT11;

void setup() {
  Serial.begin(9600);
}

void getdata(int iPuerto)
{
  int chk = DHT11.read(iPuerto);

  Serial.print("Sensor "); Serial.print(iPuerto); Serial.print(" ");
  switch (chk)
  {
    case 0:   
      Serial.print((float)DHT11.humidity, 2);
      Serial.print(" % ");
      Serial.print((float)DHT11.temperature, 2);
      Serial.println(" o C");
        break;
    case -1: Serial.println(" Checksum error"); break;
    case -2: Serial.println(" Time out error"); break;
    default: Serial.println(" Unknown error"); break;
  }

  
}

void loop() {  
  getdata(2);
  delay(2000);
}
