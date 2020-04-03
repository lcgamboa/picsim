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
#include"../../include/periferic16e.h"

void
p16e_adc_rst(void)
{
 pic->adcstep = 0;
 pic->adcon1 = 0xFF;
}

void
p16e_adc(void)
{
 float val;
 int chn;
 short dval;
 
 if (((*pic->P16Emap.ADCON0) & 0x03) == 0x03) // ADON and GO/DONE
  {
   pic->adcstep++;
   if (pic->adcstep > 10)
    {


     chn = ((*pic->P16Emap.ADCON0)&0x7C) >> 2;

     if (pic->pins[pic->adc[chn] - 1].ptype == PT_ANALOG)
      {
       val = pic->pins[pic->adc[chn] - 1].avalue;
      }
     else
      {
       val = 0;
      }

     dval = ((1023 * val) / 5.0);

     if (((*pic->P16Emap.ADCON1)&0x80) == 0x80)
      {
       (*pic->P16Emap.ADRESH) = (dval & 0xFF00) >> 8;
       (*pic->P16Emap.ADRESL) = (dval & 0x00FF);
      }
     else
      {
       dval = dval << 6;
       (*pic->P16Emap.ADRESH) = (dval & 0xFF00) >> 8;
       (*pic->P16Emap.ADRESL) = (dval & 0x00FF);
      }

     (*pic->P16Emap.ADCON0) &= ~0x02;

     //ADIF
     (*pic->P16Emap.PIR1) |= 0x40;

     pic->adcstep = 0;

     // printf("AD0=%02X AD1=%02X\n",pic->ram[ADCON0],pic->ram[ADCON1]);
     // printf("ADC conversion channel (%i)=%#04X (%08.3f)\n",chn,dval,val); 
    }
  }
 else
  {
   pic->adcstep = 0;
  }


 if (pic->lram == sfr_addr (pic->P16Emap.ANSELA))
  {
   for (int i = 0; i < pic->ADCCOUNT; i++)
    {
     if (pic->pins[pic->adc[i] - 1].port == pic->P16Emap.PORTA)
      {
       if ((*pic->P16Emap.ANSELA) & pic->pins[pic->adc[i] - 1].pord)
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

 if (pic->lram == sfr_addr (pic->P16Emap.ANSELB))
  {
   for (int i = 0; i < pic->ADCCOUNT; i++)
    {
     if (pic->pins[pic->adc[i] - 1].port == pic->P16Emap.PORTB)
      {
       if ((*pic->P16Emap.ANSELB) & pic->pins[pic->adc[i] - 1].pord)
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

 if (pic->lram == sfr_addr (pic->P16Emap.ANSELC))
  {
   for (int i = 0; i < pic->ADCCOUNT; i++)
    {
     if (pic->pins[pic->adc[i] - 1].port == pic->P16Emap.PORTC)
      {
       if ((*pic->P16Emap.ANSELC) & pic->pins[pic->adc[i] - 1].pord)
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

 if ((pic->P16Emap.ANSELD)&&(pic->lram == sfr_addr (pic->P16Emap.ANSELD)))
  {
   for (int i = 0; i < pic->ADCCOUNT; i++)
    {
     if (pic->pins[pic->adc[i] - 1].port == pic->P16Emap.PORTD)
      {
       if ((*pic->P16Emap.ANSELD) & pic->pins[pic->adc[i] - 1].pord)
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

 if ((pic->P16Emap.ANSELE)&&(pic->lram == sfr_addr (pic->P16Emap.ANSELE)))
  {
   for (int i = 0; i < pic->ADCCOUNT; i++)
    {
     if (pic->pins[pic->adc[i] - 1].port == pic->P16Emap.PORTE)
      {
       if ((*pic->P16Emap.ANSELE) & pic->pins[pic->adc[i] - 1].pord)
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