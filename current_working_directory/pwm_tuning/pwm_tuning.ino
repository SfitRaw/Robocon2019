#include <Cytron_PS2Shield.h>
#include<SoftwareSerial.h>
Cytron_PS2Shield remote(10,11);
#define dir_1 2
#define pwm_1 3
#define dir_2 4
#define pwm_2 5
#define dir_3 6
#define pwm_3 7
#define dir_4 8
#define pwm_4 9

void setup() {
    Serial.begin(9600);
    pinMode(dir_1, OUTPUT);
    pinMode(dir_2, OUTPUT);
    pinMode(dir_3, OUTPUT);
    pinMode(dir_4, OUTPUT);
    
    pinMode(pwm_1, OUTPUT);
    pinMode(pwm_2, OUTPUT);
    pinMode(pwm_3, OUTPUT);
    pinMode(pwm_4, OUTPUT);
    pinMode(13, OUTPUT);
  remote.begin(9600);

}
int speed_1 = 100;
int speed_2 = 100;
int speed_3 = 100;
int speed_4 = 100;

int factor = 10;

void forward(){
    digitalWrite(dir_1, LOW);
    digitalWrite(dir_3, HIGH);
    
    analogWrite(pwm_1, speed_1);
    analogWrite(pwm_3, speed_3);
    analogWrite(pwm_2, 0);
    analogWrite(pwm_4, 0);
}
void backward(){
    digitalWrite(dir_1, HIGH);
    digitalWrite(dir_3, LOW);
    
    analogWrite(pwm_1, speed_1);
    analogWrite(pwm_3, speed_3);
    analogWrite(pwm_2, 0);
    analogWrite(pwm_4, 0);
}
void left(){
    digitalWrite(dir_2, LOW);
    digitalWrite(dir_4, LOW);
    
    analogWrite(pwm_2, speed_2);
    analogWrite(pwm_4, speed_4);
    analogWrite(pwm_1, 0);
    analogWrite(pwm_3, 0);
}
void right(){
    digitalWrite(dir_2, HIGH);
    digitalWrite(dir_4, HIGH);
    
    analogWrite(pwm_2, speed_2);
    analogWrite(pwm_4, speed_4);
    analogWrite(pwm_1, 0);
    analogWrite(pwm_3, 0);
}
void  freeze(){
    analogWrite(pwm_1, 0);
    analogWrite(pwm_3, 0);
    analogWrite(pwm_2, 0);
    analogWrite(pwm_4, 0);
}
void loop() {
   if(remote.readButton(PS2_TRIANGLE)){
       if(remote.readButton(PS2_RIGHT_1)){
           speed_1 -= factor;
       }
       else{
           if(remote.readButton(PS2_RIGHT_2)){
               speed_1 += factor;
           }
       }
   }
   else if(remote.readButton(PS2_CIRCLE)){
       if(remote.readButton(PS2_RIGHT_1)){
           speed_2 -= factor;
       }
       else{
           if(remote.readButton(PS2_RIGHT_2)){
               speed_2 += factor;
           }
       }
   }
   else if(remote.readButton(PS2_CROSS)){
       if(remote.readButton(PS2_RIGHT_1)){
           speed_3 -= factor;
       }
       else{
           if(remote.readButton(PS2_RIGHT_2)){
               speed_3 += factor;
           }
       }
   }
   else if(remote.readButton(PS2_SQUARE)){
       if(remote.readButton(PS2_RIGHT_1)){
           speed_4 -= factor;
       }
       else{
           if(remote.readButton(PS2_RIGHT_2)){
               speed_4 += factor;
           }
       }
   }
   
   if(remote.readButton(PS2_LEFT)){
       left();
   }
   else if(remote.readButton(PS2_RIGHT)){
       right();
   }
   else if(remote.readButton(PS2_UP)){
       forward();
   }
   else if(remote.readButton(PS2_DOWN)){
       backward();
   }
   else{
      freeze();
   }
}
