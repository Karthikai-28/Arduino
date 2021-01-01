#include<IRremote.h>
int RECV = 12;
IRrecv irrecv(RECV);
decode_results results;
int remote = 0;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn();
}

void loop(){
  if(irrecv.decode(&results))
  {
    remote=results.value;
    Serial.println(remote);
    irrecv.resume();
  }
}

