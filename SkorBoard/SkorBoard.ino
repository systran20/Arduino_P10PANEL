#include <DMD.h>
#include <TimerOne.h>
#include "SystemFont5x7.h"
#include "Arial_black_16.h"

#define DISPLAYS_ACROSS 3
#define DISPLAYS_DOWN 1
DMD dmd(DISPLAYS_ACROSS, DISPLAYS_DOWN);

void ScanDMD()
{ 
  dmd.scanDisplayBySPI();
}

void setup(void)
{
   Timer1.initialize( 4000 );
   Timer1.attachInterrupt( ScanDMD );
   dmd.clearScreen( true );
}

void loop(void)
{
   byte b;
   dmd.selectFont(Arial_16);
   dmd.drawMarquee("   https://nevsehirfenlisesi.meb.k12.tr   ",39,(32*DISPLAYS_ACROSS)-1,0);
   long start=millis();
   long timer=start;
   boolean ret=false;
   while(!ret){
     if ((timer+30) < millis()) {
       ret=dmd.stepMarquee(-1,0);
       timer=millis();
     }
   }

   
   // bir yazıyı tek ekranda 2 satır olarak görüntüle
   dmd.clearScreen( true );
   dmd.selectFont(System5x7);
   for (byte x=0;x<DISPLAYS_ACROSS;x++) {
     for (byte y=0;y<DISPLAYS_DOWN;y++) {
       dmd.drawString(  2+(32*x),  1+(16*y), "EMIR", 5, GRAPHICS_NORMAL );
       dmd.drawString(  2+(32*x),  9+(16*y), "ONUGOREN", 5, GRAPHICS_NORMAL );
     }
   }
   delay( 2000 );
   
   // ekranın dışına bir çerçeve çiz
   dmd.clearScreen( true );
   dmd.drawBox(  0,  0, (32*DISPLAYS_ACROSS)-1, (16*DISPLAYS_DOWN)-1, GRAPHICS_NORMAL );
   delay( 1000 );
   
   for (byte y=0;y<DISPLAYS_DOWN;y++) {
     for (byte x=0;x<DISPLAYS_ACROSS;x++) {
       // bir X çiz
       int ix=32*x;
       int iy=16*y;
       dmd.drawLine(  0+ix,  0+iy, 11+ix, 15+iy, GRAPHICS_NORMAL );
       dmd.drawLine(  0+ix, 15+iy, 11+ix,  0+iy, GRAPHICS_NORMAL );
       delay( 1000 );
   
       // bir daire çiz
       dmd.drawCircle( 16+ix,  8+iy,  5, GRAPHICS_NORMAL );
       delay( 1000 );
   
       // içi dolu bir kutu çiz
       dmd.drawFilledBox( 24+ix, 3+iy, 29+ix, 13+iy, GRAPHICS_NORMAL );
       delay( 1000 );
     }
   }

   // şerit kovalayan testi
   for( b = 0 ; b < 20 ; b++ )
   {
      dmd.drawTestPattern( (b&1)+PATTERN_STRIPE_0 );
      delay( 200 );      
   }
   delay( 200 );      
}
