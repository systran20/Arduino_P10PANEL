#include "SPI.h"        
#include "DMD.h"        
#include "TimerOne.h"
#include "Arial_black_16.h" 
/* you can remove the fonts if unused */
#define DISPLAYS_ACROSS 3
#define DISPLAYS_DOWN 1
const byte butonPin = 2;    //2 nolu port, 0 nolu kesmeye karşılık geliyor
volatile byte state = LOW;  //volatile ???
volatile byte sayac=0;

DMD dmd( DISPLAYS_ACROSS , DISPLAYS_DOWN );

void ScanDMD()
{    
  pinMode(butonPin, INPUT_PULLUP);
  //attachInterrupt(digitalPinToInterrupt(butonPin), blink, CHANGE);
  attachInterrupt(digitalPinToInterrupt(butonPin), blink, CHANGE);
  dmd.scanDisplayBySPI();
}

void setup()
{
   Timer1.initialize( 1000 );           
   Timer1.attachInterrupt( ScanDMD );  
   dmd.clearScreen( true );            
}

//String textToScroll="... NEVSEHIR FEN LISESI 2019 ...";

void drawScrollText( String dispString ) 
{
  dmd.clearScreen( true );
  dmd.selectFont( Arial_Black_16 );
  char newString[256];
  int sLength = dispString.length();
  dispString.toCharArray( newString, sLength+1 );
  dmd.drawMarquee( newString , sLength , ( 32*DISPLAYS_ACROSS )-1 ,0);
  long start=millis();
  long timer=start;
  long timer2=start;
  boolean ret=false;
  while( !ret ){
    if ( ( timer+20 ) < millis() ) {
      ret=dmd.stepMarquee( -1 , 0 );
      timer=millis();
    }
  }
}

void drawText( String dispString ) 
{
  //dmd.clearScreen( true );
  dmd.selectFont( Arial_Black_16 );  
  char newString[256];
  int sLength = dispString.length();  
  dispString.toCharArray( newString, sLength+1 );
  dmd.drawString( 10,0 , newString , 10 , GRAPHICS_NORMAL);  
  
}


void loop()
{
  drawText(String(sayac));
  //drawText(textToScroll + state);
  //drawScrollText(String(sayac));
  
}

void blink() {
  //state = !state;
  sayac++;
}
