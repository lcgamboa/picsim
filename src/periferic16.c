/* ########################################################################

   PICsim - PIC simulator

   ########################################################################

   Copyright (c) : 2008-2020  Luis Claudio Gamboa Lopes

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
#include"../include/periferic16.h"


const int fpw2[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072,
 262144, 524288, 1048576, 2097152, 4194304, 8388608};


void pic_decode_16(void);

int
pic_wr_pin16(unsigned char pin, unsigned char value)
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
     if (pic->processor != P16F84A)
      pic->ram[sfr_addr (pic->pins[(pin - 1)].port) | 0x100] = (*pic->pins[(pin - 1)].port); //espelhamento bank2 = bank0
    }

   return 1;
  }
 else
  return 0;
}

int
pic_dir_pin16(unsigned char pin, unsigned char dir)
{
 unsigned char val = 0;
 unsigned char tris;

 if ((pic->pins[pin - 1].pord >= 0)&&(pic->pins[pin - 1].port))
  {
   val = 0x01 << (pic->pins[pin - 1].pord);
   tris = sfr_addr (pic->pins[pin - 1].port) + 0x80;

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
   pic->trisa = (*pic->P16map.TRISA);
   pic->trisb = (*pic->P16map.TRISB);
   if (pic->P16map.TRISC)pic->trisc = (*pic->P16map.TRISC);
   if (pic->P16map.TRISD)pic->trisd = (*pic->P16map.TRISD);
   if (pic->P16map.TRISE)pic->trise = (*pic->P16map.TRISE);
   return 1;
  }
 return 0;
}

inline static int
interrupt16(void)
{
 //interrupt
 //GIE
 if ((*pic->P16map.INTCON) & 0x80)
  {
   //T0IE  T0IF
   if (((*pic->P16map.INTCON)&0x20)&&((*pic->P16map.INTCON)&0x04)) return 1;
   //INTE INTF
   if (((*pic->P16map.INTCON)&0x10)&&((*pic->P16map.INTCON)&0x02)) return 1;
   //RBIE
   if (((*pic->P16map.INTCON)&0x08)&&((*pic->P16map.INTCON)&0x01)) return 1;
   //PEIE	
   if ((*pic->P16map.INTCON) & 0x40)
    {
     //EEIE
     //if(((*pic->P16map.PIE1) & 0x80)&&((*pic->P16map.PIR1) & 0x80)) return 1;
     //CMIE CMIF
     //if(((*pic->P16map.PIE1) & 0x40)&&((*pic->P16map.PIR1) & 0x40)) return 1;
     //ADIE ADIF 
     if (((*pic->P16map.PIE1) & 0x40)&&((*pic->P16map.PIR1) & 0x40)) return 1;
     //RCIE RCIF
     if (((*pic->P16map.PIE1) & 0x20)&&((*pic->P16map.PIR1) & 0x20)) return 1;
     //TXIE TXIF
     if (((*pic->P16map.PIE1) & 0x10)&&((*pic->P16map.PIR1) & 0x10)) return 1;
     //SSPIE
     if (((*pic->P16map.PIE1) & 0x08)&&((*pic->P16map.PIR1) & 0x08)) return 1;
     //CCP1IE CCP1IF
     if (((*pic->P16map.PIE1) & 0x04)&&((*pic->P16map.PIR1) & 0x04)) return 1;
     //TMR2IE TMR2IF
     if (((*pic->P16map.PIE1) & 0x02)&&((*pic->P16map.PIR1) & 0x02)) return 1;
     //TMR1IE TMR1IF
     if (((*pic->P16map.PIE1) & 0x01)&&((*pic->P16map.PIR1) & 0x01)) return 1;

     if (pic->P16map.PIE2)
      {
       //CCP2IE CCP2IF
       if (((*pic->P16map.PIE2) & 0x01)&&((*pic->P16map.PIR2) & 0x01)) return 1;
       //CCP3IE CCP3IF
       if (((*pic->P16map.PIE2) & 0x02)&&((*pic->P16map.PIR2) & 0x02)) return 1;
      }
    }

  }

 return 0;
}

void
periferic16_rst(void)
{
 pic->debug = 0;
 pic->sleep = 0;

 pic->p16latch[0] = 0;
 pic->p16latch[1] = 0;
 pic->p16latch[2] = 0;
 pic->p16latch[3] = 0;
 pic->p16latch[4] = 0;

 pic->porta = 129; //dummy value to be changed
 pic->portb = 129;
 pic->portc = 129;
 pic->portd = 129;
 pic->porte = 129;

 pic->trisa = 129;
 pic->trisb = 129;
 pic->trisc = 129;
 pic->trisd = 129;
 pic->trise = 129;

 pic->sstep = 0;
 pic->dbg = 5;

}

void
periferic16_step_in(void)
{

#ifdef ICSPDBG
 //DEBUG
 if (pic->getconf (CFG_DEBUG)) //DEBUG ON
  {
   if (pic->debug == 1)(*pic->P16map.ICKBUG) |= 0x80;
   (*pic->P16map.TRISB) |= 0xC0;
  }
#endif

 pic->periferic ();

}

void
periferic16_step_out(void)
{
 int i, val;

 unsigned char port;
 unsigned char tris;

#ifdef ICSPDBG  
 int temp;

 /*
         if(pic->lram == ICKBUG )
         {
            printf("---------------> ICKBUG write (%#02X)\n",pic->ram[ICKBUG]);
         }
	
         if(pic->lram == BIGBUG )
         {
            printf("---------------> BIGBUG write (%#02X)\n",pic->ram[BIGBUG]);
         }
  */

 //DEBUG
 if (pic->getconf (CFG_DEBUG)) //DEBUG ON
  {
   pic->ocd_pgca = pic->ocd_pgc;
   pic->ocd_pgc = pic->pins[pic->pgc - 1].value;


   if (((*pic->P16map.ICKBUG) & 0x80) == 0)
    {
     pic->dbg++;
     if (((*pic->P16map.ICKBUG)&0x20) == 0x20) pic->sstep++;

     if (((pic->ocd_pgca == 1)&&(pic->ocd_pgc == 0)) || //HardWare
         ((pic->pc == (((((*pic->P16map.ICKBUG)&0x1F) << 8) | (*pic->P16map.BIGBUG)) + 1))&&(pic->dbg > 3)) || //Break Point  
         ((((*pic->P16map.ICKBUG)&0x20) == 0x20)&&(pic->sstep == 3))) //step 
      {
       //printf("Debug Halt (%04X)   ",pic->pc);

       // if((pic->ocd_pgca ==1)&&(pic->ocd_pgc == 0)) printf("Hardware \n");                                   //HardWare
       // if(pic->pc ==   ((((pic->ram[ICKBUG]&0x1F)<<8) |  pic->ram[BIGBUG])+1)) printf("Break Point\n");      //Break Point  
       // if((pic->ram[ICKBUG]&0x20) == 0x20) printf("sstep!\n");  

       if (pic->s2 != 0)pic_decode_16 ();


       for (temp = 7; temp > 0; temp--)
        pic->stack[temp] = pic->stack[temp - 1];
       pic->stack[0] = pic->pc;

       (*pic->P16map.ICKBUG) |= 0x80;
       (*pic->P16map.ICKBUG) = ((*pic->P16map.ICKBUG)&0xE0) | ((pic->pc & 0x1F00) >> 8);
       (*pic->P16map.BIGBUG) = pic->pc & 0x00FF;
       pic->pc = 0x2004;
       pic->s2 = 1;
       pic->debug = 1;

       //printf("----------->dbg  (%#04X) %#02X  %#02X \n",ICKBUG,pic->ram[ICKBUG],pic->ram[BIGBUG] );

      }
    }
  }
