// BMP-loading example specifically for the TFTLCD breakout board.
// If using the Arduino shield, use the tftbmp_shield.pde sketch instead!
// If using an Arduino Mega, make sure the SD library is configured for
// 'soft' SPI in the file Sd2Card.h.

///////  ***** Not Tested yet on SPFD5408 - next version I do it
//#include <Adafruit_GFX.h>
//#include <Adafruit_TFTLCD.h> 
//#include <Adafruit_GFX_AS.h>     // Core graphics library
//#include <Adafruit_ILI9341_AS.h>
#include <SPFD5408_Adafruit_GFX.h>    // Core graphics library
#include <SPFD5408_Adafruit_TFTLCD.h> // Hardware-specific library
#include <SD.h>
#include <SPI.h>
// The control pins for the LCD can be assigned to any digital or
// analog pins...but we'll use the analog pins as this allows us to
// double up the pins with the touch screen (see the TFT paint example).
#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

#define ILI9341_GREY 0xCE9A

// When using the BREAKOUT BOARD only, use these 8 data lines to the LCD:
// For the Arduino Uno, Duemilanove, Diecimila, etc.:
//   D0 connects to digital pin 8  (Notice these are
//   D1 connects to digital pin 9   NOT in order!)
//   D2 connects to digital pin 2
//   D3 connects to digital pin 3
//   D4 connects to digital pin 4
//   D5 connects to digital pin 5
//   D6 connects to digital pin 6
//   D7 connects to digital pin 7
// For the Arduino Mega, use digital pins 22 through 29
// (on the 2-row header at the end of the board).

// For Arduino Uno/Duemilanove, etc
//  connect the SD card with DI going to pin 11, DO going to pin 12 and SCK going to pin 13 (standard)
//  Then pin 10 goes to CS (or whatever you have set up)
#define SD_CS 10     // Set the chip select line to whatever you use (10 doesnt conflict with the library)

// In the SD card, place 24 bit color BMP files (be sure they are 24-bit!)
// There are examples in the sketch folder

// our TFT wiring
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, A4);

void setup()
{
  Serial.begin(9600);
  tft.reset();
  tft.begin(0x9341);
  uint16_t identifier = tft.readID();

// if(identifier == 0x9325) {
//    progmemPrintln(PSTR("Found ILI9325 LCD driver"));
// } else if(identifier == 0x9328) {
//    progmemPrintln(PSTR("Found ILI9328 LCD driver"));
//  } else if(identifier == 0x7575) {
//    progmemPrintln(PSTR("Found HX8347G LCD driver"));
//  } else {
//    progmemPrint(PSTR("Unknown LCD driver chip: "));
//   Serial.println(identifier, HEX);
//    progmemPrintln(PSTR("If using the Adafruit 2.8\" TFT Arduino shield, the line:"));
//    progmemPrintln(PSTR("  #define USE_ADAFRUIT_SHIELD_PINOUT"));
//    progmemPrintln(PSTR("should appear in the library header (Adafruit_TFT.h)."));
//    progmemPrintln(PSTR("If using the breakout board, it should NOT be #defined!"));
//    progmemPrintln(PSTR("Also if using the breakout, double-check that all wiring"));
//    progmemPrintln(PSTR("matches the tutorial."));
//   return;
 pinMode(10, OUTPUT);
 digitalWrite(10, HIGH);
  

  tft.begin(identifier);

  Serial.print(PSTR("Initializing SD card..."));
  if (!SD.begin(SD_CS)) {
    Serial.println(PSTR("failed!"));
    return;
  }
  Serial.println(PSTR("OK!"));

  
}

void loop()
{
tft.setRotation(1);
  tft.fillScreen(ILI9341_GREY);
//  drawRAW("Inst_1.raw", 0, 0, 320, 240);
bmpDraw("225term.bmp", 0, 0);
  delay(2000);
   bmpDraw("tiger.bmp", 0, 0);
  delay(2000);
    bmpDraw("225termi.bmp", 0, 0);
  delay(2000);
  bmpDraw("240Moon.bmp", 0, 0);
  delay(2000);
  bmpDraw("284taz.bmp", 0, 0);
  delay(2000);
  bmpDraw("480Mouse.bmp", 0, 0);
  delay(2000);
  bmpDraw("Inst_1.bmp", 0, 0);
  delay(2000);
  bmpDraw("test_dn", 0, 0);
  delay(2000);
  bmpDraw("test_up", 0, 0);
  delay(2000);
  bmpDraw("test_ups", 0, 0);
  delay(2000);
  
   
}


