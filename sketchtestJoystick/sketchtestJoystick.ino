#include <Servo.h>
//motor 1
#define DELAY 200
#define speedPinA 5
#define directionA1 4 //IN 1
#define directionA2 3 //IN 2
// motor 2
#define speedPinB 6
#define directionB1 7 //IN 3
#define directionB2 8 //IN 4
//joystick
#define xPin A0
#define yPin A1
#define switchPin 2

Servo servoA;
int aCurrAngle = 0;

int speedA = 180;
int speedB = 180;
int xCor;
int yCor;
int Ss;

int engineResult;
int startingMotor(int);
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

//servo pin meegeven
servoA.attach(10);
servoA.write(0);

//pinmodes motor 1
pinMode(speedPinA, OUTPUT);
pinMode(directionA1, OUTPUT);
pinMode(directionA2, OUTPUT);

//pinmodes motor 2
pinMode(speedPinA, OUTPUT);
pinMode(directionB1, OUTPUT);
pinMode(directionB2, OUTPUT);

//joystick
pinMode(xPin, INPUT);
pinMode(yPin, INPUT);
pinMode(switchPin, INPUT);
digitalWrite(switchPin, HIGH);


}

void loop() {
  // put your main code here, to run repeatedly:
  xCor = analogRead(xPin);
  yCor = analogRead(yPin);
  Ss = digitalRead(switchPin);
  delay(DELAY);
  Serial.print("XCor = ");
  Serial.print(xCor);
  Serial.print("YCor = ");
  Serial.print(yCor);
  Serial.print(" Switch state is ");
  Serial.println(Ss);  
  analogWrite(speedPinA, speedA);
  analogWrite(speedPinB, speedB);
  //voruit rijden
  if(xCor < 250 && yCor < 750 && yCor > 250 && speedA == 0 && speedB == 0&& Ss == 1)
  {
    int draaien = 0;
    //dan motor starten in vooruit
    digitalWrite(directionA1, HIGH);
    digitalWrite(directionA2, LOW);
    
    digitalWrite(directionB1, LOW);
    digitalWrite(directionB2, HIGH);
    engineResult = startingMotor(draaien);
  }
  //achteruit rijden
  if(xCor > 750 && yCor < 750 && yCor > 250 && speedA == 0 && speedB == 0 && Ss == 1)
  {
    int draaien = 0;
    digitalWrite(directionA1, LOW);
    digitalWrite(directionA2, HIGH);
    
    digitalWrite(directionB1, HIGH);
    digitalWrite(directionB2, LOW);
    engineResult = startingMotor(draaien);
  }
  //links draaien
  if(yCor > 750 && xCor > 250 && xCor < 750 && speedA == 0 && speedB == 0 && Ss == 1)
  {
    int draaien = 1;
    digitalWrite(directionA1, HIGH);
    digitalWrite(directionA2, LOW);
    
    digitalWrite(directionB1, HIGH);
    digitalWrite(directionB2, LOW);
    engineResult = startingMotor(draaien);
  }
  //rechts draaien
  if(yCor < 250 && xCor > 250 && xCor < 750 && speedA == 0 && speedB == 0 && Ss == 1)
  {
    int draaien = 1;
    digitalWrite(directionA1, LOW);
    digitalWrite(directionA2, HIGH);
    
    digitalWrite(directionB1, LOW);
    digitalWrite(directionB2, HIGH);
    engineResult = startingMotor(draaien);
  }
  
  //als het volledig geaccellereert is en nog moet blijven doorrijden
  if (engineResult == 1 && Ss == 1)
   {
   speedA = 255;
   speedB = 255;
   analogWrite(speedPinA, speedA);
   analogWrite(speedPinB, speedB);
   engineResult = 0;
  }
  xCor = analogRead(xPin);
  yCor = analogRead(yPin);
  
  //als het niet meer verder mag rijden
  if (xCor > 250 && xCor < 750 && yCor < 750 && yCor > 250)
  {
    speedA = 0;
    speedB = 0;
    analogWrite(speedPinA, speedA);
    analogWrite(speedPinB, speedB);
  }
   if(Ss == 0 && yCor > 750)
  {
    while((Ss = digitalRead(switchPin)) == 1 && yCor > 750 && aCurrAngle < 40)
    {
      servoA.write(aCurrAngle);
      aCurrAngle++;
      delay(20);
      
    }
  }
   if(Ss == 0 && yCor < 250)
  {
    while((Ss = digitalRead(switchPin)) == 1 && yCor < 250 && aCurrAngle > 0)
    {
      servoA.write(aCurrAngle);
      aCurrAngle--;
      delay(20);
      
      
    }
  }
}

int startingMotor(int draaien){
  speedA = 70;
  speedB = 50;
  analogWrite(speedPinA, speedA);
  analogWrite(speedPinB, speedB);
  while(speedA < 255 && speedB < 255)
  {
    if (draaien == 0)
    {
      xCor = analogRead(xPin);
      if(xCor > 250 && xCor < 750)
      {
        speedA = 0;
        speedB = 0;
        analogWrite(speedPinA, speedA);
        analogWrite(speedPinB, speedB);
        return 0;
      }
    }
    if(draaien == 1)
    {
      yCor = analogRead(yPin);
      if(yCor > 250 && yCor < 750)
      {
        speedA = 0;
        speedB = 0;
        analogWrite(speedPinA, speedA);
        analogWrite(speedPinB, speedB);
        return 0;
      }
    }
    delay(20);
    speedA+=1;
    speedB+=1;
    analogWrite(speedPinA, speedA);
    analogWrite(speedPinB, speedB);
  }
  return 1;
}
