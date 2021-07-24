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
#include<unistd.h>
#include"../include/picsim.h"

#ifdef _WIN_
#include <time.h>
#include <windows.h>
#endif


extern void pic_decode_18(void);


#define ROM	0x01
#define CFG	0x02
#define EEPROM	0x04
 
  

static int            icsp_type;
static int            icsp_mode;
static unsigned int   icsp_addr;  
//static unsigned short icsp_data[10];
static unsigned short icsp_datac;
static unsigned int   icsp_cmddata;
static unsigned int   icsp_bit;
static unsigned char  icsp_sda;
static unsigned char  icsp_sck;
static unsigned char  icsp_cmd;  




void 
pic_icsp_init18(void)
{
     //entrando em icsp_mode de  programacao  
        icsp_sda=0;
        icsp_sck=0;
        icsp_mode=0;
        icsp_bit=0;
        icsp_cmddata=0;
	icsp_addr=0;
        icsp_type=0;
        icsp_datac=0;
        icsp_cmd=0;  
        pic->pins[(pic->pgc-1)].dir=PD_IN;
        pic->pins[(pic->pgd-1)].dir=PD_IN;
        printf  ("-------------------------------------------------------\n"); 

}
 

int 
pic_icsp18(void)
{
 
  int icsp_scka=1;
  int i;
	     
  unsigned  int pc_bkp;
  unsigned  int rom_bkp; 
  unsigned  int conf_bkp; 

  unsigned  long tblptr;

//------------------------------
//icsp

     icsp_scka=icsp_sck;
     icsp_sck=pic_get_pin(pic->pgc); 


     if((icsp_scka != icsp_sck)&&(icsp_sck == 0))  
     {
       if(icsp_mode == 0)     
       { 
         icsp_sda=pic_get_pin( pic->pgd); 
         icsp_cmddata|=(icsp_sda<<icsp_bit);
       }
       icsp_bit++;
     }  
     

      if((icsp_bit == 5)&&(!icsp_cmd))
      {
         icsp_cmd=1;
         switch((icsp_cmddata&0x00000F))
         {

	   case 0x00: //Core Instruction                 0000
	     if(pic->print)printf("_Core Instruction\n");
             break;
           case 0x02: //Shift out TABLAT register        0010
	     if(pic->print)printf("_Shift out TABLAT register\n");
	     icsp_cmddata|=((*pic->P18map.TABLAT))<<11;
	     icsp_mode=1;  	
             pic->pins[(pic->pgd-1)].dir=PD_OUT;
             if(pic->print)printf("TABLAT=0x%2X\n",(*pic->P18map.TABLAT));
             break;
           case 0x08: //Table Read                       1000
	     if(pic->print)printf("_Table Read\n");

              tblptr=((*pic->P18map.TBLPTRU)<<16) | ((*pic->P18map.TBLPTRH)<<8) | (*pic->P18map.TBLPTRL);
              if((tblptr>>1) < pic->ROMSIZE)
              {   
                if(tblptr & 0x0001)
	          icsp_cmddata|=(pic->prog[tblptr>>1]&0xFF00 )<<3;
	        else
	          icsp_cmddata|=(pic->prog[tblptr>>1]&0x00FF)<<11;
              }
              //read id
	      else if((tblptr >=0x200000)&&(tblptr <= 0x200007))
              {
                if(tblptr & 0x0001)
	          icsp_cmddata|=(pic->id[(tblptr-0x200000)>>1]&0xFF00 )<<3;
	        else
	          icsp_cmddata|=(pic->id[(tblptr-0x200000)>>1]&0x00FF)<<11;
              }	
              //read config
	      else if((tblptr >=0x300000)&&(tblptr <= 0x30000D))
              {
                if(tblptr & 0x0001)
	          icsp_cmddata|=(pic->config[(tblptr-0x300000)>>1]&0xFF00 )<<3;
	        else
	          icsp_cmddata|=(pic->config[(tblptr-0x300000)>>1]&0x00FF)<<11;
              }	
              //read device id 
              else if((tblptr & 0x3FFFFE ) == 0x3FFFFE )
              {   
                if(tblptr & 0x0001)
	          icsp_cmddata|=(pic->processor&0xFF00 )<<3;
	        else
	          icsp_cmddata|=(pic->processor&0x00FF)<<11;
              }
              //read debug vector 
	      else if((tblptr >=0x200028)&&(tblptr <= 0x200037))
              {
                if(tblptr & 0x0001)
	          icsp_cmddata|=(pic->debugv[(tblptr-0x200028)>>1]&0xFF00 )<<3;
	        else
	          icsp_cmddata|=(pic->debugv[(tblptr-0x200028)>>1]&0x00FF)<<11;
              }
              else  
	        (*pic->P18map.TABLAT)=0;

              if(pic->print)printf("READ====0x%04lX ==========0x%04X\n",tblptr,(icsp_cmddata&0x00007F800)>>11); 

	     icsp_mode=1;  	
             pic->pins[(pic->pgd-1)].dir=PD_OUT;
             break;
           case 0x09: //Table Read, post-increment       1001
	     if(pic->print)printf("_Table Read, post-increment\n");

              tblptr=((*pic->P18map.TBLPTRU)<<16) | ((*pic->P18map.TBLPTRH)<<8) | (*pic->P18map.TBLPTRL);
              if((tblptr>>1) < pic->ROMSIZE)
              {   
                if(tblptr & 0x0001)
	          icsp_cmddata|=(pic->prog[tblptr>>1]&0xFF00 )<<3;
	        else
	          icsp_cmddata|=(pic->prog[tblptr>>1]&0x00FF)<<11;
              }
              //read id
	      else if((tblptr >=0x200000)&&(tblptr <= 0x200007))
              {
                if(tblptr & 0x0001)
	          icsp_cmddata|=(pic->id[(tblptr-0x200000)>>1]&0xFF00 )<<3;
	        else
	          icsp_cmddata|=(pic->id[(tblptr-0x200000)>>1]&0x00FF)<<11;
              }	
              //read config
	      else if((tblptr >=0x300000)&&(tblptr <= 0x30000D))
              {
                if(tblptr & 0x0001)
	          icsp_cmddata|=(pic->config[(tblptr-0x300000)>>1]&0xFF00 )<<3;
	        else
	          icsp_cmddata|=(pic->config[(tblptr-0x300000)>>1]&0x00FF)<<11;
              }	
              //read device id 
              else if((tblptr & 0x3FFFFE ) == 0x3FFFFE )
              {   
                if(tblptr & 0x0001)
	          icsp_cmddata|=(pic->processor&0xFF00 )<<3;
	        else
	          icsp_cmddata|=(pic->processor&0x00FF)<<11;
              }
              //read debug vector 
	      else if((tblptr >=0x200028)&&(tblptr <= 0x200037))
              {
                if(tblptr & 0x0001)
	          icsp_cmddata|=(pic->debugv[(tblptr-0x200028)>>1]&0xFF00 )<<3;
	        else
	          icsp_cmddata|=(pic->debugv[(tblptr-0x200028)>>1]&0x00FF)<<11;
              }
              else  
	        (*pic->P18map.TABLAT)=0;

              if(pic->print)printf("READ====0x%04lX ==========0x%04X\n",tblptr,(icsp_cmddata&0x00007F800)>>11); 

              tblptr++;
              (*pic->P18map.TBLPTRU)=(tblptr&0x3F0000)>>16; 
              (*pic->P18map.TBLPTRH)=(tblptr&0x00FF00)>>8;
              (*pic->P18map.TBLPTRL)=(tblptr&0x0000FF);  

	     icsp_mode=1;  	
             pic->pins[(pic->pgd-1)].dir=PD_OUT;

             break;
           case 0x0A: //Table Read, post-decrement       1010
	     if(pic->print)printf("_Table Read, post-decrement\n");

              tblptr=((*pic->P18map.TBLPTRU)<<16) | ((*pic->P18map.TBLPTRH)<<8) | (*pic->P18map.TBLPTRL);
              if((tblptr>>1) < pic->ROMSIZE)
              {   
                if(tblptr & 0x0001)
	          icsp_cmddata|=(pic->prog[tblptr>>1]&0xFF00 )<<3;
	        else
	          icsp_cmddata|=(pic->prog[tblptr>>1]&0x00FF)<<11;
              }
              //read id
	      else if((tblptr >=0x200000)&&(tblptr <= 0x200007))
              {
                if(tblptr & 0x0001)
	          icsp_cmddata|=(pic->id[(tblptr-0x200000)>>1]&0xFF00 )<<3;
	        else
	          icsp_cmddata|=(pic->id[(tblptr-0x200000)>>1]&0x00FF)<<11;
              }	
              //read config
	      else if((tblptr >=0x300000)&&(tblptr <= 0x30000D))
              {
                if(tblptr & 0x0001)
	          icsp_cmddata|=(pic->config[(tblptr-0x300000)>>1]&0xFF00 )<<3;
	        else
	          icsp_cmddata|=(pic->config[(tblptr-0x300000)>>1]&0x00FF)<<11;
              }	
              //read device id 
              else if((tblptr & 0x3FFFFE ) == 0x3FFFFE )
              {   
                if(tblptr & 0x0001)
	          icsp_cmddata|=(pic->processor&0xFF00 )<<3;
	        else
	          icsp_cmddata|=(pic->processor&0x00FF)<<11;
              }
              //read debug vector 
	      else if((tblptr >=0x200028)&&(tblptr <= 0x200037))
              {
                if(tblptr & 0x0001)
	          icsp_cmddata|=(pic->debugv[(tblptr-0x200028)>>1]&0xFF00 )<<3;
	        else
	          icsp_cmddata|=(pic->debugv[(tblptr-0x200028)>>1]&0x00FF)<<11;
              }
              else  
	        (*pic->P18map.TABLAT)=0;

              if(pic->print)printf("READ====0x%04lX ==========0x%04X\n",tblptr,(icsp_cmddata&0x00007F800)>>11); 

              tblptr--;
              (*pic->P18map.TBLPTRU)=(tblptr&0x3F0000)>>16; 
              (*pic->P18map.TBLPTRH)=(tblptr&0x00FF00)>>8;
              (*pic->P18map.TBLPTRL)=(tblptr&0x0000FF);  

	     icsp_mode=1;  	
             pic->pins[(pic->pgd-1)].dir=PD_OUT;
             break;
           case 0x0B: //Table Read, pre-increment        1011
	     if(pic->print)printf("_Table Read, pre-increment\n");

              tblptr=((*pic->P18map.TBLPTRU)<<16) | ((*pic->P18map.TBLPTRH)<<8) | (*pic->P18map.TBLPTRL);
              tblptr++;

              if((tblptr>>1) < pic->ROMSIZE)
              {   
                if(tblptr & 0x0001)
	          icsp_cmddata|=(pic->prog[tblptr>>1]&0xFF00 )<<3;
	        else
	          icsp_cmddata|=(pic->prog[tblptr>>1]&0x00FF)<<11;
              }
              //read id
	      else if((tblptr >=0x200000)&&(tblptr <= 0x200007))
              {
                if(tblptr & 0x0001)
	          icsp_cmddata|=(pic->id[(tblptr-0x200000)>>1]&0xFF00 )<<3;
	        else
	          icsp_cmddata|=(pic->id[(tblptr-0x200000)>>1]&0x00FF)<<11;
              }	
              //read config
	      else if((tblptr >=0x300000)&&(tblptr <= 0x30000D))
              {
                if(tblptr & 0x0001)
	          icsp_cmddata|=(pic->config[(tblptr-0x300000)>>1]&0xFF00 )<<3;
	        else
	          icsp_cmddata|=(pic->config[(tblptr-0x300000)>>1]&0x00FF)<<11;
              }	
              //read device id 
              else if((tblptr & 0x3FFFFE ) == 0x3FFFFE )
              {   
                if(tblptr & 0x0001)
	          icsp_cmddata|=(pic->processor&0xFF00 )<<3;
	        else
	          icsp_cmddata|=(pic->processor&0x00FF)<<11;
              }
              //read debug vector 
	      else if((tblptr >=0x200028)&&(tblptr <= 0x200037))
              {
                if(tblptr & 0x0001)
	          icsp_cmddata|=(pic->debugv[(tblptr-0x200028)>>1]&0xFF00 )<<3;
	        else
	          icsp_cmddata|=(pic->debugv[(tblptr-0x200028)>>1]&0x00FF)<<11;
              }
              else  
	        (*pic->P18map.TABLAT)=0;

              if(pic->print)printf("READ====0x%04lX ==========0x%04X\n",tblptr,(icsp_cmddata&0x00007F800)>>11); 

              (*pic->P18map.TBLPTRU)=(tblptr&0x3F0000)>>16; 
              (*pic->P18map.TBLPTRH)=(tblptr&0x00FF00)>>8;
              (*pic->P18map.TBLPTRL)=(tblptr&0x0000FF);  

	     icsp_mode=1;  	
             pic->pins[(pic->pgd-1)].dir=PD_OUT;
             break;
           case 0x0C: //Table Write                      1100
	     if(pic->print)printf("_Table Write\n");
             break;
           case 0x0D: //Table Write, post-increment by 2 1101
	     if(pic->print)printf("_Table Write, post-increment by 2\n");
             break;
           case 0x0E: //Table Write, post-decrement by 2 1110
	     if(pic->print)printf("_Table Write, post-decrement by 2\n");
             break;
           case 0x0F: //Table Write, start programming   1111
	     if(pic->print)printf("_Table Write, start programming\n");
             break;
           default:
	      if(pic->print)printf  ("_Unknow Command %02X \n",(icsp_cmddata&0x00000F)); 
              icsp_cmddata=0;
              icsp_bit=0;
              icsp_cmd=0;
             break;
         }
      }
      else if(icsp_bit == 20)
      {
         switch((icsp_cmddata&0x00000F))
         {
	   case 0x00: //Core Instruction                 0000
	     if(pic->print)printf("Core Instruction  %#04X \n",(icsp_cmddata&0x000FFFF0)>>4);
          
             if(pic->s2 !=0)pic_decode_18();

	     pc_bkp=pic->pc;
             rom_bkp=pic->prog[pic->ROMSIZE]; 
             conf_bkp=pic->config[3];
 
             pic->config[3]|=0x80; //disdable debug bit    
	     pic->pc=(pic->ROMSIZE<<1);
             pic->prog[pic->ROMSIZE]=((icsp_cmddata&0x000FFFF0)>>4);
 
             pic_step();
              
             pic->pc=pc_bkp;
             pic->prog[pic->ROMSIZE]=rom_bkp;
             pic->config[3]=conf_bkp;
             break;
           case 0x02: //Shift out TABLAT register        0010
	     if(pic->print)printf("Shift out TABLAT register\n");
             break;
           case 0x08: //Table Read                       1000
	     if(pic->print)printf("Table Read\n");
             break;
           case 0x09: //Table Read, post-increment       1001
	     if(pic->print)printf("Table Read, post-increment\n");
             break;
           case 0x0A: //Table Read, post-decrement       1010
	     if(pic->print)printf("Table Read, post-decrement\n");
             break;
           case 0x0B: //Table Read, pre-increment        1011
	     if(pic->print)printf("Table Read, pre-increment\n");
             break;
           case 0x0C: //Table Write                      1100
	     if(pic->print)printf("Table Write\n");
              tblptr=((*pic->P18map.TBLPTRU)<<16) | ((*pic->P18map.TBLPTRH)<<8) | (*pic->P18map.TBLPTRL);
              if((tblptr>>1) < pic->ROMSIZE)
              {   
	        pic->prog[tblptr>>1]=((icsp_cmddata&0x000FFFF0)>>4);
              }
              //write id
	      else if((tblptr >=0x200000)&&(tblptr <= 0x200007))
              {
	        pic->id[(tblptr-0x200000)>>1]=((icsp_cmddata&0x000FFFF0)>>4);
              }	
              //write config
	      else if((tblptr >=0x300000)&&(tblptr <= 0x30000D))
              {
	        pic->config[(tblptr-0x300000)>>1]=((icsp_cmddata&0x000FFFF0)>>4);
                if(pic->print)printf("=>TBLWT* 0x%06lX   0x%02X \n",tblptr,((icsp_cmddata&0x000FFFF0)>>4));
              }
              //debug vector  
	      else if((tblptr >=0x200028)&&(tblptr <= 0x200037))
              {
	        pic->debugv[(tblptr - 0x200028)>>1]=((icsp_cmddata&0x000FFFF0)>>4);
              }
	      //erase control		
	      else if(tblptr ==0x3C0004)
              {
	        switch((icsp_cmddata&0x000FFFF0)>>4)
                {
                  case 0x80://chip erase    
                  case 0x81://erase data eeprom    
                  case 0x83://erase boot block    
                  case 0x88://erase panel 1     
                  case 0x89://erase panel 2    
                  case 0x8A://erase panel 3    
                  case 0x8B://erase panel 4
                    for(i=0;i<pic->CONFIGSIZE;i++)
                      pic->config[i]=0xFFFF;
 	            for(i=0;i<pic->IDSIZE;i++)
                      pic->id[i]=0xFFFF;
 	            for(i=0;i<pic->ROMSIZE;i++)
                      pic->prog[i]=0xFFFF;
                    for(i=0;i<pic->EEPROMSIZE;i++)
                      pic->eeprom[i]=0xFF;
                    break;       
                } 

              }
              
              if(pic->print)printf("WRITE====0x%04lX ==========0x%04X\n",tblptr,(icsp_cmddata&0x0000FFFF0)>>4); 

             break;
           case 0x0D: //Table Write, post-increment by 2 1101
	     if(pic->print)printf("Table Write, post-increment by 2\n");
              tblptr=((*pic->P18map.TBLPTRU)<<16) | ((*pic->P18map.TBLPTRH)<<8) | (*pic->P18map.TBLPTRL);
              if((tblptr>>1) < pic->ROMSIZE)
              {   
	        pic->prog[tblptr>>1]=((icsp_cmddata&0x000FFFF0)>>4);
              }
              //write id
	      else if((tblptr >=0x200000)&&(tblptr <= 0x200007))
              {
	        pic->id[(tblptr-0x200000)>>1]=((icsp_cmddata&0x000FFFF0)>>4);
              }	
              //write config
	      else if((tblptr >=0x300000)&&(tblptr <= 0x30000D))
              {
	        pic->config[(tblptr-0x300000)>>1]=((icsp_cmddata&0x000FFFF0)>>4);
                if(pic->print)printf("=>TBLWT*+ 0x%06lX   0x%02X \n",tblptr,((icsp_cmddata&0x000FFFF0)>>4));
              }
              //debug vector  
	      else if((tblptr >=0x200028)&&(tblptr <= 0x200037))
              {
	        pic->debugv[(tblptr - 0x200028)>>1]=((icsp_cmddata&0x000FFFF0)>>4);
              }
	
              if(pic->print)printf("WRITE====0x%04lX ==========0x%04X\n",tblptr,(icsp_cmddata&0x0000FFFF0)>>4); 

              tblptr+=2;
              (*pic->P18map.TBLPTRU)=(tblptr&0x3F0000)>>16; 
              (*pic->P18map.TBLPTRH)=(tblptr&0x00FF00)>>8;
              (*pic->P18map.TBLPTRL)=(tblptr&0x0000FF);  

             break;
           case 0x0E: //Table Write, post-decrement by 2 1110
	     if(pic->print)printf("Table Write, post-decrement by 2\n");
              tblptr=((*pic->P18map.TBLPTRU)<<16) | ((*pic->P18map.TBLPTRH)<<8) | (*pic->P18map.TBLPTRL);
              if((tblptr>>1) < pic->ROMSIZE)
              {   
	        pic->prog[tblptr>>1]=((icsp_cmddata&0x000FFFF0)>>4);
              }
              //write id
	      else if((tblptr >=0x200000)&&(tblptr <= 0x200007))
              {
	        pic->id[(tblptr-0x200000)>>1]=((icsp_cmddata&0x000FFFF0)>>4);
              }	
              //write config
	      else if((tblptr >=0x300000)&&(tblptr <= 0x30000D))
              {
	        pic->config[(tblptr-0x300000)>>1]=((icsp_cmddata&0x000FFFF0)>>4);
                if(pic->print)printf("=>TBLWT*- 0x%06lX   0x%02X \n",tblptr,((icsp_cmddata&0x000FFFF0)>>4));
              }	
              //debug vector  
	      else if((tblptr >=0x200028)&&(tblptr <= 0x200037))
              {
	        pic->debugv[(tblptr - 0x200028)>>1]=((icsp_cmddata&0x000FFFF0)>>4);
              }
              
              if(pic->print)printf("WRITE====0x%04lX ==========0x%04X\n",tblptr,(icsp_cmddata&0x0000FFFF0)>>4); 

              tblptr-=2;
              (*pic->P18map.TBLPTRU)=(tblptr&0x3F0000)>>16; 
              (*pic->P18map.TBLPTRH)=(tblptr&0x00FF00)>>8;
              (*pic->P18map.TBLPTRL)=(tblptr&0x0000FF);  
             break;
           case 0x0F: //Table Write, start programming   1111
	     if(pic->print)printf("Table Write, start programming\n");
              tblptr=((*pic->P18map.TBLPTRU)<<16) | ((*pic->P18map.TBLPTRH)<<8) | (*pic->P18map.TBLPTRL);
              if((tblptr>>1) < pic->ROMSIZE)
              {   
	        pic->prog[tblptr>>1]=((icsp_cmddata&0x000FFFF0)>>4);
              }
              //write id
	      else if((tblptr >=0x200000)&&(tblptr <= 0x200007))
              {
	        pic->id[(tblptr-0x200000)>>1]=((icsp_cmddata&0x000FFFF0)>>4);
              }	
              //write config
	      else if((tblptr >=0x300000)&&(tblptr <= 0x30000D))
              {
	        pic->config[(tblptr-0x300000)>>1]=((icsp_cmddata&0x000FFFF0)>>4);
                if(pic->print)printf("=>TBLWT* 0x%06lX   0x%02X \n",tblptr,((icsp_cmddata&0x000FFFF0)>>4));
              }	
              //debug vector  
	      else if((tblptr >=0x200028)&&(tblptr <= 0x200037))
              {
	        pic->debugv[(tblptr - 0x200028)>>1]=((icsp_cmddata&0x000FFFF0)>>4);
              }
              
              if(pic->print)printf("WRITE====0x%04lX ==========0x%04X\n",tblptr,(icsp_cmddata&0x0000FFFF0)>>4); 

             break;
           default:
	      if(pic->print)printf  ("Unknow Command %02X \n",(icsp_cmddata&0x00000F)); 
             break;
         } 

         icsp_cmddata=0;
         icsp_bit=0;
         icsp_mode=0;
         pic->pins[(pic->pgd-1)].dir=PD_IN;
         icsp_cmd=0;  
      } 



     if(icsp_mode == 1)     
     {
       if((icsp_scka != icsp_sck)&&(icsp_sck == 0))  
       {
           if((icsp_cmddata & (1<<(icsp_bit-1))) != 0 )
           {
             icsp_sda=1;
           }
           else
           { 
             icsp_sda=0;
           }
       }
       pic->pins[(pic->pgd-1)].value=icsp_sda; 
     } 



    return 1;
}