#define BUFF_SIZE 80

void drawBMP(char *filename, int x, int y, boolean flip) {
  if ((x >= tft.width()) || (y >= tft.height())) return;
  File     bmpFile;
  int16_t  bmpWidth, bmpHeight;   // Image W+H in pixels
  //uint8_t  bmpDepth;            // Bit depth (must be 24) but we dont use this
  uint32_t bmpImageoffset;        // Start address of image data in file
  uint32_t rowSize;               // Not always = bmpWidth; may have padding
  uint8_t  sdbuffer[3 * BUFF_SIZE];    // SD read pixel buffer (8 bits each R+G+B per pixel)
  uint16_t tftbuffer[BUFF_SIZE];       // TFT pixel out buffer (16-bit per pixel)
  uint8_t  sd_ptr = sizeof(sdbuffer); // sdbuffer pointer (so BUFF_SIZE must be less than 86)
  boolean  goodBmp = false;            // Flag set to true on valid header parse
  int16_t  w, h, row, col;             // to store width, height, row and column
  //uint8_t  r, g, b;   // brg encoding line concatenated for speed so not used
  uint8_t rotation;     // to restore rotation
  uint8_t  tft_ptr = 0;  // buffer pointer

  // Check file exists and open it
  if ((bmpFile = SD.open(filename)) == NULL) {
    Serial.println(F("File not found")); // Can comment out if not needed
    return;
  }

  drawTime = millis(); // Save current time for performance evaluation, comment out if not needed

  // Parse BMP header to get the information we need
  if (read16(bmpFile) == 0x4D42) { // BMP file start signature check
    read32(bmpFile);       // Dummy read to throw away and move on
    read32(bmpFile);       // Read & ignore creator bytes
    bmpImageoffset = read32(bmpFile); // Start of image data
    read32(bmpFile);       // Dummy read to throw away and move on
    bmpWidth  = read32(bmpFile);  // Image width
    bmpHeight = read32(bmpFile);  // Image height

    //if (read16(bmpFile) == 1) { // Number of image planes -- must be '1'
    // Only proceed if we pass a bitmap file check
    if ((read16(bmpFile) == 1) && (read16(bmpFile) == 24) && (read32(bmpFile) == 0)) { // Must be depth 24 and 0 (uncompressed format)
      //goodBmp = true; // Supported BMP format -- proceed!
      // BMP rows are padded (if needed) to 4-byte boundary
      rowSize = (bmpWidth * 3 + 3) & ~3;
      // Crop area to be loaded
      w = bmpWidth;
      h = bmpHeight;

      // We might need to alter rotation to avoid tedious pointer manipulation
      // Save the current value so we can restore it later
      rotation = tft.getRotation();
      // Use TFT SGRAM coord rotation if flip is set for 25% faster rendering
      if (flip) tft.setRotation((rotation + (flip<<2)) % 8); // Value 0-3 mapped to 4-7

      // We might need to flip and calculate new y plot coordinate
      // relative to top left corner as well...
      switch (rotation) {
        case 0:
          if (flip) y = tft.height() - y - h; break;
        case 1:
          y = tft.height() - y - h; break;
          break;
        case 2:
          if (flip) y = tft.height() - y - h; break;
          break;
        case 3:
          y = tft.height() - y - h; break;
          break;
      }

      // Set TFT address window to image bounds
      // Currently, image will not draw or will be corrputed if it does not fit
      // TODO -> efficient clipping, I don't need it to be idiot proof ;-)
      tft.setAddrWindow(x, y, x + w - 1, y + h - 1);

      // Finally we are ready to send rows of pixels, writing like this avoids slow 32 bit multiply
      for (uint32_t pos = bmpImageoffset; pos < bmpImageoffset + h * rowSize ; pos += rowSize) {
        // Seek if we need to on boundaries and arrange to dump buffer and start again
        if (bmpFile.position() != pos) {
          bmpFile.seek(pos);
          sd_ptr = sizeof(sdbuffer);        }

        // Fill the pixel buffer and plot
        for (col = 0; col < w; col++) { // For each column...
          // Time to read more pixel data?
          if (sd_ptr >= sizeof(sdbuffer)) {
            // Push tft buffer to the display
            if (tft_ptr) {
              // Here we are sending a uint16_t array to the function
              tft.pushColors(tftbuffer, tft_ptr);
              tft_ptr = 0; // tft_ptr and sd_ptr are not always in sync...
            }
            // Finally reading bytes from SD Card
            bmpFile.read(sdbuffer, sizeof(sdbuffer));
            sd_ptr = 0; // Set buffer index to start
          }
          // Convert pixel from BMP 8+8+8 format to TFT compatible 16 bit word
          // Blue 5 bits, green 6 bits and red 5 bits (16 bits total)
          // Is is a long line but it is faster than calling a library fn for this
          tftbuffer[tft_ptr++] = (sdbuffer[sd_ptr++] >> 3) | ((sdbuffer[sd_ptr++] & 0xFC) << 3) | ((sdbuffer[sd_ptr++] & 0xF8) << 8);
        } // Next row
      }   // All rows done

      // Write any partially full buffer to TFT
      if (tft_ptr) tft.pushColors(tftbuffer, tft_ptr);
      drawTime = millis() - drawTime;
    } // End of bitmap access
  }   // End of bitmap file check
  //}     // We can close the file now

  bmpFile.close();
  //if(!goodBmp) Serial.println(F("BMP format not recognized."));
  tft.setRotation(rotation); // Put back original rotation
}

