/* ########################################################################

   PICsim - PIC simulator

   ########################################################################

   Copyright (c) : 2008-2020  Luis Claudio Gamboa Lopes

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
#include<windows.h>
#define usleep(x) Sleep(x)
#else
#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>
#include "../include/ansi.h"
#endif

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif


_pic pic1;

void
exitcc(int sig)
{
 pic_end ();
 exit (-1);
 //void) signal(SIGINT, SIG_DFL);
}

static unsigned int fst = 0;
static unsigned int addr;
static unsigned int brkp;
static unsigned int nrep = 0;
static int rep = 0;
static int family;
static int i;
static char c = 0;

void
main_loop(void)
{

 //  printf("pc=%#06X w=%#04X 0x00=%#04X 0x04=%#04X 0x05=%#04X 0x06=%#04X status=%#04X intcon=%#04X\n",pic1.pc,pic1.w,pic1.ram[0x00],pic1.ram[0x04],pic1.ram[0x05],pic1.ram[0x06],pic1.ram[STATUS],pic1.ram[INTCON]);

 do
  {

   if (fst)
    {
     pic1.print = 0;
     pic_step ();
    }
   else
    {
#ifndef _WIN_      
     ANSI_FG_HCOLOR (RED);
#endif 
     pic1.print = 1;
     pic_step ();

#ifndef _WIN_      
     ANSI_DEFAULT ();
#endif

     switch (family)
      {
      case P16:
       printf ("PC=0x%04X W=\033[1;32m 0x%#02X \033[0m STATUS=0x%02X PORTA=0x%02X PORTB=0x%02X INTCON=\033[1;32m 0x%02X \033[0m TMR0=0x%02X TMR1H=0x%04X TMR1L=0x%04X TMR2=0x%04X\n", pic1.pc, pic1.w,
               (*pic1.P16map.STATUS), (*pic1.P16map.PORTA), (*pic1.P16map.PORTB), (*pic1.P16map.INTCON), (*pic1.P16map.TMR0), (*pic1.P16map.TMR1H),
               (*pic1.P16map.TMR1L), (*pic1.P16map.TMR2));

       for (i = 0; i < 16; i++)
        printf ("%#04X   ", pic1.ram[i]);
       printf ("\n");
       break;
      case P16E:
       printf ("PC=0x%04X W=\033[1;32m 0x%#02X \033[0m STATUS=0x%02X PORTA=0x%02X PORTB=0x%02X INTCON=\033[1;32m 0x%02X \033[0m TMR0=0x%02X TMR1H=0x%04X TMR1L=0x%04X OPTION=0x%04X\n", pic1.pc, pic1.w,
               (*pic1.P16Emap.STATUS), (*pic1.P16Emap.PORTA), (*pic1.P16Emap.PORTB), (*pic1.P16Emap.INTCON), (*pic1.P16Emap.TMR0), (*pic1.P16Emap.TMR1H),
               (*pic1.P16Emap.TMR1L), (*pic1.P16Emap.OPTION_REG));

       printf ("BSR=0x%02X INDF0=0x%02X INDF1=0x%02X afsr0=0x%04X afsr1=0x%04X\n",
               (*pic1.P16Emap.BSR), (*pic1.P16Emap.INDF0), (*pic1.P16Emap.INDF1),
               (((*pic1.P16Emap.FSR0H)&0xFF) << 8) | (*pic1.P16Emap.FSR0L),
               (((*pic1.P16Emap.FSR1H)&0xFF) << 8) | (*pic1.P16Emap.FSR1L));

       for (i = 0; i < 16; i++)
        printf ("%#04X   ", pic1.ram[i]);
       printf ("\n");
       break;
      case P18:
       printf ("PC    =0x%04X W=\033[1;32m 0x%02X \033[0m  STKPTR=0x%02X TOS=0x%06X PORTB=0x%02X PORTE=0x%02X status=\033[1;32m 0x%02X \033[0m INTCON=0x%02X afsr0=0x%04X afsr1=0x%04X afsr2=0x%04X\n", pic1.pc, pic1.w,
               (*pic1.P18map.STKPTR), (*pic1.P18map.STKPTR) << 16 | (*pic1.P18map.TOSH) << 8 | (*pic1.P18map.TOSL), (*pic1.P18map.PORTB), (*pic1.P18map.PORTE), (*pic1.P18map.STATUS), (*pic1.P18map.INTCON),
               (((*pic1.P18map.FSR0H)&0x0F) << 8) | (*pic1.P18map.FSR0L),
               (((*pic1.P18map.FSR1H)&0x0F) << 8) | (*pic1.P18map.FSR1L),
               (((*pic1.P18map.FSR2H)&0x0F) << 8) | (*pic1.P18map.FSR2L));

       printf ("INTCON=0x%02X   PIE1=0x%02X PIR1=0x%02X   TMR1=0x%04X  CCP1=0x%04X\n",
               (*pic1.P18map.INTCON),
               (*pic1.P18map.PIE1),
               (*pic1.P18map.PIR1),
               ((*pic1.P18map.TMR1H) << 8) | (*pic1.P18map.TMR1L),
               ((*pic1.P18map.CCPR1H) << 8) | (*pic1.P18map.CCPR1L));

       printf ("0x110: ");
       for (i = 0; i < 16; i++)
        printf ("%#04X   ", pic1.ram[i + 0x110]);
       printf ("\n");
       printf ("0x120: ");
       for (i = 0; i < 16; i++)
        printf ("%#04X   ", pic1.ram[i + 0x120]);
       printf ("\n");

       printf ("FSR0=%#04X  POSTINC0=%#04X\n", ((*pic1.P18map.FSR0H) << 8)+(*pic1.P18map.FSR0L), (*pic1.P18map.POSTINC0));
       /*
                     printf("0x550: ");
                     for(i=0;i<16;i++)
                   printf("%#04X   ",pic1.ram[i+0x550]);
                     printf("\n");
        */
       break;
      default:
       printf ("Unknown Family!\n");
      }


    }
   //  for(i=0;i<18;i++)
   //    printf("%02i %i %i %i\n",i,pic_get_pin_dir(&pic1,i+1), pic_get_pin(&pic1,i+1), pic_get_pin_type(&pic1,i+1));

   if (!rep)
    {
     c = getchar ();
    }
   else
    {
     if (pic1.pc == brkp)
      {
       rep = 0;
       fst = 0;
       printf ("\nBreakpoint ------------------------------------------------------------\n");
      }
     if (brkp == 0)
      {
       if (nrep == 0)
        rep = 0;
       else
        nrep--;
      }
    };

   //  usleep(1);

  }
 while (rep);


 switch (c)
  {
  case 'b':
   printf ("Stop address:\n");
   scanf ("%x", &brkp);
   rep = 1;
   break;
  case 'f':
   printf ("Stop address:\n");
   scanf ("%x", &brkp);
   rep = 1;
   fst = 1;
   break;
  case 'n':
   printf ("Number of steps:\n");
   scanf ("%x", &nrep);
   brkp = 0;
   rep = 1;
   break;
  case 'r':
   printf ("Reset:\n");
   pic_reset (0);
   rep = 0;
   break;
  case 'm':
   printf ("Memory address:\n");
   scanf ("%x", &addr);
   getchar ();
   do
    {
     printf ("\n");
     for (i = -8; i < 8; i++)
      if (((addr + i) >= 0)&&(addr + i < pic1.RAMSIZE))
       printf ("%#06X:  %#06X (%i)\n", addr + i, pic1.ram[addr + i], pic1.ram[addr + i]);
     c = getchar ();
     getchar ();
     addr += 16;
    }
   while (c == 'm');
   break;
  case 'h':
   printf ("commands:\n");
   printf ("  b - goto breakpoint\n");
   printf ("  f - goto breakpoint without print (fast)\n");
   printf ("  n - run n steps\n");
   printf ("  m - show memory\n");
   printf ("  r - reset\n");
   printf ("  q - quit\n");
   break;
  }

 if (c != 'q') c = 0;

}

