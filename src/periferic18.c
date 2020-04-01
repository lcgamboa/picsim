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
#include"../include/picsim.h"
#include"../include/periferic18.h"



const int fpw2_[8]={1,2,4,8,16,32,64,128};


extern void pic_decode_18(void);

int 
pic18_wr_pin(unsigned char pin,unsigned char value)
{
   unsigned char val;

   if((pin-1) < pic->PINCOUNT)
   {
          pic->pins[(pin-1)].value=value;
          
          if((pic->pins[(pin-1)].pord >= 0)&&(pic->pins[(pin-1)].port))
          {
     	      val=0x01<<(pic->pins[(pin-1)].pord);
              if((pic->pins[(pin-1)].value) == 1)
                (*pic->pins[(pin-1)].port)|=val;
              else	
                (*pic->pins[(pin-1)].port)&=~val;
#ifdef ICSPDBG  
              if((pic->pins[(pin-1)].port == pic->P18map.PORTB)&&((*pic->P18map.DEBUG) & 0x80)) 
              {  
                (*pic->P18map.DEBUG)= ((*pic->P18map.DEBUG)&0xF3)|(((*pic->P18map.PORTB) &0xC0)>>4) ; //espelhamento debug
              } 
#endif              
	   }

     return 1;
   } 
   else
     return 0;
};

inline static int interrupt18(void)
{
//interrupt

  if((*pic->P18map.RCON) & 0x80) //priority 
  {
    //GIEH
    if((*pic->P18map.INTCON) & 0x80)
    {
      //T0IE  T0IF
      if(((*pic->P18map.INTCON)&0x20)&&((*pic->P18map.INTCON)&0x04)&&((*pic->P18map.INTCON2) & 0x04)) return 1;
      //INTE INTF
      if(((*pic->P18map.INTCON)&0x10)&&((*pic->P18map.INTCON)&0x02)) return 1;
      //RBIE
      if(((*pic->P18map.INTCON)&0x08)&&((*pic->P18map.INTCON)&0x01)&&((*pic->P18map.INTCON2) & 0x01)) return 1;
      //EEIE
      //if(((*pic->P18map.PIE1) & 0x80)&&((*pic->P18map.PIR1) & 0x80)&&((*pic->P18map.IPR1) & 0x80)) return 1;
      //CMIE CMIF
      //if(((*pic->P18map.PIE1) & 0x40)&&((*pic->P18map.PIR1) & 0x40)&&((*pic->P18map.IPR1) & 0x40)) return 1;
      //ADIE ADIF 
      if(((*pic->P18map.PIE1) & 0x40)&&((*pic->P18map.PIR1) & 0x40)&&((*pic->P18map.IPR1) & 0x40)) return 1;
      //RCIE RCIF
      if(((*pic->P18map.PIE1) & 0x20)&&((*pic->P18map.PIR1) & 0x20)&&((*pic->P18map.IPR1) & 0x20)) return 1;
      //TXIE TXIF
      if(((*pic->P18map.PIE1) & 0x10)&&((*pic->P18map.PIR1) & 0x10)&&((*pic->P18map.IPR1) & 0x10)) return 1;
      //SSPIE
      if(((*pic->P18map.PIE1) & 0x08)&&((*pic->P18map.PIR1) & 0x08)&&((*pic->P18map.IPR1) & 0x08)) return 1;
      //CCP1IE CCP1IF
      if(((*pic->P18map.PIE1) & 0x04)&&((*pic->P18map.PIR1) & 0x04)&&((*pic->P18map.IPR1) & 0x04)) return 1;
      //TMR2IE TMR2IF
      if(((*pic->P18map.PIE1) & 0x02)&&((*pic->P18map.PIR1) & 0x02)&&((*pic->P18map.IPR1) & 0x02)) return 1;
      //TMR1IE TMR1IF
      if(((*pic->P18map.PIE1) & 0x01)&&((*pic->P18map.PIR1) & 0x01)&&((*pic->P18map.IPR1) & 0x01)) return 1;
      //TMR3IE TMR3IF
      if(((*pic->P18map.PIE2) & 0x02)&&((*pic->P18map.PIR2) & 0x02)&&((*pic->P18map.IPR2) & 0x02)) return 1;
      //CCP2IE CCP2IF
      if(((*pic->P18map.PIE2) & 0x01)&&((*pic->P18map.PIR2) & 0x01)&&((*pic->P18map.IPR2) & 0x01)) return 1;
      //INT1E INT1F
      if(((*pic->P18map.INTCON3) & 0x08)&&((*pic->P18map.INTCON3) & 0x01)&&((*pic->P18map.INTCON3) & 0x40)) return 1;
      //INT2E INT2F
      if(((*pic->P18map.INTCON3) & 0x10)&&((*pic->P18map.INTCON3) & 0x02)&&((*pic->P18map.INTCON3) & 0x80)) return 1;
    //GIEL
     if((*pic->P18map.INTCON) & 0x40)
     { 
      //T0IE  T0IF
      if(((*pic->P18map.INTCON)&0x20)&&((*pic->P18map.INTCON)&0x04)&&(!((*pic->P18map.INTCON2) & 0x04))) return 2;
      //RBIE
      if(((*pic->P18map.INTCON)&0x08)&&((*pic->P18map.INTCON)&0x01)&&(!((*pic->P18map.INTCON2) & 0x01))) return 2;
      //EEIE
      //if(((*pic->P18map.PIE1) & 0x80)&&((*pic->P18map.PIR1) & 0x80)&&(!((*pic->P18map.IPR1) & 0x80))) return 2;
      //CMIE CMIF
      //if(((*pic->P18map.PIE1) & 0x40)&&((*pic->P18map.PIR1) & 0x40)&&(!((*pic->P18map.IPR1) & 0x40))) return 2;
      //ADIE ADIF 
      if(((*pic->P18map.PIE1) & 0x40)&&((*pic->P18map.PIR1) & 0x40)&&(!((*pic->P18map.IPR1) & 0x40))) return 2;
      //RCIE RCIF
      if(((*pic->P18map.PIE1) & 0x20)&&((*pic->P18map.PIR1) & 0x20)&&(!((*pic->P18map.IPR1) & 0x20))) return 2;
      //TXIE TXIF
      if(((*pic->P18map.PIE1) & 0x10)&&((*pic->P18map.PIR1) & 0x10)&&(!((*pic->P18map.IPR1) & 0x10))) return 2;
      //SSPIE
      if(((*pic->P18map.PIE1) & 0x08)&&((*pic->P18map.PIR1) & 0x08)&&(!((*pic->P18map.IPR1) & 0x08))) return 2;
      //CCP1IE CCP1IF
      if(((*pic->P18map.PIE1) & 0x04)&&((*pic->P18map.PIR1) & 0x04)&&(!((*pic->P18map.IPR1) & 0x04))) return 2;
      //TMR2IE TMR2IF
      if(((*pic->P18map.PIE1) & 0x02)&&((*pic->P18map.PIR1) & 0x02)&&(!((*pic->P18map.IPR1) & 0x02))) return 2;
      //TMR1IE TMR1IF
      if(((*pic->P18map.PIE1) & 0x01)&&((*pic->P18map.PIR1) & 0x01)&&(!((*pic->P18map.IPR1) & 0x01))) return 2;
      //CCP2IE CCP2IF      
      if(((*pic->P18map.PIE2) & 0x01)&&((*pic->P18map.PIR2) & 0x01)&&(!((*pic->P18map.IPR2) & 0x01))) return 2;
      //TMR3IE TMR3IF
      if(((*pic->P18map.PIE2) & 0x02)&&((*pic->P18map.PIR2) & 0x02)&&(!((*pic->P18map.IPR2) & 0x02))) return 2;
      //INT1E INT1F
      if(((*pic->P18map.INTCON3) & 0x08)&&((*pic->P18map.INTCON3) & 0x01)&&(!((*pic->P18map.INTCON3) & 0x40))) return 2;
      //INT2E INT2F
      if(((*pic->P18map.INTCON3) & 0x10)&&((*pic->P18map.INTCON3) & 0x02)&&(!((*pic->P18map.INTCON3) & 0x80))) return 2;
    }
    }
  }
  else //legacy
  {
    //GIE
    if((*pic->P18map.INTCON) & 0x80)
    {
      //T0IE  T0IF
      if(((*pic->P18map.INTCON)&0x20)&&((*pic->P18map.INTCON)&0x04)) return 1;
      //INTE INTF
      if(((*pic->P18map.INTCON)&0x10)&&((*pic->P18map.INTCON)&0x02)) return 1;
      //RBIE
      if(((*pic->P18map.INTCON)&0x08)&&((*pic->P18map.INTCON)&0x01)) return 1;
      //INT1E INT1F
      if(((*pic->P18map.INTCON3) & 0x08)&&((*pic->P18map.INTCON3) & 0x01)) return 1;
      //INT2E INT2F
      if(((*pic->P18map.INTCON3) & 0x10)&&((*pic->P18map.INTCON3) & 0x02)) return 1;
      //PEIE	
      if(((*pic->P18map.INTCON) & 0x40) == 0x40)
      {
        //EEIE
        //if(((*pic->P18map.PIE1) & 0x80)&&((*pic->P18map.PIR1) & 0x80)) return 1;
        //CMIE CMIF
        //if(((*pic->P18map.PIE1) & 0x40)&&((*pic->P18map.PIR1) & 0x40)) return 1;
        //ADIE ADIF 
        if(((*pic->P18map.PIE1) & 0x40)&&((*pic->P18map.PIR1) & 0x40)) return 1;
        //RCIE RCIF
        if(((*pic->P18map.PIE1) & 0x20)&&((*pic->P18map.PIR1) & 0x20)) return 1;
        //TXIE TXIF
        if(((*pic->P18map.PIE1) & 0x10)&&((*pic->P18map.PIR1) & 0x10)) return 1;
        //SSPIE
        if(((*pic->P18map.PIE1) & 0x08)&&((*pic->P18map.PIR1) & 0x08)) return 1;
        //CCP1IE CCP1IF
        if(((*pic->P18map.PIE1) & 0x04)&&((*pic->P18map.PIR1) & 0x04)) return 1;
        //TMR2IE TMR2IF
        if(((*pic->P18map.PIE1) & 0x02)&&((*pic->P18map.PIR1) & 0x02)) return 1;
        //TMR1IE TMR1IF
        if(((*pic->P18map.PIE1) & 0x01)&&((*pic->P18map.PIR1) & 0x01)) return 1;
        //TMR3IE TMR3IF
        if(((*pic->P18map.PIE2) & 0x02)&&((*pic->P18map.PIR2) & 0x02)) return 1;
        //CCP2IE CCP2IF
        if(((*pic->P18map.PIE2) & 0x01)&&((*pic->P18map.PIR2) & 0x01)) return 1;
      }
    }
  }

 return 0;
}

