/*
 * gesture control program for controlling certain functions in windows pc
 * Code by BalaAppu
 * Website: www.electronicshub.org
 */

const int trigPin = 11; // the number of the trigger output pin ( sensor 1 )
const int echoPin = 10; // the number of the echo input pin ( sensor 1 )     

long duration;                               
int distance; 
float r;
////////////////////////////////

void find_distance (void)                   
{ 
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH, 5000);
  r = 3.4 * duration / 2;                  
  distance = r / 100.00;
  delay(50);
}

void setup() 
{
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);
  delay (1000);
    
}

void loop()
{
  distance = 0;
  find_distance(); 
  if(distance <= 25 && distance >= 1){ 
      Serial.write("right");
       Serial.print("\n");
  } 

  delay(250);
}
