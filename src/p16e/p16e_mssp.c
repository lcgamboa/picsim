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


int pic_wr_pin16E(unsigned char pin, unsigned char value);


void
p16e_mssp_rst(void)
{
 pic->ssp_sck = 0;
 pic->ssp_scka = 0;
 pic->sspsr = 0;
 pic->ssp_bit = 0;
 pic->sspsr = 0;
 
   //FIXME	
  printf ("Incomplete: %s -> %s :%i\n", __func__,__FILE__, __LINE__);
}

void
p16e_mssp(void)
{
 //FIXME	
  printf ("Incomplete: %s -> %s :%i\n", __func__,__FILE__, __LINE__);
 /*
 //MSSP

  if((pic->ram[P16E_SSPCON] & 0x20) ==0x20) //SSPEN
  {
    
     if((pic->ram[P16E_SSPCON] & 0x0F) ==0x05)//SLAVE Without SS
     {
   
       pic->pins[pic->sdi-1].dir=PD_IN; 	
 
       if(pic->rram == P16E_SSPBUF)
       {
          pic->ram[P16E_SSPSTAT]&=~0x01; //BF
       } 	

         pic->ssp_scka=pic->ssp_sck; 
         pic->ssp_sck= pic->pins[pic->sck-1].value;


     if((pic->ssp_scka == 0)&&(pic->ssp_sck == 1)) //CKP =0 CKE =0     //coloca saida na borda de subida
         {
            pic_wr_pin(pic,pic->sdo, ((pic->ram[P16E_SSPBUF] & (1 <<(7-pic->ssp_bit))) > 0));
         }


     if((pic->ssp_scka == 1)&&(pic->ssp_sck == 0)) //CKP =0 CKE =0    //le na borda de decida
         {
        pic->sspsr|= (pic->pins[pic->sdi-1].value) << (7-pic->ssp_bit);
           
            //printf("SSP bit =%i    REC=%#02X   SEND=%#02X \n",pic->ssp_bit,pic->sspsr, pic->ram[SSPBUF]);

        pic->ssp_bit++;
         }

     if(pic->ssp_bit >= 8)
         {
 //	   printf("MSSP TX=%#02X  RX=%#02X\n",pic->ram[SSPBUF],pic->sspsr);
            pic->ram[P16E_SSPBUF]=pic->sspsr;
            pic->sspsr =0;
        pic->ram[P16E_SSPSTAT]|=0x01; //BF
           
            //PSPIF
            (*pic->P16Emap.PIR1)|=0x08;
        pic->ssp_bit=0;
         }
	

     }
     else if((pic->ram[P16E_SSPCON] & 0x0F) ==0x08)//MASTER i2c
     {
      
        pic->ssp_sck++;

        if(pic->ssp_sck == ((pic->ram[P16E_SSPADD]+1/2)-1))
        {
       
          if((pic->ram[P16E_SSPCON2] & 0x01)) //start
          {
            pic->pins[pic->sck-1].dir=PD_OUT; 	
            pic->pins[pic->sdi-1].dir=PD_OUT; 	
            pic->pins[pic->sdi-1].value=1;
            pic->pins[pic->sck-1].value=1;
        
            //printf("I2C_start 1\n");
          }
          else if((pic->ram[P16E_SSPCON2] & 0x02)) //restart
          {
            pic->pins[pic->sdi-1].dir=PD_OUT; 	
            pic->pins[pic->sdi-1].value=1;
            pic->pins[pic->sck-1].value=1;
            //printf("restar1\n");
          } 
          else if((pic->ram[P16E_SSPCON2] & 0x04)) //stop
          {
            pic->pins[pic->sdi-1].dir=PD_OUT; 	
            pic->pins[pic->sdi-1].value=0;
            pic->pins[pic->sck-1].value=1;
            //printf("stop1\n");
          } 
        }

        if(pic->ssp_sck == ((pic->ram[P16E_SSPADD]+1/2)+1))
        {
       
          if((pic->ram[P16E_SSPCON2] & 0x01)) //start
          {
            pic->ram[P16E_SSPCON2] &=~ 0x01;
           
            pic->pins[pic->sdi-1].value=0;
            pic->pins[pic->sck-1].value=1;
           
            //printf("start 2\n");
          }
          else if((pic->ram[P16E_SSPCON2] & 0x02)) //restart
          {
            pic->ram[P16E_SSPCON2] &=~ 0x02;

            pic->pins[pic->sdi-1].value=0;
            pic->pins[pic->sck-1].value=1;
            //printf("restart 2\n");
          } 
          else if((pic->ram[P16E_SSPCON2] & 0x04)) //stop
          {
            pic->ram[P16E_SSPCON2] &=~ 0x04;
         
            pic->ssp_bit=10;

            pic->pins[pic->sdi-1].value=1;
            pic->pins[pic->sck-1].value=1;
            //printf("stop 2\n");
          } 
        }

 


         if(pic->lram == P16E_SSPBUF)
         {
          pic->ram[P16E_SSPSTAT]|=0x04; //R/W
          //printf("SPPBUF write (%#02X)!!!!\n",pic->ram[SSPBUF]);	
          pic->ssp_bit=0;
          pic->pins[pic->sdi-1].dir=PD_OUT; 	
          pic->ram[P16E_SSPSTAT]|=0x01; //BF
         } 	
       
         if(!(pic->ram[P16E_SSPCON2] & 0x08)) pic->ssp_scka=0;

         if((pic->ram[P16E_SSPCON2] & 0x08) && (pic->ssp_scka == 0))
         {
           pic->ssp_bit=0;

           //printf("read\n");
           pic->ram[P16E_SSPBUF]=0;
           pic->pins[pic->sdi-1].dir=PD_IN; 	
           pic->ssp_ck=pic->pins[pic->sck-1].value;
           pic->ram[P16E_SSPSTAT]&=~0x01; //BF

           pic->ssp_scka=1;
         }


        if(pic->ssp_sck > pic->ram[P16E_SSPADD])
        {
           pic->ssp_sck=0;

         //write
         if(( (pic->ram[P16E_SSPSTAT] & 0x04) )&&( pic->ssp_bit <= 9))
         {
            pic->pins[pic->sck-1].value^=0x01;


            if((pic->pins[pic->sck-1].value == 0)&&(pic->ssp_bit <= 8))
            {
              pic->pins[pic->sdi-1].value=(pic->ram[P16E_SSPBUF] & (0x01<<(7-pic->ssp_bit))) >0; 
              pic->ssp_bit++;
              if(pic->ssp_bit ==9)
              { 
                pic->pins[pic->sdi-1].dir=PD_IN;
              } 
            }


            if((pic->pins[pic->sck-1].value == 1)&&(pic->ssp_bit  > 8))
            {
              if(pic->pins[pic->sdi-1].value)
                pic->ram[P16E_SSPCON2]|=0x40; //ACKSTAT
              else
                pic->ram[P16E_SSPCON2]&=~0x40; //ACKSTAT

              pic->ram[P16E_SSPSTAT]&=~0x04; //R/W
              (*pic->P16Emap.PIR1)|=0x08;//SSPIF
              pic->ram[P16E_SSPSTAT]&=~0x01; //BF
              pic->ssp_bit++;
            }

       //    printf("wbit(%i)  sck=%i  sda=%i \n",pic->ssp_bit,pic->pins[pic->sck-1].value,pic->pins[pic->sdi-1].value); 
         }
       
       //read 
         if(((pic->ram[P16E_SSPCON2] & 0x08)||(pic->ram[P16E_SSPCON2]& 0x10))&&( pic->ssp_bit <= 9))
         {
            //printf("sck 1 =%i\n", pic->pins[pic->sck-1].value);
            pic->ssp_ck^=0x01;
            pic->pins[pic->sck-1].value=pic->ssp_ck;
            //printf("sck 2 =%i\n", pic->pins[pic->sck-1].value);

            if((pic->pins[pic->sck-1].value == 0)&&(pic->ssp_bit <= 8))
            {
              pic->ssp_bit++;
            }

            if((pic->pins[pic->sck-1].value == 1)&&(pic->ssp_bit <= 8))
            {
              pic->ram[P16E_SSPBUF]|=(pic->pins[pic->sdi-1].value << (8 -pic->ssp_bit));             
              if(pic->ssp_bit == 8)
              {
                 pic->ram[P16E_SSPCON2]&=~0x10;//ACKDT
                 (*pic->P16Emap.PIR1)|=0x08;//SSPIF
                 pic->ssp_bit++;
               
                  pic->ram[P16E_SSPCON2]&=~0x08;
                 pic->ram[P16E_SSPSTAT]|=0x01; //BF
                 //printf("recebido1 %02X\n",pic->ram[SSPBUF]);
              }
            }

            if((pic->ram[P16E_SSPCON2]& 0x10)&&(pic->pins[pic->sck-1].value == 1)&&(pic->ssp_bit  > 8))
            {
              pic->pins[pic->sdi-1].dir=PD_OUT; 	
              pic->pins[pic->sdi-1].value=(pic->ram[P16E_SSPCON2]&0x20) >0 ;
              (*pic->P16Emap.PIR1)|=0x08;//SSPIF
              pic->ssp_bit++;

              pic->ram[P16E_SSPCON2]&=~0x10;//ACKDT

            }

         //  printf("rbit(%i)  sck=%i  sda=%i sdadir=%i\n",pic->ssp_bit,pic->pins[pic->sck-1].value,pic->pins[pic->sdi-1].value,pic->pins[pic->sdi-1].dir); 
         }
             
         if(pic->ssp_bit == 10)
         { 
          pic->pins[pic->sdi-1].dir=PD_OUT; 	
          pic->pins[pic->sdi-1].value=1; 	
          pic->ssp_bit++;
         }





       }
     }
     else //Unknown
     {
     printf(" %#02X SPI mode not implemented!\n",(pic->ram[P16E_SSPCON] & 0x0F));
	
     } 
  }
  else
  {
      pic->ssp_sck=0;
      pic->ssp_scka=0;
      pic->ssp_bit=0;
  }
  */
}
