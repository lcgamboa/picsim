/* ########################################################################

   PICsim - PIC simulator

   ########################################################################

   Copyright (c) : 2008-2020  Luis Claudio Gambôa Lopes

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
#include"../include/picsim.h"
#include"../include/periferic18.h"


extern const int fpw2[];

extern void pic_decode_18(void);

int
pic_wr_pin18(unsigned char pin, unsigned char value)
{
 unsigned char val;

 if ((pin - 1) < pic->PINCOUNT)
  {
   pic->pins[(pin - 1)].value = value;

   if ((pic->pins[(pin - 1)].pord >= 0)&&(pic->pins[(pin - 1)].port))
    {
     val = 0x01 << (pic->pins[(pin - 1)].pord);
     if ((pic->pins[(pin - 1)].value) == 1)
      (*pic->pins[(pin - 1)].port) |= val;
     else
      (*pic->pins[(pin - 1)].port) &= ~val;
#ifdef ICSPDBG  
     if ((pic->pins[(pin - 1)].port == pic->P18map.PORTB)&&((*pic->P18map.DEBUG) & 0x80))
      {
       (*pic->P18map.DEBUG) = ((*pic->P18map.DEBUG)&0xF3) | (((*pic->P18map.PORTB) &0xC0) >> 4); //espelhamento debug
      }
#endif              
    }

   return 1;
  }
 else
  return 0;
}

int
pic_dir_pin18(unsigned char pin, unsigned char dir)
{
 unsigned char val = 0;
 unsigned short tris;

 if ((pic->pins[pin - 1].pord >= 0)&&(pic->pins[pin - 1].port))
  {
   val = 0x01 << (pic->pins[pin - 1].pord);
   tris = sfr_addr (pic->pins[pin - 1].port)+(sfr_addr (pic->P18map.TRISA) - sfr_addr (pic->P18map.PORTA));

   if (dir == PD_OUT)
    {
     if (pic->ram[tris] & val)
      {
       pic->pins[pin - 1].dir = PD_OUT;
       pic->ram[tris] &= ~val;
      }
     else
      {
       val = 0; //value not changed
      }
    }
   else
    {
     if (!(pic->ram[tris] & val))
      {
       pic->pins[pin - 1].dir = PD_IN;
       pic->ram[tris] |= val;
      }
     else
      {
       val = 0; //value not changed
      }
    }
  }

 if (val)
  {
   pic->trisa = (*pic->P18map.TRISA);
   pic->trisb = (*pic->P18map.TRISB);
   pic->trisc = (*pic->P18map.TRISC);
   if (pic->P18map.TRISD)pic->trisd = (*pic->P18map.TRISD);
   if (pic->P18map.TRISE)pic->trise = (*pic->P18map.TRISE);
   if (pic->P18map.TRISF)pic->trisf = (*pic->P18map.TRISF);
   if (pic->P18map.TRISG)pic->trisg = (*pic->P18map.TRISG);
   return 1;
  }
 return 0;
}

void
periferic18_rst(void)
{

 pic->debug = 0;
 pic->sleep = 0;

 pic->porta = 129;
 pic->portb = 129;
 pic->portc = 129;
 pic->portd = 129;
 pic->porte = 129;
 pic->portf = 129;
 pic->portg = 129;
  
 pic->trisa = 129;
 pic->trisb = 129;
 pic->trisc = 129;
 pic->trisd = 129;
 pic->trise = 129;
 pic->trisf = 129;
 pic->trisg = 129;

 pic->sstep = 0;
 pic->dbg = 5;

 pic->intlv = 0;

 pic->frst = 1;

}

void
periferic18_step_in(void)
{
 //int i;

#ifdef ICSPDBG  
 //DEBUG
 if (pic->getconf (CFG_DEBUG)) //DEBUG ON
  {
   if (pic->debug == 1)(*pic->P18map.DEBUG) |= 0x80;
  }
#endif

 pic->periferic ();

}

void
periferic18_step_out(void)
{
 int i, val;

 unsigned short port;
 unsigned short tris;

#ifdef ICSPDBG  
 if (pic->lram == sfr_addr (pic->P18map.DEBUG))
  {
   //printf("---------------> DEBUG write (%#02X)\n",(*pic->P18map.DEBUG));

   if (((*pic->P18map.DEBUG) & 0x80) == 0x80)
    {
     (*pic->P18map.TRISB) = ((*pic->P18map.TRISB)&0x3F) | (((*pic->P18map.DEBUG) &0x03) << 6);

     if (!((*pic->P18map.DEBUG) &0x02))(*pic->P18map.PORTB) = ((*pic->P18map.PORTB)&0x7F) | (((*pic->P18map.DEBUG) &0x08) << 4);
     if (!((*pic->P18map.DEBUG) &0x01))(*pic->P18map.PORTB) = ((*pic->P18map.PORTB)&0xBF) | (((*pic->P18map.DEBUG) &0x04) << 4);

     //printf("pgd=%i tpgd=%i pgc=%i tpgc=%i\n",pic->pins[pic->pgd-1].value,pic->pins[pic->pgd-1].dir,pic->pins[pic->pgc-1].value,pic->pins[pic->pgc-1].dir);
    }
  }

 if (pic->rram == sfr_addr (pic->P18map.DEBUG))
  {
   //printf("---------------> DEBUG read (%#02X)\n",(*pic->P18map.DEBUG));

   if (((*pic->P18map.DEBUG) & 0x80) == 0x80)
    {
     (*pic->P18map.TRISB) = ((*pic->P18map.TRISB)&0x3F) | (((*pic->P18map.DEBUG) &0x03) << 6);

     //  printf("pgd=%i tpgd=%i pgc=%i tpgc=%i\n",pic->pins[pic->pgd-1].value,pic->pins[pic->pgd-1].dir,pic->pins[pic->pgc-1].value,pic->pins[pic->pgc-1].dir);
    }

  }
 /* 
         if(pic->lram == P18_BDMSR0 )
         {
            printf("---------------> BDMSR0 write (%#02X)\n",(*pic->P18map.BDMSR0));
         }
  */


 //DEBUG
 if (pic->getconf (CFG_DEBUG)) //DEBUG ON
  {
   pic->ocd_pgca = pic->ocd_pgc;
   pic->ocd_pgc = pic->pins[pic->pgc - 1].value;


   if (((*pic->P18map.DEBUG) & 0x80) == 0)
    {
     pic->dbg++;

     if (((*pic->P18map.DEBUG)&0x20) == 0x20) pic->sstep++;

     if (((pic->ocd_pgca == 1)&&(pic->ocd_pgc == 0)) || //HardWare
         (((pic->pc >> 1) == (((((*pic->P18map.BDMSR2)&0x0F) << 16) | ((*pic->P18map.BDMSR1) << 8) | (*pic->P18map.BDMSR0))/*+1*/))&&(pic->dbg > 3)) || //Break Point  
         ((((*pic->P18map.DEBUG)&0x20) == 0x20)&&(pic->sstep == 3))) //step 
      {
       //printf("Debug Halt (%04X)   ",pic->pc);

       //         if((pic->ocd_pgca ==1)&&(pic->ocd_pgc == 0)) printf("Hardware \n");                                   //HardWare
       //         if((pic->pc>>1) ==   (((((*pic->P18map.BDMSR2)&0x0F)<<16)|((*pic->P18map.BDMSR1)<<8)|(*pic->P18map.BDMSR0))/*+1*/ )) printf("Break Point\n");      //Break Point  
       //          if(((*pic->P18map.DEBUG)&0x20) == 0x20) printf("sstep!\n");  

       if (pic->s2 != 0)pic_decode_18 ();

       if (pic->pc != 0x00000)
        {
         //printf("Debug stack save\n");
         if (((*pic->P18map.STKPTR) & 0x1F) < 31)
          {
           pic->stack[(*pic->P18map.STKPTR)& 0x1F] = pic->pc;
           (*pic->P18map.STKPTR) = ((*pic->P18map.STKPTR) &0xC0) | (((*pic->P18map.STKPTR) &0x1F) + 1);
           if (((*pic->P18map.STKPTR)& 0x1F) == 31)(*pic->P18map.STKPTR) |= 0x80; //set STKFUL
          }
         if (((*pic->P18map.STKPTR) & 0x1F) > 0)
          {
           (*pic->P18map.TOSL) = ((pic->stack[((*pic->P18map.STKPTR) & 0x1F) - 1])&0x0000FF);
           (*pic->P18map.TOSU) = ((pic->stack[((*pic->P18map.STKPTR) & 0x1F) - 1])&0x1F0000) >> 16;
           (*pic->P18map.TOSH) = ((pic->stack[((*pic->P18map.STKPTR) & 0x1F) - 1])&0x00FF00) >> 8;
          }
         else
          {
           (*pic->P18map.TOSL) = 0;
           (*pic->P18map.TOSH) = 0;
           (*pic->P18map.TOSU) = 0;
          }
        }

       (*pic->P18map.DEBUG) |= 0x80;
       (*pic->P18map.BDMSR2) = (pic->pc & 0xFF0000) >> 16;
       (*pic->P18map.BDMSR1) = (pic->pc & 0x00FF00) >> 8;
       (*pic->P18map.BDMSR0) = (pic->pc & 0x0000FF);
       pic->jpc = 0x200028;
       pic->s2 = 1;
       pic->debug = 1;
       pic->sstep = 0;

       //printf("\n----------->dbg  (%#04X) %#02X  %#02X  pc=0x%04X\n",P18_DEBUG,(*pic->P18map.DEBUG),(*pic->P18map.BDMSR0),pic->pc );
       /*           
                  pic->pins[pic->pgd-1].dir=((*pic->P18map.DEBUG)&0x02)>>1;                     
                  pic->pins[pic->pgc-1].dir=((*pic->P18map.DEBUG)&0x01);  
           
                  if(!pic->pins[pic->pgd-1].dir)pic->pins[pic->pgd-1].value=((*pic->P18map.DEBUG)&0x08)>>3;
                  if(!pic->pins[pic->pgc-1].dir)pic->pins[pic->pgc-1].value=((*pic->P18map.DEBUG)&0x04)>>2;
        */
       (*pic->P18map.TRISB) = ((*pic->P18map.TRISB)&0x3F) | (((*pic->P18map.DEBUG) &0x03) << 6);

       if (!((*pic->P18map.DEBUG) &0x02))(*pic->P18map.PORTB) = ((*pic->P18map.PORTB)&0x7F) | (((*pic->P18map.DEBUG) &0x08) << 4);
       if (!((*pic->P18map.DEBUG) &0x01))(*pic->P18map.PORTB) = ((*pic->P18map.PORTB)&0xBF) | (((*pic->P18map.DEBUG) &0x04) << 4);

      }
    }
  }
