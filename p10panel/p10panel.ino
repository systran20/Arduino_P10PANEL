#include <DMD.h>
#include <TimerOne.h>
//#include "SystemFont5x7.h"
#include "Arial_black_16.h"
#include "fonts/Droid_sans_16.h"

#define DISPLAYS_ACROSS 3
#define DISPLAYS_DOWN 1
DMD dmd(DISPLAYS_ACROSS, DISPLAYS_DOWN);
int buttonPinA=2;
int buttonPinB=3;
int resetPinA=5;
int resetPinB=4;

int golPin = 12;

int sayac=0;
int skorA =0;
int skorB =0;

char dataA[16];
char dataB[16];

void ScanDMD()
{ 
  dmd.scanDisplayBySPI();
}

void setup(void)
{
    
   Timer1.initialize( 3500 );
   Timer1.attachInterrupt( ScanDMD );
   dmd.clearScreen( true );
   //Serial.begin(9600);  
   pinMode(buttonPinA,INPUT_PULLUP);
   pinMode(buttonPinB,INPUT_PULLUP);
   pinMode(resetPinA,INPUT_PULLUP);
   pinMode(resetPinB,INPUT_PULLUP);   
   pinMode(golPin, INPUT_PULLUP);
   

   
}
void loop(void)
{   
   //dmd.clearScreen( true );
   //dmd.selectFont(SystemFont5x7);   
   //dmd.selectFont(Arial_Black_16);   
   dmd.selectFont(Droid_Sans_16);   
   sprintf(dataA , "%2d" , skorA);
   sprintf(dataB , "%2d" , skorB); 
   
  // itoa(skorB, cstrB, 10);    
   
   dmd.drawString(0,0, "11-B", 4, GRAPHICS_NORMAL );
   dmd.drawString(0+28,0, dataA , 2,GRAPHICS_NORMAL);
   dmd.drawString(50,0, "10-A", 4, GRAPHICS_NORMAL );
   dmd.drawString(52+28,0, dataB, 2,GRAPHICS_NORMAL);

   if (digitalRead(buttonPinA)==LOW) {
     sayac=0;
     while(digitalRead(buttonPinA)==LOW) {}     
     dmd.clearScreen( true );
     skorA++;      
     if (skorA>99) {skorA=0;}
   }
   if (digitalRead(buttonPinB)==LOW) {
     sayac=0;
     while(digitalRead(buttonPinB)==LOW) {}
     dmd.clearScreen( true );
     skorB++;      
     if (skorB>99) {skorB=0;}
   }     
   if (digitalRead(resetPinA)==LOW) {
     sayac=0;
     while(digitalRead(resetPinA)==LOW) {}
     dmd.clearScreen( true );
     skorA=0;     
   }
   
   if (digitalRead(resetPinB)==LOW) {
     sayac=0;
     while(digitalRead(resetPinB)==LOW) {}
     dmd.clearScreen( true );
     skorB=0;     
   }  
   if (sayac>1500) {
    dmd.clearScreen(true);
    drawScrollText("NEVSEHIR FEN LISESI 2019...");    
    sayac=0;    
   }
   if (digitalRead(golPin)==LOW) {
    sayac=0;
    while(digitalRead(golPin)==LOW) {}
    dmd.clearScreen(true);
    drawScrollText("GOOOOOOOOOOL !!!");
    
   }   
   sayac++;     
}


void drawScrollText( String dispString ) 
{
  //dmd.clearScreen( true );
  dmd.selectFont(Arial_Black_16);
  char newString[256];
  int sLength = dispString.length();
  dispString.toCharArray( newString, sLength+1 );
  dmd.drawMarquee( newString , sLength , ( 32*DISPLAYS_ACROSS )-1 ,0);
  long start=millis();
  long timer=start;
  long timer2=start;
  boolean ret=false;
  while( !ret ){
    if ( ( timer+16 ) < millis() ) {
      ret=dmd.stepMarquee( -1 , 0 );
      timer=millis();
    }
  }
}
