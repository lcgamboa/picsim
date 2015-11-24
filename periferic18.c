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
#include"picsim.h"
#include"periferic18.h"



const int fpw2_[8]={1,2,4,8,16,32,64,128};


extern void pic_decode_18(_pic * pic,int print);

int 
pic18_wr_pin(_pic * pic,unsigned char pin,unsigned char value)
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

              if((pic->pins[(pin-1)].port == P18_PORTB)&&(pic->ram[P18_DEBUG] & 0x80)) 
              {  
                pic->ram[P18_DEBUG]= (pic->ram[P18_DEBUG]&0xF3)|((pic->ram[P18_PORTB] &0xC0)>>4) ; //espelhamento debug
              } 
	   }

     return 1;
   } 
   else
     return 0;
};

int interrupt18(_pic * pic,int print)
{
//interrupt

  if(pic->ram[P18_RCON] & 0x80) //priority 
  {
    //GIEH
    if(pic->ram[P18_INTCON] & 0x80)
    {
      //T0IE  T0IF
      if((pic->ram[P18_INTCON]&0x20)&&(pic->ram[P18_INTCON]&0x04)&&(pic->ram[P18_INTCON2] & 0x04)) return 1;
      //INTE INTF
      if((pic->ram[P18_INTCON]&0x10)&&(pic->ram[P18_INTCON]&0x02)) return 1;
      //RBIE
      if((pic->ram[P18_INTCON]&0x08)&&(pic->ram[P18_INTCON]&0x01)&&(pic->ram[P18_INTCON2] & 0x01)) return 1;
      //EEIE
      //if((pic->ram[P18_PIE1] & 0x80)&&(pic->ram[P18_PIR1] & 0x80)&&(pic->ram[P18_IPR1] & 0x80)) return 1;
      //CMIE CMIF
      //if((pic->ram[P18_PIE1] & 0x40)&&(pic->ram[P18_PIR1] & 0x40)&&(pic->ram[P18_IPR1] & 0x40)) return 1;
      //ADIE ADIF 
      if((pic->ram[P18_PIE1] & 0x40)&&(pic->ram[P18_PIR1] & 0x40)&&(pic->ram[P18_IPR1] & 0x40)) return 1;
      //RCIE RCIF
      if((pic->ram[P18_PIE1] & 0x20)&&(pic->ram[P18_PIR1] & 0x20)&&(pic->ram[P18_IPR1] & 0x20)) return 1;
      //TXIE TXIF
      if((pic->ram[P18_PIE1] & 0x10)&&(pic->ram[P18_PIR1] & 0x10)&&(pic->ram[P18_IPR1] & 0x10)) return 1;
      //SSPIE
      if((pic->ram[P18_PIE1] & 0x08)&&(pic->ram[P18_PIR1] & 0x08)&&(pic->ram[P18_IPR1] & 0x08)) return 1;
      //CCP1IE CCP1IF
      if((pic->ram[P18_PIE1] & 0x04)&&(pic->ram[P18_PIR1] & 0x04)&&(pic->ram[P18_IPR1] & 0x04)) return 1;
      //TMR2IE TMR2IF
      if((pic->ram[P18_PIE1] & 0x02)&&(pic->ram[P18_PIR1] & 0x02)&&(pic->ram[P18_IPR1] & 0x02)) return 1;
      //TMR1IE TMR1IF
      if((pic->ram[P18_PIE1] & 0x01)&&(pic->ram[P18_PIR1] & 0x01)&&(pic->ram[P18_IPR1] & 0x01)) return 1;
      //TMR3IE TMR3IF
      if((pic->ram[P18_PIE2] & 0x02)&&(pic->ram[P18_PIR2] & 0x02)&&(pic->ram[P18_IPR2] & 0x02)) return 1;
      //CCP2IE CCP2IF
      if((pic->ram[P18_PIE2] & 0x01)&&(pic->ram[P18_PIR2] & 0x01)&&(pic->ram[P18_IPR2] & 0x01)) return 1;
      //INT1E INT1F
      if((pic->ram[P18_INTCON3] & 0x08)&&(pic->ram[P18_INTCON3] & 0x01)&&(pic->ram[P18_INTCON3] & 0x40)) return 1;
      //INT2E INT2F
      if((pic->ram[P18_INTCON3] & 0x10)&&(pic->ram[P18_INTCON3] & 0x02)&&(pic->ram[P18_INTCON3] & 0x80)) return 1;
    //GIEL
     if(pic->ram[P18_INTCON] & 0x40)
     { 
      //T0IE  T0IF
      if((pic->ram[P18_INTCON]&0x20)&&(pic->ram[P18_INTCON]&0x04)&&(!(pic->ram[P18_INTCON2] & 0x04))) return 2;
      //RBIE
      if((pic->ram[P18_INTCON]&0x08)&&(pic->ram[P18_INTCON]&0x01)&&(!(pic->ram[P18_INTCON2] & 0x01))) return 2;
      //EEIE
      //if((pic->ram[P18_PIE1] & 0x80)&&(pic->ram[P18_PIR1] & 0x80)&&(!(pic->ram[P18_IPR1] & 0x80))) return 2;
      //CMIE CMIF
      //if((pic->ram[P18_PIE1] & 0x40)&&(pic->ram[P18_PIR1] & 0x40)&&(!(pic->ram[P18_IPR1] & 0x40))) return 2;
      //ADIE ADIF 
      if((pic->ram[P18_PIE1] & 0x40)&&(pic->ram[P18_PIR1] & 0x40)&&(!(pic->ram[P18_IPR1] & 0x40))) return 2;
      //RCIE RCIF
      if((pic->ram[P18_PIE1] & 0x20)&&(pic->ram[P18_PIR1] & 0x20)&&(!(pic->ram[P18_IPR1] & 0x20))) return 2;
      //TXIE TXIF
      if((pic->ram[P18_PIE1] & 0x10)&&(pic->ram[P18_PIR1] & 0x10)&&(!(pic->ram[P18_IPR1] & 0x10))) return 2;
      //SSPIE
      if((pic->ram[P18_PIE1] & 0x08)&&(pic->ram[P18_PIR1] & 0x08)&&(!(pic->ram[P18_IPR1] & 0x08))) return 2;
      //CCP1IE CCP1IF
      if((pic->ram[P18_PIE1] & 0x04)&&(pic->ram[P18_PIR1] & 0x04)&&(!(pic->ram[P18_IPR1] & 0x04))) return 2;
      //TMR2IE TMR2IF
      if((pic->ram[P18_PIE1] & 0x02)&&(pic->ram[P18_PIR1] & 0x02)&&(!(pic->ram[P18_IPR1] & 0x02))) return 2;
      //TMR1IE TMR1IF
      if((pic->ram[P18_PIE1] & 0x01)&&(pic->ram[P18_PIR1] & 0x01)&&(!(pic->ram[P18_IPR1] & 0x01))) return 2;
      //CCP2IE CCP2IF      
      if((pic->ram[P18_PIE2] & 0x01)&&(pic->ram[P18_PIR2] & 0x01)&&(!(pic->ram[P18_IPR2] & 0x01))) return 2;
      //TMR3IE TMR3IF
      if((pic->ram[P18_PIE2] & 0x02)&&(pic->ram[P18_PIR2] & 0x02)&&(!(pic->ram[P18_IPR2] & 0x02))) return 2;
      //INT1E INT1F
      if((pic->ram[P18_INTCON3] & 0x08)&&(pic->ram[P18_INTCON3] & 0x01)&&(!(pic->ram[P18_INTCON3] & 0x40))) return 2;
      //INT2E INT2F
      if((pic->ram[P18_INTCON3] & 0x10)&&(pic->ram[P18_INTCON3] & 0x02)&&(!(pic->ram[P18_INTCON3] & 0x80))) return 2;
    }
    }
  }
  else //legacy
  {
    //GIE
    if(pic->ram[P18_INTCON] & 0x80)
    {
      //T0IE  T0IF
      if((pic->ram[P18_INTCON]&0x20)&&(pic->ram[P18_INTCON]&0x04)) return 1;
      //INTE INTF
      //if((pic->ram[P18_INTCON]&0x10)&&(pic->ram[P18_INTCON]&0x02)) return 1;
      //RBIE
      if((pic->ram[P18_INTCON]&0x08)&&(pic->ram[P18_INTCON]&0x01)) return 1;
      //INT1E INT1F
      if((pic->ram[P18_INTCON3] & 0x08)&&(pic->ram[P18_INTCON3] & 0x01)) return 1;
      //INT2E INT2F
      if((pic->ram[P18_INTCON3] & 0x10)&&(pic->ram[P18_INTCON3] & 0x02)) return 1;
      //PEIE	
      if((pic->ram[P18_INTCON] & 0x40) == 0x40)
      {
        //EEIE
        //if((pic->ram[P18_PIE1] & 0x80)&&(pic->ram[P18_PIR1] & 0x80)) return 1;
        //CMIE CMIF
        //if((pic->ram[P18_PIE1] & 0x40)&&(pic->ram[P18_PIR1] & 0x40)) return 1;
        //ADIE ADIF 
        if((pic->ram[P18_PIE1] & 0x40)&&(pic->ram[P18_PIR1] & 0x40)) return 1;
        //RCIE RCIF
        if((pic->ram[P18_PIE1] & 0x20)&&(pic->ram[P18_PIR1] & 0x20)) return 1;
        //TXIE TXIF
        if((pic->ram[P18_PIE1] & 0x10)&&(pic->ram[P18_PIR1] & 0x10)) return 1;
        //SSPIE
        if((pic->ram[P18_PIE1] & 0x08)&&(pic->ram[P18_PIR1] & 0x08)) return 1;
        //CCP1IE CCP1IF
        if((pic->ram[P18_PIE1] & 0x04)&&(pic->ram[P18_PIR1] & 0x04)) return 1;
        //TMR2IE TMR2IF
        if((pic->ram[P18_PIE1] & 0x02)&&(pic->ram[P18_PIR1] & 0x02)) return 1;
        //TMR1IE TMR1IF
        if((pic->ram[P18_PIE1] & 0x01)&&(pic->ram[P18_PIR1] & 0x01)) return 1;
        //TMR3IE TMR3IF
        if((pic->ram[P18_PIE2] & 0x02)&&(pic->ram[P18_PIR2] & 0x02)) return 1;
        //CCP2IE CCP2IF
        if((pic->ram[P18_PIE2] & 0x01)&&(pic->ram[P18_PIR2] & 0x01)) return 1;
      }
    }
  }

 return 0;
}

