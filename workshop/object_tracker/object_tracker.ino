// defines pins numbers
#define echo_pin_1 11
#define trig_pin_1 10
#define echo_pin_2 8
#define trig_pin_2 9

#define m1p1 2
#define m1p2 3
#define pwm1 12
int speed_1 = 100;

#define m2p1 6
#define m2p2 7
#define pwm2 13
int speed_2 = 100;

#define m3p1 40
#define m3p2 41
#define pwm3 45

#define m4p1 36
#define m4p2 37
#define pwm4 44

// defines variables
long int duration;
int distance;

//setting up cutoffs :
#define cut_low 0
#define cut_high 1000
#define no_obstacle_low 1001
#define no_obstacle_high 15000
#define something_blocked_low 15001

//setting up ultrasonic:
struct ultrasonic{
  int trig_pin;
  int echo_pin;
};
struct ultrasonic u[4];

//thresholds
int min_range = 5
int max_range = 25;
int base_speed = 100;
int scale_speed = 10;
void setup() {
    
    u1.echo_pin = echo_pin_1;
    u1.trig_pin = trig_pin_1;
    
    u2.echo_pin = echo_pin_2;
    u2.trig_pin = trig_pin_2;
    
    pinMode(u1.trig_pin, OUTPUT);
    pinMode(u1.echo_pin, INPUT);

    pinMode(u2.trig_pin, OUTPUT);
    pinMode(u2.echo_pin, INPUT);
    
    
    pinMode(m1p1, OUTPUT);
    pinMode(m1p2, OUTPUT);
    pinMode(pwm1, OUTPUT);
    
    pinMode(m2p1, OUTPUT);
    pinMode(m2p2, OUTPUT);
    pinMode(pwm2, OUTPUT);
    
    pinMode(m3p1, OUTPUT);
    pinMode(m3p2, OUTPUT);
    pinMode(pwm3, OUTPUT);
    
    pinMode(m4p1, OUTPUT);
    pinMode(m4p2, OUTPUT);
    pinMode(pwm4, OUTPUT);
    
    digitalWrite(m1p1, HIGH);
    digitalWrite(m1p2, LOW);
    
    digitalWrite(m2p1, LOW);
    digitalWrite(m2p2, HIGH);
    
    digitalWrite(m3p1, LOW);
    digitalWrite(m3p2, HIGH);
    
    digitalWrite(m4p1, LOW);
    digitalWrite(m4p2, HIGH);
    
    Serial.begin(9600); // Starts the serial communication
}


boolean in_between(long int val, long int low, long int high){
  if(val>=low && val<high){
    return true;
  }
  else{
    return false;
  }
}

int get_distance(struct ultrasonic u){
    // Clears the trigPin
    digitalWrite(u.trig_pin, LOW);
    delayMicroseconds(10);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(u.trig_pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(u.trig_pin, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(u.echo_pin, HIGH, 50000);
    // Calculating the distance
    distance = duration*0.034/2;
    return distance;
}

boolean in_range(int value, int low, int high){
  if(value>low && value<=high){
    return true;
  }
  return false;
}

void loop() {
  
    int distance_1 = get_distance(u1);
    int distance_2 = get_distance(u2);
    
    Serial.println(distance_1);
    Serial.println(distance_2);
    
    if(in_range(distance_1, min_range, max_range) && in_range(distance_2, min_range, max_range)){
        speed_1 = base_speed + scale_speed*distance_1/(distance_1+distance_2+1); 
        speed_2 = base_speed + scale_speed*distance_2/(distance_1+distance_2+1);
    }
    else if(in_range(distance_2, min_range, max_range)){
        speed_2 = base_speed;
        speed_1 = 0;
    }
    else if(in_range(distance_1, min_range, max_range)){
        speed_2 = 0;
        speed_1 = base_speed;
    }
    else{
        speed_1 = 0;
        speed_2 = 0;
    }
    Serial.print("Speed 1 = ");
    Serial.print(speed_1);
    Serial.println();
    Serial.print("Speed 2 = ");
    Serial.print(speed_2);
    Serial.println();
    digitalWrite(pwm1, speed_1);
    digitalWrite(pwm2, speed_2);
    digitalWrite(pwm3, speed_1);
    digitalWrite(pwm4, speed_2);
//    delay(100);
}
