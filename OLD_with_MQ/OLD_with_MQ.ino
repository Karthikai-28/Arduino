#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

int led = 10; 
int buzzer = 9; 
int gas_sensor = A0; 
float m = -0.318; // Slope
float b = 1.133;  // Y-Intercept
float R0 = 11.80; // Resistance of sensor in fresh air

void setup() {
 Serial.begin(9600);

 display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
 
  display.display();
  delay(2000);

 // Clear the buffer.
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.setTextColor(WHITE);

  Serial.begin(9600); 
  pinMode(led, OUTPUT); 
  digitalWrite(led, LOW); 
  pinMode(gas_sensor, INPUT);

}

void loop() {
  
  float sensor_volt;
  float RS_gas; 
  float ratio; 
  float sensorValue = analogRead(gas_sensor); 
  sensor_volt = sensorValue * (5.0 / 1023.0); 
  RS_gas = ((5.0 * 10.0) / sensor_volt) - 10.0; 
  ratio = RS_gas / R0;  

  double ppm_log = (log10(ratio) - b) / m; 
  double ppm = pow(10, ppm_log); 
  double percentage = ppm / 10000; 
  Serial.print("PPM = ");
  Serial.println(ppm);
  Serial.print(percentage);
  Serial.println("%");
  
  display.setCursor(0, 0);
  display.print("PPM = : ");
  display.println(ppm);
  display.setCursor(1, 0);
  display.print("PERCENTAGE = ");
  display.println(percentage);
  display.display(); //you have to tell the display to...display
  delay(50);
  display.clearDisplay();
}
