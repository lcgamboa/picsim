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
#include<windows.h>
#define usleep(x) Sleep(x)
#else
#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>
#include "ansi.h"
#endif
  

_pic pic1; 

void exitcc(int sig) 
{
 pic_end(&pic1);
 exit(-1);
//void) signal(SIGINT, SIG_DFL);
}


int write_ihx18(_pic * pic,const char * fname);

int 
main(int argc,char** argv)
{
 
  int i;
 
  char c=0;

  unsigned int addr;

  unsigned int brk; 
  unsigned int nrep=0;
  int rep=0;

  unsigned int fst=0;

  if(argc == 2)
  {

#ifndef _WIN_
  (void) signal(SIGINT, exitcc);
#endif
 
    pic_set_serial(&pic1,"/dev/tnt2",0,0,0);
    pic_init(&pic1,P18,P18F4620,argv[1],1,8e6);

    //write_ihx18(&pic1,"out.hex");

    while(c != 'q')
    {






      do
      {

      if(fst)
      {
        pic_step(&pic1,0);
      }
      else
      {       
        ANSI_FG_HCOLOR(RED); 
        pic_step(&pic1,1);

        ANSI_DEFAULT(); 
        printf("pc=%#06X w=\033[1;32m %#04X \033[0m STKPTR=%#04X TOS=%#08X PORTB=%#04X PORTE=%#04X status=\033[1;32m %#04X \033[0m intcon=%#04X afsr0=%#06X afsr1=%#06X afsr2=%#06X\n",pic1.pc,pic1.w,
  pic1.ram[P18_STKPTR],pic1.ram[P18_TOSU]<<16|pic1.ram[P18_TOSH]<<8|pic1.ram[P18_TOSL],pic1.ram[P18_PORTB],pic1.ram[P18_PORTE],pic1.ram[P18_STATUS],pic1.ram[P18_INTCON],  
  ((pic1.ram[P18_FSR0H]&0x0F)<<8) |pic1.ram[P18_FSR0L],
  ((pic1.ram[P18_FSR1H]&0x0F)<<8) |pic1.ram[P18_FSR1L],
  ((pic1.ram[P18_FSR2H]&0x0F)<<8) |pic1.ram[P18_FSR2L]);
       

     printf("0x110: ");
     for(i=0;i<16;i++)
	printf("%#04X   ",pic1.ram[i+0x110]);
     printf("\n");

     printf("0x120: ");
     for(i=0;i<16;i++)
	printf("%#04X   ",pic1.ram[i+0x120]);
     printf("\n");

     printf("FSR0=%#04X  POSTINC0=%#04X\n",(pic1.ram[P18_FSR0H]<<8)+pic1.ram[P18_FSR0L],pic1.ram[P18_POSTINC0]);
/*
     printf("0x550: ");
     for(i=0;i<16;i++)
	printf("%#04X   ",pic1.ram[i+0x550]);
     printf("\n");
*/

     }
    //  for(i=0;i<18;i++)
    //    printf("%02i %i %i %i\n",i,pic_get_pin_dir(&pic1,i+1), pic_get_pin(&pic1,i+1), pic_get_pin_type(&pic1,i+1));
      
      if(!rep)  
        c=getchar();
      else
      {
        if(pic1.pc == brk)
        {
         rep=0;
         fst=0;
         printf("\nBreakpoint ------------------------------------------------------------\n"); 
        }
        if(brk == 0)
        { 
          if(nrep == 0)
            rep=0;
          else
            nrep--;
        } 
      };
 
     //  usleep(1);


       if(c == 'b')
       {
         c=0;
         printf("Digite endereço de parada:\n"); 
         scanf("%x",&brk);
         rep=1;  
       } 
       
       if(c == 'f')
       {
         c=0;
         printf("Digite endereço de parada:\n"); 
         scanf("%x",&brk);
         rep=1;   
         fst=1;
       } 
       
       if(c == 'n')
       {
         c=0;
         printf("Digite numero de repetições:\n"); 
         scanf("%x",&nrep);
         brk=0;
         rep=1;  
       } 


     }
     while(rep);

     while(c == 'm')
     {
/*     //INT0
       if(pic_get_pin(&pic1,33)) 
         pic_set_pin(&pic1,33,0 );
       else
         pic_set_pin(&pic1,33,1);
*/
       printf("Digite endereço:\n"); 
       scanf("%x",&addr);  

       printf("\n");
       for(i=-8;i<8;i++)
         if(((addr+i) >= 0)&&( addr+i < pic1.RAMSIZE))  
	   printf("%#06X:  %#06X (%i)\n",addr+i,pic1.ram[addr+i],pic1.ram[addr+i]);
       
       c=getchar();
       c=getchar();
     }   


    };

     pic_end(&pic1);
   }
   else
   {
     printf("use: %s file.hex\n",argv[0]);
#ifdef _WIN_
    system("PAUSE");
#endif        
   }
    return 1;
}


