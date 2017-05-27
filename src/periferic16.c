/* ########################################################################

   PICsim - PIC simulator

   ########################################################################

   Copyright (c) : 2008-2015  Luis Claudio Gamboa Lopes

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
#include"picsim.h"
#include"periferic16.h"



const int fpw2[]={1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072,262144,524288};


extern void pic_decode_16(void);

int 
pic_wr_pin16(unsigned char pin,unsigned char value)
{
   unsigned char val;

   if((pin-1) < pic->PINCOUNT)
   {
          pic->pins[(pin-1)].value=value;
          
          if(pic->pins[(pin-1)].port > 0)
          {
     	      val=0x01<<(pic->pins[(pin-1)].pord);
              if((pic->pins[(pin-1)].value) == 1)
                pic->ram[pic->pins[(pin-1)].port]|=val;
              else	
                pic->ram[pic->pins[(pin-1)].port]&=~val;
              if(pic->processor != P16F84A)
	        pic->ram[pic->pins[(pin-1)].port | 0x100]=pic->ram[pic->pins[(pin-1)].port]; //espelhamento bank2 = bank0
	   }

     return 1;
   } 
   else
     return 0;
};

inline static int interrupt16(void)
{
//interrupt
  //GIE
  if(pic->ram[P16_INTCON] & 0x80)
  {
    //T0IE  T0IF
    if((pic->ram[P16_INTCON]&0x20)&&(pic->ram[P16_INTCON]&0x04)) return 1;
    //INTE INTF
    if((pic->ram[P16_INTCON]&0x10)&&(pic->ram[P16_INTCON]&0x02)) return 1;
    //RBIE
    if((pic->ram[P16_INTCON]&0x08)&&(pic->ram[P16_INTCON]&0x01)) return 1;
    //PEIE	
    if(pic->ram[P16_INTCON] & 0x40)
    {
      //EEIE
      //if((pic->ram[P16_PIE1] & 0x80)&&(pic->ram[P16_PIR1] & 0x80)) return 1;
      //CMIE CMIF
      //if((pic->ram[P16_PIE1] & 0x40)&&(pic->ram[P16_PIR1] & 0x40)) return 1;
      //ADIE ADIF 
      if((pic->ram[P16_PIE1] & 0x40)&&(pic->ram[P16_PIR1] & 0x40)) return 1;
      //RCIE RCIF
      if((pic->ram[P16_PIE1] & 0x20)&&(pic->ram[P16_PIR1] & 0x20)) return 1;
      //TXIE TXIF
      if((pic->ram[P16_PIE1] & 0x10)&&(pic->ram[P16_PIR1] & 0x10)) return 1;
      //SSPIE
      if((pic->ram[P16_PIE1] & 0x08)&&(pic->ram[P16_PIR1] & 0x08)) return 1;
      //CCP1IE CCP1IF
      if((pic->ram[P16_PIE1] & 0x04)&&(pic->ram[P16_PIR1] & 0x04)) return 1;
      //TMR2IE TMR2IF
      if((pic->ram[P16_PIE1] & 0x02)&&(pic->ram[P16_PIR1] & 0x02)) return 1;
      //TMR1IE TMR1IF
      if((pic->ram[P16_PIE1] & 0x01)&&(pic->ram[P16_PIR1] & 0x01)) return 1;

      //CCP2IE CCP2IF
      if((pic->ram[P16_PIE2] & 0x01)&&(pic->ram[P16_PIR2] & 0x01)) return 1;
      //CCP3IE CCP3IF
      if((pic->ram[P16_PIE2] & 0x02)&&(pic->ram[P16_PIR2] & 0x02)) return 1;
    }
  
  }

 return 0;
}

void
periferic16_rst(void)
{

pic->debug=0;

pic->cp0=0;
pic->cp1=0;
pic->cp2=0;
pic->cp2_=0;
pic->cp3=0;

pic->t2pr=0;

pic->adcstep=0;
pic->adcon1=0xFF;

pic->twdt=0;

pic->ee_wr=0;

pic->porta=129;//dummy value to be changed
pic->portb=129;
pic->portc=129;
pic->portd=129;
pic->porte=129;

pic->trisa=129;
pic->trisb=129;
pic->trisc=129;
pic->trisd=129;
pic->trise=129;



pic->ssp_sck=0;
pic->ssp_scka=0;
pic->sspsr=0;
pic->ssp_bit=0;
pic->sspsr =0;
                  
pic->sstep=0;          
pic->dbg=5; 

pic->intlv=0;

pic->int0v=0;
pic->int1v=0;
pic->int2v=0;

pic->portbm=0;

pic->frst=1;

pic->s_open=1;

}


void 
periferic16_step_in(void)
{
//int i;
float val;
int chn;
short dval;
unsigned char temp;

//DEBUG
 if((pic->config[0] & 0x0800) == 0) //DEBUG ON
 {
   if(pic->debug == 1)pic->ram[P16_ICKBUG]|=0x80;
   pic->ram[P16_TRISB]|=0xC0;
 } 



if((pic->processor == P16F877)||(pic->processor == P16F877A)||(pic->processor == P16F777))
{
//MSSP

 if((pic->ram[P16_SSPCON] & 0x20) ==0x20) //SSPEN
 {
    
    if((pic->ram[P16_SSPCON] & 0x0F) ==0x05)//SLAVE Without SS
    {
   
      pic->pins[pic->sdi-1].dir=PD_IN; 	
 
      if(pic->rram == P16_SSPBUF)
      {
         pic->ram[P16_SSPSTAT]&=~0x01; //BF
      } 	

        pic->ssp_scka=pic->ssp_sck; 
        pic->ssp_sck= pic->pins[pic->sck-1].value;


	if((pic->ssp_scka == 0)&&(pic->ssp_sck == 1)) //CKP =0 CKE =0     //coloca saida na borda de subida
        {
           pic_wr_pin16(pic->sdo, ((pic->ram[P16_SSPBUF] & (1 <<(7-pic->ssp_bit))) > 0));
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
           pic->ram[P16_SSPBUF]=pic->sspsr;
           pic->sspsr =0;
	   pic->ram[P16_SSPSTAT]|=0x01; //BF
           
           //PSPIF
           pic->ram[P16_PIR1]|=0x08;
	   pic->ssp_bit=0;
        }
	

    }
    else if((pic->ram[P16_SSPCON] & 0x0F) ==0x08)//MASTER i2c
    {
      
       pic->ssp_sck++;

       if(pic->ssp_sck == ((pic->ram[P16_SSPADD]+1/2)-1))
       {
       
         if((pic->ram[P16_SSPCON2] & 0x01)) //start
         {
           pic->pins[pic->sck-1].dir=PD_OUT; 	
           pic->pins[pic->sdi-1].dir=PD_OUT; 	
           pic->pins[pic->sdi-1].value=1;
           pic->pins[pic->sck-1].value=1;
        
           //printf("I2C_start 1\n");
         }
         else if((pic->ram[P16_SSPCON2] & 0x02)) //restart
         {
           pic->pins[pic->sdi-1].dir=PD_OUT; 	
           pic->pins[pic->sdi-1].value=1;
           pic->pins[pic->sck-1].value=1;
           //printf("restar1\n");
         } 
         else if((pic->ram[P16_SSPCON2] & 0x04)) //stop
         {
           pic->pins[pic->sdi-1].dir=PD_OUT; 	
           pic->pins[pic->sdi-1].value=0;
           pic->pins[pic->sck-1].value=1;
           //printf("stop1\n");
         } 
       }

       if(pic->ssp_sck == ((pic->ram[P16_SSPADD]+1/2)+1))
       {
       
         if((pic->ram[P16_SSPCON2] & 0x01)) //start
         {
           pic->ram[P16_SSPCON2] &=~ 0x01;
           
           pic->pins[pic->sdi-1].value=0;
           pic->pins[pic->sck-1].value=1;
           
           //printf("start 2\n");
         }
         else if((pic->ram[P16_SSPCON2] & 0x02)) //restart
         {
           pic->ram[P16_SSPCON2] &=~ 0x02;

           pic->pins[pic->sdi-1].value=0;
           pic->pins[pic->sck-1].value=1;
           //printf("restart 2\n");
         } 
         else if((pic->ram[P16_SSPCON2] & 0x04)) //stop
         {
           pic->ram[P16_SSPCON2] &=~ 0x04;
         
           pic->ssp_bit=10;

           pic->pins[pic->sdi-1].value=1;
           pic->pins[pic->sck-1].value=1;
           //printf("stop 2\n");
         } 
       }

 


        if(pic->lram == P16_SSPBUF)
        {
         pic->ram[P16_SSPSTAT]|=0x04; //R/W
         //printf("SPPBUF write (%#02X)!!!!\n",pic->ram[SSPBUF]);	
         pic->ssp_bit=0;
         pic->pins[pic->sdi-1].dir=PD_OUT; 	
         pic->ram[P16_SSPSTAT]|=0x01; //BF
        } 	
       
        if(!(pic->ram[P16_SSPCON2] & 0x08)) pic->ssp_scka=0;

        if((pic->ram[P16_SSPCON2] & 0x08) && (pic->ssp_scka == 0))
        {
          pic->ssp_bit=0;

          //printf("read\n");
          pic->ram[P16_SSPBUF]=0;
          pic->pins[pic->sdi-1].dir=PD_IN; 	
          pic->ssp_ck=pic->pins[pic->sck-1].value;
          pic->ram[P16_SSPSTAT]&=~0x01; //BF

          pic->ssp_scka=1;
        }


       if(pic->ssp_sck > pic->ram[P16_SSPADD])
       {
          pic->ssp_sck=0;

        //write
        if(( (pic->ram[P16_SSPSTAT] & 0x04) )&&( pic->ssp_bit <= 9))
        {
           pic->pins[pic->sck-1].value^=0x01;


           if((pic->pins[pic->sck-1].value == 0)&&(pic->ssp_bit <= 8))
           {
             pic->pins[pic->sdi-1].value=(pic->ram[P16_SSPBUF] & (0x01<<(7-pic->ssp_bit))) >0; 
             pic->ssp_bit++;
             if(pic->ssp_bit ==9)
             { 
               pic->pins[pic->sdi-1].dir=PD_IN;
             } 
           }


           if((pic->pins[pic->sck-1].value == 1)&&(pic->ssp_bit  > 8))
           {
             if(pic->pins[pic->sdi-1].value)
               pic->ram[P16_SSPCON2]|=0x40; //ACKSTAT
             else
               pic->ram[P16_SSPCON2]&=~0x40; //ACKSTAT

             pic->ram[P16_SSPSTAT]&=~0x04; //R/W
             pic->ram[P16_PIR1]|=0x08;//SSPIF
             pic->ram[P16_SSPSTAT]&=~0x01; //BF
             pic->ssp_bit++;
           }

      //    printf("wbit(%i)  sck=%i  sda=%i \n",pic->ssp_bit,pic->pins[pic->sck-1].value,pic->pins[pic->sdi-1].value); 
        }
       
      //read 
        if(((pic->ram[P16_SSPCON2] & 0x08)||(pic->ram[P16_SSPCON2]& 0x10))&&( pic->ssp_bit <= 9))
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
             pic->ram[P16_SSPBUF]|=(pic->pins[pic->sdi-1].value << (8 -pic->ssp_bit));             
             if(pic->ssp_bit == 8)
             {
                pic->ram[P16_SSPCON2]&=~0x10;//ACKDT
                pic->ram[P16_PIR1]|=0x08;//SSPIF
                pic->ssp_bit++;
               
                 pic->ram[P16_SSPCON2]&=~0x08;
                pic->ram[P16_SSPSTAT]|=0x01; //BF
                //printf("recebido1 %02X\n",pic->ram[SSPBUF]);
             }
           }

           if((pic->ram[P16_SSPCON2]& 0x10)&&(pic->pins[pic->sck-1].value == 1)&&(pic->ssp_bit  > 8))
           {
             pic->pins[pic->sdi-1].dir=PD_OUT; 	
             pic->pins[pic->sdi-1].value=(pic->ram[P16_SSPCON2]&0x20) >0 ;
             pic->ram[P16_PIR1]|=0x08;//SSPIF
             pic->ssp_bit++;

             pic->ram[P16_SSPCON2]&=~0x10;//ACKDT

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
	printf(" %#02X SPI mode not implemented!\n",(pic->ram[P16_SSPCON] & 0x0F));
	
    } 
 }
 else
 {
     pic->ssp_sck=0;
     pic->ssp_scka=0;
     pic->ssp_bit=0;
 }



//ADC


  if(pic->ADCCOUNT > 0 )  
  {

  if((pic->ram[P16_ADCON0] & 0x05 ) == 0x05) // ADON and GO/DONE
  {
   pic->adcstep++;
   if(pic->adcstep > 10 )
   {

     if(pic->processor == P16F777)
     {
      chn=((pic->ram[P16_ADCON0]&0x02)<<2)|((pic->ram[P16_ADCON0]&0x38)>>3);
     } 
     else
     {
      chn=(pic->ram[P16_ADCON0]&0x38)>>3;
     }


     if(pic->pins[pic->adc[chn]-1].ptype == PT_ANALOG)
     {
       val=pic->pins[pic->adc[chn]-1].avalue;
     }
     else
     {
       val=0;
     }

      dval=((1023*val)/5.0);
   
      if((pic->ram[P16_ADCON1]&0x80) == 0x80)
      { 
        pic->ram[P16_ADRESH]=(dval & 0xFF00)>>8;   	
        pic->ram[P16_ADRESL]=(dval & 0x00FF);   	
      }
      else
      {
        dval= dval <<6;	
        pic->ram[P16_ADRESH]=(dval & 0xFF00)>>8;   	
        pic->ram[P16_ADRESL]=(dval & 0x00FF);   	
      }
    
      pic->ram[P16_ADCON0]&= ~0x04;
 
      //ADIF
      pic->ram[P16_PIR1]|=0x40;

      pic->adcstep=0;

     // printf("AD0=%02X AD1=%02X\n",pic->ram[ADCON0],pic->ram[ADCON1]);
     // printf("ADC conversion channel (%i)=%#04X (%08.3f)\n",chn,dval,val); 
    }
  }  
  else
  {
   pic->adcstep=0;
  }
    
  if((pic->ram[P16_ADCON1]&0x0F) != pic->adcon1)
  {

   if(pic->processor == P16F777)
   {
    switch(pic->ram[P16_ADCON1]&0x0F)
    {
      case 0:
      case 1:
	pic->pins[pic->adc[0]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[1]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[2]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[3]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[4]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[5]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[6]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[7]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[8]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[9]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[10]-1].ptype=PT_ANALOG;
	pic->pins[pic->adc[11]-1].ptype=PT_ANALOG;
	pic->pins[pic->adc[12]-1].ptype=PT_ANALOG;
	pic->pins[pic->adc[13]-1].ptype=PT_ANALOG;
	break;
      case 2:
	pic->pins[pic->adc[0]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[1]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[2]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[3]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[4]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[5]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[6]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[7]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[8]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[9]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[10]-1].ptype=PT_ANALOG;
	pic->pins[pic->adc[11]-1].ptype=PT_ANALOG;
	pic->pins[pic->adc[12]-1].ptype=PT_ANALOG;
	pic->pins[pic->adc[13]-1].ptype=PT_CMOS;
	break;
      case 3:
	pic->pins[pic->adc[0]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[1]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[2]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[3]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[4]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[5]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[6]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[7]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[8]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[9]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[10]-1].ptype=PT_ANALOG;
	pic->pins[pic->adc[11]-1].ptype=PT_ANALOG;
	pic->pins[pic->adc[12]-1].ptype=PT_CMOS;
	pic->pins[pic->adc[13]-1].ptype=PT_CMOS;
	break;
      case 4:
	pic->pins[pic->adc[0]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[1]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[2]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[3]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[4]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[5]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[6]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[7]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[8]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[9]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[10]-1].ptype=PT_ANALOG;
	pic->pins[pic->adc[11]-1].ptype=PT_CMOS;
	pic->pins[pic->adc[12]-1].ptype=PT_CMOS;
	pic->pins[pic->adc[13]-1].ptype=PT_CMOS;
	break;
      case 5:
	pic->pins[pic->adc[0]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[1]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[2]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[3]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[4]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[5]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[6]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[7]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[8]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[9]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[10]-1].ptype=PT_CMOS;
	pic->pins[pic->adc[11]-1].ptype=PT_CMOS;
	pic->pins[pic->adc[12]-1].ptype=PT_CMOS;
	pic->pins[pic->adc[13]-1].ptype=PT_CMOS;
	break;
      case 6:
	pic->pins[pic->adc[0]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[1]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[2]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[3]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[4]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[5]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[6]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[7]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[8]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[9]-1].ptype =PT_CMOS;
	pic->pins[pic->adc[10]-1].ptype=PT_CMOS;
	pic->pins[pic->adc[11]-1].ptype=PT_CMOS;
	pic->pins[pic->adc[12]-1].ptype=PT_CMOS;
	pic->pins[pic->adc[13]-1].ptype=PT_CMOS;
	break;
      case 7:
	pic->pins[pic->adc[0]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[1]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[2]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[3]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[4]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[5]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[6]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[7]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[8]-1].ptype =PT_CMOS;
	pic->pins[pic->adc[9]-1].ptype =PT_CMOS;
	pic->pins[pic->adc[10]-1].ptype=PT_CMOS;
	pic->pins[pic->adc[11]-1].ptype=PT_CMOS;
	pic->pins[pic->adc[12]-1].ptype=PT_CMOS;
	pic->pins[pic->adc[13]-1].ptype=PT_CMOS;
	break;
      case 8:
	pic->pins[pic->adc[0]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[1]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[2]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[3]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[4]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[5]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[6]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[7]-1].ptype =PT_CMOS;
	pic->pins[pic->adc[8]-1].ptype =PT_CMOS;
	pic->pins[pic->adc[9]-1].ptype =PT_CMOS;
	pic->pins[pic->adc[10]-1].ptype=PT_CMOS;
	pic->pins[pic->adc[11]-1].ptype=PT_CMOS;
	pic->pins[pic->adc[12]-1].ptype=PT_CMOS;
	pic->pins[pic->adc[13]-1].ptype=PT_CMOS;
	break;
      case 9:
	pic->pins[pic->adc[0]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[1]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[2]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[3]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[4]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[5]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[6]-1].ptype =PT_CMOS;
	pic->pins[pic->adc[7]-1].ptype =PT_CMOS;
	pic->pins[pic->adc[8]-1].ptype =PT_CMOS;
	pic->pins[pic->adc[9]-1].ptype =PT_CMOS;
	pic->pins[pic->adc[10]-1].ptype=PT_CMOS;
	pic->pins[pic->adc[11]-1].ptype=PT_CMOS;
	pic->pins[pic->adc[12]-1].ptype=PT_CMOS;
	pic->pins[pic->adc[13]-1].ptype=PT_CMOS;
	break;
      case 10:
	pic->pins[pic->adc[0]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[1]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[2]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[3]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[4]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[5]-1].ptype =PT_CMOS;
	pic->pins[pic->adc[6]-1].ptype =PT_CMOS;
	pic->pins[pic->adc[7]-1].ptype =PT_CMOS;
	pic->pins[pic->adc[8]-1].ptype =PT_CMOS;
	pic->pins[pic->adc[9]-1].ptype =PT_CMOS;
	pic->pins[pic->adc[10]-1].ptype=PT_CMOS;
	pic->pins[pic->adc[11]-1].ptype=PT_CMOS;
	pic->pins[pic->adc[12]-1].ptype=PT_CMOS;
	pic->pins[pic->adc[13]-1].ptype=PT_CMOS;
	break;
      case 11:
	pic->pins[pic->adc[0]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[1]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[2]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[3]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[4]-1].ptype =PT_CMOS;
	pic->pins[pic->adc[5]-1].ptype =PT_CMOS;
	pic->pins[pic->adc[6]-1].ptype =PT_CMOS;
	pic->pins[pic->adc[7]-1].ptype =PT_CMOS;
	pic->pins[pic->adc[8]-1].ptype =PT_CMOS;
	pic->pins[pic->adc[9]-1].ptype =PT_CMOS;
	pic->pins[pic->adc[10]-1].ptype=PT_CMOS;
	pic->pins[pic->adc[11]-1].ptype=PT_CMOS;
	pic->pins[pic->adc[12]-1].ptype=PT_CMOS;
	pic->pins[pic->adc[13]-1].ptype=PT_CMOS;
	break;
      case 12:
	pic->pins[pic->adc[0]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[1]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[2]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[3]-1].ptype =PT_CMOS;
	pic->pins[pic->adc[4]-1].ptype =PT_CMOS;
	pic->pins[pic->adc[5]-1].ptype =PT_CMOS;
	pic->pins[pic->adc[6]-1].ptype =PT_CMOS;
	pic->pins[pic->adc[7]-1].ptype =PT_CMOS;
	pic->pins[pic->adc[8]-1].ptype =PT_CMOS;
	pic->pins[pic->adc[9]-1].ptype =PT_CMOS;
	pic->pins[pic->adc[10]-1].ptype=PT_CMOS;
	pic->pins[pic->adc[11]-1].ptype=PT_CMOS;
	pic->pins[pic->adc[12]-1].ptype=PT_CMOS;
	pic->pins[pic->adc[13]-1].ptype=PT_CMOS;
	break;
      case 13:
	pic->pins[pic->adc[0]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[1]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[2]-1].ptype =PT_CMOS;
	pic->pins[pic->adc[3]-1].ptype =PT_CMOS;
	pic->pins[pic->adc[4]-1].ptype =PT_CMOS;
	pic->pins[pic->adc[5]-1].ptype =PT_CMOS;
	pic->pins[pic->adc[6]-1].ptype =PT_CMOS;
	pic->pins[pic->adc[7]-1].ptype =PT_CMOS;
	pic->pins[pic->adc[8]-1].ptype =PT_CMOS;
	pic->pins[pic->adc[9]-1].ptype =PT_CMOS;
	pic->pins[pic->adc[10]-1].ptype=PT_CMOS;
	pic->pins[pic->adc[11]-1].ptype=PT_CMOS;
	pic->pins[pic->adc[12]-1].ptype=PT_CMOS;
	pic->pins[pic->adc[13]-1].ptype=PT_CMOS;
	break;
      case 14:
	pic->pins[pic->adc[0]-1].ptype =PT_ANALOG;
	pic->pins[pic->adc[1]-1].ptype =PT_CMOS;
	pic->pins[pic->adc[2]-1].ptype =PT_CMOS;
	pic->pins[pic->adc[3]-1].ptype =PT_CMOS;
	pic->pins[pic->adc[4]-1].ptype =PT_CMOS;
	pic->pins[pic->adc[5]-1].ptype =PT_CMOS;
	pic->pins[pic->adc[6]-1].ptype =PT_CMOS;
	pic->pins[pic->adc[7]-1].ptype =PT_CMOS;
	pic->pins[pic->adc[8]-1].ptype =PT_CMOS;
	pic->pins[pic->adc[9]-1].ptype =PT_CMOS;
	pic->pins[pic->adc[10]-1].ptype=PT_CMOS;
	pic->pins[pic->adc[11]-1].ptype=PT_CMOS;
	pic->pins[pic->adc[12]-1].ptype=PT_CMOS;
	pic->pins[pic->adc[13]-1].ptype=PT_CMOS;
	break;
      case 15:
	pic->pins[pic->adc[0]-1].ptype =PT_CMOS;
	pic->pins[pic->adc[1]-1].ptype =PT_CMOS;
	pic->pins[pic->adc[2]-1].ptype =PT_CMOS;
	pic->pins[pic->adc[3]-1].ptype =PT_CMOS;
	pic->pins[pic->adc[4]-1].ptype =PT_CMOS;
	pic->pins[pic->adc[5]-1].ptype =PT_CMOS;
	pic->pins[pic->adc[6]-1].ptype =PT_CMOS;
	pic->pins[pic->adc[7]-1].ptype =PT_CMOS;
	pic->pins[pic->adc[8]-1].ptype =PT_CMOS;
	pic->pins[pic->adc[9]-1].ptype =PT_CMOS;
	pic->pins[pic->adc[10]-1].ptype=PT_CMOS;
	pic->pins[pic->adc[11]-1].ptype=PT_CMOS;
	pic->pins[pic->adc[12]-1].ptype=PT_CMOS;
	pic->pins[pic->adc[13]-1].ptype=PT_CMOS;
	break;
     }
   }
   else
   { 
    switch(pic->ram[P16_ADCON1]&0x0F)
    {
      case 0:
	pic->pins[pic->adc[0]-1].ptype=PT_ANALOG;
	pic->pins[pic->adc[1]-1].ptype=PT_ANALOG;
	pic->pins[pic->adc[2]-1].ptype=PT_ANALOG;
	pic->pins[pic->adc[3]-1].ptype=PT_ANALOG;
	pic->pins[pic->adc[4]-1].ptype=PT_ANALOG;
	pic->pins[pic->adc[5]-1].ptype=PT_ANALOG;
	pic->pins[pic->adc[6]-1].ptype=PT_ANALOG;
	pic->pins[pic->adc[7]-1].ptype=PT_ANALOG;
	break;
      case 1:
	pic->pins[pic->adc[0]-1].ptype=PT_ANALOG;
	pic->pins[pic->adc[1]-1].ptype=PT_ANALOG;
	pic->pins[pic->adc[2]-1].ptype=PT_ANALOG;
	pic->pins[pic->adc[3]-1].ptype=PT_ANAREF;
	pic->pins[pic->adc[4]-1].ptype=PT_ANALOG;
	pic->pins[pic->adc[5]-1].ptype=PT_ANALOG;
	pic->pins[pic->adc[6]-1].ptype=PT_ANALOG;
	pic->pins[pic->adc[7]-1].ptype=PT_ANALOG;
	break;
      case 2:
	pic->pins[pic->adc[0]-1].ptype=PT_ANALOG;
	pic->pins[pic->adc[1]-1].ptype=PT_ANALOG;
	pic->pins[pic->adc[2]-1].ptype=PT_ANALOG;
	pic->pins[pic->adc[3]-1].ptype=PT_ANALOG;
	pic->pins[pic->adc[4]-1].ptype=PT_ANALOG;
	pic->pins[pic->adc[5]-1].ptype=PT_CMOS;
	pic->pins[pic->adc[6]-1].ptype=PT_CMOS;
	pic->pins[pic->adc[7]-1].ptype=PT_CMOS;
	break;
      case 3:
	pic->pins[pic->adc[0]-1].ptype=PT_ANALOG;
	pic->pins[pic->adc[1]-1].ptype=PT_ANALOG;
	pic->pins[pic->adc[2]-1].ptype=PT_ANALOG;
	pic->pins[pic->adc[3]-1].ptype=PT_ANAREF;
	pic->pins[pic->adc[4]-1].ptype=PT_ANALOG;
	pic->pins[pic->adc[5]-1].ptype=PT_CMOS;
	pic->pins[pic->adc[6]-1].ptype=PT_CMOS;
	pic->pins[pic->adc[7]-1].ptype=PT_CMOS;
	break;
      case 4:
	pic->pins[pic->adc[0]-1].ptype=PT_ANALOG;
	pic->pins[pic->adc[1]-1].ptype=PT_ANALOG;
	pic->pins[pic->adc[2]-1].ptype=PT_CMOS;
	pic->pins[pic->adc[3]-1].ptype=PT_ANALOG;
	pic->pins[pic->adc[4]-1].ptype=PT_CMOS;
	pic->pins[pic->adc[5]-1].ptype=PT_CMOS;
	pic->pins[pic->adc[6]-1].ptype=PT_CMOS;
	pic->pins[pic->adc[7]-1].ptype=PT_CMOS;
	break;
      case 5:
	pic->pins[pic->adc[0]-1].ptype=PT_ANALOG;
	pic->pins[pic->adc[1]-1].ptype=PT_ANALOG;
	pic->pins[pic->adc[2]-1].ptype=PT_CMOS;
	pic->pins[pic->adc[3]-1].ptype=PT_ANAREF;
	pic->pins[pic->adc[4]-1].ptype=PT_CMOS;
	pic->pins[pic->adc[5]-1].ptype=PT_CMOS;
	pic->pins[pic->adc[6]-1].ptype=PT_CMOS;
	pic->pins[pic->adc[7]-1].ptype=PT_CMOS;
	break;
      case 6:
      case 7:
	pic->pins[pic->adc[0]-1].ptype=PT_CMOS;
	pic->pins[pic->adc[1]-1].ptype=PT_CMOS;
	pic->pins[pic->adc[2]-1].ptype=PT_CMOS;
	pic->pins[pic->adc[3]-1].ptype=PT_CMOS;
	pic->pins[pic->adc[4]-1].ptype=PT_CMOS;
	pic->pins[pic->adc[5]-1].ptype=PT_CMOS;
	pic->pins[pic->adc[6]-1].ptype=PT_CMOS;
	pic->pins[pic->adc[7]-1].ptype=PT_CMOS;
	break;
      case 8:
	pic->pins[pic->adc[0]-1].ptype=PT_ANALOG;
	pic->pins[pic->adc[1]-1].ptype=PT_ANALOG;
	pic->pins[pic->adc[2]-1].ptype=PT_ANAREF;
	pic->pins[pic->adc[3]-1].ptype=PT_ANAREF;
	pic->pins[pic->adc[4]-1].ptype=PT_ANALOG;
	pic->pins[pic->adc[5]-1].ptype=PT_ANALOG;
	pic->pins[pic->adc[6]-1].ptype=PT_ANALOG;
	pic->pins[pic->adc[7]-1].ptype=PT_ANALOG;
	break;
      case 9:
	pic->pins[pic->adc[0]-1].ptype=PT_ANALOG;
	pic->pins[pic->adc[1]-1].ptype=PT_ANALOG;
	pic->pins[pic->adc[2]-1].ptype=PT_ANALOG;
	pic->pins[pic->adc[3]-1].ptype=PT_ANALOG;
	pic->pins[pic->adc[4]-1].ptype=PT_ANALOG;
	pic->pins[pic->adc[5]-1].ptype=PT_ANALOG;
	pic->pins[pic->adc[6]-1].ptype=PT_CMOS;
	pic->pins[pic->adc[7]-1].ptype=PT_CMOS;
	break;
      case 10:
	pic->pins[pic->adc[0]-1].ptype=PT_ANALOG;
	pic->pins[pic->adc[1]-1].ptype=PT_ANALOG;
	pic->pins[pic->adc[2]-1].ptype=PT_ANALOG;
	pic->pins[pic->adc[3]-1].ptype=PT_ANAREF;
	pic->pins[pic->adc[4]-1].ptype=PT_ANALOG;
	pic->pins[pic->adc[5]-1].ptype=PT_ANALOG;
	pic->pins[pic->adc[6]-1].ptype=PT_CMOS;
	pic->pins[pic->adc[7]-1].ptype=PT_CMOS;
	break;
      case 11:
	pic->pins[pic->adc[0]-1].ptype=PT_ANALOG;
	pic->pins[pic->adc[1]-1].ptype=PT_ANALOG;
	pic->pins[pic->adc[2]-1].ptype=PT_ANAREF;
	pic->pins[pic->adc[3]-1].ptype=PT_ANAREF;
	pic->pins[pic->adc[4]-1].ptype=PT_ANALOG;
	pic->pins[pic->adc[5]-1].ptype=PT_ANALOG;
	pic->pins[pic->adc[6]-1].ptype=PT_CMOS;
	pic->pins[pic->adc[7]-1].ptype=PT_CMOS;
	break;
      case 12:
	pic->pins[pic->adc[0]-1].ptype=PT_ANALOG;
	pic->pins[pic->adc[1]-1].ptype=PT_ANALOG;
	pic->pins[pic->adc[2]-1].ptype=PT_ANAREF;
	pic->pins[pic->adc[3]-1].ptype=PT_ANAREF;
	pic->pins[pic->adc[4]-1].ptype=PT_ANALOG;
	pic->pins[pic->adc[5]-1].ptype=PT_CMOS;
	pic->pins[pic->adc[6]-1].ptype=PT_CMOS;
	pic->pins[pic->adc[7]-1].ptype=PT_CMOS;
	break;
      case 13:
	pic->pins[pic->adc[0]-1].ptype=PT_ANALOG;
	pic->pins[pic->adc[1]-1].ptype=PT_ANALOG;
	pic->pins[pic->adc[2]-1].ptype=PT_ANAREF;
	pic->pins[pic->adc[3]-1].ptype=PT_ANAREF;
	pic->pins[pic->adc[4]-1].ptype=PT_CMOS;
	pic->pins[pic->adc[5]-1].ptype=PT_CMOS;
	pic->pins[pic->adc[6]-1].ptype=PT_CMOS;
	pic->pins[pic->adc[7]-1].ptype=PT_CMOS;
	break;
      case 14:
	pic->pins[pic->adc[0]-1].ptype=PT_ANALOG;
	pic->pins[pic->adc[1]-1].ptype=PT_CMOS;
	pic->pins[pic->adc[2]-1].ptype=PT_CMOS;
	pic->pins[pic->adc[3]-1].ptype=PT_CMOS;
	pic->pins[pic->adc[4]-1].ptype=PT_CMOS;
	pic->pins[pic->adc[5]-1].ptype=PT_CMOS;
	pic->pins[pic->adc[6]-1].ptype=PT_CMOS;
	pic->pins[pic->adc[7]-1].ptype=PT_CMOS;
	break;
      case 15:
	pic->pins[pic->adc[0]-1].ptype=PT_ANALOG;
	pic->pins[pic->adc[1]-1].ptype=PT_CMOS;
	pic->pins[pic->adc[2]-1].ptype=PT_ANAREF;
	pic->pins[pic->adc[3]-1].ptype=PT_ANAREF;
	pic->pins[pic->adc[4]-1].ptype=PT_CMOS;
	pic->pins[pic->adc[5]-1].ptype=PT_CMOS;
	pic->pins[pic->adc[6]-1].ptype=PT_CMOS;
	pic->pins[pic->adc[7]-1].ptype=PT_CMOS;
	break;
    }
   } 

    pic->adcon1=pic->ram[P16_ADCON1]&0x0F;	
   }
  
  };

}//endif P16F877 P16F877A P16F777


//INT
 
   if((pic->pins[pic->int0-1].dir == PD_IN)&&(pic->pins[pic->int0-1].value  != pic->int0v))
   {
     if(((!pic->int0v) &&(pic->ram[P16_OPTION] & 0x40))||((pic->int0v) && (!(pic->ram[P16_OPTION] & 0x40))))
     {
        pic->ram[(0x0000)|(P16_INTCON & 0x007F)]|=0x02;//INTF
        pic->ram[(0x0080)|(P16_INTCON & 0x007F)]|=0x02;
        pic->ram[(0x0100)|(P16_INTCON & 0x007F)]|=0x02;
        pic->ram[(0x0180)|(P16_INTCON & 0x007F)]|=0x02;
     } 
   } 
   pic->int0v=pic->pins[pic->int0-1].value;


//PORTB
   temp=pic->ram[P16_TRISB]&0xF0;
   if((pic->ram[P16_PORTB]&temp) != (pic->portb&temp)) 
   {
     pic->portbm=1; 
   }


if(pic->rram == P16_PORTB)
{
  pic->portbm=0;
/* Only disable mismatch
  pic->ram[(0x0000)|(INTCON & 0x007F)]&=~0x01;//RBIF
  pic->ram[(0x0080)|(INTCON & 0x007F)]&=~0x01;
  pic->ram[(0x0100)|(INTCON & 0x007F)]&=~0x01;
  pic->ram[(0x0180)|(INTCON & 0x007F)]&=~0x01;
*/
}

