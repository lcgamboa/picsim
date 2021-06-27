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
#include<stdlib.h>
#include<string.h>

#include"../include/picsim.h"
#include"../include/periferic16.h"
#include"../include/periferic16e.h"
#include"../include/periferic18.h"

#include"modules.h" //dirt hack to include dynamic load in static lib

_pic * pic; //global object

extern void pic_decode_16(void);
extern void pic_decode_16E(void);
extern void pic_decode_18(void);

unsigned char NO_IO[6] = {1, 2, 3, 4, 5, 6};

int PIC_count;

pic_desc PICS[PMAX];

unsigned short *
memsets(unsigned short * mem, unsigned short value, unsigned long size)
{
 unsigned long i;
 for (i = 0; i < size; i++)
  mem[i] = value;

 return mem;
}

void
pic_erase_flash(void)
{
 /*zerar memoria*/
 switch (pic->family)
  {
  case P16:
  case P16E:
   memsets (pic->prog, 0x3FFF, pic->ROMSIZE);
   memsets (pic->config, 0x3FFF, pic->CONFIGSIZE);
   memsets (pic->id, 0x3FFF, pic->IDSIZE);
   break;
  case P18:
   memsets (pic->prog, 0xFFFF, pic->ROMSIZE);
   memsets (pic->config, 0xFFFF, pic->CONFIGSIZE);
   memsets (pic->id, 0xFFFF, pic->IDSIZE);
   memset (pic->debugv, 0, 8 * sizeof (short));
   break;
  default:
   break;
  }
}

int
pic_init(_pic * pic_, int processor, const char * fname, int leeprom, float freq)
{
 int i;
 int retcode = 0;

 pic = pic_;

 pic->print = 0;

 pic->freq = freq;
 pic->processor = processor;
 pic->family = getfprocbynumber (processor);

 pic->pkg = PDIP;

 retcode = -1;
 for (i = 0; i < PIC_count; i++)
  {
   if (PICS[i].ID == processor)
    {
     retcode = i;
     PICS[i].start ();
     break;
    }
  }

 if (retcode == -1)
  {
   printf ("picsim error: unknown processor 0x%04X!\n", processor);
   return 1;
  }

 pic->ram = calloc (pic->RAMSIZE, sizeof (char));
 pic->prog = calloc (pic->ROMSIZE, sizeof (short));
 pic->id = calloc (pic->IDSIZE, sizeof (short));
 pic->config = calloc (pic->CONFIGSIZE, sizeof (short));
 pic->stack = calloc (pic->STACKSIZE, sizeof (int));
 pic->eeprom = calloc (pic->EEPROMSIZE, sizeof (char));
 pic->pins = calloc (pic->PINCOUNT, sizeof (picpin));
 pic->ccp = calloc (pic->CCPCOUNT, sizeof (char));
 pic->adc = calloc (pic->ADCCOUNT, sizeof (char));
 pic->usart_rx = calloc (pic->USARTCOUNT, sizeof (char));
 pic->usart_tx = calloc (pic->USARTCOUNT, sizeof (char));

 pic->mmap ();

 pic_erase_flash ();


 if (leeprom == 1)
  memset (pic->eeprom, 0xFF, pic->EEPROMSIZE);

 pic->sleep = 0;

 if (fname == NULL)
  {
   retcode = 0;
  }
 else
  {
   switch (pic->family)
    {
    case P16:
     retcode = read_ihx (fname, leeprom);
     break;
    case P16E:
     retcode = read_ihx_16e (fname, leeprom);
     break;
    case P18:
     retcode = read_ihx_18 (fname, leeprom);
     break;
    default:
     break;
    }
  }

 //configuration   
 pic_reset (1);

 for (i = 0; i < pic->PINCOUNT; i++)
  {
   pic->pins[i].ovalue = 1; //put default pin values to 1  
  }

 return retcode;
}

int
pic_getMCLRE(void)
{
 return pic->getconf (CFG_MCLR);
}

