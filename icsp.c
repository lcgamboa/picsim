/* ########################################################################

   PICsim - PIC simulator

   ########################################################################

   Copyright (c) : 2008  Luis Claudio Gambôa Lopes

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
#include"picsim.h"

#ifdef _WIN_
#include <time.h>
#include <windows.h>
#endif




#define ROM	0x01
#define CFG	0x02
#define EEPROM	0x04
 
  

int            icsp_type;
int            icsp_mode;
unsigned int   icsp_addr;  
unsigned short icsp_data[10];
unsigned short icsp_datac;
unsigned int   icsp_cmddata;
unsigned int   icsp_bit;
unsigned char  icsp_sda;
unsigned char  icsp_sck;
unsigned char  icsp_cmd;




void 
pic_icsp_init(_pic * pic)
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
pic_icsp(_pic * pic, int  print)
{
 
  int icsp_scka=1;
  int i;

//------------------------------
//icsp

     icsp_scka=icsp_sck;
     icsp_sck=pic_get_pin(pic,pic->pgc); 


     if((icsp_scka != icsp_sck)&&(icsp_sck == 0))  
     {
       if(icsp_mode == 0)     
       { 
         icsp_sda=pic_get_pin(pic, pic->pgd); 
         icsp_cmddata|=(icsp_sda<<icsp_bit);
       }
       icsp_bit++;
     }  
     

      if((icsp_bit == 6)&&(!icsp_cmd))
      {
         icsp_cmd=1;
         switch((icsp_cmddata&0x00000F))
         {
           case 0x00: //LOAD CFG
	     icsp_type= CFG;
             break;
           case 0x02: //LOAD PROGRAM
	     if(icsp_type == 0)icsp_type= ROM;
             break;
           case 0x03: //LOAD DATA
	     icsp_type= EEPROM;
             break;
           case 0x06: //INC ADDR
              icsp_addr+=1; 
	      if(print)printf  ("inc icsp_addr %#04X \n",icsp_addr);
	      if(icsp_addr >= 0x2000)
              {
		 if(icsp_addr > 0x3FFF)
                  icsp_addr=0x2000;
              }
              else
              {
		 if(icsp_addr > pic->ROMSIZE)
                  icsp_addr=0;
              }
              icsp_cmddata=0;
              icsp_bit=0;
              icsp_cmd=0;
             break;
           case 0x04: //READ PROGRAM
	     icsp_mode=1; 
             pic->pins[(pic->pgd-1)].dir=PD_OUT;
             if(icsp_addr >= 0x2000)
             {
                if(icsp_addr == 0x2006)
                {
	          icsp_cmddata|=pic->processor<<7;	
                }
                else if(icsp_addr == 0x2007)
                {
	          icsp_cmddata|=(pic->config[icsp_addr-0x2007]<<7);	
                }
                else
                {   
	          icsp_cmddata|=(pic->id[icsp_addr-0x2000]<<7);	
                }
             }
             else
             {
	        icsp_cmddata|=(pic->prog[icsp_addr]<<7);	
             }	
             break;
           case 0x05: //READ DATA
	     icsp_cmddata|=(pic->eeprom[0x0000FF&icsp_addr]<<7);		
	     icsp_mode=1;  	
             pic->pins[(pic->pgd-1)].dir=PD_OUT;
             break;
           case 0x08: //Begin Prog cycle
	      if(print)printf  ("Begin Prog cycle %i  (%i)\n",icsp_type,icsp_datac);

	       switch(icsp_type)
               {
                 case ROM:
                   for(i=0;i< icsp_datac;i++) 
                      pic->prog[icsp_addr-icsp_datac+1+i]=icsp_data[i];
                   icsp_datac=0;
                   break; 
                 case CFG:
                   if(icsp_addr == 0x2007) 
                   {
                      pic->config[icsp_addr-0x2007]=icsp_data[0];
                   }
                   else
                   { 
                   for(i=0;i< icsp_datac;i++)
                   { 
                     pic->id[icsp_addr-0x2000-icsp_datac+1+i]=icsp_data[i];
                   }
                   icsp_datac=0;
                   }
                   break; 
                 case EEPROM: 
                   pic->eeprom[0x000FF&icsp_addr]=icsp_data[0];
                   break; 
               } 
              icsp_cmddata=0;
              icsp_bit=0;
              icsp_cmd=0;
             break;
           case 0x09: //Bulk erase PROGRAM
	      if(print)printf  ("Bulk erase PROGRAM \n"); 
              if(icsp_addr >= 0x2000) 
              {
 	        for(i=0;i<pic->CONFIGSIZE;i++)
                   pic->config[i]=0x3FFF;
 	        for(i=0;i<pic->IDSIZE;i++)
                   pic->id[i]=0x3FFF;
 	        for(i=0;i<pic->ROMSIZE;i++)
                  pic->prog[i]=0x3FFF;
              } 
              else
              {
 	        for(i=0;i<pic->ROMSIZE;i++)
                  pic->prog[i]=0x3FFF;
              } 
              icsp_cmddata=0;
              icsp_bit=0;
              icsp_cmd=0;
             break;
           case 0x0B: //Bulk erase DATA
	      if(print)printf  ("Bulk erase DATA \n"); 
              for(i=0;i<pic->EEPROMSIZE;i++)
                pic->eeprom[i]=0xFF;
	      icsp_cmddata=0;
              icsp_bit=0;
              icsp_cmd=0;
             break;
           case 0x0F: //chip erase 
	      if(print)printf  ("chip erase \n"); 
                for(i=0;i<pic->CONFIGSIZE;i++)
                   pic->config[i]=0x3FFF;
 	        for(i=0;i<pic->IDSIZE;i++)
                   pic->id[i]=0x3FFF;
 	        for(i=0;i<pic->ROMSIZE;i++)
                  pic->prog[i]=0x3FFF;
                for(i=0;i<pic->EEPROMSIZE;i++)
                  pic->eeprom[i]=0xFF;
              icsp_cmddata=0;
              icsp_bit=0;
              icsp_cmd=0;
             break;
           case 0x07: //end programing 
	      if(print)printf  ("end programing \n"); 
              icsp_datac=0;
              icsp_cmddata=0;
              icsp_bit=0;
              icsp_cmd=0;
              break;
           default:
	      if(print)printf  ("Unknow Command %02X \n",(icsp_cmddata&0x00000F)); 
              icsp_cmddata=0;
              icsp_bit=0;
              icsp_cmd=0;
             break;
         } 
      }
      else if(icsp_bit == 22)
      {
         switch((icsp_cmddata&0x00000F))
         {
           case 0x00: //LOAD CFG
	     icsp_addr=0x2000;  
	     if(print)printf  ("LOAD CFG %#04X \n",(icsp_cmddata&0x001FFF80)>>7);	
	     icsp_data[0]=(icsp_cmddata&0x001FFF80)>>7; 
             break;
           case 0x02: //LOAD PROGRAM
	     if(print)printf  ("LOAD PROG  %#04X \n",(icsp_cmddata&0x001FFF80)>>7);
	     icsp_data[icsp_datac++]=(icsp_cmddata&0x001FFF80)>>7; 
             break;
           case 0x03: //LOAD DATA
	     if(print)printf  ("LOAD DATA %#04X \n",(icsp_cmddata&0x00007F80)>>7);
	     icsp_data[0]=(icsp_cmddata&0x00007F80)>>7; 
             break;
           case 0x04: //READ PROGRAM
	     if(print)printf  ("READ PROGRAM  %#04X \n",(icsp_cmddata&0x001FFF80)>>7);
             break;
           case 0x05: //READ DATA
	     if(print)printf  ("READ DATA %#04X \n",(icsp_cmddata&0x007F80)>>7); 
             break;
           default:
             break;
         } 

         icsp_cmddata=0;
         icsp_bit=0;
         icsp_cmd=0;
         icsp_mode=0;
         pic->pins[(pic->pgd-1)].dir=PD_IN;
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


