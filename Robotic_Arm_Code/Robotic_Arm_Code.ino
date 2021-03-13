#include <SoftwareSerial.h>          // import the serial library
#include <Servo.h>

SoftwareSerial BTSerial(2, 3);  // Rx,Tx

Servo BaseServo;
Servo J1Servo;
Servo J2Servo;

int BasePose = 0;
int Joint1Pose = 90;
int Joint2Pose = 90;
int threshold = 1;
char msg = 0;

void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600);

  pinMode(7,OUTPUT);
  pinMode(6,OUTPUT);
  BaseServo.attach(9);
  J1Servo.attach(10);
  J2Servo.attach(11);

  BaseServo.write(0);
  J1Servo.write(90);
  J2Servo.write(90);
  digitalWrite(6,LOW);
  digitalWrite(7,LOW);
}

void loop() {
  if(BTSerial.available()>0){
    msg = BTSerial.read();
    Serial.println(msg);
    Serial.println(Joint2Pose);
    Serial.println(Joint1Pose);
    Serial.println(BasePose);
    Serial.println(threshold);
    if(msg == 'g'){   //               threshold control
      threshold += 1;
      if(threshold >= 10){
        threshold = 10;
        BTSerial.write(threshold);
      }
      else if(threshold <=1){
        threshold = 1;
        BTSerial.write(threshold);
      }
      else{
        BTSerial.write(threshold); 
      }
    }
    if(msg == 'h'){   //               threshold control
      threshold -= 1;
      if(threshold <= 1){
        threshold = 1;
        BTSerial.write(threshold);
      }
      else if(threshold >= 10){
        threshold = 10;
        BTSerial.write(threshold);
      }
      else{
        BTSerial.write(threshold);  
      }
    }
    if(msg == 'a'){ //           Base control +
      BasePose += threshold;
      if(BasePose<=0){
        BaseServo.write(0);
        BasePose = 0;
      }
      else if(BasePose>=180){
        BaseServo.write(180);
        BasePose = 180;
      }
      else{
        BaseServo.write(BasePose);
      }
    }
    if(msg == 'b'){   //            Base control -
      BasePose -= threshold;
      if(BasePose<=0){
        BaseServo.write(0);
        BasePose = 0;
      }
      else if(BasePose>=180){
        BaseServo.write(180);
        BasePose = 180;
      }
      else{
        BaseServo.write(BasePose);
      }
    }
    
    if(msg == 'c'){   //            Joint 1 control +
      Joint1Pose += threshold;
      if(Joint1Pose<=0){
        J1Servo.write(0);
        Joint1Pose = 0;
      }
      else if(Joint1Pose>=180){
        J1Servo.write(180);
        Joint1Pose = 180;
      }
      else{
        J1Servo.write(Joint1Pose);
      }
    }
    if(msg == 'd'){   //            Joint 1 control -
      Joint1Pose -= threshold;
      if(Joint1Pose<=0){
        J1Servo.write(0);
        Joint1Pose = 0;
      }
      else if(Joint1Pose>=180){
        J1Servo.write(180);
        Joint1Pose = 180;
      }
      else{
        J1Servo.write(Joint1Pose);
      }
    }
    if(msg == 'e'){ //            Joint 2 control +
      Joint2Pose += threshold;
      if(Joint2Pose<=0){
        J2Servo.write(0);
        Joint2Pose = 0;
      }
      else if(Joint2Pose>=180){
        J2Servo.write(180);
        Joint2Pose = 180;
      }
      else{
        J2Servo.write(Joint2Pose);
      }
    }
    if(msg == 'f'){   //            Joint 2 control -
      Joint2Pose -= threshold;
      if(Joint2Pose<=0){
        J2Servo.write(0);
        Joint2Pose = 0;
      }
      else if(Joint2Pose>=180){
        J2Servo.write(180);
        Joint2Pose = 180;
      }
      else{
        J2Servo.write(Joint2Pose);
      }
    }
    if(msg == 'x'){
        digitalWrite(6,LOW);
        digitalWrite(7,HIGH);
    }
    if(msg == 'y'){
        digitalWrite(6,LOW);
        digitalWrite(7,LOW);
    }
  }
}
