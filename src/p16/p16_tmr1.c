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

extern const int fpw2[];

void
p16_tmr1_rst(void)
{
 pic->cp1 = 0;

 for (int i = 0; i < pic->CCPCOUNT; i++)
  {
   pic->ccp[i].ovalue = pic->pins[(pic->ccp[i].pin - 1)].value;
   pic->ccp[i].cap_ps = 0;
  }
}

void
p16_tmr1(void)
{
 if ((((*pic->P16map.T1CON) & 0x03) == 0x01) || //TMRICS=FOSC/4 TMREN=1
     ((((*pic->P16map.T1CON) & 0x03) == 0x03)&&((pic->t1cki_ == 0)&&(pic->pins[pic->t1cki - 1].value == 1)))) //TMRICS=t1cki  TMREN=1
  {
   pic->cp1++;

   if (pic->cp1 >= fpw2[((*pic->P16map.T1CON)&0x30) >> 4])
    {
     (*pic->P16map.TMR1L)++;
     if ((*pic->P16map.TMR1L) == 0)
      {
       if (((*pic->P16map.TMR1H) + 1) == 0x100)(*pic->P16map.PIR1) |= 0x01; //TMR1IF
       (*pic->P16map.TMR1H)++;
      }
     pic->cp1 = 0;
    }

   //CCP - only when TMR1 is ON
   //CCP1 compare modes 
   if (((pic->CCPCOUNT >= 1)&&(pic->ccp[0].pin > 0))&&((*pic->P16map.CCP1CON) & 0x0C) == 0x08)
    {
     if (((*pic->P16map.TMR1H) == (*pic->P16map.CCPR1H))&&((*pic->P16map.TMR1L) == (*pic->P16map.CCPR1L)))//match !!
      {
       (*pic->P16map.PIR1) |= 0x04; //CCP1IF
       switch ((*pic->P16map.CCP1CON) & 0x03)
        {
        case 0://set output
         if (pic->pins[pic->ccp[0].pin - 1].dir == PD_OUT)
          (*pic->pins[(pic->ccp[0].pin - 1)].port) |= 0x01 << (pic->pins[(pic->ccp[0].pin - 1)].pord);
         break;
        case 1://clear output
         if (pic->pins[pic->ccp[0].pin - 1].dir == PD_OUT)
          (*pic->pins[(pic->ccp[0].pin - 1)].port) &= ~(0x01 << (pic->pins[(pic->ccp[0].pin - 1)].pord));
         break;
        case 2://software interrupt
         break;
        case 3://trigger special event
         (*pic->P16map.TMR1H) = 0;
         (*pic->P16map.TMR1L) = 0;
         break;
        }
      }
    }

   //CCP2 compare modes 
   if ((pic->CCPCOUNT >= 2)&&(pic->ccp[1].pin > 0)&&(((*pic->P16map.CCP2CON) & 0x0C) == 0x08))
    {
     if (((*pic->P16map.TMR1H) == (*pic->P16map.CCPR2H))&&((*pic->P16map.TMR1L) == (*pic->P16map.CCPR2L)))//match !!
      {
       (*pic->P16map.PIR2) |= 0x01; //CCP2IF
       switch ((*pic->P16map.CCP2CON) & 0x03)
        {
        case 0://set output
         if (pic->pins[pic->ccp[1].pin - 1].dir == PD_OUT)
          (*pic->pins[(pic->ccp[1].pin - 1)].port) |= 0x01 << (pic->pins[(pic->ccp[1].pin - 1)].pord);
         break;
        case 1://clear output
         if (pic->pins[pic->ccp[1].pin - 1].dir == PD_OUT)
          (*pic->pins[(pic->ccp[1].pin - 1)].port) &= ~(0x01 << (pic->pins[(pic->ccp[1].pin - 1)].pord));
         break;
        case 2://software interrupt
         break;
        case 3://trigger special event
         (*pic->P16map.TMR1H) = 0;
         (*pic->P16map.TMR1L) = 0;
         if ((*pic->P16map.ADCON0) & 0x01)(*pic->P16map.ADCON0) |= 0x04; //if ad on, enable one conversion
         break;
        }
      }
    }

   //CCP3 compare modes 
   if ((pic->CCPCOUNT >= 3)&&(pic->ccp[2].pin > 0)&&(((*pic->P16map.CCP3CON) & 0x0C) == 0x08))
    {
     if (((*pic->P16map.TMR1H) == (*pic->P16map.CCPR3H))&&((*pic->P16map.TMR1L) == (*pic->P16map.CCPR3L)))//match !!
      {
       (*pic->P16map.PIR2) |= 0x02; //CCP3IF
       switch ((*pic->P16map.CCP3CON) & 0x03)
        {
        case 0://set output
         if (pic->pins[pic->ccp[2].pin - 1].dir == PD_OUT)
          (*pic->pins[(pic->ccp[2].pin - 1)].port) |= 0x01 << (pic->pins[(pic->ccp[2].pin - 1)].pord);
         break;
        case 1://clear output
         if (pic->pins[pic->ccp[2].pin - 1].dir == PD_OUT)
          (*pic->pins[(pic->ccp[2].pin - 1)].port) &= ~(0x01 << (pic->pins[(pic->ccp[2].pin - 1)].pord));
         break;
        case 2://software interrupt
         break;
        case 3://trigger special event
         (*pic->P16map.TMR1H) = 0;
         (*pic->P16map.TMR1L) = 0;
         break;
        }
      }
    }
  }

 pic->t1cki_ = pic->pins[pic->t1cki - 1].value;

 //CCP CAPTURE
 if (((*pic->P16map.T1CON) & 0x01) == 0x01) // TMREN=1
  {
   if ((pic->CCPCOUNT >= 1)&&(pic->ccp[0].pin > 0))
    {
     if (((*pic->P16map.CCP1CON) & 0x0C) == 0x04)//CAPTURE MODE
      {
       if (pic->pins[pic->ccp[0].pin - 1].value != pic->ccp[0].ovalue)//pin state change
        {
         switch ((*pic->P16map.CCP1CON) & 0x03)
          {
          case 0://Every falling edge
           if (pic->ccp[0].ovalue == 1)
            {
             (*pic->P16map.PIR1) |= 0x04; //CCP1IF
             (*pic->P16map.CCPR1H) = (*pic->P16map.TMR1H);
             (*pic->P16map.CCPR1L) = (*pic->P16map.TMR1L);
            }
           break;
          case 1://Every rising edge
           if (pic->ccp[0].ovalue == 0)
            {
             (*pic->P16map.PIR1) |= 0x04; //CCP1IF
             (*pic->P16map.CCPR1H) = (*pic->P16map.TMR1H);
             (*pic->P16map.CCPR1L) = (*pic->P16map.TMR1L);
            }
           break;
          case 2://Every 4th rising edge
           if (pic->ccp[0].ovalue == 0)
            {
             pic->ccp[0].cap_ps++;
             if (pic->ccp[0].cap_ps == 4)
              {
               pic->ccp[0].cap_ps = 0;
               (*pic->P16map.PIR1) |= 0x04; //CCP1IF
               (*pic->P16map.CCPR1H) = (*pic->P16map.TMR1H);
               (*pic->P16map.CCPR1L) = (*pic->P16map.TMR1L);
              }
            }
           break;
          case 3://Every 16th rising edge
           if (pic->ccp[0].ovalue == 0)
            {
             pic->ccp[0].cap_ps++;
             if (pic->ccp[0].cap_ps == 16)
              {
               pic->ccp[0].cap_ps = 0;
               (*pic->P16map.PIR1) |= 0x04; //CCP1IF
               (*pic->P16map.CCPR1H) = (*pic->P16map.TMR1H);
               (*pic->P16map.CCPR1L) = (*pic->P16map.TMR1L);
              }
            }
           break;
          }
         pic->ccp[0].ovalue = pic->pins[(pic->ccp[0].pin - 1)].value;
        }
      }
    }
   if ((pic->CCPCOUNT >= 2)&&(pic->ccp[1].pin > 0))
    {
     if (((*pic->P16map.CCP2CON) & 0x0C) == 0x04)//CAPTURE MODE
      {
       if (pic->pins[pic->ccp[1].pin - 1].value != pic->ccp[1].ovalue)//pin state change
        {
         switch ((*pic->P16map.CCP2CON) & 0x03)
          {
          case 0://Every falling edge
           if (pic->ccp[1].ovalue == 1)
            {
             (*pic->P16map.PIR2) |= 0x01; //CCP2IF
             (*pic->P16map.CCPR2H) = (*pic->P16map.TMR1H);
             (*pic->P16map.CCPR2L) = (*pic->P16map.TMR1L);
            }
           break;
          case 1://Every rising edge
           if (pic->ccp[1].ovalue == 0)
            {
             (*pic->P16map.PIR2) |= 0x01; //CCP2IF
             (*pic->P16map.CCPR2H) = (*pic->P16map.TMR1H);
             (*pic->P16map.CCPR2L) = (*pic->P16map.TMR1L);
            }
           break;
          case 2://Every 4th rising edge
           if (pic->ccp[1].ovalue == 0)
            {
             pic->ccp[1].cap_ps++;
             if (pic->ccp[1].cap_ps == 4)
              {
               pic->ccp[1].cap_ps = 0;
               (*pic->P16map.PIR2) |= 0x01; //CCP1IF
               (*pic->P16map.CCPR2H) = (*pic->P16map.TMR1H);
               (*pic->P16map.CCPR2L) = (*pic->P16map.TMR1L);
              }
            }
           break;
          case 3://Every 16th rising edge
           if (pic->ccp[1].ovalue == 0)
            {
             pic->ccp[1].cap_ps++;
             if (pic->ccp[1].cap_ps == 16)
              {
               pic->ccp[1].cap_ps = 0;
               (*pic->P16map.PIR2) |= 0x01; //CCP2IF
               (*pic->P16map.CCPR2H) = (*pic->P16map.TMR1H);
               (*pic->P16map.CCPR2L) = (*pic->P16map.TMR1L);
              }
            }
           break;
          }
         pic->ccp[1].ovalue = pic->pins[(pic->ccp[1].pin - 1)].value;
        }
      }
    }
  }
}