/***************************************************************************************
** Function name:           drawRAW
** Descriptions:            draw a 565 format 16 bit raw image file
***************************************************************************************/

// This function opens a ".raw" image file and displays it at the given coordinates.
// It is faster than plotting BMP images as the file is already in the correct
// format to pipe directly to the display.
// Uses same BUFF_SIZE as BMP function.
// The width and hsight of the image in pixels must be passed to the function
// as these parameters are not in the file

void drawRAW(char *filename, int16_t x, int16_t y, int16_t rawWidth, int16_t rawHeight) {
  File     rawFile;
  uint8_t  sdbuffer[2 * BUFF_SIZE];   // SD read pixel buffer (16 bits per pixel)

  // Check file exists and open it
  if ((rawFile = SD.open(filename)) == NULL) {
    Serial.println(F("File not found"));
    return;
  }

  drawTime = millis(); // Save current time for performance evaluation

  tft.setAddrWindow(x, y, x + rawWidth - 1, y + rawHeight - 1);

  // Work out how many whole buffers to send
  uint16_t nr = ((long)rawHeight * rawWidth)/BUFF_SIZE;
  while(nr--) {
    rawFile.read(sdbuffer, sizeof(sdbuffer));
    tft.pushColors(sdbuffer, BUFF_SIZE);
  }
  
  // Send any partial buffer
  nr = ((long)rawHeight * rawWidth)%BUFF_SIZE;
  if (nr) {
    rawFile.read(sdbuffer, nr<<1); // We load  2 x BUFF_SIZE bytes
    tft.pushColors(sdbuffer, nr);      // We send BUF_SIZE pixels
  }
    
  drawTime = millis() - drawTime;
  rawFile.close();
}

/***************************************************************************************
** Function name:           Support functions for drawBMP()
** Descriptions:            Read 16- and 32-bit types from the SD card file
***************************************************************************************/

// BMP data is stored little-endian, Arduino is little-endian too.
// May need to reverse subscript order if porting elsewhere.

uint16_t read16(File& f) {
  uint16_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read(); // MSB
  return result;
}

uint32_t read32(File& f) {
  uint32_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read();
  ((uint8_t *)&result)[2] = f.read();
  ((uint8_t *)&result)[3] = f.read(); // MSB
  return result;
}


