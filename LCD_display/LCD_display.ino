#include<LiquidCrystal.h>
LiquidCrystal lcd (A0, A1, A2, A3, A4, A5); 
void setup()
{
  lcd.setCursor(0, 0);
  lcd.print("Welcome");
  lcd.setCursor(0, 1);
  lcd.print("Enter Password");
}
void loop()
{
  
}

