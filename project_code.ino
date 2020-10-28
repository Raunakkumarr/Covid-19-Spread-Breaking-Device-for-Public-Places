//Code Developed by Raunak Kumar for NAST's Project
// Define pin numbers
  //Pins for Entry Ultrasonic Sensor
    const int entryTrigPin = 2;
    const int entryEchoPin = 3;
  //Pins for Exit Ultrasonic Sensor
    const int exitTrigPin = 4;
    const int exitEchoPin = 5;
  //Define variables
    long entryDuration, exitDuration;
    int entryDistance, exitDistance, leftN;
    int maxN = 20;
    int currentN = 1;
    int sensorLimit = 15;
//Setup Code
void setup() {
  //Declares Pinmode for Entry Sensor
    pinMode(entryTrigPin, OUTPUT); // Sets the trigPin as an Output
    pinMode(entryEchoPin, INPUT); // Sets the echoPin as an Input
  //Declares Pinmode for Exit Sensor
    pinMode(exitTrigPin, OUTPUT);
    pinMode(exitEchoPin, INPUT);
  // Starts the serial communication
    Serial.begin(9600);
}
//Loop Code
void loop() {
  //If there is no place left for the person to enter.
  if(currentN >= maxN){
    //Prints the place is full.
    Serial.println("Place Full, please wait.");
    //Checks Exit Sensor
      //Clears the Exit TrigPin
        digitalWrite(exitTrigPin, LOW);
        delayMicroseconds(2);
      //Sets the Exit TrigPin on HIGH state for 10 micro seconds
        digitalWrite(exitTrigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(exitTrigPin, LOW);
      //Reads the Exit EchoPin, returns the sound wave travel time in microseconds
        exitDuration = pulseIn(exitEchoPin, HIGH);
      //Calculating the exit distance
        exitDistance= exitDuration*0.034/2;
      //Prints the exit distance on the Serial Monitor
        Serial.print("Exit Distance: ");
        Serial.println(exitDistance);
      //Checks if Someone has Scanned on Exit Sensor or not
        if(exitDistance <= sensorLimit){
          //Decreses the Current Person Count
          currentN = currentN - 1;
          //Delays
          delay(7000);
          //Prints the number of People for Whom Place is Available
          Serial.println("No. of people can enter inside:");
          //Calculates the number of People for Whom Place is Available
          leftN = maxN - currentN;
          Serial.println(leftN);
        }
  }
  //If there is place left for the person to enter.
  else{
   Serial.println("Please come for scanning.");
   //Checks Entry Sensor
    //Clears the Entry TrigPin
      digitalWrite(entryTrigPin, LOW);
      delayMicroseconds(2);
      //Sets the Entry TrigPin on HIGH state for 10 micro seconds
      digitalWrite(entryTrigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(entryTrigPin, LOW);
      //Reads the Entry EchoPin, returns the sound wave travel time in microseconds
      entryDuration = pulseIn(entryEchoPin, HIGH);
      //Calculating the Entry Distance
      entryDistance= entryDuration*0.034/2;
      //Prints the Entry Distance on the Serial Monitor
      Serial.print("Entry Distance: ");
      Serial.println(entryDistance);
    //Checks if Someone has Scanned on Entry Sensor or not
      if(entryDistance <= sensorLimit){
        //Increses the Current Person Count
        currentN = currentN + 1;
        //Delays
        delay(7000);
        //Prints the number of People for Whom Place is Available
        Serial.println("No. of people can enter inside:");
        //Calculates the number of People for Whom Place is Available
        leftN = maxN - currentN;
        Serial.println(leftN);
      }
  }
  // Clears the Exit TrigPin
    digitalWrite(exitTrigPin, LOW);
    delayMicroseconds(2);
    // Sets the Exit TrigPin on HIGH state for 10 micro seconds
    digitalWrite(exitTrigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(exitTrigPin, LOW);
    // Reads the Exit EchoPin, returns the sound wave travel time in microseconds
    exitDuration = pulseIn(exitEchoPin, HIGH);
    // Calculating the Exit Distance
    exitDistance= exitDuration*0.034/2;
    // Prints the Exit Distance on the Serial Monitor
    Serial.print("Exit Distance: ");
    Serial.println(exitDistance);
    //Checks if Someone has Scanned on Exit Sensor or not
    if(exitDistance <= sensorLimit){
      //Decreses the Current Person Count
      currentN = currentN - 1;
      //Delays
      delay(7000);
      //Prints the number of People for Whom Place is Available
      Serial.println("No. of people can enter inside:");
      //Calculates the number of People for Whom Place is Available
      leftN = maxN - currentN;
      Serial.println(leftN);
    }
}
