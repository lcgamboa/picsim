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


static unsigned short opc;
static unsigned short raddr;
static unsigned short bank;

static inline void fraddr(void)
 {
     if(opc & 0x0100)//a =1
      {
       raddr=bank|(opc & 0x00FF);
      }
     else if(pic->P18map.RCON) //OLD P18
      {
       if(opc & 0x0080)//SFR bank15
        {
         raddr=0xF00|(opc & 0x00FF);
        }
       else //bank0
        {
          raddr=(opc & 0x00FF);
        }
      }
     else //NEW P18
      {
       if((opc&0x00FF) > 0x5F)//SFR bank15
        {
         raddr=0xF00|(opc & 0x00FF);
        }
       else //bank0
        {
          raddr=(opc & 0x00FF);
        }
      }
 }

//TODO add [or not] support to extended instructions 
void
pic_decode_18(void)
{
 unsigned short temp;
 unsigned char ctemp;
 //unsigned short opc;
 //unsigned short bank = (((*pic->P18map.BSR) & 0x0F) << 8);
 bank = (((*pic->P18map.BSR) & 0x0F) << 8);
 unsigned char * status = pic->P18map.STATUS;
 unsigned char * intcon = pic->P18map.INTCON;
 unsigned short afsr0 = (((*pic->P18map.FSR0H)&0x0F) << 8) | (*pic->P18map.FSR0L);
 unsigned short afsr1 = (((*pic->P18map.FSR1H)&0x0F) << 8) | (*pic->P18map.FSR1L);
 unsigned short afsr2 = (((*pic->P18map.FSR2H)&0x0F) << 8) | (*pic->P18map.FSR2L);
 //unsigned short  pc_ant;

 //unsigned short raddr;
 unsigned int tblptr;

 short jrange;

/*
#define  fraddr()\
    if(opc & 0x0100)\
      raddr=bank|(opc & 0x00FF);\
    else\
      if(opc & 0x0080)\
        raddr=0xF00|(opc & 0x00FF);\
      else\
         raddr=(opc & 0x00FF);
*/

 pic->lram = 0x8000;
 pic->rram = 0x8000;

 if (pic->sleep == 1)
  {
   if (pic->print)printf ("sleep WDT=%i wdt=%f ms=%i\n", pic->getconf(CFG_WDT), pic->twdt, pic->wdt);
   return;
  }

#ifdef ICSPDBG   
 if ((!pic->getconf(CFG_DEBUG)&&(!((*pic->P18map.DEBUG)&0x80))&&(pic->frst)&&(pic->pc == 0))
  {
   pic->frst = 0;
   return;
  }
#endif
 
 //incompleto - verificar salto pcl e pch!
 if (pic->s2 == 1)
  {
   pic->s2 = 0;
   if (pic->jpc != 0xFFFFF)
    {
     if (pic->print)printf ("NEW_PC = 0x%06X     OLD_PC = 0x%06X \n", pic->jpc,pic->pc);
     pic->pc = pic->jpc;
     pic->jpc = 0xFFFFF;
    }
   return;
  }

 if (pic->print)printf ("pc=%#06X\t", pic->pc);
 fflush(stdout);
     
 // debug
 if ((pic->pc >= 0x200028)&&((pic->pc <= 0x200037)))
  {
   //int i;
   opc = pic->debugv[pic->pc - 0x200028];
   //printf("PC=0x%04X\n",pic->pc); 
   /*
       for(i=0;i<8;i++)
          printf("debug[%i]=0x%04X\n",i,pic->debugv[i]);
    */
   //if(pic->print)printf("prog=%#06X\t",opc/*pic->prog[pic->pc]*/); 
  }
 else
  {
   opc = pic->prog[pic->pc >> 1];
   //if(pic->print)printf("prog=%#06X\t",pic->debugv[0]); 
  }

 if (pic->print)printf ("prog=%#06X\t", opc);

 pic->pc += 2;
 if (((pic->pc >> 1) >= pic->ROMSIZE)&&(pic->pc != 0x20002A)) pic->pc = 0;

 //pc
 (*pic->P18map.PCL) = pic->pc & 0x00FF;

 //pc_ant = pic->pc&0x00FF;



 (*pic->P18map.INDF0) = pic->ram[afsr0];
 (*pic->P18map.POSTINC0) = pic->ram[afsr0];
 (*pic->P18map.POSTDEC0) = pic->ram[afsr0];
 (*pic->P18map.PREINC0) = pic->ram[(afsr0 + 1) % pic->RAMSIZE];
 (*pic->P18map.PLUSW0) = pic->ram[(afsr0 + ((char) (*pic->P18map.WREG))) % pic->RAMSIZE];

 /*
   if((afsr0+1) < pic->RAMSIZE)
   {
     (*pic->P18map.PREINC0)=pic->ram[afsr0+1];
     if((afsr0+(*pic->P18map.WREG)) < pic->RAMSIZE)
     {
        (*pic->P18map.PLUSW0)=pic->ram[afsr0+((char)(*pic->P18map.WREG))];
     }
     else  
     {
        (*pic->P18map.PLUSW0)=0;
     }
   }
   else
   {
     (*pic->P18map.PREINC0)=0;
     (*pic->P18map.PLUSW0)=0;
   }
  */

 (*pic->P18map.INDF1) = pic->ram[afsr1];
 (*pic->P18map.POSTINC1) = pic->ram[afsr1];
 (*pic->P18map.POSTDEC1) = pic->ram[afsr1];
 (*pic->P18map.PREINC1) = pic->ram[(afsr1 + 1) % pic->RAMSIZE];
 (*pic->P18map.PLUSW1) = pic->ram[(afsr1 + ((char) (*pic->P18map.WREG))) % pic->RAMSIZE];

 /*
   if((afsr1+1) < pic->RAMSIZE)
   {
     (*pic->P18map.PREINC1)=pic->ram[afsr1+1];
     if((afsr1+(*pic->P18map.WREG)) < pic->RAMSIZE)
     {
       (*pic->P18map.PLUSW1)=pic->ram[afsr1+((char)(*pic->P18map.WREG))];
     }
     else
     {
       (*pic->P18map.PLUSW1)=0;
     }
   }
   else
   {
     (*pic->P18map.PREINC1)=0;
     (*pic->P18map.PLUSW1)=0;
   }
  */

 (*pic->P18map.INDF2) = pic->ram[afsr2];
 (*pic->P18map.POSTINC2) = pic->ram[afsr2];
 (*pic->P18map.POSTDEC2) = pic->ram[afsr2];
 (*pic->P18map.PREINC2) = pic->ram[(afsr2 + 1) % pic->RAMSIZE];
 (*pic->P18map.PLUSW2) = pic->ram[(afsr2 + ((char) (*pic->P18map.WREG))) % pic->RAMSIZE];

 /*
   if((afsr2+1) < pic->RAMSIZE)
   {
     (*pic->P18map.PREINC2)=pic->ram[afsr2+1];
     if((afsr2+(*pic->P18map.WREG)) < pic->RAMSIZE)
     {
       (*pic->P18map.PLUSW2)=pic->ram[afsr2+((char)(*pic->P18map.WREG))];
     }
     else
     {
       (*pic->P18map.PLUSW2)=0;
     }
   }
   else
   {
     (*pic->P18map.PREINC2)=0;
     (*pic->P18map.PLUSW2)=0;
   }
  */




 switch (opc & 0xF000)
  {
  case 0x0000:
   switch (opc & 0x0F00)
    {
    case 0x0000:
     switch (opc & 0x00FF)
      {
      case 0x0000:
       //NOP    --   		No Operation                 1     	0000 0000 0000 0000 None
       if (pic->print)printf ("NOP\n");
       break;
      case 0x0003:
       //SLEEP  --   		Go into Standby mode         1     	0000 0000 0000 0011 TO, PD
       if (pic->print)printf ("SLEEP\n");
       pic->wdt = 0;
       pic->twdt = 0;
       pic->sleep = 1;
       if(pic->P18map.RCON)
        {
       (*pic->P18map.RCON) &= ~0x08; //TO
       (*pic->P18map.RCON) |= 0x04;  //PD
        }
       else
        {
        *status &= ~0x40; //TO
        *status |= 0x20; //TD
        }
       break;
      case 0x0004:
       //CLRWDT --   		Clear Watchdog Timer         1     	0000 0000 0000 0100 TO, PD
       if (pic->print)printf ("CLRWDT\n");
       pic->wdt = 0;
       pic->twdt = 0;
       if(pic->P18map.RCON)
        {
       (*pic->P18map.RCON) |= 0x08; //TO
       (*pic->P18map.RCON) |= 0x04; //PD
        }
       else
        {
        *status |= 0x40; //TO
        *status |= 0x20; //TD
        }
       break;
      case 0x0005:
       //PUSH   --   		Push top of ret stack(TOS)   1     	0000 0000 0000 0101 None
       if (pic->print)printf ("PUSH \n");
       if (((*pic->P18map.STKPTR) & 0x1F) < 31)
        {
         pic->stack[(*pic->P18map.STKPTR)& 0x1F] = pic->pc;
         (*pic->P18map.STKPTR) = ((*pic->P18map.STKPTR) &0xC0) | (((*pic->P18map.STKPTR) &0x1F) + 1);
         if (((*pic->P18map.STKPTR)& 0x1F) == 31)(*pic->P18map.STKPTR) |= 0x80; //set STKFUL
        }
       pic->lram = sfr_addr (pic->P18map.STKPTR);
       break;
      case 0x0006:
       //POP    --   		Pop top of ret stack(TOS)    1     	0000 0000 0000 0110 None
       if (pic->print)printf ("POP \n");
       if (((*pic->P18map.STKPTR) & 0x1F) > 0)
        {
         (*pic->P18map.STKPTR) = ((*pic->P18map.STKPTR) &0xC0) | (((*pic->P18map.STKPTR) &0x1F) - 1);
        }
       else
        (*pic->P18map.STKPTR) |= 0x40; //set STKUNF  
       pic->lram = sfr_addr (pic->P18map.STKPTR);
       break;
      case 0x0007:
       //DAW    --   		Decimal Adjust WREG          1     	0000 0000 0000 0111 C
       if (pic->print)printf ("DAW \n");
       pic->lram = sfr_addr (pic->P18map.WREG);

       if ((((*pic->P18map.WREG)&0x0F) > 9) | (*status & 0x02))
        {
         temp = ((*pic->P18map.WREG) & 0x0F) + 6;
        }
       else
        {
         temp = (*pic->P18map.WREG) & 0x0F;
        }
       if ((((*pic->P18map.WREG)&0xF0) >> 4 > 9) | (*status & 0x01))
        {
         temp |= ((*pic->P18map.WREG)&0xF0) + 0x60;
        }
       else
        {
         temp |= (*pic->P18map.WREG)&0xF0;
        }

       if ((0x00FF & temp) == 0xFF)
        *status |= 0x01;
       else
        *status &= ~0x01;

       (*pic->P18map.WREG) = (temp & 0x00FF);
       break;
      case 0x0008:
       //TBLRD*       		Table Read                   2     	0000 0000 0000 1000 None
       if (pic->print)printf ("TBLRD *\n");
       tblptr = ((*pic->P18map.TBLPTRU) << 16) | ((*pic->P18map.TBLPTRH) << 8) | (*pic->P18map.TBLPTRL);
       if ((tblptr >> 1) < pic->ROMSIZE)
        {
         if (tblptr & 0x0001)
          (*pic->P18map.TABLAT) = (pic->prog[tblptr >> 1]&0xFF00) >> 8;
         else
          (*pic->P18map.TABLAT) = pic->prog[tblptr >> 1]&0x00FF;
        }
        //read id
       else if ((tblptr >= 0x200000)&&(tblptr <= 0x200007))
        {
         if (tblptr & 0x0001)
          (*pic->P18map.TABLAT) = (pic->id[(tblptr - 0x200000) >> 1]&0xFF00) >> 8;
         else
          (*pic->P18map.TABLAT) = (pic->id[(tblptr - 0x200000) >> 1]&0x00FF);
        }
        //read config
       else if ((tblptr >= 0x300000)&&(tblptr <= 0x30000D))
        {
         if (tblptr & 0x0001)
          (*pic->P18map.TABLAT) = (pic->config[(tblptr - 0x300000) >> 1]&0xFF00) >> 8;
         else
          (*pic->P18map.TABLAT) = (pic->config[(tblptr - 0x300000) >> 1]&0x00FF);
        }
        //read device id 
       else if ((tblptr & 0x3FFFFE) == 0x3FFFFE)
        {
         if (tblptr & 0x0001)
          (*pic->P18map.TABLAT) = (pic->processor & 0xFF00) >> 8;
         else
          (*pic->P18map.TABLAT) = (pic->processor & 0x00FF);
        }
        //read debug vector 
       else if ((tblptr >= 0x200028)&&(tblptr <= 0x200037))
        {
         if (tblptr & 0x0001)
          (*pic->P18map.TABLAT) = (pic->debugv[(tblptr - 0x200028) >> 1]&0xFF00) >> 8;
         else
          (*pic->P18map.TABLAT) = (pic->debugv[(tblptr - 0x200028) >> 1]&0x00FF);
        }
       else
        (*pic->P18map.TABLAT) = 0;
       pic->s2 = 1;
       break;
      case 0x0009:
       //TBLRD*+      		Table Read with post-inc     2 (5)   	0000 0000 0000 1001 None
       if (pic->print)printf ("TBLRD *+\n");
       tblptr = ((*pic->P18map.TBLPTRU) << 16) | ((*pic->P18map.TBLPTRH) << 8) | (*pic->P18map.TBLPTRL);
       if ((tblptr >> 1) < pic->ROMSIZE)
        {
         if (tblptr & 0x0001)
          (*pic->P18map.TABLAT) = (pic->prog[tblptr >> 1]&0xFF00) >> 8;
         else
          (*pic->P18map.TABLAT) = pic->prog[tblptr >> 1]&0x00FF;
        }
        //read id
       else if ((tblptr >= 0x200000)&&(tblptr <= 0x200007))
        {
         if (tblptr & 0x0001)
          (*pic->P18map.TABLAT) = (pic->id[(tblptr - 0x200000) >> 1]&0xFF00) >> 8;
         else
          (*pic->P18map.TABLAT) = (pic->id[(tblptr - 0x200000) >> 1]&0x00FF);
        }
        //read config
       else if ((tblptr >= 0x300000)&&(tblptr <= 0x30000D))
        {
         if (tblptr & 0x0001)
          (*pic->P18map.TABLAT) = (pic->config[(tblptr - 0x300000) >> 1]&0xFF00) >> 8;
         else
          (*pic->P18map.TABLAT) = (pic->config[(tblptr - 0x300000) >> 1]&0x00FF);
        }
        //read device id 
       else if ((tblptr & 0x3FFFFE) == 0x3FFFFE)
        {
         if (tblptr & 0x0001)
          (*pic->P18map.TABLAT) = (pic->processor & 0xFF00) >> 8;
         else
          (*pic->P18map.TABLAT) = (pic->processor & 0x00FF);
        }
        //read debug vector 
       else if ((tblptr >= 0x200028)&&(tblptr <= 0x200037))
        {
         if (tblptr & 0x0001)
          (*pic->P18map.TABLAT) = (pic->debugv[(tblptr - 0x200028) >> 1]&0xFF00) >> 8;
         else
          (*pic->P18map.TABLAT) = (pic->debugv[(tblptr - 0x200028) >> 1]&0x00FF);
        }
       else
        (*pic->P18map.TABLAT) = 0;
       tblptr++;
       (*pic->P18map.TBLPTRU) = (tblptr & 0x3F0000) >> 16;
       (*pic->P18map.TBLPTRH) = (tblptr & 0x00FF00) >> 8;
       (*pic->P18map.TBLPTRL) = (tblptr & 0x0000FF);
       pic->s2 = 1;
       break;
      case 0x000A:
       //TBLRD*-      		Table Read with post-dec     2 (5)   	0000 0000 0000 1010 None
       if (pic->print)printf ("TBLRD *-\n");
       tblptr = ((*pic->P18map.TBLPTRU) << 16) | ((*pic->P18map.TBLPTRH) << 8) | (*pic->P18map.TBLPTRL);
       if ((tblptr >> 1) < pic->ROMSIZE)
        {
         if (tblptr & 0x0001)
          (*pic->P18map.TABLAT) = (pic->prog[tblptr >> 1]&0xFF00) >> 8;
         else
          (*pic->P18map.TABLAT) = pic->prog[tblptr >> 1]&0x00FF;
        }
        //read id
       else if ((tblptr >= 0x200000)&&(tblptr <= 0x200007))
        {
         if (tblptr & 0x0001)
          (*pic->P18map.TABLAT) = (pic->id[(tblptr - 0x200000) >> 1]&0xFF00) >> 8;
         else
          (*pic->P18map.TABLAT) = (pic->id[(tblptr - 0x200000) >> 1]&0x00FF);
        }
        //read config
       else if ((tblptr >= 0x300000)&&(tblptr <= 0x30000D))
        {
         if (tblptr & 0x0001)
          (*pic->P18map.TABLAT) = (pic->config[(tblptr - 0x300000) >> 1]&0xFF00) >> 8;
         else
          (*pic->P18map.TABLAT) = (pic->config[(tblptr - 0x300000) >> 1]&0x00FF);
        }
        //read device id 
       else if ((tblptr & 0x3FFFFE) == 0x3FFFFE)
        {
         if (tblptr & 0x0001)
          (*pic->P18map.TABLAT) = (pic->processor & 0xFF00) >> 8;
         else
          (*pic->P18map.TABLAT) = (pic->processor & 0x00FF);
        }
        //read debug vector 
       else if ((tblptr >= 0x200028)&&(tblptr <= 0x200037))
        {
         if (tblptr & 0x0001)
          (*pic->P18map.TABLAT) = (pic->debugv[(tblptr - 0x200028) >> 1]&0xFF00) >> 8;
         else
          (*pic->P18map.TABLAT) = (pic->debugv[(tblptr - 0x200028) >> 1]&0x00FF);
        }
       else
        (*pic->P18map.TABLAT) = 0;
       tblptr--;
       (*pic->P18map.TBLPTRU) = (tblptr & 0x3F0000) >> 16;
       (*pic->P18map.TBLPTRH) = (tblptr & 0x00FF00) >> 8;
       (*pic->P18map.TBLPTRL) = (tblptr & 0x0000FF);
       pic->s2 = 1;
       break;
      case 0x000B:
       //TBLRD+*      		Table Read with pre-inc      2 (5)   	0000 0000 0000 1011 None
       if (pic->print)printf ("TBLRD +*\n");
       tblptr = ((*pic->P18map.TBLPTRU) << 16) | ((*pic->P18map.TBLPTRH) << 8) | (*pic->P18map.TBLPTRL);
       tblptr = (tblptr + 1)&0x001FFFFF;
       if ((tblptr >> 1) < pic->ROMSIZE)
        {
         if (tblptr & 0x0001)
          (*pic->P18map.TABLAT) = (pic->prog[tblptr >> 1]&0xFF00) >> 8;
         else
          (*pic->P18map.TABLAT) = pic->prog[tblptr >> 1]&0x00FF;
        }
        //read id
       else if ((tblptr >= 0x200000)&&(tblptr <= 0x200007))
        {
         if (tblptr & 0x0001)
          (*pic->P18map.TABLAT) = (pic->id[(tblptr - 0x200000) >> 1]&0xFF00) >> 8;
         else
          (*pic->P18map.TABLAT) = (pic->id[(tblptr - 0x200000) >> 1]&0x00FF);
        }
        //read config
       else if ((tblptr >= 0x300000)&&(tblptr <= 0x30000D))
        {
         if (tblptr & 0x0001)
          (*pic->P18map.TABLAT) = (pic->config[(tblptr - 0x300000) >> 1]&0xFF00) >> 8;
         else
          (*pic->P18map.TABLAT) = (pic->config[(tblptr - 0x300000) >> 1]&0x00FF);
        }
        //read device id 
       else if ((tblptr & 0x3FFFFE) == 0x3FFFFE)
        {
         if (tblptr & 0x0001)
          (*pic->P18map.TABLAT) = (pic->processor & 0xFF00) >> 8;
         else
          (*pic->P18map.TABLAT) = (pic->processor & 0x00FF);
        }
        //read debug vector 
       else if ((tblptr >= 0x200028)&&(tblptr <= 0x200037))
        {
         if (tblptr & 0x0001)
          (*pic->P18map.TABLAT) = (pic->debugv[(tblptr - 0x200028) >> 1]&0xFF00) >> 8;
         else
          (*pic->P18map.TABLAT) = (pic->debugv[(tblptr - 0x200028) >> 1]&0x00FF);
        }
       else
        (*pic->P18map.TABLAT) = 0;
       (*pic->P18map.TBLPTRU) = (tblptr & 0x3F0000) >> 16;
       (*pic->P18map.TBLPTRH) = (tblptr & 0x00FF00) >> 8;
       (*pic->P18map.TBLPTRL) = (tblptr & 0x0000FF);
       pic->s2 = 1;
       break;
      case 0x000C:
       //TBLWT*       		Table Write                  2 (5) 	0000 0000 0000 1100 None
       if (pic->print)printf ("TBLWT *\n");
       tblptr = ((*pic->P18map.TBLPTRU) << 16) | ((*pic->P18map.TBLPTRH) << 8) | (*pic->P18map.TBLPTRL);
       if ((tblptr >> 1) < pic->ROMSIZE)
        {
         if (tblptr & 0x0001)
          pic->prog[tblptr >> 1] = (pic->prog[tblptr >> 1]&0x00FF) | (*pic->P18map.TABLAT) << 8;
         else
          pic->prog[tblptr >> 1] = (pic->prog[tblptr >> 1]&0xFF00) | (*pic->P18map.TABLAT);
        }
        //write id
       else if ((tblptr >= 0x200000)&&(tblptr <= 0x200007))
        {
         if (tblptr & 0x0001)
          pic->id[(tblptr - 0x200000) >> 1] = (pic->id[(tblptr - 0x200000) >> 1]&0x00FF) | (*pic->P18map.TABLAT) << 8;
         else
          pic->id[(tblptr - 0x200000) >> 1] = (pic->id[(tblptr - 0x200000) >> 1]&0xFF00) | (*pic->P18map.TABLAT);
        }
        //write config
       else if ((tblptr >= 0x300000)&&(tblptr <= 0x30000D))
        {
         if (tblptr & 0x0001)
          pic->config[(tblptr - 0x300000) >> 1] = (pic->config[(tblptr - 0x300000) >> 1]&0x00FF) | (*pic->P18map.TABLAT) << 8;
         else
          pic->config[(tblptr - 0x300000) >> 1] = (pic->config[(tblptr - 0x300000) >> 1]&0xFF00) | (*pic->P18map.TABLAT);

         printf ("TBLWT* 0x%06X   0x%02lX \n", tblptr, sfr_addr (pic->P18map.TABLAT));
        }
        //debug vector  
       else if ((tblptr >= 0x200028)&&(tblptr <= 0x200037))
        {
         if (tblptr & 0x0001)
          pic->debugv[(tblptr - 0x200028) >> 1] = (pic->debugv[(tblptr - 0x200028) >> 1]&0x00FF) | (*pic->P18map.TABLAT) << 8;
         else
          pic->debugv[(tblptr - 0x200028) >> 1] = (pic->debugv[(tblptr - 0x200028) >> 1]&0xFF00) | (*pic->P18map.TABLAT);
        }

       pic->s2 = 1;
       break;
      case 0x000D:
       //TBLWT*+      		Table Write with post-inc    2 (5)   	0000 0000 0000 1101 None
       if (pic->print)printf ("TBLWT *+\n");
       tblptr = ((*pic->P18map.TBLPTRU) << 16) | ((*pic->P18map.TBLPTRH) << 8) | (*pic->P18map.TBLPTRL);
       if ((tblptr >> 1) < pic->ROMSIZE)
        {
         if (tblptr & 0x0001)
          pic->prog[tblptr >> 1] = (pic->prog[tblptr >> 1]&0x00FF) | (*pic->P18map.TABLAT) << 8;
         else
          pic->prog[tblptr >> 1] = (pic->prog[tblptr >> 1]&0xFF00) | (*pic->P18map.TABLAT);
        }
        //write id
       else if ((tblptr >= 0x200000)&&(tblptr <= 0x200007))
        {
         if (tblptr & 0x0001)
          pic->id[(tblptr - 0x200000) >> 1] = (pic->id[(tblptr - 0x200000) >> 1]&0x00FF) | (*pic->P18map.TABLAT) << 8;
         else
          pic->id[(tblptr - 0x200000) >> 1] = (pic->id[(tblptr - 0x200000) >> 1]&0xFF00) | (*pic->P18map.TABLAT);
        }
        //write config
       else if ((tblptr >= 0x300000)&&(tblptr <= 0x30000D))
        {
         if (tblptr & 0x0001)
          pic->config[(tblptr - 0x300000) >> 1] = (pic->config[(tblptr - 0x300000) >> 1]&0x00FF) | (*pic->P18map.TABLAT) << 8;
         else
          pic->config[(tblptr - 0x300000) >> 1] = (pic->config[(tblptr - 0x300000) >> 1]&0xFF00) | (*pic->P18map.TABLAT);
         printf ("TBLWT*+ 0x%06X   0x%02lX \n", tblptr, sfr_addr (pic->P18map.TABLAT));
        }
        //debug vector  
       else if ((tblptr >= 0x200028)&&(tblptr <= 0x200037))
        {
         if (tblptr & 0x0001)
          pic->debugv[(tblptr - 0x200028) >> 1] = (pic->debugv[(tblptr - 0x200028) >> 1]&0x00FF) | (*pic->P18map.TABLAT) << 8;
         else
          pic->debugv[(tblptr - 0x200028) >> 1] = (pic->debugv[(tblptr - 0x200028) >> 1]&0xFF00) | (*pic->P18map.TABLAT);
        }
       tblptr++;
       (*pic->P18map.TBLPTRU) = (tblptr & 0x3F0000) >> 16;
       (*pic->P18map.TBLPTRH) = (tblptr & 0x00FF00) >> 8;
       (*pic->P18map.TBLPTRL) = (tblptr & 0x0000FF);
       pic->s2 = 1;
       break;
      case 0x000E:
       //TBLWT*-      		Table Write with post-dec    2 (5)   	0000 0000 0000 1110 None
       if (pic->print)printf ("TBLWT *-\n");
       tblptr = ((*pic->P18map.TBLPTRU) << 16) | ((*pic->P18map.TBLPTRH) << 8) | (*pic->P18map.TBLPTRL);
       if ((tblptr >> 1) < pic->ROMSIZE)
        {
         if (tblptr & 0x0001)
          pic->prog[tblptr >> 1] = (pic->prog[tblptr >> 1]&0x00FF) | (*pic->P18map.TABLAT) << 8;
         else
          pic->prog[tblptr >> 1] = (pic->prog[tblptr >> 1]&0xFF00) | (*pic->P18map.TABLAT);
        }
        //write id
       else if ((tblptr >= 0x200000)&&(tblptr <= 0x200007))
        {
         if (tblptr & 0x0001)
          pic->id[(tblptr - 0x200000) >> 1] = (pic->id[(tblptr - 0x200000) >> 1]&0x00FF) | (*pic->P18map.TABLAT) << 8;
         else
          pic->id[(tblptr - 0x200000) >> 1] = (pic->id[(tblptr - 0x200000) >> 1]&0xFF00) | (*pic->P18map.TABLAT);
        }
        //write config
       else if ((tblptr >= 0x300000)&&(tblptr <= 0x30000D))
        {
         if (tblptr & 0x0001)
          pic->config[(tblptr - 0x300000) >> 1] = (pic->config[(tblptr - 0x300000) >> 1]&0x00FF) | (*pic->P18map.TABLAT) << 8;
         else
          pic->config[(tblptr - 0x300000) >> 1] = (pic->config[(tblptr - 0x300000) >> 1]&0xFF00) | (*pic->P18map.TABLAT);
         printf ("TBLWT*- 0x%06X   0x%02lX \n", tblptr, sfr_addr (pic->P18map.TABLAT));
        }
        //debug vector  
       else if ((tblptr >= 0x200028)&&(tblptr <= 0x200037))
        {
         if (tblptr & 0x0001)
          pic->debugv[(tblptr - 0x200028) >> 1] = (pic->debugv[(tblptr - 0x200028) >> 1]&0x00FF) | (*pic->P18map.TABLAT) << 8;
         else
          pic->debugv[(tblptr - 0x200028) >> 1] = (pic->debugv[(tblptr - 0x200028) >> 1]&0xFF00) | (*pic->P18map.TABLAT);
        }
       tblptr--;
       (*pic->P18map.TBLPTRU) = (tblptr & 0x3F0000) >> 16;
       (*pic->P18map.TBLPTRH) = (tblptr & 0x00FF00) >> 8;
       (*pic->P18map.TBLPTRL) = (tblptr & 0x0000FF);
       pic->s2 = 1;
       break;
      case 0x000F:
       //TBLWT+*      		Table Write with pre-inc     2 (5)   	0000 0000 0000 1111 None
       if (pic->print)printf ("TBLWT +*\n");
       tblptr = ((*pic->P18map.TBLPTRU) << 16) | ((*pic->P18map.TBLPTRH) << 8) | (*pic->P18map.TBLPTRL);
       tblptr = (tblptr + 1)&0x001FFFFF;
       if ((tblptr >> 1) < pic->ROMSIZE)
        {
         if (tblptr & 0x0001)
          pic->prog[tblptr >> 1] = (pic->prog[tblptr >> 1]&0x00FF) | (*pic->P18map.TABLAT) << 8;
         else
          pic->prog[tblptr >> 1] = (pic->prog[tblptr >> 1]&0xFF00) | (*pic->P18map.TABLAT);
        }
        //write id
       else if ((tblptr >= 0x200000)&&(tblptr <= 0x200007))
        {
         if (tblptr & 0x0001)
          pic->id[(tblptr - 0x200000) >> 1] = (pic->id[(tblptr - 0x200000) >> 1]&0x00FF) | (*pic->P18map.TABLAT) << 8;
         else
          pic->id[(tblptr - 0x200000) >> 1] = (pic->id[(tblptr - 0x200000) >> 1]&0xFF00) | (*pic->P18map.TABLAT);
        }
        //write config
       else if ((tblptr >= 0x300000)&&(tblptr <= 0x30000D))
        {
         if (tblptr & 0x0001)
          pic->config[(tblptr - 0x300000) >> 1] = (pic->config[(tblptr - 0x300000) >> 1]&0x00FF) | (*pic->P18map.TABLAT) << 8;
         else
          pic->config[(tblptr - 0x300000) >> 1] = (pic->config[(tblptr - 0x300000) >> 1]&0xFF00) | (*pic->P18map.TABLAT);
         printf ("TBLWT+* 0x%06X   0x%02lX \n", tblptr, sfr_addr (pic->P18map.TABLAT));
        }
        //debug vector  
       else if ((tblptr >= 0x200028)&&(tblptr <= 0x200037))
        {
         if (tblptr & 0x0001)
          pic->debugv[(tblptr - 0x200028) >> 1] = (pic->debugv[(tblptr - 0x200028) >> 1]&0x00FF) | (*pic->P18map.TABLAT) << 8;
         else
          pic->debugv[(tblptr - 0x200028) >> 1] = (pic->debugv[(tblptr - 0x200028) >> 1]&0xFF00) | (*pic->P18map.TABLAT);
        }
       (*pic->P18map.TBLPTRU) = (tblptr & 0x3F0000) >> 16;
       (*pic->P18map.TBLPTRH) = (tblptr & 0x00FF00) >> 8;
       (*pic->P18map.TBLPTRL) = (tblptr & 0x0000FF);
       pic->s2 = 1;
       break;
      case 0x0010:
      case 0x0011:
       //RETFIE s    		Return from interrupt enable 2     	0000 0000 0001 000s GIE/GIEH,PEIE/GIEL
       if (pic->print)printf ("RETFIE\n");

       if (((*pic->P18map.STKPTR) & 0x1F) > 0)
        {
         (*pic->P18map.STKPTR) = ((*pic->P18map.STKPTR) &0xC0) | (((*pic->P18map.STKPTR) &0x1F) - 1);
         pic->jpc = pic->stack[(*pic->P18map.STKPTR) & 0x1F];
        }
       else
        {
         (*pic->P18map.STKPTR) |= 0x40; //set STKUNF  
         pic->jpc = 0;
        }
       pic->lram = sfr_addr (pic->P18map.STKPTR);

       pic->s2 = 1;


       if (pic->intlv & 0x02)
        {
         *intcon |= 0x40;
         pic->intlv &= ~0x02;
        }
       else
        {
         *intcon |= 0x80;
         pic->intlv &= ~0x01;
        }

       if (opc & 0x0001)
        {
         (*pic->P18map.WREG) = pic->P18map.WS;
         (*pic->P18map.STATUS) = pic->P18map.STATUSS;
         (*pic->P18map.BSR) = pic->P18map.BSRS;
        }
       break;
      case 0x0012:
      case 0x0013:
       //RETURN s    		Return from Subroutine       2     	0000 0000 0001 001s None
       if (pic->print)printf ("RETURN %d\n", opc & 0x0001);
       if (((*pic->P18map.STKPTR) & 0x1F) > 0)
        {
         (*pic->P18map.STKPTR) = ((*pic->P18map.STKPTR) &0xC0) | (((*pic->P18map.STKPTR) &0x1F) - 1);
         pic->jpc = pic->stack[(*pic->P18map.STKPTR) & 0x1F];
        }
       else
        {
         (*pic->P18map.STKPTR) |= 0x40; //set STKUNF  
         pic->jpc = 0;
         if (pic->print)printf ("STKUNF !!!!!!!\n");
        }
       pic->lram = sfr_addr (pic->P18map.STKPTR);

       pic->s2 = 1;

       if (opc & 0x0001)
        {
         (*pic->P18map.WREG) = pic->P18map.WS;
         (*pic->P18map.STATUS) = pic->P18map.STATUSS;
         (*pic->P18map.BSR) = pic->P18map.BSRS;
        }
       /* debug 
   if((pic->ram[ICKBUG] & 0x80)== 0x80)printf("Out DEBUG mode\n");
   pic->debug=0;
       pic->sstep=0;          
       pic->dbg=0;          
   pic->ram[ICKBUG]&=~0x80;
        */
       break;
      case 0x00E0:
       //TRAP    		GOTO debug vector 	       2     	0000 0000 1110 0000 None
       if (pic->print)printf ("TRAP\n");
#ifdef ICSPDBG 
       if (pic->getconf(CFG_DEBUG) //DEBUG ON
        {
         if (pic->pc != 0x00000)
          {
           //printf("Debug stack save\n");
           if (((*pic->P18map.STKPTR) & 0x1F) < 31)
            {
             pic->stack[(*pic->P18map.STKPTR)& 0x1F] = pic->pc;
             (*pic->P18map.STKPTR) = ((*pic->P18map.STKPTR) &0xC0) | (((*pic->P18map.STKPTR) &0x1F) + 1);
             if (((*pic->P18map.STKPTR)& 0x1F) == 31)(*pic->P18map.STKPTR) |= 0x80; //set STKFUL
            }
           pic->lram = sfr_addr (pic->P18map.STKPTR);
          }
         (*pic->P18map.DEBUG) |= 0x80;
         (*pic->P18map.BDMSR2) = (pic->pc & 0xFF0000) >> 16;
         (*pic->P18map.BDMSR1) = (pic->pc & 0x00FF00) >> 8;
         (*pic->P18map.BDMSR0) = (pic->pc & 0x0000FF);
        
         pic->jpc = 0x200028;
         pic->s2 = 1;
         pic->debug = 1;
         pic->sstep = 0;
        }
#endif        
       break;
      case 0x00E1:
       //TRET    		Return Debug Subroutine       2     	0000 0000 1110 0001 None
       if (pic->print)printf ("TRET\n");
       if (((*pic->P18map.STKPTR) & 0x1F) > 0)
        {
         (*pic->P18map.STKPTR) = ((*pic->P18map.STKPTR) &0xC0) | (((*pic->P18map.STKPTR) &0x1F) - 1);
         pic->jpc = pic->stack[(*pic->P18map.STKPTR) & 0x1F];
        }
       else
        {
         (*pic->P18map.STKPTR) |= 0x40; //set STKUNF  
         pic->jpc = 0;
        }
       pic->lram = sfr_addr (pic->P18map.STKPTR);
       pic->s2 = 1;
       /*	  
                     if(opc & 0x0001 )
                     {
                       (*pic->P18map.WREG)=(*pic->P18map.WS); 	 
                       (*pic->P18map.STATUS)=(*pic->P18map.STATUSS);
                       (*pic->P18map.BSR)=(*pic->P18map.BSRS);
                      }
        */
       //if(((*pic->P18map.DEBUG) & 0x80)== 0x80)printf("Out DEBUG mode\n");
       pic->debug = 0;
       pic->sstep = 0;
       pic->dbg = 0;
#ifdef ICSPDBG        
       (*pic->P18map.DEBUG) &= ~0x80;
#endif      
       break;

       //RESET       		Software device RESET        1     	0000 0000 1111 1111 All
      case 0x00FF:
       if (pic->print)printf ("RESET\n");
       pic_reset (0);
       return;
       break;
      default:
       printf ("unknown opcode 0x%04X at 0x%06X !\n", opc, pic->pc-2);
       break;
      }
     break;
    case 0x0100:
     //MOVLB    k    	Move literal to BSR<3:0>     1     	0000 0001 0000 kkkk None
     if (pic->print)printf ("MOVLB %#04X\n", opc & 0x000F);
     (*pic->P18map.BSR) = (opc & 0x000F);
     pic->lram = sfr_addr (pic->P18map.BSR);
     break;
    case 0x0200:
    case 0x0300:
     //MULWF  f, a    	Multiply WREG with f         1          0000 001a ffff ffff None
     if (pic->print)printf ("MULWF %#06X,%d\n", opc & 0x00FF, (opc & 0x0100) >> 8);
     fraddr ();
     temp = (*pic->P18map.WREG) * pic->ram[raddr];
     (*pic->P18map.PRODH) = (temp & 0xFF00) >> 8;
     (*pic->P18map.PRODL) = temp & 0x00FF;
     pic->rram = raddr;
     pic->lram = sfr_addr (pic->P18map.PRODH);
     break;
    case 0x0400:
    case 0x0500:
    case 0x0600:
    case 0x0700:
     //DECF   f, d, a 	Decrement f                  1          0000 01da ffff ffff C, DC, Z, OV, N 1, 2, 3, 4
     if (pic->print)printf ("DECF %#06X,%d,%d\n", opc & 0x00FF, (opc & 0x0200) >> 9, (opc & 0x0100) >> 8);
     fraddr ();
     if ((0xF0 & ((0x0F & (pic->ram[raddr])) + 0x0F)) != 0)
      *status |= 0x02;
     else
      *status &= ~0x02;
     pic->rram = raddr;
     temp = pic->ram[raddr] - 1;

     if ((0x00FF & temp) == 0xFF)
      *status &= ~0x01;
     else
      *status |= 0x01;

     ctemp = (unsigned char) (0x00FF & temp);

     if (opc & 0x0200) //dest FILE
      {
       if ((pic->ram[raddr] & 0x80) != (ctemp & 0x80))
        *status |= 0x08;
       else
        *status &= ~0x08;
       pic->lram = raddr;
       pic->ram[raddr] = ctemp;

       if (pic->ram[raddr] == 0)
        *status |= 0x04;
       else
        *status &= ~0x04;
       if (pic->ram[raddr] & 0x80)
        *status |= 0x10;
       else
        *status &= ~0x10;

      }
     else //dest W     
      {
       if (((*pic->P18map.WREG) & 0x80) != (ctemp & 0x80))
        *status |= 0x08;
       else
        *status &= ~0x08;
       pic->lram = sfr_addr (pic->P18map.WREG);
       (*pic->P18map.WREG) = ctemp;
       if ((*pic->P18map.WREG) == 0)
        *status |= 0x04;
       else
        *status &= ~0x04;
       if ((*pic->P18map.WREG) & 0x80)
        *status |= 0x10;
       else
        *status &= ~0x10;
      }
     break;
    case 0x0800:
     //SUBLW    k    	Subtract WREG from literal   1     	0000 1000 kkkk kkkk C, DC, Z, OV, N
     if (pic->print)printf ("SUBLW %#06X\n", opc & 0x00FF);

     if ((0xF0 & ((0x0F & (~(*pic->P18map.WREG))) + 1 + (opc & 0x000F))) != 0)
      *status |= 0x02;
     else
      *status &= ~0x02;

     pic->lram = sfr_addr (pic->P18map.WREG);

     temp = (~(*pic->P18map.WREG) + 1)+(opc & 0x00FF);

     ctemp = (unsigned char) (0x00FF & temp);

     *status &= ~0x08;
     /* incompleto
   if (((*pic->P18map.WREG) & 0x80)!=(ctemp&0x80))  
      *status|=0x08;
   else   
      *status&=~0x08;
      */

     (*pic->P18map.WREG) = ctemp;

     if ((0xFF00 & temp) != 0)
      *status &= ~0x01;
     else
      *status |= 0x01;

     if ((*pic->P18map.WREG) == 0)
      *status |= 0x04;
     else
      *status &= ~0x04;
     
     if ((*pic->P18map.WREG) & 0x80)
      *status |= 0x10;
     else
      *status &= ~0x10;
     break;
    case 0x0900:
     //IORLW    k    	Inclusive OR literalw/ WREG  1     	0000 1001 kkkk kkkk Z, N
     if (pic->print)printf ("IORLW %#06X\n", opc & 0x00FF);
     (*pic->P18map.WREG) |= (opc & 0x00FF);
     pic->lram = sfr_addr (pic->P18map.WREG);
     if ((*pic->P18map.WREG) == 0)
      *status |= 0x04;
     else
      *status &= ~0x04;
     if ((*pic->P18map.WREG) & 0x80)
      *status |= 0x10;
     else
      *status &= ~0x10;
     break;
    case 0x0A00:
     //XORLW    k    	Exclusive OR literal w\WREG  1     	0000 1010 kkkk kkkk Z, N
     if (pic->print)printf ("XORLW %#06X\n", opc & 0x00FF);
     (*pic->P18map.WREG) ^= (opc & 0x00FF);
     pic->lram = sfr_addr (pic->P18map.WREG);
     if ((*pic->P18map.WREG) == 0)
      *status |= 0x04;
     else
      *status &= ~0x04;
     if ((*pic->P18map.WREG) & 0x80)
      *status |= 0x10;
     else
      *status &= ~0x10;
     break;
    case 0x0B00:
     //ANDLW    k    	AND literal with WREG        1     	0000 1011 kkkk kkkk Z, N
     if (pic->print)printf ("ANDLW %#06X\n", opc & 0x00FF);
     (*pic->P18map.WREG) &= (opc & 0x00FF);
     pic->lram = sfr_addr (pic->P18map.WREG);
     if ((*pic->P18map.WREG) == 0)
      *status |= 0x04;
     else
      *status &= ~0x04;
     if ((*pic->P18map.WREG) & 0x80)
      *status |= 0x10;
     else
      *status &= ~0x10;
     break;
    case 0x0C00:
     //RETLW    k    	Return with literal in WREG  2     	0000 1100 kkkk kkkk None
     if (pic->print)printf ("RETLW %#06X\n", opc & 0x00FF);
     if (((*pic->P18map.STKPTR) & 0x1F) > 0)
      {
       (*pic->P18map.STKPTR) = ((*pic->P18map.STKPTR) &0xC0) | (((*pic->P18map.STKPTR) &0x1F) - 1);
       pic->jpc = pic->stack[(*pic->P18map.STKPTR) & 0x1F];
      }
     else
      {
       (*pic->P18map.STKPTR) |= 0x40; //set STKUNF  
       pic->jpc = 0;
      }
     pic->lram = sfr_addr (pic->P18map.STKPTR);
     pic->s2 = 1;
     (*pic->P18map.WREG) = (opc & 0x00FF);
     break;
    case 0x0D00:
     //MULLW    k    	Multiply literal with WREG   1     	0000 1101 kkkk kkkk None
     if (pic->print)printf ("MULLW %#06X\n", opc & 0x00FF);
     temp = (*pic->P18map.WREG)*(opc & 0x00FF);
     (*pic->P18map.PRODH) = (temp & 0xFF00) >> 8;
     (*pic->P18map.PRODL) = temp & 0x00FF;
     pic->lram = sfr_addr (pic->P18map.PRODL);
     break;
    case 0x0E00:
     //MOVLW    k    	Move literal to WREG         1     	0000 1110 kkkk kkkk None
     if (pic->print)printf ("MOVLW %#06X\n", opc & 0x00FF);
     pic->lram = sfr_addr (pic->P18map.WREG);
     (*pic->P18map.WREG) = (opc & 0x00FF);
     break;
    case 0x0F00:
     //ADDLW    k    	Add literal and WREG         1     	0000 1111 kkkk kkkk C, DC, Z, OV, N
     if (pic->print)printf ("ADDLW %#06X\n", opc & 0x00FF);

     if ((0xF0 & ((0x0F & (*pic->P18map.WREG))+(opc & 0x000F))) != 0)
      *status |= 0x02;
     else
      *status &= ~0x02;
     pic->lram = sfr_addr (pic->P18map.WREG);
     temp = (*pic->P18map.WREG)+(opc & 0x00FF);
     ctemp = (unsigned char) (0x00FF & temp);


     if (((*pic->P18map.WREG) & 0x80) != (ctemp & 0x80))
      *status |= 0x08;
     else
      *status &= ~0x08;

     (*pic->P18map.WREG) = ctemp;

     if ((0xFF00 & temp) != 0)
      *status |= 0x01;
     else
      *status &= ~0x01;

     if ((*pic->P18map.WREG) == 0)
      *status |= 0x04;
     else
      *status &= ~0x04;
     if ((*pic->P18map.WREG) & 0x80)
      *status |= 0x10;
     else
      *status &= ~0x10;
     break;
    default:
     printf ("unknown opcode 0x%04X at 0x%06X !\n", opc, pic->pc-2);
     break;
    }
   break;
  case 0x1000:
   switch (opc & 0x0C00)
    {
    case 0x0000:
     //IORWF  f, d, a 	Inclusive OR WREG with f     1          0001 00da ffff ffff Z, N            1, 2
     if (pic->print)printf ("IORWF %#04X,%d,%d\n", opc & 0x00FF, (opc & 0x0200) >> 9, (opc & 0x0100) >> 8);
     fraddr ();
     pic->rram = raddr;
     if (opc & 0x0200)
      {
       pic->ram[raddr] = (*pic->P18map.WREG) | pic->ram[raddr];
       pic->lram = raddr;
       if (pic->ram[raddr] == 0)
        *status |= 0x04;
       else
        *status &= ~0x04;
       if (pic->ram[raddr] & 0x80)
        *status |= 0x10;
       else
        *status &= ~0x10;
      }
     else
      {
       (*pic->P18map.WREG) = (*pic->P18map.WREG) | pic->ram[raddr];
       pic->lram = sfr_addr (pic->P18map.WREG);
       if ((*pic->P18map.WREG) == 0)
        *status |= 0x04;
       else
        *status &= ~0x04;
       if ((*pic->P18map.WREG) & 0x80)
        *status |= 0x10;
       else
        *status &= ~0x10;
      }
     break;
    case 0x0400:
     //ANDWF  f, d, a 	AND WREG with f              1          0001 01da ffff ffff Z, N            1,2
     if (pic->print)printf ("ANDWF %#04X,%d,%d\n", opc & 0x00FF, (opc & 0x0200) >> 9, (opc & 0x0100) >> 8);
     fraddr ();
     pic->rram = raddr;
     if (opc & 0x0200)
      {
       pic->ram[raddr] = (*pic->P18map.WREG) & pic->ram[raddr];
       pic->lram = raddr;
       if (pic->ram[raddr] == 0)
        *status |= 0x04;
       else
        *status &= ~0x04;
       if (pic->ram[raddr] & 0x80)
        *status |= 0x10;
       else
        *status &= ~0x10;
      }
     else
      {
       (*pic->P18map.WREG) = (*pic->P18map.WREG) & pic->ram[raddr];
       pic->lram = sfr_addr (pic->P18map.WREG);
       if ((*pic->P18map.WREG) == 0)
        *status |= 0x04;
       else
        *status &= ~0x04;
       if ((*pic->P18map.WREG) & 0x80)
        *status |= 0x10;
       else
        *status &= ~0x10;
      }
     break;
    case 0x0800:
     //XORWF  f, d, a 	Exclusive OR WREG with f     1          0001 10da ffff ffff Z, N
     if (pic->print)printf ("XORWF %#04X,%d,%d\n", opc & 0x00FF, (opc & 0x0200) >> 9, (opc & 0x0100) >> 8);
     fraddr ();
     pic->rram = raddr;
     if (opc & 0x0200)
      {
       pic->ram[raddr] = (*pic->P18map.WREG) ^ pic->ram[raddr];
       pic->lram = raddr;
       if (pic->ram[raddr] == 0)
        *status |= 0x04;
       else
        *status &= ~0x04;
       if (pic->ram[raddr] & 0x80)
        *status |= 0x10;
       else
        *status &= ~0x10;
      }
     else
      {
       (*pic->P18map.WREG) = (*pic->P18map.WREG) ^ pic->ram[raddr];
       pic->lram = sfr_addr (pic->P18map.WREG);
       if ((*pic->P18map.WREG) == 0)
        *status |= 0x04;
       else
        *status &= ~0x04;
       if ((*pic->P18map.WREG) & 0x80)
        *status |= 0x10;
       else
        *status &= ~0x10;
      }
     break;
    case 0x0C00:
     //COMF   f, d, a 	Complement f                 1          0001 11da ffff ffff Z, N            1, 2
     if (pic->print)printf ("COMF %#06X,%d,%d\n", opc & 0x00FF, (opc & 0x0200) >> 9, (opc & 0x0100) >> 8);
     fraddr ();
     pic->rram = raddr;
     if (opc & 0x0200)
      {
       pic->ram[raddr] = ~pic->ram[raddr];
       pic->lram = raddr;
       if (pic->ram[raddr] == 0)
        *status |= 0x04;
       else
        *status &= ~0x04;
       if (pic->ram[raddr] & 0x80)
        *status |= 0x10;
       else
        *status &= ~0x10;
      }
     else
      {
       (*pic->P18map.WREG) = ~pic->ram[raddr];
       pic->lram = sfr_addr (pic->P18map.WREG);
       if ((*pic->P18map.WREG) == 0)
        *status |= 0x04;
       else
        *status &= ~0x04;
       if ((*pic->P18map.WREG) & 0x80)
        *status |= 0x10;
       else
        *status &= ~0x10;
      }
     break;
    default:
     printf ("unknown opcode 0x%04X at 0x%06X !\n", opc, pic->pc-2);
     break;
    }
   break;
  case 0x2000:
   switch (opc & 0x0C00)
    {
    case 0x0000:
     //ADDWFC f, d, a 	Add WREG and Carry bit to f  1          0010 00da ffff ffff C, DC, Z, OV, N 1, 2
     if (pic->print)printf ("ADDWFC %#06X,%d,%d\n", opc & 0x00FF, (opc & 0x0200) >> 9, (opc & 0x0100) >> 8);
     fraddr ();
     if ((0xF0 & ((0x0F & ((*pic->P18map.WREG) + pic->ram[raddr]))+((*pic->P18map.STATUS)&0x01))) != 0)
      *status |= 0x02; //DC=1
     else
      *status &= ~0x02; //DC=0

     temp = (*pic->P18map.WREG) + pic->ram[raddr]+((*pic->P18map.STATUS)&0x01);

     pic->rram = raddr;

     if ((0xFF00 & temp))
      *status |= 0x01; //C=1
     else
      *status &= ~0x01; //C=0

     ctemp = (unsigned char) (0x00FF & temp);
     if (opc & 0x0200)
      {
       if (((pic->ram[raddr]+(*pic->P18map.WREG)) & 0x80) != (ctemp & 0x80))
        *status |= 0x08; //OV=1
       else
        *status &= ~0x08; //OV=0
       pic->ram[raddr] = ctemp;
       pic->lram = raddr;
       if (pic->ram[raddr] == 0)
        *status |= 0x04; //Z=1
       else
        *status &= ~0x04; //Z=0
       if (pic->ram[raddr] & 0x80)
        *status |= 0x10; //N=1
       else
        *status &= ~0x10; //N=0
      }
     else
      {
       if (((pic->ram[raddr]+(*pic->P18map.WREG)) & 0x80) != (ctemp & 0x80))
        *status |= 0x08;
       else
        *status &= ~0x08;
       (*pic->P18map.WREG) = ctemp;
       pic->lram = sfr_addr (pic->P18map.WREG);
       if ((*pic->P18map.WREG) == 0)
        *status |= 0x04;
       else
        *status &= ~0x04;
       if ((*pic->P18map.WREG) & 0x80)
        *status |= 0x10;
       else
        *status &= ~0x10;
      }
     break;
    case 0x0400:
     //ADDWF  f, d, a 	Add WREG and f               1          0010 01da ffff ffff C, DC, Z, OV, N 1, 2
     if (pic->print)printf ("ADDWF %#06X,%d,%d\n", opc & 0x00FF, (opc & 0x0200) >> 9, (opc & 0x0100) >> 8);
     fraddr ();
     if ((0xF0 & ((0x0F & (*pic->P18map.WREG))+(0x0F & pic->ram[raddr]))) != 0)
      *status |= 0x02;
     else
      *status &= ~0x02;

     temp = (*pic->P18map.WREG) + pic->ram[raddr];

     pic->rram = raddr;

     if ((0xFF00 & temp) != 0)
      *status |= 0x01;
     else
      *status &= ~0x01;

     ctemp = (unsigned char) (0x00FF & temp);

     if (opc & 0x0200)
      {
       if ((pic->ram[raddr] & 0x80) != (ctemp & 0x80))
        *status |= 0x08;
       else
        *status &= ~0x08;
       pic->ram[raddr] = ctemp;
       pic->lram = raddr;
       if (pic->ram[raddr] == 0)
        *status |= 0x04;
       else
        *status &= ~0x04;
       if (pic->ram[raddr] & 0x80)
        *status |= 0x10;
       else
        *status &= ~0x10;
      }
     else
      {
       if (((*pic->P18map.WREG) & 0x80) != (ctemp & 0x80))
        *status |= 0x08;
       else
        *status &= ~0x08;
       (*pic->P18map.WREG) = ctemp;
       pic->lram = sfr_addr (pic->P18map.WREG);
       if ((*pic->P18map.WREG) == 0)
        *status |= 0x04;
       else
        *status &= ~0x04;
       if ((*pic->P18map.WREG) & 0x80)
        *status |= 0x10;
       else
        *status &= ~0x10;
      }
     break;
    case 0x0800:
     //INCF   f, d, a 	Increment f                  1          0010 10da ffff ffff C, DC, Z, OV, N 1, 2, 3, 4
     if (pic->print)printf ("INCF %#06X,%d,%d\n", opc & 0x00FF, (opc & 0x0200) >> 9, (opc & 0x0100) >> 8);
     fraddr ();
     if ((0xF0 & ((0x0F & (pic->ram[raddr])) + 1)) != 0)
      *status |= 0x02;
     else
      *status &= ~0x02;
     pic->rram = raddr;
     temp = pic->ram[raddr] + 1;

     if ((0xFF00 & temp))
      *status |= 0x01;
     else
      *status &= ~0x01;

     ctemp = (unsigned char) (0x00FF & temp);

     if (opc & 0x0200) //dest FILE
      {
       if ((pic->ram[raddr] & 0x80) != (ctemp & 0x80))
        *status |= 0x08;
       else
        *status &= ~0x08;
       pic->lram = raddr;
       pic->ram[raddr] = ctemp;

       if (pic->ram[raddr] == 0)
        *status |= 0x04;
       else
        *status &= ~0x04;
       if (pic->ram[raddr] & 0x80)
        *status |= 0x10;
       else
        *status &= ~0x10;
      }
     else //dest W     
      {
       if (((*pic->P18map.WREG) & 0x80) != (ctemp & 0x80))
        *status |= 0x08;
       else
        *status &= ~0x08;
       pic->lram = sfr_addr (pic->P18map.WREG);
       (*pic->P18map.WREG) = ctemp;
       if ((*pic->P18map.WREG) == 0)
        *status |= 0x04;
       else
        *status &= ~0x04;
       if ((*pic->P18map.WREG) & 0x80)
        *status |= 0x10;
       else
        *status &= ~0x10;
      }
     break;
    case 0x0C00:
     //DECFSZ f, d, a 	Decrement f, Skip if 0       1 (2 or 3) 0010 11da ffff ffff None            1, 2, 3, 4
     if (pic->print)printf ("DECFSZ %#06X,%d,%d\n", opc & 0x00FF, (opc & 0x0200) >> 9, (opc & 0x0100) >> 8);
     fraddr ();
     pic->rram = raddr;
     if (opc & 0x0200)
      {
       pic->ram[raddr]--;
       pic->lram = raddr;
       if (pic->ram[raddr] == 0)
        {
         pic->jpc = pic->pc + 2;
         pic->s2 = 1;
        };
      }
     else
      {
       (*pic->P18map.WREG) = pic->ram[raddr] - 1;
       pic->lram = sfr_addr (pic->P18map.WREG);
       if ((*pic->P18map.WREG) == 0)
        {
         pic->jpc = pic->pc + 2;
         pic->s2 = 1;
        };
      }
     break;
    default:
     printf ("unknown opcode 0x%04X at 0x%06X !\n", opc, pic->pc-2);
     break;
    }
   break;
  case 0x3000:
   switch (opc & 0x0C00)
    {
    case 0x0000:
     //RRCF   f, d, a 	Rotate Right f through Carry 1          0011 00da ffff ffff C, Z, N
     if (pic->print)printf ("RRCF %#06X,%d,%d\n", opc & 0x00FF, (opc & 0x0200) >> 9, (opc & 0x0100) >> 8);
     fraddr ();
     pic->rram = raddr;
     temp = (pic->ram[raddr]);
     if ((*status & 0x01) == 0x01)temp |= 0x0100;
     if ((temp & 0x0001) == 0x01)
      *status |= 0x01;
     else
      *status &= ~0x01;
     temp = temp >> 1;

     if (temp & 0x0080)
      *status |= 0x10;
     else
      *status &= ~0x10;
     if (temp & 0x00FF)
      *status &= ~0x04;
     else
      *status |= 0x04;

     if (opc & 0x0200)
      {
       pic->ram[raddr] = 0x00FF & temp;
       pic->lram = raddr;
      }
     else
      {
       (*pic->P18map.WREG) = 0x00FF & temp;
       pic->lram = sfr_addr (pic->P18map.WREG);
      }
     break;
    case 0x0400:
     //RLCF   f, d, a 	Rotate Left f through Carry  1          0011 01da ffff ffff C, Z, N
     if (pic->print)printf ("RLCF %#06X,%d,%d\n", opc & 0x00FF, (opc & 0x0200) >> 9, (opc & 0x0100) >> 8);
     fraddr ();
     pic->rram = raddr;
     temp = (pic->ram[raddr]) << 1;
     if ((*status & 0x01) == 0x01)temp |= 0x0001;
     if ((temp & 0x0100) == 0x0100)
      *status |= 0x01;
     else
      *status &= ~0x01;
     if (temp & 0x0080)
      *status |= 0x10;
     else
      *status &= ~0x10;
     if (temp & 0x00FF)
      *status &= ~0x04;
     else
      *status |= 0x04;
     if (opc & 0x0200)
      {
       pic->ram[raddr] = 0x00FF & temp;
       pic->lram = raddr;
      }
     else
      {
       (*pic->P18map.WREG) = 0x00FF & temp;
       pic->lram = sfr_addr (pic->P18map.WREG);
      }
     break;
    case 0x0800:
     //SWAPF  f, d, a 	Swap nibbles in f            1          0011 10da ffff ffff None            4
     if (pic->print)printf ("SWAPF %#06X,%d,%d\n", opc & 0x00FF, (opc & 0x0200) >> 9, (opc & 0x0100) >> 8);
     fraddr ();
     pic->rram = raddr;
     if (opc & 0x0200)
      {
       pic->ram[raddr] =
           ((pic->ram[raddr]&0x0F) << 4) |
           ((pic->ram[raddr]&0xF0) >> 4);
       pic->lram = raddr;
      }
     else
      {
       (*pic->P18map.WREG) = ((pic->ram[raddr]&0x0F) << 4) |
           ((pic->ram[raddr]&0xF0) >> 4);
       pic->lram = sfr_addr (pic->P18map.WREG);
      }
     break;
    case 0x0C00:
     //INCFSZ f, d, a 	Increment f, Skip if 0       1 (2 or 3) 0011 11da ffff ffff None            4
     if (pic->print)printf ("INCFSZ %#06X,%d,%d\n", opc & 0x00FF, (opc & 0x0200) >> 9, (opc & 0x0100) >> 8);
     fraddr ();
     pic->rram = raddr;
     if (opc & 0x0200)
      {
       pic->ram[raddr]++;
       pic->lram = raddr;
       if (pic->ram[raddr] == 0)
        {
         pic->jpc = pic->pc + 2;
         pic->s2 = 1;
        };
      }
     else
      {
       (*pic->P18map.WREG) = pic->ram[raddr] + 1;
       pic->lram = sfr_addr (pic->P18map.WREG);
       if ((*pic->P18map.WREG) == 0)
        {
         pic->jpc = pic->pc + 2;
         pic->s2 = 1;
        };
      }
     break;
    default:
     printf ("unknown opcode 0x%04X at 0x%06X !\n", opc, pic->pc-2);
     break;
    }
   break;
  case 0x4000:
   switch (opc & 0x0C00)
    {
    case 0x0000:
     //RRNCF  f, d, a	Rotate Right f (No Carry)    1          0100 00da ffff ffff Z, N
     if (pic->print)printf ("RRNCF %#06X,%d,%d\n", opc & 0x00FF, (opc & 0x0200) >> 9, (opc & 0x0100) >> 8);
     fraddr ();
     pic->rram = raddr;
     temp = (pic->ram[raddr]);
     if ((pic->ram[raddr]&0x01) == 0x01)temp |= 0x0100;

     temp = temp >> 1;

     if (temp & 0x00FF)
      *status &= ~0x04;
     else
      *status |= 0x04;

     if (temp & 0x0080)
      *status |= 0x10;
     else
      *status &= ~0x10;

     if (opc & 0x0200)
      {
       pic->ram[raddr] = 0x00FF & temp;
       pic->lram = raddr;
      }
     else
      {
       (*pic->P18map.WREG) = 0x00FF & temp;
       pic->lram = sfr_addr (pic->P18map.WREG);
      }
     break;
    case 0x0400:
     //RLNCF  f, d, a 	Rotate Left f (No Carry)     1          0100 01da ffff ffff Z, N            1, 2
     if (pic->print)printf ("RLNCF %#06X,%d,%d\n", opc & 0x00FF, (opc & 0x0200) >> 9, (opc & 0x0100) >> 8);
     fraddr ();
     pic->rram = raddr;
     temp = (pic->ram[raddr]) << 1;
     if ((pic->ram[raddr]&0x80) == 0x80)temp |= 0x0001;

     if (temp & 0x00FF)
      *status &= ~0x04;
     else
      *status |= 0x04;
     if (temp & 0x0080)
      *status |= 0x10;
     else
      *status &= ~0x10;

     if (opc & 0x0200)
      {
       pic->ram[raddr] = 0x00FF & temp;
       pic->lram = raddr;
      }
     else
      {
       (*pic->P18map.WREG) = 0x00FF & temp;
       pic->lram = sfr_addr (pic->P18map.WREG);
      }
     break;
    case 0x0800:
     //INFSNZ f, d, a 	Increment f, Skip if Not 0   1 (2 or 3) 0100 10da ffff ffff None            1, 2
     if (pic->print)printf ("INFSNZ %#06X,%d,%d\n", opc & 0x00FF, (opc & 0x0200) >> 9, (opc & 0x0100) >> 8);
     fraddr ();
     pic->rram = raddr;
     if (opc & 0x0200)
      {
       pic->ram[raddr]++;
       pic->lram = raddr;
       if (pic->ram[raddr] != 0)
        {
         pic->jpc = pic->pc + 2;
         pic->s2 = 1;
        };
      }
     else
      {
       (*pic->P18map.WREG) = pic->ram[raddr] + 1;
       if ((*pic->P18map.WREG) != 0)
        {
         pic->jpc = pic->pc + 2;
         pic->s2 = 1;
        };
      }
     break;
    case 0x0C00:
     //DCFSNZ f, d, a 	Decrement f, Skip if Not 0   1 (2 or 3) 0100 11da ffff ffff None            1, 2
     if (pic->print)printf ("DCFSNZ %#06X,%d,%d\n", opc & 0x00FF, (opc & 0x0200) >> 9, (opc & 0x0100) >> 8);
     fraddr ();
     pic->rram = raddr;
     if (opc & 0x0200)
      {
       pic->ram[raddr]--;
       pic->lram = raddr;
       if (pic->ram[raddr] != 0)
        {
         pic->jpc = pic->pc + 2;
         pic->s2 = 1;
        };
      }
     else
      {
       (*pic->P18map.WREG) = pic->ram[raddr] - 1;
       if ((*pic->P18map.WREG) != 0)
        {
         pic->jpc = pic->pc + 2;
         pic->s2 = 1;
        };
      }
     break;
    default:
     printf ("unknown opcode 0x%04X at 0x%06X !\n", opc, pic->pc-2);
     break;
    }
   break;
  case 0x5000:
   switch (opc & 0x0C00)
    {
    case 0x0000:
     //MOVF   f, d, a 	Move f                       1          0101 00da ffff ffff Z, N            1
     if (pic->print)printf ("MOVF %#06X,%d,%d\n", opc & 0x00FF, (opc & 0x0200) >> 9, (opc & 0x0100) >> 8);
     fraddr ();
     if (opc & 0x0200)
      {
       if (pic->ram[raddr] == 0)
        *status |= 0x04;
       else
        *status &= ~0x04;
       if (pic->ram[raddr] & 0x80)
        *status |= 0x10;
       else
        *status &= ~0x10;
       pic->rram = raddr;
       pic->lram = raddr;
      }
     else
      {
       (*pic->P18map.WREG) = pic->ram[raddr];
       if ((*pic->P18map.WREG) == 0)
        *status |= 0x04;
       else
        *status &= ~0x04;
       if ((*pic->P18map.WREG) & 0x80)
        *status |= 0x10;
       else
        *status &= ~0x10;
       pic->rram = raddr;
       pic->lram = sfr_addr (pic->P18map.WREG);
      }
     break;
    case 0x0400:
     //SUBFWB f, d, a 	Subtract f from WREG with b. 1          0101 01da ffff ffff C, DC, Z, OV, N 1, 2
     if (pic->print)printf ("SUBFWB %#06X,%d,%d\n", opc & 0x00FF, (opc & 0x0200) >> 9, (opc & 0x0100) >> 8);
     fraddr ();
     if ((0xF0 & ((0x0F & (~pic->ram[raddr]))+(!((*pic->P18map.STATUS)&0x01)) + 1 + (0x0F & (*pic->P18map.WREG)))) != 0)
      *status |= 0x02;
     else
      *status &= ~0x02;

     temp = (~(pic->ram[raddr]+(!((*pic->P18map.STATUS)&0x01))) + 1)+(*pic->P18map.WREG);

     if ((0xFF00 & temp) != 0)
      *status &= ~0x01;
     else
      *status |= 0x01;

     pic->rram = raddr;

     ctemp = (unsigned char) (0x00FF & temp);

     if (opc & 0x0200)
      {
       *status &= ~0x08;
       /* incompleto
       if ((pic->ram[raddr] & 0x80)!=(ctemp&0x80))  
        *status|=0x08;
       else   
        *status&=~0x08;
        */
       pic->ram[raddr] = ctemp;
       pic->lram = raddr;
       if (pic->ram[raddr ] == 0)
        *status |= 0x04;
       else
        *status &= ~0x04;
       if (pic->ram[raddr] & 0x80)
        *status |= 0x10;
       else
        *status &= ~0x10;
      }
     else
      {
       *status &= ~0x08;
       /* incompleto
       if (((*pic->P18map.WREG) & 0x80)!=(ctemp&0x80))  
        *status|=0x08;
       else   
        *status&=~0x08;
        */
       (*pic->P18map.WREG) = ctemp;
       pic->lram = sfr_addr (pic->P18map.WREG);
       if ((*pic->P18map.WREG) == 0)
        *status |= 0x04;
       else
        *status &= ~0x04;
       if ((*pic->P18map.WREG) & 0x80)
        *status |= 0x10;
       else
        *status &= ~0x10;
      }
     break;
    case 0x0800:
     //SUBWFB f, d, a 	Subtract WREG from f with b. 1          0101 10da ffff ffff C, DC, Z, OV, N 1, 2
     if (pic->print)printf ("SUBWFB %#06X,%d,%d\n", opc & 0x00FF, (opc & 0x0200) >> 9, (opc & 0x0100) >> 8);
     fraddr ();
     if ((0xF0 & ((0x0F & (~(*pic->P18map.WREG)))+(!((*pic->P18map.STATUS)&0x01)) + 1 + (0x0F & pic->ram[raddr]))) != 0)
      *status |= 0x02;
     else
      *status &= ~0x02;

     temp = (~((*pic->P18map.WREG)+(!((*pic->P18map.STATUS)&0x01))) + 1) + pic->ram[raddr];

     if ((0xFF00 & temp) != 0)
      *status &= ~0x01;
     else
      *status |= 0x01;

     pic->rram = raddr;

     ctemp = (unsigned char) (0x00FF & temp);

     if (opc & 0x0200)
      {
       *status &= ~0x08;
       //TODO P18 incomplet SUBWFB flags
       /*
       if ((pic->ram[raddr] & 0x80)!=(ctemp&0x80))  
        *status|=0x08;
       else   
        *status&=~0x08;
        */
       pic->ram[raddr] = ctemp;
       pic->lram = raddr;
       if (pic->ram[raddr ] == 0)
        *status |= 0x04;
       else
        *status &= ~0x04;
       if (pic->ram[raddr] & 0x80)
        *status |= 0x10;
       else
        *status &= ~0x10;
      }
     else
      {
       *status &= ~0x08;
       //TODO P18  incomplet  SUBWFB flags
       /* 
       if (((*pic->P18map.WREG) & 0x80)!=(ctemp&0x80))  
        *status|=0x08;
       else   
        *status&=~0x08;
        */
       (*pic->P18map.WREG) = ctemp;
       pic->lram = sfr_addr (pic->P18map.WREG);
       if ((*pic->P18map.WREG) == 0)
        *status |= 0x04;
       else
        *status &= ~0x04;
       if ((*pic->P18map.WREG) & 0x80)
        *status |= 0x10;
       else
        *status &= ~0x10;
      }
     break;
    case 0x0C00:
     //SUBWF  f, d, a 	Subtract WREG from f         1          0101 11da ffff ffff C, DC, Z, OV, N
     if (pic->print)printf ("SUBWF %#06X,%d,%d\n", opc & 0x00FF, (opc & 0x0200) >> 9, (opc & 0x0100) >> 8);
     fraddr ();
     if ((0xF0 & ((0x0F & (~(*pic->P18map.WREG))) + 1 + (0x0F & pic->ram[raddr]))) != 0)
      *status |= 0x02;
     else
      *status &= ~0x02;

     temp = (~(*pic->P18map.WREG) + 1) + pic->ram[raddr];

     if ((0xFF00 & temp) != 0)
      *status &= ~0x01;
     else
      *status |= 0x01;

     pic->rram = raddr;

     ctemp = (unsigned char) (0x00FF & temp);
     if (opc & 0x0200)
      {
       *status &= ~0x08;
       //TODO P18  incomplet  SUBWF flags
       /* 
       if ((pic->ram[raddr] & 0x80)!=(ctemp&0x80))  
        *status|=0x08;
       else   
        *status&=~0x08;
        */
       pic->ram[raddr] = ctemp;
       pic->lram = raddr;
       if (pic->ram[raddr ] == 0)
        *status |= 0x04;
       else
        *status &= ~0x04;
       if (pic->ram[raddr] & 0x80)
        *status |= 0x10;
       else
        *status &= ~0x10;
      }
     else
      {
       *status &= ~0x08;
       //TODO  P18 incomplet SUBWF flags
       /*
      if (((*pic->P18map.WREG) & 0x80)!=(ctemp&0x80))  
        *status|=0x08;
      else   
        *status&=~0x08;
        */
       (*pic->P18map.WREG) = ctemp;
       pic->lram = sfr_addr (pic->P18map.WREG);
       if ((*pic->P18map.WREG) == 0)
        *status |= 0x04;
       else
        *status &= ~0x04;
       if ((*pic->P18map.WREG) & 0x80)
        *status |= 0x10;
       else
        *status &= ~0x10;
      }
     break;
    default:
     printf ("unknown opcode 0x%04X at 0x%06X !\n", opc, pic->pc-2);
     break;
    }
   break;
  case 0x6000:
   switch (opc & 0x0E00)
    {
    case 0x0000:
     //CPFSLT f, a    	Compare f with WREG, skip <  1 (2 or 3) 0110 000a ffff ffff None            1, 2
     if (pic->print)printf ("CPFSLT %#06X,%d \n", opc & 0x00FF, (opc & 0x0100) >> 8);
     fraddr ();
     pic->rram = raddr;
     if (pic->ram[raddr] < (*pic->P18map.WREG))
      {
       pic->jpc = pic->pc + 2;
       pic->s2 = 1;
      }
     break;
    case 0x0200:
     //CPFSEQ f, a    	Compare f with WREG, skip =  1 (2 or 3) 0110 001a ffff ffff None            4
     if (pic->print)printf ("CPFSEQ  %#06X,%d \n", opc & 0x00FF, (opc & 0x0100) >> 8);
     fraddr ();
     pic->rram = raddr;
     if (pic->ram[raddr] == (*pic->P18map.WREG))
      {
       pic->jpc = pic->pc + 2;
       pic->s2 = 1;
      }
     break;
    case 0x0400:
     //CPFSGT f, a    	Compare f with WREG, skip >  1 (2 or 3) 0110 010a ffff ffff None            4
     if (pic->print)printf ("CPFSGT %#06X,%d \n", opc & 0x00FF, (opc & 0x0100) >> 8);
     fraddr ();
     pic->rram = raddr;
     if (pic->ram[raddr] > (*pic->P18map.WREG))
      {
       pic->jpc = pic->pc + 2;
       pic->s2 = 1;
      }
     break;
    case 0x0600:
     //TSTFSZ f, a    	Test f, skip if 0            1 (2 or 3) 0110 011a ffff ffff None            1, 2
     if (pic->print)printf ("TSTFSZ %#06X,%d \n", opc & 0x00FF, (opc & 0x0100) >> 8);
     fraddr ();
     pic->rram = raddr;
     if (!pic->ram[raddr])
      {
       pic->jpc = pic->pc + 2;
       pic->s2 = 1;
      }
     break;
    case 0x0800:
     //SETF   f, a    	Set f                        1          0110 100a ffff ffff None
     if (pic->print)printf ("SETF %#06X,%d \n", opc & 0x00FF, (opc & 0x0100) >> 8);
     fraddr ();
     pic->rram = raddr;
     pic->lram = raddr;
     pic->ram[raddr] = 0xFF;
     break;
    case 0x0A00:
     //CLRF   f, a    	Clear f                      1          0110 101a ffff ffff Z               2
     if (pic->print)printf ("CLRF %#06X,%d \n", opc & 0x00FF, (opc & 0x0100) >> 8);
     fraddr ();
     pic->rram = raddr;
     pic->lram = raddr;
     pic->ram[raddr] = 0;
     *status |= 0x04;
     break;
    case 0x0C00:
     //NEGF   f, a    	Negate f                     1          0110 110a ffff ffff C, DC, Z, OV, N 1, 2
     if (pic->print)printf ("NEGF %#06X,%d\n", opc & 0x00FF, (opc & 0x0100) >> 8);
     fraddr ();
     pic->rram = raddr;
     if ((0xF0 & ((0x0F & (~pic->ram[raddr])) + 1)) != 0)
      *status |= 0x02;
     else
      *status &= ~0x02;

     temp = ~pic->ram[raddr] + 1;

     if ((0xFF00 & temp))
      *status &= ~0x01;
     else
      *status |= 0x01;

     ctemp = (unsigned char) (0x00FF & temp);

     if ((pic->ram[raddr] & 0x80) != (ctemp & 0x80))
      *status &= ~0x08;
     else
      *status |= 0x08;
     pic->ram[raddr] = ctemp;
     pic->lram = raddr;
     if (pic->ram[raddr] == 0)
      *status |= 0x04;
     else
      *status &= ~0x04;
     if (pic->ram[raddr] & 0x80)
      *status |= 0x10;
     else
      *status &= ~0x10;
     break;
    case 0x0E00:
     //MOVWF  f, a    	Move WREG to f               1          0110 111a ffff ffff None
     if (pic->print)printf ("MOVWF %#06X,%d\n", opc & 0x00FF, (opc & 0x0100) >> 8);
     fraddr ();
     pic->ram[raddr] = (*pic->P18map.WREG);
     pic->lram = raddr;
     pic->rram = sfr_addr (pic->P18map.WREG);
     break;
    default:
     printf ("unknown opcode 0x%04X at 0x%06X !\n", opc, pic->pc-2);
     break;
    }
   break;
  case 0x7000:
   //BTG    f, b, a 	Bit Toggle f                 1          0111 bbba ffff ffff None 1, 2
   if (pic->print)printf ("BTG %#06X,%d,%d\n", opc & 0x00FF, (opc & 0x0E00) >> 9, (opc & 0x0100) >> 8);
   fraddr ();
   pic->rram = raddr;
   pic->ram[raddr] ^= (0x01 << ((opc & 0x0E00) >> 9));
   pic->lram = raddr;
   break;
  case 0x8000:
   //BSF    f, b, a 	Bit Set f                    1          1000 bbba ffff ffff None 1, 2
   if (pic->print)printf ("BSF %#06X,%d,%d\n", opc & 0x00FF, (opc & 0x0E00) >> 9, (opc & 0x0100) >> 8);
   fraddr ();
   pic->rram = raddr;
   pic->ram[raddr] |= (0x01 << ((opc & 0x0E00) >> 9));
   pic->lram = raddr;
   break;
  case 0x9000:
   //BCF    f, b, a 	Bit Clear f                  1          1001 bbba ffff ffff None 1, 2
   if (pic->print)printf ("BCF %#06X,%d,%d\n", opc & 0x00FF, (opc & 0x0E00) >> 9, (opc & 0x0100) >> 8);
   fraddr ();
   pic->rram = raddr;
   pic->ram[raddr] &= ~(0x01 << ((opc & 0x0E00) >> 9));
   pic->lram = raddr;
   break;
  case 0xA000:
   //BTFSS  f, b, a 	Bit Test f, Skip if Set      1 (2 or 3) 1010 bbba ffff ffff None 3, 4
   if (pic->print)printf ("BTFSS %#06X,%d,%d\n", opc & 0x00FF, (opc & 0x0E00) >> 9, (opc & 0x0100) >> 8);
   fraddr ();
   pic->rram = raddr;
   if ((pic->ram[raddr] & (0x01 << ((opc & 0x0E00) >> 9))) != 0)
    {
     pic->jpc = pic->pc + 2;
     pic->s2 = 1;
    }
   break;
  case 0xB000:
   //BTFSC  f, b, a 	Bit Test f, Skip if Clear    1 (2 or 3) 1011 bbba ffff ffff None 3, 4
   if (pic->print)printf ("BTFSC %#06X,%d,%d\n", opc & 0x00FF, (opc & 0x0E00) >> 9, (opc & 0x0100) >> 8);
   fraddr ();
   pic->rram = raddr;
   if ((pic->ram[raddr] & (0x01 << ((opc & 0x0E00) >> 9))) == 0)
    {
     pic->jpc = pic->pc + 2;
     pic->s2 = 1;
    }
   break;
  case 0xC000:
   //MOVFF  fs, fd  	Move fs (source) to 1st word 2          1100 ffff  ffff ffff None
   //                   	fd (destination) 2nd word               1111 ffff  ffff ffff
   if (pic->print)printf ("MOVFF %#06X,%#06X\n", opc & 0x0FFF, pic->prog[pic->pc >> 1] & 0x0FFF);
   pic->ram[pic->prog[pic->pc >> 1] & 0x0FFF] = pic->ram[opc & 0x0FFF];
   pic->rram = opc & 0x0FFF;
   pic->lram = pic->prog[pic->pc >> 1] & 0x0FFF;
   break;
  case 0xD000:
   switch (opc & 0x0800)
    {
    case 0x0000:
     //BRA    n    		Branch Unconditionally       1 (2) 	1101 0nnn nnnn nnnn None
     jrange = (((short) ((opc & 0x07FF) << 5)) / 16);
     if (pic->print)printf ("BRA %#06X\n", (pic->pc + jrange)&((pic->ROMSIZE << 1) - 1));
     pic->jpc = (pic->pc + jrange)&((pic->ROMSIZE << 1) - 1);
     pic->s2 = 1;
     break;
    case 0x0800:
     //RCALL  n    		Relative Call                2     	1101 1nnn nnnn nnnn None
     jrange = (((short) ((opc & 0x07FF) << 5)) / 16);
     if (pic->print)printf ("RCALL %#06X\n", (pic->pc + jrange)&((pic->ROMSIZE << 1) - 1));
     if (((*pic->P18map.STKPTR) & 0x1F) < 31)
      {
       pic->stack[(*pic->P18map.STKPTR)& 0x1F] = pic->pc;
       (*pic->P18map.STKPTR) = ((*pic->P18map.STKPTR) &0xC0) | (((*pic->P18map.STKPTR) &0x1F) + 1);
       if (((*pic->P18map.STKPTR) & 0x1F) == 31)(*pic->P18map.STKPTR) |= 0x80; //set STKFUL
      }
     pic->jpc = (pic->pc + jrange)&((pic->ROMSIZE << 1) - 1);
     pic->lram = sfr_addr (pic->P18map.STKPTR);
     pic->s2 = 1;
     break;
     break;
    default:
     printf ("unknown opcode 0x%04X at 0x%06X !\n", opc, pic->pc-2);
     break;
    }
   break;
  case 0xE000:
   switch (opc & 0x0F00)
    {
    case 0x0000:
     //BZ     n    		Branch if Zero               1 (2) 	1110 0000 nnnn nnnn None
     jrange = (((char) (opc & 0x00FF))*2);
     if (pic->print)printf ("BZ  %#06X\n", (pic->pc + jrange)&((pic->ROMSIZE << 1) - 1));
     if ((*pic->P18map.STATUS) & 0x04)
      {
       pic->jpc = (pic->pc + jrange)&((pic->ROMSIZE << 1) - 1);
       pic->s2 = 1;
      }
     break;
    case 0x0100:
     //BNZ    n    		Branch if Not Zero           2     	1110 0001 nnnn nnnn None
     jrange = (((char) (opc & 0x00FF))*2);
     if (pic->print)printf ("BNZ %#06X\n", (pic->pc + jrange)&((pic->ROMSIZE << 1) - 1));
     if (!((*pic->P18map.STATUS) & 0x04))
      {
       pic->jpc = (pic->pc + jrange)&((pic->ROMSIZE << 1) - 1);
       pic->s2 = 1;
      }
     break;
    case 0x0200:
     //BC     n    		Branch if Carry              1 (2)      1110 0010 nnnn nnnn None
     jrange = (((char) (opc & 0x00FF))*2);
     if (pic->print)printf ("BC  %#06X\n", (pic->pc + jrange)&((pic->ROMSIZE << 1) - 1));
     if ((*pic->P18map.STATUS) & 0x01)
      {
       pic->jpc = (pic->pc + jrange)&((pic->ROMSIZE << 1) - 1);
       pic->s2 = 1;
      }
     break;
    case 0x0300:
     //BNC    n    		Branch if Not Carry          1 (2) 	1110 0011 nnnn nnnn None
     jrange = (((char) (opc & 0x00FF))*2);
     if (pic->print)printf ("BNC %#06X\n", (pic->pc + jrange)&((pic->ROMSIZE << 1) - 1));
     if (!((*pic->P18map.STATUS) & 0x01))
      {
       pic->jpc = (pic->pc + jrange)&((pic->ROMSIZE << 1) - 1);
       pic->s2 = 1;
      }
     break;
    case 0x0400:
     //BOV    n    		Branch if Overflow           1 (2) 	1110 0100 nnnn nnnn None
     jrange = (((char) (opc & 0x00FF))*2);
     if (pic->print)printf ("BOV  %#06X\n", (pic->pc + jrange)&((pic->ROMSIZE << 1) - 1));
     if ((*pic->P18map.STATUS) & 0x08)
      {
       pic->jpc = (pic->pc + jrange)&((pic->ROMSIZE << 1) - 1);
       pic->s2 = 1;
      }
     break;
    case 0x0500:
     //BNOV   n    		Branch if Not Overflow       1 (2) 	1110 0101 nnnn nnnn None
     jrange = (((char) (opc & 0x00FF))*2);
     if (pic->print)printf ("BNOV %#06X\n", (pic->pc + jrange)&((pic->ROMSIZE << 1) - 1));
     if (!((*pic->P18map.STATUS) & 0x08))
      {
       pic->jpc = (pic->pc + jrange)&((pic->ROMSIZE << 1) - 1);
       pic->s2 = 1;
      }
     break;
    case 0x0600:
     //BN     n    		Branch if Negative           1 (2)      1110 0110 nnnn nnnn None
     jrange = (((char) (opc & 0x00FF))*2);
     if (pic->print)printf ("BN  %#06X\n", (pic->pc + jrange)&((pic->ROMSIZE << 1) - 1));
     if ((*pic->P18map.STATUS) & 0x10)
      {
       pic->jpc = (pic->pc + jrange)&((pic->ROMSIZE << 1) - 1);
       pic->s2 = 1;
      }
     break;
    case 0x0700:
     //BNN    n    		Branch if Not Negative       1 (2) 	1110 0111 nnnn nnnn None
     jrange = (((char) (opc & 0x00FF))*2);
     if (pic->print)printf ("BNN %#06X\n", (pic->pc + jrange)&((pic->ROMSIZE << 1) - 1));
     if (!((*pic->P18map.STATUS) & 0x10))
      {
       pic->jpc = (pic->pc + jrange)&((pic->ROMSIZE << 1) - 1);
       pic->s2 = 1;
      }
     break;
    case 0x0C00:
    case 0x0D00:
     //CALL   n, s 		Call subroutine1st word      2     	1110 110s kkkk kkkk None
     //            		2nd word                             	1111 kkkk kkkk kkkk
     if (pic->print)printf ("CALL %#012X,%d\n", (((pic->prog[pic->pc >> 1] & 0x0FFF) << 8) | (opc & 0x00FF)) << 1, (opc & 0x0100) >> 8);

     if (opc & 0x0100)
      {
       pic->P18map.WS = (*pic->P18map.WREG);
       pic->P18map.STATUSS = (*pic->P18map.STATUS);
       pic->P18map.BSRS = (*pic->P18map.BSR);
      }
     if (((*pic->P18map.STKPTR) & 0x1F) < 31)
      {
       pic->stack[(*pic->P18map.STKPTR)& 0x1F] = pic->pc + 2;
       (*pic->P18map.STKPTR) = ((*pic->P18map.STKPTR) &0xC0) | (((*pic->P18map.STKPTR) &0x1F) + 1);
       if (((*pic->P18map.STKPTR)& 0x1F) == 31)(*pic->P18map.STKPTR) |= 0x80; //set STKFUL
      }
     pic->jpc = (((pic->prog[pic->pc >> 1] & 0x0FFF) << 8) | (opc & 0x00FF)) << 1;
     pic->lram = sfr_addr (pic->P18map.STKPTR);
     pic->s2 = 1;
     break;
    case 0x0E00:
     //LFSR     f, k 	Move literal (12-bit) 2nd w  2  	1110 1110 00ff kkkk None
     //                   	to FSRx 1st word                   	1111 0000 kkkk kkkk
     if (pic->print)printf ("LFSR %d,%#08X\n", (opc & 0x0030) >> 4, ((opc & 0x000F) << 8) | (pic->prog[pic->pc >> 1] & 0x00FF));

     switch ((opc & 0x0030) >> 4)
      {
      case 0:
       (*pic->P18map.FSR0H) = ((opc & 0x000F));
       (*pic->P18map.FSR0L) = (pic->prog[pic->pc >> 1] & 0x00FF);
       pic->lram = sfr_addr (pic->P18map.FSR0L);
       break;
      case 1:
       (*pic->P18map.FSR1H) = ((opc & 0x000F));
       (*pic->P18map.FSR1L) = (pic->prog[pic->pc >> 1] & 0x00FF);
       pic->lram = sfr_addr (pic->P18map.FSR1L);
       break;
      case 2:
       (*pic->P18map.FSR2H) = ((opc & 0x000F));
       (*pic->P18map.FSR2L) = (pic->prog[pic->pc >> 1] & 0x00FF);
       pic->lram = sfr_addr (pic->P18map.FSR2L);
       break;
      default:
       printf ("LFSR Error!\n");
       break;
      }
     break;
    case 0x0F00:
     //GOTO   n    		Go to address1st word        2     	1110 1111 kkkk kkkk None
     //            		2nd word                             	1111 kkkk kkkk kkkk
     if ((pic->pc >= 0x200028)&&(pic->pc < 0x200037))//DEBUG
      {
       if (pic->print)printf ("GOTO %#012X\n", (((pic->debugv[pic->pc - 0x200027] & 0x0FFF) << 8) | (opc & 0x00FF)) << 1);
       pic->jpc = (((pic->debugv[pic->pc - 0x200029] & 0x0FFF) << 8) | (opc & 0x00FF)) << 1;

       //printf("debugv %i\n",pic->pc-0x200029); 
      }
     else
      {
       if (pic->print)printf ("GOTO %#012X\n", (((pic->prog[pic->pc >> 1] & 0x0FFF) << 8) | (opc & 0x00FF)) << 1);
       pic->jpc = (((pic->prog[pic->pc >> 1] & 0x0FFF) << 8) | (opc & 0x00FF)) << 1;
      }
     pic->s2 = 1;
     break;
    default:
     printf ("unknown opcode 0x%04X at 0x%06X !\n", opc, pic->pc-2);     
     break;
    }
   break;
  case 0xF000:
   //NOP    --   		No Operation                 1     	1111 xxxx xxxx xxxx None      4
   if (pic->print)printf ("NOP\n");
   break;
  default:
   printf ("unknown opcode 0x%04X at 0x%06X !\n", opc, pic->pc-2);
   break;
  }



 if (pic->lram != 0x8000)
  {
   unsigned char * plram = &pic->ram[pic->lram];

   if (plram == pic->P18map.INDF0)
    {
     pic->ram[afsr0] = (*pic->P18map.INDF0);
     pic->lram = afsr0;
    }
   if (plram == pic->P18map.POSTINC0)
    {
     pic->ram[afsr0] = (*pic->P18map.POSTINC0);
     pic->lram = afsr0;
     (*pic->P18map.FSR0H) = ((afsr0 + 1)&0xFF00) >> 8;
     (*pic->P18map.FSR0L) = (afsr0 + 1)&0x00FF;
    }
   if (plram == pic->P18map.POSTDEC0)
    {
     pic->ram[afsr0] = (*pic->P18map.POSTDEC0);
     if (pic->lram == pic->rram)pic->rram = 0x8000;
     pic->lram = afsr0;
     (*pic->P18map.FSR0H) = ((afsr0 - 1)&0xFF00) >> 8;
     (*pic->P18map.FSR0L) = (afsr0 - 1)&0x00FF;
    }
   if (plram == pic->P18map.PREINC0)
    {
     pic->ram[afsr0 + 1] = (*pic->P18map.PREINC0);
     if (pic->lram == pic->rram)pic->rram = 0x8000;
     pic->lram = afsr0 + 1;
     (*pic->P18map.FSR0H) = ((afsr0 + 1)&0xFF00) >> 8;
     (*pic->P18map.FSR0L) = (afsr0 + 1)&0x00FF;
    }
   if (plram == pic->P18map.PLUSW0)
    {
     pic->ram[afsr0 + ((char) (*pic->P18map.WREG))] = (*pic->P18map.PLUSW0);
     pic->lram = afsr0 + ((char) (*pic->P18map.WREG));
    }

   if (plram == pic->P18map.INDF1)
    {
     pic->ram[afsr1] = (*pic->P18map.INDF1);
     pic->lram = afsr1;
    }
   if (plram == pic->P18map.POSTINC1)
    {
     pic->ram[afsr1] = (*pic->P18map.POSTINC1);
     pic->lram = afsr1;
     (*pic->P18map.FSR1H) = ((afsr1 + 1)&0xFF00) >> 8;
     (*pic->P18map.FSR1L) = (afsr1 + 1)&0x00FF;
    }
   if (plram == pic->P18map.POSTDEC1)
    {
     pic->ram[afsr1] = (*pic->P18map.POSTDEC1);
     pic->lram = afsr1;
     (*pic->P18map.FSR1H) = ((afsr1 - 1)&0xFF00) >> 8;
     (*pic->P18map.FSR1L) = (afsr1 - 1)&0x00FF;
    }
   if (plram == pic->P18map.PREINC1)
    {
     pic->ram[afsr1 + 1] = (*pic->P18map.PREINC1);
     pic->lram = afsr1 + 1;
     (*pic->P18map.FSR1H) = ((afsr1 + 1)&0xFF00) >> 8;
     (*pic->P18map.FSR1L) = (afsr1 + 1)&0x00FF;
    }
   if (plram == pic->P18map.PLUSW1)
    {
     pic->ram[afsr1 + ((char) (*pic->P18map.WREG))] = (*pic->P18map.PLUSW1);
     pic->lram = afsr1 + ((char) (*pic->P18map.WREG));
    }

   if (plram == pic->P18map.INDF2)
    {
     pic->ram[afsr2] = (*pic->P18map.INDF2);
     pic->lram = afsr2;
    }
   if (plram == pic->P18map.POSTINC2)
    {
     pic->ram[afsr2] = (*pic->P18map.POSTINC2);
     pic->lram = afsr2;
     (*pic->P18map.FSR2H) = ((afsr2 + 1)&0xFF00) >> 8;
     (*pic->P18map.FSR2L) = (afsr2 + 1)&0x00FF;
    }
   if (plram == pic->P18map.POSTDEC2)
    {
     pic->ram[afsr2] = (*pic->P18map.POSTDEC2);
     pic->lram = afsr2;
     (*pic->P18map.FSR2H) = ((afsr2 - 1)&0xFF00) >> 8;
     (*pic->P18map.FSR2L) = (afsr2 - 1)&0x00FF;
    }
   if (plram == pic->P18map.PREINC2)
    {
     pic->ram[afsr2 + 1] = (*pic->P18map.PREINC2);
     pic->lram = afsr2 + 1;
     (*pic->P18map.FSR2H) = ((afsr2 + 1)&0xFF00) >> 8;
     (*pic->P18map.FSR2L) = (afsr2 + 1)&0x00FF;
    }
   if (plram == pic->P18map.PLUSW2)
    {
     pic->ram[afsr2 + ((char) (*pic->P18map.WREG))] = (*pic->P18map.PLUSW2);
     pic->lram = afsr2 + ((char) (*pic->P18map.WREG));
    }



   //second pass with new lram    
   plram = &pic->ram[pic->lram];

   if (plram == pic->P18map.STKPTR)
    {
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
   if (plram == pic->P18map.TOSL)
    {
     if (((*pic->P18map.STKPTR) & 0x1F) > 0)
      pic->stack[((*pic->P18map.STKPTR) & 0x1F) - 1] = (pic->stack[((*pic->P18map.STKPTR) & 0x1F) - 1] & 0x1FFF00) | (*pic->P18map.TOSL);
    }
   if (plram == pic->P18map.TOSH)
    {
     if (((*pic->P18map.STKPTR) & 0x1F) > 0)
      pic->stack[((*pic->P18map.STKPTR) & 0x1F) - 1] = (pic->stack[((*pic->P18map.STKPTR) & 0x1F) - 1] & 0x1F00FF) | ((*pic->P18map.TOSH) << 8);
    }
   if (plram == pic->P18map.TOSU)
    {
     if (((*pic->P18map.STKPTR) & 0x1F) > 0)
      pic->stack[((*pic->P18map.STKPTR) & 0x1F) - 1] = (pic->stack[((*pic->P18map.STKPTR) & 0x1F) - 1] & 0x00FFFF) | (((*pic->P18map.TOSU)&0x1F) << 16);
    }

   if (plram == pic->P18map.LATA)
    {
     (*pic->P18map.PORTA) = ((*pic->P18map.PORTA)&(*pic->P18map.TRISA))|((*pic->P18map.LATA)&(~(*pic->P18map.TRISA)));
    }
   if (plram == pic->P18map.LATB)
    {
     (*pic->P18map.PORTB) = ((*pic->P18map.PORTB)&(*pic->P18map.TRISB))|((*pic->P18map.LATB)&(~(*pic->P18map.TRISB)));
    }
   if (plram == pic->P18map.LATC)
    {
     (*pic->P18map.PORTC) = ((*pic->P18map.PORTC)&(*pic->P18map.TRISC))|((*pic->P18map.LATC)&(~(*pic->P18map.TRISC)));
    }
   if (plram == pic->P18map.LATD)
    {
     (*pic->P18map.PORTD) = ((*pic->P18map.PORTD)&(*pic->P18map.TRISD))|((*pic->P18map.LATD)&(~(*pic->P18map.TRISD)));
    }
   if (plram == pic->P18map.LATE)
    {
     (*pic->P18map.PORTE) = ((*pic->P18map.PORTE)&(*pic->P18map.TRISE))|((*pic->P18map.LATE)&(~(*pic->P18map.TRISE)));
    }

   if (plram == pic->P18map.PORTA)
    {
     (*pic->P18map.LATA) = (*pic->P18map.PORTA);
    }
   if (plram == pic->P18map.PORTB)
    {
     (*pic->P18map.LATB) = (*pic->P18map.PORTB);
    }
   if (plram == pic->P18map.PORTC)
    {
     (*pic->P18map.LATC) = (*pic->P18map.PORTC);
    }
   if (plram == pic->P18map.PORTD)
    {
     (*pic->P18map.LATD) = (*pic->P18map.PORTD);
    }
   if (plram == pic->P18map.PORTE)
    {
     (*pic->P18map.LATE) = (*pic->P18map.PORTE);
    }

   if (plram == pic->P18map.PCL)
    {
     pic->pc = (((*pic->P18map.PCLATU)&0x1F) << 16) | (((*pic->P18map.PCLATH)) << 8) | (*pic->P18map.PCL);
     //	      printf("###############PCL write  (%#04X %#04X %#04X) %#08X\n",((*pic->P18map.PCLATU)&0x1F)<<16,((*pic->P18map.PCLATH))<<8,(*pic->P18map.PCL),pic->pc);
    }

  }

 if (pic->rram != 0x8000)
  {
   unsigned char * prram = &pic->ram[pic->rram];

   if (prram == pic->P18map.INDF0)
    {
     pic->rram = afsr0;
    }
   if (prram == pic->P18map.POSTINC0)
    {
     (*pic->P18map.FSR0H) = ((afsr0 + 1)&0xFF00) >> 8;
     (*pic->P18map.FSR0L) = (afsr0 + 1)&0x00FF;
     pic->rram = afsr0;
    }
   if (prram == pic->P18map.POSTDEC0)
    {
     (*pic->P18map.FSR0H) = ((afsr0 - 1)&0xFF00) >> 8;
     (*pic->P18map.FSR0L) = (afsr0 - 1)&0x00FF;
     pic->rram = afsr0;
    }
   if (prram == pic->P18map.PREINC0)
    {
     (*pic->P18map.FSR0H) = ((afsr0 + 1)&0xFF00) >> 8;
     (*pic->P18map.FSR0L) = (afsr0 + 1)&0x00FF;
     pic->rram = afsr0 + 1;
    }
   if (prram == pic->P18map.PLUSW0)
    {
     pic->rram = afsr0 + ((char) (*pic->P18map.WREG));
    }

   if (prram == pic->P18map.INDF1)
    {
     pic->rram = afsr1;
    }
   if (prram == pic->P18map.POSTINC1)
    {
     (*pic->P18map.FSR1H) = ((afsr1 + 1)&0xFF00) >> 8;
     (*pic->P18map.FSR1L) = (afsr1 + 1)&0x00FF;
     pic->rram = afsr1;
    }
   if (prram == pic->P18map.POSTDEC1)
    {
     (*pic->P18map.FSR1H) = ((afsr1 - 1)&0xFF00) >> 8;
     (*pic->P18map.FSR1L) = (afsr1 - 1)&0x00FF;
     pic->rram = afsr1;
    }
   if (prram == pic->P18map.PREINC1)
    {
     (*pic->P18map.FSR1H) = ((afsr1 + 1)&0xFF00) >> 8;
     (*pic->P18map.FSR1L) = (afsr1 + 1)&0x00FF;
     pic->rram = afsr1 + 1;
    }
   if (prram == pic->P18map.PLUSW1)
    {
     pic->rram = afsr1 + ((char) (*pic->P18map.WREG));
    }

   if (prram == pic->P18map.INDF2)
    {
     pic->rram = afsr2;
    }
   if (prram == pic->P18map.POSTINC2)
    {
     (*pic->P18map.FSR2H) = ((afsr2 + 1)&0xFF00) >> 8;
     (*pic->P18map.FSR2L) = (afsr2 + 1)&0x00FF;
     pic->rram = afsr2;
    }
   if (prram == pic->P18map.POSTDEC2)
    {
     (*pic->P18map.FSR2H) = ((afsr2 - 1)&0xFF00) >> 8;
     (*pic->P18map.FSR2L) = (afsr2 - 1)&0x00FF;
     pic->rram = afsr2;
    }
   if (prram == pic->P18map.PREINC2)
    {
     (*pic->P18map.FSR2H) = ((afsr2 + 1)&0xFF00) >> 8;
     (*pic->P18map.FSR2L) = (afsr2 + 1)&0x00FF;
     pic->rram = afsr2 + 1;
    }
   if (prram == pic->P18map.PLUSW2)
    {
     pic->rram = afsr2 + ((char) (*pic->P18map.WREG));
    }


   //second pass with new rram
   prram = &pic->ram[pic->rram];

   if (prram == pic->P18map.PCL)
    {
     //    printf("###############PCL read\n");
     (*pic->P18map.PCLATU) = (pic->pc & 0x1F0000) >> 16;
     (*pic->P18map.PCLATH) = (pic->pc & 0x00FF00) >> 8;
    }

  }

 pic->w = (*pic->P18map.WREG);

 if ((pic->print)&&(pic->rram != 0x8000))printf ("mem read  %#06X: %10s= %#06X\n", pic->rram, getFSRname_18 (pic->rram), pic->ram[pic->rram]);
 if ((pic->print)&&(pic->lram != 0x8000))printf ("mem write %#06X: %10s= %#06X\n", pic->lram, getFSRname_18 (pic->lram), pic->ram[pic->lram]);
 /*
 if ((pic->print)&&(pic->lram ==  sfr_addr (pic->P18map.STKPTR)))
  {
   printf("STKPTR=%u\n",(*pic->P18map.STKPTR));
   for(int i=0;i< pic->STACKSIZE ; i++)
    {
     printf("  stack[%02i]=0x%06X \n",i,pic->stack[i]);
    }
  }
   if(((*pic->P18map.PCL)) != (pc_ant&0x00FF))
   {
     pic->pc=(((*pic->P18map.PCLATH)&0x1F)<<8)|pic->ram[PCL];//conferir
   }
  */

}


