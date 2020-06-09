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
#include"../../include/periferic18.h"

void
p18_eeprom_rst(void)
{
 pic->ee_wr = 0;
}

void
p18_eeprom(void)
{
 if (((*pic->P18map.EECON1) & 0x04) == 0x04)
  {
   if ((*pic->P18map.EECON2) != 0)
    {
     if ((*pic->P18map.EECON2) == 0x55)
      {
       (*pic->P18map.EECON2) = 0;
       pic->ee_wr = -1;
      }
     else
      {
       if (((*pic->P18map.EECON2) == 0xAA)&&(pic->ee_wr == -1))
        {
         (*pic->P18map.EECON2) = 0;
         pic->ee_wr = 1;
        }
       else
        {
         (*pic->P18map.EECON2) = 0;
         pic->ee_wr = 0;
        }
      }
    }
  }


 if (((*pic->P18map.EECON1) & 0x03) != 0x00)
  {
   if (((*pic->P18map.EECON1) & 0x01) == 0x01) //RD
    {
     if (((*pic->P18map.EECON1) & 0x80) == 0)
      {
       (*pic->P18map.EEDATA) = pic->eeprom[(*pic->P18map.EEADR)];
      }
     /*
           else
           {
              (*pic->P18map.EEDATA)=   (pic->prog[(pic->ram[P18_EEADRH]<<8)|(*pic->P18map.EEADR)])&0x00FF;
              pic->ram[P18_EEDATAH]= ((pic->prog[(pic->ram[P18_EEADRH]<<8)|(*pic->P18map.EEADR)])&0xFF00)>>8;
           }
      */
     (*pic->P18map.EECON1) &= ~0x01;
    }
   else
    {
     if (pic->ee_wr == 1)
      {
       if (((*pic->P18map.EECON1) & 0x80) == 0)
        {
         pic->eeprom[(*pic->P18map.EEADR)] = (*pic->P18map.EEDATA);
        }
       /*
               else
               {
                 pic->prog[(pic->ram[P18_EEADRH]<<8)|(*pic->P18map.EEADR)] = (pic->ram[P18_EEDATAH]<<8) | (*pic->P18map.EEDATA);

               }  
        */
       (*pic->P18map.EECON1) &= ~0x02;
       pic->ee_wr = 0;
      }
    }
  }
}



void
p18_eeprom_2(void)
{
 return;
 
 if (((*pic->P18map.NVMCON1) & 0x04) == 0x04)
  {
   if ((*pic->P18map.NVMCON2) != 0)
    {
     if ((*pic->P18map.NVMCON2) == 0x55)
      {
       (*pic->P18map.NVMCON2) = 0;
       pic->ee_wr = -1;
      }
     else
      {
       if (((*pic->P18map.NVMCON2) == 0xAA)&&(pic->ee_wr == -1))
        {
         (*pic->P18map.NVMCON2) = 0;
         pic->ee_wr = 1;
        }
       else
        {
         (*pic->P18map.NVMCON2) = 0;
         pic->ee_wr = 0;
        }
      }
    }
  }


 if (((*pic->P18map.NVMCON1) & 0x03) != 0x00)
  {
   if (((*pic->P18map.NVMCON1) & 0x01) == 0x01) //RD
    {
     if (((*pic->P18map.NVMCON1) & 0x80) == 0)
      {
       (*pic->P18map.NVMDAT) = pic->eeprom[((*pic->P18map.NVMADRH)<<8)|(*pic->P18map.NVMADRL)];
      }
     /*
           else
           {
              (*pic->P18map.EEDATA)=   (pic->prog[(pic->ram[P18_EEADRH]<<8)|(*pic->P18map.EEADR)])&0x00FF;
              pic->ram[P18_EEDATAH]= ((pic->prog[(pic->ram[P18_EEADRH]<<8)|(*pic->P18map.EEADR)])&0xFF00)>>8;
           }
      */
     (*pic->P18map.NVMCON1) &= ~0x01;
    }
   else
    {
     if (pic->ee_wr == 1)
      {
       if (((*pic->P18map.NVMCON1) & 0x80) == 0)
        {
         pic->eeprom[((*pic->P18map.NVMADRH)<<8)|(*pic->P18map.NVMADRL)] = (*pic->P18map.NVMDAT);
        }
       /*
               else
               {
                 pic->prog[(pic->ram[P18_EEADRH]<<8)|(*pic->P18map.EEADR)] = (pic->ram[P18_EEDATAH]<<8) | (*pic->P18map.EEDATA);

               }  
        */
       (*pic->P18map.NVMCON1) &= ~0x02;
       pic->ee_wr = 0;
      }
    }
  }
}