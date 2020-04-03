/* ########################################################################

   PICsim - PIC simulator

   ########################################################################

   Copyright (c) : 2019-2020  Luis Claudio Gamboa Lopes

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

   For e-mail suggestions :  lcgamboa@yahoo.com
   ######################################################################## */

#include<stdio.h>
#include"../../include/picsim.h"
#include"../../include/periferic16.h"

void
p16e_eeprom_rst(void) 
{
 pic->ee_wr = 0;
   //FIXME	
  printf ("Incomplete: %s -> %s :%i\n", __func__,__FILE__, __LINE__);
}

void
p16e_eeprom(void)
{
  //FIXME	
  printf ("Incomplete: %s -> %s :%i\n", __func__,__FILE__, __LINE__);
 /*
 //EEPROM

 if((pic->processor == P16F628)||(pic->processor == P16F628A))
 {
   if((pic->ram[P16E_P628_EECON1] & 0x04) == 0x04 )
   {
     if(pic->ram[P16E_P628_EECON2] != 0 )
     {
       if(pic->ram[P16E_P628_EECON2] == 0x55 )
       {
         pic->ram[P16E_P628_EECON2] = 0; 
         pic->ee_wr=-1;
       }
       else
       {
         if((pic->ram[P16E_P628_EECON2] == 0xAA )&&(pic->ee_wr == -1))
         {
           pic->ram[P16E_P628_EECON2] = 0; 
           pic->ee_wr=1;
         }
         else
         {
           pic->ram[P16E_P628_EECON2] = 0; 
           pic->ee_wr=0;
         }
       }
     }    
   }

   if((pic->ram[P16E_P628_EECON1] & 0x03) != 0x00 )
   {
     if((pic->ram[P16E_P628_EECON1] & 0x01) == 0x01 ) //RD
     {
       pic->ram[P16E_P628_EEDATA]= pic->eeprom[pic->ram[P16E_P628_EEADR]];
       pic->ram[P16E_P628_EECON1]&=~0x01;  
     }
     else
     {
       if(pic->ee_wr == 1)
       {
         pic->eeprom[pic->ram[P16E_P628_EEADR]]=pic->ram[P16E_P628_EEDATA];       
         pic->ram[P16E_P628_EECON1]&=~0x02; 
         pic->ee_wr=0;
       } 
     }
   } 
 }
 else if((pic->processor == P16F877)||(pic->processor == P16F877A))
 {

   if((pic->ram[P16E_P877_EECON1] & 0x04) == 0x04 )
   {
     if(pic->ram[P16E_P877_EECON2] != 0 )
     {
       if(pic->ram[P16E_P877_EECON2] == 0x55 )
       {
         pic->ram[P16E_P877_EECON2] = 0; 
         pic->ee_wr=-1;
       }
       else
       {
         if((pic->ram[P16E_P877_EECON2] == 0xAA )&&(pic->ee_wr == -1))
         {
           pic->ram[P16E_P877_EECON2] = 0; 
           pic->ee_wr=1;
         }
         else
         {
           pic->ram[P16E_P877_EECON2] = 0; 
           pic->ee_wr=0;
         }
       }
     }    
   }



   if((pic->ram[P16E_P877_EECON1] & 0x03) != 0x00 )
   {
     if((pic->ram[P16E_P877_EECON1] & 0x01) == 0x01 ) //RD
     { 
       if((pic->ram[P16E_P877_EECON1] & 0x80) == 0)
       {  
          pic->ram[P16E_P877_EEDATA]= pic->eeprom[pic->ram[P16E_P877_EEADR]];
       }
       else
       {
          pic->ram[P16E_P877_EEDATA]=   (pic->prog[(pic->ram[P16E_P877_EEADRH]<<8)|pic->ram[P16E_P877_EEADR]])&0x00FF;
          pic->ram[P16E_P877_EEDATAH]= ((pic->prog[(pic->ram[P16E_P877_EEADRH]<<8)|pic->ram[P16E_P877_EEADR]])&0xFF00)>>8;
   //       printf("Reading %04X=%04X\n",(pic->ram[P877_EEADRH]<<8)|pic->ram[P877_EEADR],(pic->ram[P877_EEDATAH]<<8) | pic->ram[P877_EEDATA]);
       }
       pic->ram[P16E_P877_EECON1]&=~0x01;  
     }
     else
     {
       if(pic->ee_wr == 1)
       {
         if((pic->ram[P16E_P877_EECON1] & 0x80) == 0)
         { 
           pic->eeprom[pic->ram[P16E_P877_EEADR]]=pic->ram[P16E_P877_EEDATA];
         }
         else
         {
           pic->prog[(pic->ram[P16E_P877_EEADRH]<<8)|pic->ram[P16E_P877_EEADR]] = (pic->ram[P16E_P877_EEDATAH]<<8) | pic->ram[P16E_P877_EEDATA];

     //      printf("Writing %04X=%04X\n",(pic->ram[P877_EEADRH]<<8)|pic->ram[P877_EEADR],(pic->ram[P877_EEDATAH]<<8) | pic->ram[P877_EEDATA]);
         }       
         pic->ram[P16E_P877_EECON1]&=~0x02; 
         pic->ee_wr=0;
       } 
     }
   } 
 }
  */
}