if(pic->portbm)
{
  pic->ram[(0x0000)|(P16_INTCON & 0x007F)]|=0x01;//RBIF
  pic->ram[(0x0080)|(P16_INTCON & 0x007F)]|=0x01;
  if(pic->processor != P16F84A)
  {
    pic->ram[(0x0100)|(P16_INTCON & 0x007F)]|=0x01;
    pic->ram[(0x0180)|(P16_INTCON & 0x007F)]|=0x01;
  }
}  



 


//TMR0

  if(((pic->ram[P16_OPTION] & 0x20) == 0x00 )||  //TOCS=FOSC/4
    (((pic->ram[P16_OPTION] & 0x30) == 0x20 )&&((pic->t0cki_ == 0)&&(pic->pins[pic->t0cki-1].value == 1)))|| //T0CS=t0cki  T0SE =0
    (((pic->ram[P16_OPTION] & 0x30) == 0x30 )&&((pic->t0cki_ == 1)&&(pic->pins[pic->t0cki-1].value == 0))))  //T0CS=t0cki  T0SE =1
  {
     pic->cp0++;

     if(pic->lram == P16_TMR0)pic->cp0=0; //RESET prescaler	 

     if((pic->ram[P16_OPTION] & 0x08) == 0x08) //PSA
     {                                   
        if(((pic->ram[P16_TMR0]+1) == 0x100))
        {
             pic->ram[(0x0000)|(P16_INTCON & 0x007F)]|=0x04;//T0IF
             pic->ram[(0x0080)|(P16_INTCON & 0x007F)]|=0x04;
             if(pic->processor != P16F84A)
             { 
               pic->ram[(0x0100)|(P16_INTCON & 0x007F)]|=0x04;
               pic->ram[(0x0180)|(P16_INTCON & 0x007F)]|=0x04;
             }; 
        }
        pic->ram[P16_TMR0]++;
        pic->cp0=0;
     }
     else
     { 
        if(pic->cp0 >= 2*(fpw2[pic->ram[P16_OPTION]&0x07]) )
        {
          if(((pic->ram[P16_TMR0]+1) == 0x100))
          {
             pic->ram[(0x0000)|(P16_INTCON & 0x007F)]|=0x04;//T0IF
             pic->ram[(0x0080)|(P16_INTCON & 0x007F)]|=0x04;
             if(pic->processor != P16F84A)
             { 
               pic->ram[(0x0100)|(P16_INTCON & 0x007F)]|=0x04;
               pic->ram[(0x0180)|(P16_INTCON & 0x007F)]|=0x04;
             }
          }
          pic->ram[P16_TMR0]++;
          pic->cp0=0;
        }
     }
  } 
  pic->t0cki_=pic->pins[pic->t0cki-1].value;


