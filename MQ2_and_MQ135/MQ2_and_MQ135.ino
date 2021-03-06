#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Adafruit_TFTLCD.h>
//#include <SPFD5408_Adafruit_GFX.h>    // Core graphics library
//#include <SPFD5408_Adafruit_TFTLCD.h>
//#include <SD.h>
//#include <SPI.h>

//#define OLED_RESET 4
//Adafruit_SSD1306 display(OLED_RESET);

#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
#define SD_CS 10
//int led = 10;
//int buzzer = 9;
int mq2 = A14;
int mq135 = A15;
float m = -0.318; // Slope
float a = 116.6020682;
float b = -2.769034857;
float c = 1.133;  // Y-Intercept
float R0 = 11.80; // Resistance of sensor in fresh air
float R01 = 25.5;

void setup() {

  Serial.begin(9600);

  //display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  //display.display();
  //delay(2000);

  //display.clearDisplay();
  //display.setTextSize(1);
  //display.setCursor(0, 0);
  //display.setTextColor(BLACK);

  tft.reset();
  tft.begin(0x9341);
  tft.setRotation(90);
  tft.fillScreen(WHITE);

  uint16_t identifier = tft.readID();

  //pinMode(led, OUTPUT);
  //digitalWrite(led, LOW);
  pinMode(mq2, INPUT);
  pinMode(mq135, INPUT);
  pinMode(10, OUTPUT);
  digitalWrite(10, HIGH);


  //  tft.begin(identifier);
  //
  //  Serial.print(PSTR("Initializing SD card..."));
  //  if (!SD.begin(SD_CS)) {
  //    Serial.println(PSTR("failed!"));
  //    return;
  //  }
  //  Serial.println(PSTR("OK!"));
  //}
}

