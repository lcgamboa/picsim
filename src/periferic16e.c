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

#include "../include/periferic16e.h"
#include "../include/picsim.h"
#include <stdio.h>

extern const int fpw2[];

extern void pic_decode_16E(_pic *pic);

int pic_wr_pin16E(_pic *pic, unsigned char pin, unsigned char value) {
  unsigned char val;

  if ((pin - 1) < pic->PINCOUNT) {
    if (pic->pins[(pin - 1)].value != value) {
      pic->ioupdated = 1;
    }    

    pic->pins[(pin - 1)].value = value;

    if ((pic->pins[(pin - 1)].pord >= 0) && (pic->pins[(pin - 1)].port)) {
      val = 0x01 << (pic->pins[(pin - 1)].pord);
      if ((pic->pins[(pin - 1)].value) == 1)
        (*pic->pins[(pin - 1)].port) |= val;
      else
        (*pic->pins[(pin - 1)].port) &= ~val;
    }
    return 1;
  } else
    return 0;
}

int pic_dir_pin16E(_pic *pic, unsigned char pin, unsigned char dir) {
  unsigned char val = 0;
  unsigned short tris;
  if ((pic->pins[pin - 1].pord >= 0) && (pic->pins[pin - 1].port)) {
    val = 0x01 << (pic->pins[pin - 1].pord);
    tris = sfr_addr(pic->pins[pin - 1].port) +
           (sfr_addr(pic->P16Emap.TRISA) - sfr_addr(pic->P16Emap.PORTA));

    if (dir == PD_OUT) {
      if (pic->ram[tris] & val) {
        pic->pins[pin - 1].dir = PD_OUT;
        pic->ram[tris] &= ~val;
      } else {
        val = 0; // value not changed
      }
    } else {
      if (!(pic->ram[tris] & val)) {
        pic->pins[pin - 1].dir = PD_IN;
        pic->ram[tris] |= val;
      } else {
        val = 0; // value not changed
      }
    }
  }

  if (val) {
    pic->trisa = (*pic->P16Emap.TRISA);
    pic->trisb = (*pic->P16Emap.TRISB);
    pic->trisc = (*pic->P16Emap.TRISC);
    if (pic->P16Emap.TRISD)
      pic->trisd = (*pic->P16Emap.TRISD);
    if (pic->P16Emap.TRISE)
      pic->trise = (*pic->P16Emap.TRISE);
    return 1;
  }
  return 0;
}

void periferic16E_rst(_pic *pic) {

  pic->debug = 0;
  pic->sleep = 0;

  pic->porta = 129; // dummy value to be changed
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

  pic->intlv = 0;

  pic->frst = 1;
}

void periferic16E_step_in(_pic *pic) {

  /*
  //DEBUG
   if((pic->config[0] & 0x0800) == 0) //DEBUG ON
   {
     if(pic->debug == 1)pic->ram[P16E_ICKBUG]|=0x80;
     (*pic->P16Emap.TRISB)|=0xC0;
   }
   */

  pic->periferic(pic);
}