int
pic_reset(int flags)
{
 int i;

 //verify MCLRE
 if ((flags < 0)&& !pic_getMCLRE ())
  {
   return 0;
  }

 pic->w = 0;
 pic->pc = 0;
 pic->s2 = 0;
 pic->lram = 0;
 pic->rram = 0;


 pic->jpc = 0xFFFFF;

 pic->t0cki_ = 0;
 pic->t1cki_ = 1;

 /*memory clear*/
 memset (pic->ram, 0, pic->RAMSIZE);
 memset (pic->stack, 0, pic->STACKSIZE * sizeof (int));

 for (i = 0; i < pic->PINCOUNT; i++)
  {
   pic->pins[i].avalue = 0;
   pic->pins[i].lvalue = 0;
   pic->pins[i].pord = 0;
   pic->pins[i].port = 0;
   pic->pins[i].value = 0;
   pic->pins[i].ptype = PT_DIGITAL;
   pic->pins[i].dir = PD_IN;
   //pic->pins[i].ovalue=0;
   pic->pins[i].oavalue = 0;
  }

 pic->reset ();

 for (i = 0; i < pic->PINCOUNT; i++)
  {
     if((pic->pins[i].port == P_VDD )||(pic->pins[i].port == P_VSS ))
     {
       pic->pins[i].ptype = PT_POWER;      
     }
  }

 switch (pic->family)
  {
  case P16:

   if (abs (flags) == 1)
    {
     pic->ram[(0x0000) | (sfr_addr (pic->P16map.STATUS) & 0x007F)] = 0x18;
     pic->ram[(0x0080) | (sfr_addr (pic->P16map.STATUS) & 0x007F)] = 0x18;
     if (pic->processor != P16F84A)
      {
       pic->ram[(0x0100) | (sfr_addr (pic->P16map.STATUS) & 0x007F)] = 0x18;
       pic->ram[(0x0180) | (sfr_addr (pic->P16map.STATUS) & 0x007F)] = 0x18;
      }
    }

   (*pic->P16map.TRISA) = 0xFF;
   (*pic->P16map.TRISB) = 0xFF;
   if (pic->P16map.TRISC)(*pic->P16map.TRISC) = 0xFF;
   if (pic->P16map.TRISD)(*pic->P16map.TRISD) = 0xFF;
   if (pic->P16map.TRISE)(*pic->P16map.TRISE) = 0x07;
   if (pic->P16map.PR2)(*pic->P16map.PR2) = 0xFF;
   periferic16_rst ();

   break;
  case P16E:

   if (abs (flags) == 1)
    {
     unsigned short offset = (sfr_addr (pic->P16Emap.STATUS) & 0x007F);
     for (int bk = 0; bk < 32; bk++)
      {
       pic->ram[(0x0080 * bk) | (offset)] = 0x18;
      }
    }

   (*pic->P16Emap.TRISA) = 0xFF;
   if (pic->P16Emap.TRISB)(*pic->P16Emap.TRISB) = 0xFF;
   if (pic->P16Emap.TRISC)(*pic->P16Emap.TRISC) = 0xFF;
   if (pic->P16Emap.TRISD)(*pic->P16Emap.TRISD) = 0xFF;
   if (pic->P16Emap.TRISE)(*pic->P16Emap.TRISE) = 0x07;
   if (pic->P16Emap.PR2)(*pic->P16Emap.PR2) = 0xFF;

   (*pic->P16Emap.ANSELA) = 0xFF;
   if (pic->P16Emap.ANSELB)(*pic->P16Emap.ANSELB) = 0xFF;
   if (pic->P16Emap.ANSELC)(*pic->P16Emap.ANSELC) = 0xFF;
   if (pic->P16Emap.ANSELD)(*pic->P16Emap.ANSELD) = 0xFF;
   if (pic->P16Emap.ANSELE)(*pic->P16Emap.ANSELE) = 0xFF;


   periferic16E_rst ();

   for (i = 0; i < pic->ADCCOUNT; i++)
    {
     if (pic->adc[i])
      {
       pic->pins[pic->adc[i] - 1].ptype = PT_ANALOG;
      }
    }
   break;
  case P18:
   if ((abs (flags) == 1)&&(pic->P18map.RCON))
    {
     (*pic->P18map.RCON) = 0x0C;
    }

   *pic->P18map.TRISA = 0xFF;
   *pic->P18map.TRISB = 0xFF;
   *pic->P18map.TRISC = 0xFF;
   if (pic->P18map.TRISD)*pic->P18map.TRISD = 0xFF;
   if (pic->P18map.TRISE)*pic->P18map.TRISE = 0x07;
   if (pic->P18map.PR2)*pic->P18map.PR2 = 0xFF;
   *pic->P18map.STKPTR = 0x00;

   if (pic->P18map.ANSELA)*pic->P18map.ANSELA = 0xFF;
   if (pic->P18map.ANSELB)*pic->P18map.ANSELB = 0xFF;
   if (pic->P18map.ANSELC)*pic->P18map.ANSELC = 0xFF;
   if (pic->P18map.ANSELD)*pic->P18map.ANSELD = 0xFF;
   if (pic->P18map.ANSELE)*pic->P18map.ANSELE = 0xFF;

   periferic18_rst ();

   if (pic->P18map.ANSELA)
    {
     for (i = 0; i < pic->ADCCOUNT; i++)
      {
       if (pic->adc[i])
        {
         pic->pins[pic->adc[i] - 1].ptype = PT_ANALOG;
        }
      }
    }
   break;
  default:
   break;
  }
 
 for(i=0 ; i < SERIAL_MAX; i++)
  {
    pic->serial[i].serialbaud = 9600;
    pic->serial[i].serialexbaud = 9600.0;
  }

 //  pic->debug=0;

 return 1;
}

