#include <DHT.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

//Constants
#define SERIAL_DEBUG

// DHT22
#define DHTPIN 2    
#define DHTTYPE DHT22   

// For the LCD shield, these are the default.
#define TFT_DC 9
#define TFT_CS 10

// Initialize LCD
// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

// If using the breakout, change pins as desired
//Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

// Initialize DHT sensor for normal 16mhz Arduino
DHT dht(DHTPIN, DHTTYPE); 

//Variables
float hum;  //Stores humidity value
float temp; //Stores temperature value
float converted = 0.00;

//Arduino setup
void setup() 
{
  #ifdef SERIAL_DEBUG
    Serial.begin(9600);
    Serial.println("ILI9341 Test!"); 
    Serial.println("DHT22 temperature / humidity sensor Test");
  #endif
  
  //Initialize TFT LCD
  tft.begin();

  //Initialize the DHT sensor
  dht.begin();
    
  #ifdef SERIAL_DEBUG
    // read diagnostics (optional but can help debug problems)
    uint8_t x = tft.readcommand8(ILI9341_RDMODE);
    Serial.print("Display Power Mode: 0x"); Serial.println(x, HEX);
    x = tft.readcommand8(ILI9341_RDMADCTL);
    Serial.print("MADCTL Mode: 0x"); Serial.println(x, HEX);
    x = tft.readcommand8(ILI9341_RDPIXFMT);
    Serial.print("Pixel Format: 0x"); Serial.println(x, HEX);
    x = tft.readcommand8(ILI9341_RDIMGFMT);
    Serial.print("Image Format: 0x"); Serial.println(x, HEX);
    x = tft.readcommand8(ILI9341_RDSELFDIAG);
    Serial.print("Self Diagnostic: 0x"); Serial.println(x, HEX);
  #endif 

 //Rotate the screen to right direction
 tft.setRotation(1);

 //Print the headers
 printHeader();
}

//Main loop
void loop(void) 
{ 

  //Read data and store it to variables hum and temp
  hum = dht.readHumidity();
  temp= dht.readTemperature();
    
  printTemperatureHumidity();

  //Delay 2 Seconds
  delay(2000);
}

//Print headers
unsigned long printHeader(void )
{
  tft.fillRect(0,0,240, 64,ILI9341_GREEN);
  tft.fillRect(0,64,240, 64,ILI9341_RED);
  tft.fillRect(0,128,240, 64,ILI9341_CYAN);
  tft.fillRect(0,192,240, 64,ILI9341_YELLOW);
  tft.fillRect(0,256,240, 64,ILI9341_ORANGE);

  unsigned long start = micros();
  tft.setTextColor(ILI9341_BLACK);   
  tft.setTextSize(3);
  //
  tft.setCursor(50,0+20);
  tft.print("CELCIUS");

  //
  tft.setCursor(50,64+20);
  tft.print("FAHRENHEIT");
  //
  tft.setCursor(50,128+20);
  tft.print("KELVIN");

    //
  tft.setCursor(50,192+20);
  tft.print("RANKIN");

   //
  tft.setCursor(50,256+20);
  tft.print("HUMIDITY");
  
  return micros() - start;
    
}

//Print temperature and humidity
unsigned long printTemperatureHumidity() 
{
  tft.fillRect(241,0,240, 64,ILI9341_CYAN);
  tft.fillRect(241,64,240, 64,ILI9341_YELLOW);
  tft.fillRect(241,128,240, 64,ILI9341_ORANGE);
  tft.fillRect(241,192,240, 64,ILI9341_GREEN);
  tft.fillRect(241,256,240, 64,ILI9341_RED);
    
  //tft.fillScreen(ILI9341_BLUE);
  unsigned long start = micros();
  tft.setTextColor(ILI9341_BLACK);   
  tft.setTextSize(4);

  #ifdef SERIAL_DEBUG
    Serial.print("Celsius = ");
    Serial.print(temp);
    //Print degree symbol
    Serial.write(176); 
    Serial.println("C");
  #endif
        
  tft.setCursor(250,0+20);
  tft.print(temp);
  tft.print(" ");
  tft.print((char)247);
  tft.println("C");

    //Fahrenheit
    //T(°F) = T(°C) × 9/5 + 32
    converted = ( temp * 1.8 ) + 32;
  #ifdef SERIAL_DEBUG
    Serial.print("Fahrenheit = ");
    Serial.print(converted);
    //Print degree symbol
    Serial.write(176); 
    Serial.println("F");
  #endif
      
    tft.setCursor(250,64+20);
    tft.print(converted);
    tft.print(" ");
    tft.print((char)247);
    tft.println("F");

//Kelvin
    //T(K) = T(°C) + 273.15          
    converted = temp + 273.15;
 #ifdef SERIAL_DEBUG    
    Serial.print("Kelvin = ");
    Serial.print(converted);
    Serial.println(" K");
 #endif
  tft.setCursor(250,128+20);
  tft.print(converted);
  tft.print(" ");
  tft.println("K");

   //Rankine
    //T(°R) = (T(°C) + 273.15) × 9/5          
    converted = temp + 273.15;
    converted = (converted * 1.8);
  #ifdef SERIAL_DEBUG
    Serial.print("Rankin = ");
    Serial.print(converted);
    //Print degree symbol
    Serial.write(176);    
    Serial.println("R");
  #endif
  tft.setCursor(250,192+20);
  tft.print(converted);
  tft.print(" ");
  tft.print((char)247);
  tft.println("R");

 //Humidity
 #ifdef SERIAL_DEBUG
    Serial.print("Humidity =");
    Serial.println(hum);
 #endif
    
  tft.setCursor(250,256+20);
  tft.print(hum);
  tft.print(" ");
  tft.println("%");
  
  return micros() - start;
}
