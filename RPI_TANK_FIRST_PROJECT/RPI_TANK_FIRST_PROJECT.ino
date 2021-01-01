const int D0 = 0;       //RPI 21
const int D1 = 1;       //RPI 22
const int D2 = 2;       //RPI 23
const int D3 = 3;       //RPI 24

const int Motor1DIR = 7;
const int Motor1PWM = 6;

const int Motor2PWM = 9;
const int Motor2DIR = 8;

int a,b,c,d,data;

void setup(){
  Serial.begin(9600);
  pinMode(Motor1DIR, OUTPUT);
  pinMode(Motor1PWM, OUTPUT);
  pinMode(Motor2DIR, OUTPUT);
  pinMode(Motor2PWM, OUTPUT);

  pinMode(D0, INPUT_PULLUP);
  pinMode(D1, INPUT_PULLUP);
  pinMode(D2, INPUT_PULLUP);
  pinMode(D3, INPUT_PULLUP);
}

void loop(){
  Data();
  
  if(data==0){
    Forward();
  }
  else if(data==1){
    Right1();
  }  
  else if(data==2){
    Right2();
  }  
  else if(data==3){
    Right3();
  } 
  else if(data==4){
    Left1();
  } 
  else if(data==5){
    Left2();
  }  
  else if(data==6){
    Left3();
  } 
  else if(data==7){
    UTurn();
  }
  else if (data>7){
    Stop();
  }
}





void Data(){
  a = digitalRead(D0);
  b = digitalRead(D1);
  c = digitalRead(D2);
  d = digitalRead(D3);

  data = 8*d+4*c+2*b+a;

  delay(100);
  Serial.print(a);
   Serial.print(b);
    Serial.print(c);
     Serial.println(d);
}

void Forward(){
  analogWrite(Motor1PWM, 100);
  analogWrite(Motor2PWM, 100);
  
  digitalWrite(Motor1DIR, LOW);
  digitalWrite(Motor2DIR, LOW);

  delay(1000);
}

void Reverse(){
  analogWrite(Motor1PWM, 100);
  analogWrite(Motor2PWM, 100);
  
  digitalWrite(Motor1DIR, HIGH);
  digitalWrite(Motor2DIR, HIGH);

  delay(1000);
}

void Right(){
  analogWrite(Motor1PWM, 255);
  analogWrite(Motor2PWM, 255);
  
  digitalWrite(Motor1DIR, LOW);
  digitalWrite(Motor2DIR, HIGH);

  delay(1000);
}

void Right1(){
  analogWrite(Motor1PWM, 255);
  analogWrite(Motor2PWM, 160);
  
  digitalWrite(Motor1DIR, LOW);
  digitalWrite(Motor2DIR, HIGH);

  delay(1000);
}

void Right2(){
  analogWrite(Motor1PWM, 255);
  analogWrite(Motor2PWM, 90);
  
  digitalWrite(Motor1DIR, LOW);
  digitalWrite(Motor2DIR, HIGH);

  delay(1000);
}

void Right3(){
  analogWrite(Motor1PWM, 255);
  analogWrite(Motor2PWM, 50);
  
  digitalWrite(Motor1DIR, LOW);
  digitalWrite(Motor2DIR, HIGH);

  delay(1000);
}

void Stop(){
  digitalWrite(Motor1PWM, LOW);
  digitalWrite(Motor2PWM, LOW);
  
  digitalWrite(Motor1DIR, LOW);
  digitalWrite(Motor2DIR, LOW);
}

void Left1(){
  analogWrite(Motor1PWM, 160);
  analogWrite(Motor2PWM, 255);
  
  digitalWrite(Motor1DIR, HIGH);
  digitalWrite(Motor2DIR, LOW);

  delay(1000);
}

void Left2(){
  analogWrite(Motor1PWM, 90);
  analogWrite(Motor2PWM, 255);
  
  digitalWrite(Motor1DIR, HIGH);
  digitalWrite(Motor2DIR, LOW);

  delay(1000);
}

void Left3(){
  analogWrite(Motor1PWM, 50);
  analogWrite(Motor2PWM, 255);
  
  digitalWrite(Motor1DIR, HIGH);
  digitalWrite(Motor2DIR, LOW);

  delay(1000);
}

void UTurn(){
  Stop();
  delay(1000);

  Forward();
  delay(1000);

  Stop();
  delay(400);

  Right();
  delay(4000);

  Stop();
  delay(400);

  Forward();
  delay(900);

  Stop();
  delay(400);

  Right();
  delay(4000);

  Stop();
  delay(400);

  Forward();
  delay(1000);

    Stop();
  delay(400);
}
