int mqInput = A0;
//pull-down resistor value
int mqR = 22000;
//rO sensor value
long rO = 41763;
//min value for Rs/Ro
float minRsRo = 0.358;
//max value for Rs/Ro
float maxRsRo = 2.428;
//sensor a coefficient value
float a = 116.6020682;
//sensor b coefficient value
float b = -2.769034857;

void setup() {
  pinMode(mqInput, INPUT);
  Serial.begin(9600);
  
}
 
void loop() {
  double x;
double z;
 
  int adcRaw = analogRead(mqInput);
  long rS = ((1024.0 * mqR) / adcRaw) - mqR;
  Serial.print("Rs: ");
  Serial.println(rS);
  float rSrO = (float)rS / (float)rO;
  Serial.print("Rs/Ro: ");
  Serial.println(rSrO);
  if(rSrO < maxRsRo && rSrO > minRsRo) 
  x = a *((float)rS / (float)rO);
  z = pow (b);
 float ppm =( x * z);
 Serial.print("ppm: ");
 Serial.println(ppm);
  delay(1000);
}
