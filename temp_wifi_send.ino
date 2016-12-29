//Brun -> 3
//Lila -> 2
//Röd & Gul -> VCC3.3
//Svart -> GND



#include <SoftwareSerial.h>
#include <dht11.h>  //Import needed libraries

static int tempPin = 6;
static int ledPin = 13;

int motionValue = 0;
SoftwareSerial mySerial(3,2); //rx, tx

dht11 DHT11;

#define DHT11PIN 6  //Declare Pin Numbers

void setup() {
  //pinMode(tempPin, INPUT);
  pinMode(ledPin, OUTPUT);
  
  // setup serial
  delay(5000);
  Serial.begin(9600);
  mySerial.begin(9600);
  delay(1000);

  //Setup IP connection to receiving computer
  mySerial.print("AT+CIPSTART=\"UDP\",\"192.168.0.255\",8000");
  mySerial.write(13);    // CR
  mySerial.write(10);    // LF
  mySerial.flush();
  delay(3000);
  print_ip_address();
  delay(5000);
}

void loop() {
  check_sensor();
  float temp = DHT11.temperature;
  float humi = DHT11.humidity;
  
 if(true){
    digitalWrite(ledPin, HIGH);
    mySerial.print("AT+CIPSEND=4");
    mySerial.write(13);    // CR
    mySerial.write(10);    // LF
    delay(500);
    mySerial.print((float)DHT11.temperature, 2);
    mySerial.write(13);    // CR
    mySerial.write(10);    // LF
    delay(5000);
  }else{
    digitalWrite(ledPin, LOW);
  }
}

void read_serial(){
    while(mySerial.available()){
    Serial.write(mySerial.read());
  }
}

void check_sensor(){
    int chk = DHT11.read(tempPin);

  Serial.print("Read sensor: ");
  switch (chk)
  {
    case 0: Serial.println("OK"); break;
    case -1: Serial.println("Checksum error"); break;
    case -2: Serial.println("Time out error"); break;
    default: Serial.println("Unknown error"); break;
  }
}

void print_ip_address(){
  mySerial.flush();
  mySerial.print("AT+CIPSR");
  mySerial.write(13);    // CR
  mySerial.write(10);    // LF
  delay(1000);
  read_serial();
}

