/* ########################################################################

   PICsim - PIC simulator

   ########################################################################

   Copyright (c) : 2015-2016  Luis Claudio Gambôa Lopes

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


void ReadIndf(_pic * pic, unsigned short *afsr)
{
   int i;
   
   afsr[0]=(pic->ram[P16E_FSR0H] <<8)|pic->ram[P16E_FSR0L];
   afsr[1]=(pic->ram[P16E_FSR1H] <<8)|pic->ram[P16E_FSR1L];
  
  for( i=0;i<2;i++)
  {
    if(afsr[i] <= 0x0FFF) //0x0000 - 0x0FFF traditional data memory
    {
      pic->ram[P16E_INDF0+i]=pic->ram[afsr[i]]; 
    }
    else
    {
      if(afsr[i] >= 0x8000)// 0x8000 - 0xFFFF Program flash memory 
      {
        unsigned short addr= afsr[i]-0x8000;
        
        if(addr < pic->ROMSIZE)
        {
           pic->ram[P16E_INDF0+i]=pic->prog[addr] &0x00FF;   
        }
        else
           pic->ram[P16E_INDF0+i]=0;
      }
      else //0x2000 - 0x29AF linear data memory      
      {
        unsigned short addr= afsr[i]-0x2000;

        int bk=addr/80;
        int bkoff=addr%80;
        unsigned short laddr= (bk*0x80)+0x20+bkoff;

        pic->ram[P16E_INDF0+i]=pic->ram[laddr];

      }
    }
  }
      
  
  pic->ram[P16E_INDF1]=pic->ram[afsr[1]];
  
 
  
  //mirror on all banks
  int bk;  
  int offset=0x007F&P16E_INDF0;
  unsigned char temp0=pic->ram[P16E_INDF0];
  unsigned char temp1=pic->ram[P16E_INDF1];
    
  for(bk=0;bk<32;bk++)
  {
    pic->ram[(0x0080*bk)|(offset)]=temp0;
    pic->ram[(0x0080*bk)|(offset+1)]=temp1;
  } 
 

}

void
pic_decode_16E(_pic * pic,int print)
{
  unsigned short temp;
  unsigned short opc;
  unsigned short bank= (pic->ram[P16E_BSR] & 0x003F)<<7;
  unsigned char * status = &pic->ram[bank|(P16E_STATUS & 0x007F)];
  unsigned char * intcon = &pic->ram[bank|(P16E_INTCON & 0x007F)];
  unsigned short  afsr[2];
  short jrange;
  int afsrpos=0;

  if(pic->pc != 0x2004) 
    opc=pic->prog[pic->pc];
  else
    opc=pic->id[4];

  pic->lram=0x8000;
  pic->rram=0x8000;
  
  if(pic->sleep == 1)
  {
    if(print)printf("sleep WDT=%i wdt=%f ms=%i\n",((pic->config[0] & 0x04) == 0x04 ),pic->twdt,pic->wdt); 
    return;
  }
  
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
  
  //print (Address)
  if(print)
  {
    printf("pc=%#06X\t",pic->pc); 
    if(pic->pc != 0x2004) 
      printf("prog=%#06X\t",pic->prog[pic->pc]); 
    else
      printf("prog=%#06X\t",pic->id[4]); 
  }
  
  pic->pc++;
  if(pic->pc >= pic->ROMSIZE) pic->pc=0;


//pc
  temp = pic->pc&0x00FF;
  pic->ram[(0x0000)|(P16E_PCL & 0x007F)]=temp;
  pic->ram[(0x0080)|(P16E_PCL & 0x007F)]=temp;
  if(pic->processor != P16F84A)
  {
    pic->ram[(0x0100)|(P16E_PCL & 0x007F)]=temp;
    pic->ram[(0x0180)|(P16E_PCL & 0x007F)]=temp;
  }  
  //pc_ant = temp;

  ReadIndf(pic, afsr);
  
  
  switch(opc & 0x3000)
  {
    case 0x0000:
      switch(opc & 0x0F00)
      {
        case 0x0000:
          switch(opc & 0x0080)
          {
            case 0x0000:
              switch(opc & 0x007F)
              { 
                case 0x0000:
//NOP     --  	No Operation                 1     0000000 0000000  
                  if(print)printf("NOP\n");
		break;
                case 0x0001:
//RESET    -     Software device Reset              1    00 0000 0000 0001  
                  if(print)printf("RESET\n");                
		  pic_reset(pic,0);  
                break;
		case 0x0008:
///RETURN  --  	Return from Subroutine       2     0000000 0001000
                  if(print)printf("RETURN\n");
	          pic->jpc=pic->stack[0];
                  for(temp=0;temp<15;temp++)
	            pic->stack[temp]=pic->stack[temp+1];
		  pic->stack[15]=0;
	          pic->s2=1;
//		  if((pic->ram[ICKBUG] & 0x80)== 0x80)printf("Out DEBUG mode\n");
	          pic->debug=0;
                  pic->sstep=0;          
                  pic->dbg=0;          
//TODO	P16E DEBUG
                  //pic->ram[P16E_ICKBUG]&=~0x80;
                break;
		case 0x0009:
//RETFIE  --  	Return from interrupt        2     0000000 0001001                                                         
                  if(print)printf("RETFIE\n");
	          pic->jpc=pic->stack[0];
                  for(temp=0;temp<15;temp++)
	            pic->stack[temp]=pic->stack[temp+1];
		  pic->stack[15]=0;
	          pic->s2=1;
	          *intcon|=0x80;
                  pic->lram=P16E_INTCON;
                  //restore shadow
                  int bk;  
                  int offset;
                  pic->ram[P16E_STATUS]=pic->ram[P16E_STATUS_SHAD];  
                  offset=0x007F&P16E_STATUS;
                  temp=pic->ram[P16E_STATUS];
                  for(bk=0;bk<32;bk++)
                    pic->ram[(0x0080*bk)|offset]=temp;
    
                  pic->ram[P16E_WREG]=pic->ram[P16E_WREG_SHAD];  
                  offset=0x007F&P16E_WREG;
                  temp=pic->ram[P16E_WREG];
                  for(bk=0;bk<32;bk++)
                    pic->ram[(0x0080*bk)|offset]=temp;      
                  
                  pic->ram[P16E_BSR]= pic->ram[P16E_BSR_SHAD];       
                  offset=0x007F&P16E_BSR;
                  temp=pic->ram[P16E_BSR];
                  for(bk=0;bk<32;bk++)
                    pic->ram[(0x0080*bk)|offset]=temp;
                  
                  pic->ram[P16E_PCLATH]=pic->ram[P16E_PCLATH_SHAD]; 
                  offset=0x007F&P16E_PCLATH;
                  temp=pic->ram[P16E_PCLATH];
                  for(bk=0;bk<32;bk++)
                    pic->ram[(0x0080*bk)|offset]=temp;
                  
                  pic->ram[P16E_FSR0L]=pic->ram[P16E_FSR0L_SHAD]; 
                  offset=0x007F&P16E_FSR0L;
                  temp=pic->ram[P16E_FSR0L];
                  for(bk=0;bk<32;bk++)
                    pic->ram[(0x0080*bk)|offset]=temp;
                  
                  pic->ram[P16E_FSR0H]=pic->ram[P16E_FSR0H_SHAD];  
                  offset=0x007F&P16E_FSR0H;
                  temp=pic->ram[P16E_FSR0H];
                  for(bk=0;bk<32;bk++)
                    pic->ram[(0x0080*bk)|offset]=temp;
                  
                  pic->ram[P16E_FSR1L]=pic->ram[P16E_FSR1L_SHAD];  
                  offset=0x007F&P16E_FSR1L;
                  temp=pic->ram[P16E_FSR1L];
                  for(bk=0;bk<32;bk++)
                    pic->ram[(0x0080*bk)|offset]=temp;
                  
                  pic->ram[P16E_FSR1H]=pic->ram[P16E_FSR1H_SHAD];               
                  offset=0x007F&P16E_FSR1H;
                  temp=pic->ram[P16E_FSR1H];
                  for(bk=0;bk<32;bk++)
                    pic->ram[(0x0080*bk)|offset]=temp;        
                  
                break;
                case 0x000A:
//CALLW    -     Call Subroutine with W             2    00 0000 0000 1010    
                  if(print)printf("CALLW\n");
                  for(temp=15;temp>0;temp--)
	            pic->stack[temp]=pic->stack[temp-1];  //TODO P16E implement acess to stack  and STKPTR
	          pic->stack[0]=pic->pc;
	          pic->jpc=((pic->ram[P16E_PCLATH]&0x1F)<<8)|pic->ram[P16E_WREG];
	          pic->s2=1;   
                break;     
                case 0x000B:
//BRW      -     Relative Branch with W             2    00 0000 0000 1011   
                  if(print)printf("BRW\n");
//TODO P16E DEBUG
/*          
        if(((pic->config[0] & 0x0800) == 0)&&(((pic->ram[P16E_ICKBUG])&0x80)== 0x80) )//DEBUG ON
//	  pic->jpc=((0x18)<<8)|(opc & 0x07FF);
          pic->jpc=(pic->ROMSIZE-1)&(((0xF8)<<8)|(opc & 0x07FF));
       else  
 */ 
                     pic->jpc=(pic->pc+pic->ram[P16E_WREG])&((pic->ROMSIZE<<1)-1);
	          pic->s2=1;  
                break;      
                case 0x0010 ... 0x0017:
//MOVIW    n,m   Move Indirect FSRn to W with       1    00 0000 0001 0nmm   Z   
//               pre/post inc/dec modifier, mm  
                 if(print)printf("MOVIW FSR%i, %i\n",(opc & 0x0004) != 0,opc & 0x0003 );   
                 pic->lram=P16E_WREG;   
                 if(opc & 0x0004)//INDF1
                 {
                   switch(opc &0x0003)
                   {
                     case 0://pre inc
                     afsr[1]++; 
                     pic->ram[P16E_FSR1H]=(afsr[1] & 0xFF00)>>8;
                     pic->ram[P16E_FSR1L]=afsr[1] & 0x00FF; 
                     ReadIndf(pic, afsr);
                     pic->rram=afsr[1];
                     pic->ram[P16E_WREG]=pic->ram[P16E_INDF1];
                     break;    
                     case 1://pre dec
                     afsr[1]--;    
                     pic->ram[P16E_FSR1H]=(afsr[1] & 0xFF00)>>8;
                     pic->ram[P16E_FSR1L]=afsr[1] & 0x00FF; 
                     ReadIndf(pic, afsr);
                     pic->rram=afsr[1];
                     pic->ram[P16E_WREG]=pic->ram[P16E_INDF1];
                     break;
                     case 2://post inc
                     pic->ram[P16E_WREG]=pic->ram[P16E_INDF1];
                     pic->rram=afsr[1];
                     afsr[1]++;
                     pic->ram[P16E_FSR1H]=(afsr[1] & 0xFF00)>>8;
                     pic->ram[P16E_FSR1L]=afsr[1] & 0x00FF;   
                     break;
                     case 3://post dec
                     pic->ram[P16E_WREG]=pic->ram[P16E_INDF1];   
                     pic->rram=afsr[1];
                     afsr[1]--;
                     pic->ram[P16E_FSR1H]=(afsr[1] & 0xFF00)>>8;
                     pic->ram[P16E_FSR1L]=afsr[1] & 0x00FF;        
                     break;
                   }
                 }
                 else//INDF0
                 {
                   switch(opc &0x0003)
                   {
                     case 0://pre inc
                     afsr[0]++; 
                     pic->ram[P16E_FSR0H]=(afsr[0] & 0xFF00)>>8;
                     pic->ram[P16E_FSR0L]=afsr[0] & 0x00FF; 
                     ReadIndf(pic, afsr);
                     pic->rram=afsr[0];
                     pic->ram[P16E_WREG]=pic->ram[P16E_INDF0];
                     break;    
                     case 1://pre dec
                     afsr[0]--;    
                     pic->ram[P16E_FSR0H]=(afsr[0] & 0xFF00)>>8;
                     pic->ram[P16E_FSR0L]=afsr[0] & 0x00FF; 
                     ReadIndf(pic, afsr);
                     pic->rram=afsr[0];
                     pic->ram[P16E_WREG]=pic->ram[P16E_INDF0];
                     break;
                     case 2://post inc
                     pic->ram[P16E_WREG]=pic->ram[P16E_INDF0];
                     pic->rram=afsr[0];
                     afsr[0]++;
                     pic->ram[P16E_FSR0H]=(afsr[0] & 0xFF00)>>8;
                     pic->ram[P16E_FSR0L]=afsr[0] & 0x00FF;   
                     break;
                     case 3://post dec
                     pic->ram[P16E_WREG]=pic->ram[P16E_INDF0];   
                     pic->rram=afsr[0];
                     afsr[0]--;
                     pic->ram[P16E_FSR1H]=(afsr[0] & 0xFF00)>>8;
                     pic->ram[P16E_FSR1L]=afsr[0] & 0x00FF;        
                     break;
                   }                 
                 }     
                break;   
                case 0x0018 ... 0x001F:
//MOVWI    n,m   Move W to Indirect FSRn with       1    00 0000 0001 1nmm   
//               pre/post inc/dec modifier, mm       
                 if(print)printf("MOVWI FSR%i, %i\n",(opc & 0x0004) != 0,opc & 0x0003 );   
                 pic->rram=P16E_WREG;   
                 if(opc & 0x0004)//INDF1
                 {
                   switch(opc &0x0003)
                   {
                     case 0://pre inc
                     afsr[1]++; 
                     pic->ram[P16E_FSR1H]=(afsr[1] & 0xFF00)>>8;
                     pic->ram[P16E_FSR1L]=afsr[1] & 0x00FF; 
                     ReadIndf(pic, afsr);
                     pic->lram=P16E_INDF1;
                     pic->ram[P16E_INDF1]=pic->ram[P16E_WREG];
                     break;    
                     case 1://pre dec
                     afsr[1]--;    
                     pic->ram[P16E_FSR1H]=(afsr[1] & 0xFF00)>>8;
                     pic->ram[P16E_FSR1L]=afsr[1] & 0x00FF; 
                     ReadIndf(pic, afsr);
                     pic->lram=P16E_INDF1;
                     pic->ram[P16E_INDF1]=pic->ram[P16E_WREG];
                     break;
                     case 2://post inc
                     pic->ram[P16E_INDF1]=pic->ram[P16E_WREG];
                     pic->lram=P16E_INDF1;
                     afsrpos=+1; 
                     break;
                     case 3://post dec
                     pic->ram[P16E_INDF1]=pic->ram[P16E_WREG];   
                     pic->lram=P16E_INDF1; 
                     afsrpos=-1;
                     break;
                   }
                 }
                 else//INDF0
                 {
                   switch(opc &0x0003)
                   {
                     case 0://pre inc
                     afsr[0]++; 
                     pic->ram[P16E_FSR0H]=(afsr[0] & 0xFF00)>>8;
                     pic->ram[P16E_FSR0L]=afsr[0] & 0x00FF; 
                     ReadIndf(pic, afsr);
                     pic->lram=P16E_INDF0;
                     pic->ram[P16E_INDF0]=pic->ram[P16E_WREG];
                     break;    
                     case 1://pre dec
                     afsr[0]--;    
                     pic->ram[P16E_FSR0H]=(afsr[0] & 0xFF00)>>8;
                     pic->ram[P16E_FSR0L]=afsr[0] & 0x00FF; 
                     ReadIndf(pic, afsr);
                     pic->lram=P16E_INDF0;
                     pic->ram[P16E_INDF0]=pic->ram[P16E_WREG];
                     break;
                     case 2://post inc
                     pic->ram[P16E_INDF0]=pic->ram[P16E_WREG];
                     pic->lram=P16E_INDF0;
                     afsrpos=+1;
                     break;
                     case 3://post dec
                     pic->ram[P16E_INDF0]=pic->ram[P16E_WREG];   
                     pic->lram=P16E_INDF0;
                     afsrpos=-1;
                     break;
                   }                 
                 }     
                break;      
                case 0x0020 ... 0x003F:
