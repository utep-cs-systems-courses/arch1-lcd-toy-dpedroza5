#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"

u_char stringRow = 5;
u_char nextStringRow = 5;
signed char Velocity = 1;

short redrawScreen = 1;
u_int fontFgColor = COLOR_GREEN;

void wdt_c_handler() //animates the string vertically
{
  static int secCount = 0;
  static int dsecCount = 0; 

  secCount ++;
  dsecCount ++;
  if (secCount == 250) {		/* once/sec */
    secCount = 0;
    fontFgColor = (fontFgColor == COLOR_RED) ? COLOR_GREEN : COLOR_RED;
    redrawScreen = 1;
  }
  if (dsecCount == 25) {
    dsecCount = 0;
    nextStringRow += Velocity;
    if (nextStringRow > 20 || nextStringRow <= 5){
      Velocity = -Velocity;
      nextStringRow += Velocity;
    }
    redrawScreen = 1;
  }
}

/** Initializes everything, clears the screen, draws "My project" and a sword */
int
main()
{
  configureClocks();
  lcd_init();
  u_char width = screenWidth, height = screenHeight;

  clearScreen(COLOR_BLACK);
  while (1) {			/* forever */
    if (redrawScreen) {
      redrawScreen = 0;
      drawString5x7(5,stringRow, "My Project", COLOR_BLACK, COLOR_BLACK);
      drawString5x7(5,nextStringRow, "My Project", fontFgColor, COLOR_BLACK);
      stringRow = nextStringRow;
   
      //creates a sword
      RightFacingTriangle(9,9,100,100);
      fillRectangle(50,80,50,20, COLOR_BROWN);
      fillRectangle(45,70,5,40, COLOR_GREEN);
      fillRectangle(40,80,5,20, COLOR_ORANGE);
      fillRectangle(35,80,5,20, COLOR_GREEN);
      fillRectangle(30,80,5,20, COLOR_ORANGE);
      fillRectangle(25,80,5,20, COLOR_GREEN);
      fillRectangle(40,70,5,5, COLOR_GREEN);
      fillRectangle(40,105,5,5, COLOR_GREEN);
    }
  }
}
