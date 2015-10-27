/* ########################################################################

   PICsim - PIC simulator

   ########################################################################

   Copyright (c) : 2011  Luis Claudio Gambôa Lopes

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

#include <stdio.h>
#include <string.h>

#include "picsim.h"

int getprocbyname(char *str)
{

  if(!strcmp("PIC16F628" ,str))return P16F628;
  if(!strcmp("PIC16F628A",str))return P16F628A;	
  if(!strcmp("PIC16F648A",str))return P16F648A;	
  if(!strcmp("PIC16F648AICD",str))return P16F648AICD;	
  if(!strcmp("PIC16F877" ,str))return P16F877;
  if(!strcmp("PIC16F877A",str))return P16F877A;
  if(!strcmp("PIC16F777" ,str))return P16F777;

  if(!strcmp("PIC18F452" ,str))return P18F452;
  if(!strcmp("PIC18F4620" ,str))return P18F4620;
  if(!strcmp("PIC18F4550" ,str))return P18F4550;

  return 0;
}

char * getnamebyproc(int proc,char *str)
{
  switch(proc)
  {
    case P16F628:
        strcpy(str,"PIC16F628");
        break;
    case P16F628A:
        strcpy(str,"PIC16F628A");
        break;
    case P16F648A:
        strcpy(str,"PIC16F648A");
        break;
    case P16F648AICD:
        strcpy(str,"PIC16F648AICD");
        break;
    case P16F877:
        strcpy(str,"PIC16F877");
        break;
    case P16F877A:
        strcpy(str,"PIC16F877A");
        break;
    case P16F777:
        strcpy(str,"PIC16F777");
        break;

    case P18F452:
        strcpy(str,"PIC18F452");
        break;
    
    case P18F4620:
        strcpy(str,"PIC18F4620");
        break;
    
    case P18F4550:
        strcpy(str,"PIC18F4550");
        break;
    
    default:
        str=NULL;
  }

   return str;
};

int getfprocbyname(char *str)
{

  if(!strcmp("PIC16F628" ,str))return P16;
  if(!strcmp("PIC16F628A",str))return P16;	
  if(!strcmp("PIC16F648A",str))return P16;	
  if(!strcmp("PIC16F648AICD",str))return P16;	
  if(!strcmp("PIC16F877" ,str))return P16;
  if(!strcmp("PIC16F877A",str))return P16;
  if(!strcmp("PIC16F777" ,str))return P16;

  if(!strcmp("PIC18F452" ,str))return P18;
  if(!strcmp("PIC18F4620" ,str))return P18;
  if(!strcmp("PIC18F4550" ,str))return P18;

  return 0;
}


int getfprocbynumber(int proc)
{

  if(P16F628 == proc)return P16;
  if(P16F628A == proc)return P16;	
  if(P16F648A == proc)return P16;	
  if(P16F648AICD == proc)return P16;	
  if(P16F877 == proc)return P16;
  if(P16F877A == proc)return P16;
  if(P16F777 == proc)return P16;

  if(P18F452 == proc)return P18;
  if(P18F4620 == proc)return P18;
  if(P18F4550 == proc)return P18;

  return 0;
}


