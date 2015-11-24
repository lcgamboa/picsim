/* ########################################################################

   PICsim - PIC simulator

   ########################################################################

   Copyright (c) : 2008-2015  Luis Claudio Gambôa Lopes

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

#include"picsim.h"
#include"periferic18.h"


#include "ansi.h"



void
pic_decode_18(_pic * pic,int print)
{
  unsigned short temp;
  unsigned char  ctemp;
  unsigned short opc;
  unsigned short bank= ((pic->ram[P18_BSR] & 0x0F)<<8);
  unsigned char * status = &pic->ram[P18_STATUS];
  unsigned char * intcon = &pic->ram[P18_INTCON];
  unsigned short  afsr0= ((pic->ram[P18_FSR0H]&0x0F)<<8) |pic->ram[P18_FSR0L];
  unsigned short  afsr1= ((pic->ram[P18_FSR1H]&0x0F)<<8) |pic->ram[P18_FSR1L];
  unsigned short  afsr2= ((pic->ram[P18_FSR2H]&0x0F)<<8) |pic->ram[P18_FSR2L];
  //unsigned short  pc_ant;
 
  unsigned short raddr;
  unsigned int tblptr;
  
  short jrange; 

/*
  inline void fraddr(void)
  {
    if(opc & 0x0100)//a =1
      raddr=bank|(opc & 0x00FF);
    else
      if(opc & 0x0080)//SFR bank15
        raddr=0xF00|(opc & 0x00FF);
      else //bank0
         raddr=(opc & 0x00FF);
  };
*/
#define  fraddr()\
    if(opc & 0x0100)\
      raddr=bank|(opc & 0x00FF);\
    else\
      if(opc & 0x0080)\
        raddr=0xF00|(opc & 0x00FF);\
      else\
         raddr=(opc & 0x00FF);


  pic->lram=0x8000;
  pic->rram=0x8000;
  
  if(pic->sleep == 1)
  {
    if(print)printf("sleep WDT=%i wdt=%f ms=%i\n",((pic->config[0] & 0x04) == 0x04 ),pic->twdt,pic->wdt); 
    return;
  }
  
  if((!(pic->config[3] & 0x0080))&&(!(pic->ram[P18_DEBUG]&0x80))&&(pic->frst)&&(pic->pc == 0))
  {
    pic->frst=0; 
    return;
  }
  
  //incompleto - verificar salto pcl e pch!
  if(pic->s2 == 1)
  {
    pic->s2=0;
    if(pic->jpc != 0xFFFFF)
    {
      pic->pc=pic->jpc;
      pic->jpc=0xFFFFF;
    }

    return;
  };
  
    if(print)printf("pc=%#06X\t",pic->pc); 
// debug
  if((pic->pc >= 0x200028)&&((pic->pc <= 0x200037)))
  {
    //int i;
    opc= pic->debugv[pic->pc - 0x200028];
    //printf("PC=0x%04X\n",pic->pc); 
/*
    for(i=0;i<8;i++)
       printf("debug[%i]=0x%04X\n",i,pic->debugv[i]);
*/      
     //if(print)printf("prog=%#06X\t",opc/*pic->prog[pic->pc]*/); 
  }
  else
  { 
    opc=pic->prog[pic->pc>>1];
    //if(print)printf("prog=%#06X\t",pic->debugv[0]); 
  }
 
  if(print)printf("prog=%#06X\t",opc); 

  pic->pc+=2;
  if(((pic->pc>>1) >= pic->ROMSIZE)&&(pic->pc!=0x20002A )) pic->pc=0;

//pc
  pic->ram[P18_PCL] = pic->pc&0x00FF;
  
	  //pc_ant = pic->pc&0x00FF;
  
  pic->ram[P18_INDF0]=pic->ram[afsr0];
  pic->ram[P18_POSTINC0]=pic->ram[afsr0];
  pic->ram[P18_POSTDEC0]=pic->ram[afsr0];
  pic->ram[P18_PREINC0]=pic->ram[(afsr0+1) % pic->RAMSIZE]; 
  pic->ram[P18_PLUSW0]=pic->ram[(afsr0+((char)pic->ram[P18_WREG])) % pic->RAMSIZE];
 
/*
  if((afsr0+1) < pic->RAMSIZE)
  {
    pic->ram[P18_PREINC0]=pic->ram[afsr0+1];
    if((afsr0+pic->ram[P18_WREG]) < pic->RAMSIZE)
    {
       pic->ram[P18_PLUSW0]=pic->ram[afsr0+((char)pic->ram[P18_WREG])];
    }
    else  
    {
       pic->ram[P18_PLUSW0]=0;
    }
  }
  else
  {
    pic->ram[P18_PREINC0]=0;
    pic->ram[P18_PLUSW0]=0;
  }
*/

  pic->ram[P18_INDF1]=pic->ram[afsr1];
  pic->ram[P18_POSTINC1]=pic->ram[afsr1];
  pic->ram[P18_POSTDEC1]=pic->ram[afsr1];
  pic->ram[P18_PREINC1]=pic->ram[(afsr1+1) % pic->RAMSIZE]; 
  pic->ram[P18_PLUSW1]=pic->ram[(afsr1+((char)pic->ram[P18_WREG])) % pic->RAMSIZE];

/*
  if((afsr1+1) < pic->RAMSIZE)
  {
    pic->ram[P18_PREINC1]=pic->ram[afsr1+1];
    if((afsr1+pic->ram[P18_WREG]) < pic->RAMSIZE)
    {
      pic->ram[P18_PLUSW1]=pic->ram[afsr1+((char)pic->ram[P18_WREG])];
    }
    else
    {
      pic->ram[P18_PLUSW1]=0;
    }
  }
  else
  {
    pic->ram[P18_PREINC1]=0;
    pic->ram[P18_PLUSW1]=0;
  }
*/
 
  pic->ram[P18_INDF2]=pic->ram[afsr2];
  pic->ram[P18_POSTINC2]=pic->ram[afsr2];
  pic->ram[P18_POSTDEC2]=pic->ram[afsr2];
  pic->ram[P18_PREINC2]=pic->ram[(afsr2+1) % pic->RAMSIZE]; 
  pic->ram[P18_PLUSW2]=pic->ram[(afsr2+((char)pic->ram[P18_WREG])) % pic->RAMSIZE];

