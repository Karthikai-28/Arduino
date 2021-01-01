#include<Adafruit_TFTLCD.h>
#include<Adafruit_GFX.h>

#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4

#define TS_MINX 1017
#define TS_MINY 981
#define TS_MAXX 953
#define TS_MINY 944

#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);


boolean buttonEnabled = true;

void setup() {
  tft.reset();
  uint16_t identifier = tft.readID();
  tft.begin(identifier);
  tft.setRotation(0);
  tft.fillScreen(WHITE);
  tft.drawRect(0,0,240, 400, YELLOW);

  tft.setCursor(30,40);
  tft.setTextColor(BLACK);
  tft.setTextSize(2);
  tft.print("HEY");
  
}

