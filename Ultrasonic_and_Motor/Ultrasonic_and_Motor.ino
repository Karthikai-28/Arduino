#define fronttrigPin1 8
#define frontechoPin1 9
#define righttrigPin2 10
#define rightechoPin2 9
#define lefttrigPin3 8
#define leftechoPin3 7
#define reartrigPin4 4
#define rearechoPin4 2
#define lmt1 3
#define lmt2 5
#define rmt1 11
#define rmt2 6

void setup() {
  Serial.begin (9600);
  pinMode(fronttrigPin1, OUTPUT);
  pinMode(frontechoPin1, INPUT);
  pinMode(righttrigPin2, OUTPUT);
  pinMode(rightechoPin2, INPUT);
  pinMode(lefttrigPin3, OUTPUT);
  pinMode(leftechoPin3, INPUT);
  pinMode(reartrigPin4, OUTPUT);
  pinMode(rearechoPin4, INPUT);
  pinMode(lmt1, OUTPUT);
  pinMode(lmt2, OUTPUT);
  pinMode(rmt1, OUTPUT);
  pinMode(rmt2, OUTPUT);
  
}
  
void loop () {
   int movement = 0;
   int duration, distance;
   digitalWrite (fronttrigPin1, HIGH);
   delayMicroseconds (10);
   digitalWrite (fronttrigPin1, LOW);
   duration = pulseIn (frontechoPin1, HIGH);
   distance = (duration/2) / 29.1;
   Serial.print(distance);
   if (distance < 10) { 
    forward();
   
}
  else{
    reverse();
    
  }
    
}

   digitalWrite (righttrigPin2, HIGH);
   delayMicroseconds (10);
   digitalWrite (righttrigPin2, LOW);
   duration = pulseIn (rightechoPin2, HIGH);
   distance = (duration/2) / 29.1;
   if (distance < 10) {
    left();
    
   }

   digitalWrite (lefttrigPin3, HIGH);
   delayMicroseconds (10);
   digitalWrite (lefttrigPin3, LOW);
   duration = pulseIn (leftechoPin3, HIGH);
   distance = (duration/2) / 29.1;
   if (distance < 10) {
    right();
    
   }

   digitalWrite (lefttrigPin3, HIGH);
   delayMicroseconds (10);
   digitalWrite (lefttrigPin3, LOW);
   duration = pulseIn (leftechoPin3, HIGH);
   digitalWrite (fronttrigPin1, HIGH);
   delayMicroseconds (10);
   digitalWrite (fronttrigPin1, LOW);
   duration = pulseIn (frontechoPin1, HIGH);
   digitalWrite (righttrigPin2, HIGH);
   delayMicroseconds (10);
   digitalWrite (righttrigPin2, LOW);
   duration = pulseIn (rightechoPin2, HIGH);
   distance = (duration/2) / 29.1;
   if (distance < 10){
    stp();
   }
   
  
   if  (distance > 10) {  
    Serial.println("Out of range");
  }
  else {
    Serial.print(distance);
    Serial.println(" cm");
  }
}

void forward()
{
  
  digitalWrite(lmt1, HIGH);
  digitalWrite(lmt2, LOW);
  digitalWrite(rmt1, HIGH);
  digitalWrite(rmt2, LOW);
}
void reverse()
{
  digitalWrite(lmt1, LOW);
  digitalWrite(lmt2, HIGH);
  digitalWrite(rmt1, LOW);
  digitalWrite(rmt2, HIGH);
}
void left()
{
  
  digitalWrite(lmt1, LOW);
  digitalWrite(lmt2, HIGH);
  digitalWrite(rmt1, HIGH);
  digitalWrite(rmt2, LOW);
}
void right()
{
 
  digitalWrite(lmt1, HIGH);
  digitalWrite(lmt2, LOW);
  digitalWrite(rmt1, LOW);
  digitalWrite(rmt2, HIGH);
}
void stp()
{
  digitalWrite(lmt1, LOW);
  digitalWrite(lmt2, LOW);
  digitalWrite(rmt1, LOW);
  digitalWrite(rmt2, LOW);
}
void stpleft()
{
  
  digitalWrite(lmt1, LOW);
  digitalWrite(lmt2, LOW);
  digitalWrite(rmt1, HIGH);
  digitalWrite(rmt2, LOW);
}
void stpright()
{
  
  digitalWrite(lmt1, HIGH);
  digitalWrite(lmt2, LOW);
  digitalWrite(rmt1, LOW);
  digitalWrite(rmt2, LOW);
}
