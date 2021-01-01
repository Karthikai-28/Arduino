int LED1 =3;
int LED2 =4;
int LED3 =5;
int LED4 =6;

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
}

void loop() {
  digitalWrite(3, HIGH);   
  delay(1000);                       
  digitalWrite(4, HIGH);    
  delay(1000);  
  digitalWrite(5, HIGH);   
  delay(1000);                       
  digitalWrite(6, HIGH);    
  delay(1000);
  digitalWrite(6, LOW);   
  delay(1000);                       
  digitalWrite(5, LOW);    
  delay(1000);  
  digitalWrite(4, LOW);   
  delay(1000);                       
  digitalWrite(3, LOW);    
  delay(1000);                     
}

