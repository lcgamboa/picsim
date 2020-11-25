/* ########################################################################

   PICsim - PIC simulator

   ########################################################################

   Copyright (c) : 2008-2020  Luis Claudio Gambôa Lopes

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

#include "../../include/picsim.h"

#define _POSIX_SOURCE 1 /* POSIX compliant source */
#define FALSE 0
#define TRUE 1

int pic_wr_pin18(unsigned char pin, unsigned char value);
int pic_dir_pin18(unsigned char pin, unsigned char dir);

int pic_wr_pin16E(unsigned char pin, unsigned char value);
int pic_dir_pin16E(unsigned char pin, unsigned char dir);

int pic_wr_pin16(unsigned char pin, unsigned char value);
int pic_dir_pin16(unsigned char pin, unsigned char dir);

int
serial_open(int nser)
{

 if (nser >= SERIAL_MAX) return 1;

 pic->serial[nser].bc = 0;
 pic->serial[nser].serialc = 0;
 pic->serial[nser].recb = 0;
 pic->serial[nser].s_open = 0;

 bitbang_uart_init (&pic->serial[nser].bbuart);


 if (pic->serial[nser].SERIALDEVICE[0] == 0)
  {
   pic->serial[nser].serialfd = 0;
   return 0;
  }

#ifdef _WIN_
 pic->serial[nser].serialfd = CreateFile (pic->serial[nser].SERIALDEVICE, GENERIC_READ | GENERIC_WRITE,
                                          0, // exclusive access
                                          NULL, // no security
                                          OPEN_EXISTING,
                                          0, // no overlapped I/O
                                          NULL); // null template
 if (pic->serial[nser].serialfd == INVALID_HANDLE_VALUE)
  {
   pic->serial[nser].serialfd = 0;
   //     printf("Erro on Port Open:%s!\n",pic->serial[nser].SERIALDEVICE);
   return 0;
  }
#else
 pic->serial[nser].serialfd = open (pic->serial[nser].SERIALDEVICE, O_RDWR | O_NOCTTY | O_NONBLOCK);

 if (pic->serial[nser].serialfd <= 0)
  {
   pic->serial[nser].serialfd = 0;
   perror (pic->serial[nser].SERIALDEVICE);
   //    printf("Erro on Port Open:%s!\n",pic->SERIALDEVICE);
   return 0;
  }
 //  printf("Port Open:%s!\n",pic->SERIALDEVICE);
#endif
 return 1;
}

int
serial_close(int nser)
{
 if (nser >= SERIAL_MAX) return 1;

 if (pic->serial[nser].serialfd > 0)
  {
#ifdef _WIN_
   CloseHandle (pic->serial[nser].serialfd);
#else    
   close (pic->serial[nser].serialfd);
#endif
   pic->serial[nser].serialfd = 0;
  }
 bitbang_uart_end (&pic->serial[nser].bbuart);
 return 0;
}

