/*
  Web client
  
  Verifica se  servidor envia uma resposta positiva [ok] ou negtiva [nok]
  Sinaliza com o led cad auma das respostas:
  [ok] led verde
  [nok] led amarelo
 */

#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = {  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
//IPAddress server(173,194,33,104); // Google
IPAddress server(192,168,0,130); //my machine...

int ledOK = 6;
int ledNOK = 7;

String currentLine = ""; 

// Initialize the Ethernet client library
// with the IP address and port of the server 
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;



void blinkNOK() {
  for (int i = 0; i < 1; i++) {
    digitalWrite(ledNOK, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(100);               // wait for a second  
    digitalWrite(ledNOK, LOW);    // turn the LED off by making the voltage LOW  
    delay(100);               // wait for a second  
  }
}


void blinkOK() {
  for (int i = 0; i < 20; i++) {
    digitalWrite(ledOK, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(50);               // wait for a second  
    digitalWrite(ledOK, LOW);    // turn the LED off by making the voltage LOW  
    delay(50);               // wait for a second  
  }
}


void blinkERROR() {
  for (int i = 0; i < 20; i++) {
    digitalWrite(ledOK, HIGH); digitalWrite(ledNOK, HIGH);
    delay(50);               // wait for a second  
    digitalWrite(ledOK, LOW); digitalWrite(ledNOK, LOW);
    delay(50);               // wait for a second  
  }
}



void setup() {
  pinMode(ledOK, OUTPUT);     
  pinMode(ledNOK, OUTPUT);       
  
  currentLine.reserve(256);
  
  
  // start the serial library:
  Serial.begin(9600);
  
  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    for(;;)
      ;
  }
  
  // give the Ethernet shield a second to initialize:
  delay(1000);
  Serial.println("connecting...");

  // if you get a connection, report back via serial:
  if (client.connect(server, 3000)) {
    
    Serial.println("connected");
    // Make a HTTP request:
//    client.println("GET / HTTP/1.0");
    client.println("GET /arduino/ HTTP/1.0");
    
    client.println();
    
  } 
  else {
    // kf you didn't get a connection to the server:
    blinkERROR();
    Serial.println("connection failed");
  }
}






/*
 *
 */
void loop() {
  
  
  // if there are incoming bytes available 
  // from the server, read them and print them:
  if (client.available()) {
    char c = client.read();
    currentLine += c;    
    Serial.print(c);
  }

  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    
    Serial.println("\n\n");
    Serial.println("------------------------------");
    Serial.println(currentLine);
    
    Serial.println("\n\n");    
    int indexOfNOK = currentLine.indexOf("nok");
    String out = ">>"; out += indexOfNOK; out += "<<";
    Serial.println(out);
    Serial.println("------------------------------");

    
    if (indexOfNOK > 0) {
      blinkNOK();    
    } else {
      blinkOK();    
    }
    
    currentLine = "";
    
    delay(1000);
    Serial.println();
    Serial.println("reconecting...");
    client.stop();
    delay(1000);
    
    if (client.connect(server, 3000)) {      
      Serial.println("connected");
      client.println("GET /arduino/ HTTP/1.0");
      client.println();
    } 
    else {
      blinkERROR();
      Serial.println("connection failed");
    }        
  }

}

