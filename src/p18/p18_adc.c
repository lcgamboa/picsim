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
p18_adc_rst(void)
{
 pic->adcstep = 0;
 pic->adcon1 = 0xFF;
}

void
p18_adc(void)
{
 float val;
 int chn;
 short dval;

 if (pic->ADCCOUNT > 0)
  {

   if (((*pic->P18map.ADCON0) & 0x03) == 0x03) //ADON and GO/DONE
    {
     pic->adcstep++;
     if (pic->adcstep > 10)
      {
       chn = ((*pic->P18map.ADCON0)&0x3C) >> 2;

       if ((pic->pins[pic->adc[chn] - 1].ptype == PT_ANALOG)&&(chn < pic->ADCCOUNT))
        {
         val = pic->pins[pic->adc[chn] - 1].avalue;
        }
       else
        {
         val = 0;
        }

       dval = ((1023 * val) / 5.0);

       if ((*pic->P18map.ADCON2)&0x80)//ADFM
        { //Rigth
         (*pic->P18map.ADRESH) = (dval & 0xFF00) >> 8;
         (*pic->P18map.ADRESL) = (dval & 0x00FF);
        }
       else
        { //left
         dval = dval << 6;
         (*pic->P18map.ADRESH) = (dval & 0xFF00) >> 8;
         (*pic->P18map.ADRESL) = (dval & 0x00FF);
        }

       (*pic->P18map.ADCON0) &= ~0x02;

       //ADIF
       (*pic->P18map.PIR1) |= 0x40;

       pic->adcstep = 0;
      }
    }
   else
    {
     pic->adcstep = 0;
    }


   if (! pic->P18map.ANSELA)
    {
     if (((*pic->P18map.ADCON1)&0x0F) != pic->adcon1)
      {
       int i;
       for (i = 0; i < pic->ADCCOUNT; i++)
        {
         if (((*pic->P18map.ADCON1)&0x0F) < (0x0F - i))
          pic->pins[pic->adc[i] - 1].ptype = PT_ANALOG;
         else
          pic->pins[pic->adc[i] - 1].ptype = PT_CMOS;
        }

       if ((*pic->P18map.ADCON1) & 0x20)//VCFG1  
        pic->pins[pic->adc[2] - 1].ptype = PT_ANAREF;
       if ((*pic->P18map.ADCON1) & 0x10)//VCFG0  
        pic->pins[pic->adc[3] - 1].ptype = PT_ANAREF;

       pic->adcon1 = (*pic->P18map.ADCON1)&0x0F;
      }
    }
   else
    {

     if (pic->lram == sfr_addr (pic->P18map.ANSELA))
      {
       for (int i = 0; i < pic->ADCCOUNT; i++)
        {
         if ((pic->adc[i])&&(pic->pins[pic->adc[i] - 1].port == pic->P18map.PORTA))
          {
           if ((*pic->P18map.ANSELA) & (1 << pic->pins[pic->adc[i] - 1].pord))
            {
             pic->pins[pic->adc[i] - 1].ptype = PT_ANALOG;
            }
           else
            {
             pic->pins[pic->adc[i] - 1].ptype = PT_CMOS;
            }
          }
        }
      }

     if (pic->lram == sfr_addr (pic->P18map.ANSELB))
      {
       for (int i = 0; i < pic->ADCCOUNT; i++)
        {
         if ((pic->adc[i])&&(pic->pins[pic->adc[i] - 1].port == pic->P18map.PORTB))
          {
           if ((*pic->P18map.ANSELB) & (1 << pic->pins[pic->adc[i] - 1].pord))
            {
             pic->pins[pic->adc[i] - 1].ptype = PT_ANALOG;
            }
           else
            {
             pic->pins[pic->adc[i] - 1].ptype = PT_CMOS;
            }
          }
        }
      }

     if (pic->lram == sfr_addr (pic->P18map.ANSELC))
      {
       for (int i = 0; i < pic->ADCCOUNT; i++)
        {
         if ((pic->adc[i])&&(pic->pins[pic->adc[i] - 1].port == pic->P18map.PORTC))
          {
           if ((*pic->P18map.ANSELC) & (1 << pic->pins[pic->adc[i] - 1].pord))
            {
             pic->pins[pic->adc[i] - 1].ptype = PT_ANALOG;
            }
           else
            {
             pic->pins[pic->adc[i] - 1].ptype = PT_CMOS;
            }
          }
        }
      }

     if ((pic->P18map.ANSELD)&&(pic->lram == sfr_addr (pic->P18map.ANSELD)))
      {
       for (int i = 0; i < pic->ADCCOUNT; i++)
        {
         if ((pic->adc[i])&&(pic->pins[pic->adc[i] - 1].port == pic->P18map.PORTD))
          {
           if ((*pic->P18map.ANSELD) & (1 << pic->pins[pic->adc[i] - 1].pord))
            {
             pic->pins[pic->adc[i] - 1].ptype = PT_ANALOG;
            }
           else
            {
             pic->pins[pic->adc[i] - 1].ptype = PT_CMOS;
            }
          }
        }
      }

     if ((pic->P18map.ANSELE)&&(pic->lram == sfr_addr (pic->P18map.ANSELE)))
      {
       for (int i = 0; i < pic->ADCCOUNT; i++)
        {
         if ((pic->adc[i])&&(pic->pins[pic->adc[i] - 1].port == pic->P18map.PORTE))
          {
           if ((*pic->P18map.ANSELE) & (1 << pic->pins[pic->adc[i] - 1].pord))
            {
             pic->pins[pic->adc[i] - 1].ptype = PT_ANALOG;
            }
           else
            {
             pic->pins[pic->adc[i] - 1].ptype = PT_CMOS;
            }
          }
        }
      }
    }


  }
}

