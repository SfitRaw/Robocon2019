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

#define trig_pin_1 -1
#define echo_pin_1 -1

#define trig_pin_2 -1
#define echo_pin_2 -1



int pwm = 100;

class Motor{
    int pwm;
    int pole_1, pole_2;
    public:
    
    Motor(int c_pole_1, int c_pole_2, int c_pwm){            //c stands for constructor.
        pole_1 = c_pole_1;
        pole_2 = c_pole_2;
        c_pwm = pwm;
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

class Ultrasonic{
    int trig_pin;
    int echo_pin;
    public:
        
        Ultrasonic(int c_trig_pin, int c_echo_pin){
            trig_pin = c_trig_pin;
            echo_pin = c_echo_pin;
            pinMode(trig_pin, OUTPUT); // Sets the trigPin as an Output
            pinMode(echo_pin, INPUT); // Sets the echoPin as an Input
        }
        
        int get_distance(){
            // Clears the trigPin
            digitalWrite(trig_pin, LOW);
            delayMicroseconds(2);
            // Sets the trigPin on HIGH state for 10 micro seconds
            digitalWrite(trig_pin, HIGH);
            delayMicroseconds(10);
            digitalWrite(trig_pin, LOW);
            // Reads the echoPin, returns the sound wave travel time in microseconds
            long int duration = pulseIn(echo_pin, HIGH, 5000);
            // Calculating the distance
            int distance= duration*0.034/2;
            return distance;
        }
};

Ultrasonic *u1, *u2;

Motor *motor_1;
Motor *motor_2;
Motor *motor_3;
Motor *motor_4;

void setup(){
   
  Serial.begin(9600);
    
    motor_1 = new Motor(M1P1, M1P2, PWM1);
    motor_2 = new Motor(M2P1, M2P2, PWM2);
    motor_3 = new Motor(M3P1, M3P2, PWM3);
    motor_4 = new Motor(M4P1, M4P2, PWM4);
    
    u1 = new Ultrasonic(trig_pin_1, echo_pin_1);
    u2 = new Ultrasonic(trig_pin_2, echo_pin_2);
}

void loop(){
    delay(1000);  
}
