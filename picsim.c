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

int write_ihx(_pic * pic,const char * fname);

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
    pic_init(&pic1,P16,P16F628A,argv[1],1,4e6);
//    pic_init(&pic1,P16,P16F877A,argv[1],1,4e6);
    write_ihx(&pic1,"out.hex");

    while(c != 'q')
    {

    //  printf("pc=%#06X w=%#04X 0x00=%#04X 0x04=%#04X 0x05=%#04X 0x06=%#04X status=%#04X intcon=%#04X\n",pic1.pc,pic1.w,pic1.ram[0x00],pic1.ram[0x04],pic1.ram[0x05],pic1.ram[0x06],pic1.ram[STATUS],pic1.ram[INTCON]);

      do
      {

      if(fst)
      {
        pic_step(&pic1,0);
      }
      else
      { 
#ifndef _WIN_      
        ANSI_FG_HCOLOR(RED);
#endif 
        pic_step(&pic1,1);

#ifndef _WIN_      
        ANSI_DEFAULT(); 
#endif
        printf("pc=%#06X w=\033[1;32m %#04X \033[0m STATUS=%#04X PORTA=%#04X PORTB=%#04X INTCON=\033[1;32m %#04X \033[0m TMR0=%#04X TMR1H=%#06X TMR1L=%#06X TMR2=%#06X\n",pic1.pc,pic1.w,
         pic1.ram[STATUS],pic1.ram[PORTA],pic1.ram[PORTB],pic1.ram[INTCON],pic1.ram[TMR0],pic1.ram[TMR1H],  
         pic1.ram[TMR1L],pic1.ram[TMR2]); 

     for(i=0;i<16;i++)
	printf("%#04X   ",pic1.ram[i]);
     printf("\n");

     }
    //  for(i=0;i<18;i++)
    //    printf("%02i %i %i %i\n",i,pic_get_pin_dir(&pic1,i+1), pic_get_pin(&pic1,i+1), pic_get_pin_type(&pic1,i+1));
      
      if(!rep) 
      { 
        c=getchar();
      }
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


