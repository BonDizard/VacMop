#include<Servo.h>
#define eye 5
Servo myservo;

char t;
int distance = 0;
int trig = 8;
int echo = 9;
int t1 = 0;
int right_ir;
int left_ir;
int pos;

void setup() {
  Serial.begin(9600);
  pinMode(13,OUTPUT);  
  pinMode(12,OUTPUT); 
  pinMode(11,OUTPUT); 
  pinMode(10,OUTPUT);
  pinMode(2,INPUT);                  //left ir
  pinMode(3,INPUT);                  //RIGHT IR
  pinMode(trig, OUTPUT);             //ULTRA SONIC
  pinMode(echo, INPUT);  
   myservo.attach(7); 
}

void loop() {
    digitalWrite(trig,HIGH);
    delayMicroseconds(10);
    digitalWrite(trig,LOW);
    t1 = pulseIn(echo,HIGH);
    distance = (t1*0.034)/2;
    Serial.println(distance);
      
      left_ir = digitalRead(2);
      right_ir = digitalRead(3);
      
      if((distance > 1) && (distance < 15)&&(left_ir == LOW)&&(right_ir==LOW)){
         
          digitalWrite(13,HIGH);
          digitalWrite(11,HIGH);
            delay(1000);
       digitalWrite(13,LOW);
        digitalWrite(11,LOW);
        digitalWrite(10,LOW);
        digitalWrite(12,LOW);
      }
    else if(left_ir == HIGH && (distance > 1) && (distance < 15)){
             digitalWrite(13,HIGH);
              delay(1000);
                    digitalWrite(13,LOW);
        digitalWrite(11,LOW);
        digitalWrite(10,LOW);
        digitalWrite(12,LOW);
    }
      else if(right_ir == HIGH&&(distance > 1) && (distance < 15)){
 digitalWrite(11,HIGH);
 delay(1000);
          digitalWrite(13,LOW);
        digitalWrite(11,LOW);
        digitalWrite(10,LOW);
        digitalWrite(12,LOW);
    }
    else{
        digitalWrite(13,LOW);
        digitalWrite(11,LOW);
        digitalWrite(10,LOW);
        digitalWrite(12,LOW);
    }
 }
