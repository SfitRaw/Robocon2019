#define PWM1 3
#define PWM2 6
#define PWM3 7
#define PWM4 9

#define M1P1 51
#define M1P2 50
#define M2P1 11
#define M2P2 8
#define M3P1 23
#define M3P2 22
#define M4P1 39
#define M4P2 38


class Motor{
    int pwm;
    int pole_1, pole_2;
    public:
    
    Motor(int c_pole_1, int c_pole_2, int c_pwm){            //c stands for constructor.
        pole_1 = c_pole_1;
        pole_2 = c_pole_2;
        c_pwm = pwm;
    }
    
    void setup_motor(){
        pinMode(pole_1, OUTPUT);
        pinMode(pole_2, OUTPUT);
        pinMode(pwm, OUTPUT);
    }

    void forward(int speed){
        digitalWrite(pole_1, HIGH);
        digitalWrite(pole_2, LOW);
        analogWrite(pwm, speed);
    }

    void backward(int speed){
        digitalWrite(pole_1, LOW);
        digitalWrite(pole_2, HIGH);      
        analogWrite(pwm, speed);
    }

    void freeze(){
        digitalWrite(pwm, 0);
    }
};

Motor *motor_1;
Motor *motor_2;
Motor *motor_3;
Motor *motor_4;

void forward();
void backward();
void right();
void left();

void setup(){
   
  Serial.begin(9600);
    
    motor_1 = new Motor(M1P1, M1P2, PWM1);
    motor_2 = new Motor(M2P1, M2P2, PWM2);
    motor_3 = new Motor(M3P1, M3P2, PWM3);
    motor_4 = new Motor(M4P1, M4P2, PWM4);
    
    motor_1->setup_motor();
    motor_2->setup_motor();
    motor_3->setup_motor();
    motor_4->setup_motor();
}

void forward(){
   motor_1->forward(100);
   motor_2->freeze();
   motor_3->forward(100);
   motor_4->freeze();
}

void backward(){
   motor_1->backward(100);
   motor_2->freeze();
   motor_3->backward(100);
   motor_4->freeze();
}

void right(){
    motor_1->freeze();
    motor_2->forward(100);
    motor_3->freeze();
    motor_4->forward(100);
}

void left(){
    motor_1->freeze();
    motor_2->backward(100);
    motor_3->freeze();
    motor_4->backward(100);
}

void loop(){
    forward();
    right();
    backward();
    left();  
}
