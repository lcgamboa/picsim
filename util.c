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

char FSRname[20];

const char * getFSRname(unsigned int addr)
{

  switch(addr)
  { 
    case 0x00: return "INDF";
    case 0x01: return "TMR0";	
    case 0x02: return "PCL";	
    case 0x03: return "STATUS"; 	
    case 0x04: return "FSR";	
    case 0x05: return "PORTA";	
    case 0x06: return "PORTB";	
    case 0x07: return "PORTC";	
    case 0x08: return "PORTD";	
    case 0x09: return "PORTE";	
    case 0x0A: return "PCLATH";	
    case 0x0B: return "INTCON";  
    case 0x0C: return "PIR1";	
    case 0x0D: return "PIR2";	
    case 0x0E: return "TMR1L";	
    case 0x0F: return "TMR1H";	
    case 0x10: return "T1CON";	
    case 0x11: return "TMR2";	
    case 0x12: return "T2CON";	
    case 0x13: return "SSPBUF";  
    case 0x14: return "SSPCON";  
    case 0x15: return "CCPR1L";	
    case 0x16: return "CCPR1H"; 	
    case 0x17: return "CCP1CON";	
    case 0x18: return "RCSTA";	
    case 0x19: return "TXREG";	
    case 0x1A: return "RCREG";	
    case 0x1B: return "CCPR2L";	
    case 0x1C: return "CCPR2H"; 	
    case 0x1D: return "CCP2CON";	
    case 0x1E: return "ADRESH";  
    case 0x1F: return "CMCON/ADCON0";   


    case 0x81: return "OPTION";  
    case 0x85: return "TRISA";	
    case 0x86: return "TRISB";	
    case 0x87: return "TRISC";	
    case 0x88: return "TRISD";	
    case 0x89: return "TRISE";	
    case 0x8C: return "PIE1";	
    case 0x8D: return "PIE2";	
    case 0x91: return "SSPCON2"; 
    case 0x92: return "PR2";	
    case 0x93: return "SSPADD";  
    case 0x94: return "SSPSTAT"; 
    case 0x95: return "CCPR3L";  
    case 0x96: return "CCPR3H";  
    case 0x97: return "CCP3CON"; 
    case 0x98: return "TXSTA";	
    case 0x99: return "SPBRG";	
    case 0x9B: return "EEADR/ADCON2";  
    case 0x9E: return "ADRESL";  
    case 0x9F: return "ADCON1";  

    case 0x18E: return "ICKBUG";	
    case 0x18F: return "BIGBUG";  

    case 0x9A: return "P628_EEDATA";  
    //case 0x9B: return "P628_EEADR";   
    case 0x9C: return "P628_EECON1";  
    case 0x9D: return "P628_EECON2";  

    case 0x10C: return "P877_EEDATA";  
    case 0x10D: return "P877_EEADR";   
    case 0x10E: return "P877_EEDATAH"; 
    case 0x10F: return "P877_EEADRH";  
    case 0x18C: return "P877_EECON1";  
    case 0x18D: return "P877_EECON2";  
    default:
        sprintf(FSRname,"0x%03X",addr);
        return FSRname;
   }

}

