// Created by Raunak
#include <Wire.h>
#include <Adafruit_MLX90614.h>                 //Includes Library for MLX90614 Temperature Sensor
Adafruit_MLX90614 mlx = Adafruit_MLX90614();   //Renames Adafruit MLX90614 library to mlx
#include <LiquidCrystal.h>                     //Includes Library for LCD
#include <Servo.h>                             //Includes Servo Library

//LED sign pins
int redLedPin = 11;
int yellowLedPin = 12;
int greenLedPin = 13;

//Entry ultrasonic sensor Pins
int entryEchoPin = 7;
int entryTrigPin = 6;

//Exit ultrasonic sensor Pins
int exitEchoPin = 9;
int exitTrigPin = 10;

//Pins for motor
int motorPin = 8;
Servo RaunakServo;  //Creates Servo Object

//Pins for IR Temperature Sensor
int sclPin = 5;
int sdaPin = 6;

//Pins for LCD
LiquidCrystal lcd(A0,A1,A2,A3,A4,A5);
/*
LCD -> Arduino Pin
RS -> A0
Enable -> A1
D4 -> A2
D5 -> A3
D6 -> A4
D7 -> A5
R/W -> Gnd
Vss -> Gnd
Vcc -> 5V
*/

void setup() {
  Serial.begin(9600);  
  //Setting the LED pins
  pinMode(redLedPin, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  //Setting the entry ultrasonic sesnor pins
  pinMode(entryEchoPin, OUTPUT);
  pinMode(entryTrigPin, INPUT);
  //Setting the exit ultrasonic sesnor pins
  pinMode(exitEchoPin, OUTPUT);
  pinMode(exitTrigPin, INPUT);
  //Setting Motor Pins
  pinMode(motorPin, OUTPUT);
  RaunakServo.attach(8);
  //Setting LCD Pins
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);
  lcd.begin(16, 2);
  lcd.print("Please wear your mask and follow the instructions.");//Prints the message on LCD
  lcd.setCursor(0, 1);//Sets the cursor at the desired point. Here, 0is the first column and 1 is the second row.
  lcd.print("Numbers of People Inside: 0");//Prints the no. of seconds since reset
}

