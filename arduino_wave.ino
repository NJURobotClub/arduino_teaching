const int trigPin = 11; // the number of the trigger output pin
const int echoPin = 10; // the number of the echo input pin
////////////////////////////////// variables used for distance calculation 
long duration;                               
int distance; 
float r;
////////////////////////////////

// this function returns the value in cm.
void find_distance (void)                   
{ 
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH, 5000);
  r = 3.4 * duration / 2;                  // calculation to get the measurement in cm using the time returned by the pulsein function.     
  distance = r / 100.00;
  delay(50);
}

void setup() 
{
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT); // initialize the trigger and echo pins of both the sensor as input and output:
  pinMode(echoPin, INPUT);
  delay (1000);
    
}

void loop()
{
  distance = 0;
  find_distance(); // this function will stores the current distance measured by the ultrasonic sensor in the global variable "distance1 and distance2"

  Serial.print(distance);
  Serial.print("\n");

  delay(250);
}
