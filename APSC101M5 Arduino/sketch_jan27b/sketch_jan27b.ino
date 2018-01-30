#include <NewPing.h>           //include the NewPing library for this program
#include <Servo.h>
#define GroundPin 10
#define echoPin 11
#define trigPin 12
#define VccPin 13

#define MAX_DISTANCE 200       //maximum distance set to 200 cm
#define MAX_HEIGHT 50

#define PICKUP 0
#define DROPOFF 1

Servo myservo;

int val1, val0;
int toggle = 0;
int pos = 0;

NewPing sonar(trigPin, echoPin, MAX_DISTANCE);  //initialize NewPing

void setup()                   //do the following things once
{
  Serial.begin(9600);          //set data transmission rate to communicate with computer
  pinMode(VccPin, OUTPUT) ;    //tell pin 13 it is going to be an output
  digitalWrite(VccPin, HIGH) ; //tell pin 13 to output HIGH (+5V)
  pinMode(GroundPin, OUTPUT) ; //tell pin 10 it is going to be an output
  digitalWrite(GroundPin,LOW) ;//tell pin 10 to output LOW (0V, or ground)
  myservo.attach(9);
}


void loop()                            //do the following things forever
{
  delay(100);                          //wait for this number of milliseconds
  int DISTANCE_IN_CM = sonar.ping_cm();//read the sonar sensor, using a variable  
  Serial.print("Ping: ");              //print "Ping:" on the computer display
  Serial.print(DISTANCE_IN_CM);        //print the value of the variable next
  Serial.println("cm");                //print "cm" after that, then go to next line
/*  if (DISTANCE_IN_CM > 20)
    myservo.write(180);
  else
    myservo.write(0);
*/


  if (DISTANCE_IN_CM < 30 && DISTANCE_IN_CM != 0 && toggle == PICKUP){
    Serial.println("Opening sequence initiated for pickup");
    pos = 179;
    myservo.write(pos);

    Serial.println("Opening");
    
    for (; pos >= 0; pos -= 2) { // goes from 0 degrees to 180 degrees
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
    
    delay(5000);
    Serial.println("Closing");
    
    for (; pos <= 180; pos += 2) { // goes from 180 degrees to 0 degrees
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }

    Serial.println("Closed");
    while(1){
       delay(100);
      if (sonar.ping_cm()>30)
        break;
      else
        continue;
    }

    Serial.println("Pick up complete");
    toggle = DROPOFF;
  }
  else if (DISTANCE_IN_CM < 30 && DISTANCE_IN_CM != 0 && toggle == DROPOFF){
    Serial.println("Opening sequence initiated for drop off");
    pos = 179;
    myservo.write(pos);
    
    Serial.println("Opening");
    
    for (; pos >= 0; pos -= 2) { // goes from 0 degrees to 180 degrees
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
    
    delay(5000);
    Serial.println("Closing");
    
    for (; pos <= 180; pos += 2) { // goes from 180 degrees to 0 degrees
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }

    Serial.println("Closed");
    while(1){
      delay(100);
      if (sonar.ping_cm()>30)
        break;
      else
        continue;
    }

    Serial.println("Drop off complete");
    toggle = PICKUP;
  }
  /*
  if (DISTANCE_IN_CM > MAX_HEIGHT)
    DISTANCE_IN_CM = MAX_HEIGHT;
   
  val0 = val1;
  val1 = map(DISTANCE_IN_CM, 0, MAX_HEIGHT, 0, 180);
  if (fabs(val1-val0) < MAX_HEIGHT && (val1 > 1) && fabs(val1-val0) > 5)
    myservo.write(val1);
  */
}
