/*----- Libraries -----*/
#include <SoftwareSerial.h>  /*  If using Arduino with multiple hardware Serial Interfaces (such as Arudino Mega), you can use regular Serial Library instead of SoftwareSerial
/*----- Pin Numbers -----*/
#define HC_05_TX_1ST   5
#define HC_05_RX_1ST   6
#define HC_05_EN_PIN_1ST   7

const int LED_PINS[3] = {8,9,10};

SoftwareSerial BT1(HC_05_TX_1ST, HC_05_RX_1ST); // Software Serial setup for RX / TX pins Bluetooth module 1

void setup() 
{
  //Setup LED Pins
  for(int i = 0; i < 3; i++){
    pinMode(LED_PINS[i],OUTPUT);
    digitalWrite(LED_PINS[i],0);
  }
  
  //Setup bluetooth
  pinMode(HC_05_EN_PIN_1ST, OUTPUT);  // Setting up pins on Arduino as output to pull HC-05 EN pin high to go into AT Command Mode for adjusting settings

  digitalWrite(HC_05_EN_PIN_1ST, LOW);  // Put HC-05 module 1 into Data Transfer Mode
  
  Serial.begin(9600);   // For the Arduino IDE Serial Monitor
  Serial.println("Set Serial Monitor to 'Both NL & CR' and '9600 Baud'"); // Just a Reminder
  
  BT1.begin(38400);  // HC-05 default UART Serial speed = 38400
  BT1.flush();
  delay(250); // small delay to setup connection
}

void loop() 
{
  int prevValue = 0;
  int valueRead = 0; //- '0' converts to integer
  if (BT1.available()){
    while(BT1.available()){
      // Read current value
      valueRead = BT1.read();
      // Based on last received character, turn on appropriate LED
      // A is LED 0, B is LED 1, C is LED 2
      if(prevValue == 'A'){
        if((valueRead- '0') > 6){
          digitalWrite(LED_PINS[0],1);
        }
        else{
          digitalWrite(LED_PINS[0],0);
        }
      }
      else if(prevValue == 'B'){
        if((valueRead- '0') > 6){
          digitalWrite(LED_PINS[1],1);
        }
        else{
          digitalWrite(LED_PINS[1],0);
        }
      }
      else if(prevValue == 'C'){
        if((valueRead - '0') > 6){
          digitalWrite(LED_PINS[2],1);
        }
        else{
          digitalWrite(LED_PINS[2],0);
        }
      }
      //Store previous value
      prevValue = valueRead;
    }
  }


  delay(500);
}
