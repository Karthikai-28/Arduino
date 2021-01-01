#include <SPFD5408_Adafruit_GFX.h>    // Core graphics library
#include <SPFD5408_Adafruit_TFTLCD.h> // Hardware-specific library
#include <SPFD5408_TouchScreen.h>
#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0
#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
 
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
void setup(void) {
 
  Serial.begin(9600);
 
  progmemPrintln(PSTR("TFT LCD test"));
 
#ifdef USE_ADAFRUIT_SHIELD_PINOUT
  progmemPrintln(PSTR("Using Adafruit 2.8\" TFT Arduino Shield Pinout"));
#else
  progmemPrintln(PSTR("Using Adafruit 2.8\" TFT Breakout Board Pinout"));
#endif
 
  tft.reset(); //Do not change
  tft.begin(0x9341); //Do not change!
  tft.setRotation(0); //Change the rotation of the screen.
  progmemPrintln(PSTR("Benchmark                Time (microseconds)"));
  progmemPrintln(PSTR("Done!"));
}
 
void loop(void) {
  // Colorcheck start
  tft.fillScreen(BLACK);
  tft.fillScreen(RED);
  tft.fillScreen(GREEN);
  tft.fillScreen(BLUE);
  tft.fillScreen(BLACK);
  // Colorcheck stop
 tft.setCursor(0, 0);
 tft.setTextColor(BLUE);
 tft.setTextSize(2);
 tft.print("Hello world !!");
  tft.setTextColor(GREEN);
 tft.setTextSize(2);
 tft.print("      Waiting 7 seconds ..");
 delay(7000);
}
 
 
 
 
 
 
 
 
 
 
 
// don't change !!!!
void progmemPrint(const char *str) {
  char c;
  while(c = pgm_read_byte(str++)) Serial.print(c);
}
 
// Same as above, with trailing newline
void progmemPrintln(const char *str) {
  progmemPrint(str);
  Serial.println();
}
