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

extern const int fpw2[];

void
p18_tmr0_rst(void)
{
 pic->cp0 = 0;
}

void
p18_tmr0(void)
{
 if (pic->P18map.T0CON)
  {
   if ((*pic->P18map.T0CON) & 0x80) //TMR0ON
    {
     if ((((*pic->P18map.T0CON) & 0x20) == 0x00) || //TOCS=FOSC/4
         ((((*pic->P18map.T0CON) & 0x30) == 0x20)&&((pic->t0cki_ == 0)&&(pic->pins[pic->t0cki - 1].value == 1))) || //T0CS=t0cki  T0SE =0
         ((((*pic->P18map.T0CON) & 0x30) == 0x30)&&((pic->t0cki_ == 1)&&(pic->pins[pic->t0cki - 1].value == 0)))) //T0CS=t0cki  T0SE =1
      {
       pic->cp0++;

       if (pic->lram == sfr_addr (pic->P18map.TMR0L))pic->cp0 = 0; //RESET prescaler	 

       if (((*pic->P18map.T0CON) & 0x08) == 0x08) //PSA
        {

         if (((*pic->P18map.T0CON) & 0x40)&& (((*pic->P18map.TMR0L) + 1) == 0x100))(*pic->P18map.INTCON) |= 0x04; //T0IF

         (*pic->P18map.TMR0L)++;
         if ((!(*pic->P18map.TMR0L))&&(!((*pic->P18map.T0CON) & 0x40)))
          {
           if (((*pic->P18map.TMR0H) + 1) == 0x100)(*pic->P18map.INTCON) |= 0x04; //T0IF
           (*pic->P18map.TMR0H)++;
          }
         pic->cp0 = 0;
        }
       else
        {
         if (pic->cp0 >= 2 * (fpw2[(*pic->P18map.T0CON)&0x07]))
          {

           if (((*pic->P18map.T0CON) & 0x40)&& (((*pic->P18map.TMR0L) + 1) == 0x100))(*pic->P18map.INTCON) |= 0x04; //T0IF

           (*pic->P18map.TMR0L)++;
           if ((!(*pic->P18map.TMR0L))&&(!((*pic->P18map.T0CON) & 0x40)))
            {
             if (((*pic->P18map.TMR0H) + 1) == 0x100)(*pic->P18map.INTCON) |= 0x04; //T0IF
             (*pic->P18map.TMR0H)++;
            }
           pic->cp0 = 0;
          }
        }
      }
    }
   pic->t0cki_ = pic->pins[pic->t0cki - 1].value;
  }
}

void
p18_tmr0_2(void)
{
 if (pic->P18map.T0CON0)
  {
   if ((*pic->P18map.T0CON0) & 0x80) //T0EN
    {
     if ((((*pic->P18map.T0CON1) & 0xE0) == 0x40) || //TOCS=FOSC/4
         ((((*pic->P18map.T0CON1) & 0xE0) == 0x00)&&((pic->t0cki_ == 0)&&(pic->pins[pic->t0cki - 1].value == 1))) || //T0CS=t0cki  
         ((((*pic->P18map.T0CON1) & 0xE0) == 0x20)&&((pic->t0cki_ == 1)&&(pic->pins[pic->t0cki - 1].value == 0)))) //T0CS=t0cki  
      {
       pic->cp0++;

       if (pic->lram == sfr_addr (pic->P18map.TMR0L))pic->cp0 = 0; //RESET prescaler	 


       if (pic->cp0 >= 2 * (fpw2[(*pic->P18map.T0CON1)&0x0F]))
        {

         (*pic->P18map.TMR0L)++;
                  
         //8 bit mode
         if (!((*pic->P18map.T0CON0) & 0x10) && ((*pic->P18map.TMR0H) == (*pic->P18map.TMR0L)))
          {
           (*pic->P18map.PIR0) |= 0x20; //TMR0IF
           (*pic->P18map.TMR0L)=0;
           //TODO buffer TMR0H writes
          }

         //16 bit mode;
         if ((!(*pic->P18map.TMR0L))&&(((*pic->P18map.T0CON0) & 0x10)))
          {
           if (((*pic->P18map.TMR0H) + 1) == 0x100)(*pic->P18map.PIR0) |= 0x20; //TMR0IF
           (*pic->P18map.TMR0H)++;
          }
         pic->cp0 = 0;
        }
       //TODO implement postscaler
      }
    }
   pic->t0cki_ = pic->pins[pic->t0cki - 1].value;
  }
}