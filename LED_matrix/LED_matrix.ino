#include <LedControlMS.h>

 //pin 4 is connected to the DataIn

// pin 3 is connected to the CLK

 //pin 2 is connected to LOAD

 

#define NBR_MTX 1 //number of matrices attached is one

LedControl lc=LedControl(4,3,2, NBR_MTX);//

 

void setup()

{

  for (int i=0; i< NBR_MTX; i++)

  {

    lc.shutdown(i,false);

  /* Set the brightness to a medium values */

    lc.setIntensity(i,8);

  /* and clear the display */

    lc.clearDisplay(i);

                delay(100);

  }

}

 

void loop()

{

                  lc.writeString(0,"CIRCUITDIGEST");//sending characters to display

                  lc.clearAll();//clearing the display

                  delay(1000);

}
