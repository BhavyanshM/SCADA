#include <ESP8266WiFi.h>
#include <ModbusTCPSlave.h>
#include <Ticker.h>

Ticker Stop;
ModbusTCPSlave Mb;

// Network Addresses
byte ip[] = {192, 168, 0, 29};
byte gateway[] = {192, 168, 0, 1};
byte subnet[] = {255, 255, 255, 0};


void monitoring(){
  digitalWrite(LED_BUILTIN, Mb.MBHoldingRegister[0]);  
  
}

void setup(){
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  Mb.begin("E10BAC", "3HW155W001F44", ip, gateway, subnet);
  delay(1000);
}

void loop(){
  Mb.Run();
  Stop.attach_ms(35, monitoring); 
}
