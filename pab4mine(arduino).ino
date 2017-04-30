//initialisation library
#include <Wire.h> 
#include "HTU21D.h" 
#include "BH1750.h"
#include <AFMotor.h>
#include <SoftwareSerial.h>

//initialisation object
HTU21D myHumidity; //temp and hum
BH1750 lightMeter; //light
SoftwareSerial btSerial(5, 4); //bluetooth
AF_DCMotor motor1(1); 
AF_DCMotor motor2(2);

void setup() {
btSerial.begin(9600);
btSerial.println("start");
pinMode(13,OUTPUT);
digitalWrite (13,HIGH);
myHumidity.begin();
lightMeter.begin();
}

void btProcessor () //
{
  String receivedString = btSerial.readStringUntil('\n');
   btSerial.print("recive : ");                                                                                                                                                                                 
   btSerial.println (receivedString);
  Serial.println (receivedString);
  if (receivedString == "move")
  {    
    //move forward
    motor1.setSpeed(255);
    motor2.setSpeed(255);
    motor1.run(FORWARD);
    motor2.run(FORWARD);
  }
  else if (receivedString == "stop")
  {
    //dont move
    motor1.setSpeed(255);
    motor2.setSpeed(255);
    motor1.run(RELEASE);
    motor2.run(RELEASE); 
  }
  else if (receivedString == "back")
  {   
    //move back 
    motor1.setSpeed(255);
    motor2.setSpeed(255);
    motor1.run(RELEASE);
    motor2.run(RELEASE); 
    motor1.run(BACKWARD);
    motor2.run(BACKWARD);
  }
  else
  {
    btSerial.println("Failed!! Not correct request");
  }
}
void loop() {
  //bleutooth request
  if(btSerial.available())
  {
    btProcessor ();
  }
  
  //data set
  float humd = myHumidity.readHumidity();
  float temp = myHumidity.readTemperature();
  uint16_t lux = lightMeter.readLightLevel();

  //bleutooth output
  btSerial.print(temp);
  btSerial.print("|");
  btSerial.print(humd);
  btSerial.print("|");
  btSerial.println(lux);

  //checkworks
  digitalWrite (13,HIGH);
  delay(200);
  digitalWrite (13,LOW);
  delay(200);
}