void
periferic18_rst(_pic * pic)
{

pic->debug=0;

pic->cp0=0;
pic->cp1=0;
pic->cp2=0;
pic->cp2_=0;
pic->cp3=0;

pic->t2pr=0;

pic->adcstep=0;

pic->twdt=0;

pic->ee_wr=0;

pic->porta=129;
pic->portb=129;
pic->portc=129;
pic->portd=129;
pic->porte=129;

pic->trisa=129;
pic->trisb=129;
pic->trisc=129;
pic->trisd=129;
pic->trise=129;

pic->adcon1=64;

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

}


void 
periferic18_step_in(_pic * pic,int print)
{
//int i;
float val;
int chn;
short dval;


//DEBUG
 if((pic->config[3] & 0x0080) == 0) //DEBUG ON
 {
   if(pic->debug == 1)pic->ram[P18_DEBUG]|=0x80;
 } 



//MSSP

 if((pic->ram[P18_SSPCON1] & 0x20) ==0x20) //SSPEN
 {
    
    if((pic->ram[P18_SSPCON1] & 0x0F) ==0x05)//SLAVE Without SS
    {
   
      pic->pins[pic->sdi-1].dir=PD_IN; 	
 
      if(pic->rram == P18_SSPBUF)
      {
         pic->ram[P18_SSPSTAT]&=~0x01; //BF
      } 	

        pic->ssp_scka=pic->ssp_sck; 
        pic->ssp_sck= pic->pins[pic->sck-1].value;


	if((pic->ssp_scka == 0)&&(pic->ssp_sck == 1)) //CKP =0 CKE =0     //coloca saida na borda de subida
        {
           pic18_wr_pin(pic,pic->sdo, ((pic->ram[P18_SSPBUF] & (1 <<(7-pic->ssp_bit))) > 0));
        }


	if((pic->ssp_scka == 1)&&(pic->ssp_sck == 0)) //CKP =0 CKE =0    //le na borda de decida
        {
	   pic->sspsr|= (pic->pins[pic->sdi-1].value) << (7-pic->ssp_bit);
           
           //printf("SSP bit =%i    REC=%#02X   SEND=%#02X \n",pic->ssp_bit,pic->sspsr, pic->ram[P18_SSPBUF]);

	   pic->ssp_bit++;
        }

	if(pic->ssp_bit >= 8)
        {
//	   printf("MSSP TX=%#02X  RX=%#02X\n",pic->ram[P18_SSPBUF],pic->sspsr);
           pic->ram[P18_SSPBUF]=pic->sspsr;
           pic->sspsr =0;
	   pic->ram[P18_SSPSTAT]|=0x01; //BF
	           
           //PSPIF
           pic->ram[P18_PIR1]|=0x08; //PSPIF
	   pic->ssp_bit=0;
        }
	

    }
    else if((pic->ram[P18_SSPCON1] & 0x0F) ==0x08)//MASTER i2c
    {
      
       pic->ssp_sck++;

       if(pic->ssp_sck == ((pic->ram[P18_SSPADD]+1/2)-1))
       {
       
         if((pic->ram[P18_SSPCON2] & 0x01)) //start
         {
           pic->pins[pic->sck-1].dir=PD_OUT; 	
           pic->pins[pic->sdi-1].dir=PD_OUT; 	
           pic->pins[pic->sdi-1].value=1;
           pic->pins[pic->sck-1].value=1;
        
           //printf("I2C_start 1\n");
         }
         else if((pic->ram[P18_SSPCON2] & 0x02)) //restart
         {
           pic->pins[pic->sdi-1].dir=PD_OUT; 	
           pic->pins[pic->sdi-1].value=1;
           pic->pins[pic->sck-1].value=1;
           //printf("restar1\n");
         } 
         else if((pic->ram[P18_SSPCON2] & 0x04)) //stop
         {
           pic->pins[pic->sdi-1].dir=PD_OUT; 	
           pic->pins[pic->sdi-1].value=0;
           pic->pins[pic->sck-1].value=1;
           //printf("stop1\n");
         } 
       }

       if(pic->ssp_sck == ((pic->ram[P18_SSPADD]+1/2)+1))
       {
       
         if((pic->ram[P18_SSPCON2] & 0x01)) //start
         {
           pic->ram[P18_SSPCON2] &=~ 0x01;
           
           pic->pins[pic->sdi-1].value=0;
           pic->pins[pic->sck-1].value=1;
           
           //printf("start 2\n");
         }
         else if((pic->ram[P18_SSPCON2] & 0x02)) //restart
         {
           pic->ram[P18_SSPCON2] &=~ 0x02;

           pic->pins[pic->sdi-1].value=0;
           pic->pins[pic->sck-1].value=1;
           //printf("restart 2\n");
         } 
         else if((pic->ram[P18_SSPCON2] & 0x04)) //stop
         {
           pic->ram[P18_SSPCON2] &=~ 0x04;
         
           pic->ssp_bit=10;

           pic->pins[pic->sdi-1].value=1;
           pic->pins[pic->sck-1].value=1;
           //printf("stop 2\n");
         } 
       }

 


        if(pic->lram == P18_SSPBUF) //write init
        {
         pic->ram[P18_SSPSTAT]|=0x04; //R/W
         //printf("SPPBUF write (%#02X)!!!!\n",pic->ram[P18_SSPBUF]);	
         pic->ssp_bit=0;
         pic->pins[pic->sdi-1].dir=PD_OUT; 	
         pic->ram[P18_SSPSTAT]|=0x01; //BF
        } 	
       
        if(!(pic->ram[P18_SSPCON2] & 0x08)) pic->ssp_scka=0;

        if((pic->ram[P18_SSPCON2] & 0x08) && (pic->ssp_scka == 0)) //read init
        {
          pic->ssp_bit=0;

          //printf("I2C read\n");
          pic->ram[P18_SSPBUF]=0;
          pic->pins[pic->sdi-1].dir=PD_IN; 	
          pic->ssp_ck=pic->pins[pic->sck-1].value;
          pic->ram[P18_SSPSTAT]&=~0x01; //BF

          pic->ssp_scka=1;
        }


       if(pic->ssp_sck > pic->ram[P18_SSPADD])
       {
          pic->ssp_sck=0;

        //write
        if(( (pic->ram[P18_SSPSTAT] & 0x04) )&&( pic->ssp_bit <= 9))
        {
           pic->pins[pic->sck-1].value^=0x01;


           if((pic->pins[pic->sck-1].value == 0)&&(pic->ssp_bit <= 8))
           {
             pic->pins[pic->sdi-1].value=(pic->ram[P18_SSPBUF] & (0x01<<(7-pic->ssp_bit))) >0; 
             pic->ssp_bit++;
             if(pic->ssp_bit ==9)
             { 
               pic->pins[pic->sdi-1].dir=PD_IN;
             } 
           }


           if((pic->pins[pic->sck-1].value == 1)&&(pic->ssp_bit  > 8))
           {
             if(pic->pins[pic->sdi-1].value)
               pic->ram[P18_SSPCON2]|=0x40; //ACKSTAT
             else
               pic->ram[P18_SSPCON2]&=~0x40; //ACKSTAT

             pic->ram[P18_SSPSTAT]&=~0x04; //R/W
             pic->ram[P18_PIR1]|=0x08;//SSPIF
             pic->ram[P18_SSPSTAT]&=~0x01; //BF
             pic->ssp_bit++;
           }

      //    printf("wbit(%i)  sck=%i  sda=%i \n",pic->ssp_bit,pic->pins[pic->sck-1].value,pic->pins[pic->sdi-1].value); 
        }
       
      //read 
        if(((pic->ram[P18_SSPCON2] & 0x08)||(pic->ram[P18_SSPCON2]& 0x10))&&( pic->ssp_bit <= 9))
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
             pic->ram[P18_SSPBUF]|=(pic->pins[pic->sdi-1].value << (8 -pic->ssp_bit)); 
             if(pic->ssp_bit == 8)
             {
                pic->ram[P18_SSPCON2]&=~0x10;//ACKDT
                pic->ram[P18_PIR1]|=0x08;//SSPIF
                pic->ssp_bit++;
               
                 pic->ram[P18_SSPCON2]&=~0x08;
                pic->ram[P18_SSPSTAT]|=0x01; //BF
                //printf("recebido1 %02X\n",pic->ram[P18_SSPBUF]);
             }
           }

           if((pic->ram[P18_SSPCON2]& 0x10)&&(pic->pins[pic->sck-1].value == 1)&&(pic->ssp_bit  > 8))
           {
             pic->pins[pic->sdi-1].dir=PD_OUT; 	
             pic->pins[pic->sdi-1].value=(pic->ram[P18_SSPCON2]&0x20) >0 ;
             pic->ram[P18_PIR1]|=0x08;//SSPIF;
             pic->ssp_bit++;

             pic->ram[P18_SSPCON2]&=~0x10;//ACKDT

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
	printf(" %#02X SPI mode not implemented!\n",(pic->ram[P18_SSPCON1] & 0x0F));
	
    } 
 }
 else
 {
     pic->ssp_sck=0;
     pic->ssp_scka=0;
     pic->ssp_bit=0;
 }



//ADC

if(pic->processor == P18F452)
{

  if((pic->ADCCOUNT > 0)&&((pic->ram[P18_ADCON0] & 0x01) == 0x01) )  //ADON
  {

  if((pic->ram[P18_ADCON0] & 0x04 ) == 0x04) //GO/DONE
  {
   pic->adcstep++;
   if(pic->adcstep > 10 )
   {
     chn=(pic->ram[P18_ADCON0]&0x38)>>3;

     if(pic->pins[pic->adc[chn]-1].ptype == PT_ANALOG)
     {
       val=pic->pins[pic->adc[chn]-1].avalue;
     }
     else
     {
       val=0;
     }

      dval=((1023*val)/5.0);
   
      if((pic->ram[P18_ADCON1]&0x80) == 0x80)//ADFM
      { 
        pic->ram[P18_ADRESH]=(dval & 0xFF00)>>8;   	
        pic->ram[P18_ADRESL]=(dval & 0x00FF);   	
      }
      else
      {
        dval= dval <<6;	
        pic->ram[P18_ADRESH]=(dval & 0xFF00)>>8;   	
        pic->ram[P18_ADRESL]=(dval & 0x00FF);   	
      }
    
      pic->ram[P18_ADCON0]&= ~0x04; 
      
      //ADIF
      pic->ram[P18_PIR1]|=0x40;

      pic->adcstep=0;
    }
  }
   

 
    
  if((pic->ram[P18_ADCON1]&0x0F) != pic->adcon1)
  {
    switch(pic->ram[P18_ADCON1]&0x0F)
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

    pic->adcon1=pic->ram[P18_ADCON1]&0x0F;	
   }
  
  
  }
  else
  {
   pic->adcon1=64;
   pic->adcstep=0;
  };
}
else //PIC18F4620 and PIC18F4550
{

  if((pic->ADCCOUNT > 0)&&((pic->ram[P18_ADCON0] & 0x01) == 0x01) )  //ADON
  {

  if((pic->ram[P18_ADCON0] & 0x02 ) == 0x02) //GO/DONE
  {
   pic->adcstep++;
   if(pic->adcstep > 10 )
   {
     chn=(pic->ram[P18_ADCON0]&0x3C)>>2;

     if((pic->pins[pic->adc[chn]-1].ptype == PT_ANALOG)&&(chn < pic->ADCCOUNT))
     {
       val=pic->pins[pic->adc[chn]-1].avalue;
     }
     else
     {
       val=0;
     }

      dval=((1023*val)/5.0);
   
      if((pic->ram[P18_ADCON2]&0x80) == 0x80)//ADFM
      { 
        pic->ram[P18_ADRESH]=(dval & 0xFF00)>>8;   	
        pic->ram[P18_ADRESL]=(dval & 0x00FF);   	
      }
      else
      {
        dval= dval <<6;	
        pic->ram[P18_ADRESH]=(dval & 0xFF00)>>8;   	
        pic->ram[P18_ADRESL]=(dval & 0x00FF);   	
      }
    
      pic->ram[P18_ADCON0]&= ~0x02; 
      
      //ADIF
      pic->ram[P18_PIR1]|=0x40;

      pic->adcstep=0;
    }
  }
   

 
    
  if((pic->ram[P18_ADCON1]&0x0F) != pic->adcon1)
  {
   int i;
   for(i=0;i < pic->ADCCOUNT;i++)  
   {
        if((pic->ram[P18_ADCON1]&0x0F) <  (0x0F-i))
	  pic->pins[pic->adc[i]-1].ptype=PT_ANALOG;
        else
	  pic->pins[pic->adc[i]-1].ptype=PT_CMOS;
    } 

    if(pic->ram[P18_ADCON1] & 0x20)//VCFG1  
	pic->pins[pic->adc[2]-1].ptype=PT_ANAREF;
    if(pic->ram[P18_ADCON1] & 0x10)//VCFG0  
	pic->pins[pic->adc[3]-1].ptype=PT_ANAREF;

    pic->adcon1=pic->ram[P18_ADCON1]&0x0F;	
   }
  
  
  }
  else
  {
   pic->adcon1=64;
   pic->adcstep=0;
  };

}


//INT0
   if((pic->pins[pic->int0-1].dir == PD_IN)&&(pic->pins[pic->int0-1].value != pic->int0v))
   {
     if(((!pic->int0v) &&(pic->ram[P18_INTCON2] & 0x40))||((pic->int0v) && (!(pic->ram[P18_INTCON2] & 0x40))))
     {
        pic->ram[P18_INTCON]|=0x02;//INTF
     } 
   } 
   pic->int0v=pic->pins[pic->int0-1].value; 

//INT1
   if((pic->pins[pic->int1-1].dir == PD_IN)&&(pic->pins[pic->int1-1].value != pic->int1v))
   {
     if(((!pic->int1v) &&(pic->ram[P18_INTCON2] & 0x20))||((pic->int1v) && (!(pic->ram[P18_INTCON2] & 0x20))))
     {
        pic->ram[P18_INTCON3]|=0x01;//INT1F
     } 
   } 
   pic->int1v=pic->pins[pic->int1-1].value; 

//INT2
   if((pic->pins[pic->int2-1].dir == PD_IN)&&(pic->pins[pic->int2-1].value != pic->int2v))
   {
     if(((!pic->int2v) &&(pic->ram[P18_INTCON2] & 0x10))||((pic->int2v) && (!(pic->ram[P18_INTCON2] & 0x10))))
     {
        pic->ram[P18_INTCON3]|=0x02;//INT2F
     } 
   } 
   pic->int2v=pic->pins[pic->int2-1].value; 

//PORTB
if((pic->ram[P18_PORTB]&pic->ram[P18_TRISB]&0xF0) != (pic->portb&pic->ram[P18_TRISB]&0xF0)) 
{
  pic->portbm=1;
}

if(pic->rram == P18_PORTB)
{
  pic->portbm=0;
  //Only disable mismatch
  //pic->ram[P18_INTCON]&=~0x01;//RBIF
}

if(pic->portbm)
{
  pic->ram[P18_INTCON]|=0x01;//RBIF
}  



//TMR0
  if(pic->ram[P18_T0CON] & 0x80) //TMR0ON
  {
  if(((pic->ram[P18_T0CON] & 0x20) == 0x00 )||  //TOCS=FOSC/4
    (((pic->ram[P18_T0CON] & 0x30) == 0x20 )&&((pic->t0cki_ == 0)&&(pic->pins[pic->t0cki-1].value==1)))|| //T0CS=t0cki  T0SE =0
    (((pic->ram[P18_T0CON] & 0x30) == 0x30 )&&((pic->t0cki_ == 1)&&(pic->pins[pic->t0cki-1].value==0))))  //T0CS=t0cki  T0SE =1
  {
     pic->cp0++;

     if(pic->lram == P18_TMR0L)pic->cp0=0; //RESET prescaler	 

     if((pic->ram[P18_T0CON] & 0x08) == 0x08) //PSA
     {

        if((pic->ram[P18_T0CON] & 0x40)&& ((pic->ram[P18_TMR0L]+1) == 0x100))pic->ram[P18_INTCON]|=0x04;//T0IF

        pic->ram[P18_TMR0L]++;
        if((!pic->ram[P18_TMR0L])&&(!(pic->ram[P18_T0CON] & 0x40)))
        {
          if((pic->ram[P18_TMR0H]+1) == 0x100)pic->ram[P18_INTCON]|=0x04;//T0IF
          pic->ram[P18_TMR0H]++;
        }
        pic->cp0=0;
     }
     else
     { 
        if(pic->cp0 >= 2*(fpw2_[pic->ram[P18_T0CON]&0x07]) )
        {
  
          if((pic->ram[P18_T0CON] & 0x40)&& ((pic->ram[P18_TMR0L]+1) == 0x100))pic->ram[P18_INTCON]|=0x04;//T0IF
          
          pic->ram[P18_TMR0L]++;
          if((!pic->ram[P18_TMR0L])&&(!(pic->ram[P18_T0CON] & 0x40)))
          {
            if((pic->ram[P18_TMR0H]+1) == 0x100)pic->ram[P18_INTCON]|=0x04;//T0IF
            pic->ram[P18_TMR0H]++;
          }
          pic->cp0=0;
        }
     }
  }
  } 
  pic->t0cki_=pic->pins[pic->t0cki-1].value; 


//TMR1

  if(((pic->ram[P18_T1CON] & 0x03) == 0x01 )||  //TMRICS=FOSC/4 TMREN=1
    (((pic->ram[P18_T1CON] & 0x03) == 0x03 )&&((pic->t1cki_ == 0)&&(pic->pins[pic->t1cki-1].value==1)))) //TMRICS=t1cki  TMREN=1
  {
     pic->cp1++;
     
     if(pic->cp1 >= fpw2_[(pic->ram[P18_T1CON]&0x30)>>4]) 
     {
       pic->ram[P18_TMR1L]++;
       if(pic->ram[P18_TMR1L] == 0)
       {
        if((pic->ram[P18_TMR1H]+1) == 0x100)pic->ram[P18_PIR1]|=0x01;//TMR1IF
        pic->ram[P18_TMR1H]++;
       }
       pic->cp1=0;
     }
 
   //CCP - only when TMR1 is ON
   //CCP1 compare modes 
     if((pic->CCPCOUNT >= 1)&&(pic->ccp[0] > 0)&&((pic->ram[P18_CCP1CON] & 0x0C) == 0x08)&&(!(pic->ram[P18_T3CON] & 0x40)))   
     {
       if((pic->ram[P18_TMR1H]==pic->ram[P18_CCPR1H])&&(pic->ram[P18_TMR1L]==pic->ram[P18_CCPR1L]))//match !!
       {
          pic->ram[P18_PIR1]|=0x04;//CCP1IF
          switch(pic->ram[P18_CCP1CON] & 0x03)
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
              pic->ram[P18_TMR1H]=0;
              pic->ram[P18_TMR1L]=0;
              break;
          }
       }
     }
//CCP2 compare modes 
     if((pic->CCPCOUNT >= 2)&&(pic->ccp[1] > 0)&&((pic->ram[P18_CCP2CON] & 0x0C) == 0x08)&&(!(pic->ram[P18_T3CON] & 0x48)))
     {
       if((pic->ram[P18_TMR1H]==pic->ram[P18_CCPR2H])&&(pic->ram[P18_TMR1L]==pic->ram[P18_CCPR2L]))//match !!
       {
          pic->ram[P18_PIR2]|=0x01;//CCP2IF
          switch(pic->ram[P18_CCP2CON] & 0x03)
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
              pic->ram[P18_TMR1H]=0;
              pic->ram[P18_TMR1L]=0;
              if(pic->processor == P18F452)
              {
                if(pic->ram[P18_ADCON0] & 0x01)pic->ram[P18_ADCON0]|=0x04; //if ad on, enable one conversion
              }
              else
              {
                if(pic->ram[P18_ADCON0] & 0x01)pic->ram[P18_ADCON0]|=0x02; //if ad on, enable one conversion  
              }
              break;
          }
       }
     }

  

  } 
  