int
serial_cfg(int nser)
{
 unsigned int BAUDRATE;

 if (nser >= SERIAL_MAX) return 1;

 if (*pic->serial[nser].serial_TXSTA & 0x04) //BRGH=1 
  {
   pic->serial[nser].serialexbaud = pic->freq / (16 * ((*pic->serial[nser].serial_SPBRG) + 1));
  }
 else
  {
   pic->serial[nser].serialexbaud = pic->freq / (64 * ((*pic->serial[nser].serial_SPBRG) + 1));
  }




 switch (((int) ((pic->serial[nser].serialexbaud / 300.0) + 0.5)))
  {
  case 0 ... 1:
   pic->serial[nser].serialbaud = 300;
#ifndef _WIN_
   BAUDRATE = B300;
#else
   BAUDRATE = 300;
#endif  
   break;
  case 2 ... 3:
   pic->serial[nser].serialbaud = 600;
#ifndef _WIN_
   BAUDRATE = B600;
#else
   BAUDRATE = 600;
#endif  
   break;
  case 4 ... 7:
   pic->serial[nser].serialbaud = 1200;
#ifndef _WIN_
   BAUDRATE = B1200;
#else
   BAUDRATE = 1200;
#endif  
   break;
  case 8 ... 15:
   pic->serial[nser].serialbaud = 2400;
#ifndef _WIN_
   BAUDRATE = B2400;
#else
   BAUDRATE = 2400;
#endif  
   break;
  case 16 ... 31:
   pic->serial[nser].serialbaud = 4800;
#ifndef _WIN_
   BAUDRATE = B4800;
#else
   BAUDRATE = 4800;
#endif  
   break;
  case 32 ... 63:
   pic->serial[nser].serialbaud = 9600;
#ifndef _WIN_
   BAUDRATE = B9600;
#else
   BAUDRATE = 9600;
#endif  
   break;
  case 64 ... 127:
   pic->serial[nser].serialbaud = 19200;
#ifndef _WIN_
   BAUDRATE = B19200;
#else
   BAUDRATE = 19200;
#endif  
   break;
  case 128 ... 191:
   pic->serial[nser].serialbaud = 38400;
#ifndef _WIN_
   BAUDRATE = B38400;
#else
   BAUDRATE = 38400;
#endif  
   break;
  case 192 ... 383:
   pic->serial[nser].serialbaud = 57600;
#ifndef _WIN_
   BAUDRATE = B57600;
#else
   BAUDRATE = 57600;
#endif  
   break;
  default:
   pic->serial[nser].serialbaud = 115200;
#ifndef _WIN_
   BAUDRATE = B115200;
#else
   BAUDRATE = 115200;
#endif  
   break;
  }

 bitbang_uart_set_clk_freq (&pic->serial[nser].bbuart, pic->freq / 4);
 bitbang_uart_set_speed (&pic->serial[nser].bbuart, pic->serial[nser].serialbaud);

#ifdef _WIN_
 //BOOL bPortReady;
 DCB dcb;
 COMMTIMEOUTS CommTimeouts;

 /*bPortReady =*/ GetCommState (pic->serial[nser].serialfd, &dcb);
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

 /*bPortReady =*/ SetCommState (pic->serial[nser].serialfd, &dcb);

 // Communication timeouts are optional

 /*bPortReady =*/ GetCommTimeouts (pic->serial[nser].serialfd, &CommTimeouts);

 CommTimeouts.ReadIntervalTimeout = MAXDWORD;
 CommTimeouts.ReadTotalTimeoutConstant = 0;
 CommTimeouts.ReadTotalTimeoutMultiplier = 0;
 CommTimeouts.WriteTotalTimeoutConstant = 0;
 CommTimeouts.WriteTotalTimeoutMultiplier = 0;

 /*bPortReady =*/ SetCommTimeouts (pic->serial[nser].serialfd, &CommTimeouts);


 EscapeCommFunction (pic->serial[nser].serialfd, SETRTS);

#else
 struct termios newtio;
 int cmd;

 //        tcgetattr(fd,&oldtio); /* save current port settings */

 bzero (&newtio, sizeof (newtio));
 newtio.c_cflag = BAUDRATE | CS8 | CLOCAL | CREAD;
 newtio.c_iflag = IGNPAR | IGNBRK;
 newtio.c_oflag = 0;

 /* set input mode (non-canonical, no echo,...) */
 newtio.c_lflag = 0;

 newtio.c_cc[VTIME] = 0; /* inter-character timer unused */
 newtio.c_cc[VMIN] = 5; /* blocking read until 5 chars received */

 tcflush (pic->serial[nser].serialfd, TCIFLUSH);
 tcsetattr (pic->serial[nser].serialfd, TCSANOW, &newtio);

 cmd = TIOCM_RTS;
 ioctl (pic->serial[nser].serialfd, TIOCMBIS, &cmd);
#endif

 return 0;
}

unsigned long
serial_send(int nser, unsigned char c)
{
 if (pic->serial[nser].serialfd > 0)
  {
#ifdef _WIN_
   unsigned long nbytes;

   WriteFile (pic->serial[nser].serialfd, &c, 1, &nbytes, NULL);
   return nbytes;
#else
   return write (pic->serial[nser].serialfd, &c, 1);
#endif
  }
 else
  return 0;
}

