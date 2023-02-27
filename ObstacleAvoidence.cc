#include<Servo.h>
#define eye 5
Servo myservo;

char t;
int distance = 0;
int trig = 8;
int echo = 9;
int time = 0;
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
}

void loop() {
    digitalWrite(trig,HIGH);
    delayMicroseconds(10);
    digitalWrite(trig,LOW);
    time = pulseIn(echo,HIGH);
    distance = (time*0.034)/2;
    
    if(Serial.available()){
      t = Serial.read();
      Serial.println(t);

      
      left_ir = digitalRead(2);
      right_ir = digitalRead(3);

    
    if(distance <= 15){
          myservo.attach(7); 
          digitalWrite(13,LOW);
          digitalWrite(11,LOW);
          digitalWrite(10,LOW);
          digitalWrite(12,LOW);
          delay(2000);
          while(true){
              for(pos = 90; pos >=0; pos -= 1){
                  myservo.write(pos);   
                  delay(15);                   
              } 
               digitalWrite(trig,HIGH);
               delayMicroseconds(10);
               digitalWrite(trig,LOW);
               time = pulseIn(echo,HIGH);
               distance = (time*0.034)/2;
              if(!(distance<=15)){
                left_u();
                break;   
              }
              for(pos = 0; pos >= 180; pos+= 1) { 
                 myservo.write(pos);    
                 delay(15);
              }
                  digitalWrite(trig,HIGH);
                  delayMicroseconds(10);
                  digitalWrite(trig,LOW);
                  time = pulseIn(echo,HIGH);
                  distance = (time*0.034)/2;
              if(!(distance<=15)){
                right_u();
                break;  
              }
          }
      }
      else{
            digitalWrite(13,HIGH);
            digitalWrite(11,HIGH);
      }
   }
}
void left_u(){
   digitalWrite(11,HIGH);
   delay(5000);
   digitalWrite(11,LOW);
}
void right_u(){
   digitalWrite(13,HIGH);
   delay(5000);
   digitalWrite(13,LOW);
}
