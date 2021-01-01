/* Sensor 
  VCC - A1
  GND - GND
  O/P - A0 */

long startTime = 0;
int state, prevState = 0;
int sensor = 0;
long counter = 0;
float wheel_dia= 0.41;
int sw = 5;
int i = 0 ;
void setup()
{
  Serial.begin(9600);
  pinMode(A1,OUTPUT);
  pinMode(sw, OUTPUT);
}

void loop()
{
  //reset variables.
  sensor = 0;
  state = 0;
  prevState = 0;
  counter = 0;

  float mps, kmph, rpm=0;
  
  startTime = millis();
  
  //enable sensor and turn on LED
  digitalWrite(A1, HIGH);
  Serial.write(12);
  Serial.print("\nMeasuring...\n");

  //Loop for sample duration of 1 second
  while((millis() - startTime) < (10000/2))
  {
    sensor =  analogRead(0);
    if (sensor > 700)
      state = 1;
    else
      state = 0;
    
    //On change of state increment counter.
    //A change in state twice represents one revolution
    if(state != prevState)
    {
      counter=0;
      counter++;
      prevState = state;
    }
  }

    rpm = counter; 
    mps = ((3.14 * wheel_dia * counter) / 60);
    kmph = mps * 3.6;

  //Turn off Sensor and LED
  digitalWrite(A1, LOW);
  i++;
  Serial.print("\n");
  Serial.print(i); Serial.print(" second");
  
  Serial.print("\nRPM = "); 
  Serial.print(rpm);

  Serial.print("\nMps = "); 
  Serial.print(mps);

  Serial.print("\nKmph = "); 
  Serial.print(kmph);

  if(kmph > 0.1)
    digitalWrite(sw, HIGH);
  else
    digitalWrite(sw, LOW);
}