void
p18_adc_2(void)
{
 float val;
 int chn;
 short dval;

 if (pic->ADCCOUNT > 0)
  {

   if (((*pic->P18map.ADCON0) & 0x05) == 0x05) // ADON and GO/DONE
    {
     pic->adcstep++;
     if (pic->adcstep > 10)
      {
       chn = ((*pic->P18map.ADCON0)&0x38) >> 3;

       if (pic->pins[pic->adc[chn] - 1].ptype == PT_ANALOG)
        {
         val = pic->pins[pic->adc[chn] - 1].avalue;
        }
       else
        {
         val = 0;
        }

       dval = ((1023 * val) / 5.0);

       if (((*pic->P18map.ADCON1)&0x80) == 0x80)//ADFM
        {
         (*pic->P18map.ADRESH) = (dval & 0xFF00) >> 8;
         (*pic->P18map.ADRESL) = (dval & 0x00FF);
        }
       else
        {
         dval = dval << 6;
         (*pic->P18map.ADRESH) = (dval & 0xFF00) >> 8;
         (*pic->P18map.ADRESL) = (dval & 0x00FF);
        }

       (*pic->P18map.ADCON0) &= ~0x04;

       //ADIF
       (*pic->P18map.PIR1) |= 0x40;

       pic->adcstep = 0;
      }
    }
   else
    {
     pic->adcstep = 0;
    }



   if (((*pic->P18map.ADCON1)&0x0F) != pic->adcon1)
    {
     switch ((*pic->P18map.ADCON1)&0x0F)
      {
      case 0:
       pic->pins[pic->adc[0] - 1].ptype = PT_ANALOG;
       pic->pins[pic->adc[1] - 1].ptype = PT_ANALOG;
       pic->pins[pic->adc[2] - 1].ptype = PT_ANALOG;
       pic->pins[pic->adc[3] - 1].ptype = PT_ANALOG;
       pic->pins[pic->adc[4] - 1].ptype = PT_ANALOG;
       pic->pins[pic->adc[5] - 1].ptype = PT_ANALOG;
       pic->pins[pic->adc[6] - 1].ptype = PT_ANALOG;
       pic->pins[pic->adc[7] - 1].ptype = PT_ANALOG;
       break;
      case 1:
       pic->pins[pic->adc[0] - 1].ptype = PT_ANALOG;
       pic->pins[pic->adc[1] - 1].ptype = PT_ANALOG;
       pic->pins[pic->adc[2] - 1].ptype = PT_ANALOG;
       pic->pins[pic->adc[3] - 1].ptype = PT_ANAREF;
       pic->pins[pic->adc[4] - 1].ptype = PT_ANALOG;
       pic->pins[pic->adc[5] - 1].ptype = PT_ANALOG;
       pic->pins[pic->adc[6] - 1].ptype = PT_ANALOG;
       pic->pins[pic->adc[7] - 1].ptype = PT_ANALOG;
       break;
      case 2:
       pic->pins[pic->adc[0] - 1].ptype = PT_ANALOG;
       pic->pins[pic->adc[1] - 1].ptype = PT_ANALOG;
       pic->pins[pic->adc[2] - 1].ptype = PT_ANALOG;
       pic->pins[pic->adc[3] - 1].ptype = PT_ANALOG;
       pic->pins[pic->adc[4] - 1].ptype = PT_ANALOG;
       pic->pins[pic->adc[5] - 1].ptype = PT_CMOS;
       pic->pins[pic->adc[6] - 1].ptype = PT_CMOS;
       pic->pins[pic->adc[7] - 1].ptype = PT_CMOS;
       break;
      case 3:
       pic->pins[pic->adc[0] - 1].ptype = PT_ANALOG;
       pic->pins[pic->adc[1] - 1].ptype = PT_ANALOG;
       pic->pins[pic->adc[2] - 1].ptype = PT_ANALOG;
       pic->pins[pic->adc[3] - 1].ptype = PT_ANAREF;
       pic->pins[pic->adc[4] - 1].ptype = PT_ANALOG;
       pic->pins[pic->adc[5] - 1].ptype = PT_CMOS;
       pic->pins[pic->adc[6] - 1].ptype = PT_CMOS;
       pic->pins[pic->adc[7] - 1].ptype = PT_CMOS;
       break;
      case 4:
       pic->pins[pic->adc[0] - 1].ptype = PT_ANALOG;
       pic->pins[pic->adc[1] - 1].ptype = PT_ANALOG;
       pic->pins[pic->adc[2] - 1].ptype = PT_CMOS;
       pic->pins[pic->adc[3] - 1].ptype = PT_ANALOG;
       pic->pins[pic->adc[4] - 1].ptype = PT_CMOS;
       pic->pins[pic->adc[5] - 1].ptype = PT_CMOS;
       pic->pins[pic->adc[6] - 1].ptype = PT_CMOS;
       pic->pins[pic->adc[7] - 1].ptype = PT_CMOS;
       break;
      case 5:
       pic->pins[pic->adc[0] - 1].ptype = PT_ANALOG;
       pic->pins[pic->adc[1] - 1].ptype = PT_ANALOG;
       pic->pins[pic->adc[2] - 1].ptype = PT_CMOS;
       pic->pins[pic->adc[3] - 1].ptype = PT_ANAREF;
       pic->pins[pic->adc[4] - 1].ptype = PT_CMOS;
       pic->pins[pic->adc[5] - 1].ptype = PT_CMOS;
       pic->pins[pic->adc[6] - 1].ptype = PT_CMOS;
       pic->pins[pic->adc[7] - 1].ptype = PT_CMOS;
       break;
      case 6:
      case 7:
       pic->pins[pic->adc[0] - 1].ptype = PT_CMOS;
       pic->pins[pic->adc[1] - 1].ptype = PT_CMOS;
       pic->pins[pic->adc[2] - 1].ptype = PT_CMOS;
       pic->pins[pic->adc[3] - 1].ptype = PT_CMOS;
       pic->pins[pic->adc[4] - 1].ptype = PT_CMOS;
       pic->pins[pic->adc[5] - 1].ptype = PT_CMOS;
       pic->pins[pic->adc[6] - 1].ptype = PT_CMOS;
       pic->pins[pic->adc[7] - 1].ptype = PT_CMOS;
       break;
      case 8:
       pic->pins[pic->adc[0] - 1].ptype = PT_ANALOG;
       pic->pins[pic->adc[1] - 1].ptype = PT_ANALOG;
       pic->pins[pic->adc[2] - 1].ptype = PT_ANAREF;
       pic->pins[pic->adc[3] - 1].ptype = PT_ANAREF;
       pic->pins[pic->adc[4] - 1].ptype = PT_ANALOG;
       pic->pins[pic->adc[5] - 1].ptype = PT_ANALOG;
       pic->pins[pic->adc[6] - 1].ptype = PT_ANALOG;
       pic->pins[pic->adc[7] - 1].ptype = PT_ANALOG;
       break;
      case 9:
       pic->pins[pic->adc[0] - 1].ptype = PT_ANALOG;
       pic->pins[pic->adc[1] - 1].ptype = PT_ANALOG;
       pic->pins[pic->adc[2] - 1].ptype = PT_ANALOG;
       pic->pins[pic->adc[3] - 1].ptype = PT_ANALOG;
       pic->pins[pic->adc[4] - 1].ptype = PT_ANALOG;
       pic->pins[pic->adc[5] - 1].ptype = PT_ANALOG;
       pic->pins[pic->adc[6] - 1].ptype = PT_CMOS;
       pic->pins[pic->adc[7] - 1].ptype = PT_CMOS;
       break;
      case 10:
       pic->pins[pic->adc[0] - 1].ptype = PT_ANALOG;
       pic->pins[pic->adc[1] - 1].ptype = PT_ANALOG;
       pic->pins[pic->adc[2] - 1].ptype = PT_ANALOG;
       pic->pins[pic->adc[3] - 1].ptype = PT_ANAREF;
       pic->pins[pic->adc[4] - 1].ptype = PT_ANALOG;
       pic->pins[pic->adc[5] - 1].ptype = PT_ANALOG;
       pic->pins[pic->adc[6] - 1].ptype = PT_CMOS;
       pic->pins[pic->adc[7] - 1].ptype = PT_CMOS;
       break;
      case 11:
       pic->pins[pic->adc[0] - 1].ptype = PT_ANALOG;
       pic->pins[pic->adc[1] - 1].ptype = PT_ANALOG;
       pic->pins[pic->adc[2] - 1].ptype = PT_ANAREF;
       pic->pins[pic->adc[3] - 1].ptype = PT_ANAREF;
       pic->pins[pic->adc[4] - 1].ptype = PT_ANALOG;
       pic->pins[pic->adc[5] - 1].ptype = PT_ANALOG;
       pic->pins[pic->adc[6] - 1].ptype = PT_CMOS;
       pic->pins[pic->adc[7] - 1].ptype = PT_CMOS;
       break;
      case 12:
       pic->pins[pic->adc[0] - 1].ptype = PT_ANALOG;
       pic->pins[pic->adc[1] - 1].ptype = PT_ANALOG;
       pic->pins[pic->adc[2] - 1].ptype = PT_ANAREF;
       pic->pins[pic->adc[3] - 1].ptype = PT_ANAREF;
       pic->pins[pic->adc[4] - 1].ptype = PT_ANALOG;
       pic->pins[pic->adc[5] - 1].ptype = PT_CMOS;
       pic->pins[pic->adc[6] - 1].ptype = PT_CMOS;
       pic->pins[pic->adc[7] - 1].ptype = PT_CMOS;
       break;
      case 13:
       pic->pins[pic->adc[0] - 1].ptype = PT_ANALOG;
       pic->pins[pic->adc[1] - 1].ptype = PT_ANALOG;
       pic->pins[pic->adc[2] - 1].ptype = PT_ANAREF;
       pic->pins[pic->adc[3] - 1].ptype = PT_ANAREF;
       pic->pins[pic->adc[4] - 1].ptype = PT_CMOS;
       pic->pins[pic->adc[5] - 1].ptype = PT_CMOS;
       pic->pins[pic->adc[6] - 1].ptype = PT_CMOS;
       pic->pins[pic->adc[7] - 1].ptype = PT_CMOS;
       break;
      case 14:
       pic->pins[pic->adc[0] - 1].ptype = PT_ANALOG;
       pic->pins[pic->adc[1] - 1].ptype = PT_CMOS;
       pic->pins[pic->adc[2] - 1].ptype = PT_CMOS;
       pic->pins[pic->adc[3] - 1].ptype = PT_CMOS;
       pic->pins[pic->adc[4] - 1].ptype = PT_CMOS;
       pic->pins[pic->adc[5] - 1].ptype = PT_CMOS;
       pic->pins[pic->adc[6] - 1].ptype = PT_CMOS;
       pic->pins[pic->adc[7] - 1].ptype = PT_CMOS;
       break;
      case 15:
       pic->pins[pic->adc[0] - 1].ptype = PT_ANALOG;
       pic->pins[pic->adc[1] - 1].ptype = PT_CMOS;
       pic->pins[pic->adc[2] - 1].ptype = PT_ANAREF;
       pic->pins[pic->adc[3] - 1].ptype = PT_ANAREF;
       pic->pins[pic->adc[4] - 1].ptype = PT_CMOS;
       pic->pins[pic->adc[5] - 1].ptype = PT_CMOS;
       pic->pins[pic->adc[6] - 1].ptype = PT_CMOS;
       pic->pins[pic->adc[7] - 1].ptype = PT_CMOS;
       break;
      }

     pic->adcon1 = (*pic->P18map.ADCON1)&0x0F;
    }

  }
}