void periferic16E_step_out(_pic *pic) {
  int i, val;

  unsigned short port;
  unsigned short tris;

  // int temp;

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
  /*
  //DEBUG
    if((pic->config[0] & 0x0800) == 0) //DEBUG ON
     {
      pic->ocd_pgca=pic->ocd_pgc;
          pic->ocd_pgc=pic->pins[pic->pgc-1].value;


          if((pic->ram[P16E_ICKBUG] & 0x80) == 0)
          {
            pic->dbg++;
            if((pic->ram[P16E_ICKBUG]&0x20) == 0x20) pic->sstep++;

            if(((pic->ocd_pgca ==1)&&(pic->ocd_pgc == 0)) || //HardWare
                ((pic->pc ==   ((((pic->ram[P16E_ICKBUG]&0x1F)<<8) |
  pic->ram[P16E_BIGBUG])+1))&&(pic->dbg > 3 ))||    //Break Point
                (((pic->ram[P16E_ICKBUG]&0x20) == 0x20)&&(pic->sstep== 3)) )
  //step
            {
            //printf("Debug Halt (%04X)   ",pic->pc);

           // if((pic->ocd_pgca ==1)&&(pic->ocd_pgc == 0)) printf("Hardware
  \n");                                   //HardWare
           // if(pic->pc ==   ((((pic->ram[ICKBUG]&0x1F)<<8) |
  pic->ram[BIGBUG])+1)) printf("Break Point\n");      //Break Point
           // if((pic->ram[ICKBUG]&0x20) == 0x20) printf("sstep!\n");

            if(pic->s2 !=0)pic_decode_16(pic,print);


            for(temp=15;temp>0;temp--)
          pic->stack[temp]=pic->stack[temp-1];
        pic->stack[0]=pic->pc;

        pic->ram[P16E_ICKBUG]|=0x80;
        pic->ram[P16E_ICKBUG]= (pic->ram[P16E_ICKBUG]&0xE0)|((pic->pc &
  0x1F00)>>8); pic->ram[P16E_BIGBUG]=pic->pc & 0x00FF; pic->pc=0x2004;
        pic->s2=1;
            pic->debug=1;

        //printf("----------->dbg  (%#04X) %#02X  %#02X
  \n",ICKBUG,pic->ram[ICKBUG],pic->ram[BIGBUG] );

            };
          };

     };
   */

  // PINOUTS

  if (((*pic->P16Emap.PORTA) != pic->porta) ||
      ((pic->P16Emap.PORTB) && ((*pic->P16Emap.PORTB) != pic->portb)) ||
      ((*pic->P16Emap.PORTC) != pic->portc) ||
      ((pic->P16Emap.PORTD) && ((*pic->P16Emap.PORTD) != pic->portd)) ||
      ((pic->P16Emap.PORTE) && ((*pic->P16Emap.PORTE) != pic->porte))) {
    for (i = 0; i < pic->PINCOUNT; i++) {
      if (pic->pins[i].pord >= 0)
        switch (pic->pins[i].dir) {
        case PD_OUT:
          //	    case 7:
          //               if((pic->ram[RCSTA] & 0x80)==0x80)break;
          //	    case 17:
          //              if((pic->ram[RCSTA] & 0x80)==0x80)break;
          //	   if(pic->pins[i].ptype > 2)break;
          val = 0x01 << (pic->pins[i].pord);
          port = sfr_addr(pic->pins[i].port);
          pic->pins[i].value = ((pic->ram[port] & val) != 0);
          pic->pins[i].lvalue = pic->pins[i].value;
          pic->ioupdated = 1;
          break;
        case PD_IN:
          val = 0x01 << (pic->pins[i].pord);
          // port = sfr_addr (pic->pins[i].port)+256;
          port = sfr_addr(pic->pins[i].port) +
                 (sfr_addr(pic->P16Emap.LATA) - sfr_addr(pic->P16Emap.PORTA));
          pic->pins[i].lvalue = ((pic->ram[port] & val) != 0); // latch
          if (pic->pins[i].ptype > 2)
            pic_wr_pin16E(pic, i + 1, 0);
          else
            pic_wr_pin16E(pic, i + 1, pic->pins[i].value);
          break;
        default:
          break;
        };
    }
    pic->porta = (*pic->P16Emap.PORTA);
    if (pic->P16Emap.PORTB)
      pic->portb = (*pic->P16Emap.PORTB);
    pic->portc = (*pic->P16Emap.PORTC);
    if (pic->P16Emap.PORTD)
      pic->portd = (*pic->P16Emap.PORTD);
    if (pic->P16Emap.PORTE)
      pic->porte = (*pic->P16Emap.PORTE);
  }

  if (((*pic->P16Emap.TRISA) != pic->trisa) ||
      ((pic->P16Emap.TRISD) && ((*pic->P16Emap.TRISB) != pic->trisb)) ||
      ((*pic->P16Emap.TRISC) != pic->trisc) ||
      ((pic->P16Emap.TRISD) && ((*pic->P16Emap.TRISD) != pic->trisd)) ||
      ((pic->P16Emap.TRISE) && ((*pic->P16Emap.TRISE) != pic->trise))) {
    for (i = 0; i < pic->PINCOUNT; i++) {
      if ((pic->pins[i].pord >= 0) && (pic->pins[i].port)) {
        val = 0x01 << (pic->pins[i].pord);
        tris = sfr_addr(pic->pins[i].port) +
               (sfr_addr(pic->P16Emap.TRISA) - sfr_addr(pic->P16Emap.PORTA));
        if ((pic->ram[tris] & val) == 0) {
          pic->pins[i].dir = PD_OUT;
          pic_wr_pin16E(pic, i + 1, pic->pins[i].lvalue);
        } else {
          val = pic->pins[i].dir;
          pic->pins[i].dir = PD_IN;
          if (val != PD_IN)
            pic_wr_pin16E(pic, i + 1, pic->pins[i].ovalue);
        }
      }
    }
    pic->trisa = (*pic->P16Emap.TRISA);
    if (pic->P16Emap.TRISB)
      pic->trisb = (*pic->P16Emap.TRISB);
    pic->trisc = (*pic->P16Emap.TRISC);
    if (pic->P16Emap.TRISD)
      pic->trisd = (*pic->P16Emap.TRISD);
    if (pic->P16Emap.TRISE)
      pic->trise = (*pic->P16Emap.TRISE);
  }

  // interrupt
  if (pic->s2 == 0) {
    if (pic->interrupt(pic)) {
      pic->sleep = 0;

      int bk;
      int offset = 0x007F & sfr_addr(pic->P16Emap.INTCON);
      for (bk = 0; bk < 32; bk++)
        pic->ram[(0x0080 * bk) | offset] &= 0x7F; // disable GIE

      // save shadow
      (*pic->P16Emap.STATUS_SHAD) = (*pic->P16Emap.STATUS);
      (*pic->P16Emap.WREG_SHAD) = (*pic->P16Emap.WREG);
      (*pic->P16Emap.BSR_SHAD) = (*pic->P16Emap.BSR);
      (*pic->P16Emap.PCLATH_SHAD) = (*pic->P16Emap.PCLATH);
      (*pic->P16Emap.FSR0L_SHAD) = (*pic->P16Emap.FSR0L);
      (*pic->P16Emap.FSR0H_SHAD) = (*pic->P16Emap.FSR0H);
      (*pic->P16Emap.FSR1L_SHAD) = (*pic->P16Emap.FSR1L);
      (*pic->P16Emap.FSR1H_SHAD) = (*pic->P16Emap.FSR1H);

      if (pic->print)
        printf("interrupt!");
      for (i = 15; i > 0; i--)
        pic->stack[i] = pic->stack[i - 1];
      pic->stack[0] = pic->pc;
      pic->pc = 0x0004;
      pic->s2 = 1;
    }
  }
}
