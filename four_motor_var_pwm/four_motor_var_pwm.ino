
/*-------------------------------------------------------------------------------------------------------------------------------------
triangle = motor 1 ---north 
cross    = motor 3 ---south
circle   = motor 2 ---east
square   = motor 4 ---west

press and hold any shape button and RIGHT_1  to increment pwm (of the motor decided by the shape eg for incrementing pwm of motor1 use triangle)by a user defined factor
press and hold any shape button and LEFT_1  to decrement pwm (of the motor decided by the shape eg for decrementing pwm of motor1 use triangle)by a user defined factor

BUTTON- n - FUNCTION
UP      1   forward    motor 2,4
DOWN    2   reverse 
LEFT    3   left       motor 1,3
RIGHT   4   right
START   5   halt    -stop all the motors

serial monitor display pwm value and value of n (deciding the function in switch case) 

 ------------------------------------------------------------------------------------------------------------------------------------------*/


#include<SoftwareSerial.h>
#include<Cytron_PS2Shield.h>
Cytron_PS2Shield ps2(10,11);

int m1_dir = 2;  
int m2_dir = 3;
int m3_dir = 4;
int m4_dir = 5;

int m1_pwm = 6;
int m2_pwm = 7;
int m3_pwm = 8;
int m4_pwm = 9;

int pwm1 = 0;
int pwm2 = 0;
int pwm3 = 0;
int pwm4 = 0;

int pwm = 0;
int n= 0;           //switching var for different fuctions
int factor = 25;    //increment factor
int flag = 0;       //used in debouncing
int prev = 1;       //used in debouncing
int current = 0;    //used in debouncing

void setup(){
  Serial.begin(9600);
  ps2.begin(9600);

  pinMode(m1_dir, OUTPUT);
  pinMode(m2_dir, OUTPUT);
  pinMode(m3_dir, OUTPUT);
  pinMode(m4_dir, OUTPUT);
  
  pinMode(m1_pwm, OUTPUT);
  pinMode(m2_pwm, OUTPUT);
  pinMode(m3_pwm, OUTPUT);
  pinMode(m4_pwm, OUTPUT);
  
}

void forward(){
  digitalWrite(m2_dir , HIGH);
  analogWrite(m2_pwm, pwm2);
  digitalWrite(m4_dir , HIGH);
  analogWrite(m4_pwm, pwm4);
}

void reverse(){
  digitalWrite(m2_dir , LOW);
  analogWrite(m2_pwm, pwm2);
  digitalWrite(m4_dir , LOW);
  analogWrite(m4_pwm, pwm4);
}

void right(){
  digitalWrite(m1_dir , HIGH);
  analogWrite(m1_pwm, pwm1);
  digitalWrite(m3_dir , HIGH);
  analogWrite(m3_pwm, pwm3);
}

void left(){
  digitalWrite(m1_dir , LOW);
  analogWrite(m1_pwm, pwm1);
  digitalWrite(m3_dir , LOW);
  analogWrite(m3_pwm, pwm3);
}

void halt(){
  analogWrite(m1_pwm, 0);
  analogWrite(m2_pwm, 0);
  analogWrite(m3_pwm, 0);
  analogWrite(m4_pwm, 0);
}

void debounce(){                           //incrementing pwm
  
  current = ps2.readButton(PS2_RIGHT_1);
    if(current != prev){
      prev = current;
      delay(100);
      if(ps2.readButton(PS2_RIGHT_1)==0){
        flag= 1;
      }
      else flag = 0;
    }
    if(flag){
    pwm =  constrain(pwm +factor,0, 225);
      flag = 0;
    }
  
}
 void debounce2(){                           //decrementing pwm
    current = ps2.readButton(PS2_LEFT_1);
    if(current != prev){
      prev = current;
      delay(100);
      if(ps2.readButton(PS2_LEFT_1)==0){
        flag= 1;
      }
      else flag = 0;
    }
    if(flag){
      pwm =  constrain(pwm -factor,0, 225);
      flag = 0;
    }
  
}

void loop(){
  
  if(ps2.readButton(PS2_TRIANGLE)==0){
   debounce();
   debounce2();
   pwm1 = pwm;
   }  

  if(ps2.readButton(PS2_CIRCLE)==0){
   debounce();
   debounce2();
   pwm2 = pwm;
   }

    if(ps2.readButton(PS2_CROSS)==0){
   debounce();
   debounce2();
   pwm3 = pwm;
   }

   if(ps2.readButton(PS2_SQUARE)==0){
   debounce();
   debounce2();
   pwm4 = pwm;
   }
  
  Serial.println(pwm);
  delay(10);
  Serial.println(n);
  delay(10);
  if(ps2.readButton(PS2_UP)==0)
 {
  n=1;
 }
 else  if(ps2.readButton(PS2_DOWN)==0)
 {
  n=2;
 }
 else  if(ps2.readButton(PS2_LEFT)==0)
 {
  n=3;
 }
 else  if(ps2.readButton(PS2_RIGHT)==0)
 {
  n=4;
 }
 else  if(ps2.readButton(PS2_START)==0)
 {
  n=5;
 }
 switch(n){
  case 1: forward();
  break;
  case 2: reverse();
  break;
  case 3: left();
  break;
  case 4: right();
  break;
  case 5: halt();
  break;
 }
}