unsigned long
serial_rec(_pic * pic, int nser, unsigned char * c)
{
 if (pic->serial[nser].serialfd > 0)
  {
#ifdef _WIN_
   unsigned long nbytes;

   ReadFile (pic->serial[nser].serialfd, c, 1, &nbytes, NULL);
#else
   long nbytes;

   nbytes = read (pic->serial[nser].serialfd, c, 1);
   if (nbytes < 0)nbytes = 0;
#endif    

   if (!nbytes)
    {
     if (bitbang_uart_data_available (&pic->serial[nser].bbuart))
      {
       *c = bitbang_uart_recv (&pic->serial[nser].bbuart);
       nbytes = 1;
      }
    }

   return nbytes;
  }
 else
  return 0;
}

unsigned long
serial_rec_tout(int nser, unsigned char * c)
{
 unsigned int tout = 0;

 if (pic->serial[nser].serialfd > 0)
  {
#ifdef _WIN_
   unsigned long nbytes;
   do
    {
     Sleep (1);
     ReadFile (pic->serial[nser].serialfd, c, 1, &nbytes, NULL);
#else
   long nbytes;
   do
    {
     usleep (100);
     nbytes = read (pic->serial[nser].serialfd, c, 1);
     if (nbytes < 0)nbytes = 0;
#endif    
     tout++;
    }
   while ((nbytes == 0)&&(tout < 1000));
   return nbytes;
  }
 else
  return 0;
}

unsigned long
serial_recbuff(int nser, unsigned char * c)
{
 int i;


 if (pic->serial[nser].flowcontrol)
  {

   if (serial_rec (pic, nser, &pic->serial[nser].buff[pic->serial[nser].bc]) == 1)
    {
     pic->serial[nser].bc++;

     if (pic->serial[nser].bc > BUFFMAX)
      {
       printf ("serial buffer overflow \n");
       pic->serial[nser].bc = BUFFMAX - 1;
       //       getchar();	
      };
    }


   if ((pic_get_pin (pic->serial[nser].ctspin) == 0)&&(pic->serial[nser].bc > 0))
    {
     *c = pic->serial[nser].buff[0];

     pic->serial[nser].bc--;
     for (i = 0; i < pic->serial[nser].bc; i++)
      pic->serial[nser].buff[i] = pic->serial[nser].buff[i + 1];
     return 1;
    }
   else
    {
     return 0;
    }
  }
 else
  {
   return serial_rec (pic, nser, c);
  }

}

void
serial(int nser)
{
 unsigned char rctemp;
 unsigned int sr;


 if (pic->lram == pic->serial[nser].serial_TXREG_ADDR)
  {
   pic->serial[nser].txtc++;
   if (pic->serial[nser].txtc > 1)pic->serial[nser].txtc = 1;
   pic->serial[nser].txtemp[(unsigned char) pic->serial[nser].txtc] = *pic->serial[nser].serial_TXREG;
   *pic->serial[nser].serial_TXSTA &= ~0x02; //TRMT=0 full   
   *pic->serial[nser].serial_PIR &= ~pic->serial[nser].TXIF_mask; //TXIF=0 trasmiting
   bitbang_uart_send (&pic->serial[nser].bbuart, *pic->serial[nser].serial_TXREG);
   pic->serial[nser].serialc = 0;
  }

 if (pic->lram == pic->serial[nser].serial_RCSTA_ADDR)
  { //CREN 
   if ((*pic->serial[nser].serial_RCSTA & 0x10) == 0)
    {
     *pic->serial[nser].serial_RCSTA &= ~0x02; //clear OERR
     sr = 1;
    }
  }


 if (pic->rram == pic->serial[nser].serial_RCREG_ADDR)
  {
   switch (pic->serial[nser].recb)
    {
    case 1:
     *pic->serial[nser].serial_RCREG = 0;
     *pic->serial[nser].serial_PIR &= ~pic->serial[nser].RXIF_mask; //clear RCIF
     pic->serial[nser].recb--;
     break;
    case 2:
     *pic->serial[nser].serial_RCREG = pic->serial[nser].RCREG2;
     pic->serial[nser].RCREG2 = 0;
     pic->serial[nser].recb--;
     break;
    default:
     break;
    }

  }



 if ((*pic->serial[nser].serial_RCSTA & 0x80) == 0x80)
  {
   if (pic->serial[nser].s_open == 0)
    {

     if (pic->serial[nser].serialfd > 0)
      {
       serial_cfg (nser);
       pic->serial[nser].s_open = 1;
       if (pic->print)printf ("#Open Port:%s!\n", pic->serial[nser].SERIALDEVICE);
      }
     else
      {
       if (pic->print)printf ("#Erro Open Port:%s!\n", pic->serial[nser].SERIALDEVICE);
       pic->serial[nser].s_open = -1;
      }
     *pic->serial[nser].serial_TXSTA |= 0x02; //TRMT=1 empty 
     *pic->serial[nser].serial_PIR |= pic->serial[nser].TXIF_mask; //TXIF=1  
     pic->serial[nser].txtc = -1;

     //pic->pins[pic->usart_rx[nser] - 1].ptype = PT_USART;
     //pic->pins[pic->usart_tx[nser] - 1].ptype = PT_USART;
     if (pic->serial[nser].flowcontrol)pic_set_pin (pic->serial[nser].rtspin, 0); //enable send
     switch (pic->family)
      {
      case P16:
       pic_dir_pin16 (pic->usart_tx[nser], PD_OUT);
       pic_dir_pin16 (pic->usart_rx[nser], PD_IN);
       break;
      case P16E:
       pic_dir_pin16E (pic->usart_tx[nser], PD_OUT);
       pic_dir_pin16E (pic->usart_rx[nser], PD_IN);
       break;
      case P18:
       pic_dir_pin18 (pic->usart_tx[nser], PD_OUT);
       pic_dir_pin18 (pic->usart_rx[nser], PD_IN);
       break;
      }
    }



   //envia byte para TSTR
   if ((*pic->serial[nser].serial_TXSTA & 0x02)&&(pic->serial[nser].txtc >= 0))
    {
     pic->serial[nser].txtc--;

     if (!pic->serial[nser].txtc)
      {
       pic->serial[nser].txtemp[(unsigned char) pic->serial[nser].txtc] = *pic->serial[nser].serial_TXREG;
       *pic->serial[nser].serial_TXSTA &= ~0x02; //TRMT=0 full   
       *pic->serial[nser].serial_PIR &= ~pic->serial[nser].TXIF_mask; //TXIF=0 trasmiting
       bitbang_uart_send (&pic->serial[nser].bbuart, *pic->serial[nser].serial_TXREG);
       sr = 1;
      }
    }


   pic->serial[nser].serialc++;

   if (*pic->serial[nser].serial_TXSTA & 0x04)
    {
     //BRGH=1  start + 8 bits + stop
     if (pic->serial[nser].serialc >= (((*pic->serial[nser].serial_SPBRG) + 1)*40))
      {
       sr = 1;
      }
    }
   else
    {
     //BRGH=0  start + 8 bits + stop
     if (pic->serial[nser].serialc >= (((*pic->serial[nser].serial_SPBRG) + 1)*160))
      {
       sr = 1;
      }
    }

   if (sr)
    {
     sr = 0;
     pic->serial[nser].serialc = 0;

     if ((pic->serial[nser].s_open == 1)&&((*pic->serial[nser].serial_TRIS_RX & pic->serial[nser].serial_TRIS_RX_MASK) != 0)) //work only if RX tris bit is set
      {
       if (serial_recbuff (nser, &rctemp) == 1)
        {

         if ((*pic->serial[nser].serial_RCSTA & 0x12) == 0x10)//CREN=1  OERR=0 
          {
           switch (pic->serial[nser].recb)
            {
            case 0:
             *pic->serial[nser].serial_RCREG = rctemp;
             pic->serial[nser].RCREG2 = 0;
             pic->serial[nser].recb++;
             break;
            case 1:
             pic->serial[nser].RCREG2 = rctemp;
             pic->serial[nser].recb++;
             break;
            default:
             *pic->serial[nser].serial_RCSTA |= 0x02; //set OERR
             break;
            }
          }

         //       printf("reb=%i temp=%02X RCREG=%02X RECREG2=%02X  RCSTA=%02X\n",pic->recb,rctemp,pic->ram[RCREG],pic->RCREG2,pic->ram[RCSTA]);

         if (((*pic->serial[nser].serial_PIE & pic->serial[nser].RXIF_mask) == pic->serial[nser].RXIF_mask)&&((*pic->serial[nser].serial_PIR & pic->serial[nser].RXIF_mask) != pic->serial[nser].RXIF_mask))
          {
           if (pic->print)printf ("serial rx interrupt (%#04X)\n", rctemp);
          }
         //set RCIF
         *pic->serial[nser].serial_PIR |= pic->serial[nser].RXIF_mask;
        }
      }
    }
   if (!bitbang_uart_transmitting (&pic->serial[nser].bbuart))
    {
     //if(((pic->ram[P18_TXSTA] & 0x02) == 0 ) &&((pic->ram[pic->pins[pic->usart[1]-1].port+0x12] &  (0x01 << pic->pins[pic->usart[1]-1].pord)) == 0))
     if ((*pic->serial[nser].serial_TXSTA & 0x02) == 0)
      {
       if (pic->serial[nser].s_open == 1) serial_send (nser, pic->serial[nser].txtemp[0]);
       *pic->serial[nser].serial_TXSTA |= 0x02; //TRMT=1 empty  

       if (((*pic->serial[nser].serial_PIE & pic->serial[nser].TXIF_mask) == pic->serial[nser].TXIF_mask)&&((*pic->serial[nser].serial_PIR & pic->serial[nser].TXIF_mask) != pic->serial[nser].TXIF_mask))
        {
         if (pic->print)printf ("serial tx interrupt (%#04X)\n", pic->serial[nser].txtemp[0]);
        }
       *pic->serial[nser].serial_PIR |= pic->serial[nser].TXIF_mask; //TXIF=1  
      }
    }
   switch (pic->family)
    {
    case P16:
     pic_wr_pin16 (pic->usart_tx[nser], bitbang_uart_io (&pic->serial[nser].bbuart, pic->pins[pic->usart_rx[nser] - 1].value));
     break;
    case P16E:
     pic_wr_pin16E (pic->usart_tx[nser], bitbang_uart_io (&pic->serial[nser].bbuart, pic->pins[pic->usart_rx[nser] - 1].value));
     break;
    case P18:
     pic_wr_pin18 (pic->usart_tx[nser], bitbang_uart_io (&pic->serial[nser].bbuart, pic->pins[pic->usart_rx[nser] - 1].value));
     break;
    }

   //Hardware flowcontrol
  }
 else
  {
   if (pic->serial[nser].s_open == 1)
    {
     pic->serial[nser].s_open = 0;
     //pic->pins[pic->usart_rx[nser] - 1].ptype = PT_CMOS;
     //pic->pins[pic->usart_tx[nser] - 1].ptype = PT_CMOS;
     if (pic->serial[nser].flowcontrol)pic_set_pin (pic->serial[nser].rtspin, 1); //disable send
    }
  }



}

int
pic_set_serial(_pic * pic_, int nser, const char * name, int flowcontrol, int ctspin, int rtspin)
{
 if (nser >= SERIAL_MAX) return 1;
 pic = pic_;
 strcpy (pic->serial[nser].SERIALDEVICE, name);

 pic->serial[nser].flowcontrol = flowcontrol;
 pic->serial[nser].serialfd = 0;
 if (flowcontrol == 1)
  {
   pic->serial[nser].ctspin = ctspin;
   pic->serial[nser].rtspin = rtspin;
  }
 return 0;
}
