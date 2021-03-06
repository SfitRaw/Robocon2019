/* 
* Assumptions : 
*      1) Orientation of motors' forward direction is in clockwise direction.
*                
*           FOR PLUS CONFIGURATION :: 
*                ———>
*             _________
*            |         |
*          ^ |         | |
*          | |         | v
*            |         |
*             ‾‾‾‾‾‾‾‾‾
*               <———
*           Arrow indicates the direction of motors' forward direction.
*/


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

#define trig_pin_3 -1
#define echo_pin_3 -1

#define setpoint 100

int forward_speed = 100;

int pwm = 100;
long long int prev_time = 0;
float fraction_inertia = 12/100;

struct two_parameters{
    int first;
    int second;
};

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

Ultrasonic *u1, *u2, *u3;

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
    u3 = new Ultrasonic(trig_pin_3, echo_pin_3);   
}

int calculate(Ultrasonic *u1, Ultrasonic *u2, int r){
/*

  \<————d1———>|        ┃                                     |        |        ┃
   \          |        ┃                                     |        |        ┃
    \         |        ┃                     --->            |<———————|——d————>┃
     \        |        ┃                                     |        |        ┃
      \       |        ┃                                     |        |        ┃
       \<—d2->|        ┃                                     |        |        ┃
*/   
    //For case 1):
    
    int d1 = u1->get_distance()-setpoint;
    int d2 = u2->get_distance()-setpoint;
    int current_time = millis();
    int dt = current_time - prev_time;
    int  s = d1 - d2;
    int theta = s/r;
    int v0 = (theta/dt)*(r);
    
    //For case 2):
    int del_d = d2;
    int v1 = del_d/dt;
    
    return v0+v1;
}

void loop(){
    int distance_1 = u1->get_distance();
    int distance_2 = u2->get_distance();
    int distance_3 = u3->get_distance();
    
    /*


                                     wall to 
                          setpoint    follow                                           setpoint   wall to 
           /\<———————d1——————>|        ┃                            ________________              follow
         /    \               |        ┃                           |              u1|<—d1—>|        ┃
       /        \<—————d2————>|        ┃                           |                |      |        ┃
     /            \           |        ┃     Transformed to        |                |      |        ┃
   /                \<———d3——>|        ┃       ------->            |                |      |        ┃
   \                /         |        ┃                           |              u2|<—d2—>|        ┃
     \            /           |        ┃                           |                |      |        ┃
       \        /             |        ┃                           |                |      |        ┃
         \    /               |        ┃                           |              u3|<—d3—>|        ┃
           \/                 |        ┃                            ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
      Case of variable                                                 
          speeding                                               Same speed for all parallel motors
*/ 
}