if(pic->processor != P16F84A)
{
//TMR1

  if(((pic->ram[P16_T1CON] & 0x03) == 0x01 )||  //TMRICS=FOSC/4 TMREN=1
    (((pic->ram[P16_T1CON] & 0x03) == 0x03 )&&((pic->t1cki_ == 0)&&(pic->pins[pic->t1cki-1].value == 1)))) //TMRICS=t1cki  TMREN=1
  {
     pic->cp1++;
     
     if(pic->cp1 >= fpw2[(pic->ram[P16_T1CON]&0x30)>>4]) 
     {
       pic->ram[P16_TMR1L]++;
       if(pic->ram[P16_TMR1L] == 0)
       {
        if((pic->ram[P16_TMR1H]+1) == 0x100)pic->ram[P16_PIR1]|=0x01;//TMR1IF
        pic->ram[P16_TMR1H]++;
       }
       pic->cp1=0;
     }

//CCP - only when TMR1 is ON
//CCP1 compare modes 
     if((pic->CCPCOUNT >= 1)&&(pic->ccp[0] > 0)&&((pic->ram[P16_CCP1CON] & 0x0C) == 0x08))
     {
       if((pic->ram[P16_TMR1H]==pic->ram[P16_CCPR1H])&&(pic->ram[P16_TMR1L]==pic->ram[P16_CCPR1L]))//match !!
       {
          pic->ram[P16_PIR1]|=0x04;//CCP1IF
          switch(pic->ram[P16_CCP1CON] & 0x03)
          {
            case 0://set output
              if(pic->pins[pic->ccp[0]-1].dir == PD_OUT)
                pic->ram[pic->pins[(pic->ccp[0]-1)].port]|=0x01<<(pic->pins[(pic->ccp[0]-1)].pord);
              break;
            case 1://clear output
              if(pic->pins[pic->ccp[0]-1].dir == PD_OUT)
                pic->ram[pic->pins[(pic->ccp[0]-1)].port]&=~(0x01<<(pic->pins[(pic->ccp[0]-1)].pord));
              break;
            case 2://software interrupt
              break;
            case 3://trigger special event
              pic->ram[P16_TMR1H]=0;
              pic->ram[P16_TMR1L]=0;
              break;
          }
       }
     }
//CCP2 compare modes 
     if((pic->CCPCOUNT >= 2)&&(pic->ccp[1] > 0)&&((pic->ram[P16_CCP2CON] & 0x0C) == 0x08))
     {
       if((pic->ram[P16_TMR1H]==pic->ram[P16_CCPR2H])&&(pic->ram[P16_TMR1L]==pic->ram[P16_CCPR2L]))//match !!
       {
          pic->ram[P16_PIR2]|=0x01;//CCP2IF
          switch(pic->ram[P16_CCP2CON] & 0x03)
          {
            case 0://set output
              if(pic->pins[pic->ccp[1]-1].dir == PD_OUT)
                pic->ram[pic->pins[(pic->ccp[1]-1)].port]|=0x01<<(pic->pins[(pic->ccp[1]-1)].pord);
              break;
            case 1://clear output
              if(pic->pins[pic->ccp[1]-1].dir == PD_OUT)
                pic->ram[pic->pins[(pic->ccp[1]-1)].port]&=~(0x01<<(pic->pins[(pic->ccp[1]-1)].pord));
              break;
            case 2://software interrupt
              break;
            case 3://trigger special event
              pic->ram[P16_TMR1H]=0;
              pic->ram[P16_TMR1L]=0;
              if(pic->ram[P16_ADCON0] & 0x01)pic->ram[P16_ADCON0]|=0x04; //if ad on, enable one conversion
              break;
          }
       }
     }
//CCP3 compare modes 
     if((pic->CCPCOUNT >= 3)&&(pic->ccp[2] > 0)&&((pic->ram[P16_CCP3CON] & 0x0C) == 0x08))
     {
       if((pic->ram[P16_TMR1H]==pic->ram[P16_CCPR3H])&&(pic->ram[P16_TMR1L]==pic->ram[P16_CCPR3L]))//match !!
       {
          pic->ram[P16_PIR2]|=0x02;//CCP3IF
          switch(pic->ram[P16_CCP3CON] & 0x03)
          {
            case 0://set output
              if(pic->pins[pic->ccp[2]-1].dir == PD_OUT)
                pic->ram[pic->pins[(pic->ccp[2]-1)].port]|=0x01<<(pic->pins[(pic->ccp[2]-1)].pord);
              break;
            case 1://clear output
              if(pic->pins[pic->ccp[2]-1].dir == PD_OUT)
                pic->ram[pic->pins[(pic->ccp[2]-1)].port]&=~(0x01<<(pic->pins[(pic->ccp[2]-1)].pord));
              break;
            case 2://software interrupt
              break;
            case 3://trigger special event
              pic->ram[P16_TMR1H]=0;
              pic->ram[P16_TMR1L]=0;
              break;
          }
       }
     }


  } 

  pic->t1cki_=pic->pins[pic->t1cki-1].value;
 
//TMR2

  if((pic->ram[P16_T2CON] & 0x04) == 0x04 )  //TMR2EN
  {
     pic->cp2++;
     
     if((pic->ram[P16_T2CON]&0x02) == 0x02)
     {
       pic->t2pr=16;
     }
     else if ((pic->ram[P16_T2CON]&0x01) == 0x01)
     {
       pic->t2pr=4;
     }
     else
     {
       pic->t2pr=1;
     }

     if(pic->cp2 >= pic->t2pr) 
     {
       pic->ram[P16_TMR2]++;
       if(pic->ram[P16_TMR2] == pic->ram[P16_PR2])
       {
         pic->ram[P16_TMR2]=0;
         pic->cp2_++;

         if(pic->cp2_ >= (((pic->ram[P16_T2CON]&0x78)>>3)+1) )
         { 
           pic->ram[P16_PIR1]|=0x02;//TMR2IF
           pic->cp2_=0;
         }

         //PWM
          	
	 if((pic->CCPCOUNT >= 1)&&(pic->ccp[0] > 0)&&(pic->ram[P16_CCP1CON]& 0x0C) == 0x0C)
         {
           pic->ram[P16_CCPR1H]=pic->ram[P16_CCPR1L];
           if(pic->pins[pic->ccp[0]-1].dir == PD_OUT)
             pic->ram[pic->pins[(pic->ccp[0]-1)].port]|=0x01<<(pic->pins[(pic->ccp[0]-1)].pord);
         } 
	 
         if((pic->CCPCOUNT >= 2)&&(pic->ccp[1] > 0)&&(pic->ram[P16_CCP2CON]& 0x0C) == 0x0C)
         {
           pic->ram[P16_CCPR2H]=pic->ram[P16_CCPR2L];
           if(pic->pins[pic->ccp[1]-1].dir == PD_OUT)
             pic->ram[pic->pins[(pic->ccp[1]-1)].port]|=0x01<<(pic->pins[(pic->ccp[1]-1)].pord);
         } 
         
         if((pic->CCPCOUNT >= 3)&&(pic->ccp[2] > 0)&&(pic->ram[P16_CCP3CON]& 0x0C) == 0x0C)
         {
           pic->ram[P16_CCPR3H]=pic->ram[P16_CCPR3L];
           if(pic->pins[pic->ccp[2]-1].dir == PD_OUT)
             pic->ram[pic->pins[(pic->ccp[2]-1)].port]|=0x01<<(pic->pins[(pic->ccp[2]-1)].pord);
         } 
	
       }
       pic->cp2=0;
     }
//PWM - only if TMR2 is on

//only use 8 bits ! not 10 bits  
   if((pic->CCPCOUNT >= 1)&&(pic->ccp[0] > 0)&&(pic->ram[P16_CCP1CON]& 0x0C) == 0x0C)
   {
      if(pic->ram[P16_TMR2] >=  pic->ram[P16_CCPR1H])
      {
        if(pic->pins[pic->ccp[0]-1].dir == PD_OUT)
          pic->ram[pic->pins[(pic->ccp[0]-1)].port]&=~(0x01<<(pic->pins[(pic->ccp[0]-1)].pord));
      }
   }	
   
   if((pic->CCPCOUNT >= 2)&&(pic->ccp[1] > 0)&&(pic->ram[P16_CCP2CON]& 0x0C) == 0x0C)
   {
      if(pic->ram[P16_TMR2] >=  pic->ram[P16_CCPR2H])
      {
        if(pic->pins[pic->ccp[1]-1].dir == PD_OUT)
          pic->ram[pic->pins[(pic->ccp[1]-1)].port]&=~(0x01<<(pic->pins[(pic->ccp[1]-1)].pord));
      }
   }	
   
   if((pic->CCPCOUNT >= 3)&&(pic->ccp[2] > 0)&&(pic->ram[P16_CCP3CON]& 0x0C) == 0x0C)
   {
      if(pic->ram[P16_TMR2] >=  pic->ram[P16_CCPR3H])
      {
        if(pic->pins[pic->ccp[2]-1].dir == PD_OUT)
          pic->ram[pic->pins[(pic->ccp[2]-1)].port]&=~(0x01<<(pic->pins[(pic->ccp[2]-1)].pord));
      }
   }	


  } 


} //end if P16F84A