/*
  if((afsr2+1) < pic->RAMSIZE)
  {
    pic->ram[P18_PREINC2]=pic->ram[afsr2+1];
    if((afsr2+pic->ram[P18_WREG]) < pic->RAMSIZE)
    {
      pic->ram[P18_PLUSW2]=pic->ram[afsr2+((char)pic->ram[P18_WREG])];
    }
    else
    {
      pic->ram[P18_PLUSW2]=0;
    }
  }
  else
  {
    pic->ram[P18_PREINC2]=0;
    pic->ram[P18_PLUSW2]=0;
  }
*/
            


  
  switch(opc & 0xF000)
  {
    case 0x0000:
      switch(opc & 0x0F00)
      {
        case 0x0000:
	  switch(opc & 0x00FF)
          { 
            case 0x0000:
//NOP    --   		No Operation                 1     	0000 0000 0000 0000 None
              if(print)printf("NOP\n");
              break;
            case 0x0003:
//SLEEP  --   		Go into Standby mode         1     	0000 0000 0000 0011 TO, PD
              if(print)printf("SLEEP\n");
  	      pic->wdt=0;
  	      pic->sleep=1;
	      pic->ram[P18_RCON]&=~0x08;
	      pic->ram[P18_RCON]|=0x04;
	      break;
            case 0x0004:
//CLRWDT --   		Clear Watchdog Timer         1     	0000 0000 0000 0100 TO, PD
              if(print)printf("CLRWDT\n");
              pic->wdt=0;
	      pic->ram[P18_RCON]|=0x08;
	      pic->ram[P18_RCON]|=0x04;
  	      break;
            case 0x0005:
//PUSH   --   		Push top of ret stack(TOS)   1     	0000 0000 0000 0101 None
              if(print)printf("PUSH \n");           
              if((pic->ram[P18_STKPTR] & 0x1F) < 31 )
              {
	        pic->stack[pic->ram[P18_STKPTR]& 0x1F]=pic->pc;
                pic->ram[P18_STKPTR]=(pic->ram[P18_STKPTR] &0xC0) | ((pic->ram[P18_STKPTR] &0x1F)+1);    
                if((pic->ram[P18_STKPTR]& 0x1F) == 31)pic->ram[P18_STKPTR]|=0x80; //set STKFUL
              }
              pic->lram=P18_STKPTR;
	      break;
            case 0x0006:
//POP    --   		Pop top of ret stack(TOS)    1     	0000 0000 0000 0110 None
              if(print)printf("POP \n");
              if((pic->ram[P18_STKPTR] & 0x1F) > 0 )
              {
                pic->ram[P18_STKPTR]=(pic->ram[P18_STKPTR] &0xC0) | ((pic->ram[P18_STKPTR] &0x1F)-1);    
              }
              else
                pic->ram[P18_STKPTR]|=0x40; //set STKUNF  
              pic->lram=P18_STKPTR;
              break;
            case 0x0007:
//DAW    --   		Decimal Adjust WREG          1     	0000 0000 0000 0111 C
              if(print)printf("DAW \n");
              pic->lram=P18_WREG;

	      if(((pic->ram[P18_WREG]&0x0F) >9) | (*status &0x02))
              {
                temp=(pic->ram[P18_WREG] & 0x0F)+6;
              }
              else
              {
                temp=pic->ram[P18_WREG] & 0x0F;
              } 
              if(((pic->ram[P18_WREG]&0xF0)>>4   >9) | (*status & 0x01))
              {
                temp|=(pic->ram[P18_WREG]&0xF0)+0x60;
              } 
              else
              {
                temp|=pic->ram[P18_WREG]&0xF0;
	      } 

	      if ((0x00FF&temp) == 0xFF) 
	        *status|=0x01;
	      else   
	        *status&=~0x01;

	      pic->ram[P18_WREG]=(temp & 0x00FF);
	      break;
            case 0x0008:
//TBLRD*       		Table Read                   2     	0000 0000 0000 1000 None
              if(print)printf("TBLRD *\n");
              tblptr=(pic->ram[P18_TBLPTRU]<<16) | (pic->ram[P18_TBLPTRH]<<8) | pic->ram[P18_TBLPTRL];
              if((tblptr>>1) < pic->ROMSIZE)
              {   
                if(tblptr & 0x0001)
	          pic->ram[P18_TABLAT]=(pic->prog[tblptr>>1]&0xFF00 )>> 8;
	        else
	          pic->ram[P18_TABLAT]=pic->prog[tblptr>>1]&0x00FF;
              }
              //read id
	      else if((tblptr >=0x200000)&&(tblptr <= 0x200007))
              {
                if(tblptr & 0x0001)
	          pic->ram[P18_TABLAT]=(pic->id[(tblptr-0x200000)>>1]&0xFF00 )>>8;
	        else
	          pic->ram[P18_TABLAT]=(pic->id[(tblptr-0x200000)>>1]&0x00FF);
              }	
              //read config
	      else if((tblptr >=0x300000)&&(tblptr <= 0x30000D))
              {
                if(tblptr & 0x0001)
	          pic->ram[P18_TABLAT]=(pic->config[(tblptr-0x300000)>>1]&0xFF00 )>>8;
	        else
	          pic->ram[P18_TABLAT]=(pic->config[(tblptr-0x300000)>>1]&0x00FF);
              }	
              //read device id 
              else if((tblptr & 0x3FFFFE ) == 0x3FFFFE )
              {   
                if(tblptr & 0x0001)
	          pic->ram[P18_TABLAT]=(pic->processor&0xFF00 )>>8;
	        else
	          pic->ram[P18_TABLAT]=(pic->processor&0x00FF);
              }
              //read debug vector 
	      else if((tblptr >=0x200028)&&(tblptr <= 0x200037))
              {
                if(tblptr & 0x0001)
	          pic->ram[P18_TABLAT]=(pic->debugv[(tblptr-0x200028)>>1]&0xFF00 )>>8;
	        else
	          pic->ram[P18_TABLAT]=(pic->debugv[(tblptr-0x200028)>>1]&0x00FF);
              }
              else
	        pic->ram[P18_TABLAT]=0;
	      pic->s2=1;
              break; 
            case 0x0009:
//TBLRD*+      		Table Read with post-inc     2 (5)   	0000 0000 0000 1001 None
              if(print)printf("TBLRD *+\n");
              tblptr=(pic->ram[P18_TBLPTRU]<<16) | (pic->ram[P18_TBLPTRH]<<8) | pic->ram[P18_TBLPTRL];
              if((tblptr>>1) < pic->ROMSIZE)
              {   
                if(tblptr & 0x0001)
	          pic->ram[P18_TABLAT]=(pic->prog[tblptr>>1]&0xFF00 )>> 8;
	        else
	          pic->ram[P18_TABLAT]=pic->prog[tblptr>>1]&0x00FF;
              }
              //read id
	      else if((tblptr >=0x200000)&&(tblptr <= 0x200007))
              {
                if(tblptr & 0x0001)
	          pic->ram[P18_TABLAT]=(pic->id[(tblptr-0x200000)>>1]&0xFF00 )>>8;
	        else
	          pic->ram[P18_TABLAT]=(pic->id[(tblptr-0x200000)>>1]&0x00FF);
              }	
              //read config
	      else if((tblptr >=0x300000)&&(tblptr <= 0x30000D))
              {
                if(tblptr & 0x0001)
	          pic->ram[P18_TABLAT]=(pic->config[(tblptr-0x300000)>>1]&0xFF00 )>>8;
	        else
	          pic->ram[P18_TABLAT]=(pic->config[(tblptr-0x300000)>>1]&0x00FF);
              }	
              //read device id 
              else if((tblptr & 0x3FFFFE ) == 0x3FFFFE )
              {   
                if(tblptr & 0x0001)
	          pic->ram[P18_TABLAT]=(pic->processor&0xFF00 )>>8;
	        else
	          pic->ram[P18_TABLAT]=(pic->processor&0x00FF);
              }
              //read debug vector 
	      else if((tblptr >=0x200028)&&(tblptr <= 0x200037))
              {
                if(tblptr & 0x0001)
	          pic->ram[P18_TABLAT]=(pic->debugv[(tblptr-0x200028)>>1]&0xFF00 )>>8;
	        else
	          pic->ram[P18_TABLAT]=(pic->debugv[(tblptr-0x200028)>>1]&0x00FF);
              }
              else
	        pic->ram[P18_TABLAT]=0;
              tblptr++;
              pic->ram[P18_TBLPTRU]=(tblptr&0x3F0000)>>16; 
              pic->ram[P18_TBLPTRH]=(tblptr&0x00FF00)>>8;
              pic->ram[P18_TBLPTRL]=(tblptr&0x0000FF);  
	      pic->s2=1;
              break; 
            case 0x000A:
//TBLRD*-      		Table Read with post-dec     2 (5)   	0000 0000 0000 1010 None
              if(print)printf("TBLRD *-\n");
              tblptr=(pic->ram[P18_TBLPTRU]<<16) | (pic->ram[P18_TBLPTRH]<<8) | pic->ram[P18_TBLPTRL];
              if((tblptr>>1) < pic->ROMSIZE)
              {   
                if(tblptr & 0x0001)
	          pic->ram[P18_TABLAT]=(pic->prog[tblptr>>1]&0xFF00 )>> 8;
	        else
	          pic->ram[P18_TABLAT]=pic->prog[tblptr>>1]&0x00FF;
              }
              //read id
	      else if((tblptr >=0x200000)&&(tblptr <= 0x200007))
              {
                if(tblptr & 0x0001)
	          pic->ram[P18_TABLAT]=(pic->id[(tblptr-0x200000)>>1]&0xFF00 )>>8;
	        else
	          pic->ram[P18_TABLAT]=(pic->id[(tblptr-0x200000)>>1]&0x00FF);
              }	
              //read config
	      else if((tblptr >=0x300000)&&(tblptr <= 0x30000D))
              {
                if(tblptr & 0x0001)
	          pic->ram[P18_TABLAT]=(pic->config[(tblptr-0x300000)>>1]&0xFF00 )>>8;
	        else
	          pic->ram[P18_TABLAT]=(pic->config[(tblptr-0x300000)>>1]&0x00FF);
              }	
              //read device id 
              else if((tblptr & 0x3FFFFE ) == 0x3FFFFE )
              {   
                if(tblptr & 0x0001)
	          pic->ram[P18_TABLAT]=(pic->processor&0xFF00 )>>8;
	        else
	          pic->ram[P18_TABLAT]=(pic->processor&0x00FF);
              }
              //read debug vector 
	      else if((tblptr >=0x200028)&&(tblptr <= 0x200037))
              {
                if(tblptr & 0x0001)
	          pic->ram[P18_TABLAT]=(pic->debugv[(tblptr-0x200028)>>1]&0xFF00 )>>8;
	        else
	          pic->ram[P18_TABLAT]=(pic->debugv[(tblptr-0x200028)>>1]&0x00FF);
              }
              else
	        pic->ram[P18_TABLAT]=0;
              tblptr--;
              pic->ram[P18_TBLPTRU]=(tblptr&0x3F0000)>>16; 
              pic->ram[P18_TBLPTRH]=(tblptr&0x00FF00)>>8;
              pic->ram[P18_TBLPTRL]=(tblptr&0x0000FF);  
	      pic->s2=1;
              break; 
            case 0x000B:
//TBLRD+*      		Table Read with pre-inc      2 (5)   	0000 0000 0000 1011 None
              if(print)printf("TBLRD +*\n");
              tblptr=(pic->ram[P18_TBLPTRU]<<16) | (pic->ram[P18_TBLPTRH]<<8) | pic->ram[P18_TBLPTRL];
              tblptr= (tblptr+1)&0x001FFFFF;
              if((tblptr>>1) < pic->ROMSIZE)
              {   
                if(tblptr & 0x0001)
	          pic->ram[P18_TABLAT]=(pic->prog[tblptr>>1]&0xFF00 )>> 8;
	        else
	          pic->ram[P18_TABLAT]=pic->prog[tblptr>>1]&0x00FF;
              }
              //read id
	      else if((tblptr >=0x200000)&&(tblptr <= 0x200007))
              {
                if(tblptr & 0x0001)
	          pic->ram[P18_TABLAT]=(pic->id[(tblptr-0x200000)>>1]&0xFF00 )>>8;
	        else
	          pic->ram[P18_TABLAT]=(pic->id[(tblptr-0x200000)>>1]&0x00FF);
              }	
              //read config
	      else if((tblptr >=0x300000)&&(tblptr <= 0x30000D))
              {
                if(tblptr & 0x0001)
	          pic->ram[P18_TABLAT]=(pic->config[(tblptr-0x300000)>>1]&0xFF00 )>>8;
	        else
	          pic->ram[P18_TABLAT]=(pic->config[(tblptr-0x300000)>>1]&0x00FF);
              }	
              //read device id 
              else if((tblptr & 0x3FFFFE ) == 0x3FFFFE )
              {   
                if(tblptr & 0x0001)
	          pic->ram[P18_TABLAT]=(pic->processor&0xFF00 )>>8;
	        else
	          pic->ram[P18_TABLAT]=(pic->processor&0x00FF);
              }
              //read debug vector 
	      else if((tblptr >=0x200028)&&(tblptr <= 0x200037))
              {
                if(tblptr & 0x0001)
	          pic->ram[P18_TABLAT]=(pic->debugv[(tblptr-0x200028)>>1]&0xFF00 )>>8;
	        else
	          pic->ram[P18_TABLAT]=(pic->debugv[(tblptr-0x200028)>>1]&0x00FF);
              }
              else
	        pic->ram[P18_TABLAT]=0;
              pic->ram[P18_TBLPTRU]=(tblptr&0x3F0000)>>16; 
              pic->ram[P18_TBLPTRH]=(tblptr&0x00FF00)>>8;
              pic->ram[P18_TBLPTRL]=(tblptr&0x0000FF);  
	      pic->s2=1;
              break; 
            case 0x000C:
//TBLWT*       		Table Write                  2 (5) 	0000 0000 0000 1100 None
              if(print)printf("TBLWT *\n");
              tblptr=(pic->ram[P18_TBLPTRU]<<16) | (pic->ram[P18_TBLPTRH]<<8) | pic->ram[P18_TBLPTRL];
              if((tblptr>>1) < pic->ROMSIZE)
              {   
                if(tblptr & 0x0001)
	          pic->prog[tblptr>>1] = (pic->prog[tblptr>>1]&0x00FF ) |  pic->ram[P18_TABLAT]<<8;
	        else
	          pic->prog[tblptr>>1] = (pic->prog[tblptr>>1]&0xFF00 ) |  pic->ram[P18_TABLAT];
              }
              //write id
	      else if((tblptr >=0x200000)&&(tblptr <= 0x200007))
              {
                if(tblptr & 0x0001)
	          pic->id[(tblptr-0x200000)>>1] = (pic->id[(tblptr-0x200000)>>1]&0x00FF ) |  pic->ram[P18_TABLAT]<<8;
	        else
	          pic->id[(tblptr-0x200000)>>1] = (pic->id[(tblptr-0x200000)>>1]&0xFF00 ) |  pic->ram[P18_TABLAT];
              }	
              //write config
	      else if((tblptr >=0x300000)&&(tblptr <= 0x30000D))
              {
                if(tblptr & 0x0001)
	          pic->config[(tblptr-0x300000)>>1] = (pic->config[(tblptr-0x300000)>>1]&0x00FF ) |  pic->ram[P18_TABLAT]<<8;
	        else
	          pic->config[(tblptr-0x300000)>>1] = (pic->config[(tblptr-0x300000)>>1]&0xFF00 ) |  pic->ram[P18_TABLAT];

                printf("TBLWT* 0x%06X   0x%02X \n",tblptr,P18_TABLAT);
              }
              //debug vector  
	      else if((tblptr >=0x200028)&&(tblptr <= 0x200037))
              {
                if(tblptr & 0x0001)
	          pic->debugv[(tblptr-0x200028)>>1] = (pic->debugv[(tblptr-0x200028)>>1]&0x00FF ) |  pic->ram[P18_TABLAT]<<8;
	        else
	          pic->debugv[(tblptr-0x200028)>>1] = (pic->debugv[(tblptr-0x200028)>>1]&0xFF00 ) |  pic->ram[P18_TABLAT];
              }

	      pic->s2=1;
              break; 
            case 0x000D:
//TBLWT*+      		Table Write with post-inc    2 (5)   	0000 0000 0000 1101 None
              if(print)printf("TBLWT *+\n");
              tblptr=(pic->ram[P18_TBLPTRU]<<16) | (pic->ram[P18_TBLPTRH]<<8) | pic->ram[P18_TBLPTRL];
              if((tblptr>>1) < pic->ROMSIZE)
              {   
                if(tblptr & 0x0001)
	          pic->prog[tblptr>>1] = (pic->prog[tblptr>>1]&0x00FF ) |  pic->ram[P18_TABLAT]<<8;
	        else
	          pic->prog[tblptr>>1] = (pic->prog[tblptr>>1]&0xFF00 ) |  pic->ram[P18_TABLAT];
              }
              //write id
	      else if((tblptr >=0x200000)&&(tblptr <= 0x200007))
              {
                if(tblptr & 0x0001)
	          pic->id[(tblptr-0x200000)>>1] = (pic->id[(tblptr-0x200000)>>1]&0x00FF ) |  pic->ram[P18_TABLAT]<<8;
	        else
	          pic->id[(tblptr-0x200000)>>1] = (pic->id[(tblptr-0x200000)>>1]&0xFF00 ) |  pic->ram[P18_TABLAT];
              }	
              //write config
	      else if((tblptr >=0x300000)&&(tblptr <= 0x30000D))
              {
                if(tblptr & 0x0001)
	          pic->config[(tblptr-0x300000)>>1] = (pic->config[(tblptr-0x300000)>>1]&0x00FF ) |  pic->ram[P18_TABLAT]<<8;
	        else
	          pic->config[(tblptr-0x300000)>>1] = (pic->config[(tblptr-0x300000)>>1]&0xFF00 ) |  pic->ram[P18_TABLAT];
                printf("TBLWT*+ 0x%06X   0x%02X \n",tblptr,P18_TABLAT);
              }
              //debug vector  
	      else if((tblptr >=0x200028)&&(tblptr <= 0x200037))
              {
                if(tblptr & 0x0001)
	          pic->debugv[(tblptr-0x200028)>>1] = (pic->debugv[(tblptr-0x200028)>>1]&0x00FF ) |  pic->ram[P18_TABLAT]<<8;
	        else
	          pic->debugv[(tblptr-0x200028)>>1] = (pic->debugv[(tblptr-0x200028)>>1]&0xFF00 ) |  pic->ram[P18_TABLAT];
              }
              tblptr++;
              pic->ram[P18_TBLPTRU]=(tblptr&0x3F0000)>>16; 
              pic->ram[P18_TBLPTRH]=(tblptr&0x00FF00)>>8;
              pic->ram[P18_TBLPTRL]=(tblptr&0x0000FF);  
	      pic->s2=1;
              break; 
            case 0x000E:
//TBLWT*-      		Table Write with post-dec    2 (5)   	0000 0000 0000 1110 None
              if(print)printf("TBLWT *-\n");
              tblptr=(pic->ram[P18_TBLPTRU]<<16) | (pic->ram[P18_TBLPTRH]<<8) | pic->ram[P18_TBLPTRL];
              if((tblptr>>1) < pic->ROMSIZE)
              {   
                if(tblptr & 0x0001)
	          pic->prog[tblptr>>1] = (pic->prog[tblptr>>1]&0x00FF ) |  pic->ram[P18_TABLAT]<<8;
	        else
	          pic->prog[tblptr>>1] = (pic->prog[tblptr>>1]&0xFF00 ) |  pic->ram[P18_TABLAT];
              }
              //write id
	      else if((tblptr >=0x200000)&&(tblptr <= 0x200007))
              {
                if(tblptr & 0x0001)
	          pic->id[(tblptr-0x200000)>>1] = (pic->id[(tblptr-0x200000)>>1]&0x00FF ) |  pic->ram[P18_TABLAT]<<8;
	        else
	          pic->id[(tblptr-0x200000)>>1] = (pic->id[(tblptr-0x200000)>>1]&0xFF00 ) |  pic->ram[P18_TABLAT];
              }	
              //write config
	      else if((tblptr >=0x300000)&&(tblptr <= 0x30000D))
              {
                if(tblptr & 0x0001)
	          pic->config[(tblptr-0x300000)>>1] = (pic->config[(tblptr-0x300000)>>1]&0x00FF ) |  pic->ram[P18_TABLAT]<<8;
	        else
	          pic->config[(tblptr-0x300000)>>1] = (pic->config[(tblptr-0x300000)>>1]&0xFF00 ) |  pic->ram[P18_TABLAT];
                printf("TBLWT*- 0x%06X   0x%02X \n",tblptr,P18_TABLAT);
              }
              //debug vector  
	      else if((tblptr >=0x200028)&&(tblptr <= 0x200037))
              {
                if(tblptr & 0x0001)
	          pic->debugv[(tblptr-0x200028)>>1] = (pic->debugv[(tblptr-0x200028)>>1]&0x00FF ) |  pic->ram[P18_TABLAT]<<8;
	        else
	          pic->debugv[(tblptr-0x200028)>>1] = (pic->debugv[(tblptr-0x200028)>>1]&0xFF00 ) |  pic->ram[P18_TABLAT];
              }
              tblptr--;
              pic->ram[P18_TBLPTRU]=(tblptr&0x3F0000)>>16; 
              pic->ram[P18_TBLPTRH]=(tblptr&0x00FF00)>>8;
              pic->ram[P18_TBLPTRL]=(tblptr&0x0000FF);  
	      pic->s2=1;
              break; 
            case 0x000F:
//TBLWT+*      		Table Write with pre-inc     2 (5)   	0000 0000 0000 1111 None
              if(print)printf("TBLWT +*\n");
              tblptr=(pic->ram[P18_TBLPTRU]<<16) | (pic->ram[P18_TBLPTRH]<<8) | pic->ram[P18_TBLPTRL];
              tblptr= (tblptr+1)&0x001FFFFF;
              if((tblptr>>1) < pic->ROMSIZE)
              {   
                if(tblptr & 0x0001)
	          pic->prog[tblptr>>1] = (pic->prog[tblptr>>1]&0x00FF ) |  pic->ram[P18_TABLAT]<<8;
	        else
	          pic->prog[tblptr>>1] = (pic->prog[tblptr>>1]&0xFF00 ) |  pic->ram[P18_TABLAT];
              }
              //write id
	      else if((tblptr >=0x200000)&&(tblptr <= 0x200007))
              {
                if(tblptr & 0x0001)
	          pic->id[(tblptr-0x200000)>>1] = (pic->id[(tblptr-0x200000)>>1]&0x00FF ) |  pic->ram[P18_TABLAT]<<8;
	        else
	          pic->id[(tblptr-0x200000)>>1] = (pic->id[(tblptr-0x200000)>>1]&0xFF00 ) |  pic->ram[P18_TABLAT];
              }	
              //write config
	      else if((tblptr >=0x300000)&&(tblptr <= 0x30000D))
              {
                if(tblptr & 0x0001)
	          pic->config[(tblptr-0x300000)>>1] = (pic->config[(tblptr-0x300000)>>1]&0x00FF ) |  pic->ram[P18_TABLAT]<<8;
	        else
	          pic->config[(tblptr-0x300000)>>1] = (pic->config[(tblptr-0x300000)>>1]&0xFF00 ) |  pic->ram[P18_TABLAT];
                printf("TBLWT+* 0x%06X   0x%02X \n",tblptr,P18_TABLAT);
              }
              //debug vector  
	      else if((tblptr >=0x200028)&&(tblptr <= 0x200037))
              {
                if(tblptr & 0x0001)
	          pic->debugv[(tblptr-0x200028)>>1] = (pic->debugv[(tblptr-0x200028)>>1]&0x00FF ) |  pic->ram[P18_TABLAT]<<8;
	        else
	          pic->debugv[(tblptr-0x200028)>>1] = (pic->debugv[(tblptr-0x200028)>>1]&0xFF00 ) |  pic->ram[P18_TABLAT];
              }
              pic->ram[P18_TBLPTRU]=(tblptr&0x3F0000)>>16; 
              pic->ram[P18_TBLPTRH]=(tblptr&0x00FF00)>>8;
              pic->ram[P18_TBLPTRL]=(tblptr&0x0000FF);  
	      pic->s2=1;
              break; 
            case 0x0010:
            case 0x0011:
//RETFIE s    		Return from interrupt enable 2     	0000 0000 0001 000s GIE/GIEH,PEIE/GIEL
              if(print)printf("RETFIE\n");
	      
              if((pic->ram[P18_STKPTR] & 0x1F) > 0 )
              {
                pic->ram[P18_STKPTR]=(pic->ram[P18_STKPTR] &0xC0) | ((pic->ram[P18_STKPTR] &0x1F)-1);      
                pic->jpc=pic->stack[pic->ram[P18_STKPTR] & 0x1F];  
              }
              else
              {
                pic->ram[P18_STKPTR]|=0x40; //set STKUNF  
                pic->jpc=0;
              }
              pic->lram=P18_STKPTR;
              
	      pic->s2=1;

            
              if(pic->intlv &0x02)
              {
	        *intcon|=0x40;
                pic->intlv&=~0x02;
              }
              else  
              { 
	        *intcon|=0x80;
                pic->intlv&=~0x01;
              }

              if(opc & 0x0001 )
              {
                pic->ram[P18_WREG]=pic->ram[P18_WS]; 	 
                pic->ram[P18_STATUS]=pic->ram[P18_STATUSS];
                pic->ram[P18_BSR]=pic->ram[P18_BSRS];
              }
	      break;
            case 0x0012:
            case 0x0013:
//RETURN s    		Return from Subroutine       2     	0000 0000 0001 001s None
              if(print)printf("RETURN %d\n",opc & 0x0001);
              if((pic->ram[P18_STKPTR] & 0x1F) > 0 )
              {
                pic->ram[P18_STKPTR]=(pic->ram[P18_STKPTR] &0xC0) | ((pic->ram[P18_STKPTR] &0x1F)-1);     
                pic->jpc=pic->stack[pic->ram[P18_STKPTR] & 0x1F];   
              }
              else
              {
                pic->ram[P18_STKPTR]|=0x40; //set STKUNF  
                pic->jpc=0;
              }
              pic->lram=P18_STKPTR;
              
	      pic->s2=1;
	  
              if(opc & 0x0001 )
              {
                pic->ram[P18_WREG]=pic->ram[P18_WS]; 	 
                pic->ram[P18_STATUS]=pic->ram[P18_STATUSS];
                pic->ram[P18_BSR]=pic->ram[P18_BSRS];
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
              if(print)printf("TRAP\n");
          
 	      if((pic->config[3] & 0x0080) == 0) //DEBUG ON
              {
              if(pic->pc != 0x00000)
              {
                 //printf("Debug stack save\n");
                 if((pic->ram[P18_STKPTR] & 0x1F) < 31 )
                 {
	            pic->stack[pic->ram[P18_STKPTR]& 0x1F]=pic->pc;
                    pic->ram[P18_STKPTR]=(pic->ram[P18_STKPTR] &0xC0) | ((pic->ram[P18_STKPTR] &0x1F)+1);    
                    if((pic->ram[P18_STKPTR]& 0x1F) == 31)pic->ram[P18_STKPTR]|=0x80; //set STKFUL
                 }
                 pic->lram=P18_STKPTR;
              }
	  
	     pic->ram[P18_DEBUG]|=0x80;
	     pic->ram[P18_BDMSR2]= (pic->pc&0xFF0000)>>16;
	     pic->ram[P18_BDMSR1]= (pic->pc&0x00FF00)>>8;
	     pic->ram[P18_BDMSR0]= (pic->pc&0x0000FF);
	     pic->jpc=0x200028;
	     pic->s2=1;
             pic->debug=1;
             pic->sstep=0;
             } 
	      break;
            case 0x00E1:
//TRET    		Return Debug Subroutine       2     	0000 0000 1110 0001 None
              if(print)printf("TRET\n");
              if((pic->ram[P18_STKPTR] & 0x1F) > 0 )
              {
                pic->ram[P18_STKPTR]=(pic->ram[P18_STKPTR] &0xC0) | ((pic->ram[P18_STKPTR] &0x1F)-1);    
                pic->jpc=pic->stack[pic->ram[P18_STKPTR] & 0x1F];    
              }
              else
              {
                pic->ram[P18_STKPTR]|=0x40; //set STKUNF  
                pic->jpc=0;
              }
              pic->lram=P18_STKPTR;
	      pic->s2=1;
/*	  
              if(opc & 0x0001 )
              {
                pic->ram[P18_WREG]=pic->ram[P18_WS]; 	 
                pic->ram[P18_STATUS]=pic->ram[P18_STATUSS];
                pic->ram[P18_BSR]=pic->ram[P18_BSRS];
               }
*/
	      //if((pic->ram[P18_DEBUG] & 0x80)== 0x80)printf("Out DEBUG mode\n");
	      pic->debug=0;
              pic->sstep=0;          
              pic->dbg=0;          
	      pic->ram[P18_DEBUG]&=~0x80;
	      break;

//RESET       		Software device RESET        1     	0000 0000 1111 1111 All
            case 0x00FF:
		pic_reset(pic,0);
		return;
	      break;
            default:
              //printf("unknown opcode!\n");
              break; 
          }
	  break;
        case 0x0100:
//MOVLB    k    	Move literal to BSR<3:0>     1     	0000 0001 0000 kkkk None
          if(print)printf("MOVLB %#04X\n",opc & 0x000F);
	  pic->ram[P18_BSR]= (opc & 0x000F);
          pic->lram=P18_BSR;
          break;
        case 0x0200:
        case 0x0300:
//MULWF  f, a    	Multiply WREG with f         1          0000 001a ffff ffff None
          if(print)printf("MULWF %#06X,%d\n",opc & 0x00FF,(opc & 0x0100)>>8);
          fraddr();
	  temp=pic->ram[P18_WREG]*pic->ram[raddr];
          pic->ram[P18_PRODH]=(temp&0xFF00)>>8;
          pic->ram[P18_PRODL]=temp & 0x00FF;
          pic->rram=raddr;
          pic->lram=P18_PRODH;
	  break;
        case 0x0400:
        case 0x0500:
        case 0x0600:
        case 0x0700:
//DECF   f, d, a 	Decrement f                  1          0000 01da ffff ffff C, DC, Z, OV, N 1, 2, 3, 4
          if(print)printf("DECF %#06X,%d,%d\n",opc & 0x00FF,(opc & 0x0200)>>9,(opc & 0x0100)>>8);
	  fraddr();	
	  if((0xF0&((0x0F&(pic->ram[raddr]))+0x0F)) !=0)
	    *status|=0x02;
	  else   
	    *status&=~0x02;
          pic->rram=raddr;
          temp=pic->ram[raddr]-1;
	
	  if ((0x00FF&temp) == 0xFF) 
	    *status&=~0x01;
	  else   
	    *status|=0x01;

          ctemp=(unsigned char)(0x00FF &temp);

          if(opc & 0x0200) //dest FILE
	  {
	    if ((pic->ram[raddr] & 0x80)!=(ctemp&0x80))  
	       *status|=0x08;
	    else   
	       *status&=~0x08;
            pic->lram=raddr;
	    pic->ram[raddr]=ctemp;
	    
            if (pic->ram[raddr] == 0) 
	       *status|=0x04;
	    else   
	       *status&=~0x04;
	    if (pic->ram[raddr] & 0x80) 
	       *status|=0x10;
	    else   
	       *status&=~0x10;
 
	  } 
          else  //dest W     
	  {
	    if ((pic->ram[P18_WREG] & 0x80)!=(ctemp&0x80))  
	       *status|=0x08;
	    else   
	       *status&=~0x08;
            pic->lram=P18_WREG;
	    pic->ram[P18_WREG]=ctemp;
	    if (pic->ram[P18_WREG] == 0) 
	       *status|=0x04;
	    else   
	       *status&=~0x04;
	    if (pic->ram[P18_WREG] & 0x80) 
	       *status|=0x10;
	    else   
	       *status&=~0x10;
          }
	  break;
        case 0x0800:
//SUBLW    k    	Subtract WREG from literal   1     	0000 1000 kkkk kkkk C, DC, Z, OV, N
          if(print)printf("SUBLW %#06X\n",opc & 0x00FF);
	
	  if((0xF0&((0x0F&(~pic->ram[P18_WREG]))+1+(opc & 0x000F))) !=0)
	    *status|=0x02;
	  else   
	    *status&=~0x02;

          pic->lram=P18_WREG;
          
	  temp=(~pic->ram[P18_WREG]+1)+(opc & 0x00FF);

	  ctemp=(unsigned char)(0x00FF &temp);
	
	   *status&=~0x08;
        /* incompleto
	  if ((pic->ram[P18_WREG] & 0x80)!=(ctemp&0x80))  
	    *status|=0x08;
	  else   
	    *status&=~0x08;
        */
 
          pic->ram[P18_WREG]=ctemp;
	
	  if ((0xFF00&temp) != 0) 
	    *status&=~0x01;
	  else   
	    *status|=0x01;
	
	  if (pic->ram[P18_WREG] == 0) 
	    *status|=0x04;
	  else   
	    *status&=~0x04;
          break;
	  if (pic->ram[P18_WREG] & 0x80) 
	     *status|=0x10;
	  else   
	     *status&=~0x10;
        case 0x0900:
//IORLW    k    	Inclusive OR literalw/ WREG  1     	0000 1001 kkkk kkkk Z, N
          if(print)printf("IORLW %#06X\n",opc & 0x00FF);
	  pic->ram[P18_WREG] |= (opc & 0x00FF);
          pic->lram=P18_WREG;
	  if (pic->ram[P18_WREG] == 0) 
	    *status|=0x04;
	  else   
	    *status&=~0x04;
	  if (pic->ram[P18_WREG] & 0x80) 
	    *status|=0x10;
	  else   
	    *status&=~0x10;
          break;
        case 0x0A00:
//XORLW    k    	Exclusive OR literal w\WREG  1     	0000 1010 kkkk kkkk Z, N
          if(print)printf("XORLW %#06X\n",opc & 0x00FF);
	  pic->ram[P18_WREG] ^= (opc & 0x00FF);
          pic->lram=P18_WREG;
	  if (pic->ram[P18_WREG] == 0) 
	    *status|=0x04;
	  else   
	    *status&=~0x04;
	  if (pic->ram[P18_WREG] & 0x80) 
	    *status|=0x10;
	  else   
	    *status&=~0x10;
          break;
        case 0x0B00:
//ANDLW    k    	AND literal with WREG        1     	0000 1011 kkkk kkkk Z, N
          if(print)printf("ANDLW %#06X\n",opc & 0x00FF);
	  pic->ram[P18_WREG] &= (opc & 0x00FF);
          pic->lram=P18_WREG;
	  if (pic->ram[P18_WREG] == 0) 
	    *status|=0x04;
	  else   
	    *status&=~0x04;
	  if (pic->ram[P18_WREG] & 0x80) 
	    *status|=0x10;
	  else   
	    *status&=~0x10;
          break;
        case 0x0C00:
//RETLW    k    	Return with literal in WREG  2     	0000 1100 kkkk kkkk None
          if(print)printf("RETLW %#06X\n",opc & 0x00FF);  
          if((pic->ram[P18_STKPTR] & 0x1F) > 0 )
          {
            pic->ram[P18_STKPTR]=(pic->ram[P18_STKPTR] &0xC0) | ((pic->ram[P18_STKPTR] &0x1F)-1);    
            pic->jpc=pic->stack[pic->ram[P18_STKPTR] & 0x1F];    
          }
          else
          {
            pic->ram[P18_STKPTR]|=0x40; //set STKUNF  
            pic->jpc=0;
          }
          pic->lram=P18_STKPTR;
	  pic->s2=1;
	  pic->ram[P18_WREG]= (opc & 0x00FF);
          break;
        case 0x0D00:
//MULLW    k    	Multiply literal with WREG   1     	0000 1101 kkkk kkkk None
          if(print)printf("MULLW %#06X\n",opc & 0x00FF);
	  temp= pic->ram[P18_WREG]*(opc & 0x00FF);
          pic->ram[P18_PRODH]=(temp&0xFF00)>>8;
          pic->ram[P18_PRODL]=temp&0x00FF;
          pic->lram=P18_PRODL;
        case 0x0E00:
//MOVLW    k    	Move literal to WREG         1     	0000 1110 kkkk kkkk None
          if(print)printf("MOVLW %#06X\n",opc & 0x00FF);
          pic->lram=P18_WREG;
          pic->ram[P18_WREG]= (opc & 0x00FF);
          break;
        case 0x0F00:
//ADDLW    k    	Add literal and WREG         1     	0000 1111 kkkk kkkk C, DC, Z, OV, N
          if(print)printf("ADDLW %#06X\n",opc & 0x00FF);
	
	  if((0xF0&((0x0F&pic->ram[P18_WREG])+(opc & 0x000F))) !=0)
	    *status|=0x02;
	  else   
	    *status&=~0x02;
          pic->lram=P18_WREG; 
	  temp=pic->ram[P18_WREG]+(opc & 0x00FF);
	  ctemp=(unsigned char)(0x00FF &temp);
	  

	  if ((pic->ram[P18_WREG] & 0x80)!=(ctemp&0x80))  
	    *status|=0x08;
	  else   
	    *status&=~0x08;
          
          pic->ram[P18_WREG]= ctemp;
	
	  if ((0xFF00&temp) != 0) 
	    *status|=0x01;
	  else   
	    *status&=~0x01;
	
	  if (pic->ram[P18_WREG] == 0) 
	    *status|=0x04;
	  else   
	    *status&=~0x04;
	  if (pic->ram[P18_WREG] & 0x80) 
	     *status|=0x10;
	  else   
	     *status&=~0x10;
	  break;
        default:
          //printf("unknown opcode!\n");
          break; 
      }
      break; 
    case 0x1000:
      switch(opc & 0x0C00)
      {
	case 0x0000:
//IORWF  f, d, a 	Inclusive OR WREG with f     1          0001 00da ffff ffff Z, N            1, 2
          if(print)printf("IORWF %#04X,%d,%d\n",opc & 0x00FF,(opc & 0x0200)>>9,(opc & 0x0100)>>8);
          fraddr();
          pic->rram=raddr;
          if(opc & 0x0200)
	  {
	    pic->ram[raddr]= pic->ram[P18_WREG] | pic->ram[raddr];
            pic->lram=raddr;
	    if (pic->ram[raddr] == 0) 
	       *status|=0x04;
	    else   
	       *status&=~0x04;
	    if (pic->ram[raddr] & 0x80) 
	       *status|=0x10;
	    else   
	       *status&=~0x10;
	  } 
          else 
	  {
	    pic->ram[P18_WREG]= pic->ram[P18_WREG] | pic->ram[raddr];
            pic->lram=P18_WREG;
	    if (pic->ram[P18_WREG] == 0) 
	       *status|=0x04;
	    else   
	       *status&=~0x04;
	    if (pic->ram[P18_WREG] & 0x80) 
	       *status|=0x10;
	    else   
	       *status&=~0x10;
          }
          break;     
	case 0x0400:
//ANDWF  f, d, a 	AND WREG with f              1          0001 01da ffff ffff Z, N            1,2
          if(print)printf("ANDWF %#04X,%d,%d\n",opc & 0x00FF,(opc & 0x0200)>>9,(opc & 0x0100)>>8);
          fraddr();
          pic->rram=raddr;
          if(opc & 0x0200)
	  {
	    pic->ram[raddr]= pic->ram[P18_WREG] & pic->ram[raddr];
            pic->lram=raddr;
	    if (pic->ram[raddr] == 0) 
	       *status|=0x04;
	    else   
	       *status&=~0x04;
	    if (pic->ram[raddr] & 0x80) 
	       *status|=0x10;
	    else   
	       *status&=~0x10;
	  } 
          else 
	  {
	    pic->ram[P18_WREG]= pic->ram[P18_WREG] & pic->ram[raddr];
            pic->lram=P18_WREG;
	    if (pic->ram[P18_WREG] == 0) 
	       *status|=0x04;
	    else   
	       *status&=~0x04;
	    if (pic->ram[P18_WREG] & 0x80) 
	       *status|=0x10;
	    else   
	       *status&=~0x10;
          }
          break;     
	case 0x0800:
//XORWF  f, d, a 	Exclusive OR WREG with f     1          0001 10da ffff ffff Z, N
          if(print)printf("XORWF %#04X,%d,%d\n",opc & 0x00FF,(opc & 0x0200)>>9,(opc & 0x0100)>>8);
          fraddr();
          pic->rram=raddr;
          if(opc & 0x0200)
	  {
	    pic->ram[raddr]= pic->ram[P18_WREG] ^ pic->ram[raddr];
            pic->lram=raddr;
	    if (pic->ram[raddr] == 0) 
	       *status|=0x04;
	    else   
	       *status&=~0x04;
	    if (pic->ram[raddr] & 0x80) 
	       *status|=0x10;
	    else   
	       *status&=~0x10;
	  } 
          else 
	  {
	    pic->ram[P18_WREG]= pic->ram[P18_WREG] ^ pic->ram[raddr];
            pic->lram=P18_WREG;
	    if (pic->ram[P18_WREG] == 0) 
	       *status|=0x04;
	    else   
	       *status&=~0x04;
	    if (pic->ram[P18_WREG] & 0x80) 
	       *status|=0x10;
	    else   
	       *status&=~0x10;
          }
          break;     
	case 0x0C00:
//COMF   f, d, a 	Complement f                 1          0001 11da ffff ffff Z, N            1, 2
          if(print)printf("COMF %#06X,%d,%d\n",opc & 0x00FF,(opc & 0x0200)>>9,(opc & 0x0100)>>8);
	  fraddr();
          pic->rram=raddr;
          if(opc & 0x0200 )
	  {
	    pic->ram[raddr]=~pic->ram[raddr];
            pic->lram=raddr;
	    if (pic->ram[raddr] == 0) 
	       *status|=0x04;
	    else   
	       *status&=~0x04;
	    if (pic->ram[raddr] & 0x80) 
	       *status|=0x10;
	    else   
	       *status&=~0x10;
	  }
          else     
	  {
	    pic->ram[P18_WREG]=~pic->ram[raddr];
            pic->lram=P18_WREG;
	    if (pic->ram[P18_WREG] == 0) 
	       *status|=0x04;
	    else   
	       *status&=~0x04;
	    if (pic->ram[P18_WREG] & 0x80) 
	       *status|=0x10;
	    else   
	       *status&=~0x10;
          }
          break;
        default:
          //printf("unknown opcode!\n");
          break; 
      }
      break; 
    case 0x2000:
      switch(opc & 0x0C00)
      {
	case 0x0000:
//ADDWFC f, d, a 	Add WREG and Carry bit to f  1          0010 00da ffff ffff C, DC, Z, OV, N 1, 2
          if(print)printf("ADDWFC %#06X,%d,%d\n",opc & 0x00FF,(opc & 0x0200)>>9, (opc & 0x0100)>>8);
          fraddr(); 	
	  if((0xF0&((0x0F&(pic->ram[P18_WREG]+pic->ram[raddr]))+(pic->ram[P18_STATUS]&0x01))) !=0)
	    *status|=0x02; //DC=1
	  else   
	    *status&=~0x02; //DC=0

	  temp=pic->ram[P18_WREG]+pic->ram[raddr]+(pic->ram[P18_STATUS]&0x01);
          
          pic->rram=raddr;
	
	  if ((0xFF00&temp)) 
	    *status|=0x01; //C=1
	  else    
	    *status&=~0x01;//C=0

	  ctemp=(unsigned char)(0x00FF &temp);
          if(opc & 0x0200)
	  {
	    if (((pic->ram[raddr]+pic->ram[P18_WREG]) & 0x80)!=(ctemp&0x80))  
	       *status|=0x08;//OV=1
	    else   
	       *status&=~0x08;//OV=0
	    pic->ram[raddr]=ctemp;
            pic->lram=raddr;
	    if (pic->ram[raddr] == 0) 
	       *status|=0x04; //Z=1
	    else   
	       *status&=~0x04;//Z=0
	    if (pic->ram[raddr] & 0x80) 
	       *status|=0x10; //N=1
	    else   
	       *status&=~0x10;//N=0
	  }
          else     
	  {
	    if (((pic->ram[raddr]+pic->ram[P18_WREG]) & 0x80)!=(ctemp&0x80))  
	       *status|=0x08;
	    else   
	       *status&=~0x08;
	    pic->ram[P18_WREG] = ctemp;
            pic->lram=P18_WREG;
	    if (pic->ram[P18_WREG] == 0) 
	       *status|=0x04;
	    else   
	       *status&=~0x04;
	    if (pic->ram[P18_WREG] & 0x80) 
	       *status|=0x10;
	    else   
	       *status&=~0x10;
          }
	  break;
        case 0x0400:
//ADDWF  f, d, a 	Add WREG and f               1          0010 01da ffff ffff C, DC, Z, OV, N 1, 2
          if(print)printf("ADDWF %#06X,%d,%d\n",opc & 0x00FF,(opc & 0x0200)>>9, (opc & 0x0100)>>8);
          fraddr(); 	
	  if((0xF0&((0x0F&pic->ram[P18_WREG])+(0x0F&pic->ram[raddr]))) !=0)
	    *status|=0x02;
	  else   
	    *status&=~0x02;

	  temp=pic->ram[P18_WREG]+pic->ram[raddr];
            
          pic->rram=raddr;
	
	  if ((0xFF00&temp) != 0) 
	    *status|=0x01;
	  else   
	    *status&=~0x01;

	  ctemp=(unsigned char)(0x00FF &temp);

          if(opc & 0x0200)
	  {
	    if ((pic->ram[raddr] & 0x80)!=(ctemp&0x80))  
	       *status|=0x08;
	    else   
	       *status&=~0x08;
	    pic->ram[raddr]=ctemp;
            pic->lram=raddr;
	    if (pic->ram[raddr] == 0) 
	       *status|=0x04;
	    else   
	       *status&=~0x04;
	    if (pic->ram[raddr] & 0x80) 
	       *status|=0x10;
	    else   
	       *status&=~0x10;
	  }
          else     
	  {
	    if ((pic->ram[P18_WREG] & 0x80)!=(ctemp&0x80))  
	       *status|=0x08;
	    else   
	       *status&=~0x08;
	    pic->ram[P18_WREG] = ctemp;
            pic->lram=P18_WREG;
	    if (pic->ram[P18_WREG] == 0) 
	       *status|=0x04;
	    else   
	       *status&=~0x04;
	    if (pic->ram[P18_WREG] & 0x80) 
	       *status|=0x10;
	    else   
	       *status&=~0x10;
          }
	  break;
        case 0x0800:
//INCF   f, d, a 	Increment f                  1          0010 10da ffff ffff C, DC, Z, OV, N 1, 2, 3, 4
          if(print)printf("INCF %#06X,%d,%d\n",opc & 0x00FF,(opc & 0x0200)>>9,(opc & 0x0100)>>8);
	  fraddr();	
	  if((0xF0&((0x0F&(pic->ram[raddr]))+1)) !=0)
	    *status|=0x02;
	  else   
	    *status&=~0x02;
	  pic->rram=raddr;
          temp=pic->ram[raddr]+1;
	
	  if ((0xFF00&temp)) 
	    *status|=0x01;
	  else   
	    *status&=~0x01;
	  
          ctemp=(unsigned char)(0x00FF &temp);

          if(opc & 0x0200) //dest FILE
	  {
	    if ((pic->ram[raddr] & 0x80)!=(ctemp&0x80))  
	       *status|=0x08;
	    else   
	       *status&=~0x08;
            pic->lram=raddr;
	    pic->ram[raddr]=ctemp;
        
	    if (pic->ram[raddr] == 0) 
	       *status|=0x04;
	    else   
	       *status&=~0x04;
	    if (pic->ram[raddr] & 0x80) 
	       *status|=0x10;
	    else   
	       *status&=~0x10;
	  } 
          else  //dest W     
	  {
	    if ((pic->ram[P18_WREG] & 0x80)!=(ctemp&0x80))  
	       *status|=0x08;
	    else   
	       *status&=~0x08;
            pic->lram=P18_WREG;
	    pic->ram[P18_WREG]=ctemp;
	    if (pic->ram[P18_WREG] == 0) 
	       *status|=0x04;
	    else   
	       *status&=~0x04;
	    if (pic->ram[P18_WREG] & 0x80) 
	       *status|=0x10;
	    else   
	       *status&=~0x10;
          }
	break;
        case 0x0C00:
//DECFSZ f, d, a 	Decrement f, Skip if 0       1 (2 or 3) 0010 11da ffff ffff None            1, 2, 3, 4
          if(print)printf("DECFSZ %#06X,%d,%d\n",opc & 0x00FF,(opc & 0x0200)>>9,(opc & 0x0100)>>8);
          fraddr();
          pic->rram=raddr; 
          if(opc & 0x0200 )
	  {
	    pic->ram[raddr]--;
            pic->lram=raddr;
	    if (pic->ram[raddr] == 0) 
	    {
	      pic->jpc=pic->pc+2;
	      pic->s2=1;
	    };
	  } 
          else     
	  {
	    pic->ram[P18_WREG]=pic->ram[raddr]-1;
            pic->lram=P18_WREG;
	    if (pic->ram[P18_WREG] == 0)
	    {
	      pic->jpc=pic->pc+2;
	      pic->s2=1;
	    };
          }
          break;
        default:
          //printf("unknown opcode!\n");
          break; 
      }
      break; 
    case 0x3000:
      switch(opc & 0x0C00)
      {
        case 0x0000:
//RRCF   f, d, a 	Rotate Right f through Carry 1          0011 00da ffff ffff C, Z, N
          if(print)printf("RRCF %#06X,%d,%d\n",opc & 0x00FF,(opc & 0x0200)>>9,(opc & 0x0100)>>8);
          fraddr();
           pic->rram=raddr;
	  temp=(pic->ram[raddr]);
	  if((*status&0x01) ==0x01)temp|=0x0100;
	  if((temp&0x0001) ==0x01)
	    *status|=0x01;
	  else  
	    *status&=~0x01;
	  temp=temp>>1;

	  if (temp & 0x0080) 
	     *status|=0x10;
	  else   
	     *status&=~0x10;
	  if (temp & 0x00FF) 
	     *status&=~0x04;
	  else   
	     *status|=0x04;

          if(opc & 0x0200 )
	  {
	    pic->ram[raddr]=0x00FF&temp;
            pic->lram=raddr;
	  }
          else     
	  {
	    pic->ram[P18_WREG]=0x00FF&temp;
            pic->lram=P18_WREG;
          }
	  break;
	case 0x0400:
//RLCF   f, d, a 	Rotate Left f through Carry  1          0011 01da ffff ffff C, Z, N
          if(print)printf("RLCF %#06X,%d,%d\n",opc & 0x00FF,(opc & 0x0200)>>9,(opc & 0x0100)>>8);
	  fraddr();
          pic->rram=raddr;
	  temp=(pic->ram[raddr])<<1;
	  if((*status&0x01) ==0x01)temp|=0x0001;
	  if((temp&0x0100) ==0x0100)
	    *status|=0x01;
	  else  
	    *status&=~0x01;
	  if (temp & 0x0080) 
	     *status|=0x10;
	  else   
	     *status&=~0x10;
	  if (temp & 0x00FF) 
	     *status&=~0x04;
	  else   
	     *status|=0x04;
          if(opc & 0x0200)
	  {
	    pic->ram[raddr]= 0x00FF & temp;
            pic->lram=raddr;
	  }
          else
	  {
	    pic->ram[P18_WREG]=0x00FF & temp;
            pic->lram=P18_WREG;
          }
          break;     
        case 0x0800:
//SWAPF  f, d, a 	Swap nibbles in f            1          0011 10da ffff ffff None            4
          if(print)printf("SWAPF %#06X,%d,%d\n",opc & 0x00FF,(opc & 0x0200)>>9,(opc & 0x0100)>>8);
	  fraddr();
          pic->rram=raddr;
          if(opc & 0x0200)
	  {
	    pic->ram[raddr]=
	           ((pic->ram[raddr]&0x0F)<<4)|
	           ((pic->ram[raddr]&0xF0)>>4);
            pic->lram=raddr;
	  }
          else   
	  {
	    pic->ram[P18_WREG]=((pic->ram[raddr]&0x0F)<<4)|
	           ((pic->ram[raddr]&0xF0)>>4);
            pic->lram=P18_WREG; 
          }
          break;  
        case 0x0C00:
//INCFSZ f, d, a 	Increment f, Skip if 0       1 (2 or 3) 0011 11da ffff ffff None            4
          if(print)printf("INCFSZ %#06X,%d,%d\n",opc & 0x00FF,(opc & 0x0200)>>9,(opc & 0x0100)>>8);
          fraddr(); 
          pic->rram=raddr;
	  if(opc & 0x0200)
	  {
	    pic->ram[raddr]++;
            pic->lram=raddr;
	    if (pic->ram[raddr] == 0) 
	    {
	      pic->jpc=pic->pc+2;
	      pic->s2=1;
	    };
	  } 
          else     
	  {
	    pic->ram[P18_WREG]=pic->ram[raddr]+1;
            pic->lram=P18_WREG;
	    if (pic->ram[P18_WREG] == 0)
	    {
	      pic->jpc=pic->pc+2;
	      pic->s2=1;
	    };
          }
	  break;
        default:
          //printf("unknown opcode!\n");
          break; 
      }
      break; 
    case 0x4000:
      switch(opc & 0x0C00)
      {
	case 0x0000:
//RRNCF  f, d, a	Rotate Right f (No Carry)    1          0100 00da ffff ffff Z, N
          if(print)printf("RRNCF %#06X,%d,%d\n",opc & 0x00FF,(opc & 0x0200)>>9,(opc & 0x0100)>>8);
          fraddr();
          pic->rram=raddr;
	  temp=(pic->ram[raddr]);
	  if((pic->ram[raddr]&0x01) ==0x01)temp|=0x0100;
          
          temp=temp>>1;
	  
          if (temp & 0x00FF) 
	    *status&=~0x04;
	  else   
	    *status|=0x04;

	  if (temp & 0x0080) 
	     *status|=0x10;
	  else   
	     *status&=~0x10;

          if(opc & 0x0200 )
	  {
	    pic->ram[raddr]=0x00FF&temp;
            pic->lram=raddr;
	  }
          else     
	  {
	    pic->ram[P18_WREG]=0x00FF&temp;
            pic->lram=P18_WREG;
          }
	  break;
	case 0x0400:
//RLNCF  f, d, a 	Rotate Left f (No Carry)     1          0100 01da ffff ffff Z, N            1, 2
          if(print)printf("RLNCF %#06X,%d,%d\n",opc & 0x00FF,(opc & 0x0200)>>9,(opc & 0x0100)>>8);
	  fraddr();
          pic->rram=raddr;
	  temp=(pic->ram[raddr])<<1;
	  if((pic->ram[raddr]&0x80) ==0x80)temp|=0x0001;
	    
          if (temp & 0x00FF) 
	    *status&=~0x04;
	  else   
	    *status|=0x04;
	  if (temp & 0x0080) 
	     *status|=0x10;
	  else   
	     *status&=~0x10;
          
          if(opc & 0x0200)
	  {
	    pic->ram[raddr]= 0x00FF & temp;
            pic->lram=raddr;
	  }
          else
	  {
	    pic->ram[P18_WREG]=0x00FF & temp;
            pic->lram=P18_WREG;
          }
	  break;
	case 0x0800:
//INFSNZ f, d, a 	Increment f, Skip if Not 0   1 (2 or 3) 0100 10da ffff ffff None            1, 2
          if(print)printf("INFSNZ %#06X,%d,%d\n",opc & 0x00FF,(opc & 0x0200)>>9,(opc & 0x0100)>>8);
          fraddr(); 
          pic->rram=raddr; 
	  if(opc & 0x0200)
	  {
	    pic->ram[raddr]++;
            pic->lram=raddr;
	    if (pic->ram[raddr] != 0) 
	    {
	      pic->jpc=pic->pc+2;
	      pic->s2=1;
	    };
	  } 
          else     
	  {
	    pic->ram[P18_WREG]=pic->ram[raddr]+1;
	    if (pic->ram[P18_WREG] != 0)
	    {
	      pic->jpc=pic->pc+2;
	      pic->s2=1;
	    };
          }
	  break;
	case 0x0C00:
//DCFSNZ f, d, a 	Decrement f, Skip if Not 0   1 (2 or 3) 0100 11da ffff ffff None            1, 2
          if(print)printf("DCFSNZ %#06X,%d,%d\n",opc & 0x00FF,(opc & 0x0200)>>9,(opc & 0x0100)>>8);
          fraddr();
          pic->rram=raddr;
          if(opc & 0x0200 )
	  {
	    pic->ram[raddr]--;
            pic->lram=raddr;
	    if (pic->ram[raddr] != 0) 
	    {
	      pic->jpc=pic->pc+2;
	      pic->s2=1;
	    };
	  } 
          else     
	  {
	    pic->ram[P18_WREG]=pic->ram[raddr]-1;
	    if (pic->ram[P18_WREG] != 0)
	    {
	      pic->jpc=pic->pc+2;
	      pic->s2=1;
	    };
          }
          break;
        default:
          //printf("unknown opcode!\n");
          break; 
      }
      break; 
    case 0x5000:
      switch(opc & 0x0C00)
      {
	case 0x0000:
//MOVF   f, d, a 	Move f                       1          0101 00da ffff ffff Z, N            1
          if(print)printf("MOVF %#06X,%d,%d\n",opc & 0x00FF,(opc & 0x0200)>>9,(opc & 0x0100)>>8);
	  fraddr();
          if(opc & 0x0200)
	  {
	    if (pic->ram[raddr] == 0) 
	       *status|=0x04;
	    else   
	       *status&=~0x04;
	    if (pic->ram[raddr] & 0x80) 
	       *status|=0x10;
	    else   
	       *status&=~0x10;
            pic->rram=raddr;
            pic->lram=raddr;
	  }
          else     
	  {
	    pic->ram[P18_WREG]=pic->ram[raddr];
	    if (pic->ram[P18_WREG] == 0) 
	       *status|=0x04;
	    else   
	       *status&=~0x04;
	    if (pic->ram[P18_WREG] & 0x80) 
	       *status|=0x10;
	    else   
	       *status&=~0x10;
            pic->rram=raddr;
            pic->lram=P18_WREG;
          }
          break;
	case 0x0400:
//SUBFWB f, d, a 	Subtract f from WREG with b. 1          0101 01da ffff ffff C, DC, Z, OV, N 1, 2
          if(print)printf("SUBFWB %#06X,%d,%d\n",opc & 0x00FF,(opc & 0x0200)>>9, (opc & 0x0100)>>8);
	  fraddr();	
	  if((0xF0&((0x0F&(~pic->ram[raddr]))+(!(pic->ram[P18_STATUS]&0x01))+1+(0x0F&pic->ram[P18_WREG]))) !=0) 
	    *status|=0x02;
	  else   
	    *status&=~0x02;

	  temp=(~(pic->ram[raddr]+(!(pic->ram[P18_STATUS]&0x01)))+1)+pic->ram[P18_WREG];
	
	  if ((0xFF00&temp) != 0) 
	    *status&=~0x01;
	  else   
	    *status|=0x01;

          pic->rram=raddr;

	  ctemp=(unsigned char)(0x00FF &temp);

          if(opc & 0x0200 )
	  {
	   *status&=~0x08;
        /* incompleto
	    if ((pic->ram[raddr] & 0x80)!=(ctemp&0x80))  
	       *status|=0x08;
	    else   
	       *status&=~0x08;
         */
	    pic->ram[raddr]=ctemp;
            pic->lram=raddr;
	    if (pic->ram[raddr ] == 0) 
	       *status|=0x04;
	    else   
	       *status&=~0x04;
	    if (pic->ram[raddr] & 0x80) 
	       *status|=0x10;
	    else   
	       *status&=~0x10;
	  }
          else      
	  {
	   *status&=~0x08;
        /* incompleto
	    if ((pic->ram[P18_WREG] & 0x80)!=(ctemp&0x80))  
	       *status|=0x08;
	    else   
	       *status&=~0x08;
         */
	    pic->ram[P18_WREG] = ctemp;
            pic->lram=P18_WREG;
	    if (pic->ram[P18_WREG] == 0) 
	       *status|=0x04;
	    else   
	       *status&=~0x04;
	    if (pic->ram[P18_WREG] & 0x80) 
	       *status|=0x10;
	    else   
	       *status&=~0x10;
          }
          break;
	case 0x0800: 
//SUBWFB f, d, a 	Subtract WREG from f with b. 1          0101 10da ffff ffff C, DC, Z, OV, N 1, 2
          if(print)printf("SUBWFB %#06X,%d,%d\n",opc & 0x00FF,(opc & 0x0200)>>9, (opc & 0x0100)>>8);
	  fraddr();	
	  if((0xF0&((0x0F&(~pic->ram[P18_WREG]))+(!(pic->ram[P18_STATUS]&0x01))+1+(0x0F&pic->ram[raddr]))) !=0) 
	    *status|=0x02;
	  else   
	    *status&=~0x02;

	  temp=(~(pic->ram[P18_WREG]+(!(pic->ram[P18_STATUS]&0x01)))+1)+pic->ram[raddr];
	
	  if ((0xFF00&temp) != 0) 
	    *status&=~0x01;
	  else   
	    *status|=0x01;
          
          pic->rram=raddr;

	  ctemp=(unsigned char)(0x00FF &temp);

          if(opc & 0x0200 )
	  {
	   *status&=~0x08;
        //FIXME  incompleto
        /*
	    if ((pic->ram[raddr] & 0x80)!=(ctemp&0x80))  
	       *status|=0x08;
	    else   
	       *status&=~0x08;
        */
	    pic->ram[raddr]=ctemp;
            pic->lram=raddr;
	    if (pic->ram[raddr ] == 0) 
	       *status|=0x04;
	    else   
	       *status&=~0x04;
	    if (pic->ram[raddr] & 0x80) 
	       *status|=0x10;
	    else   
	       *status&=~0x10;
	  }
          else      
	  {
	   *status&=~0x08;
        //FIXME  incompleto
        /* 
	    if ((pic->ram[P18_WREG] & 0x80)!=(ctemp&0x80))  
	       *status|=0x08;
	    else   
	       *status&=~0x08;
         */
	    pic->ram[P18_WREG] = ctemp;
            pic->lram=P18_WREG;
	    if (pic->ram[P18_WREG] == 0) 
	       *status|=0x04;
	    else   
	       *status&=~0x04;
	    if (pic->ram[P18_WREG] & 0x80) 
	       *status|=0x10;
	    else   
	       *status&=~0x10;
          }
          break;
	case 0x0C00:
//SUBWF  f, d, a 	Subtract WREG from f         1          0101 11da ffff ffff C, DC, Z, OV, N
          if(print)printf("SUBWF %#06X,%d,%d\n",opc & 0x00FF,(opc & 0x0200)>>9, (opc & 0x0100)>>8);
	  fraddr();	
	  if((0xF0&((0x0F&(~pic->ram[P18_WREG]))+1+(0x0F&pic->ram[raddr]))) !=0)
	    *status|=0x02;
	  else   
	    *status&=~0x02;

	  temp=(~pic->ram[P18_WREG]+1)+pic->ram[raddr];
	
	  if ((0xFF00&temp) != 0) 
	    *status&=~0x01;
	  else   
	    *status|=0x01;
          
          pic->rram=raddr;

	  ctemp=(unsigned char)(0x00FF &temp);
          if(opc & 0x0200 )
	  {
	   *status&=~0x08;
        //FIXME  incompleto
        /* 
	    if ((pic->ram[raddr] & 0x80)!=(ctemp&0x80))  
	       *status|=0x08;
	    else   
	       *status&=~0x08;
        */
	    pic->ram[raddr]=ctemp;
            pic->lram=raddr;
	    if (pic->ram[raddr ] == 0) 
	       *status|=0x04;
	    else   
	       *status&=~0x04;
	    if (pic->ram[raddr] & 0x80) 
	       *status|=0x10;
	    else   
	       *status&=~0x10;
	  }
          else      
	  {
	   *status&=~0x08;
        //FIXME  incompleto
         /*
	    if ((pic->ram[P18_WREG] & 0x80)!=(ctemp&0x80))  
	       *status|=0x08;
	    else   
	       *status&=~0x08;
         */
	    pic->ram[P18_WREG] = ctemp;
            pic->lram=P18_WREG;
	    if (pic->ram[P18_WREG] == 0) 
	       *status|=0x04;
	    else   
	       *status&=~0x04;
	    if (pic->ram[P18_WREG] & 0x80) 
	       *status|=0x10;
	    else   
	       *status&=~0x10;
          }
          break;
        default:
          //printf("unknown opcode!\n");
          break; 
      }
      break; 
    case 0x6000:
      switch(opc & 0x0E00)
      {
	case 0x0000:
//CPFSLT f, a    	Compare f with WREG, skip <  1 (2 or 3) 0110 000a ffff ffff None            1, 2
          if(print)printf("CPFSLT %#06X,%d \n",opc & 0x00FF, (opc & 0x0100)>>8);
          fraddr();
          pic->rram=raddr;
	  if(pic->ram[raddr] < pic->ram[P18_WREG])
          {
	    pic->jpc=pic->pc+2;
            pic->s2=1;
          }
	  break;
	case 0x0200:
//CPFSEQ f, a    	Compare f with WREG, skip =  1 (2 or 3) 0110 001a ffff ffff None            4
          if(print)printf("CPFSEQ  %#06X,%d \n",opc & 0x00FF, (opc & 0x0100)>>8);
          fraddr();
          pic->rram=raddr;
	  if(pic->ram[raddr] == pic->ram[P18_WREG])
          {
	    pic->jpc=pic->pc+2;
            pic->s2=1;
          }
	  break;
	case 0x0400:
//CPFSGT f, a    	Compare f with WREG, skip >  1 (2 or 3) 0110 010a ffff ffff None            4
          if(print)printf("CPFSGT %#06X,%d \n",opc & 0x00FF, (opc & 0x0100)>>8);
          fraddr();
          pic->rram=raddr;
	  if(pic->ram[raddr] > pic->ram[P18_WREG])
          {
	    pic->jpc=pic->pc+2;
            pic->s2=1;
          }
	  break;
	case 0x0600:
//TSTFSZ f, a    	Test f, skip if 0            1 (2 or 3) 0110 011a ffff ffff None            1, 2
          if(print)printf("TSTFSZ %#06X,%d \n",opc & 0x00FF, (opc & 0x0100)>>8);
          fraddr();
          pic->rram=raddr;
	  if(!pic->ram[raddr])
          {
	    pic->jpc=pic->pc+2;
            pic->s2=1;
          }
	  break;
        case 0x0800:
//SETF   f, a    	Set f                        1          0110 100a ffff ffff None
          if(print)printf("SETF %#06X,%d \n",opc & 0x00FF, (opc & 0x0100)>>8);
          fraddr();
          pic->rram=raddr;
          pic->lram=raddr;
          pic->ram[raddr]=0xFF;
          break; 
        case 0x0A00:
//CLRF   f, a    	Clear f                      1          0110 101a ffff ffff Z               2
          if(print)printf("CLRF %#06X,%d \n",opc & 0x00FF, (opc & 0x0100)>>8);
          fraddr();
          pic->rram=raddr;
          pic->lram=raddr;
          pic->ram[raddr]=0;
	  *status|=0x04;
          break; 
        case 0x0C00:
//NEGF   f, a    	Negate f                     1          0110 110a ffff ffff C, DC, Z, OV, N 1, 2
          if(print)printf("NEGF %#06X,%d\n",opc & 0x00FF,(opc & 0x0100)>>8);
	  fraddr();
          pic->rram=raddr;
	  if((0xF0&((0x0F&(~pic->ram[raddr]))+1)) !=0)
	    *status|=0x02;
	  else   
	    *status&=~0x02;
	  
          temp=~pic->ram[raddr]+1;
	
	  if ((0xFF00&temp)) 
	    *status&=~0x01;
	  else   
	    *status|=0x01;
	  
          ctemp=(unsigned char)(0x00FF &temp);

	  if ((pic->ram[raddr] & 0x80) !=(ctemp&0x80))  
	     *status&=~0x08;
	  else   
	     *status|=0x08;
	  pic->ram[raddr]=ctemp;
          pic->lram=raddr;
	  if (pic->ram[raddr] == 0) 
	     *status|=0x04;
	  else   
	     *status&=~0x04;
	  if (pic->ram[raddr] & 0x80) 
	     *status|=0x10;
	  else   
	     *status&=~0x10;
          break;
        case 0x0E00:
//MOVWF  f, a    	Move WREG to f               1          0110 111a ffff ffff None
          if(print)printf("MOVWF %#06X,%d\n",opc & 0x00FF, (opc & 0x0100)>>8);
	  fraddr();
	  pic->ram[raddr]=pic->ram[P18_WREG];
          pic->lram=raddr;
          pic->rram=P18_WREG;
	  break;
        default:
          //printf("unknown opcode!\n");
          break; 
      }
      break; 
    case 0x7000:
//BTG    f, b, a 	Bit Toggle f                 1          0111 bbba ffff ffff None 1, 2
      if(print)printf("BTG %#06X,%d,%d\n",opc & 0x00FF,(opc & 0x0E00)>>9,(opc & 0x0100)>>8 );
      fraddr(); 
      pic->rram=raddr;
      pic->ram[raddr]^=(0x01<<((opc & 0x0E00)>>9));
      pic->lram=raddr;
      break; 
    case 0x8000:
//BSF    f, b, a 	Bit Set f                    1          1000 bbba ffff ffff None 1, 2
      if(print)printf("BSF %#06X,%d,%d\n",opc & 0x00FF,(opc & 0x0E00)>>9,(opc & 0x0100)>>8 );
      fraddr(); 
      pic->rram=raddr;
      pic->ram[raddr]|=(0x01<<((opc & 0x0E00)>>9));
      pic->lram=raddr;
      break; 
    case 0x9000:
//BCF    f, b, a 	Bit Clear f                  1          1001 bbba ffff ffff None 1, 2
      if(print)printf("BCF %#06X,%d,%d\n",opc & 0x00FF,(opc & 0x0E00)>>9,(opc & 0x0100)>>8 );
      fraddr(); 
      pic->rram=raddr;
      pic->ram[raddr]&=~(0x01<<((opc & 0x0E00)>>9));
      pic->lram=raddr;
      break; 
    case 0xA000:
//BTFSS  f, b, a 	Bit Test f, Skip if Set      1 (2 or 3) 1010 bbba ffff ffff None 3, 4
        if(print)printf("BTFSS %#06X,%d,%d\n",opc & 0x00FF,(opc & 0x0E00)>>9, (opc&0x0100)>>8);
        fraddr();
        pic->rram=raddr;
	if((pic->ram[raddr] & (0x01<<((opc & 0x0E00)>>9))) != 0)
	{
	  pic->jpc=pic->pc+2;
          pic->s2=1;
        }
      break; 
    case 0xB000:
//BTFSC  f, b, a 	Bit Test f, Skip if Clear    1 (2 or 3) 1011 bbba ffff ffff None 3, 4
        if(print)printf("BTFSC %#06X,%d,%d\n",opc & 0x00FF,(opc & 0x0E00)>>9, (opc&0x0100)>>8);
        fraddr();
        pic->rram=raddr;
	if((pic->ram[raddr] & (0x01<<((opc & 0x0E00)>>9))) == 0)
	{
	  pic->jpc=pic->pc+2;
          pic->s2=1;
        }
      break; 
    case 0xC000:
//MOVFF  fs, fd  	Move fs (source) to 1st word 2          1100 ffff  ffff ffff None
//                   	fd (destination) 2nd word               1111 ffff  ffff ffff
          if(print)printf("MOVFF %#06X,%#06X\n",opc & 0x0FFF, pic->prog[pic->pc>>1] & 0x0FFF );
          pic->ram[pic->prog[pic->pc>>1] & 0x0FFF] = pic->ram[opc & 0x0FFF];
	  pic->rram=opc & 0x0FFF;
          pic->lram=pic->prog[pic->pc>>1] & 0x0FFF;
      break; 
    case 0xD000:
      switch(opc & 0x0800)
      {
        case 0x0000: 
//BRA    n    		Branch Unconditionally       1 (2) 	1101 0nnn nnnn nnnn None
          jrange=(((short)((opc & 0x07FF)<<5))/16); 
          if(print)printf("BRA %#06X\n",(pic->pc+jrange)&((pic->ROMSIZE<<1)-1));
          pic->jpc=(pic->pc+jrange)&((pic->ROMSIZE<<1)-1);
	  pic->s2=1;
	  break;
        case 0x0800: 
//RCALL  n    		Relative Call                2     	1101 1nnn nnnn nnnn None
          jrange=(((short)((opc & 0x07FF)<<5))/16); 
          if(print)printf("RCALL %#06X\n",(pic->pc+jrange)&((pic->ROMSIZE<<1)-1));
          if((pic->ram[P18_STKPTR] & 0x1F) < 31 )
          {
	     pic->stack[pic->ram[P18_STKPTR]& 0x1F]=pic->pc;
             pic->ram[P18_STKPTR]=(pic->ram[P18_STKPTR] &0xC0) | ((pic->ram[P18_STKPTR] &0x1F)+1);    
             if((pic->ram[P18_STKPTR] & 0x1F)== 31)pic->ram[P18_STKPTR]|=0x80; //set STKFUL
          }
          pic->jpc=(pic->pc+jrange)&((pic->ROMSIZE<<1)-1) ;
          pic->lram=P18_STKPTR;
	  pic->s2=1;
	break;
	  break;
        default:
          //printf("unknown opcode!\n");
          break; 
      }
      break; 
    case 0xE000:
      switch(opc & 0x0F00)
      {
        case 0x0000:	
//BZ     n    		Branch if Zero               1 (2) 	1110 0000 nnnn nnnn None
          jrange=(((char)(opc & 0x00FF))*2); 
          if(print)printf("BZ  %#06X\n",(pic->pc+jrange)&((pic->ROMSIZE<<1)-1));
          if(pic->ram[P18_STATUS] & 0x04)
          {
            pic->jpc=(pic->pc+jrange)&((pic->ROMSIZE<<1)-1) ;
	    pic->s2=1;
          }
          break;
        case 0x0100:	
//BNZ    n    		Branch if Not Zero           2     	1110 0001 nnnn nnnn None
          jrange=(((char)(opc & 0x00FF))*2); 
          if(print)printf("BNZ %#06X\n",(pic->pc+jrange)&((pic->ROMSIZE<<1)-1));
          if(!(pic->ram[P18_STATUS] & 0x04))
          {
            pic->jpc=(pic->pc+jrange)&((pic->ROMSIZE<<1)-1) ;
	    pic->s2=1;
          }
          break;
        case 0x0200:	
//BC     n    		Branch if Carry              1 (2)      1110 0010 nnnn nnnn None
          jrange=(((char)(opc & 0x00FF))*2); 
          if(print)printf("BC  %#06X\n",(pic->pc+jrange)&((pic->ROMSIZE<<1)-1));
          if(pic->ram[P18_STATUS] & 0x01)
          {
            pic->jpc=(pic->pc+jrange)&((pic->ROMSIZE<<1)-1) ;
	    pic->s2=1;
          }
          break;
        case 0x0300:	
//BNC    n    		Branch if Not Carry          1 (2) 	1110 0011 nnnn nnnn None
          jrange=(((char)(opc & 0x00FF))*2); 
          if(print)printf("BNC %#06X\n",(pic->pc+jrange)&((pic->ROMSIZE<<1)-1));
          if(!(pic->ram[P18_STATUS] & 0x01))
          {
            pic->jpc=(pic->pc+jrange)&((pic->ROMSIZE<<1)-1) ;
	    pic->s2=1;
          }
          break;
        case 0x0400:	
//BOV    n    		Branch if Overflow           1 (2) 	1110 0100 nnnn nnnn None
          jrange=(((char)(opc & 0x00FF))*2); 
          if(print)printf("BOV  %#06X\n",(pic->pc+jrange)&((pic->ROMSIZE<<1)-1));
          if(pic->ram[P18_STATUS] & 0x08)
          {
            pic->jpc=(pic->pc+jrange)&((pic->ROMSIZE<<1)-1) ;
	    pic->s2=1;
          }
          break;
        case 0x0500:	
//BNOV   n    		Branch if Not Overflow       1 (2) 	1110 0101 nnnn nnnn None
          jrange=(((char)(opc & 0x00FF))*2); 
          if(print)printf("BNOV %#06X\n",(pic->pc+jrange)&((pic->ROMSIZE<<1)-1));
          if(!(pic->ram[P18_STATUS] & 0x08))
          {
            pic->jpc=(pic->pc+jrange)&((pic->ROMSIZE<<1)-1) ;
	    pic->s2=1;
          }
          break;
        case 0x0600:	
//BN     n    		Branch if Negative           1 (2)      1110 0110 nnnn nnnn None
          jrange=(((char)(opc & 0x00FF))*2); 
          if(print)printf("BN  %#06X\n",(pic->pc+jrange)&((pic->ROMSIZE<<1)-1));
          if(pic->ram[P18_STATUS] & 0x10)
          {
            pic->jpc=(pic->pc+jrange)&((pic->ROMSIZE<<1)-1) ;
	    pic->s2=1;
          }
          break;
        case 0x0700:	
//BNN    n    		Branch if Not Negative       1 (2) 	1110 0111 nnnn nnnn None
          jrange=(((char)(opc & 0x00FF))*2); 
          if(print)printf("BNN %#06X\n",(pic->pc+jrange)&((pic->ROMSIZE<<1)-1));
          if(!(pic->ram[P18_STATUS] & 0x10))
          {
            pic->jpc=(pic->pc+jrange)&((pic->ROMSIZE<<1)-1) ;
	    pic->s2=1;
          }
          break;
	case 0x0C00:
	case 0x0D00:
//CALL   n, s 		Call subroutine1st word      2     	1110 110s kkkk kkkk None
//            		2nd word                             	1111 kkkk kkkk kkkk
          if(print)printf("CALL %#012X,%d\n", (((pic->prog[pic->pc>>1] & 0x0FFF)<<8)| (opc & 0x00FF))<<1, (opc & 0x0100)>>8  );

	  if(opc & 0x0100)
          {
            pic->ram[P18_WS]=pic->ram[P18_WREG]; 	 
            pic->ram[P18_STATUSS]=pic->ram[P18_STATUS];
            pic->ram[P18_BSRS]=pic->ram[P18_BSR];
          }
          if((pic->ram[P18_STKPTR] & 0x1F) < 31 )
          {
	      pic->stack[pic->ram[P18_STKPTR]& 0x1F]=pic->pc+2;
              pic->ram[P18_STKPTR]=(pic->ram[P18_STKPTR] &0xC0) | ((pic->ram[P18_STKPTR] &0x1F)+1);    
             if((pic->ram[P18_STKPTR]& 0x1F) == 31)pic->ram[P18_STKPTR]|=0x80; //set STKFUL
          }
	  pic->jpc=(((pic->prog[pic->pc>>1] & 0x0FFF)<<8)| (opc & 0x00FF))<<1;
          pic->lram=P18_STKPTR;
	  pic->s2=1;
	break;
	case 0x0E00:
//LFSR     f, k 	Move literal (12-bit) 2nd w  2  	1110 1110 00ff kkkk None
//                   	to FSRx 1st word                   	1111 0000 kkkk kkkk
          if(print)printf("LFSR %d,%#08X\n",(opc & 0x0030)>>4 , ((opc & 0x000F)<<8)|(pic->prog[pic->pc>>1] & 0x00FF) );

          switch((opc & 0x0030)>>4 )
          {
            case 0:
              pic->ram[P18_FSR0H]=((opc & 0x000F));
              pic->ram[P18_FSR0L]=(pic->prog[pic->pc>>1] & 0x00FF);
              pic->lram=P18_FSR0L;
              break;
            case 1:
              pic->ram[P18_FSR1H]=((opc & 0x000F));
              pic->ram[P18_FSR1L]=(pic->prog[pic->pc>>1] & 0x00FF);
              pic->lram=P18_FSR1L;
              break;
            case 2:
              pic->ram[P18_FSR2H]=((opc & 0x000F));
              pic->ram[P18_FSR2L]=(pic->prog[pic->pc>>1] & 0x00FF);
              pic->lram=P18_FSR2L;
              break;
            default:
              printf("LFSR Error!\n");
              break;
          }
          break;
	case 0x0F00:
//GOTO   n    		Go to address1st word        2     	1110 1111 kkkk kkkk None
//            		2nd word                             	1111 kkkk kkkk kkkk
          if((pic->pc >=0x200028)&&(pic->pc < 0x200037))//DEBUG
          {
            if(print)printf("GOTO %#012X\n", (((pic->debugv[pic->pc-0x200027] & 0x0FFF)<<8)| (opc & 0x00FF))<<1  );
            pic->jpc=(((pic->debugv[pic->pc-0x200029] & 0x0FFF)<<8)| (opc & 0x00FF))<<1 ;

            //printf("debugv %i\n",pic->pc-0x200029); 
          }
          else
          {
            if(print)printf("GOTO %#012X\n", (((pic->prog[pic->pc>>1] & 0x0FFF)<<8)| (opc & 0x00FF))<<1  );
            pic->jpc=(((pic->prog[pic->pc>>1] & 0x0FFF)<<8)| (opc & 0x00FF))<<1 ;
          }
	  pic->s2=1;
	  break;
        default:
          //printf("unknown opcode!\n");
          break; 
      }
      break; 
    case 0xF000:
//NOP    --   		No Operation                 1     	1111 xxxx xxxx xxxx None      4
      if(print)printf("NOP\n");
      break;
    default:
      //printf("unknown opcode!\n");
      break; 
  }



  if(pic->lram != 0x8000) 
  {
  switch(pic->lram)
  {
    case P18_INDF0:
      pic->ram[afsr0]=pic->ram[P18_INDF0];
      pic->lram=afsr0;
      break; 
    case P18_POSTINC0:
      pic->ram[afsr0]=pic->ram[P18_POSTINC0];
      pic->lram=afsr0;
      pic->ram[P18_FSR0H]=((afsr0+1)&0xFF00)>>8;
      pic->ram[P18_FSR0L]=(afsr0+1)&0x00FF;
      break;
    case P18_POSTDEC0:
      pic->ram[afsr0]=pic->ram[P18_POSTDEC0];
      if(pic->lram == pic->rram)pic->rram=0x8000;
      pic->lram=afsr0;
      pic->ram[P18_FSR0H]=((afsr0-1)&0xFF00)>>8;
      pic->ram[P18_FSR0L]=(afsr0-1)&0x00FF;
      break;
    case P18_PREINC0:
      pic->ram[afsr0+1]=pic->ram[P18_PREINC0];
      if(pic->lram == pic->rram)pic->rram=0x8000;
      pic->lram=afsr0+1;
      pic->ram[P18_FSR0H]=((afsr0+1)&0xFF00)>>8;
      pic->ram[P18_FSR0L]=(afsr0+1)&0x00FF;
      break;
    case P18_PLUSW0:
      pic->ram[afsr0+((char)pic->ram[P18_WREG])]=pic->ram[P18_PLUSW0];
      pic->lram=afsr0+((char)pic->ram[P18_WREG]);
      break; 

    case P18_INDF1:
      pic->ram[afsr1]=pic->ram[P18_INDF1];
      pic->lram=afsr1;
      break; 
    case P18_POSTINC1:
      pic->ram[afsr1]=pic->ram[P18_POSTINC1];
      pic->lram=afsr1;
      pic->ram[P18_FSR1H]=((afsr1+1)&0xFF00)>>8;
      pic->ram[P18_FSR1L]=(afsr1+1)&0x00FF;
      break;
    case P18_POSTDEC1:
      pic->ram[afsr1]=pic->ram[P18_POSTDEC1];
      pic->lram=afsr1;
      pic->ram[P18_FSR1H]=((afsr1-1)&0xFF00)>>8;
      pic->ram[P18_FSR1L]=(afsr1-1)&0x00FF;
      break;
    case P18_PREINC1:
      pic->ram[afsr1+1]=pic->ram[P18_PREINC1];
      pic->lram=afsr1+1;
      pic->ram[P18_FSR1H]=((afsr1+1)&0xFF00)>>8;
      pic->ram[P18_FSR1L]=(afsr1+1)&0x00FF;
      break;
    case P18_PLUSW1:
      pic->ram[afsr1+((char)pic->ram[P18_WREG])]=pic->ram[P18_PLUSW1];
      pic->lram=afsr1+((char)pic->ram[P18_WREG]);
      break; 
    
     case P18_INDF2:
      pic->ram[afsr2]=pic->ram[P18_INDF2];
      pic->lram=afsr2;
      break; 
    case P18_POSTINC2:
      pic->ram[afsr2]=pic->ram[P18_POSTINC2];
      pic->lram=afsr2;
      pic->ram[P18_FSR2H]=((afsr2+1)&0xFF00)>>8;
      pic->ram[P18_FSR2L]=(afsr2+1)&0x00FF;
      break;
    case P18_POSTDEC2:
      pic->ram[afsr2]=pic->ram[P18_POSTDEC2];
      pic->lram=afsr2;
      pic->ram[P18_FSR2H]=((afsr2-1)&0xFF00)>>8;
      pic->ram[P18_FSR2L]=(afsr2-1)&0x00FF;
      break;
    case P18_PREINC2:
      pic->ram[afsr2+1]=pic->ram[P18_PREINC2];
      pic->lram=afsr2+1;
      pic->ram[P18_FSR2H]=((afsr2+1)&0xFF00)>>8;
      pic->ram[P18_FSR2L]=(afsr2+1)&0x00FF;
      break;
    case P18_PLUSW2:
      pic->ram[afsr2+((char)pic->ram[P18_WREG])]=pic->ram[P18_PLUSW2];
      pic->lram=afsr2+((char)pic->ram[P18_WREG]);
      break;
  }   
  //second pass with new lram    
  switch(pic->lram)
  {   
    case P18_STKPTR:
      if((pic->ram[P18_STKPTR] & 0x1F) >0)
      {
        pic->ram[P18_TOSL]=((pic->stack[(pic->ram[P18_STKPTR] & 0x1F)-1])&0x0000FF);  
        pic->ram[P18_TOSU]=((pic->stack[(pic->ram[P18_STKPTR] & 0x1F)-1])&0x1F0000)>>16; 
        pic->ram[P18_TOSH]=((pic->stack[(pic->ram[P18_STKPTR] & 0x1F)-1])&0x00FF00)>>8;   
      }
      else
      {
        pic->ram[P18_TOSL]=0;
        pic->ram[P18_TOSH]=0;
        pic->ram[P18_TOSU]=0;
      }        
      break;
    case P18_TOSL:
      if((pic->ram[P18_STKPTR] & 0x1F) > 0)  
        pic->stack[(pic->ram[P18_STKPTR] & 0x1F)-1]= ((pic->ram[P18_TOSU]&0x1F)<<16) |((pic->ram[P18_TOSH])<<8)|pic->ram[P18_TOSL];
      break;
      
    case P18_LATA:
      pic->ram[P18_PORTA]=pic->ram[P18_LATA];
      break;	
    case P18_LATB:
      pic->ram[P18_PORTB]=pic->ram[P18_LATB];
      break;	
    case P18_LATC:
      pic->ram[P18_PORTC]=pic->ram[P18_LATC];
      break;	
    case P18_LATD:
      pic->ram[P18_PORTD]=pic->ram[P18_LATD];
      break;	
    case P18_LATE:
      pic->ram[P18_PORTE]=pic->ram[P18_LATE];
      break;	
 
    case P18_PORTA:
      pic->ram[P18_LATA]=pic->ram[P18_PORTA];
      break;	
    case P18_PORTB:
      pic->ram[P18_LATB]=pic->ram[P18_PORTB];
      break;	
    case P18_PORTC:
      pic->ram[P18_LATC]=pic->ram[P18_PORTC];
      break;	
    case P18_PORTD:
      pic->ram[P18_LATD]=pic->ram[P18_PORTD];
      break;	
    case P18_PORTE:
      pic->ram[P18_LATE]=pic->ram[P18_PORTE];
      break;	
    
    case P18_PCL:
      pic->pc= ((pic->ram[P18_PCLATU]&0x1F)<<16) |((pic->ram[P18_PCLATH])<<8)|pic->ram[P18_PCL];
//	      printf("###############PCL write  (%#04X %#04X %#04X) %#08X\n",(pic->ram[P18_PCLATU]&0x1F)<<16,(pic->ram[P18_PCLATH])<<8,pic->ram[P18_PCL],pic->pc);
      break; 
  }
  }
  
  if(pic->rram != 0x8000)
  {
  switch(pic->rram)
  {
    case P18_INDF0:
      pic->rram=afsr0;  
      break;  
    case P18_POSTINC0:
      pic->ram[P18_FSR0H]=((afsr0+1)&0xFF00)>>8;
      pic->ram[P18_FSR0L]=(afsr0+1)&0x00FF;
      pic->rram=afsr0;
      break;
    case P18_POSTDEC0:
      pic->ram[P18_FSR0H]=((afsr0-1)&0xFF00)>>8;
      pic->ram[P18_FSR0L]=(afsr0-1)&0x00FF;
      pic->rram=afsr0;
      break;
    case P18_PREINC0:
      pic->ram[P18_FSR0H]=((afsr0+1)&0xFF00)>>8;
      pic->ram[P18_FSR0L]=(afsr0+1)&0x00FF;
      pic->rram=afsr0+1;
      break;
    case P18_PLUSW0:
      pic->rram=afsr0+((char)pic->ram[P18_WREG]);  
      break;  

    case P18_INDF1:
      pic->rram=afsr1;  
      break;   
    case P18_POSTINC1:
      pic->ram[P18_FSR1H]=((afsr1+1)&0xFF00)>>8;
      pic->ram[P18_FSR1L]=(afsr1+1)&0x00FF;
      pic->rram=afsr1;
      break;
    case P18_POSTDEC1:
      pic->ram[P18_FSR1H]=((afsr1-1)&0xFF00)>>8;
      pic->ram[P18_FSR1L]=(afsr1-1)&0x00FF;
      pic->rram=afsr1;
      break;
    case P18_PREINC1:
      pic->ram[P18_FSR1H]=((afsr1+1)&0xFF00)>>8;
      pic->ram[P18_FSR1L]=(afsr1+1)&0x00FF;
      pic->rram=afsr1+1;
      break;
    case P18_PLUSW1:
      pic->rram=afsr1+((char)pic->ram[P18_WREG]);  
      break;  
    
    case P18_INDF2:
      pic->rram=afsr2;  
      break;   
    case P18_POSTINC2:
      pic->ram[P18_FSR2H]=((afsr2+1)&0xFF00)>>8;
      pic->ram[P18_FSR2L]=(afsr2+1)&0x00FF;
      pic->rram=afsr2;
      break;
    case P18_POSTDEC2:
      pic->ram[P18_FSR2H]=((afsr2-1)&0xFF00)>>8;
      pic->ram[P18_FSR2L]=(afsr2-1)&0x00FF;
      pic->rram=afsr2;
      break;
    case P18_PREINC2:
      pic->ram[P18_FSR2H]=((afsr2+1)&0xFF00)>>8;
      pic->ram[P18_FSR2L]=(afsr2+1)&0x00FF;
      pic->rram=afsr2+1;
      break;
    case P18_PLUSW2:
      pic->rram=afsr2+((char)pic->ram[P18_WREG]);  
      break;  
  }
  
  //second pass with new rram
  switch(pic->rram)
  {    
    case P18_TOSL:
       if((pic->ram[P18_STKPTR] & 0x1F) >0) 
       {
         pic->ram[P18_TOSU]=((pic->stack[(pic->ram[P18_STKPTR] & 0x1F)-1])&0x1F0000)>>16; 
         pic->ram[P18_TOSH]=((pic->stack[(pic->ram[P18_STKPTR] & 0x1F)-1])&0x00FF00)>>8;      
       } 
     break;
     
     case P18_PCL:
  //    printf("###############PCL read\n");
      pic->ram[P18_PCLATU]=(pic->pc&0x1F0000)>>16;
      pic->ram[P18_PCLATH]=(pic->pc&0x00FF00)>>8;
     break;
  }
  }

    pic->w=pic->ram[P18_WREG];

  if((print)&&(pic->rram != 0x8000))printf("mem read  %#06X: %10s= %#06X\n",pic->rram,getFSRname_18(pic->rram),pic->ram[pic->rram]);
  if((print)&&(pic->lram != 0x8000))printf("mem write %#06X: %10s= %#06X\n",pic->lram,getFSRname_18(pic->lram),pic->ram[pic->lram]);
/*
  if((pic->ram[P18_PCL]) != (pc_ant&0x00FF))
  {
    pic->pc=((pic->ram[P18_PCLATH]&0x1F)<<8)|pic->ram[PCL];//conferir
  }
*/  

}