//TMR3
  if(((pic->ram[P18_T3CON] & 0x03) == 0x01 )||  //TMRICS=FOSC/4 TMREN=1
    (((pic->ram[P18_T3CON] & 0x03) == 0x03 )&&((pic->t1cki_ == 0)&&(pic->pins[pic->t1cki-1].value ==1)))) //TMRICS=t1cki  TMREN=1
  {
     pic->cp3++;
     
     if(pic->cp3 >= fpw2_[(pic->ram[P18_T3CON]&0x30)>>4]) 
     {
       pic->ram[P18_TMR3L]++;
       if(pic->ram[P18_TMR3L] == 0)
       {
        if((pic->ram[P18_TMR3H]+1) == 0x100)pic->ram[P18_PIR2]|=0x02;//TMR3IF
        pic->ram[P18_TMR3H]++;
       }
       pic->cp3=0;
     }

   //CCP - only when TMR3 is ON
   //CCP3 compare modes 
     if((pic->CCPCOUNT >= 1)&&(pic->ccp[0] > 0)&&((pic->ram[P18_CCP1CON] & 0x0C) == 0x08)&&(pic->ram[P18_T3CON] & 0x40))   
     {
       if((pic->ram[P18_TMR3H]==pic->ram[P18_CCPR1H])&&(pic->ram[P18_TMR3L]==pic->ram[P18_CCPR1L]))//match !!
       {
          pic->ram[P18_PIR1]|=0x04;//CCP1IF
          switch(pic->ram[P18_CCP1CON] & 0x03)
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
              pic->ram[P18_TMR3H]=0;
              pic->ram[P18_TMR3L]=0;
              break;
          }
       }
     }
