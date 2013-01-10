
int led = 13;
int infraPin = 7;

void setup() {                
  Serial.begin(9600);
  pinMode(led, OUTPUT);     
  pinMode(infraPin, INPUT);
}


void loop() {  
  Serial.println("reading....");
  digitalWrite(led, LOW);
  if (digitalRead(infraPin)) {
    Serial.println("ACTIVE");
    digitalWrite(led, HIGH);
    delay(2000);         
  }
}