//EEPROM

if((pic->processor == P16F628)||(pic->processor == P16F628A))
{
  if((pic->ram[P16_P628_EECON1] & 0x04) == 0x04 )
  {
    if(pic->ram[P16_P628_EECON2] != 0 )
    {
      if(pic->ram[P16_P628_EECON2] == 0x55 )
      {
        pic->ram[P16_P628_EECON2] = 0; 
        pic->ee_wr=-1;
      }
      else
      {
        if((pic->ram[P16_P628_EECON2] == 0xAA )&&(pic->ee_wr == -1))
        {
          pic->ram[P16_P628_EECON2] = 0; 
          pic->ee_wr=1;
        }
        else
        {
          pic->ram[P16_P628_EECON2] = 0; 
          pic->ee_wr=0;
        }
      }
    }    
  }

  if((pic->ram[P16_P628_EECON1] & 0x03) != 0x00 )
  {
    if((pic->ram[P16_P628_EECON1] & 0x01) == 0x01 ) //RD
    {
      pic->ram[P16_P628_EEDATA]= pic->eeprom[pic->ram[P16_P628_EEADR]];
      pic->ram[P16_P628_EECON1]&=~0x01;  
    }
    else
    {
      if(pic->ee_wr == 1)
      {
        pic->eeprom[pic->ram[P16_P628_EEADR]]=pic->ram[P16_P628_EEDATA];       
        pic->ram[P16_P628_EECON1]&=~0x02; 
        pic->ee_wr=0;
      } 
    }
  } 
}
else if((pic->processor == P16F877)||(pic->processor == P16F877A))
{

  if((pic->ram[P16_P877_EECON1] & 0x04) == 0x04 )
  {
    if(pic->ram[P16_P877_EECON2] != 0 )
    {
      if(pic->ram[P16_P877_EECON2] == 0x55 )
      {
        pic->ram[P16_P877_EECON2] = 0; 
        pic->ee_wr=-1;
      }
      else
      {
        if((pic->ram[P16_P877_EECON2] == 0xAA )&&(pic->ee_wr == -1))
        {
          pic->ram[P16_P877_EECON2] = 0; 
          pic->ee_wr=1;
        }
        else
        {
          pic->ram[P16_P877_EECON2] = 0; 
          pic->ee_wr=0;
        }
      }
    }    
  }



  if((pic->ram[P16_P877_EECON1] & 0x03) != 0x00 )
  {
    if((pic->ram[P16_P877_EECON1] & 0x01) == 0x01 ) //RD
    { 
      if((pic->ram[P16_P877_EECON1] & 0x80) == 0)
      {  
         pic->ram[P16_P877_EEDATA]= pic->eeprom[pic->ram[P16_P877_EEADR]];
      }
      else
      {
         pic->ram[P16_P877_EEDATA]=   (pic->prog[(pic->ram[P16_P877_EEADRH]<<8)|pic->ram[P16_P877_EEADR]])&0x00FF;
         pic->ram[P16_P877_EEDATAH]= ((pic->prog[(pic->ram[P16_P877_EEADRH]<<8)|pic->ram[P16_P877_EEADR]])&0xFF00)>>8;
  //       printf("Reading %04X=%04X\n",(pic->ram[P877_EEADRH]<<8)|pic->ram[P877_EEADR],(pic->ram[P877_EEDATAH]<<8) | pic->ram[P877_EEDATA]);
      }
      pic->ram[P16_P877_EECON1]&=~0x01;  
    }
    else
    {
      if(pic->ee_wr == 1)
      {
        if((pic->ram[P16_P877_EECON1] & 0x80) == 0)
        { 
          pic->eeprom[pic->ram[P16_P877_EEADR]]=pic->ram[P16_P877_EEDATA];
        }
        else
        {
          pic->prog[(pic->ram[P16_P877_EEADRH]<<8)|pic->ram[P16_P877_EEADR]] = (pic->ram[P16_P877_EEDATAH]<<8) | pic->ram[P16_P877_EEDATA];

    //      printf("Writing %04X=%04X\n",(pic->ram[P877_EEADRH]<<8)|pic->ram[P877_EEADR],(pic->ram[P877_EEDATAH]<<8) | pic->ram[P877_EEDATA]);
        }       
        pic->ram[P16_P877_EECON1]&=~0x02; 
        pic->ee_wr=0;
      } 
    }
  } 
}

