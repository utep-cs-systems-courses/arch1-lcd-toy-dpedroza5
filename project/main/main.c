#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "switches.h"
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
  if (secCount == 250) {
    secCount = 0;
    fontFgColor = (fontFgColor == COLOR_GREEN) ? COLOR_RED : COLOR_GREEN;
    redrawScreen = 1;
  }
  if (dsecCount == 25) {
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
  P1DIR |= LED_GREEN;/**< Green led on when CPU on */
  P1OUT |= LED_GREEN;
  configureClocks();
  lcd_init();

  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);              /**< GIE (enable interrupts) */

  clearScreen(COLOR_BLACK);
  while (1) {/* forever */
    if (redrawScreen) {
      redrawScreen = 0;

      switch_init();
      if (switch1_state_down){
	state1();
      }
      else if (switch2_state_down){
	state2();
      }
      else if (switch3_state_down){
	state3();
      }
      else if (switch4_state_down){
	state4();
      }
      else{
	clearScreen(COLOR_BLACK);
      }

      stringOffset = nextStringOffset;
    }
    P1OUT &= ~LED_GREEN;/* green off */
    or_sr(0x10);/**< CPU OFF */
    P1OUT |= LED_GREEN;/* green on */
  }
}

void state1() //creates the font
{
  drawString11x16(5,stringOffset, "My Project", COLOR_BLACK, COLOR_BLACK);
  drawString11x16(5,nextStringOffset, "My Project", fontFgColor, COLOR_BLACK);
  fillRectangle(60,55,10,5, COLOR_BROWN);
  fillRectangle(55,60,20,50, COLOR_BROWN);
  fillRectangle(45,110,40,5, COLOR_GREEN);
  fillRectangle(55,115,20,5, COLOR_ORANGE);
  fillRectangle(55,120,20,5, COLOR_GREEN);
  fillRectangle(55,125,20,5, COLOR_ORANGE);
  fillRectangle(55,130,20,5, COLOR_GREEN);
  fillRectangle(45,115,5,5, COLOR_GREEN);
  fillRectangle(80,115,5,5, COLOR_GREEN);
}

void state2() //creates the sword
{
  fillRectangle(100+stringOffset,85,5,10, COLOR_BLACK);
  fillRectangle(50+stringOffset,80,50,20, COLOR_BLACK);
  fillRectangle(45+stringOffset,70,5,40, COLOR_BLACK);
  fillRectangle(40+stringOffset,80,5,20, COLOR_BLACK);
  fillRectangle(35+stringOffset,80,5,20, COLOR_BLACK);
  fillRectangle(30+stringOffset,80,5,20, COLOR_BLACK);
  fillRectangle(25+stringOffset,80,5,20, COLOR_BLACK);
  fillRectangle(40+stringOffset,70,5,5, COLOR_BLACK);
  fillRectangle(40+stringOffset,105,5,5, COLOR_BLACK);
      
  fillRectangle(100+nextStringOffset,85,5,10, COLOR_BROWN);
  fillRectangle(50+nextStringOffset,80,50,20, COLOR_BROWN);
  fillRectangle(45+nextStringOffset,70,5,40, COLOR_GREEN);
  fillRectangle(40+nextStringOffset,80,5,20, COLOR_ORANGE);
  fillRectangle(35+nextStringOffset,80,5,20, COLOR_GREEN);
  fillRectangle(30+nextStringOffset,80,5,20, COLOR_ORANGE);
  fillRectangle(25+nextStringOffset,80,5,20, COLOR_GREEN);
  fillRectangle(40+nextStringOffset,70,5,5, COLOR_GREEN);
  fillRectangle(40+nextStringOffset,105,5,5, COLOR_GREEN);
}

void state3() //rotates the sword down
{
  fillRectangle(60,130+stringOffset,10,5, COLOR_BLACK);
  fillRectangle(55,80+stringOffset,20,50, COLOR_BLACK);
  fillRectangle(45,75+stringOffset,40,5, COLOR_BLACK);
  fillRectangle(55,70+stringOffset,20,5, COLOR_BLACK);
  fillRectangle(55,65+stringOffset,20,5, COLOR_BLACK);
  fillRectangle(55,60+stringOffset,20,5, COLOR_BLACK);
  fillRectangle(55,55+stringOffset,20,5, COLOR_BLACK);
  fillRectangle(45,70+stringOffset,5,5, COLOR_BLACK);
  fillRectangle(80,70+stringOffset,5,5, COLOR_BLACK);
      
  fillRectangle(60,130+nextStringOffset,10,5, COLOR_BROWN);
  fillRectangle(55,80+nextStringOffset,20,50, COLOR_BROWN);
  fillRectangle(45,75+nextStringOffset,40,5, COLOR_GREEN);
  fillRectangle(55,70+nextStringOffset,20,5, COLOR_ORANGE);
  fillRectangle(55,65+nextStringOffset,20,5, COLOR_GREEN);
  fillRectangle(55,60+nextStringOffset,20,5, COLOR_ORANGE);
  fillRectangle(55,55+nextStringOffset,20,5, COLOR_GREEN);
  fillRectangle(45,70+nextStringOffset,5,5, COLOR_GREEN);
  fillRectangle(80,70+nextStringOffset,5,5, COLOR_GREEN);
}

void state4() //mirrors the sword
{
  fillRectangle(25-stringOffset,85,5,10, COLOR_BLACK);
  fillRectangle(30-stringOffset,80,50,20, COLOR_BLACK);
  fillRectangle(80-stringOffset,70,5,40, COLOR_BLACK);
  fillRectangle(85-stringOffset,80,5,20, COLOR_BLACK);
  fillRectangle(90-stringOffset,80,5,20, COLOR_BLACK);
  fillRectangle(95-stringOffset,80,5,20, COLOR_BLACK);
  fillRectangle(100-stringOffset,80,5,20, COLOR_BLACK);
  fillRectangle(85-stringOffset,70,5,5, COLOR_BLACK);
  fillRectangle(85-stringOffset,105,5,5, COLOR_BLACK);
      
  fillRectangle(25-nextStringOffset,85,5,10, COLOR_BROWN);
  fillRectangle(30-nextStringOffset,80,50,20, COLOR_BROWN);
  fillRectangle(80-nextStringOffset,70,5,40, COLOR_GREEN);
  fillRectangle(85-nextStringOffset,80,5,20, COLOR_ORANGE);
  fillRectangle(90-nextStringOffset,80,5,20, COLOR_GREEN);
  fillRectangle(95-nextStringOffset,80,5,20, COLOR_ORANGE);
  fillRectangle(100-nextStringOffset,80,5,20, COLOR_GREEN);
  fillRectangle(85-nextStringOffset,70,5,5, COLOR_GREEN);
  fillRectangle(85-nextStringOffset,105,5,5, COLOR_GREEN);
}