//CCP2 compare modes 
     if((pic->CCPCOUNT >= 2)&&(pic->ccp[1] > 0)&&((pic->ram[P18_CCP2CON] & 0x0C) == 0x08)&&(pic->ram[P18_T3CON] & 0x48))
     {
       if((pic->ram[P18_TMR3H]==pic->ram[P18_CCPR2H])&&(pic->ram[P18_TMR3L]==pic->ram[P18_CCPR2L]))//match !!
       {
          pic->ram[P18_PIR2]|=0x01;//CCP2IF
          switch(pic->ram[P18_CCP2CON] & 0x03)
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
              pic->ram[P18_TMR3H]=0;
              pic->ram[P18_TMR3L]=0;
              if(pic->processor == P18F452)
              {
                if(pic->ram[P18_ADCON0] & 0x01)pic->ram[P18_ADCON0]|=0x04; //if ad on, enable one conversion
              }
              else
              {
                if(pic->ram[P18_ADCON0] & 0x01)pic->ram[P18_ADCON0]|=0x02; //if ad on, enable one conversion  
              }
              break;
          }
       }
     }
   
     
     
     
  } 

  pic->t1cki_=pic->pins[pic->t1cki-1].value; 
 


//TMR2
  
  if((pic->ram[P18_T2CON] & 0x04) == 0x04 )  //TMR2EN
  {
     pic->cp2++;
     
     if((pic->ram[P18_T2CON]&0x02) == 0x02)
     {
       pic->t2pr=16;
     }
     else if ((pic->ram[P18_T2CON]&0x01) == 0x01)
     {
       pic->t2pr=4;
     }
     else
     {
       pic->t2pr=1;
     }

     if(pic->cp2 >= pic->t2pr) 
     {
       pic->ram[P18_TMR2]++;
       if(pic->ram[P18_TMR2] == pic->ram[P18_PR2])
       {
         pic->ram[P18_TMR2]=0;
         pic->cp2_++;

         if(pic->cp2_ >= (((pic->ram[P18_T2CON]&0x78)>>3)+1) )
         { 
           pic->ram[P18_PIR1]|=0x02; //TMR2IF
           pic->cp2_=0; 
         }

         //PWM
          	
	 if((pic->CCPCOUNT >= 1)&&(pic->ccp[0] > 0)&&(pic->ram[P18_CCP1CON]& 0x0C) == 0x0C)
         {
           pic->ram[P18_CCPR1H]=pic->ram[P18_CCPR1L];
           if(pic->pins[pic->ccp[0]-1].dir == PD_OUT)
             pic->ram[pic->pins[(pic->ccp[0]-1)].port]|=0x01<<(pic->pins[(pic->ccp[0]-1)].pord);
         } 
	 
         if((pic->CCPCOUNT >= 2)&&(pic->ccp[1] > 0)&&(pic->ram[P18_CCP2CON]& 0x0C) == 0x0C)
         {
           pic->ram[P18_CCPR2H]=pic->ram[P18_CCPR2L];
           if(pic->pins[pic->ccp[1]-1].dir == PD_OUT)
             pic->ram[pic->pins[(pic->ccp[1]-1)].port]|=0x01<<(pic->pins[(pic->ccp[1]-1)].pord);
         } 
	
       }
       pic->cp2=0;
     }
//PWM - only if TMR2 is on

//only use 8 bits ! not 10 bits  
   if((pic->CCPCOUNT >= 1)&&(pic->ccp[0] > 0)&&(pic->ram[P18_CCP1CON]& 0x0C) == 0x0C)
   {
      if(pic->ram[P18_TMR2] >=  pic->ram[P18_CCPR1H])
      {
        if(pic->pins[pic->ccp[0]-1].dir == PD_OUT)
          pic->ram[pic->pins[(pic->ccp[0]-1)].port]&=~(0x01<<(pic->pins[(pic->ccp[0]-1)].pord));
      }
   }	
   
   if((pic->CCPCOUNT >= 2)&&(pic->ccp[1] > 0)&&(pic->ram[P18_CCP2CON]& 0x0C) == 0x0C)
   {
      if(pic->ram[P18_TMR2] >=  pic->ram[P18_CCPR2H])
      {
        if(pic->pins[pic->ccp[1]-1].dir == PD_OUT)
          pic->ram[pic->pins[(pic->ccp[1]-1)].port]&=~(0x01<<(pic->pins[(pic->ccp[1]-1)].pord));
      }
   }	


  } 