//WDT

  if((pic->config[0] & 0x04) == 0x04 )  
  {
    pic->twdt+=4.0/pic->freq;
    
    if((pic->ram[P16_OPTION] & 0x08)) //PSA
    {
      if(pic->twdt > (1e-3*fpw2[pic->ram[P16_OPTION] & 0x07]))
      {
        pic->twdt=0;
        pic->wdt++;
        if(pic->wdt == pic->WDT_MS)
        {
         //reset
         pic->wdt=0;
   
         pic->ram[((0x0000)<<2)|(P16_STATUS & 0x007F)]&=~0x10;
         pic->ram[((0x0020)<<2)|(P16_STATUS & 0x007F)]&=~0x10;
         pic->ram[((0x0040)<<2)|(P16_STATUS & 0x007F)]&=~0x10;
         pic->ram[((0x0060)<<2)|(P16_STATUS & 0x007F)]&=~0x10;
          
         if( pic->sleep == 1)
         {
           pic->sleep=0;
         } 
         else
         {
           pic_reset(0);
         }
        } 
      }
    }
    else
    {
      if(pic->twdt > 1e-3)
      {
        pic->twdt=0;
        pic->wdt++;
        if(pic->wdt == pic->WDT_MS)
        {
         //reset
         pic->wdt=0;
         
         pic->ram[((0x0000)<<2)|(P16_STATUS & 0x007F)]&=~0x10;
         pic->ram[((0x0020)<<2)|(P16_STATUS & 0x007F)]&=~0x10;
         pic->ram[((0x0040)<<2)|(P16_STATUS & 0x007F)]&=~0x10;
         pic->ram[((0x0060)<<2)|(P16_STATUS & 0x007F)]&=~0x10;
         
         if( pic->sleep == 1)
         {
           pic->sleep=0;
         } 
         else
         {
           pic_reset(0);
         }
        } 
//        printf("WDT=%02X\n",pic->wdt);
      }
    }
  } 




