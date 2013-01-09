int ledPin = 13; // choose the pin for the LED

int sub_a_in = 7;     // entrada SUB time A
int sub_a_val = 0;  // leitura do 'pressbutton' de SUB para o time A
int sub_a_stsAnterior = LOW; // status anterior SUB A

int add_a_in = 8;     // entrada ADD time A
int add_a_val = 0;  // leitura do 'pressbutton' de ADD para o time A
int add_a_stsAnterior = LOW; // status anterior ADD A

int countA = 0;     // pontuacao time A





void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);  
  pinMode(add_a_in, INPUT);    
  pinMode(sub_a_in, INPUT);      
}



void addA(int statusAgora) {
  if ((add_a_stsAnterior == HIGH) && (statusAgora == LOW)) {
    if (countA < 12) {
      countA++;
    }
  }
  add_a_stsAnterior = statusAgora;
}


void subA(int statusAgora) {
  if ((sub_a_stsAnterior == HIGH) && (statusAgora == LOW)) {
    if (countA > 0) {
      countA--;
    }
  }
  sub_a_stsAnterior = statusAgora;
}


void loop(){
  
  
  add_a_val = digitalRead(add_a_in);  // read input value
  if (add_a_val == HIGH) {         // check if the input is HIGH (button released)
    digitalWrite(ledPin, LOW);  // turn LED OFF
    addA(HIGH);    
  } else {
    digitalWrite(ledPin, HIGH);  // turn LED ON
    addA(LOW);
  }
  
  
  sub_a_val = digitalRead(sub_a_in);  // read input value
  if (sub_a_val == HIGH) {         // check if the input is HIGH (button released)
    digitalWrite(ledPin, LOW);  // turn LED OFF
    subA(HIGH);    
  } else {
    digitalWrite(ledPin, HIGH);  // turn LED ON
    subA(LOW);
  }  
  
  
  Serial.print("H/L: ");Serial.print(add_a_val);
  Serial.print(" count: "); Serial.print(countA); Serial.print("\n");
}