void loop() {
  //  bmpDraw("flower.bmp", 0, 0);
  //  delay(2000);
  //   bmpDraw("tiger.bmp", 0, 0);
  //  delay(2000);
  //    bmpDraw("tree.bmp", 0, 0);
  //  delay(2000);
  //
  //
  //  #define BUFFPIXEL 20
  //
  //void bmpDraw(char *filename, int x, int y) {
  //
  //  File     bmpFile;
  //  int      bmpWidth, bmpHeight;   // W+H in pixels
  //  uint8_t  bmpDepth;              // Bit depth (currently must be 24)
  //  uint32_t bmpImageoffset;        // Start of image data in file
  //  uint32_t rowSize;               // Not always = bmpWidth; may have padding
  //  uint8_t  sdbuffer[3*BUFFPIXEL]; // pixel in buffer (R+G+B per pixel)
  //  uint16_t lcdbuffer[BUFFPIXEL];  // pixel out buffer (16-bit per pixel)
  //  uint8_t  buffidx = sizeof(sdbuffer); // Current position in sdbuffer
  //  boolean  goodBmp = false;       // Set to true on valid header parse
  //  boolean  flip    = true;        // BMP is stored bottom-to-top
  //  int      w, h, row, col;
  //  uint8_t  r, g, b;
  //  uint32_t pos = 0, startTime = millis();
  //  uint8_t  lcdidx = 0;
  //  boolean  first = true;
  //
  //  if((x >= tft.width()) || (y >= tft.height())) return;
  //
  //  Serial.println();
  //  progmemPrint(PSTR("Loading image '"));
  //  Serial.print(filename);
  //  Serial.println('\'');
  //  // Open requested file on SD card
  //  if ((bmpFile = SD.open(filename)) == NULL) {
  //    progmemPrintln(PSTR("File not found"));
  //    return;
  //  }
  //
  //  // Parse BMP header
  //  if(read16(bmpFile) == 0x4D42) { // BMP signature   4D42
  //    progmemPrint(PSTR("File size: ")); Serial.println(read32(bmpFile));
  //    (void)read32(bmpFile); // Read & ignore creator bytes
  //    bmpImageoffset = read32(bmpFile); // Start of image data
  //    progmemPrint(PSTR("Image Offset: ")); Serial.println(bmpImageoffset, DEC);
  //    // Read DIB header
  //    progmemPrint(PSTR("Header size: ")); Serial.println(read32(bmpFile));
  //    bmpWidth  = read32(bmpFile);
  //    bmpHeight = read32(bmpFile);
  //    if(read16(bmpFile) == 1) { // # planes -- must be '1'
  //      bmpDepth = read16(bmpFile); // bits per pixel
  //      progmemPrint(PSTR("Bit Depth: ")); Serial.println(bmpDepth);
  //      if((bmpDepth == 24) && (read32(bmpFile) == 0)) { // 0 = uncompressed
  //
  //        goodBmp = true; // Supported BMP format -- proceed!
  //        progmemPrint(PSTR("Image size: "));
  //        Serial.print(bmpWidth);
  //        Serial.print('x');
  //        Serial.println(bmpHeight);
  //
  //        // BMP rows are padded (if needed) to 4-byte boundary
  //        rowSize = (bmpWidth * 3 + 3) & ~3;
  //
  //        // If bmpHeight is negative, image is in top-down order.
  //        // This is not canon but has been observed in the wild.
  //        if(bmpHeight < 0) {
  //          bmpHeight = -bmpHeight;
  //          flip      = false;
  //        }
  //
  //        // Crop area to be loaded
  //        w = bmpWidth;
  //        h = bmpHeight;
  //        if((x+w-1) >= tft.width())  w = tft.width()  - x;
  //        if((y+h-1) >= tft.height()) h = tft.height() - y;
  //
  //        // Set TFT address window to clipped image bounds
  //        tft.setAddrWindow(x, y, x+w-1, y+h-1);
  //
  //        for (row=0; row<h; row++) { // For each scanline...
  //          // Seek to start of scan line.  It might seem labor-
  //          // intensive to be doing this on every line, but this
  //          // method covers a lot of gritty details like cropping
  //          // and scanline padding.  Also, the seek only takes
  //          // place if the file position actually needs to change
  //          // (avoids a lot of cluster math in SD library).
  //          if(flip) // Bitmap is stored bottom-to-top order (normal BMP)
  //            pos = bmpImageoffset + (bmpHeight - 1 - row) * rowSize;
  //          else     // Bitmap is stored top-to-bottom
  //            pos = bmpImageoffset + row * rowSize;
  //          if(bmpFile.position() != pos) { // Need seek?
  //            bmpFile.seek(pos);
  //            buffidx = sizeof(sdbuffer); // Force buffer reload
  //          }
  //
  //          for (col=0; col<w; col++) { // For each column...
  //            // Time to read more pixel data?
  //            if (buffidx >= sizeof(sdbuffer)) { // Indeed
  //              // Push LCD buffer to the display first
  //              if(lcdidx > 0) {
  //                tft.pushColors(lcdbuffer, lcdidx, first);
  //                lcdidx = 0;
  //                first  = false;
  //              }
  //              bmpFile.read(sdbuffer, sizeof(sdbuffer));
  //              buffidx = 0; // Set index to beginning
  //            }
  //
  //            // Convert pixel from BMP to TFT format
  //            b = sdbuffer[buffidx++];
  //            g = sdbuffer[buffidx++];
  //            r = sdbuffer[buffidx++];
  //            lcdbuffer[lcdidx++] = tft.color565(r,g,b);
  //          } // end pixel
  //        } // end scanline
  //        // Write any remaining data to LCD
  //        if(lcdidx > 0) {
  //          tft.pushColors(lcdbuffer, lcdidx, first);
  //        }
  //        progmemPrint(PSTR("Loaded in "));
  //        Serial.print(millis() - startTime);
  //        Serial.println(" ms");
  //      } // end goodBmp
  //    }
  //  }
  //
  //  bmpFile.close();
  //  if(!goodBmp) progmemPrintln(PSTR("BMP format not recognized."));
  //}
  //
  //// These read 16- and 32-bit types from the SD card file.
  //// BMP data is stored little-endian, Arduino is little-endian too.
  //// May need to reverse subscript order if porting elsewhere.
  //
  //uint16_t read16(File f) {
  //  uint16_t result;
  //  ((uint8_t *)&result)[0] = f.read(); // LSB
  //  ((uint8_t *)&result)[1] = f.read(); // MSB
  //  return result;
  //}
  //
  //uint32_t read32(File f) {
  //  uint32_t result;
  //  ((uint8_t *)&result)[0] = f.read(); // LSB
  //  ((uint8_t *)&result)[1] = f.read();
  //  ((uint8_t *)&result)[2] = f.read();
  //  ((uint8_t *)&result)[3] = f.read(); // MSB
  //  return result;
  //}
  //
  //// Copy string from flash to serial port
  //// Source string MUST be inside a PSTR() declaration!
  //void progmemPrint(const char *str) {
  //  char c;
  //  while(c = pgm_read_byte(str++)) Serial.print(c);
  //}
  //
  //// Same as above, with trailing newline
  //void progmemPrintln(const char *str) {
  //  progmemPrint(str);
  Serial.println();

  float sensor_volt;
  float sensor_volt1;
  float RS_gas;
  float RS_gas1;
  float ratio;
  float ratio1;

  float sensorValue = analogRead(mq2);
  float sensorvalue1 = analogRead(mq135);

  sensor_volt = sensorValue * (5.0 / 1023.0);
  sensor_volt1 = sensorvalue1 * (5.0 / 1023.0);

  RS_gas = ((5.0 * 10.0) / sensor_volt) - 10.0;
  RS_gas1 = ((5.0 * 10.0) / sensor_volt1) - 10.0;

  ratio = RS_gas / R0;
  ratio1 = RS_gas1 / R01;

  double ppm2_log = (log10(ratio) - c) / m;
  double ppm2 = pow(10, ppm2_log);
  double percentage2 = ppm2 / 10000;

  double ppm135 = a * pow((ratio1), b);
  double percentage135 = ppm135 / 1000;


  //tft.reset();

  tft.setCursor(0, 0);
  tft.setTextColor(BLACK);
  tft.setTextSize(2);
  tft.print("PPM_MQ2 = ");
  tft.println(ppm2);


  tft.setCursor(0, 20);
  tft.setTextColor(BLACK);
  tft.setTextSize(2);
  tft.print("PERCENTAGE_MQ2 = ");
  tft.println(percentage2);

  tft.setCursor(0, 40);
  tft.setTextColor(BLACK);
  tft.setTextSize(2);
  tft.print("RATIO_MQ2 = ");
  tft.println(ratio);

  tft.setCursor(0, 200);
  tft.setTextColor(BLACK);
  tft.setTextSize(2);
  tft.print("PPM_MQ135 = ");
  tft.println(ppm135);

  tft.setCursor(0, 220);
  tft.setTextColor(BLACK);
  tft.setTextSize(2);
  tft.print("PERCENTAGE_MQ135 = ");
  tft.println(percentage135);

  tft.setCursor(0, 240);
  tft.setTextColor(BLACK);
  tft.setTextSize(2);
  tft.print("RATIO_MQ135 = ");
  tft.println(ratio1);


  if (ppm2 > 2000)  {

    tft.setCursor(0, 130);
    tft.setTextColor(RED);
    tft.setTextSize(3);
    tft.print("PRESENCE OF INFLAMMABLE GAS");

  }
  if (ppm135 > 400)  {
    tft.setCursor(0, 300);
    tft.setTextColor(RED);
    tft.setTextSize(3);
    tft.print("PRESENCE OF TOXIC GAS");
  }




  delay(2000);

  tft.fillScreen(WHITE);



  //tft.setCursor(135,215);
  //tft.setTextColor(BLACK);
  //tft.setTextSize(4);
  //tft.print("Subscribe");

  //tft.drawRect(0,0,480,320,BLACK);
  // delay(1000);




  //  if (ratio = max(1.7, 0.27)){
  //    Serial.print("LPG = ");
  //  }else if{
  //    (ratio = max(1.725, 0.28));{
  //      Serial.print("Propane = ");
  //    }else if{
  //    (ratio = max(2.1, 0.33));{
  //      Serial.print("H2 = ");
  //    }else if{
  //    (ratio = max(2.9, 0.65));{
  //      Serial.print("Alocohol = ");
  //    }else if{
  //    (ratio = max(3, 0.7));{
  //      Serial.print("Methane = ");
  //    }
  //    else if{
  //    (ratio = max(3.4, 0.6));{
  //      Serial.print("Smoke = ");
  //    }
  //    else if{
  //    (ratio = max(5.15, 1.5));{
  //      Serial.print("CO = ");
  //    }else if{
  //    (ratio = max(10, 10));{
  //      Serial.print("Air = ");
  //    }
  //  }

  //  delay (1000);
  //  Serial.print("PPM_MQ2 = ");
  //  Serial.println(ppm2);
  //  Serial.print("Percentage_MQ2 = ");
  //  Serial.println(percentage2);
  //  delay(1000);

  //display.setCursor(0,0);
  //display.print("PPM_MQ2 = ");
  //display.println(ppm2);
  //display.setCursor(0, 10);
  //display.print("Percentage_MQ2 = ");
  //display.println(percentage2);
  //display.setCursor(0, 20);
  //display.print("Ratio1 = ");
  //display.println(ratio1);

  delay(1000);
  Serial.print("PPM_MQ135 = ");
  Serial.println(ppm135);
  Serial.print("Percentage_MQ135 = ");
  Serial.println(percentage135);
  delay(1000);


  //display.print("PPM_MQ135 = ");
  //display.println(ppm135);
  //display.setCursor(0, 30);
  //display.print("Percentage_MQ135 = ");
  //display.println(percentage135);
  //display.display();
  //delay(50);
  //display.clearDisplay();





}