void loop() {
  //variables to be used
  long maxN, currentN, exitduration, exitdistance, entryduration, entrydistance;
  //Any distance under this value (cm) is a confirmed scan
  int sensorLimit = 15;
  //If current customer count is greater or equal to max allowance, show the red sign.
  if (currentN >= maxN) {
    digitalWrite(redLedPin, HIGH);
    lcd.print("The place is filled, please wait.");
    lcd.scrollDisplayLeft();
    //Taking a exit sensor reading
        // Clears the trigPin
        digitalWrite(exitTrigPin, LOW);
        delayMicroseconds(2);
        // Sets the trigPin on HIGH state for 10 micro seconds
        digitalWrite(exitTrigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(exitTrigPin, LOW);
        // Reads the echoPin, returns the sound wave travel time in microseconds
        exitduration = pulseIn(exitEchoPin, HIGH);
        // Calculating the distance
        exitdistance= entryduration*0.034/2;
        // Prints the distance on the Serial Monitor
        Serial.print("Distance: ");
        Serial.println(exitdistance);
        if(exitdistance <= sensorLimit){
          //Noting the departure of a person
          currentN--;
          //Turns all lights On
          digitalWrite(redLedPin, HIGH);
          digitalWrite(yellowLedPin, HIGH);
          digitalWrite(greenLedPin, HIGH);
          //Opens the door for exit
          RaunakServo.write(90);  //Makes Servo go to 90 degrees
          delay(60000);
          }
  }
  //Otherwise show the yellow sign and detect for an entry
  else {
    digitalWrite(yellowLedPin, HIGH);
    lcd.print("Place is vacant for segmentN people, please scan yourself to enter.");
    //Taking a enrty sensor reading
      // Clears the trigPin
      digitalWrite(entryTrigPin, LOW);
      delayMicroseconds(2);
      // Sets the trigPin on HIGH state for 10 micro seconds
      digitalWrite(entryTrigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(entryTrigPin, LOW);
      // Reads the echoPin, returns the sound wave travel time in microseconds
      entryduration = pulseIn(entryEchoPin, HIGH);
      // Calculating the distance
      entrydistance= entryduration*0.034/2;
      // Prints the distance on the Serial Monitor
      Serial.print("Distance: ");
      Serial.println(entrydistance);
    //If the distance is below the sensorLimit and there is space, the green light will turn on
    if (entrydistance <= sensorLimit & currentN < maxN) {
      digitalWrite(yellowLedPin, LOW);
      lcd.setCursor(0, 1);
      lcd.print("Get your Temperature Checked");
      //Checks Temperature
      mlx.begin();           //need to store the temperature measured as a variable x
      if(mlx.readObjectTempC()<38){                  //need to execute the function say, if x<30
       //Noting the entry of a person
       currentN++;
       digitalWrite(greenLedPin, HIGH);
       lcd.setCursor(0, 1);
       lcd.print("Getting your Temperature Checked");
       //Opens the door for entry
       RaunakServo.write(90);  //Makes Servo go to 90 degrees
       delay(60000);
      }
      else{
        lcd.setCursor(0, 1);
        lcd.print("Due to high body temperature, we can't allow you to enter.");
        //Taking a exit sensor reading
        // Clears the trigPin
        digitalWrite(exitTrigPin, LOW);
        delayMicroseconds(2);
        // Sets the trigPin on HIGH state for 10 micro seconds
        digitalWrite(exitTrigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(exitTrigPin, LOW);
        // Reads the echoPin, returns the sound wave travel time in microseconds
        exitduration = pulseIn(exitEchoPin, HIGH);
        // Calculating the distance
        exitdistance= entryduration*0.034/2;
        // Prints the distance on the Serial Monitor
        Serial.print("Distance: ");
        Serial.println(exitdistance);
        if(exitdistance <= sensorLimit){
          //Noting the departure of a person
          currentN--;
          digitalWrite(redLedPin, HIGH);
          digitalWrite(yellowLedPin, HIGH);
          digitalWrite(greenLedPin, HIGH);
          //Opens the door for exit
          RaunakServo.write(90);  //Makes Servo go to 90 degrees
          delay(60000);
        }
      }
    }
    else{
      //Taking a exit sensor reading
        // Clears the trigPin
        digitalWrite(exitTrigPin, LOW);
        delayMicroseconds(2);
        // Sets the trigPin on HIGH state for 10 micro seconds
        digitalWrite(exitTrigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(exitTrigPin, LOW);
        // Reads the echoPin, returns the sound wave travel time in microseconds
        exitduration = pulseIn(exitEchoPin, HIGH);
        // Calculating the distance
        exitdistance= entryduration*0.034/2;
        // Prints the distance on the Serial Monitor
        Serial.print("Distance: ");
        Serial.println(exitdistance);
        if(exitdistance <= sensorLimit){
          //Noting the departure of a person
          currentN--;
          digitalWrite(redLedPin, HIGH);
          digitalWrite(yellowLedPin, HIGH);
          digitalWrite(greenLedPin, HIGH);
          //Opens the door for exit
          RaunakServo.write(90);  //Makes Servo go to 90 degrees
          delay(60000);
        }
    }
  }

  //If a person can leave, detect for one
  if (currentN > 0) {
    //Taking a exit sensor reading
        // Clears the trigPin
        digitalWrite(exitTrigPin, LOW);
        delayMicroseconds(2);
        // Sets the trigPin on HIGH state for 10 micro seconds
        digitalWrite(exitTrigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(exitTrigPin, LOW);
        // Reads the echoPin, returns the sound wave travel time in microseconds
        exitduration = pulseIn(exitEchoPin, HIGH);
        // Calculating the distance
        exitdistance= entryduration*0.034/2;
        // Prints the distance on the Serial Monitor
        Serial.print("Distance: ");
        Serial.println(exitdistance);
    if (exitdistance <= sensorLimit) {
      currentN--;
      //Putting all lights on to indicate the departure has been read.
      digitalWrite(yellowLedPin, HIGH);
      digitalWrite(greenLedPin, HIGH);
      digitalWrite(redLedPin, HIGH);
      currentN--;
      Serial.println("Person left the room, person Count:");
      Serial.println(currentN);
      delay(3000);
      //Opens the door for exit
      RaunakServo.write(90);  //Makes Servo go to 90 degrees
      delay(60000);
    }
  }
  //resetting the lights
  digitalWrite(yellowLedPin, LOW);
  digitalWrite(greenLedPin, LOW);
  digitalWrite(redLedPin, LOW);
}