#endif

 //PINOUTS
 if (((*pic->P16map.PORTA) != pic->porta) ||
     ((*pic->P16map.PORTB) != pic->portb) ||
     ((pic->P16map.PORTC)&&((*pic->P16map.PORTC) != pic->portc)) ||
     ((pic->P16map.PORTD)&&((*pic->P16map.PORTD) != pic->portd)) ||
     ((pic->P16map.PORTE)&&((*pic->P16map.PORTE) != pic->porte)))
  {

   for (i = 0; i < pic->PINCOUNT; i++)
    {
     if (pic->pins[i].pord >= 0)
      switch (pic->pins[i].dir)
       {
       case PD_OUT:
        //	    case 7:
        //               if((pic->ram[RCSTA] & 0x80)==0x80)break; 
        //	    case 17:
        //              if((pic->ram[RCSTA] & 0x80)==0x80)break;
        //	   if(pic->pins[i].ptype > 2)break;	 
        val = 0x01 << (pic->pins[i].pord);
        port = sfr_addr (pic->pins[i].port);
        pic->pins[i].value = ((pic->ram[port] & val) != 0);
        pic->pins[i].lvalue = pic->pins[i].value;
        break;
       case PD_IN:
        val = 0x01 << (pic->pins[i].pord);
        port = sfr_addr (pic->pins[i].port);
        pic->pins[i].lvalue = ((pic->p16latch[port - sfr_addr (pic->P16map.PORTA)] & val) != 0); //latch
        if (pic->pins[i].ptype > 2)
         pic_wr_pin16 (i + 1, 0);
        else
         pic_wr_pin16 (i + 1, pic->pins[i].value);
        break;
       default:
        break;
       }
    }
   pic->porta = (*pic->P16map.PORTA);
   pic->portb = (*pic->P16map.PORTB);
   if (pic->P16map.PORTC)pic->portc = (*pic->P16map.PORTC);
   if (pic->P16map.PORTD)pic->portd = (*pic->P16map.PORTD);
   if (pic->P16map.PORTE)pic->porte = (*pic->P16map.PORTE);
  }



 if (((*pic->P16map.TRISA) != pic->trisa) ||
     ((*pic->P16map.TRISB) != pic->trisb) ||
     ((pic->P16map.TRISC)&&((*pic->P16map.TRISC) != pic->trisc)) ||
     ((pic->P16map.TRISD)&&((*pic->P16map.TRISD) != pic->trisd)) ||
     ((pic->P16map.TRISE)&&((*pic->P16map.TRISE) != pic->trise)))
  {
   for (i = 0; i < pic->PINCOUNT; i++)
    {
     if (pic->pins[i].pord >= 0)
      {
       val = 0x01 << (pic->pins[i].pord);
       tris = sfr_addr (pic->pins[i].port) + 0x80;
       if ((pic->ram[tris] & val) == 0)
        {
         pic->pins[i].dir = PD_OUT;
         pic_wr_pin16 (i + 1, pic->pins[i].lvalue);
        }
       else
        {
         val = pic->pins[i].dir;
         pic->pins[i].dir = PD_IN;
         if (val != PD_IN)pic_wr_pin16 (i + 1, pic->pins[i].ovalue);
        }
      }
    }
   pic->trisa = (*pic->P16map.TRISA);
   pic->trisb = (*pic->P16map.TRISB);
   if (pic->P16map.TRISC)pic->trisc = (*pic->P16map.TRISC);
   if (pic->P16map.TRISD)pic->trisd = (*pic->P16map.TRISD);
   if (pic->P16map.TRISE)pic->trise = (*pic->P16map.TRISE);
  }


 //interrupt
 if (pic->s2 == 0)
  {
   if (interrupt16 ())
    {
     pic->sleep = 0;

     pic->ram[(0x0000) | (sfr_addr (pic->P16map.INTCON) & 0x007F)] &= ~0x80;
     pic->ram[(0x0080) | (sfr_addr (pic->P16map.INTCON) & 0x007F)] &= ~0x80;
     pic->ram[(0x0100) | (sfr_addr (pic->P16map.INTCON) & 0x007F)] &= ~0x80;
     pic->ram[(0x0180) | (sfr_addr (pic->P16map.INTCON) & 0x007F)] &= ~0x80;

     if (pic->print)printf ("interrupt!");
     for (i = 7; i > 0; i--)
      pic->stack[i] = pic->stack[i - 1];
     pic->stack[0] = pic->pc;
     pic->pc = 0x0004;
     pic->s2 = 1;
    }

  }
}

