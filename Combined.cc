#include<Servo.h>

Servo myservo;

int left_ir;
int right_ir;
char t;
int distance = 0;
int trig = 8;
int echo = 9;
int time = 0;
int t1;
int pos;
int x;

void setup() {

  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(2, INPUT); //left ir
  pinMode(3, INPUT); //RIGHT IR
  pinMode(trig, OUTPUT); //ULTRA SONIC
  pinMode(echo, INPUT);
turnFront();
      }

void loop() {
  if (Serial.available()) {
    while(true){
    t = Serial.read();
    Serial.println(t);
    if (t == 'F') {
      digitalWrite(13, HIGH);
      digitalWrite(11, HIGH);
    } else if (t == 'B') {
      digitalWrite(12, HIGH);
      digitalWrite(10, HIGH);
    } else if (t == 'L') {
      digitalWrite(11, HIGH);
    } else if (t == 'R') {
      digitalWrite(13, HIGH);
    } else if (t == 'S') {
      digitalWrite(13, LOW);
      digitalWrite(12, LOW);
      digitalWrite(11, LOW);
      digitalWrite(10, LOW);
    } 
    else if(t=='U'){
      break;
    }
    else if (t == 'W') { //Gesture
      distance = getDistance();
      left_ir = digitalRead(2);
      right_ir = digitalRead(3);
      if ((distance >= 5) && (distance <= 15) && (left_ir == LOW) && (right_ir == LOW)) {
        forward(1000);
        delay(500);
        stopWheels();
      } else if (left_ir == HIGH && (distance >= 5) && (distance <= 15)) {
        right(1000);
        delay(500);
        stopWheels();
      } else if (right_ir == HIGH && (distance >= 5) && (distance <= 15)) {
        left(1000);
        delay(500);
        stopWheels();
      } else if ((distance > 0) && (distance < 5)) {
        reverse(1000);
        delay(500);
        stopWheels();
      } else {
       stopWheels(); 
      }
    }
    }
  }  else if (!Serial.available()){
    autoPi();
  }
}
 void turnFront(){
        myservo.attach(7);
      for (pos = 0; pos >= 90; pos += 1) {
        myservo.write(pos);
        delay(15);
      }
  }
void stopWheels() {
  digitalWrite(13, LOW);
  digitalWrite(11, LOW);
  digitalWrite(10, LOW);
  digitalWrite(12, LOW);
}
void forward(int x) {
  digitalWrite(13, HIGH);
  digitalWrite(12, LOW);
  digitalWrite(11, HIGH);
  digitalWrite(10, LOW);
  delay(x);
}
void reverse(int x) {
  digitalWrite(10, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(11, LOW);
  digitalWrite(13, LOW);
  delay(x);
}

void left(int x) {
  digitalWrite(11, HIGH);
  digitalWrite(13, LOW);
  digitalWrite(12, LOW);
  digitalWrite(10, LOW);
  delay(2000);
}
void right(int x) {
  digitalWrite(13, HIGH);
  digitalWrite(12, LOW);
  digitalWrite(11, LOW);
  digitalWrite(10, LOW);
  delay(x);
}
void left_u() {
  digitalWrite(11, HIGH);
  delay(5000);
  digitalWrite(11, LOW);
}
void right_u() {
  digitalWrite(13, HIGH);
  delay(5000);
  digitalWrite(13, LOW);
}

int getDistance() {
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  time = pulseIn(echo, HIGH);
  distance = (time * 0.034) / 2;
  Serial.println(distance);
  return distance;
}

void autoPi() {
  for (pos = 0; pos >= 90; pos += 1) {
        myservo.write(pos);
        delay(15);
      }
  distance = getDistance();
  if (distance <= 15) {
    myservo.attach(7);
    stopWheels();
    delay(1000);
    while (true) {
      for (pos = 90; pos >= 0; pos -= 1) {
        myservo.write(pos);
        delay(15);
      }
      delay(2000);
      distance = getDistance();
      if (!(distance <= 15)) {
        left_u();
      for (pos = 0; pos <= 90; pos += 1) {
        myservo.write(pos);
        delay(15);
      }
        break;
      } 
      else {
        for (pos = 90; pos <= 180; pos += 1) {
          myservo.write(pos);
          delay(15);
        }
                delay(2000);
        distance = getDistance();
        if (!(distance <= 15)) {
          right_u();
          for (pos = 180; pos >= 90; pos -= 1) {
          myservo.write(pos);
          delay(15);
        }
          break;
        } else {
          stopWheels();
        }
      }
    }
  } else {
    forward(1000);
  }
}
