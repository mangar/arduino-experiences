

int led = 13;
int infraPin = 7;

// the setup routine runs once when you press reset:
void setup() {                
  Serial.begin(9600);
  pinMode(led, OUTPUT);     
  pinMode(infraPin, INPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  
  Serial.println("lendo....");
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  if (digitalRead(infraPin)) {
    Serial.println("ATIVO");
    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(2000);               // wait for a second
  }
}
