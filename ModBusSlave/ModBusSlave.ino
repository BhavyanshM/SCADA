#include <ESP8266WiFi.h>
#include <ModbusTCPSlave.h>
#include <Ticker.h>

#define MBDebug 

Ticker Stop;
ModbusTCPSlave Mb;

#define TRIG_PIN D1
#define ECHO_PIN D2

// Network Addresses
byte ip[] = {192, 168, 0, 40};
byte gateway[] = {192, 168, 0, 1};
byte subnet[] = {255, 255, 255, 0};

long duration;
int distance;

void monitoring(){
  Mb.MBHoldingRegister[0] = 234; 
  Mb.MBHoldingRegister[1] = distance; 
  Mb.MBHoldingRegister[3] = random(1000);

//  Serial.println(Mb.MBHoldingRegister[2]);
  digitalWrite(TRIG_PIN, LOW);;
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.034/2;

  Serial.print("Distance = ");
  Serial.println(distance);
  delay(100);
}

void setup(){
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  Mb.begin("E10BAC", "3HW155W001F44", ip, gateway, subnet);
//  Mb.begin("dlink-62EC", "nhvtg79881", ip, gateway, subnet);
  delay(1000);
}

void loop(){
  Mb.Run();
  Stop.attach_ms(35, monitoring);  
}
