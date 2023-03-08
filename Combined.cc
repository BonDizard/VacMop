#include<Servo.h>
Servo myservo;

int  left_ir;
int right_ir;
char t;
int distance = 0;
int trig = 8;
int echo = 9;
int time = 0;

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
      distance = getDistance();
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
              for(pos = 0; pos <=90; pos += 1){
                  myservo.write(pos);   
                  delay(15);                   
              } 
              distance = getDistance();
                
              if(!(distance<=15)){
                delay(2000);
                left_u();
                break;   
              }
              delay(5000);
              for(pos = 90; pos <= 180; pos+= 1) { 
                 myservo.write(pos);    
                 delay(1000);
              }
              distance = getDistance();
              if(!(distance<=15)){
                delay(2000);
                right_u();
                break;  
              }
              delay(5000);
              else{
                 digitalWrite(13,LOW);
                 digitalWrite(11,LOW);
                 digitalWrite(10,LOW);
                 digitalWrite(12,LOW);
              }
          }
      }
      else{
            digitalWrite(13,HIGH);
            digitalWrite(11,HIGH);
      }

      if(Serial.available()){
      t = Serial.read();
      Serial.println(t);
      if(t=='B'){
         Bluetooth(); 
      }
      else if(t=='G'){
        Guesture();
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
void Bluetooth(){
    t=Serial.read();
        if(t == 'F'){                 //Forward
            digitalWrite(13,HIGH);
            digitalWrite(11,HIGH);
           }
      else if(t == 'R'){              //Reverse
            digitalWrite(12,HIGH);
            digitalWrite(10,HIGH);
          } 
      else if(t == 'L'){              //Left
            digitalWrite(11,HIGH);
          } 
      else   if(t == 'D'){            //Right
              digitalWrite(13,HIGH);
          }
      else if(t == 'S'){              //Break
              digitalWrite(13,LOW);
              digitalWrite(12,LOW);
              digitalWrite(11,LOW);
              digitalWrite(10,LOW);
          }
}

void Guesture() {
    distance = getDistance();
    Serial.println(distance);
      
    left_ir = digitalRead(2);
    right_ir = digitalRead(3);
      
    if((distance >= 5) && (distance <= 15)&&(left_ir == LOW)&&(right_ir==LOW)){ 
        digitalWrite(13,HIGH);
        digitalWrite(11,HIGH);
        delay(500);
        digitalWrite(13,LOW);
        digitalWrite(11,LOW);
        digitalWrite(10,LOW);
        digitalWrite(12,LOW);
      }
    else if(left_ir == HIGH && (distance >= 5) && (distance <= 15)){
        digitalWrite(13,HIGH);
        delay(500);
        digitalWrite(13,LOW);
        digitalWrite(11,LOW);
        digitalWrite(10,LOW);
        digitalWrite(12,LOW);
    }
    else if(right_ir == HIGH&&(distance >= 5) && (distance <= 15)){
        digitalWrite(11,HIGH);
        delay(500);
        digitalWrite(13,LOW);
        digitalWrite(11,LOW);
        digitalWrite(10,LOW);
        digitalWrite(12,LOW);
    }
    else if((distance >0) && (distance < 5)){
        digitalWrite(12,HIGH);
        digitalWrite(10,HIGH);
        delay(500);
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

int getDistance(){
    digitalWrite(trig,HIGH);
    delayMicroseconds(10);
    digitalWrite(trig,LOW);
    time = pulseIn(echo,HIGH);
    distance = (time*0.034)/2;
    Serial.println(distance);
    return distance;
}
