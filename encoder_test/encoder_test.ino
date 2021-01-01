int encoder_pin = 2;             //Pin 2, donde se conecta el encoder   
int encoder_pin1 = 3;    
unsigned int rpm = 0;           // Revoluciones por minuto calculadas.
float velocity = 0;                  //Velocidad en [Km/h]
volatile byte pulses = 0;       // Número de pulsos leidos por el Arduino en un segundo
unsigned long timeold = 0;  // Tiempo 
unsigned int pulsesperturn = 20; // Número de muescas que tiene el disco del encoder.
const int wheel_diameter = 64;   // Diámetro de la rueda pequeña[mm]
static volatile unsigned long debounce = 0; // Tiempo del rebote.
unsigned int counter = 0;
////  Configuración del Arduino /////////////////////////////////////////////////////////
void setup(){
   Serial.begin(9600); // Configuración del puerto serie  
   pinMode(encoder_pin, INPUT); // Configuración del pin nº2
   pinMode(encoder_pin1, INPUT);
   attachInterrupt(0, counter, RISING); // Configuración de la interrupción 0, donde esta conectado. 
   pulses = 0;
   rpm = 0;
   timeold = 0;
  Serial.print("Seconds ");
  Serial.print("RPM ");
  Serial.print("Pulses ");
  Serial.println("Velocity[Km/h]");}
////  Programa principal ///////////////////////////////////////////////////////////////////////
 void loop(){
   if (millis() - timeold >= 1000){  // Se actualiza cada segundo
      noInterrupts(); //Don't process interrupts during calculations // Desconectamos la interrupción para que no actué en esta parte del programa.
      rpm = (60 * 1000 / pulsesperturn )/ (millis() - timeold)* pulses; // Calculamos las revoluciones por minuto
      velocity = rpm * 3.1416 * wheel_diameter * 60 / 1000000; // Cálculo de la velocidad en [Km/h] 
      timeold = millis(); // Almacenamos el tiempo actual.
      Serial.print(millis()/1000); //Serial.print("       ");// Se envia al puerto serie el valor de tiempo, de las rpm y los pulsos.
      Serial.print(rpm,DEC); //Serial.print("   ");
      Serial.print(pulses,DEC);// Serial.print("     ");
      Serial.println(velocity,2); 
      pulses = 0;  // Inicializamos los pulsos.
      interrupts(); // Restart the interrupt processing // Reiniciamos la interrupción
   }
  }