const char * getFSRname_18(unsigned int addr)
{
  switch(addr)
  {
    case 0xFFF: return "TOSU"; 
    case 0xFFE: return "TOSH";	
    case 0xFFD: return "TOSL";	
    case 0xFFC: return "STKPTR";	
    case 0xFFB: return "PCLATU";	
    case 0xFFA: return "PCLATH";	
    case 0xFF9: return "PCL";		
    case 0xFF8: return "TBLPTRU"; 	
    case 0xFF7: return "TBLPTRH"; 	
    case 0xFF6: return "TBLPTRL"; 	
    case 0xFF5: return "TABLAT"; 	
    case 0xFF4: return "PRODH";	
    case 0xFF3: return "PRODL";	
    case 0xFF2: return "INTCON";  	
    case 0xFF1: return "INTCON2";  	
    case 0xFF0: return "INTCON3"; 	
    case 0xFEF: return "INDF0";	
    case 0xFEE: return "POSTINC0";	
    case 0xFED: return "POSTDEC0";	
    case 0xFEC: return "PREINC0";	
    case 0xFEB: return "PLUSW0";	
    case 0xFEA: return "FSR0H";	
    case 0xFE9: return "FSR0L";	
    case 0xFE8: return "WREG";	
    case 0xFE7: return "INDF1";	
    case 0xFE6: return "POSTINC1";	
    case 0xFE5: return "POSTDEC1";	
    case 0xFE4: return "PREINC1";	
    case 0xFE3: return "PLUSW1";	
    case 0xFE2: return "FSR1H";	
    case 0xFE1: return "FSR1L";	
    case 0xFE0: return "BSR";		
    case 0xFDF: return "INDF2";	
    case 0xFDE: return "POSTINC2";	
    case 0xFDD: return "POSTDEC2";	
    case 0xFDC: return "PREINC2";	
    case 0xFDB: return "PLUSW2";	
    case 0xFDA: return "FSR2H";	
    case 0xFD9: return "FSR2L";	
    case 0xFD8: return "STATUS"; 	
    case 0xFD7: return "TMR0H";	
    case 0xFD6: return "TMR0L";	
    case 0xFD5: return "T0CON";	
    case 0xFD4: return "DEBUG";	
    case 0xFD3: return "OSCCON";	 
    case 0xFD2: return "LVDCON";	
    case 0xFD1: return "WDTCON";	
    case 0xFD0: return "RCON";	
    case 0xFCF: return "TMR1H";	
    case 0xFCE: return "TMR1L";	
    case 0xFCD: return "T1CON";	
    case 0xFCC: return "TMR2";	
    case 0xFCB: return "PR2";		
    case 0xFCA: return "T2CON";	
    case 0xFC9: return "SSPBUF";	
    case 0xFC8: return "SSPADD";	
    case 0xFC7: return "SSPSTAT";	
    case 0xFC6: return "SSPCON1";	
    case 0xFC5: return "SSPCON2";	
    case 0xFC4: return "ADRESH";	
    case 0xFC3: return "ADRESL"; 	
    case 0xFC2: return "ADCON0";	
    case 0xFC1: return "ADCON1";	
    case 0xFC0: return "ADCON2";	
    case 0xFBF: return "CCPR1H";	
    case 0xFBE: return "CCPR1L";	
    case 0xFBD: return "CCP1CON";	
    case 0xFBC: return "CCPR2H";	
    case 0xFBB: return "CCPR2L";	
    case 0xFBA: return "CCP2CON";	

    case 0xFB9: return "BDMSR2";	 
 //   case 0xFB8: return "BDMSR1";	 
 //   case 0xFB7: return "BDMSR0";	 

    case 0xFB8: return "BAUDCON";	
    case 0xFB7: return "PWM1CON";	
    case 0xFB6: return "ECCP1AS";	
    case 0xFB5: return "CVRCON";	
    case 0xFB4: return "CMCON";	
    case 0xFB3: return "TMR3H";	
    case 0xFB2: return "TMR3L";	
    case 0xFB1: return "T3CON";	
    case 0xFB0: return "SPBRGH";	
    case 0xFAF: return "SPBRG"; 	
    case 0xFAE: return "RCREG"; 	
    case 0xFAD: return "TXREG"; 	
    case 0xFAC: return "TXSTA"; 	
    case 0xFAB: return "RCSTA"; 	
    case 0XFAA: return "EEADRH";	
    case 0XFA9: return "EEADR";	
    case 0XFA8: return "EEDATA";	
    case 0XFA7: return "EECON2";	
    case 0XFA6: return "EECON1";	

    case 0xFA2: return "IPR2";	
    case 0xFA1: return "PIR2";	
    case 0xFA0: return "PIE2";	
    case 0xF9F: return "IPR1";	
    case 0xF9E: return "PIR1";	
    case 0xF9D: return "PIE1";	

    case 0xF9B: return "OSCTUNE";	

    case 0xF96: return "TRISE";	
    case 0xF95: return "TRISD";	
    case 0xF94: return "TRISC";	
    case 0xF93: return "TRISB";	
    case 0xF92: return "TRISA";	

    case 0xF8D: return "LATE";	
    case 0xF8C: return "LATD";	
    case 0xF8B: return "LATC";	
    case 0xF8A: return "LATB";	
    case 0xF89: return "LATA";	

    case 0xF84: return "PORTE";	
    case 0xF83: return "PORTD";	
    case 0xF82: return "PORTC";	
    case 0xF81: return "PORTB";	
    case 0xF80: return "PORTA";	

//PIC18F4550
    case 0xF7F: return "UEP15";	
    case 0xF7E: return "UEP14";	
    case 0xF7D: return "UEP13";	
    case 0xF7C: return "UEP12";	
    case 0xF7B: return "UEP11";	
    case 0xF7A: return "UEP10";	
    case 0xF79: return "UEP9";	
    case 0xF78: return "UEP8";	
    case 0xF77: return "UEP7";	
    case 0xF76: return "UEP6";	
    case 0xF75: return "UEP5";	
    case 0xF74: return "UEP4";	
    case 0xF73: return "UEP3";	
    case 0xF72: return "UEP2";	
    case 0xF71: return "UEP1";	
    case 0xF70: return "UEP0";	
    case 0xF6F: return "UCFG";	
    case 0xF6E: return "UADDR";	
    case 0xF6D: return "UCON";	
    case 0xF6C: return "USTAT";	
    case 0xF6B: return "UEIE";	
    case 0xF6A: return "UIER"; 	
    case 0xF69: return "UIE"; 	
    case 0xF68: return "UIR"; 	
    case 0xF67: return "UFRMH";	
    case 0xF66: return "UFRML";	
    case 0xF65: return "SPPCON";	
    case 0xF64: return "SPPEPS";	
    case 0xF63: return "SPPCFG";	
    case 0xF62: return "SPPDATA";	



//shadow
    case 0xF00: return "WS";		
    case 0xF01: return "STATUSS";	
    case 0xF02: return "BSRS";	
    default:
        sprintf(FSRname,"0x%03X",addr);
        return FSRname;
  }
}