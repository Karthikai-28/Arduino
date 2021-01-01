int led = 13;
int received = 0;
int i;
void setup() {
  Serial.begin(9600); 
  pinMode(led, OUTPUT);
}
 
void loop() {
  if (Serial.available() > 0) {
received = Serial.read();
  
    if (received == 'a'){
    digitalWrite(led, HIGH);
    }
     else if (received == 'b'){
      for(i=0;i<5;i++){
    digitalWrite(led, LOW);
    delay(1000);
    }
  } 
}
}