//EEPROM

  if((pic->ram[P18_EECON1] & 0x04) == 0x04 )
  {
    if(pic->ram[P18_EECON2] != 0 )
    {
      if(pic->ram[P18_EECON2] == 0x55 )
      {
        pic->ram[P18_EECON2] = 0; 
        pic->ee_wr=-1;
      }
      else
      {
        if((pic->ram[P18_EECON2] == 0xAA )&&(pic->ee_wr == -1))
        {
          pic->ram[P18_EECON2] = 0; 
          pic->ee_wr=1;
        }
        else
        {
          pic->ram[P18_EECON2] = 0; 
          pic->ee_wr=0;
        }
      }
    }    
  }



  if((pic->ram[P18_EECON1] & 0x03) != 0x00 )
  {
    if((pic->ram[P18_EECON1] & 0x01) == 0x01 ) //RD
    { 
      if((pic->ram[P18_EECON1] & 0x80) == 0)
      {  
         pic->ram[P18_EEDATA]= pic->eeprom[pic->ram[P18_EEADR]];
      }
/*
      else
      {
         pic->ram[P18_EEDATA]=   (pic->prog[(pic->ram[P18_EEADRH]<<8)|pic->ram[P18_EEADR]])&0x00FF;
         pic->ram[P18_EEDATAH]= ((pic->prog[(pic->ram[P18_EEADRH]<<8)|pic->ram[P18_EEADR]])&0xFF00)>>8;
      }
*/
      pic->ram[P18_EECON1]&=~0x01;  
    }
    else
    {
      if(pic->ee_wr == 1)
      {
        if((pic->ram[P18_EECON1] & 0x80) == 0)
        { 
          pic->eeprom[pic->ram[P18_EEADR]]=pic->ram[P18_EEDATA];
        }
/*
        else
        {
          pic->prog[(pic->ram[P18_EEADRH]<<8)|pic->ram[P18_EEADR]] = (pic->ram[P18_EEDATAH]<<8) | pic->ram[P18_EEDATA];

        }  
*/     
        pic->ram[P18_EECON1]&=~0x02; 
        pic->ee_wr=0;
      } 
    }
  } 



