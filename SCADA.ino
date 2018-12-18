#include <SM.h>
#include <State.h>

#include <SPI.h>
#include <MCP492X.h>
#include <Mcp23s17.h>

#define XPAND_1_CS_PIN 2 //Chip Select Pin for the first MCP23S17
#define DAC_CS_PIN 5 //Chip Select Pin for the MCP4921

MCP23S17 xpand1 = MCP23S17( XPAND_1_CS_PIN, 0x01 );//Address B001
MCP492X dac1 = MCP492X(DAC_CS_PIN);//DAC Instantiation

SM STM(S0);

void setup() {
  // put your setup code here, to run once:
  pinMode(XPAND_1_CS_PIN, OUTPUT);//Set CS for first MCP23S17 as output
  xpand1.pinMode(0, OUTPUT);
  xpand1.pinMode(1, OUTPUT);
  xpand1.pinMode(2, OUTPUT);
  xpand1.pinMode(3, OUTPUT);
  xpand1.pinMode(4, OUTPUT);
  xpand1.pinMode(5, OUTPUT);
  xpand1.pinMode(6, OUTPUT);
  xpand1.pinMode(7, OUTPUT);
  xpand1.pinMode(8, INPUT);
  xpand1.pinMode(9, INPUT);
  xpand1.pinMode(10, INPUT);
  xpand1.pinMode(11, INPUT);
  xpand1.pinMode(12, INPUT);
  xpand1.pinMode(13, INPUT);
  xpand1.pinMode(14, INPUT);
  xpand1.pinMode(15, INPUT);

  Serial.begin(9600);
  
//  xpand1.pinMode(OUTPUT);
//  xpand1.port(0x0000);

  dac1.begin();
  
 
  
}
int input = 0;
int i = 0;
void loop() {
  input = xpand1.port()/256;//Get the MSB of the xpand1 port
//  Serial.println(input, HEX);//Print the MSB of the xpand1 port to the Serial Monitor
  EXEC(STM);//Execute the State machine
}


// State Machines States for STM Start Here
State S0(){
   Serial.println("State_0");
   xpand1.port(0x0000);
   if(input==0x10 || input==0x11)STM.Set(S1);
   if(input==0x40 || input==0x41)STM.Set(S2);
}

State S1(){
  Serial.println("State_1");
  xpand1.port(0xFFFF);
  if(input==0x20 || input==0x21)STM.Set(S0); 
  if(input==0x40 || input==0x41)STM.Set(S2); 
}

State S2(){
  Serial.println("State_2");
  i++;i%=0xFF;
  dac1.analogWrite(2048);
  xpand1.port(i);
  delay(200);
  if(input==0x20 || input==0x21)STM.Set(S0);
  if(input==0x10 || input==0x11)STM.Set(S1);
}
