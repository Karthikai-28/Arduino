int hallsensor = A0;                // Hall sensor at pin A0

long counter;

//unsigned long passedtime;

//const float wheeldia = 0.05;

unsigned long int prevmillis;

long startTime = 0;

int state, prevstate = 0;

#define seconds() (millis()*1000)


void setup()

 {Serial.begin(115200);

   //Intiates Serial communications

  // attachInterrupt(0, counter, RISING); //Interrupts are called on Rise of Input

   pinMode(hallsensor, INPUT); //Sets hallsensor as input

   pinMode(5, OUTPUT);

 }
 void loop()
 {


analogread();
kmphmps();
  
  }

//void calibration()
//  {
//float rpm, KMPH, MPS=0;
//   Serial.print("Calibrate the Sensor");
//    if(2 == HIGH){
//      rpm=0;
//      KMPH=0;
//      MPS=0;
//   Serial.print("Please Wait");
//    }else{
//      Serial.print("Please Calibrate the Sensor");
//    }
//  }

//void Reader()
//  {
//   delay(1000);//Update RPM every second
//
//   detachInterrupt(0); //Interrupts are disabled
//
//   passedtime = 0;
//
//   rpm = 60*1000/(millis() - passedtime)*counter;
//
//   prevmillis = millis();
//
//   passedtime = millis()-prevmillis;
//
//   counter = 0;
//
//   Serial.print("RPM = ");
//
//   Serial.println(rpm); //Print out result to monitor
//
//   attachInterrupt(0, counter, RISING);   //Restart the interrupt processing
//  }

void analogread()
{
  hallsensor=0;
  state=0;
  prevstate=0;
  counter=0;
  startTime=millis();

  digitalWrite(hallsensor, HIGH);
  Serial.print("Measuring..");

  while((millis()-startTime)<1000)
  {
    hallsensor=analogRead(0);
    if(hallsensor>700)
    state=1;
    else
    state=0;

    if(state!=prevstate)
    {
      counter++;
      prevstate=state;
    }
  }
 Serial.print("RPM = ");
 Serial.println(counter);
 delay(100);
}

void kmphmps()
{

   float KMPH, MPS, rpm=0;

   float wheel_dia=0.41;

   rpm = counter;   

   MPS = ((3.14*wheel_dia*rpm)/60);

   KMPH = MPS*3.6;

    
    if(KMPH>0.3){
    digitalWrite(5, HIGH);
  }else{
    digitalWrite(5, LOW);
  }

   Serial.print("MPS = ");

   Serial.println(MPS);

   Serial.print("KMPH = ");

   Serial.println(KMPH);
}
