#include <ESP8266WiFi.h>
#include <ModbusTCPSlave.h>
#include <Ticker.h>

#define MBDebug 

Ticker Stop;
ModbusTCPSlave Mb;

#define TRIG_PIN D1
#define ECHO_PIN D2
#define SWITCH_PIN D3

// Network Addresses
byte ip[] = {192, 168, 0, 40};
byte gateway[] = {192, 168, 0, 1};
byte subnet[] = {255, 255, 255, 0};

long duration;
int distance, prev_distance;
int sw, count;

void monitoring(){
  Mb.MBHoldingRegister[0] = 234; 
  Mb.MBHoldingRegister[1] = distance;
  int sinSwitchVal = 50 + 50*sin(3.1415*count/180);
  Mb.MBHoldingRegister[2] = sinSwitchVal;
  Mb.MBHoldingRegister[3] = count/40;
  
  
//  Serial.println(Mb.MBHoldingRegister[2]);

  sw = digitalRead(SWITCH_PIN);
  int new_distance = (analogRead(A0) - 630)/2;
  distance = (new_distance + prev_distance)/2;
  prev_distance = new_distance;
  
  Serial.print(-50+(-10)*sw);Serial.print("\t");Serial.println(sinSwitchVal);
  if(sw == 0){
    count+=2;
  }
  delay(50);
}

void setup(){
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
//  Mb.begin("E10BAC", "3HW155W001F44", ip, gateway, subnet);
  Mb.begin("dlink-62EC", "nhvtg79881", ip, gateway, subnet);
  delay(1000);
}

void loop(){
  Mb.Run();
  Stop.attach_ms(35, monitoring);  
}
