// defines pins numbers
#define echo_pin_1 11
#define trig_pin_1 10
#define echo_pin_2 8
#define trig_pin_2 9

#define no_of_ultrasonics 2
#define no_of_motors 2

const int echo_pins[] = {11, 8};
const int trig_pins[] = {10, 9};

const int poles_1[] = {3, 6, 40, 36};
const int poles_2[] = {2, 7, 41, 37};
const int    pwms[] = {12, 13, 5, 4};

// defines variables
long int duration;
int distance;
int speed_1 = 100;
int speed_2 = 100;

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
struct ultrasonic u[no_of_ultrasonics];

struct motor{
    int pole_1;
    int pole_2;
    int pwm;
};

struct motor motors[no_of_motors];

//thresholds
int min_range = 5;
int max_range = 25;
int base_speed = 100;
int scale_speed = 10;

void setup() {
  
    for(int i = 0; i<no_of_ultrasonics; i++){
        u[i].echo_pin = echo_pins[i];
        pinMode(echo_pins[i], INPUT);
        
        u[i].trig_pin = trig_pins[i];
        pinMode(trig_pins[i], OUTPUT);
    }

    for(int i = 0; i<no_of_motors; i++){
        pinMode(motors[i].pole_1, OUTPUT);
        digitalWrite(motors[i].pole_1, LOW);
        
        pinMode(motors[i].pole_2, OUTPUT);
        digitalWrite(motors[i].pole_2, HIGH);
        
        pinMode(motors[i].pwm, OUTPUT);
    }
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
  
    digitalWrite(u.trig_pin, LOW);
    delayMicroseconds(10);
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
  
    int distance_1 = get_distance(u[0]);
    int distance_2 = get_distance(u[1]);
    
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
    int speeds = 254;
    digitalWrite(motors[0].pwm, speeds);
    digitalWrite(motors[1].pwm, speeds);
    digitalWrite(motors[2].pwm, speeds);
    digitalWrite(motors[3].pwm, speeds);
    delay(100);
}
