#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
float value;
int tmp = A1;
const int ledPin = 13;   //the number of the LED pin
const int ldrPin = A0;  //the number of the LDR pin
int v_GasSen = 0; //Gas sensor pins

void setup() 
{
 pinMode(tmp,INPUT);
 
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);  //initialize the LED pin as an output
  pinMode(ldrPin, INPUT);   //initialize the LDR pin as an input
  
  pinMode(A2, INPUT);
  pinMode(7, OUTPUT);
 }

void loop() 
{
  
  //Checking temperature
  value = analogRead(tmp)* 0.00482814;
  value =(value - 0.5) * 100.0; // Converting temperature to celcius
  
  lcd.setCursor(0, 1); // Setting cursor for LCD
  lcd.print("Tmp:");
  lcd.print(value); //Displaying value read and converted
  delay(1000);
  lcd.clear();
  
  
  //LED Implementation
  int ldrStatus = analogRead(ldrPin);   //read the status of the LDR value

  //check if the LDR status is <= 300
  //if it is, the LED is HIGH

  if (ldrStatus <=300) 
  {
    digitalWrite(ledPin, HIGH);           //turn LED on
    Serial.println("LDR is DARK, LED is ON");
   }
  else 
  {
    digitalWrite(ledPin, LOW);          //turn LED off
    Serial.println("---------------");
	}
  
  
  //Gas sensor Implementation
  v_GasSen = analogRead(A2);
  if (v_GasSen >= 250) 
  {
    tone(7, 523, 1000); // play tone 60 (C5 = 523 Hz)
  }
  delay(10); // Delay a little bit to improve simulation performance

}
   
