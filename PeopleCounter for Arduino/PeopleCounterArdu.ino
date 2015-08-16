 /*
  Web client

 This sketch connects to a website http://herokuapp.com
 to make a HTTP request using an Arduino Wiznet Ethernet shield.

 Circuit:
 * Ethernet shield attached to pins A0,A2

 created 14/08/2015
 by Oliver Alderete

 */

#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
//IPAddress server(74,125,232,128);  // numeric IP for Google (no DNS)
char server[] = "herokuapp.com";    // name address for Google (using DNS)

// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(192, 168, 0, 5);

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;

const int sensorPinEnter = A0; //Select de input pin for the enter sensor
const int sensorPinLeave = A2; //Select de imput pin for the leave sensor

const int LeaveEnable = 800; // <<<<<<< Adjust the Sensor
const int EnterEnable = 980; // <<<<<<< Adjust the Sensor

int sensorValueEnter = 0;        // value read from the pot
int sensorValueLeave = 0;

int passing = 0;     //store the sensor State

void espera(){
      Serial.print("Espere");
      delay(50);
      Serial.print(".");
      delay(50);
      Serial.print(".");
      delay(50);
      Serial.print(".");
      delay(100);
}
void visit(){
  client.connect(server, 80);
  Serial.println("Entrando\n");
  // Make a HTTP request:
  client.println("GET http://flextronicschallenge.herokuapp.com/counts/door/1.json?enter=1 HTTP/1.0");
  client.println("Connection: close");
  client.println();
  client.stop();
  }
  else {
    // kf you didn't get a connection to the server:
    Serial.println("connection failed");
  }
}

void unvisit(){
  client.connect(server, 80);
  Serial.println("Saliendo\n");
  // Make a HTTP request: DOOR ID = 1
  client.println("GET http://flextronicschallenge.herokuapp.com/counts/door/1.json?leave=1 HTTP/1.0");
  // to change the door that will be updated please change de above number  |
  client.println("Connection: close");
  client.println();
  client.stop();
  }
  else {
    // kf you didn't get a connection to the server:
    Serial.println("connection failed");
  }
}

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  pinMode(sensorPinEnter, INPUT);
  pinMode(sensorPinLeave, INPUT);

  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip);
  }
  // give the Ethernet shield a second to initialize:
  delay(1000);
  Serial.println("connecting...");
}

void loop(){
  if (!client.connected()) {
    sensorValueEnter = analogRead(sensorPinEnter);
    sensorValueLeave = analogRead(sensorPinLeave);
//    Serial.print("sensor = " );
//    Serial.print(sensorValueEnter);
//    Serial.print("\t 2: = ");
//    Serial.println(sensorValueLeave);

    if ( sensorValueLeave > LeaveEnable && passing == 0){
      passing = 1;
      //Serial.print(sensorValueLeave);
      Serial.println("Saliendo!");
      unvisit();
    }    

    if ( sensorValueEnter > EnterEnable && passing == 0){
      passing = 1;
      //Serial.print(sensorValueEnter);
      Serial.println("Entrando!");
      visit();
    }
    if (sensorValueEnter < EnterEnable && sensorValueLeave < LeaveEnable && passing == 1){
      espera();
      passing = 0;  
      Serial.println("Adelante!");
    }
  }
}