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


#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#ifdef _WIN_
#include <conio.h>
#include <time.h>
#include <windows.h>
#else
#include <termios.h>
#include <sys/ioctl.h>
#endif

#include "picsim.h"
#include "periferic.h"
#include "periferic18.h"
        
#define _POSIX_SOURCE 1 /* POSIX compliant source */
#define FALSE 0
#define TRUE 1
        


#ifdef _WIN_
#define BAUDRATE 19200
#else
#define BAUDRATE B19200
#endif



int 
serial_open(_pic * pic)
{
      if(pic->SERIALDEVICE[0] == 0)
      { 	
#ifdef _WIN_
        strcpy(pic->SERIALDEVICE,"COM2");
#else
        strcpy(pic->SERIALDEVICE,"/dev/tnt2");
#endif
      }

  pic->bc=0;
  pic->sr=0;
  pic->serialc=0;
  pic->recb=0;
  pic->s_open=0;

#ifdef _WIN_
  pic->serialfd = CreateFile(pic->SERIALDEVICE, GENERIC_READ | GENERIC_WRITE,
0, // exclusive access
NULL, // no security
OPEN_EXISTING,
0, // no overlapped I/O
NULL); // null template
  if( pic->serialfd == INVALID_HANDLE_VALUE)
  {
     pic->serialfd=0;
//     printf("Erro on Port Open:%s!\n",pic->SERIALDEVICE);
     return 0; 
  }
#else
  pic->serialfd = open(pic->SERIALDEVICE, O_RDWR | O_NOCTTY | O_NONBLOCK);
 
  if (pic->serialfd < 0) 
  {
    pic->serialfd=0;
    perror(pic->SERIALDEVICE); 
//    printf("Erro on Port Open:%s!\n",pic->SERIALDEVICE);
    return 0; 
  }
//  printf("Port Open:%s!\n",pic->SERIALDEVICE);
#endif
  return 1;
}

int 
serial_close(_pic * pic)
{
  if (pic->serialfd != 0) 
  {
#ifdef _WIN_
  CloseHandle(pic->serialfd);
#else    
    close(pic->serialfd);
#endif
    pic->serialfd=0;
  }
  return 0;
}



int
serial_cfg(_pic * pic)
{
#ifdef _WIN_
  BOOL bPortReady;
  DCB dcb;
  COMMTIMEOUTS CommTimeouts;

bPortReady = GetCommState(pic->serialfd , &dcb);
dcb.BaudRate = BAUDRATE;
dcb.ByteSize = 8;
dcb.Parity = NOPARITY;
dcb.StopBits = ONESTOPBIT;
dcb.fAbortOnError = TRUE;

// set XON/XOFF
dcb.fOutX = FALSE; // XON/XOFF off for transmit
dcb.fInX = FALSE; // XON/XOFF off for receive
// set RTSCTS
dcb.fOutxCtsFlow = FALSE; // turn off CTS flow control
//dcb.fRtsControl = RTS_CONTROL_HANDSHAKE; //
dcb.fRtsControl = RTS_CONTROL_DISABLE; //
// set DSRDTR
dcb.fOutxDsrFlow = FALSE; // turn off DSR flow control
//dcb.fDtrControl = DTR_CONTROL_ENABLE; //
dcb.fDtrControl = DTR_CONTROL_DISABLE; //
// dcb.fDtrControl = DTR_CONTROL_HANDSHAKE; //

bPortReady = SetCommState(pic->serialfd , &dcb);

// Communication timeouts are optional

bPortReady = GetCommTimeouts (pic->serialfd , &CommTimeouts);

CommTimeouts.ReadIntervalTimeout = MAXDWORD;
CommTimeouts.ReadTotalTimeoutConstant = 0;
CommTimeouts.ReadTotalTimeoutMultiplier = 0;
CommTimeouts.WriteTotalTimeoutConstant = 0;
CommTimeouts.WriteTotalTimeoutMultiplier = 0;

bPortReady = SetCommTimeouts (pic->serialfd , &CommTimeouts);
	

EscapeCommFunction(pic->serialfd ,SETRTS );

#else
   struct termios newtio;
   int cmd;   
        
//        tcgetattr(fd,&oldtio); /* save current port settings */
        
        bzero(&newtio, sizeof(newtio));
        newtio.c_cflag = BAUDRATE |CS8 | CLOCAL | CREAD;
        newtio.c_iflag = IGNPAR|IGNBRK;
        newtio.c_oflag = 0;
        
        /* set input mode (non-canonical, no echo,...) */
        newtio.c_lflag = 0;
         
        newtio.c_cc[VTIME]    = 0;   /* inter-character timer unused */
        newtio.c_cc[VMIN]     = 5;   /* blocking read until 5 chars received */
        
        tcflush(pic->serialfd, TCIFLUSH);
        tcsetattr(pic->serialfd,TCSANOW,&newtio);
        
	cmd=TIOCM_RTS;
	ioctl(pic->serialfd, TIOCMBIS ,&cmd);
#endif   
	return 0; 
}


      
unsigned long serial_send(_pic * pic, unsigned char c)
{
  if(pic->serialfd)
  {
#ifdef _WIN_
   unsigned long nbytes;
    
   WriteFile(pic->serialfd, &c, 1, &nbytes,NULL);
   return nbytes;
#else
  return write (pic->serialfd,&c,1);   
#endif
  }
  else
    return 0;
}

