int dir1 = 12;
int pwm1 = 10;
int dir2 = 11;
int pwm2 = 9;
void setup() {
  pinMode(dir1, OUTPUT);
pinMode(pwm1, OUTPUT);
pinMode(dir2, OUTPUT);
pinMode(pwm2, OUTPUT);
}

void loop() {
  analogWrite(pwm1, 120);
  digitalWrite(dir1, HIGH);
analogWrite(pwm2, 120);
  digitalWrite(dir2, HIGH);

  delay(2000);
analogWrite(pwm1, 120);
  digitalWrite(dir1, LOW);
analogWrite(pwm2, 120);
  digitalWrite(dir2, LOW);

  delay(2000);
  
}