#endif




 //PINOUTS

 if (((*pic->P18map.PORTA) != pic->porta) ||
     ((*pic->P18map.PORTB) != pic->portb) ||
     ((*pic->P18map.PORTC) != pic->portc) ||
     ((pic->P18map.PORTD)&&((*pic->P18map.PORTD)) != pic->portd) ||
     ((pic->P18map.PORTE)&&((*pic->P18map.PORTE)) != pic->porte) ||
     ((pic->P18map.PORTF)&&((*pic->P18map.PORTF)) != pic->portf) ||
     ((pic->P18map.PORTG)&&((*pic->P18map.PORTG)) != pic->portg))
  {
   for (i = 0; i < pic->PINCOUNT; i++)
    {
     if ((pic->pins[i].pord >= 0)&&(pic->pins[i].port))
      switch (pic->pins[i].dir)
       {
       case PD_OUT:
        //	    case 7:
        //               if((pic->ram[P18_RCSTA] & 0x80)==0x80)break; 
        //	    case 17:
        //              if((pic->ram[P18_RCSTA] & 0x80)==0x80)break;
        //	   if(pic->pins[i].ptype > 2)break;	 
        val = 0x01 << (pic->pins[i].pord);
        port = sfr_addr (pic->pins[i].port);
        pic->pins[i].value = ((pic->ram[port] & val) != 0);
        pic->pins[i].lvalue = pic->pins[i].value;
        break;
       case PD_IN:
        val = 0x01 << (pic->pins[i].pord);
        port = sfr_addr (pic->pins[i].port)+(sfr_addr (pic->P18map.LATA) - sfr_addr (pic->P18map.PORTA));
        pic->pins[i].lvalue = ((pic->ram[port] & val) != 0); //latch
        if (pic->pins[i].ptype > 2)
         pic_wr_pin18 (i + 1, 0);
        else
         pic_wr_pin18 (i + 1, pic->pins[i].value);
        break;
       default:
        break;
       }
    }

   pic->porta = (*pic->P18map.PORTA);
   pic->portb = (*pic->P18map.PORTB);
   pic->portc = (*pic->P18map.PORTC);
   if (pic->P18map.PORTD)pic->portd = (*pic->P18map.PORTD);
   if (pic->P18map.PORTE)pic->porte = (*pic->P18map.PORTE);
   if (pic->P18map.PORTF)pic->portf = (*pic->P18map.PORTF);
   if (pic->P18map.PORTG)pic->portg = (*pic->P18map.PORTG);
  }



 if (((*pic->P18map.TRISA) != pic->trisa) ||
     ((*pic->P18map.TRISB) != pic->trisb) ||
     ((*pic->P18map.TRISC) != pic->trisc) ||
     ((pic->P18map.TRISD)&&((*pic->P18map.TRISD) != pic->trisd)) ||
     ((pic->P18map.TRISE)&&((*pic->P18map.TRISE) != pic->trise)) ||
     ((pic->P18map.TRISF)&&((*pic->P18map.TRISF) != pic->trisf)) ||
     ((pic->P18map.TRISG)&&((*pic->P18map.TRISG) != pic->trisg)))
  {
   for (i = 0; i < pic->PINCOUNT; i++)
    {
     if ((pic->pins[i].pord >= 0)&&(pic->pins[i].port))
      {
       val = 0x01 << (pic->pins[i].pord);
       tris = sfr_addr (pic->pins[i].port)+(sfr_addr (pic->P18map.TRISA) - sfr_addr (pic->P18map.PORTA));
       if ((pic->ram[tris] & val) == 0)
        {
         pic->pins[i].dir = PD_OUT;
         pic_wr_pin18 (i + 1, pic->pins[i].lvalue);
        }
       else
        {
         val = pic->pins[i].dir;
         pic->pins[i].dir = PD_IN;
         if (val != PD_IN)pic_wr_pin18 (i + 1, pic->pins[i].ovalue);
        }
      }

    }
   pic->trisa = (*pic->P18map.TRISA);
   pic->trisb = (*pic->P18map.TRISB);
   pic->trisc = (*pic->P18map.TRISC);
   if (pic->P18map.TRISD)pic->trisd = (*pic->P18map.TRISD);
   if (pic->P18map.TRISE)pic->trise = (*pic->P18map.TRISE);
   if (pic->P18map.TRISF)pic->trisf = (*pic->P18map.TRISF);
   if (pic->P18map.TRISG)pic->trisg = (*pic->P18map.TRISG);
  }




 //interrupt
 if (pic->s2 == 0)
  {
   int iret = pic->interrupt ();
   if (iret)
    {
     pic->sleep = 0;
     if (pic->print)printf ("interrupt!\n");
     if (((*pic->P18map.STKPTR) & 0x1F) < 31)
      {
       pic->stack[(*pic->P18map.STKPTR)& 0x1F] = pic->pc;
       (*pic->P18map.STKPTR) = ((*pic->P18map.STKPTR) &0xC0) | (((*pic->P18map.STKPTR) &0x1F) + 1);
       if (((*pic->P18map.STKPTR)& 0x1F) == 31)(*pic->P18map.STKPTR) |= 0x80; //set STKFUL
      }
     if (((*pic->P18map.STKPTR) & 0x1F) > 0)
      {
       (*pic->P18map.TOSL) = ((pic->stack[((*pic->P18map.STKPTR) & 0x1F) - 1])&0x0000FF);
       (*pic->P18map.TOSU) = ((pic->stack[((*pic->P18map.STKPTR) & 0x1F) - 1])&0x1F0000) >> 16;
       (*pic->P18map.TOSH) = ((pic->stack[((*pic->P18map.STKPTR) & 0x1F) - 1])&0x00FF00) >> 8;
      }
     else
      {
       (*pic->P18map.TOSL) = 0;
       (*pic->P18map.TOSH) = 0;
       (*pic->P18map.TOSU) = 0;
      }
     //fast stack       
     pic->P18map.WS = pic->w;
     pic->P18map.STATUSS = (*pic->P18map.STATUS);
     pic->P18map.BSRS = (*pic->P18map.BSR);


     if (iret == 2)
      {
       (*pic->P18map.INTCON) &= ~0x40; //GIEL
       pic->pc = 0x0018;
       pic->intlv |= 0x02;
      }
     else
      {
       (*pic->P18map.INTCON) &= ~0x80; //GIE/GIEH
       pic->pc = 0x0008;
       pic->intlv |= 0x01;
      };
     pic->s2 = 1;
    }
  }

}

