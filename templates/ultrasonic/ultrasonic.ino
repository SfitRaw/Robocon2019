// defines pins numbers
#define echo_pin 10
#define trig_pin 9
// defines variables
long duration;
int distance;

void setup() {
    pinMode(trig_pin, OUTPUT); // Sets the trigPin as an Output
    pinMode(echo_pin, INPUT); // Sets the echoPin as an Input
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
    distance= duration*0.034/2;
}
void loop() {
    Serial.println(get_distance());
}
