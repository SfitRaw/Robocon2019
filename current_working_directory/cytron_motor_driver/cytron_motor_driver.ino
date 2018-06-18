#define dir_1 2
#define pwm_1 3
#define dir_2 4
#define pwm_2 5
#define dir_3 6
#define pwm_3 7
#define dir_4 8
#define pwm_4 9

void setup(){
    pinMode(dir_1, OUTPUT);
    pinMode(dir_2, OUTPUT);
    pinMode(dir_3, OUTPUT);
    pinMode(dir_4, OUTPUT);
    
    pinMode(pwm_1, OUTPUT);
    pinMode(pwm_2, OUTPUT);
    pinMode(pwm_3, OUTPUT);
    pinMode(pwm_4, OUTPUT);
    pinMode(13, OUTPUT);
}
void forward(int  speed_1, int  speed_2){
    digitalWrite(dir_1, LOW);
    digitalWrite(dir_3, HIGH);
    
    analogWrite(pwm_1, speed_1);
    analogWrite(pwm_3, speed_2);
    analogWrite(pwm_2, 0);
    analogWrite(pwm_4, 0);
}
void backward(int  speed_1, int  speed_2){
    digitalWrite(dir_1, HIGH);
    digitalWrite(dir_3, LOW);
    
    analogWrite(pwm_1, speed_1);
    analogWrite(pwm_3, speed_2);
    analogWrite(pwm_2, 0);
    analogWrite(pwm_4, 0);
}
void left(int  speed_1, int  speed_2){
    digitalWrite(dir_2, LOW);
    digitalWrite(dir_4, LOW);
    
    analogWrite(pwm_2, speed_1);
    analogWrite(pwm_4, speed_2);
    analogWrite(pwm_1, 0);
    analogWrite(pwm_3, 0);
}
void right(int  speed_1, int  speed_2){
    digitalWrite(dir_2, HIGH);
    digitalWrite(dir_4, HIGH);
    
    analogWrite(pwm_2, speed_1);
    analogWrite(pwm_4, speed_2);
    analogWrite(pwm_1, 0);
    analogWrite(pwm_3, 0);
}
void  freeze(){
    analogWrite(pwm_1, 0);
    analogWrite(pwm_3, 0);
    analogWrite(pwm_2, 0);
    analogWrite(pwm_4, 0);
}
int s = 100;
void loop(){
    forward();
    delay(5000);
    right();
    delay(5000);
    backward();
    delay();
    left();
    delay(5000);
}