void
periferic18_rst(void)
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
pic->wdt=0;

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
periferic18_step_in(void)
{
//int i;
float val;
int chn;
short dval;
unsigned char temp;

#ifdef ICSPDBG  
//DEBUG
 if(pic->getconf(CFG_DEBUG)) //DEBUG ON
 {
   if(pic->debug == 1)(*pic->P18map.DEBUG)|=0x80;
 } 
#endif


//MSSP

 if(((*pic->P18map.SSPCON1) & 0x20) ==0x20) //SSPEN
 {
   
    switch((*pic->P18map.SSPCON1))
    {
            case 0x00://SPI Master mode, clock = FOSC/4
            case 0x01://SPI Master mode, clock = FOSC/16
            case 0x02://SPI Master mode, clock = FOSC/64
            case 0x03://SPI Master mode, clock = TMR2 output/2
            //TODO: CLK POL and FREQ READ OP
                if (pic->lram == sfr_addr(pic->P18map.SSPBUF))
                {
                  pic->ssp_bit=8;
                  pic->ssp_sck=0;
                  pic18_wr_pin (pic->sck, 0);
                }
                
                if(pic->ssp_bit)
                {
                    if(pic->ssp_sck == 1)
                    {
                      pic18_wr_pin (pic->sdo, (((*pic->P18map.SSPBUF) & (1 << ((pic->ssp_bit-1)))) > 0));
                      pic18_wr_pin (pic->sck, 1); 
                    }
                    else if(pic->ssp_sck == 2)
                    {
                      pic18_wr_pin (pic->sck, 0); 
                      pic->ssp_sck=0;
                      pic->ssp_bit--;
                    }
                    pic->ssp_sck++;
                }
                break;
            //case 0x04://SPI Slave mode, clock = SCK pin. SS pin control enabled.
            case 0x05://SPI Slave mode, clock = SCK pin. SS pin control disabled.
      pic->pins[pic->sdi-1].dir=PD_IN; 	
 
      if(pic->rram == sfr_addr(pic->P18map.SSPBUF))
      {
         (*pic->P18map.SSPSTAT)&=~0x01; //BF
      } 	

        pic->ssp_scka=pic->ssp_sck; 
        pic->ssp_sck= pic->pins[pic->sck-1].value;


	if((pic->ssp_scka == 0)&&(pic->ssp_sck == 1)) //CKP =0 CKE =0     //coloca saida na borda de subida
        {
           pic18_wr_pin(pic->sdo, (((*pic->P18map.SSPBUF) & (1 <<(7-pic->ssp_bit))) > 0));
        }


	if((pic->ssp_scka == 1)&&(pic->ssp_sck == 0)) //CKP =0 CKE =0    //le na borda de decida
        {
	   pic->sspsr|= (pic->pins[pic->sdi-1].value) << (7-pic->ssp_bit);
           
           //printf("SSP bit =%i    REC=%#02X   SEND=%#02X \n",pic->ssp_bit,pic->sspsr, (*pic->P18map.SSPBUF));

	   pic->ssp_bit++;
        }

	if(pic->ssp_bit >= 8)
        {
//	   printf("MSSP TX=%#02X  RX=%#02X\n",(*pic->P18map.SSPBUF),pic->sspsr);
           (*pic->P18map.SSPBUF)=pic->sspsr;
           pic->sspsr =0;
	   (*pic->P18map.SSPSTAT)|=0x01; //BF
	           
           //PSPIF
           (*pic->P18map.PIR1)|=0x08; //PSPIF
	   pic->ssp_bit=0;
        }
        break;	
            //case 0x06://I2C Slave mode, 7-bit address
            //case 0x07://I2C Slave mode, 10-bit address
            case 0x08://I2C Master mode, clock = FOSC /(4 * (SSPADD + 1))
       pic->ssp_sck++;

       if(pic->ssp_sck == (((*pic->P18map.SSPADD)+1/2)-1))
       {
       
         if(((*pic->P18map.SSPCON2) & 0x01)) //start
         {
           pic->pins[pic->sck-1].dir=PD_OUT; 	
           pic->pins[pic->sdi-1].dir=PD_OUT; 	
           pic->pins[pic->sdi-1].value=1;
           pic->pins[pic->sck-1].value=1;
        
           //printf("I2C_start 1\n");
         }
         else if(((*pic->P18map.SSPCON2) & 0x02)) //restart
         {
           pic->pins[pic->sdi-1].dir=PD_OUT; 	
           pic->pins[pic->sdi-1].value=1;
           pic->pins[pic->sck-1].value=1;
           //printf("restar1\n");
         } 
         else if(((*pic->P18map.SSPCON2) & 0x04)) //stop
         {
           pic->pins[pic->sdi-1].dir=PD_OUT; 	
           pic->pins[pic->sdi-1].value=0;
           pic->pins[pic->sck-1].value=1;
           //printf("stop1\n");
         } 
       }

       if(pic->ssp_sck == (((*pic->P18map.SSPADD)+1/2)+1))
       {
       
         if(((*pic->P18map.SSPCON2) & 0x01)) //start
         {
           (*pic->P18map.SSPCON2) &=~ 0x01;
           
           pic->pins[pic->sdi-1].value=0;
           pic->pins[pic->sck-1].value=1;
           
           //printf("start 2\n");
         }
         else if(((*pic->P18map.SSPCON2) & 0x02)) //restart
         {
           (*pic->P18map.SSPCON2) &=~ 0x02;

           pic->pins[pic->sdi-1].value=0;
           pic->pins[pic->sck-1].value=1;
           //printf("restart 2\n");
         } 
         else if(((*pic->P18map.SSPCON2) & 0x04)) //stop
         {
           (*pic->P18map.SSPCON2) &=~ 0x04;
         
           pic->ssp_bit=10;

           pic->pins[pic->sdi-1].value=1;
           pic->pins[pic->sck-1].value=1;
           //printf("stop 2\n");
         } 
       }

 


        if(pic->lram == sfr_addr(pic->P18map.SSPBUF)) //write init
        {
         (*pic->P18map.SSPSTAT)|=0x04; //R/W
         //printf("SPPBUF write (%#02X)!!!!\n",(*pic->P18map.SSPBUF));	
         pic->ssp_bit=0;
         pic->pins[pic->sdi-1].dir=PD_OUT; 	
         (*pic->P18map.SSPSTAT)|=0x01; //BF
        } 	
       
        if(!((*pic->P18map.SSPCON2) & 0x08)) pic->ssp_scka=0;

        if(((*pic->P18map.SSPCON2) & 0x08) && (pic->ssp_scka == 0)) //read init
        {
          pic->ssp_bit=0;

          //printf("I2C read\n");
          (*pic->P18map.SSPBUF)=0;
          pic->pins[pic->sdi-1].dir=PD_IN; 	
          pic->ssp_ck=pic->pins[pic->sck-1].value;
          (*pic->P18map.SSPSTAT)&=~0x01; //BF

          pic->ssp_scka=1;
        }


       if(pic->ssp_sck > (*pic->P18map.SSPADD))
       {
          pic->ssp_sck=0;

        //write
        if(( ((*pic->P18map.SSPSTAT) & 0x04) )&&( pic->ssp_bit <= 9))
        {
           pic->pins[pic->sck-1].value^=0x01;


           if((pic->pins[pic->sck-1].value == 0)&&(pic->ssp_bit <= 8))
           {
             pic->pins[pic->sdi-1].value=((*pic->P18map.SSPBUF) & (0x01<<(7-pic->ssp_bit))) >0; 
             pic->ssp_bit++;
             if(pic->ssp_bit ==9)
             { 
               pic->pins[pic->sdi-1].dir=PD_IN;
             } 
           }


           if((pic->pins[pic->sck-1].value == 1)&&(pic->ssp_bit  > 8))
           {
             if(pic->pins[pic->sdi-1].value)
               (*pic->P18map.SSPCON2)|=0x40; //ACKSTAT
             else
               (*pic->P18map.SSPCON2)&=~0x40; //ACKSTAT

             (*pic->P18map.SSPSTAT)&=~0x04; //R/W
             (*pic->P18map.PIR1)|=0x08;//SSPIF
             (*pic->P18map.SSPSTAT)&=~0x01; //BF
             pic->ssp_bit++;
           }

      //    printf("wbit(%i)  sck=%i  sda=%i \n",pic->ssp_bit,pic->pins[pic->sck-1].value,pic->pins[pic->sdi-1].value); 
        }
       
      //read 
        if((((*pic->P18map.SSPCON2) & 0x08)||((*pic->P18map.SSPCON2)& 0x10))&&( pic->ssp_bit <= 9))
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
             (*pic->P18map.SSPBUF)|=(pic->pins[pic->sdi-1].value << (8 -pic->ssp_bit)); 
             if(pic->ssp_bit == 8)
             {
                (*pic->P18map.SSPCON2)&=~0x10;//ACKDT
                (*pic->P18map.PIR1)|=0x08;//SSPIF
                pic->ssp_bit++;
               
                 (*pic->P18map.SSPCON2)&=~0x08;
                (*pic->P18map.SSPSTAT)|=0x01; //BF
                //printf("recebido1 %02X\n",(*pic->P18map.SSPBUF));
             }
           }

           if(((*pic->P18map.SSPCON2)& 0x10)&&(pic->pins[pic->sck-1].value == 1)&&(pic->ssp_bit  > 8))
           {
             pic->pins[pic->sdi-1].dir=PD_OUT; 	
             pic->pins[pic->sdi-1].value=((*pic->P18map.SSPCON2)&0x20) >0 ;
             (*pic->P18map.PIR1)|=0x08;//SSPIF;
             pic->ssp_bit++;

             (*pic->P18map.SSPCON2)&=~0x10;//ACKDT

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
    break;   
            //case 0x09://Reserved
            //case 0x0A://Reserved
            //case 0x0B://I2C Firmware Controlled Master mode (Slave Idle)
            //case 0x0C://Reserved
            //case 0x0D://Reserved
            //case 0x0E://I2C Slave mode, 7-bit address with Start and Stop bit interrupts enabled
            //case 0x0F://I2C Slave mode, 10-bit address with Start and Stop bit interrupts enabled
    default: //unknown
	printf(" %#02X SPI mode not implemented!\n",((*pic->P18map.SSPCON1) & 0x0F));
	break;
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

  if(pic->ADCCOUNT > 0 )  
  {

  if(((*pic->P18map.ADCON0) & 0x05 ) == 0x05) // ADON and GO/DONE
  {
   pic->adcstep++;
   if(pic->adcstep > 10 )
   {
     chn=((*pic->P18map.ADCON0)&0x38)>>3;

     if(pic->pins[pic->adc[chn]-1].ptype == PT_ANALOG)
     {
       val=pic->pins[pic->adc[chn]-1].avalue;
     }
     else
     {
       val=0;
     }

      dval=((1023*val)/5.0);
   
      if(((*pic->P18map.ADCON1)&0x80) == 0x80)//ADFM
      { 
        (*pic->P18map.ADRESH)=(dval & 0xFF00)>>8;   	
        (*pic->P18map.ADRESL)=(dval & 0x00FF);   	
      }
      else
      {
        dval= dval <<6;	
        (*pic->P18map.ADRESH)=(dval & 0xFF00)>>8;   	
        (*pic->P18map.ADRESL)=(dval & 0x00FF);   	
      }
    
      (*pic->P18map.ADCON0)&= ~0x04; 
      
      //ADIF
      (*pic->P18map.PIR1)|=0x40;

      pic->adcstep=0;
    }
  }
  else
  {
   pic->adcstep=0;
  }

 
    
  if(((*pic->P18map.ADCON1)&0x0F) != pic->adcon1)
  {
    switch((*pic->P18map.ADCON1)&0x0F)
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

    pic->adcon1=(*pic->P18map.ADCON1)&0x0F;	
   }
  
  };
}
else //PIC18F4620 PIC18F4520 and PIC18F4550
{

  if(pic->ADCCOUNT > 0 )  
  {

  if(((*pic->P18map.ADCON0) & 0x03 ) == 0x03) //ADON and GO/DONE
  {
   pic->adcstep++;
   if(pic->adcstep > 10 )
   {
     chn=((*pic->P18map.ADCON0)&0x3C)>>2;

     if((pic->pins[pic->adc[chn]-1].ptype == PT_ANALOG)&&(chn < pic->ADCCOUNT))
     {
       val=pic->pins[pic->adc[chn]-1].avalue;
     }
     else
     {
       val=0;
     }

      dval=((1023*val)/5.0);
   
      if((*pic->P18map.ADCON2)&0x80)//ADFM
      { //Rigth
        (*pic->P18map.ADRESH)=(dval & 0xFF00)>>8;   	
        (*pic->P18map.ADRESL)=(dval & 0x00FF);   	
      }
      else
      { //left
        dval= dval <<6;	
        (*pic->P18map.ADRESH)=(dval & 0xFF00)>>8;   	
        (*pic->P18map.ADRESL)=(dval & 0x00FF);   	
      }
    
      (*pic->P18map.ADCON0)&= ~0x02; 
      
      //ADIF
      (*pic->P18map.PIR1)|=0x40;

      pic->adcstep=0;
    }
  }  
  else
  {
   pic->adcstep=0;
  }

 
    
  if(((*pic->P18map.ADCON1)&0x0F) != pic->adcon1)
  {
   int i;
   for(i=0;i < pic->ADCCOUNT;i++)  
   {
        if(((*pic->P18map.ADCON1)&0x0F) <  (0x0F-i))
	  pic->pins[pic->adc[i]-1].ptype=PT_ANALOG;
        else
	  pic->pins[pic->adc[i]-1].ptype=PT_CMOS;
    } 

    if((*pic->P18map.ADCON1) & 0x20)//VCFG1  
	pic->pins[pic->adc[2]-1].ptype=PT_ANAREF;
    if((*pic->P18map.ADCON1) & 0x10)//VCFG0  
	pic->pins[pic->adc[3]-1].ptype=PT_ANAREF;

    pic->adcon1=(*pic->P18map.ADCON1)&0x0F;	
   }
  
 
  };

}


//INT0
   if((pic->pins[pic->int0-1].dir == PD_IN)&&(pic->pins[pic->int0-1].value != pic->int0v))
   {
     if(((!pic->int0v) &&((*pic->P18map.INTCON2) & 0x40))||((pic->int0v) && (!((*pic->P18map.INTCON2) & 0x40))))
     {
        (*pic->P18map.INTCON)|=0x02;//INTF
     } 
   } 
   pic->int0v=pic->pins[pic->int0-1].value; 

//INT1
   if((pic->pins[pic->int1-1].dir == PD_IN)&&(pic->pins[pic->int1-1].value != pic->int1v))
   {
     if(((!pic->int1v) &&((*pic->P18map.INTCON2) & 0x20))||((pic->int1v) && (!((*pic->P18map.INTCON2) & 0x20))))
     {
        (*pic->P18map.INTCON3)|=0x01;//INT1F
     } 
   } 
   pic->int1v=pic->pins[pic->int1-1].value; 

//INT2
   if((pic->pins[pic->int2-1].dir == PD_IN)&&(pic->pins[pic->int2-1].value != pic->int2v))
   {
     if(((!pic->int2v) &&((*pic->P18map.INTCON2) & 0x10))||((pic->int2v) && (!((*pic->P18map.INTCON2) & 0x10))))
     {
        (*pic->P18map.INTCON3)|=0x02;//INT2F
     } 
   } 
   pic->int2v=pic->pins[pic->int2-1].value; 

//PORTB
   temp=(*pic->P18map.TRISB)&0xF0;
   if(((*pic->P18map.PORTB)&temp) != (pic->portb&temp)) 
   {
      pic->portbm=1;
   }

if(pic->rram == sfr_addr(pic->P18map.PORTB))
{
  pic->portbm=0;
  //Only disable mismatch
  //(*pic->P18map.INTCON)&=~0x01;//RBIF
}

if(pic->portbm)
{
  (*pic->P18map.INTCON)|=0x01;//RBIF
}  



//TMR0
  if((*pic->P18map.T0CON) & 0x80) //TMR0ON
  {
  if((((*pic->P18map.T0CON) & 0x20) == 0x00 )||  //TOCS=FOSC/4
    ((((*pic->P18map.T0CON) & 0x30) == 0x20 )&&((pic->t0cki_ == 0)&&(pic->pins[pic->t0cki-1].value==1)))|| //T0CS=t0cki  T0SE =0
    ((((*pic->P18map.T0CON) & 0x30) == 0x30 )&&((pic->t0cki_ == 1)&&(pic->pins[pic->t0cki-1].value==0))))  //T0CS=t0cki  T0SE =1
  {
     pic->cp0++;

     if(pic->lram == sfr_addr(pic->P18map.TMR0L))pic->cp0=0; //RESET prescaler	 

     if(((*pic->P18map.T0CON) & 0x08) == 0x08) //PSA
     {

        if(((*pic->P18map.T0CON) & 0x40)&& (((*pic->P18map.TMR0L)+1) == 0x100))(*pic->P18map.INTCON)|=0x04;//T0IF

        (*pic->P18map.TMR0L)++;
        if((!(*pic->P18map.TMR0L))&&(!((*pic->P18map.T0CON) & 0x40)))
        {
          if(((*pic->P18map.TMR0H)+1) == 0x100)(*pic->P18map.INTCON)|=0x04;//T0IF
          (*pic->P18map.TMR0H)++;
        }
        pic->cp0=0;
     }
     else
     { 
        if(pic->cp0 >= 2*(fpw2_[(*pic->P18map.T0CON)&0x07]) )
        {
  
          if(((*pic->P18map.T0CON) & 0x40)&& (((*pic->P18map.TMR0L)+1) == 0x100))(*pic->P18map.INTCON)|=0x04;//T0IF
          
          (*pic->P18map.TMR0L)++;
          if((!(*pic->P18map.TMR0L))&&(!((*pic->P18map.T0CON) & 0x40)))
          {
            if(((*pic->P18map.TMR0H)+1) == 0x100)(*pic->P18map.INTCON)|=0x04;//T0IF
            (*pic->P18map.TMR0H)++;
          }
          pic->cp0=0;
        }
     }
  }
  } 
  pic->t0cki_=pic->pins[pic->t0cki-1].value; 


//TMR1

  if((((*pic->P18map.T1CON) & 0x03) == 0x01 )||  //TMRICS=FOSC/4 TMREN=1
    ((((*pic->P18map.T1CON) & 0x03) == 0x03 )&&((pic->t1cki_ == 0)&&(pic->pins[pic->t1cki-1].value==1)))) //TMRICS=t1cki  TMREN=1
  {
     pic->cp1++;
     
     if(pic->cp1 >= fpw2_[((*pic->P18map.T1CON)&0x30)>>4]) 
     {
       (*pic->P18map.TMR1L)++;
       if((*pic->P18map.TMR1L) == 0)
       {
        if(((*pic->P18map.TMR1H)+1) == 0x100)(*pic->P18map.PIR1)|=0x01;//TMR1IF
        (*pic->P18map.TMR1H)++;
       }
       pic->cp1=0;
     }
 
   //CCP - only when TMR1 is ON
   //CCP1 compare modes 
     if((pic->CCPCOUNT >= 1)&&(pic->ccp[0] > 0)&&(((*pic->P18map.CCP1CON) & 0x0C) == 0x08)&&(!((*pic->P18map.T3CON) & 0x40)))   
     {
       if(((*pic->P18map.TMR1H)==(*pic->P18map.CCPR1H))&&((*pic->P18map.TMR1L)==(*pic->P18map.CCPR1L)))//match !!
       {
          (*pic->P18map.PIR1)|=0x04;//CCP1IF
          switch((*pic->P18map.CCP1CON) & 0x03)
          {
            case 0://set output
              if(pic->pins[pic->ccp[0]-1].dir == PD_OUT)
                (*pic->pins[(pic->ccp[0]-1)].port)|=0x01<<(pic->pins[(pic->ccp[0]-1)].pord);
              break;
            case 1://clear output
              if(pic->pins[pic->ccp[0]-1].dir == PD_OUT)
                (*pic->pins[(pic->ccp[0]-1)].port)&=~(0x01<<(pic->pins[(pic->ccp[0]-1)].pord));
              break;
            case 2://software interrupt
              break;
            case 3://trigger special event
              (*pic->P18map.TMR1H)=0;
              (*pic->P18map.TMR1L)=0;
              break;
          }
       }
     }
//CCP2 compare modes 
     if((pic->CCPCOUNT >= 2)&&(pic->ccp[1] > 0)&&(((*pic->P18map.CCP2CON) & 0x0C) == 0x08)&&(!((*pic->P18map.T3CON) & 0x48)))
     {
       if(((*pic->P18map.TMR1H)==(*pic->P18map.CCPR2H))&&((*pic->P18map.TMR1L)==(*pic->P18map.CCPR2L)))//match !!
       {
          (*pic->P18map.PIR2)|=0x01;//CCP2IF
          switch((*pic->P18map.CCP2CON) & 0x03)
          {
            case 0://set output
              if(pic->pins[pic->ccp[1]-1].dir == PD_OUT)
                (*pic->pins[(pic->ccp[1]-1)].port)|=0x01<<(pic->pins[(pic->ccp[1]-1)].pord);
              break;
            case 1://clear output
              if(pic->pins[pic->ccp[1]-1].dir == PD_OUT)
                (*pic->pins[(pic->ccp[1]-1)].port)&=~(0x01<<(pic->pins[(pic->ccp[1]-1)].pord));
              break;
            case 2://software interrupt
              break;
            case 3://trigger special event
              (*pic->P18map.TMR1H)=0;
              (*pic->P18map.TMR1L)=0;
              if(pic->processor == P18F452)
              {
                if((*pic->P18map.ADCON0) & 0x01)(*pic->P18map.ADCON0)|=0x04; //if ad on, enable one conversion
              }
              else
              {
                if((*pic->P18map.ADCON0) & 0x01)(*pic->P18map.ADCON0)|=0x02; //if ad on, enable one conversion  
              }
              break;
          }
       }
     }

  

  } 
  
//TMR3
  if((((*pic->P18map.T3CON) & 0x03) == 0x01 )||  //TMRICS=FOSC/4 TMREN=1
    ((((*pic->P18map.T3CON) & 0x03) == 0x03 )&&((pic->t1cki_ == 0)&&(pic->pins[pic->t1cki-1].value ==1)))) //TMRICS=t1cki  TMREN=1
  {
     pic->cp3++;
     
     if(pic->cp3 >= fpw2_[((*pic->P18map.T3CON)&0x30)>>4]) 
     {
       (*pic->P18map.TMR3L)++;
       if((*pic->P18map.TMR3L) == 0)
       {
        if(((*pic->P18map.TMR3H)+1) == 0x100)(*pic->P18map.PIR2)|=0x02;//TMR3IF
        (*pic->P18map.TMR3H)++;
       }
       pic->cp3=0;
     }

   //CCP - only when TMR3 is ON
   //CCP3 compare modes 
     if((pic->CCPCOUNT >= 1)&&(pic->ccp[0] > 0)&&(((*pic->P18map.CCP1CON) & 0x0C) == 0x08)&&((*pic->P18map.T3CON) & 0x40))   
     {
       if(((*pic->P18map.TMR3H)==(*pic->P18map.CCPR1H))&&((*pic->P18map.TMR3L)==(*pic->P18map.CCPR1L)))//match !!
       {
          (*pic->P18map.PIR1)|=0x04;//CCP1IF
          switch((*pic->P18map.CCP1CON) & 0x03)
          {
            case 0://set output
              if(pic->pins[pic->ccp[0]-1].dir == PD_OUT)
                (*pic->pins[(pic->ccp[0]-1)].port)|=0x01<<(pic->pins[(pic->ccp[0]-1)].pord);
              break;
            case 1://clear output
              if(pic->pins[pic->ccp[0]-1].dir == PD_OUT)
                (*pic->pins[(pic->ccp[0]-1)].port)&=~(0x01<<(pic->pins[(pic->ccp[0]-1)].pord));
              break;
            case 2://software interrupt
              break;
            case 3://trigger special event
              (*pic->P18map.TMR3H)=0;
              (*pic->P18map.TMR3L)=0;
              break;
          }
       }
     }
//CCP2 compare modes 
     if((pic->CCPCOUNT >= 2)&&(pic->ccp[1] > 0)&&(((*pic->P18map.CCP2CON) & 0x0C) == 0x08)&&((*pic->P18map.T3CON) & 0x48))
     {
       if(((*pic->P18map.TMR3H)==(*pic->P18map.CCPR2H))&&((*pic->P18map.TMR3L)==(*pic->P18map.CCPR2L)))//match !!
       {
          (*pic->P18map.PIR2)|=0x01;//CCP2IF
          switch((*pic->P18map.CCP2CON) & 0x03)
          {
            case 0://set output
              if(pic->pins[pic->ccp[1]-1].dir == PD_OUT)
                (*pic->pins[(pic->ccp[1]-1)].port)|=0x01<<(pic->pins[(pic->ccp[1]-1)].pord);
              break;
            case 1://clear output
              if(pic->pins[pic->ccp[1]-1].dir == PD_OUT)
                (*pic->pins[(pic->ccp[1]-1)].port)&=~(0x01<<(pic->pins[(pic->ccp[1]-1)].pord));
              break;
            case 2://software interrupt
              break;
            case 3://trigger special event
              (*pic->P18map.TMR3H)=0;
              (*pic->P18map.TMR3L)=0;
              if(pic->processor == P18F452)
              {
                if((*pic->P18map.ADCON0) & 0x01)(*pic->P18map.ADCON0)|=0x04; //if ad on, enable one conversion
              }
              else
              {
                if((*pic->P18map.ADCON0) & 0x01)(*pic->P18map.ADCON0)|=0x02; //if ad on, enable one conversion  
              }
              break;
          }
       }
     }
   
     
     
     
  } 

  pic->t1cki_=pic->pins[pic->t1cki-1].value; 
 


//TMR2
  
  if(((*pic->P18map.T2CON) & 0x04) == 0x04 )  //TMR2EN
  {
     pic->cp2++;
     
     if(((*pic->P18map.T2CON)&0x02) == 0x02)
     {
       pic->t2pr=16;
     }
     else if (((*pic->P18map.T2CON)&0x01) == 0x01)
     {
       pic->t2pr=4;
     }
     else
     {
       pic->t2pr=1;
     }

     if(pic->cp2 >= pic->t2pr) 
     {
       (*pic->P18map.TMR2)++;
       if((*pic->P18map.TMR2) == (*pic->P18map.PR2))
       {
         (*pic->P18map.TMR2)=0;
         pic->cp2_++;

         if(pic->cp2_ >= ((((*pic->P18map.T2CON)&0x78)>>3)+1) )
         { 
           (*pic->P18map.PIR1)|=0x02; //TMR2IF
           pic->cp2_=0; 
         }

         //PWM
          	
	 if((pic->CCPCOUNT >= 1)&&(pic->ccp[0] > 0)&&((*pic->P18map.CCP1CON)& 0x0C) == 0x0C)
         {
           (*pic->P18map.CCPR1H)=(*pic->P18map.CCPR1L);
           if(pic->pins[pic->ccp[0]-1].dir == PD_OUT)
             (*pic->pins[(pic->ccp[0]-1)].port)=0x01<<(pic->pins[(pic->ccp[0]-1)].pord);
         } 
	 
         if((pic->CCPCOUNT >= 2)&&(pic->ccp[1] > 0)&&((*pic->P18map.CCP2CON)& 0x0C) == 0x0C)
         {
           (*pic->P18map.CCPR2H)=(*pic->P18map.CCPR2L);
           if(pic->pins[pic->ccp[1]-1].dir == PD_OUT)
             (*pic->pins[(pic->ccp[1]-1)].port)|=0x01<<(pic->pins[(pic->ccp[1]-1)].pord);
         } 
	
       }
       pic->cp2=0;
     }
//PWM - only if TMR2 is on

//only use 8 bits ! not 10 bits  
   if((pic->CCPCOUNT >= 1)&&(pic->ccp[0] > 0)&&((*pic->P18map.CCP1CON)& 0x0C) == 0x0C)
   {
      if((*pic->P18map.TMR2) >=  (*pic->P18map.CCPR1H))
      {
        if(pic->pins[pic->ccp[0]-1].dir == PD_OUT)
          (*pic->pins[(pic->ccp[0]-1)].port)&=~(0x01<<(pic->pins[(pic->ccp[0]-1)].pord));
      }
   }	
   
   if((pic->CCPCOUNT >= 2)&&(pic->ccp[1] > 0)&&((*pic->P18map.CCP2CON)& 0x0C) == 0x0C)
   {
      if((*pic->P18map.TMR2) >=  (*pic->P18map.CCPR2H))
      {
        if(pic->pins[pic->ccp[1]-1].dir == PD_OUT)
          (*pic->pins[(pic->ccp[1]-1)].port)&=~(0x01<<(pic->pins[(pic->ccp[1]-1)].pord));
      }
   }	


  } 



//EEPROM
  if(pic->P18map.EECON1)
  {
  if(((*pic->P18map.EECON1) & 0x04) == 0x04 )
  {
    if((*pic->P18map.EECON2) != 0 )
    {
      if((*pic->P18map.EECON2) == 0x55 )
      {
        (*pic->P18map.EECON2) = 0; 
        pic->ee_wr=-1;
      }
      else
      {
        if(((*pic->P18map.EECON2) == 0xAA )&&(pic->ee_wr == -1))
        {
          (*pic->P18map.EECON2) = 0; 
          pic->ee_wr=1;
        }
        else
        {
          (*pic->P18map.EECON2) = 0; 
          pic->ee_wr=0;
        }
      }
    }    
  }



  if(((*pic->P18map.EECON1) & 0x03) != 0x00 )
  {
    if(((*pic->P18map.EECON1) & 0x01) == 0x01 ) //RD
    { 
      if(((*pic->P18map.EECON1) & 0x80) == 0)
      {  
         (*pic->P18map.EEDATA)= pic->eeprom[(*pic->P18map.EEADR)];
      }
/*
      else
      {
         (*pic->P18map.EEDATA)=   (pic->prog[(pic->ram[P18_EEADRH]<<8)|(*pic->P18map.EEADR)])&0x00FF;
         pic->ram[P18_EEDATAH]= ((pic->prog[(pic->ram[P18_EEADRH]<<8)|(*pic->P18map.EEADR)])&0xFF00)>>8;
      }
*/
      (*pic->P18map.EECON1)&=~0x01;  
    }
    else
    {
      if(pic->ee_wr == 1)
      {
        if(((*pic->P18map.EECON1) & 0x80) == 0)
        { 
          pic->eeprom[(*pic->P18map.EEADR)]=(*pic->P18map.EEDATA);
        }
/*
        else
        {
          pic->prog[(pic->ram[P18_EEADRH]<<8)|(*pic->P18map.EEADR)] = (pic->ram[P18_EEDATAH]<<8) | (*pic->P18map.EEDATA);

        }  
*/     
        (*pic->P18map.EECON1)&=~0x02; 
        pic->ee_wr=0;
      } 
    }
  } 
}


//WDT

  if(pic->getconf(CFG_WDT) || ((*pic->P18map.WDTCON) & 0x01))  
  {
//     printf("WDT ON %f   %i  0x%02X\n",pic->twdt ,pic->wdt,(*pic->P18map.RCON));

    pic->twdt+=4.0/pic->freq;
    
      if(pic->twdt > (1e-3*fpw2_[(pic->config[1] & 0x0E00)>>9]))
      {
        pic->twdt=0;
        pic->wdt++;

        if(pic->wdt == pic->WDT_MS) 
        {
         //reset
         pic->wdt=0;
   
         (*pic->P18map.RCON)&=~0x08; //clear TO
           
          
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



   serial();

};

void 
periferic18_step_out(void)
{
int i,val;

unsigned short port;
unsigned short tris;
    
#ifdef ICSPDBG  
	if(pic->lram == sfr_addr(pic->P18map.DEBUG) )
        {
           //printf("---------------> DEBUG write (%#02X)\n",(*pic->P18map.DEBUG));

          if(((*pic->P18map.DEBUG) & 0x80) == 0x80)
          {
           (*pic->P18map.TRISB)= ((*pic->P18map.TRISB)&0x3F)| (((*pic->P18map.DEBUG) &0x03)<<6);
                
           if(!((*pic->P18map.DEBUG) &0x02))(*pic->P18map.PORTB)=((*pic->P18map.PORTB)&0x7F)| (((*pic->P18map.DEBUG) &0x08)<<4); 
           if(!((*pic->P18map.DEBUG) &0x01))(*pic->P18map.PORTB)=((*pic->P18map.PORTB)&0xBF)| (((*pic->P18map.DEBUG) &0x04)<<4); 
             
           //printf("pgd=%i tpgd=%i pgc=%i tpgc=%i\n",pic->pins[pic->pgd-1].value,pic->pins[pic->pgd-1].dir,pic->pins[pic->pgc-1].value,pic->pins[pic->pgc-1].dir);
          }                    
        }

        if(pic->rram == sfr_addr(pic->P18map.DEBUG))
        {
           //printf("---------------> DEBUG read (%#02X)\n",(*pic->P18map.DEBUG));
           
          if(((*pic->P18map.DEBUG) & 0x80) == 0x80)
          {
           (*pic->P18map.TRISB)= ((*pic->P18map.TRISB)&0x3F)| (((*pic->P18map.DEBUG) &0x03)<<6);

           //  printf("pgd=%i tpgd=%i pgc=%i tpgc=%i\n",pic->pins[pic->pgd-1].value,pic->pins[pic->pgd-1].dir,pic->pins[pic->pgc-1].value,pic->pins[pic->pgc-1].dir);
          }      

	     }
/* 
        if(pic->lram == P18_BDMSR0 )
        {
           printf("---------------> BDMSR0 write (%#02X)\n",(*pic->P18map.BDMSR0));
        }
*/

 
//DEBUG
  if(pic->getconf(CFG_DEBUG)) //DEBUG ON
   {
	pic->ocd_pgca=pic->ocd_pgc;
        pic->ocd_pgc=pic->pins[pic->pgc-1].value;

 
        if(((*pic->P18map.DEBUG) & 0x80) == 0)
        {
          pic->dbg++;

          if(((*pic->P18map.DEBUG)&0x20) == 0x20) pic->sstep++;          
 
          if(((pic->ocd_pgca ==1)&&(pic->ocd_pgc == 0)) ||    //HardWare
             (((pic->pc>>1) == (((((*pic->P18map.BDMSR2)&0x0F)<<16)|((*pic->P18map.BDMSR1)<<8)|(*pic->P18map.BDMSR0))/*+1*/ ))&&(pic->dbg > 3 ))|| //Break Point  
              ((((*pic->P18map.DEBUG)&0x20) == 0x20)&&(pic->sstep== 3)))          //step 
          {
          //printf("Debug Halt (%04X)   ",pic->pc);
          
 //         if((pic->ocd_pgca ==1)&&(pic->ocd_pgc == 0)) printf("Hardware \n");                                   //HardWare
 //         if((pic->pc>>1) ==   (((((*pic->P18map.BDMSR2)&0x0F)<<16)|((*pic->P18map.BDMSR1)<<8)|(*pic->P18map.BDMSR0))/*+1*/ )) printf("Break Point\n");      //Break Point  
//          if(((*pic->P18map.DEBUG)&0x20) == 0x20) printf("sstep!\n");  
          
          if(pic->s2 !=0)pic_decode_18();

          if(pic->pc != 0x00000)
          {
            //printf("Debug stack save\n");
            if(((*pic->P18map.STKPTR) & 0x1F) < 31 )
            {
	      pic->stack[(*pic->P18map.STKPTR)& 0x1F]=pic->pc;
              (*pic->P18map.STKPTR)=((*pic->P18map.STKPTR) &0xC0) | (((*pic->P18map.STKPTR) &0x1F)+1);    
              if(((*pic->P18map.STKPTR)& 0x1F) == 31)(*pic->P18map.STKPTR)|=0x80; //set STKFUL
            }
            if(((*pic->P18map.STKPTR) & 0x1F) >0)
            {    
              (*pic->P18map.TOSL)=((pic->stack[((*pic->P18map.STKPTR) & 0x1F) -1])&0x0000FF);  
              (*pic->P18map.TOSU)=((pic->stack[((*pic->P18map.STKPTR) & 0x1F)-1])&0x1F0000)>>16; 
              (*pic->P18map.TOSH)=((pic->stack[((*pic->P18map.STKPTR) & 0x1F)-1])&0x00FF00)>>8;   
            }
            else
            {
              (*pic->P18map.TOSL)=0;
              (*pic->P18map.TOSH)=0;
              (*pic->P18map.TOSU)=0;
            }
          }
	  
	  (*pic->P18map.DEBUG)|=0x80;
	  (*pic->P18map.BDMSR2)= (pic->pc&0xFF0000)>>16;
	  (*pic->P18map.BDMSR1)= (pic->pc&0x00FF00)>>8;
	  (*pic->P18map.BDMSR0)= (pic->pc&0x0000FF);
	  pic->jpc=0x200028;
	  pic->s2=1;
          pic->debug=1;
          pic->sstep=0;

	  //printf("\n----------->dbg  (%#04X) %#02X  %#02X  pc=0x%04X\n",P18_DEBUG,(*pic->P18map.DEBUG),(*pic->P18map.BDMSR0),pic->pc );
/*           
           pic->pins[pic->pgd-1].dir=((*pic->P18map.DEBUG)&0x02)>>1;                     
           pic->pins[pic->pgc-1].dir=((*pic->P18map.DEBUG)&0x01);  
           
           if(!pic->pins[pic->pgd-1].dir)pic->pins[pic->pgd-1].value=((*pic->P18map.DEBUG)&0x08)>>3;
           if(!pic->pins[pic->pgc-1].dir)pic->pins[pic->pgc-1].value=((*pic->P18map.DEBUG)&0x04)>>2;
*/
           (*pic->P18map.TRISB)= ((*pic->P18map.TRISB)&0x3F)| (((*pic->P18map.DEBUG) &0x03)<<6);
           
           if(!((*pic->P18map.DEBUG) &0x02))(*pic->P18map.PORTB)=((*pic->P18map.PORTB)&0x7F)| (((*pic->P18map.DEBUG) &0x08)<<4); 
           if(!((*pic->P18map.DEBUG) &0x01))(*pic->P18map.PORTB)=((*pic->P18map.PORTB)&0xBF)| (((*pic->P18map.DEBUG) &0x04)<<4); 
                
          }
        }
   }
#endif




//PINOUTS
  
 if(((*pic->P18map.PORTA) != pic->porta)||
    ((*pic->P18map.PORTB) != pic->portb)||
    ((*pic->P18map.PORTC) != pic->portc)||
    ((*pic->P18map.PORTD) != pic->portd)||
    ((*pic->P18map.PORTE) != pic->porte))
 {
   for(i=0;i<pic->PINCOUNT;i++)
   {
     if((pic->pins[i].pord >= 0)&&(pic->pins[i].port))
     switch(pic->pins[i].dir)
     {
	case PD_OUT:
//	    case 7:
//               if((pic->ram[P18_RCSTA] & 0x80)==0x80)break; 
//	    case 17:
//              if((pic->ram[P18_RCSTA] & 0x80)==0x80)break;
//	   if(pic->pins[i].ptype > 2)break;	 
              val=0x01<<(pic->pins[i].pord);
              port=sfr_addr(pic->pins[i].port);
              pic->pins[i].value= ((pic->ram[port] & val) != 0);
	      pic->pins[i].lvalue=pic->pins[i].value;
	  break;
	case PD_IN:
              val=0x01<<(pic->pins[i].pord);
              port=sfr_addr(pic->pins[i].port);
              pic->pins[i].lvalue= ((pic->ram[port+9] & val) != 0); //latch
  	      if(pic->pins[i].ptype > 2)	 
                pic18_wr_pin(i+1, 0);
              else  
                pic18_wr_pin(i+1,pic->pins[i].value);
	break;
	default:
	break;
     }
    } 
   
    pic->porta=(*pic->P18map.PORTA);
    pic->portb=(*pic->P18map.PORTB);
    pic->portc=(*pic->P18map.PORTC);
    pic->portd=(*pic->P18map.PORTD);
    pic->porte=(*pic->P18map.PORTE);
  }



 if(((*pic->P18map.TRISA) != pic->trisa)||
    ((*pic->P18map.TRISB) != pic->trisb)||
    ((*pic->P18map.TRISC) != pic->trisc)||
    ((*pic->P18map.TRISD) != pic->trisd)||
    ((*pic->P18map.TRISE) != pic->trise))
 {
   for(i=0;i<pic->PINCOUNT;i++)
   {
     if(pic->pins[i].pord >= 0)
     {
     val=0x01<<(pic->pins[i].pord);
     tris=sfr_addr(pic->pins[i].port)+0x12;
     if((pic->ram[tris] & val)==0)
     {
       pic->pins[i].dir=PD_OUT;
       pic18_wr_pin(i+1,pic->pins[i].lvalue);
     }
     else
     {
       val=pic->pins[i].dir;
       pic->pins[i].dir=PD_IN;
       if(val != PD_IN)pic18_wr_pin(i+1,pic->pins[i].ovalue);
     }
     }

   }
   pic->trisa=(*pic->P18map.TRISA);
   pic->trisb=(*pic->P18map.TRISB);
   pic->trisc=(*pic->P18map.TRISC);
   pic->trisd=(*pic->P18map.TRISD);
   pic->trise=(*pic->P18map.TRISE);
 }



  
//interrupt
if(pic->s2 == 0)
{
  int iret=interrupt18(); 
  if (iret)
  {
     pic->sleep=0; 
     if(pic->print)printf("interrupt!\n");
     if(((*pic->P18map.STKPTR) & 0x1F) < 31 )
     {
       pic->stack[(*pic->P18map.STKPTR)& 0x1F]=pic->pc;
       (*pic->P18map.STKPTR)=((*pic->P18map.STKPTR) &0xC0) | (((*pic->P18map.STKPTR) &0x1F)+1);    
       if(((*pic->P18map.STKPTR)& 0x1F) == 31)(*pic->P18map.STKPTR)|=0x80; //set STKFUL
     }
     if(((*pic->P18map.STKPTR) & 0x1F) >0)
     {
        (*pic->P18map.TOSL)=((pic->stack[((*pic->P18map.STKPTR) & 0x1F) -1])&0x0000FF);  
        (*pic->P18map.TOSU)=((pic->stack[((*pic->P18map.STKPTR) & 0x1F)-1])&0x1F0000)>>16; 
        (*pic->P18map.TOSH)=((pic->stack[((*pic->P18map.STKPTR) & 0x1F)-1])&0x00FF00)>>8;   
     }
      else
      {
        (*pic->P18map.TOSL)=0;
        (*pic->P18map.TOSH)=0;
        (*pic->P18map.TOSU)=0;
      }
     //fast stack       
     (*pic->P18map.WS)=pic->w; 	 
     (*pic->P18map.STATUSS)=(*pic->P18map.STATUS);
     (*pic->P18map.BSRS)=(*pic->P18map.BSR);

     
     if(iret ==  2)
     {
       (*pic->P18map.INTCON)&=~0x40;//GIEL
       pic->pc=0x0018;
       pic->intlv|=0x02;
     }
     else
     {
       (*pic->P18map.INTCON)&=~0x80;//GIE/GIEH
       pic->pc=0x0008;
       pic->intlv|=0x01;
     };
     pic->s2=1;
  }  
}

}
   
