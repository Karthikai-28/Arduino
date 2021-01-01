//#include <LiquidCrystal.h>
//LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
int sensor = 3;
unsigned long start_time = 0;
unsigned long end_time = 0;
int steps=0;
float steps_old=0;
float temp=0;
float rpm=0;
volatile byte pulses=0;

void setup() 
{
  Serial.begin(9600);
  //lcd.begin(16, 2);
  pinMode(sensor,INPUT_PULLUP);
  //lcd.setCursor(0,0);
  Serial.println(" STEPS - 0");
  //lcd.setCursor(0,1);
  Serial.print(" RPS   - 0.00");
  pulses=0;
  rpm=0;
  steps_old=0;
  
}
 
void loop()
{
 start_time=millis();
 end_time=start_time+1000;
 while(millis()<end_time)
 {
   if(digitalRead(sensor))
   {
    steps=steps+1; 
    while(digitalRead(sensor));
   }
   //lcd.setCursor(9,0);
   Serial.print("The Steps is...");
   Serial.println(steps);
   //lcd.print("   ");
// 
if(millis()-steps_old>=1000){
  noInterrupts();
}
   //temp=steps-steps_old;
   //steps_old=steps;

    rpm=(60*1000/20)/(millis()-steps_old)*pulses;
    //lcd.setCursor(9,1);
    Serial.print("The RPM is...");
    Serial.print(rpm);
    //lcd.print("   ");
 }
}