int
main(int argc, char** argv)
{

 int proc;

 int error;

 if (argc == 3)
  {

#ifndef _WIN_
   (void) signal (SIGINT, exitcc);
#endif

   proc = getprocbyname (argv[1]);
   if (proc == 0)
    {
     printf ("Error: Invalid processor (%s)\n", argv[1]);
     return -1;
    }

   family = getfprocbyname (argv[1]);

   pic_set_serial (&pic1, 0, "/dev/tnt2", 0, 0, 0);
   pic_set_serial (&pic1, 1, "", 0, 0, 0);

   if ((error = pic_init (&pic1, proc, argv[2], 1, 20e6)))
    {
     printf ("Pic_init error n=%i\n", error);
     return 0;
    }

   /* 
   if(family == P16)
     write_ihx(&pic1,"out.hex");
   else
    write_ihx18(&pic1,"out.hex");
    */

#ifdef __EMSCRIPTEN__
   emscripten_set_main_loop (main_loop, -1, 1);
#else 
   while (c != 'q')
    {
     main_loop ();
    }
#endif
   pic_end ();
  }
 else
  {
   int pc;
   char plist[PMAX][30];
   
   printf ("use: %s PICXXFXXX file.hex\n\n", argv[0]);
   printf ("supported processors:\n");
	  
   pc = getproclist(plist, PMAX);

   int j=0;
   for(int i=0; i < pc; i++)
   {
     printf("\t%s", &plist[i][0]);
     j++;
     if(j >5)
     {
	 j=0;    
	 printf("\n");
     } 
   }
   printf("\n\n"); 

#ifdef _WIN_
   system ("PAUSE");
#endif        
  }
 return 1;
}