//pinouts 

/*
   for(i=0;i< pic->PINCOUNT ;i++)
   {
     switch(pic->pins[i].type)
     {
        case P_IC:
	case P_IT:
          if(pic->pins[i].pic->port > 0)
          {
     	      val=0x01<<(pic->pins[i].pord);
              pic->port=pic->pins[i].port;
              if((pic->pins[i].value) == 1)
                pic->ram[pic->port]|=val;
              else	
                pic->ram[pic->port]&=~val;
	   }
	break;
	case P_IA:
	break;
	default:
	break;
     };
   };
*/

if(pic->processor != P16F84A)
   serial();
};

void 
periferic16_step_out(void)
{
int i,val;

unsigned char port;
unsigned char tris;
  
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
  if((pic->config[0] & 0x0800) == 0) //DEBUG ON
   {
	pic->ocd_pgca=pic->ocd_pgc;
        pic->ocd_pgc=pic->pins[pic->pgc-1].value;

 
        if((pic->ram[P16_ICKBUG] & 0x80) == 0)
        {
          pic->dbg++; 
          if((pic->ram[P16_ICKBUG]&0x20) == 0x20) pic->sstep++;          
 
          if(((pic->ocd_pgca ==1)&&(pic->ocd_pgc == 0)) ||                               //HardWare
              ((pic->pc ==   ((((pic->ram[P16_ICKBUG]&0x1F)<<8) |  pic->ram[P16_BIGBUG])+1))&&(pic->dbg > 3 ))||    //Break Point  
              (((pic->ram[P16_ICKBUG]&0x20) == 0x20)&&(pic->sstep== 3))                               )          //step 
          {
          //printf("Debug Halt (%04X)   ",pic->pc);
          
         // if((pic->ocd_pgca ==1)&&(pic->ocd_pgc == 0)) printf("Hardware \n");                                   //HardWare
         // if(pic->pc ==   ((((pic->ram[ICKBUG]&0x1F)<<8) |  pic->ram[BIGBUG])+1)) printf("Break Point\n");      //Break Point  
         // if((pic->ram[ICKBUG]&0x20) == 0x20) printf("sstep!\n");  
          
          if(pic->s2 !=0)pic_decode_16();


          for(temp=7;temp>0;temp--)
	    pic->stack[temp]=pic->stack[temp-1];
	  pic->stack[0]=pic->pc;
	  
	  pic->ram[P16_ICKBUG]|=0x80;
	  pic->ram[P16_ICKBUG]= (pic->ram[P16_ICKBUG]&0xE0)|((pic->pc & 0x1F00)>>8);
	  pic->ram[P16_BIGBUG]=pic->pc & 0x00FF;
	  pic->pc=0x2004;
	  pic->s2=1;
          pic->debug=1;

	  //printf("----------->dbg  (%#04X) %#02X  %#02X \n",ICKBUG,pic->ram[ICKBUG],pic->ram[BIGBUG] );

          };
        }; 

   };





//PINOUTS
  
 if((pic->ram[P16_PORTA] != pic->porta)||
    (pic->ram[P16_PORTB] != pic->portb)||
    (pic->ram[P16_PORTC] != pic->portc)||
    (pic->ram[P16_PORTD] != pic->portd)||
    (pic->ram[P16_PORTE] != pic->porte))
 {
   for(i=0;i<pic->PINCOUNT;i++)
   {
    if(pic->pins[i].port)
     switch(pic->pins[i].dir)
     {
	case PD_OUT:
//	    case 7:
//               if((pic->ram[RCSTA] & 0x80)==0x80)break; 
//	    case 17:
//              if((pic->ram[RCSTA] & 0x80)==0x80)break;
//	   if(pic->pins[i].ptype > 2)break;	 
              val=0x01<<(pic->pins[i].pord);
              port=pic->pins[i].port;
              pic->pins[i].value= ((pic->ram[port] & val) != 0);
	      pic->pins[i].lvalue=pic->pins[i].value;
	  break;
	case PD_IN:
              val=0x01<<(pic->pins[i].pord);
              port=pic->pins[i].port;
              pic->pins[i].lvalue= ((pic->ram[port] & val) != 0); //latch
  	      if(pic->pins[i].ptype > 2)
                pic_wr_pin16(i+1, 0);
              else
                pic_wr_pin16(i+1,pic->pins[i].value);
	break;
	default:
	break;
     };
    } 
    pic->porta=pic->ram[P16_PORTA];
    pic->portb=pic->ram[P16_PORTB];
    pic->portc=pic->ram[P16_PORTC];
    pic->portd=pic->ram[P16_PORTD];
    pic->porte=pic->ram[P16_PORTE];
  }



 if((pic->ram[P16_TRISA] != pic->trisa)||
    (pic->ram[P16_TRISB] != pic->trisb)||
    (pic->ram[P16_TRISC] != pic->trisc)||
    (pic->ram[P16_TRISD] != pic->trisd)||
    (pic->ram[P16_TRISE] != pic->trise))
 {
   for(i=0;i<pic->PINCOUNT;i++)
   {
    if(pic->pins[i].port)
     { 
     val=0x01<<(pic->pins[i].pord);
     tris=pic->pins[i].port+0x80;
     if((pic->ram[tris] & val)==0)
     {
       pic->pins[i].dir=PD_OUT;
       pic_wr_pin16(i+1,pic->pins[i].lvalue);
     }
     else
     {
       val=pic->pins[i].dir;
       pic->pins[i].dir=PD_IN;
       if(val != PD_IN)pic_wr_pin16(i+1,pic->pins[i].ovalue);
     }
     }
   };
   pic->trisa=pic->ram[P16_TRISA];
   pic->trisb=pic->ram[P16_TRISB];
   pic->trisc=pic->ram[P16_TRISC];
   pic->trisd=pic->ram[P16_TRISD];
   pic->trise=pic->ram[P16_TRISE];
 };


//interrupt
if(pic->s2 == 0)
{
  if (interrupt16() )
  {
       pic->sleep=0; 

       pic->ram[(0x0000)|(P16_INTCON & 0x007F)]&=~0x80;
       pic->ram[(0x0080)|(P16_INTCON & 0x007F)]&=~0x80;
       pic->ram[(0x0100)|(P16_INTCON & 0x007F)]&=~0x80;
       pic->ram[(0x0180)|(P16_INTCON & 0x007F)]&=~0x80;

       if(pic->print)printf("interrupt!");
       for(i=7;i>0;i--)
         pic->stack[i]=pic->stack[i-1];
       pic->stack[0]=pic->pc;
       pic->pc=0x0004;
       pic->s2=1;
    }



}

};
   