void
pic_step(void)
{
 switch (pic->family)
  {
  case P16:
   pic_decode_16 ();
   periferic16_step_in ();
   periferic16_step_out ();
   break;
  case P16E:
   pic_decode_16E ();
   periferic16E_step_in ();
   periferic16E_step_out ();
   break;
  case P18:
   pic_decode_18 ();
   periferic18_step_in ();
   periferic18_step_out ();
   break;
  }
}

void
pic_end(void)
{
 if (pic->ram)free (pic->ram);
 if (pic->prog)free (pic->prog);
 if (pic->id)free (pic->id);
 if (pic->config)free (pic->config);
 if (pic->stack)free (pic->stack);
 if (pic->eeprom)free (pic->eeprom);
 if (pic->pins)free (pic->pins);
 if (pic->ccp)free (pic->ccp);
 if (pic->adc)free (pic->adc);
 if (pic->usart_rx)free (pic->usart_rx);
 if (pic->usart_tx)free (pic->usart_tx);

 pic->stop();
 
 pic = NULL;
}

unsigned char
pic_get_pin(unsigned char pin)
{
 if ((pin - 1) < pic->PINCOUNT)
  {
   //     if((pic->pins[(pin-1)].type == P_OC)||(pic->pins[(pin-1)].type == P_OT))
   //     {
   return pic->pins[(pin - 1)].value;
   //     }
   //     else
   //     {
   //       return 0;
   //     } 
  }
 else
  return 0;
};

int
pic_set_pin(unsigned char pin, unsigned char value)
{
 unsigned char val;

 if (pin && ((pin - 1) < pic->PINCOUNT))
  {
   if (pic->pins[(pin - 1)].value == value) return 1;

   if ((pic->pins[(pin - 1)].dir == PD_IN)&&(pic->pins[(pin - 1)].ptype < 3))
    {
     pic->pins[(pin - 1)].value = value;

     if (pic->pins[(pin - 1)].port && pic->pins[(pin - 1)].pord >= 0)
      {
       val = 0x01 << (pic->pins[(pin - 1)].pord);
       if ((pic->pins[(pin - 1)].value) == 1)
        (*pic->pins[(pin - 1)].port) |= val;
       else
        (*pic->pins[(pin - 1)].port) &= ~val;
       switch (pic->family)
        {
        case P16:
         if (pic->processor != P16F84A)
          pic->ram[sfr_addr (pic->pins[(pin - 1)].port) | 0x100] = (*pic->pins[(pin - 1)].port); //espelhamento bank2 = bank0
         break;
        case P16E:
         break;
#ifdef ICSPDBG                    
        case P18:
         if ((pic->pins[(pin - 1)].port == pic->P18map.PORTB)&&((*pic->P18map.DEBUG) & 0x80))
          {
           (*pic->P18map.DEBUG) = ((*pic->P18map.DEBUG)&0xF3) | ((*pic->P18map.PORTB & 0xC0) >> 4); //espelhamento debug
          }
         break;
#endif                  
        }
      }

     return 1;
    }
   else
    {
     return 0;
    }
  }
 else
  return 0;
};

int
pic_set_apin(unsigned char pin, float value)
{

 if (pin && ((pin - 1) < pic->PINCOUNT))
  {
   if (pic->pins[(pin - 1)].avalue == value) return 1;

   if ((pic->pins[(pin - 1)].dir == PD_IN)&&((pic->pins[(pin - 1)].ptype == PT_ANALOG)||(pic->pins[(pin - 1)].ptype == PT_ANAREF)))
    {
     pic->pins[(pin - 1)].avalue = value;
     return 1;
    }
   else
    {
     pic->pins[(pin - 1)].avalue = 0;
     return 0;
    }
  }
 else
  return 0;
}

unsigned char
pic_get_pin_type(unsigned char pin)
{
 if ((pin - 1) < pic->PINCOUNT)
  {
   return pic->pins[(pin - 1)].ptype;
  }
 else
  return 0;
};

unsigned char
pic_get_pin_dir(unsigned char pin)
{
 if ((pin - 1) < pic->PINCOUNT)
  {
   return pic->pins[(pin - 1)].dir;
  }
 else
  return 0;
}

int
pic_set_pin_DOV(unsigned char pin, unsigned char value)
{
 if ((pin - 1) < pic->PINCOUNT)
  {
   if (pic->pins[(pin - 1)].ovalue == value) return 1;

   pic->pins[(pin - 1)].ovalue = value;
   return 1;
  }
 else
  return 0;
}

unsigned char
pic_get_pin_DOV(unsigned char pin)
{
 if ((pin - 1) < pic->PINCOUNT)
  {
   return pic->pins[(pin - 1)].ovalue;
  }
 else
  return 0;
}

void
pic_register(pic_desc picd)
{
 if (PIC_count == PMAX)
  {
   printf ("Error PIC_count > PMAX !\n");
   exit (-1);
  }

 memcpy ((void*) &PICS[PIC_count], (void *) &picd, sizeof (pic_desc));
 PIC_count++;

 //printf ("%02i register PIC 0x%04X family=%i %s \n",PIC_count,  picd.ID, picd.family, picd.name);
}