//MOVLB    k     Move literal to BSR                1    00 0000 001k kkkk                      
                  if(print)printf("MOVLB %#04X\n",opc & 0x001F);
	          pic->ram[P16E_BSR]= (opc & 0x001F);
                  pic->lram=P16E_BSR;
                break;    
                case 0x0063:
//SLEEP   --  	Go into Standby mode         1     0000000 1100011   	TO,PD
                  if(print)printf("SLEEP\n");   
  		  pic->wdt=0;
  		  pic->sleep=1;
	          *status&=~0x08;
	          *status|=0x10;
                break;
		case 0x0064:
//CLRWDT  --  	Clear Watchdog Timer         1     0000000 1100100   	TO,PD
                  if(print)printf("CLRWDT\n");   
  		  pic->wdt=0;
	          *status|=0x08;
	          *status|=0x10;
  		break;
                case 0x0065 ... 0x0067:
//TRIS     f     Load TRIS register with W          1    00 0000 0110 01ff                
                  if(print)printf("TRIS %#04X\n",opc & 0x0007);
                  switch(opc&0x0003)
                  {
                      case 1:
                        pic->ram[P16E_TRISA]= pic->ram[P16E_WREG];
                        pic->lram=P16E_TRISA;
                      break;    
                      case 2:
                        pic->ram[P16E_TRISB]= pic->ram[P16E_WREG];
                        pic->lram=P16E_TRISB;
                      break;
                      case 3:
                        pic->ram[P16E_TRISC]= pic->ram[P16E_WREG];
                        pic->lram=P16E_TRISC;
                      break;
                  }
                break;                  
                case 0x006A:
//OPTION   -     Load OPTION_REG register with W    1    00 0000 0110 0010     
                  if(print)printf("OPTION\n");
	          pic->ram[P16E_OPTION_REG]= pic->ram[P16E_WREG];
                  pic->lram=P16E_OPTION_REG; 
                break;    
                default:
                printf("unknown opcode 0x%04X!\n",opc);
                break;
              };
	    break;
	    case 0x0080:
//MOVWF   f  	Move W to f                  1     0000001 fffffff
              if(print)printf("MOVWF %#04X\n",opc & 0x007F);
	      pic->ram[bank|(opc & 0x007F)]=pic->ram[P16E_WREG];
              pic->lram=bank|(opc & 0x007F);
	    break;
          default:
            printf("unknown opcode 0x%04X!\n",opc);
            break;
	  }
	break;
	case 0x0100:
          switch(opc & 0x0080)
          {
            case 0x0000:
//CLRW    --  	Clear W                      1     0000010 00000xx 	Z	
              if(print)printf("CLRW\n");
              pic->ram[P16E_WREG]=0;
              pic->lram=P16E_WREG;
            break;
	    case 0x0080:
//CLRF    f  	Clear f                      1     0000011 fffffff 	Z       2
              if(print)printf("CLRF %#04X\n",opc & 0x007F);
              pic->ram[bank|(opc & 0x007F) ]=0;
              pic->lram=bank|(opc & 0x007F);
	    break;
          default:
            printf("unknown opcode 0x%04X!\n",opc);
            break;
	  };
	break;
	case 0x0200:
//SUBWF   f, d 	Subtract W from f            1     000010 dfffffff 	C,DC,Z  1, 2
          if(print)printf("SUBWF %#04X,%d\n",opc & 0x007F,(opc & 0x0080)>>7);
	
	  if((0xF0&((0x0F&(~pic->ram[P16E_WREG]))+1+(0x0F&pic->ram[bank|(opc & 0x007F)]))) !=0)
	    *status|=0x02;
	  else   
	    *status&=~0x02;

	  temp=(~pic->ram[P16E_WREG]+1)+pic->ram[bank|(opc & 0x007F)];
	
	  if ((0xFF00&temp) != 0) 
	    *status&=~0x01;
	  else   
	    *status|=0x01;

          if((opc & 0x0080) == 0 )
	  {
	    pic->ram[P16E_WREG] = (unsigned char)(0x00FF &temp);
            pic->lram=P16E_WREG;
	    if (pic->ram[P16E_WREG] == 0) 
	       *status|=0x04;
	    else   
	       *status&=~0x04;
          }
	  else
	  {
	    pic->ram[bank|(opc & 0x007F)]=(unsigned char)(0x00FF &temp);
            pic->lram=bank|(opc & 0x007F);
	    if (pic->ram[bank|(opc & 0x007F) ] == 0) 
	       *status|=0x04;
	    else   
	       *status&=~0x04;
	  };     
        break;
	case 0x0300:
//DECF    f, d 	Decrement f                  1     000011 dfffffff  	Z       1, 2
          if(print)printf("DECF %#04X,%d\n",opc & 0x007F,(opc & 0x0080)>>7);
          if((opc & 0x0080) == 0 )
	  {
	    pic->ram[P16E_WREG]=pic->ram[bank|(opc & 0x007F)]-1;
            pic->lram=P16E_WREG;
	    if (pic->ram[P16E_WREG] == 0) 
	       *status|=0x04;
	    else   
	       *status&=~0x04;
          }
	  else
	  {
	    pic->ram[bank|(opc & 0x007F) ]--;
            pic->lram=bank|(opc & 0x007F);
	    if (pic->ram[bank|(opc & 0x007F) ] == 0) 
	       *status|=0x04;
	    else   
	       *status&=~0x04;
	  };     
        break;
	case 0x0400:
//IORWF   f, d 	Inclusive OR W with f        1     000100 dfffffff   	Z       1, 2
          if(print)printf("IORWF %#04X,%d\n",opc & 0x007F,(opc & 0x0080)>>7);
          if((opc & 0x0080) == 0 )
	  {
	    pic->ram[P16E_WREG]= pic->ram[P16E_WREG] | pic->ram[bank|(opc & 0x007F)];
            pic->lram=P16E_WREG;
	    if (pic->ram[P16E_WREG] == 0) 
	       *status|=0x04;
	    else   
	       *status&=~0x04;
          }
	  else
	  {
	    pic->ram[bank|(opc & 0x007F) ]= pic->ram[P16E_WREG] | pic->ram[bank|(opc & 0x007F)];
            pic->lram=bank|(opc & 0x007F);
	    if (pic->ram[bank|(opc & 0x007F) ] == 0) 
	       *status|=0x04;
	    else   
	       *status&=~0x04;
	  };     
        break;
	case 0x0500:
//ANDWF   f, d 	AND W with f                 1     000101 dfffffff	Z       1, 2
          if(print)printf("ANDWF %#04X,%d\n",opc & 0x007F,(opc & 0x0080)>>7);
          if((opc & 0x0080) == 0 )
	  {
	    pic->ram[P16E_WREG]= pic->ram[P16E_WREG] & pic->ram[bank|(opc & 0x007F)];
            pic->lram=P16E_WREG;
	    if (pic->ram[P16E_WREG] == 0) 
	       *status|=0x04;
	    else   
	       *status&=~0x04;
          }
	  else
	  {
	    pic->ram[bank|(opc & 0x007F) ]= pic->ram[P16E_WREG] & pic->ram[bank|(opc & 0x007F)];
            pic->lram=bank|(opc & 0x007F);
	    if (pic->ram[bank|(opc & 0x007F) ] == 0) 
	       *status|=0x04;
	    else   
	       *status&=~0x04;
	  };     
        break;
	case 0x0600:
//XORWF   f, d 	Exclusive OR W with f        1     000110 dfffffff  	Z       1, 2
          if(print)printf("XORWF %#04X,%d\n",opc & 0x007F,(opc & 0x0080)>>7);
          if((opc & 0x0080) == 0 )
	  {
	    pic->ram[P16E_WREG]= pic->ram[P16E_WREG] ^ pic->ram[bank|(opc & 0x007F)];
            pic->lram=P16E_WREG;
	    if (pic->ram[P16E_WREG] == 0) 
	       *status|=0x04;
	    else   
	       *status&=~0x04;
          }
	  else
	  {
	    pic->ram[bank|(opc & 0x007F) ]= pic->ram[P16E_WREG] ^ pic->ram[bank|(opc & 0x007F)];
            pic->lram=bank|(opc & 0x007F);
	    if (pic->ram[bank|(opc & 0x007F) ] == 0) 
	       *status|=0x04;
	    else   
	       *status&=~0x04;
	  };     
        break;
	case 0x0700:
//ADDWF	f, d 	Add W and f                  1     000111 dfffffff	C,DC,Z  1, 2
          if(print)printf("ADDWF %#04X,%d\n",opc & 0x007F,(opc & 0x0080)>>7);
	
	  if((0xF0&((0x0F&pic->ram[P16E_WREG])+(0x0F&pic->ram[bank|(opc & 0x007F)]))) !=0)
	    *status|=0x02;
	  else   
	    *status&=~0x02;

	  temp=pic->ram[P16E_WREG]+pic->ram[bank|(opc & 0x007F)];
	
	  if ((0xFF00&temp) != 0) 
	    *status|=0x01;
	  else   
	    *status&=~0x01;

          if((opc & 0x0080) == 0 )
	  {
	    pic->ram[P16E_WREG] = (unsigned char)(0x00FF &temp);
            pic->lram=P16E_WREG;
	    if (pic->ram[P16E_WREG] == 0) 
	       *status|=0x04;
	    else   
	       *status&=~0x04;
          }
	  else
	  {
	    pic->ram[bank|(opc & 0x007F)]=(unsigned char)(0x00FF &temp);
            pic->lram=bank|(opc & 0x007F);
	    if (pic->ram[bank|(opc & 0x007F) ] == 0) 
	       *status|=0x04;
	    else   
	       *status&=~0x04;
	  };     
        break;
	case 0x0800:
//MOVF    f, d 	Move f                       1     001000 dfffffff 	Z       1, 2
          if(print)printf("MOVF %#04X,%d\n",opc & 0x007F,(opc & 0x0080)>>7);
          if((opc & 0x0080) == 0 )
	  {
	    pic->ram[P16E_WREG]=pic->ram[bank|(opc & 0x007F)];
	    if (pic->ram[P16E_WREG] == 0) 
	       *status|=0x04;
	    else   
	       *status&=~0x04;
            pic->rram=bank|(opc & 0x007F);
            pic->lram=P16E_WREG;
          }
	  else
	  {
	    if (pic->ram[bank|(opc & 0x007F) ] == 0) 
	       *status|=0x04;
	    else   
	       *status&=~0x04;
            pic->rram=bank|(opc & 0x007F);
            pic->lram=bank|(opc & 0x007F);
	  };     
        break;
	case 0x0900:
//COMF    f, d 	Complement f                 1     001001 dfffffff 	Z       1, 2
          if(print)printf("COMF %#04X,%d\n",opc & 0x007F,(opc & 0x0080)>>7);
          if((opc & 0x0080) == 0 )
	  {
	    pic->ram[P16E_WREG]=~pic->ram[bank|(opc & 0x007F)];
            pic->lram=P16E_WREG;
	    if (pic->ram[P16E_WREG] == 0) 
	       *status|=0x04;
	    else   
	       *status&=~0x04;
          }
	  else
	  {
	    pic->ram[bank|(opc & 0x007F) ]=~pic->ram[bank|(opc & 0x007F) ];
            pic->lram=bank|(opc & 0x007F);
	    if (pic->ram[bank|(opc & 0x007F) ] == 0) 
	       *status|=0x04;
	    else   
	       *status&=~0x04;
	  };     
        break;
	case 0x0A00:
//INCF    f, d 	Increment f                  1     001010 dfffffff	Z       1, 2
          if(print)printf("INCF %#04X,%d\n",opc & 0x007F,(opc & 0x0080)>>7);
          if((opc & 0x0080) == 0 )
	  {
	    pic->ram[P16E_WREG]=pic->ram[bank|(opc & 0x007F)]+1;
            pic->lram=P16E_WREG;
	    if (pic->ram[P16E_WREG] == 0) 
	       *status|=0x04;
	    else   
	       *status&=~0x04;
          }
	  else
	  {
	    pic->ram[bank|(opc & 0x007F) ]++;
            pic->lram=bank|(opc & 0x007F);
	    if (pic->ram[bank|(opc & 0x007F) ] == 0) 
	       *status|=0x04;
	    else   
	       *status&=~0x04;
	  };     
        break;
	case 0x0B00:
//DECFSZ  f, d 	Decrement f, Skip if 0       1(2)  001011 dfffffff 		1, 2, 3  
          if(print)printf("DECFSZ %#04X,%d\n",opc & 0x007F,(opc & 0x0080)>>7);
          if((opc & 0x0080) == 0 )
	  {
	    pic->ram[P16E_WREG]=pic->ram[bank|(opc & 0x007F)]-1;
            pic->lram=P16E_WREG;
	    if (pic->ram[P16E_WREG] == 0)
	    {
	      pic->jpc=pic->pc+1;
	      pic->s2=1;
	    };
          }
	  else
	  {
	    pic->ram[bank|(opc & 0x007F) ]--;
            pic->lram=bank|(opc & 0x007F);
	    if (pic->ram[bank|(opc & 0x007F) ] == 0) 
	    {
	      pic->jpc=pic->pc+1;
	      pic->s2=1;
	    };
	  };     
        break;
	case 0x0C00:
//RRF     f, d 	Rotate Right f through Carry 1     001100 dfffffff	C       1, 2
          if(print)printf("RRF %#04X,%d\n",opc & 0x007F,(opc & 0x0080)>>7);
	  temp=(pic->ram[bank|(opc & 0x007F)]);
	  if((*status&0x01) ==0x01)temp|=0x0100;
	  if((temp&0x0001) ==0x01)
	    *status|=0x01;
	  else  
	    *status&=~0x01;
	  temp=temp>>1;
          if((opc & 0x0080) == 0 )
	  {
	    pic->ram[P16E_WREG]=0x00FF&temp;
            pic->lram=P16E_WREG;
          }
	  else
	  {
	    pic->ram[bank|(opc & 0x007F) ]=0x00FF&temp;
            pic->lram=bank|(opc & 0x007F);
	  };     
        break;
	case 0x0D00:
//RLF     f, d 	Rotate Left f through Carry  1     001101 dfffffff	C       1, 2                   
          if(print)printf("RLF %#04X,%d\n",opc & 0x007F,(opc & 0x0080)>>7);
	  temp=(pic->ram[bank|(opc & 0x007F)]);
	  temp=temp<<1;
	  if((*status&0x01) ==0x01)temp|=0x0001;
	  if((temp&0x0100) ==0x0100)
	    *status|=0x0001;
	  else  
	    *status&=~0x0001;
          if((opc & 0x0080) == 0 )
	  {
	    pic->ram[P16E_WREG]=0x00FF & temp;
            pic->lram=P16E_WREG;
          }
	  else
	  {
	    pic->ram[bank|(opc & 0x007F) ]= 0x00FF & temp;
            pic->lram=bank|(opc & 0x007F);
	  };     
        break;
	case 0x0E00:
//SWAPF   f, d 	Swap nibbles in f            1     001110 dfffffff 		1, 2
          if(print)printf("SWAPF %#04X,%d\n",opc & 0x007F,(opc & 0x0080)>>7);
          if((opc & 0x0080) == 0 )
	  {
	    pic->ram[P16E_WREG]=((pic->ram[bank|(opc & 0x007F)]&0x0F)<<4)|
	           ((pic->ram[bank|(opc & 0x007F)]&0xF0)>>4);
            pic->lram=P16E_WREG;
          }
	  else
	  {
	    pic->ram[bank|(opc & 0x007F) ]=
	           ((pic->ram[bank|(opc & 0x007F)]&0x0F)<<4)|
	           ((pic->ram[bank|(opc & 0x007F)]&0xF0)>>4);
            pic->lram=bank|(opc & 0x007F);
	  };     
        break;
	case 0x0F00:
//INCFSZ  f, d 	Increment f, Skip if 0       1(2)  001111 dfffffff		1, 2, 3 
          if(print)printf("INCFSZ %#04X,%d\n",opc & 0x007F,(opc & 0x0080)>>7);
          if((opc & 0x0080) == 0 )
	  {
	    pic->ram[P16E_WREG]=pic->ram[bank|(opc & 0x007F)]+1;
            pic->lram=P16E_WREG;
	    if (pic->ram[P16E_WREG] == 0)
	    {
	      pic->jpc=pic->pc+1;
	      pic->s2=1;
	    };
          }
	  else
	  {
	    pic->ram[bank|(opc & 0x007F) ]++;
            pic->lram=bank|(opc & 0x007F);
	    if (pic->ram[bank|(opc & 0x007F) ] == 0) 
	    {
	      pic->jpc=pic->pc+1;
	      pic->s2=1;
	    };
	  };     
        break;
      default:
        printf("unknown opcode 0x%04X!\n",opc);
        break;
      }
    break; 
    case 0x1000:
      switch(opc & 0x0C00)
      {
        case 0x0000:
//BCF     f, b 	Bit Clear f                  1     0100 bbbfffffff           1, 2
          if(print)printf("BCF %#04X,%d\n",opc & 0x007F,(opc & 0x0380)>>7);
	  pic->ram[bank|(opc & 0x007F)]&=~(0x01<<((opc & 0x0380)>>7));
          pic->lram=bank|(opc & 0x007F);
	break;
	case 0x0400:
//BSF     f, b 	Bit Set f                    1     0101 bbbfffffff           1, 2
          if(print)printf("BSF %#04X,%d\n",opc & 0x007F,(opc & 0x0380)>>7);
	  pic->ram[bank|(opc & 0x007F)]|=(0x01<<((opc & 0x0380)>>7));
          pic->lram=bank|(opc & 0x007F);
        break;
	case 0x0800:
//BTFSC   f, b 	Bit Test f, Skip if Clear    1(2)  0110 bbbfffffff           3
        if(print)printf("BTFSC %#04X,%d\n",opc & 0x007F,(opc & 0x0380)>>7);
	if((pic->ram[bank|(opc & 0x007F)] & (0x01<<((opc & 0x0380)>>7))) == 0)
	{
	      pic->jpc=pic->pc+1;
	      pic->s2=1;
	}
        break;
	case 0x0C00:
//BTFSS   f, b 	Bit Test f, Skip if Set      1(2)  0111 bbbfffffff           3
        if(print)printf("BTFSS %#04X,%d\n",opc & 0x007F,(opc & 0x0380)>>7);
	if((pic->ram[bank|(opc & 0x007F)] & (0x01<<((opc & 0x0380)>>7))) != 0)
	{
	      pic->jpc=pic->pc+1;
	      pic->s2=1;
	}
        break;
      default:
        printf("unknown opcode 0x%04X!\n",opc);
        break;
      };
    break; 
    case 0x2000:
      switch(opc & 0x0800)
      {
        case 0x0000:
//CALL    k  	Call subroutine              2     100 kkkkkkkkkkk
          if(print)printf("CALL %#05X\n",opc & 0x07FF);
          for(temp=15;temp>0;temp--)
	    pic->stack[temp]=pic->stack[temp-1];  //TODO P16E implement acess to stack  and STKPTR
	  pic->stack[0]=pic->pc;
	  pic->jpc=((pic->ram[bank|(P16E_PCLATH & 0x007F)]&0x18)<<8)|(opc & 0x07FF);
	  pic->s2=1;
        break;
	case 0x0800:
//GOTO    k  	Go to address                2     101 kkkkkkkkkkk
          if(print)printf("GOTO %#05X\n",opc & 0x07FF);
//TODO P16E DEBUG
/*          
          if(((pic->config[0] & 0x0800) == 0)&&(((pic->ram[P16E_ICKBUG])&0x80)== 0x80) )//DEBUG ON
//	    pic->jpc=((0x18)<<8)|(opc & 0x07FF);
	    pic->jpc=(pic->ROMSIZE-1)&(((0xF8)<<8)|(opc & 0x07FF));
	  else  
 */ 
            pic->jpc=((pic->ram[bank|(P16E_PCLATH & 0x007F)]&0x18)<<8)|(opc & 0x07FF);
	  pic->s2=1;
  	break;
      default:
        printf("unknown opcode 0x%04X!\n",opc);
        break;
      }
    break; 
    case 0x3000:
      switch(opc & 0x0F00)
      {
        case 0x0000:
//MOVLW   k  	Move literal to W            1     110000 kkkkkkkk 
        if(print)printf("MOVLW %#04X\n",opc & 0x00FF);
	pic->ram[P16E_WREG]= (opc & 0x00FF);
        pic->lram=P16E_WREG;
        break;
        case 0x0100:
            switch(opc & 0x0080)
            {               
              case 0x0080:
//MOVLP    k     Move literal to PCLATH             1    11 0001 1kkk kkkk                   
                if(print)printf("MOVLP %#04X\n",opc & 0x007F);
	        pic->ram[P16E_PCLATH]= (opc & 0x007F);
                pic->lram=P16E_PCLATH;
                break;      
              case 0x0000: 
//ADDFSR   n,k   Add Literal k to FSRn              1    11 0001 0nkk kkkk  
                 jrange=(((short)((opc & 0x003F)<<10))/1024);   
                 if(print)printf("ADDFSR FSR%i ,%i\n",(opc & 0x0040) != 0, jrange); 
                 if(opc & 0x0040)//FSR1
                 {
                   afsr[1]+=jrange;
                   pic->ram[P16E_FSR1H]=(afsr[1] & 0xFF00)>>8;
                   pic->ram[P16E_FSR1L]=afsr[1] & 0x00FF;     
                   pic->lram=P16E_FSR1L;
                 }
                 else //FSR0
                 {
                   afsr[0]+=jrange;
                   pic->ram[P16E_FSR0H]=(afsr[0] & 0xFF00)>>8;
                   pic->ram[P16E_FSR0L]=afsr[0] & 0x00FF;    
                   pic->lram=P16E_FSR0L;
                 }
              break;  
              default:
                printf("unknown opcode 0x%04X!\n",opc);
              break;
            }
        break;
	case 0x0200:
        case 0x0300:    
//         BRA      k     Relative Branch                    2    11 001k kkkk kkkk
        jrange=(((short)((opc & 0x01FF)<<7))/64);    
        //if(print)printf("BRA %#05X\n",opc & 0x01FF);
        if(print)printf("BRA %#06X\n",(pic->pc+jrange)&((pic->ROMSIZE<<1)-1));
//TODO P16E DEBUG
/*          
        if(((pic->config[0] & 0x0800) == 0)&&(((pic->ram[P16E_ICKBUG])&0x80)== 0x80) )//DEBUG ON
//	  pic->jpc=((0x18)<<8)|(opc & 0x07FF);
          pic->jpc=(pic->ROMSIZE-1)&(((0xF8)<<8)|(opc & 0x07FF));
       else  
 */ 
            pic->jpc=(pic->pc+jrange)&((pic->ROMSIZE<<1)-1);
	  pic->s2=1;         
        break;    
	case 0x0400:
//RETLW   k  	Return with literal in W     2     110100 kkkkkkkk
          if(print)printf("RETLW %#04X\n",opc & 0x00FF);
	  pic->jpc=pic->stack[0];
          for(temp=0;temp<15;temp++)
	    pic->stack[temp]=pic->stack[temp+1];
	  pic->stack[15]=0;
	  pic->s2=1;
	  pic->ram[P16E_WREG]= (opc & 0x00FF);
        break;     
	case 0x0500:        
//LSLF     f,d   Logical Left Shift                 1    11 0101 dfff ffff     C, Z        2             
          if(print)printf("LSLF %#04X,%d\n",opc & 0x007F,(opc & 0x0080)>>7);
	  temp=(pic->ram[bank|(opc & 0x007F)]);
	  temp=temp<<1;
	  if((temp&0x0100) ==0x0100)
	    *status|=0x0001;
	  else  
	    *status&=~0x0001;
          if((opc & 0x0080) == 0 )
	  {
	    pic->ram[P16E_WREG]=0x00FF & temp;
          }
	  else
	  {
	    pic->ram[bank|(opc & 0x007F) ]= 0x00FF & temp;
            pic->lram=bank|(opc & 0x007F);
	  };     
        break;     
	case 0x0600:            
//LSRF     f,d   Logical Right Shift                1    11 0110 dfff ffff     C, Z        2   
          if(print)printf("LSRF %#04X,%d\n",opc & 0x007F,(opc & 0x0080)>>7);
	  temp=(pic->ram[bank|(opc & 0x007F)]);
	  if((temp&0x0001) ==0x01)
	    *status|=0x01;
	  else  
	    *status&=~0x01;
	  temp=temp>>1;
          if((opc & 0x0080) == 0 )
	  {
	    pic->ram[P16E_WREG]=0x00FF&temp;
          }
	  else
	  {
	    pic->ram[bank|(opc & 0x007F) ]=0x00FF&temp;
            pic->lram=bank|(opc & 0x007F);
	  };     
        break;         
        case 0x0700:
//ASRF     f,d   Arithmetic Right Shift             1    11 0111 dfff ffff     C, Z        2
          if(print)printf("ASRF %#04X,%d\n",opc & 0x007F,(opc & 0x0080)>>7);
	  temp=(pic->ram[bank|(opc & 0x007F)]);
	  if((temp&0x0001) ==0x01)
	    *status|=0x01;
	  else  
	    *status&=~0x01;
	  temp=(temp&0x80)|(temp>>1);
          if((opc & 0x0080) == 0 )
	  {
	    pic->ram[P16E_WREG]=0x00FF&temp;
          }
	  else
	  {
	    pic->ram[bank|(opc & 0x007F) ]=0x00FF&temp;
            pic->lram=bank|(opc & 0x007F);
	  };   
        break;    
	case 0x0800:
//IORLW   k  	Inclusive OR literal with W  1     111000 kkkkkkkk   	Z
        if(print)printf("IORLW %#04X\n",opc & 0x00FF);
	pic->ram[P16E_WREG] |= (opc & 0x00FF);
	if (pic->ram[P16E_WREG] == 0) 
	  *status|=0x04;
	else   
	  *status&=~0x04;
        break;
	case 0x0900:
//ANDLW   k 	AND literal with W           1     111001 kkkkkkkk   	Z
        if(print)printf("ANDLW %#04X\n",opc & 0x00FF);
	pic->ram[P16E_WREG] &= (opc & 0x00FF);
	if (pic->ram[P16E_WREG] == 0) 
	  *status|=0x04;
	else   
	  *status&=~0x04;
        break;
	case 0x0A00:
//XORLW   k  	Exclusive OR literal with W  1     111010 kkkkkkkk   	Z
        if(print)printf("XORLW %#04X\n",opc & 0x00FF);
	pic->ram[P16E_WREG] ^= (opc & 0x00FF);
	if (pic->ram[P16E_WREG] == 0) 
	  *status|=0x04;
	else   
	  *status&=~0x04;
        break;
	case 0x0B00:
//SUBWFB   f,d   Subtract with Borrow W from f      1    11 1011 dfff ffff     C, DC, Z    2
         if(print)printf("SUBWFB %#04X,%d\n",opc & 0x007F,(opc & 0x0080)>>7);
	 if((0xF0&((0x0F&(~pic->ram[P16E_WREG]))+(!(pic->ram[P16E_STATUS]&0x01))+1+(0x0F&pic->ram[bank|(opc & 0x007F)]))) !=0)
	   *status|=0x02;
	 else   
	   *status&=~0x02;

	 temp=(~(pic->ram[P16E_WREG]+(!(pic->ram[P16E_STATUS]&0x01)))+1)+pic->ram[bank|(opc & 0x007F)];
	
	 if ((0xFF00&temp) != 0) 
	   *status&=~0x01;
	 else   
	   *status|=0x01;

         if((opc & 0x0080) == 0 )
	 {
	   pic->ram[P16E_WREG] = (unsigned char)(0x00FF &temp);
	   if (pic->ram[P16E_WREG] == 0) 
	      *status|=0x04;
	   else   
	      *status&=~0x04;
         }
	 else
	 {
	   pic->ram[bank|(opc & 0x007F)]=(unsigned char)(0x00FF &temp);
           pic->lram=bank|(opc & 0x007F);
	   if (pic->ram[bank|(opc & 0x007F) ] == 0) 
	      *status|=0x04;
	   else   
	      *status&=~0x04;
	 };     
        break;
	case 0x0C00:
//SUBLW   k  	Subtract W from literal      1     111100 kkkkkkkk   	C,DC,Z
        if(print)printf("SUBLW %#04X\n",opc & 0x00FF);
	
	if((0xF0&((0x0F&(~pic->ram[P16E_WREG]))+1+(opc & 0x000F))) !=0)
	  *status|=0x02;
	else   
	  *status&=~0x02;

	temp=(~pic->ram[P16E_WREG]+1)+(opc & 0x00FF);
	pic->ram[P16E_WREG] = (unsigned char)(0x00FF &temp);
	
	if ((0xFF00&temp) != 0) 
	  *status&=~0x01;
	else   
	  *status|=0x01;
	
	if (pic->ram[P16E_WREG] == 0) 
	  *status|=0x04;
	else   
	  *status&=~0x04;
        break;
        case 0x0D00:
//ADDWFC   f,d   Add W and f and Carry                       1    11 1101 dfff ffff     C, DC, Z    2 
          if(print)printf("ADDWFC %#04X,%d\n",opc & 0x007F,(opc & 0x0080)>>7);
	
	  if((0xF0&((0x0F&pic->ram[P16E_WREG])+(0x0F&pic->ram[bank|(opc & 0x007F)])+(pic->ram[P16E_STATUS]&0x01))) !=0)
	    *status|=0x02;
	  else   
	    *status&=~0x02;

	  temp=pic->ram[P16E_WREG]+pic->ram[bank|(opc & 0x007F)]+(pic->ram[P16E_STATUS]&0x01);
	
	  if ((0xFF00&temp) != 0) 
	    *status|=0x01;
	  else   
	    *status&=~0x01;

          if((opc & 0x0080) == 0 )
	  {
	    pic->ram[P16E_WREG] = (unsigned char)(0x00FF &temp);
	    if (pic->ram[P16E_WREG] == 0) 
	       *status|=0x04;
	    else   
	       *status&=~0x04;
          }
	  else
	  {
	    pic->ram[bank|(opc & 0x007F)]=(unsigned char)(0x00FF &temp);
            pic->lram=bank|(opc & 0x007F);
	    if (pic->ram[bank|(opc & 0x007F) ] == 0) 
	       *status|=0x04;
	    else   
	       *status&=~0x04;
	  };     
        break;              
	case 0x0E00:
//ADDLW   k  	Add literal and W            1     111110 kkkkkkkk   	C,DC,Z
        if(print)printf("ADDLW %#04X\n",opc & 0x00FF);
	
	if((0xF0&((0x0F&pic->ram[P16E_WREG])+(opc & 0x000F))) !=0)
	  *status|=0x02;
	else   
	  *status&=~0x02;

	temp=pic->ram[P16E_WREG]+(opc & 0x00FF);
	pic->ram[P16E_WREG] = (unsigned char)(0x00FF &temp);
	
	if ((0xFF00&temp) != 0) 
	  *status|=0x01;
	else   
	  *status&=~0x01;
	
	if (pic->ram[P16E_WREG] == 0) 
	  *status|=0x04;
	else   
	  *status&=~0x04;
        break;
	case 0x0F00:
          switch(opc & 0x0080)
          {
            case 0x0000:
//MOVIW    k[n]  Move INDFn to W, Indexed Indirect  1    11 1111 0nkk kkkk   Z  
              jrange=(((short)((opc & 0x003F)<<10))/1024);    
              if(print)printf("MOVIW %i[FSR%i]\n",jrange, (opc & 0x0040) != 0 );   
              pic->lram=P16E_WREG;  
              if(opc & 0x0040)//INDF1
              {
                afsr[1]+=jrange;
                pic->ram[P16E_FSR1H]=(afsr[1] & 0xFF00)>>8;
                pic->ram[P16E_FSR1L]=afsr[1] & 0x00FF; 
                ReadIndf(pic, afsr);
                pic->rram=afsr[1];
                pic->ram[P16E_WREG]=pic->ram[P16E_INDF1];  
                afsr[1]-=jrange;
                pic->ram[P16E_FSR1H]=(afsr[1] & 0xFF00)>>8;
                pic->ram[P16E_FSR1L]=afsr[1] & 0x00FF; 
              }
              else//INDF0
              {
                afsr[0]+=jrange;
                pic->ram[P16E_FSR0H]=(afsr[0] & 0xFF00)>>8;
                pic->ram[P16E_FSR0L]=afsr[0] & 0x00FF; 
                ReadIndf(pic, afsr);
                pic->rram=afsr[0];
                pic->ram[P16E_WREG]=pic->ram[P16E_INDF0];  
                afsr[0]-=jrange;
                pic->ram[P16E_FSR0H]=(afsr[0] & 0xFF00)>>8;
                pic->ram[P16E_FSR0L]=afsr[0] & 0x00FF;     
              }  
            break;
            case 0x0080:
//MOVWI    k[n]  Move W to INDFn, Indexed Indirect  1    11 1111 1nkk kkkk      
              jrange=(((short)((opc & 0x003F)<<10))/1024);    
              if(print)printf("MOVWI %i[FSR%i]\n",jrange, (opc & 0x0040) != 0 );   
              pic->rram=P16E_WREG;    
              if(opc & 0x0040)//INDF1
              {
                afsr[1]+=jrange;
                pic->ram[P16E_FSR1H]=(afsr[1] & 0xFF00)>>8;
                pic->ram[P16E_FSR1L]=afsr[1] & 0x00FF; 
                ReadIndf(pic, afsr);
                pic->lram=P16E_INDF1;
                pic->ram[P16E_INDF1]=pic->ram[P16E_WREG];  
                afsrpos=-jrange;
              }
              else//INDF0
              {
                afsr[0]+=jrange;
                pic->ram[P16E_FSR0H]=(afsr[0] & 0xFF00)>>8;
                pic->ram[P16E_FSR0L]=afsr[0] & 0x00FF; 
                ReadIndf(pic, afsr);
                pic->lram=P16E_INDF0;
                pic->ram[P16E_INDF0]=pic->ram[P16E_WREG];  
                afsrpos=-jrange;     
              }  
              break;    
            break;
            default:
              printf("unknown opcode 0x%04X!\n",opc);
            break;    
          }
        break; 
      default:
        printf("unknown opcode 0x%04X!\n",opc);
        break;
      }
    break;
    default:
      printf("unknown opcode 0x%04X!\n",opc);
      break;
  }
  

  
  if(pic->lram != 0x8000) 
  {
      
  switch(pic->lram)
  {
    case P16E_INDF0:
      if(afsr[0] <= 0x0FFF)//taditional data memory
      {
        pic->ram[afsr[0]]=pic->ram[P16E_INDF0];
        pic->lram=afsr[0];
      }
      else
      {
        if(afsr[0] >= 0x8000)// 0x8000 - 0xFFFF Program flash memory 
        {
          //do nothing, ROM memory
        }
        else //0x2000 - 0x29AF linear data memory      
        {
          unsigned short addr= afsr[0]-0x2000;

          int bk=addr/80;
          int bkoff=addr%80;
          unsigned short laddr= (bk*0x80)+0x20+bkoff;

          pic->ram[laddr]=pic->ram[P16E_INDF0];
          pic->lram=afsr[0];
        }
      }
      if(afsrpos != 0)
      {
        afsr[0]+=afsrpos;  
        pic->ram[P16E_FSR0H]=(afsr[0] & 0xFF00)>>8;
        pic->ram[P16E_FSR0L]=afsr[0] & 0x00FF;  
      }               
      break; 

    case P16E_INDF1:
      if(afsr[1] <= 0x0FFF)//taditional data memory
      {  
        pic->ram[afsr[1]]=pic->ram[P16E_INDF1];
        pic->lram=afsr[1];
      }
      else
      {
        if(afsr[1] >= 0x8000)// 0x8000 - 0xFFFF Program flash memory 
        {
          //do nothing, ROM memory
        }
        else //0x2000 - 0x29AF linear data memory      
        {
          unsigned short addr= afsr[1]-0x2000;

          int bk=addr/80;
          int bkoff=addr%80;
          unsigned short laddr= (bk*0x80)+0x20+bkoff;

          pic->ram[laddr]=pic->ram[P16E_INDF1];
          pic->lram=afsr[1];
        }    
      }
      if(afsrpos != 0)
      {
        afsr[1]+=afsrpos;  
        pic->ram[P16E_FSR1H]=(afsr[1] & 0xFF00)>>8;
        pic->ram[P16E_FSR1L]=afsr[1] & 0x00FF;  
      }  
      break; 
  }   

      
    //bank init mirror
  if((pic->lram & 0x007F) <= 0x000B)
  {
    int bk;  
    int offset=0x007F&pic->lram;
    temp=pic->ram[pic->lram];
    
    for(bk=0;bk<32;bk++)
       pic->ram[(0x0080*bk)|offset]=temp;
  }
  
  
  //bank end mirror
  if((pic->lram & 0x007F) >= 0x0070)
  {
    int bk;  
    int offset=0x007F&pic->lram;
    temp=pic->ram[pic->lram];
    
    for(bk=0;bk<32;bk++)
       pic->ram[(0x0080*bk)|offset]=temp;
  }
      
      
  //second pass with new lram    
  switch(pic->lram)
  {   
    case P16E_STKPTR:
      if((pic->ram[P16E_STKPTR] & 0x1F) >0)
      {
        pic->ram[P16E_TOSL]=((pic->stack[(pic->ram[P16E_STKPTR] & 0x1F)-1])&0x0000FF);  
        pic->ram[P16E_TOSH]=((pic->stack[(pic->ram[P16E_STKPTR] & 0x1F)-1])&0x00FF00)>>8;   
      }
      else
      {
        pic->ram[P16E_TOSL]=0;
        pic->ram[P16E_TOSH]=0;
      }        
      break;
    case P16E_TOSL:
      if((pic->ram[P16E_STKPTR] & 0x1F) > 0)  
        pic->stack[(pic->ram[P16E_STKPTR] & 0x1F)-1]= (pic->stack[(pic->ram[P16E_STKPTR] & 0x1F)-1] & 0x1FFF00)|pic->ram[P16E_TOSL];
      break;
    case P16E_TOSH:
      if((pic->ram[P16E_STKPTR] & 0x1F) > 0)  
        pic->stack[(pic->ram[P16E_STKPTR] & 0x1F)-1]= (pic->stack[(pic->ram[P16E_STKPTR] & 0x1F)-1] & 0x1F00FF)|(pic->ram[P16E_TOSH]<<8);
      break;

    
    case P16E_PCL:
      pic->pc=  ((pic->ram[P16E_PCLATH])<<8)|pic->ram[P16E_PCL];
//	      printf("###############PCL write  (%#04X %#04X %#04X) %#08X\n",(pic->ram[P16E_PCLATU]&0x1F)<<16,(pic->ram[P16E_PCLATH])<<8,pic->ram[P16E_PCL],pic->pc);
      break; 
  }
  
   //second pass with new lram  family dependent   
  if(pic->family == P16E)
  {
    switch(pic->lram)
    {    
    case P16E_LATA:
      pic->ram[P16E_PORTA]=pic->ram[P16E_LATA];
      break;	
    case P16E_LATB:
      pic->ram[P16E_PORTB]=pic->ram[P16E_LATB];
      break;	
    case P16E_LATC:
      pic->ram[P16E_PORTC]=pic->ram[P16E_LATC];
      break;	
    case P16E_LATD:
      pic->ram[P16E_PORTD]=pic->ram[P16E_LATD];
      break;	
  
    case P16E_PORTA:
      pic->ram[P16E_LATA]=pic->ram[P16E_PORTA];
      break;	
    case P16E_PORTB:
      pic->ram[P16E_LATB]=pic->ram[P16E_PORTB];
      break;	
    case P16E_PORTC:
      pic->ram[P16E_LATC]=pic->ram[P16E_PORTC];
      break;	
    case P16E_PORTD:
      pic->ram[P16E_LATD]=pic->ram[P16E_PORTD];
      break;	
    }
  }
  else  //P16E2
  {
    switch(pic->lram)
    {    
    case P16E2_LATA:
      pic->ram[P16E2_PORTA]=pic->ram[P16E2_LATA];
      break;	
    case P16E2_LATB:
      pic->ram[P16E2_PORTB]=pic->ram[P16E2_LATB];
      break;	
    case P16E2_LATC:
      pic->ram[P16E2_PORTC]=pic->ram[P16E2_LATC];
      break;	
    case P16E2_LATD:
      pic->ram[P16E2_PORTD]=pic->ram[P16E2_LATD];
      break;	
    case P16E2_LATE:
      pic->ram[P16E2_PORTE]=pic->ram[P16E2_LATE];
      break;  
  
    case P16E2_PORTA:
      pic->ram[P16E2_LATA]=pic->ram[P16E2_PORTA];
      break;	
    case P16E2_PORTB:
      pic->ram[P16E2_LATB]=pic->ram[P16E2_PORTB];
      break;	
    case P16E2_PORTC:
      pic->ram[P16E2_LATC]=pic->ram[P16E2_PORTC];
      break;	
    case P16E2_PORTD:
      pic->ram[P16E2_LATD]=pic->ram[P16E2_PORTD];
      break;	
    case P16E2_PORTE:
      pic->ram[P16E2_LATE]=pic->ram[P16E2_PORTE];
      break;  
    }
  }      
 
  }
  
  if(pic->rram != 0x8000)
  {
      
  switch(pic->rram)
  {
    case P16E_INDF0:
      pic->rram=afsr[0];  
      break;  
  
    case P16E_INDF1:
      pic->rram=afsr[1];  
      break;   
  }
  
  //second pass with new rram
  switch(pic->rram)
  {    
     case P16E_PCL:
  //    printf("###############PCL read\n");
      pic->ram[P16E_PCLATH]=(pic->pc&0x00FF00)>>8;
     break;
  }
  }

  
  
  
  pic->w=pic->ram[P16E_WREG];

  if((pic->rram != 0x8000)&&(print))
  {
    if(pic->rram <= 0x0FFF)
    {
      if(pic->family == P16E)  
        printf("mem read  %#06X: %10s= %#06X\n",pic->rram,getFSRname_16E(pic->rram),pic->ram[pic->rram]);
      else
        printf("mem read  %#06X: %10s= %#06X\n",pic->rram,getFSRname_16E2(pic->rram),pic->ram[pic->rram]);  
    }
    else
    {
      if(pic->rram >= 0x8000)
      {
        unsigned short addr= pic->rram-0x8000;  
        printf("mem read  %#06X: %10s= %#06X\n",pic->rram,"PROG MEM",pic->prog[addr]);
      }
      else //linear bank
      {
          unsigned short addr= pic->rram -0x2000;

          int bk=addr/80;
          int bkoff=addr%80;
          unsigned short laddr= (bk*0x80)+0x20+bkoff;

          printf("mem read  %#06X: %10s= %#06X\n",pic->rram,"LINEAR MEM",pic->ram[laddr]);
      }
    }
  }
  
  if((pic->lram != 0x8000)&&(print))
  {
    if(pic->lram <= 0x0FFF)  
    {
      if(pic->family == P16E)    
        printf("mem write %#06X: %10s= %#06X\n",pic->lram,getFSRname_16E(pic->lram),pic->ram[pic->lram]);
      else
        printf("mem write %#06X: %10s= %#06X\n",pic->lram,getFSRname_16E2(pic->lram),pic->ram[pic->lram]);          
    }
    else
    {
      if(pic->lram >= 0x8000)
      {  
        unsigned short addr= pic->lram-0x8000;  
        printf("mem write  %#06X: %10s= %#06X\n",pic->lram,"PROG MEM",pic->prog[addr]);
      }
      else
      {
        unsigned short addr= pic->lram -0x2000;
        int bk=addr/80;
        int bkoff=addr%80;
        unsigned short laddr= (bk*0x80)+0x20+bkoff;

        printf("mem write  %#06X: %10s= %#06X\n",pic->rram,"LINEAR MEM",pic->ram[laddr]);
      }    
    }
  }

}


