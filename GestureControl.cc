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
      right_ir = digitalRead…
[1:53 pm, 25/02/2023] BonD: Obstacle avoidence
[1:54 pm, 25/02/2023] BonD: #include<Servo.h>
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
      
      if((distance > 1) && (distance < 15)){
          myservo.attach(7); 
          digitalWrite(13,HIGH);
          digitalWrite(11,HIGH);
          
          if(left_ir == LOW){
            digitalWrite(11,HIGH);
          }
          else if(right_ir==LOW){
            digitalWrite(13,HIGH);
        }
     }
    else{
        digitalWrite(13,LOW);
        digitalWrite(11,LOW);
        digitalWrite(10,LOW);
        digitalWrite(12,LOW);
    }
  }
}