//WDT

  if((pic->config[1] & 0x0100) || (pic->ram[P18_WDTCON] & 0x01))  
  {
//     printf("WDT ON %f   %i  0x%02X\n",pic->twdt ,pic->wdt,pic->ram[P18_RCON]);

    pic->twdt+=4.0/pic->freq;
    
      if(pic->twdt > (1e-3*fpw2_[(pic->config[1] & 0x0E00)>>9]))
      {
        pic->twdt=0;
        pic->wdt++;

        if(pic->wdt == pic->WDT_MS) 
        {
         //reset
         pic->wdt=0;
   
         pic->ram[P18_RCON]&=~0x08; //clear TO
           
          
         if( pic->sleep == 1)
         {
           pic->sleep=0;
         } 
         else
         {
           pic_reset(pic,0);
         }

        } 
      }
  } 



   serial18( pic,print);

};

void 
periferic18_step_out(_pic * pic,int print)
{
int i,val;

unsigned short port;
unsigned short tris;
    

	if(pic->lram == P18_DEBUG )
        {
           //printf("---------------> DEBUG write (%#02X)\n",pic->ram[P18_DEBUG]);

          if((pic->ram[P18_DEBUG] & 0x80) == 0x80)
          {
           pic->ram[P18_TRISB]= (pic->ram[P18_TRISB]&0x3F)| ((pic->ram[P18_DEBUG] &0x03)<<6);
                
           if(!(pic->ram[P18_DEBUG] &0x02))pic->ram[P18_PORTB]=(pic->ram[P18_PORTB]&0x7F)| ((pic->ram[P18_DEBUG] &0x08)<<4); 
           if(!(pic->ram[P18_DEBUG] &0x01))pic->ram[P18_PORTB]=(pic->ram[P18_PORTB]&0xBF)| ((pic->ram[P18_DEBUG] &0x04)<<4); 
             
           //printf("pgd=%i tpgd=%i pgc=%i tpgc=%i\n",pic->pins[pic->pgd-1].value,pic->pins[pic->pgd-1].dir,pic->pins[pic->pgc-1].value,pic->pins[pic->pgc-1].dir);
          }                    
        }

        if(pic->rram == P18_DEBUG)
        {
           //printf("---------------> DEBUG read (%#02X)\n",pic->ram[P18_DEBUG]);
           
          if((pic->ram[P18_DEBUG] & 0x80) == 0x80)
          {
           pic->ram[P18_TRISB]= (pic->ram[P18_TRISB]&0x3F)| ((pic->ram[P18_DEBUG] &0x03)<<6);

           //  printf("pgd=%i tpgd=%i pgc=%i tpgc=%i\n",pic->pins[pic->pgd-1].value,pic->pins[pic->pgd-1].dir,pic->pins[pic->pgc-1].value,pic->pins[pic->pgc-1].dir);
          }      

	}
/* 
        if(pic->lram == P18_BDMSR0 )
        {
           printf("---------------> BDMSR0 write (%#02X)\n",pic->ram[P18_BDMSR0]);
        }
*/

 
//DEBUG
  if((pic->config[3] & 0x0080) == 0) //DEBUG ON
   {
	pic->ocd_pgca=pic->ocd_pgc;
        pic->ocd_pgc=pic->pins[pic->pgc-1].value;

 
        if((pic->ram[P18_DEBUG] & 0x80) == 0)
        {
          pic->dbg++;

          if((pic->ram[P18_DEBUG]&0x20) == 0x20) pic->sstep++;          
 
          if(((pic->ocd_pgca ==1)&&(pic->ocd_pgc == 0)) ||    //HardWare
             (((pic->pc>>1) == ((((pic->ram[P18_BDMSR2]&0x0F)<<16)|(pic->ram[P18_BDMSR1]<<8)|pic->ram[P18_BDMSR0])/*+1*/ ))&&(pic->dbg > 3 ))|| //Break Point  
              (((pic->ram[P18_DEBUG]&0x20) == 0x20)&&(pic->sstep== 3)))          //step 
          {
          //printf("Debug Halt (%04X)   ",pic->pc);
          
 //         if((pic->ocd_pgca ==1)&&(pic->ocd_pgc == 0)) printf("Hardware \n");                                   //HardWare
 //         if((pic->pc>>1) ==   ((((pic->ram[P18_BDMSR2]&0x0F)<<16)|(pic->ram[P18_BDMSR1]<<8)|pic->ram[P18_BDMSR0])/*+1*/ )) printf("Break Point\n");      //Break Point  
//          if((pic->ram[P18_DEBUG]&0x20) == 0x20) printf("sstep!\n");  
          
          if(pic->s2 !=0)pic_decode_18(pic,print);

          if(pic->pc != 0x00000)
          {
            //printf("Debug stack save\n");
            if((pic->ram[P18_STKPTR] & 0x1F) < 31 )
            {
	      pic->stack[pic->ram[P18_STKPTR]& 0x1F]=pic->pc;
              pic->ram[P18_STKPTR]=(pic->ram[P18_STKPTR] &0xC0) | ((pic->ram[P18_STKPTR] &0x1F)+1);    
              if((pic->ram[P18_STKPTR]& 0x1F) == 31)pic->ram[P18_STKPTR]|=0x80; //set STKFUL
            }
            if((pic->ram[P18_STKPTR] & 0x1F) >0)
            {    
              pic->ram[P18_TOSL]=((pic->stack[(pic->ram[P18_STKPTR] & 0x1F) -1])&0x0000FF);  
              pic->ram[P18_TOSU]=((pic->stack[(pic->ram[P18_STKPTR] & 0x1F)-1])&0x1F0000)>>16; 
              pic->ram[P18_TOSH]=((pic->stack[(pic->ram[P18_STKPTR] & 0x1F)-1])&0x00FF00)>>8;   
            }
            else
            {
              pic->ram[P18_TOSL]=0;
              pic->ram[P18_TOSH]=0;
              pic->ram[P18_TOSU]=0;
            }
          }
	  
	  pic->ram[P18_DEBUG]|=0x80;
	  pic->ram[P18_BDMSR2]= (pic->pc&0xFF0000)>>16;
	  pic->ram[P18_BDMSR1]= (pic->pc&0x00FF00)>>8;
	  pic->ram[P18_BDMSR0]= (pic->pc&0x0000FF);
	  pic->jpc=0x200028;
	  pic->s2=1;
          pic->debug=1;
          pic->sstep=0;

	  //printf("\n----------->dbg  (%#04X) %#02X  %#02X  pc=0x%04X\n",P18_DEBUG,pic->ram[P18_DEBUG],pic->ram[P18_BDMSR0],pic->pc );
/*           
           pic->pins[pic->pgd-1].dir=(pic->ram[P18_DEBUG]&0x02)>>1;                     
           pic->pins[pic->pgc-1].dir=(pic->ram[P18_DEBUG]&0x01);  
           
           if(!pic->pins[pic->pgd-1].dir)pic->pins[pic->pgd-1].value=(pic->ram[P18_DEBUG]&0x08)>>3;
           if(!pic->pins[pic->pgc-1].dir)pic->pins[pic->pgc-1].value=(pic->ram[P18_DEBUG]&0x04)>>2;
*/
           pic->ram[TRISB]= (pic->ram[TRISB]&0x3F)| ((pic->ram[P18_DEBUG] &0x03)<<6);
           
           if(!(pic->ram[P18_DEBUG] &0x02))pic->ram[PORTB]=(pic->ram[PORTB]&0x7F)| ((pic->ram[P18_DEBUG] &0x08)<<4); 
           if(!(pic->ram[P18_DEBUG] &0x01))pic->ram[PORTB]=(pic->ram[PORTB]&0xBF)| ((pic->ram[P18_DEBUG] &0x04)<<4); 
                
          };
        }; 

   };





//PINOUTS
  
 if((pic->ram[P18_PORTA] != pic->porta)||
    (pic->ram[P18_PORTB] != pic->portb)||
    (pic->ram[P18_PORTC] != pic->portc)||
    (pic->ram[P18_PORTD] != pic->portd)||
    (pic->ram[P18_PORTE] != pic->porte))
 {
   for(i=0;i<pic->PINCOUNT;i++)
   {
    if(pic->pins[i].port)
     switch(pic->pins[i].dir)
     {
	case PD_OUT:
//	    case 7:
//               if((pic->ram[P18_RCSTA] & 0x80)==0x80)break; 
//	    case 17:
//              if((pic->ram[P18_RCSTA] & 0x80)==0x80)break;
	   if(pic->pins[i].ptype > 2)break;	 
              val=0x01<<(pic->pins[i].pord);
              port=pic->pins[i].port;
              pic->pins[i].value= ((pic->ram[port] & val) != 0);
	      pic->pins[i].lvalue=pic->pins[i].value;
	  break;
	case PD_IN:
              val=0x01<<(pic->pins[i].pord);
              port=pic->pins[i].port;
              pic->pins[i].lvalue= ((pic->ram[port] & val) != 0); //latch
              pic18_wr_pin(pic,i+1,pic->pins[i].value);
	break;
	default:
	break;
     };
    } 
  }

  pic->porta=pic->ram[P18_PORTA];
  pic->portb=pic->ram[P18_PORTB];
  pic->portc=pic->ram[P18_PORTC];
  pic->portd=pic->ram[P18_PORTD];
  pic->porte=pic->ram[P18_PORTE];

 if((pic->ram[P18_TRISA] != pic->trisa)||
    (pic->ram[P18_TRISB] != pic->trisb)||
    (pic->ram[P18_TRISC] != pic->trisc)||
    (pic->ram[P18_TRISD] != pic->trisd)||
    (pic->ram[P18_TRISE] != pic->trise))
 {
   for(i=0;i<pic->PINCOUNT;i++)
   {
     if(pic->pins[i].port)
     {
     val=0x01<<(pic->pins[i].pord);
     tris=pic->pins[i].port+0x12;
     if((pic->ram[tris] & val)==0)
     {
       pic->pins[i].dir=PD_OUT;
       pic18_wr_pin(pic,i+1,pic->pins[i].lvalue);
     }
     else
     {
       val=pic->pins[i].dir;
       pic->pins[i].dir=PD_IN;
       if(val != PD_IN)pic18_wr_pin(pic,i+1,pic->pins[i].ovalue);
     }
     }

   }
 }


  pic->trisa=pic->ram[P18_TRISA];
  pic->trisb=pic->ram[P18_TRISB];
  pic->trisc=pic->ram[P18_TRISC];
  pic->trisd=pic->ram[P18_TRISD];
  pic->trise=pic->ram[P18_TRISE];

  
//interrupt
if(pic->s2 == 0)
{
  int iret=interrupt18(pic,print); 
  if (iret)
  {
     pic->sleep=0; 
     if(print)printf("interrupt!\n");
     if((pic->ram[P18_STKPTR] & 0x1F) < 31 )
     {
       pic->stack[pic->ram[P18_STKPTR]& 0x1F]=pic->pc;
       pic->ram[P18_STKPTR]=(pic->ram[P18_STKPTR] &0xC0) | ((pic->ram[P18_STKPTR] &0x1F)+1);    
       if((pic->ram[P18_STKPTR]& 0x1F) == 31)pic->ram[P18_STKPTR]|=0x80; //set STKFUL
     }
     if((pic->ram[P18_STKPTR] & 0x1F) >0)
     {
        pic->ram[P18_TOSL]=((pic->stack[(pic->ram[P18_STKPTR] & 0x1F) -1])&0x0000FF);  
        pic->ram[P18_TOSU]=((pic->stack[(pic->ram[P18_STKPTR] & 0x1F)-1])&0x1F0000)>>16; 
        pic->ram[P18_TOSH]=((pic->stack[(pic->ram[P18_STKPTR] & 0x1F)-1])&0x00FF00)>>8;   
     }
      else
      {
        pic->ram[P18_TOSL]=0;
        pic->ram[P18_TOSH]=0;
        pic->ram[P18_TOSU]=0;
      }
     //fast stack       
     pic->ram[P18_WS]=pic->w; 	 
     pic->ram[P18_STATUSS]=pic->ram[P18_STATUS];
     pic->ram[P18_BSRS]=pic->ram[P18_BSR];

     
     if(iret ==  2)
     {
       pic->ram[P18_INTCON]&=~0x40;//GIEL
       pic->pc=0x0018;
       pic->intlv|=0x02;
     }
     else
     {
       pic->ram[P18_INTCON]&=~0x80;//GIE/GIEH
       pic->pc=0x0008;
       pic->intlv|=0x01;
     };
     pic->s2=1;
  }  
}

};
   
