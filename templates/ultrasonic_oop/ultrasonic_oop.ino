// defines pins numbers
int echo_pin = 10;
int trig_pin = 9;
// defines variables
long duration;
int distance;

class Ultrasonic{
    int trig_pin;
    int echo_pin;
    public:
        
        Ultrasonic(int c_trig_pin, int c_echo_pin){
            trig_pin = c_trig_pin;
            echo_pin = c_echo_pin;
        }
        void setup_ultrasonic(){
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
            duration = pulseIn(echo_pin, HIGH, 5000);
            // Calculating the distance
            int distance= duration*0.034/2;
            return distance;
        }
};

Ultrasonic *u;

void setup() {
    u = new Ultrasonic(trig_pin, echo_pin);
    u->setup_ultrasonic();
    Serial.begin(9600); // Starts the serial communication
}

// A utility function : 
boolean in_between(long int val, long int low, long int high){
  return (val>=low && val<high)?true:false;
}

void loop() {
    Serial.println(u->get_distance());
}
