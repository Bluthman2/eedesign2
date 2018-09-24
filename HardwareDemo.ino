/*----- Libraries -----*/
#include <SoftwareSerial.h>  /*  If using Arduino with multiple hardware Serial Interfaces (such as Arudino Mega), you can use regular Serial Library instead of SoftwareSerial
/*----- Pin Numbers -----*/
#define HC_05_TX_1ST   2
#define HC_05_RX_1ST   3
#define HC_05_EN_PIN_1ST   4

#define FLEX_PIN_1 A0 // Pin connected to voltage divider output
#define FLEX_PIN_2 A1 // Pin connected to voltage divider output
#define FLEX_PIN_3 A2 // Pin connected to voltage divider output

SoftwareSerial BT1(HC_05_TX_1ST, HC_05_RX_1ST); // Software Serial setup for RX / TX pins Bluetooth module 1

// Measure the voltage at 5V and the actual resistance of your
// 47k resistor, and enter them below:
const float VCC = 4.98; // Measured voltage of Ardunio 5V line
const float R_DIV = 10000.0; // Measured resistance of 3.3k resistor

// Upload the code, then try to adjust these values to more
// accurately calculate bend degree.
const float STRAIGHT_RESISTANCE = 37300.0; // resistance when straight
const float BEND_RESISTANCE = 90000.0; // resistance at 90 deg

void setup() 
{
  pinMode(FLEX_PIN_1, INPUT);
  pinMode(FLEX_PIN_2, INPUT);
  pinMode(FLEX_PIN_3, INPUT);
  
  pinMode(HC_05_EN_PIN_1ST, OUTPUT);  // Setting up pins on Arduino as output to pull HC-05 EN pin high to go into AT Command Mode for adjusting settings

  /* AT Commands to setup BT Module as 'Master' only needs to be done once, 
     after initial setup is complete then you no longer need to go into AT Command Mode so pull EN Pin LOW instead of HIGH
     BT module defaults to 'Slave' */
  
  digitalWrite(HC_05_EN_PIN_1ST, LOW);  // Put HC-05 module 1 into Data Transfer Mode
  
  Serial.begin(9600);   // For the Arduino IDE Serial Monitor
  Serial.println("Set Serial Monitor to 'Both NL & CR' and '9600 Baud'"); // Just a Reminder
  
  BT1.begin(38400);  // HC-05 default UART Serial speed = 38400
  BT1.flush();
  delay(250); // small delay to setup connection
}

void loop() 
{
  String toSend = "";
  // Read the ADC, and calculate voltage and resistance from it
  int flexADC_1 = analogRead(FLEX_PIN_1);
  float flexV_1 = flexADC_1 * VCC / 1023.0;
  float flexR_1 = R_DIV * (VCC / flexV_1 - 1.0);
  Serial.println("Resistance 1: " + String(flexR_1) + " ohms");
  int angle_1 = map(flexR_1, STRAIGHT_RESISTANCE, BEND_RESISTANCE,
                   0, 10);
  angle_1 = constrain(angle_1,0,9);                 
  Serial.println(angle_1);
  toSend += "A" + String(angle_1);
  // Read the ADC, and calculate voltage and resistance from it
  int flexADC_2 = analogRead(FLEX_PIN_2);
  float flexV_2 = flexADC_2 * VCC / 1023.0;
  float flexR_2 = R_DIV * (VCC / flexV_2 - 1.0);
  Serial.println("Resistance 2: " + String(flexR_2) + " ohms");
  int angle_2 = map(flexR_2, STRAIGHT_RESISTANCE, BEND_RESISTANCE,
                   0, 9);
  angle_2 = constrain(angle_2,0,9);
  toSend += "B" + String(angle_2);
  // Read the ADC, and calculate voltage and resistance from it
  int flexADC_3 = analogRead(FLEX_PIN_3);
  float flexV_3 = flexADC_3 * VCC / 1023.0;
  float flexR_3 = R_DIV * (VCC / flexV_3 - 1.0);
  Serial.println("Resistance 3: " + String(flexR_3) + " ohms");
  int angle_3 = map(flexR_3, STRAIGHT_RESISTANCE, BEND_RESISTANCE,
                   0, 10);
  angle_3 = constrain(angle_3,0,9);
  toSend += "C" + String(angle_3);
  Serial.println(toSend);
  BT1.println(toSend);
  delay(500);
}
