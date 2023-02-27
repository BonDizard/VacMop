#include<Servo.h>
#define eye 5
Servo myservo;

char t;
int right_ir;
int left_ir;
int distance;
int pos;

void setup() {
  pinMode(13,OUTPUT);  
  pinMode(12,OUTPUT); 
  pinMode(11,OUTPUT); 
  pinMode(10,OUTPUT);
  pinMode(2,INPUT);             //left ir
  pinMode(3,INPUT);             //RIGHT IR
  pinMode(3,INPUT);             //ULTRA SONIC
  Serial.begin(9600);
}

void loop() {
    if(Serial.available()){
      t = Serial.read();
      Serial.println(t);
      if(t == 'F'){
            digitalWrite(13,HIGH);
            digitalWrite(11,HIGH);
           }
      else if(t == 'B'){
            digitalWrite(12,HIGH);
            digitalWrite(10,HIGH);
          } 
      else if(t == 'L'){
            digitalWrite(11,HIGH);
          } 
      else   if(t == 'R'){
              digitalWrite(13,HIGH);
          }
      else if(t == 'S'){
              digitalWrite(13,LOW);
              digitalWrite(12,LOW);
              digitalWrite(11,LOW);
              digitalWrite(10,LOW);
          }
    }
}
