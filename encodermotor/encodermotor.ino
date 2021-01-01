

#define ENCODEROUTPUT 120

#define BUTTON 2 // Maker UNO built-in button connected to pin 2
#define HALLSEN_A 3 // Hall sensor A connected to pin 3 (external interrupt)
#define BUZZER  8 // Maker UNO built-in buzzer connected to pin 8
#define PWM 10 // MD10C PWM connected to pin 10
#define DIR 12 // MD10C DIR connected to pin 12

// Note and frequencies
#define NOTE_G4  392
#define NOTE_C5  523
#define NOTE_E5  659
#define NOTE_G5  784

int melody[] = {
  NOTE_G4, NOTE_C5, NOTE_E5, NOTE_G5, 0, NOTE_E5, NOTE_G5
};

int noteDurations[] = {
  10, 10, 10, 10, 10, 10, 4, -10, -20, -30, 0, 10, 20, 30
};

volatile long encoderValue = 0;

int interval = 1000;
long previousMillis = 0;
long currentMillis = 0;

int rpm = 0;
boolean measureRpm = false;
int motorPwm = 0;

void setup()
{
  Serial.begin(9600); // Initialize serial with 9600 baudrate

  pinMode(BUTTON, INPUT_PULLUP); // Set button as input pullup
  pinMode(HALLSEN_A, INPUT_PULLUP); // Set hall sensor A as input pullup
  pinMode(BUZZER, OUTPUT); // Set buzzer as output
  pinMode(PWM, OUTPUT); // Set PWM pin as output
  pinMode(DIR, OUTPUT); // Set DIR pin as output
  
  // Attach interrupt at hall sensor A on each rising signal
  attachInterrupt(digitalPinToInterrupt(HALLSEN_A), updateEncoder, RISING);

  Serial.print("\n\n");
  Serial.println("Measuring DC Motor's RPM");
  Serial.println("Press Maker UNO button to begin.");
  Serial.println("Press again to stop.");
}

void loop()
{
  if (digitalRead(BUTTON) == LOW) { // If button is pressed...
    measureRpm = !measureRpm;
    if (measureRpm == true) { // 1st pressed, start moving the motor
      Serial.println("\nStart...\n");
      Serial.println("PWM\tRPM");
      playMelody();
    }
    else if (measureRpm == false) { // 2nd pressed, stop the motor
      Serial.println("\nStop...");
      tone(BUZZER, NOTE_C5, 100);
    }
    
    delay(500);
    encoderValue = 0;
    previousMillis = millis();
  }

  // Update RPM value on every second
  currentMillis = millis();
  if (currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;

    if (measureRpm == true &&
        motorPwm < 250) {
      motorPwm += 50;
      analogWrite(PWM, motorPwm);
    }
    else if (measureRpm == false &&
        motorPwm > 0) {
      motorPwm -= 50;
      analogWrite(PWM, motorPwm);
    }

    // Revolutions per minute (RPM) =
    // (total encoder pulse in 1s / motor encoder output) x 60s
    rpm = (float)(encoderValue * 60 / ENCODEROUTPUT);

    // Only update display when there have readings
    if (motorPwm > 0 || rpm > 0) {
      Serial.print(motorPwm);
      Serial.print('\t');
      Serial.print(encoderValue);
      Serial.print(" pulse / ");
      Serial.print(ENCODEROUTPUT);
      Serial.print(" pulse per rotation x 60 seconds = ");
      Serial.print(rpm);
      Serial.println(" RPM");
    }
    
    encoderValue = 0;
  }
}

void updateEncoder()
{
  // Add encoderValue by 1, each time it detects rising signal
  // from hall sensor A
  encoderValue++;
}

void playMelody()
{
  for (int thisNote = 0; thisNote < 7; thisNote++) {
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(BUZZER, melody[thisNote], noteDuration);
    delay(noteDuration);
    noTone(BUZZER);
  }
}
