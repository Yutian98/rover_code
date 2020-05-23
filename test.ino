#include <NewPing.h>

const int maxDistance = 200; // the sensor can only output max 200cm

const int echoPin1   = 12;  //echoPin1 RIGHT SIDE
const int trigPin1   = 13;  //TriggerPin1

const int echoPin2   = 8;   //echoPin2  FRONT
const int trigPin2   = 9;   // TriggerPin2

//MotorLeft
const int leftForward  = 6;    // Pin 2 of SN754410NE IC
const int leftBackward  = 4;    // Pin 7 of SN754410NE IC
int EN1 = 11;                 // Pin 1 of SN754410NE IC

//MotorRight
const int rightForward  = 5;    // Pin  10 of SN754410NE IC
const int rightBackward  = 7;    // Pin  15 of SN754410NE IC
int EN2 = 10;                 // Pin 9 of SN754410NE IC

const int ms = 5000; // delay
long fDistance;    // front distance
long rDistance;    // left  distance


NewPing fSensor(trigPin2, echoPin2, maxDistance);  // front facing sensor
NewPing rSensor(trigPin1, echoPin1, maxDistance);  // left  facing sensor

void setup()
{
  Serial.begin(9600);
  pinMode(leftForward, OUTPUT);
  pinMode(rightForward, OUTPUT);
  pinMode(leftBackward, OUTPUT);
  pinMode(rightBackward, OUTPUT);

  pinMode(EN1, OUTPUT);
  pinMode(EN2, OUTPUT);

  delay(7000);
}

void loop()
{
  fDistance = fSensor.convert_cm(fSensor.ping_median(5));  // new median filter front sensor
  rDistance = rSensor.convert_cm(rSensor.ping_median(5));  // new median filter left  sensor
  Serial.print( "front sensor reading: ");
  Serial.println(fDistance);
  Serial.print( "right sensor reading: ");
  Serial.println(rDistance);

  if (rDistance > 10)   //Front blocked, turn right
  {

    right();
    Reset();
    rDistance = rSensor.convert_cm(rSensor.ping_median(5));
    if (rDistance<5){
      return;
    }
    right();
    Reset();
    rDistance = rSensor.convert_cm(rSensor.ping_median(5));
    if (rDistance<5){
      return;
    }
    right();
    Reset();
    rDistance = rSensor.convert_cm(rSensor.ping_median(5));
    if (rDistance<5){
      return;
    }
    fDistance = fSensor.convert_cm(fSensor.ping_median(5));
    if (fDistance<20){
      right();
      Reset();
      rDistance = rSensor.convert_cm(rSensor.ping_median(5));
      if (rDistance<5){
        return;
      }
      right();
      Reset();
      rDistance = rSensor.convert_cm(rSensor.ping_median(5));
      if (rDistance<5){
        return;
      }
      right();
      Reset();
      rDistance = rSensor.convert_cm(rSensor.ping_median(5));
      if (rDistance<5){
        return;
      }
    }else{
    straight();
    Reset();
  }
  delay(1000);
  Reset();
  }
  else if (rDistance < 5) {
      Reset();
      slight_left();
      Reset();
      return;
  }
  else if (rDistance > 8) {
      Reset();
      slight_right();
      Reset();
      return;
  }

if (fDistance > 8)
{
  straight();
  Reset();

}

}

void Reset()
{
digitalWrite(leftForward, LOW);
digitalWrite(leftBackward, LOW);   // Stop motor
digitalWrite(rightForward, LOW);
digitalWrite(rightBackward, LOW);
}

void straight()
{
analogWrite(EN1, 150);
analogWrite(EN2, 157);
digitalWrite(leftForward, HIGH);
digitalWrite(leftBackward, LOW);
digitalWrite(rightForward, HIGH);  // Go straight
digitalWrite(rightBackward, LOW);
delay(1500);
}

void reverse()
{
analogWrite(EN1, 150);
analogWrite(EN2, 160);
digitalWrite(leftForward, LOW);
digitalWrite(leftBackward, HIGH);
digitalWrite(rightForward, LOW);  // Reverse
digitalWrite(rightBackward, HIGH);
delay(160);
}

void right()
{
analogWrite(EN1, 173);
analogWrite(EN2, 150);
digitalWrite(leftForward, HIGH);
digitalWrite(leftBackward, LOW);   // Turn right
digitalWrite(rightForward, LOW);
digitalWrite(rightBackward, HIGH);
delay(950);
}

void left()
{
analogWrite(EN1, 150);
analogWrite(EN2, 173);
digitalWrite(leftForward, LOW);
digitalWrite(leftBackward, HIGH);   // Turn right
digitalWrite(rightForward, HIGH);
digitalWrite(rightBackward, LOW);
delay(950);
}

void slight_right()
{
analogWrite(EN1, 150);
analogWrite(EN2, 100);
digitalWrite(leftForward, HIGH);
digitalWrite(leftBackward, LOW);   // Turn slight_right
digitalWrite(rightForward, HIGH);
digitalWrite(rightBackward, LOW);
delay(100);
}

void slight_left()
{
analogWrite(EN1, 100);
analogWrite(EN2, 150);
digitalWrite(leftForward, HIGH);
digitalWrite(leftBackward, LOW);   // Turn slight_right
digitalWrite(rightForward, HIGH);
digitalWrite(rightBackward, LOW);
delay(100);
}
