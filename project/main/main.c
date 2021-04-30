#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"

#define LED_GREEN BIT6             // P1.6

u_char stringOffset = 5;
u_char nextStringOffset = 5;
signed char Velocity = 1;

short redrawScreen = 1;
u_int fontFgColor = COLOR_GREEN;

void wdt_c_handler()
{
  static int secCount = 0;
  static int dsecCount = 0; 

  secCount ++;
  dsecCount ++;
  if (secCount == 250) {		/* once/sec */
    secCount = 0;
    fontFgColor = (fontFgColor == COLOR_GREEN) ? COLOR_RED : COLOR_GREEN;
    redrawScreen = 1;
  }
  if (dsecCount == 50) { //5 times/sec
    dsecCount = 0;
    nextStringOffset += Velocity;
    if (nextStringOffset > 20 || nextStringOffset <= 5){
      Velocity = -Velocity;
      nextStringOffset += Velocity;
    }
    redrawScreen = 1;
  }
}
  

void main()
{
  P1DIR |= LED_GREEN;		/**< Green led on when CPU on */		
  P1OUT |= LED_GREEN;
  configureClocks();
  lcd_init();
  
  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);	              /**< GIE (enable interrupts) */
  
  clearScreen(COLOR_BLACK);
  while (1) {			/* forever */
    if (redrawScreen) {
      redrawScreen = 0;
      drawString11x16(5,stringOffset, "My Project", COLOR_BLACK, COLOR_BLACK);
      drawString11x16(5,nextStringOffset, "My Project", fontFgColor, COLOR_BLACK);
      
      //creates a sword
      //RightFacingTriangle(9,9,100,100+stringOffset, COLOR_BLACK);
      fillRectangle(100+stringOffset,85,5,10, COLOR_BLACK);
      fillRectangle(50+stringOffset,80,50,20, COLOR_BLACK);
      fillRectangle(45+stringOffset,70,5,40, COLOR_BLACK);
      fillRectangle(40+stringOffset,80,5,20, COLOR_BLACK);
      fillRectangle(35+stringOffset,80,5,20, COLOR_BLACK);
      fillRectangle(30+stringOffset,80,5,20, COLOR_BLACK);
      fillRectangle(25+stringOffset,80,5,20, COLOR_BLACK);
      fillRectangle(40+stringOffset,70,5,5, COLOR_BLACK);
      fillRectangle(40+stringOffset,105,5,5, COLOR_BLACK);

      //RightFacingTriangle(9,9,100,100+nextStringOffset, COLOR_BROWN);
      fillRectangle(100+nextStringOffset,85,5,10, COLOR_BROWN);
      fillRectangle(50+nextStringOffset,80,50,20, COLOR_BROWN);
      fillRectangle(45+nextStringOffset,70,5,40, COLOR_GREEN);
      fillRectangle(40+nextStringOffset,80,5,20, COLOR_ORANGE);
      fillRectangle(35+nextStringOffset,80,5,20, COLOR_GREEN);
      fillRectangle(30+nextStringOffset,80,5,20, COLOR_ORANGE);
      fillRectangle(25+nextStringOffset,80,5,20, COLOR_GREEN);
      fillRectangle(40+nextStringOffset,70,5,5, COLOR_GREEN);
      fillRectangle(40+nextStringOffset,105,5,5, COLOR_GREEN);

      stringOffset = nextStringOffset;
    }
    P1OUT &= ~LED_GREEN;	/* green off */
    or_sr(0x10);		/**< CPU OFF */
    P1OUT |= LED_GREEN;		/* green on */
  }
}

    
    



