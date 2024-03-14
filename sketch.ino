#include <Servo.h>  

int ServoLEFTPin = 8 ;   
int ServoRIGHTPin = 7 ;   
int HorizontalPotPin = A1;  
int VerticalPotPin = A0;  


Servo LEFTServo;  
Servo RIGHTServo;

int HorizontalPotValue;         
int LEFTServoPosition;    
int VerticalPotValue;         
int RIGHTServoPosition; 
int VerticalMovement;
int HorizontalAdjustment;

void setup()   
{
  LEFTServo.attach(ServoLEFTPin);   
  RIGHTServo.attach(ServoRIGHTPin); 
  pinMode(VerticalPotPin, INPUT);
  pinMode(HorizontalPotPin, INPUT);
  Serial.begin(9600);      
}

void loop()  
{

  int VerticalPotValue = analogRead(VerticalPotPin);  
  int HorizontalPotValue = analogRead(HorizontalPotPin); 

  // For vertical movements: Both servos move in sync
  int VerticalServoPosition = map(VerticalPotValue, 0, 1023, 60, 120); // 90 ± 30 degrees for flexion/extension
  
  // For horizontal movements: Servos move inversely within a ±20 degree range from their current vertical position
  int HorizontalAdjustment = map(HorizontalPotValue, 0, 1023, -20, 20); 
  int LEFTServoPosition = constrain(VerticalServoPosition + HorizontalAdjustment, 60, 120);
  int RIGHTServoPosition = constrain(VerticalServoPosition - HorizontalAdjustment, 60, 120);
  LEFTServo.write(LEFTServoPosition);       
  RIGHTServo.write(180-RIGHTServoPosition); 

  Serial.print("HorizontalPotValue: ");
  Serial.println(HorizontalPotValue);
  Serial.print("VerticalPotValue: ");
  Serial.println(VerticalPotValue);
  Serial.print("LEFTServoPosition: ");
  Serial.println(LEFTServoPosition);
  Serial.print("RIGHTServoPosition: ");
  Serial.println(RIGHTServoPosition);
}