unsigned long serial_rec(_pic * pic, unsigned char * c)
{
  if(pic->serialfd)
  {
#ifdef _WIN_
    unsigned long nbytes;
      
    ReadFile(pic->serialfd, c, 1,&nbytes, NULL);
#else
    long nbytes;

     nbytes = read (pic->serialfd,c,1);   
     if(nbytes<0)nbytes=0;
#endif    
    return nbytes;
   }
   else
     return 0;
}

unsigned long serial_rec_tout(_pic * pic, unsigned char * c)
{
 unsigned int tout=0;

  if(pic->serialfd)
  {
#ifdef _WIN_
    unsigned long nbytes;
    do
    { 
      Sleep(1);	
      ReadFile(pic->serialfd, c, 1,&nbytes, NULL);
#else
    long nbytes;
    do
    { 
      usleep(100);
      nbytes = read (pic->serialfd,c,1);   
      if(nbytes<0)nbytes=0;
#endif    
      tout++;
    }while((nbytes == 0 )&&(tout < 1000));
    return nbytes;
   }
   else
     return 0;
}


unsigned long serial_recbuff(_pic * pic, unsigned char * c)
{
int i;


  if(pic->flowcontrol)
  {
  
   if(serial_rec(pic,&pic->buff[pic->bc]) == 1)
    {
     pic->bc++;

     if(pic->bc > BUFFMAX)
     {
       printf("serial buffer overflow \n") ;
       pic->bc = BUFFMAX-1;  
//       getchar();	
     };
    }


    if((pic_get_pin(pic,pic->ctspin) == 0)&&(pic->bc > 0))
    {
      *c=pic->buff[0];

      pic->bc--;
      for(i=0;i<pic->bc;i++)
        pic->buff[i]=pic->buff[i+1]; 
      return 1;
    }
    else
    {
      return 0;
    }
  }
  else
  {
     return serial_rec(pic,c);
  }
  
}





void serial(_pic * pic,int print)
{
  unsigned char rctemp;


  if((pic->ram[RCSTA] & 0x80)==0x80)
  {
    if(pic->s_open == 0) 
    {

      if(pic->serialfd > 0)
      {
        serial_cfg(pic);
        pic->s_open=1;
       if(print)printf("#Open Port:%s!\n",pic->SERIALDEVICE);
      }
      else
      {
        if(print)printf("#Erro Open Port:%s!\n",pic->SERIALDEVICE);
        pic->s_open=-1;
      }
      pic->ram[TXSTA]|=0x02; //TRMT=1 empty 
      pic->ram[PIR1]|=0x10; //TXIF=1  
    }
   pic->pins[pic->usart[0]-1].ptype=PT_USART;
   pic->pins[pic->usart[1]-1].ptype=PT_USART;
   
   if(pic->flowcontrol)pic_set_pin(pic, pic->rtspin,0); //enable send
  }
  else
  {
    if(pic->s_open == 1)
    {
      pic->s_open=0;
    }
   pic->pins[pic->usart[0]-1].ptype=PT_CMOS;
   pic->pins[pic->usart[1]-1].ptype=PT_CMOS;
   if(pic->flowcontrol)pic_set_pin(pic, pic->rtspin,1); //disable send
  }
  

   if(pic->lram == TXREG)    
    { 
      pic->txtemp=pic->ram[TXREG];
      pic->ram[TXSTA]&=~0x02; //TRMT=0 full   
      pic->ram[PIR1]&=~0x10; //TXIF=0 trasmiting 
    }
   

   if(pic->lram == RCSTA)
   {               //CREN 
      if((pic->ram[RCSTA] & 0x10) == 0)
      {  
       pic->ram[RCSTA]&=~0x02; //clear OERR
       pic->serialc=0;
      }
   }    


   if(pic->rram == RCREG)    
    { 
      switch(pic->recb)
      {
        case 1:
          pic->ram[RCREG]=0;
          pic->ram[PIR1]&=~0x20; //clear RCIF
          pic->recb--;    
          break;
        case 2:
          pic->ram[RCREG]=pic->RCREG2;
          pic->RCREG2=0; 
	  pic->recb--;    
          break;
        default:
        break; 
      }

    }


    pic->serialc++;

    if((pic->ram[TXSTA] & 0x04) == 0x04)
    {
       //BRGH=1  start + 8 bits + stop
       if(pic->serialc >= ((pic->ram[SPBRG]+1)*40))pic->sr =1;
    }
    else
    {
       //BRGH=0  start + 8 bits + stop
       if(pic->serialc >= ((pic->ram[SPBRG]+1)*160))pic->sr =1;
    }

  
    if(pic->sr ==1 )
    {
    
     pic->serialc=0;
  
     if(pic->s_open != 0)
     {
      if(serial_recbuff(pic,&rctemp) == 1)
      {

        if((pic->ram[RCSTA] & 0x12) == 0x10)//CREN=1  OERR=0 
        { 
         switch(pic->recb)
         {
         case 0: 
           pic->ram[RCREG]=rctemp;
	   pic->RCREG2=0;
           pic->recb++;
           break;
         case 1: 
           pic->RCREG2=rctemp;
           pic->recb++;
           break; 
         default: 
           pic->ram[RCSTA]|=0x02; //set OERR
           break; 
          }
        }
        
   //       printf("reb=%i temp=%02X RCREG=%02X RECREG2=%02X  RCSTA=%02X\n",pic->recb,rctemp,pic->ram[RCREG],pic->RCREG2,pic->ram[RCSTA]);
        
         if(((pic->ram[PIE1] & 0x20) == 0x20)&&((pic->ram[PIR1] & 0x20) != 0x20))
         {
           if(print)printf("serial rx interrupt (%#04X)\n",rctemp);
         }
         //set RCIF
         pic->ram[PIR1]|=0x20;  
      }
     } 
    
      if((pic->ram[TXSTA] & 0x02) == 0 )
      {   
        if(pic->s_open == 1 ) serial_send(pic,pic->txtemp);
        pic->ram[TXSTA]|=0x02; //TRMT=1 empty  
    
        if(((pic->ram[PIE1] & 0x10) == 0x10)&&((pic->ram[PIR1] & 0x10) != 0x10))
        {
          if(print)printf("serial tx interrupt (%#04X)\n",pic->txtemp);
        }
        pic->ram[PIR1]|=0x10; //TXIF=1  
      }   
      pic->sr=0;
    }

//Hardware flowcontrol



}

void serial18(_pic * pic,int print)
{
  unsigned char rctemp;


  if((pic->ram[P18_RCSTA] & 0x80)==0x80)
  {
    if(pic->s_open == 0) 
    {

      if(pic->serialfd > 0)
      {
        serial_cfg(pic);
        pic->s_open=1;
       if(print)printf("#Open Port:%s!\n",pic->SERIALDEVICE);
      }
      else
      {
        if(print)printf("#Erro Open Port:%s!\n",pic->SERIALDEVICE);
        pic->s_open=-1;
      }
      pic->ram[P18_TXSTA]|=0x02; //TRMT=1 empty 
      pic->ram[P18_PIR1]|=0x10; //TXIF=1  
    }
   pic->pins[pic->usart[0]-1].ptype=PT_USART;
   pic->pins[pic->usart[1]-1].ptype=PT_USART;
   
   if(pic->flowcontrol)pic_set_pin(pic, pic->rtspin,0); //enable send
  }
  else
  {
    if(pic->s_open == 1)
    {
      pic->s_open=0;
    }
   pic->pins[pic->usart[0]-1].ptype=PT_CMOS;
   pic->pins[pic->usart[1]-1].ptype=PT_CMOS;
   if(pic->flowcontrol)pic_set_pin(pic, pic->rtspin,1); //disable send
  }
  

   if(pic->lram == P18_TXREG)    
    { 
      pic->txtemp=pic->ram[P18_TXREG];
      pic->ram[P18_TXSTA]&=~0x02; //TRMT=0 full   
      pic->ram[P18_PIR1]&=~0x10; //TXIF=0 trasmiting 
    }
   

   if(pic->lram == P18_RCSTA)
   {               //CREN 
      if((pic->ram[P18_RCSTA] & 0x10) == 0)
      {  
       pic->ram[P18_RCSTA]&=~0x02; //clear OERR
       pic->serialc=0;
      }
   }    


   if(pic->rram == P18_RCREG)    
    { 
      switch(pic->recb)
      {
        case 1:
          pic->ram[P18_RCREG]=0;
          pic->ram[P18_PIR1]&=~0x20; //clear RCIF
          pic->recb--;    
          break;
        case 2:
          pic->ram[P18_RCREG]=pic->RCREG2;
          pic->RCREG2=0; 
	  pic->recb--;    
          break;
        default:
        break; 
      }

    }


    pic->serialc++;

    if((pic->ram[P18_TXSTA] & 0x04) == 0x04)
    {
       //BRGH=1  start + 8 bits + stop
       if(pic->serialc >= ((pic->ram[P18_SPBRG]+1)*40))pic->sr =1;
    }
    else
    {
       //BRGH=0  start + 8 bits + stop
       if(pic->serialc >= ((pic->ram[P18_SPBRG]+1)*160))pic->sr =1;
    }

  
    if(pic->sr ==1 )
    {
    
     pic->serialc=0;
  
     if(pic->s_open != 0)
     {
      if(serial_recbuff(pic,&rctemp) == 1)
      {

        if((pic->ram[P18_RCSTA] & 0x12) == 0x10)//CREN=1  OERR=0 
        { 
         switch(pic->recb)
         {
         case 0: 
           pic->ram[P18_RCREG]=rctemp;
	   pic->RCREG2=0;
           pic->recb++;
           break;
         case 1: 
           pic->RCREG2=rctemp;
           pic->recb++;
           break; 
         default: 
           pic->ram[P18_RCSTA]|=0x02; //set OERR
           break; 
          }
        }
        
   //       printf("reb=%i temp=%02X RCREG=%02X RECREG2=%02X  RCSTA=%02X\n",pic->recb,rctemp,pic->ram[RCREG],pic->RCREG2,pic->ram[RCSTA]);
        
         if(((pic->ram[P18_PIE1] & 0x20) == 0x20)&&((pic->ram[P18_PIR1] & 0x20) != 0x20))
         {
           if(print)printf("serial rx interrupt (%#04X)\n",rctemp);
         }
         //set RCIF
         pic->ram[P18_PIR1]|=0x20;  
      }
     } 
    
      if((pic->ram[P18_TXSTA] & 0x02) == 0 )
      {   
        if(pic->s_open == 1 ) serial_send(pic,pic->txtemp);
        pic->ram[P18_TXSTA]|=0x02; //TRMT=1 empty  
    
        if(((pic->ram[P18_PIE1] & 0x10) == 0x10)&&((pic->ram[P18_PIR1] & 0x10) != 0x10))
        {
          if(print)printf("serial tx interrupt (%#04X)\n",pic->txtemp);
        }
        pic->ram[P18_PIR1]|=0x10; //TXIF=1  
      }   
      pic->sr=0;
    }

//Hardware flowcontrol



}


void 
pic_set_serial(_pic * pic, char * name, int flowcontrol,int ctspin,int  rtspin)
{
  strcpy(pic->SERIALDEVICE,name);
  
  pic->flowcontrol=flowcontrol;
  pic->serialfd=0;
  if(flowcontrol == 1)
  {
    pic->ctspin=ctspin;
    pic->rtspin=rtspin;
  }
};
