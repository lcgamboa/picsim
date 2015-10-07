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

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN_
#include <windows.h>
#endif

typedef struct
{
unsigned char ptype;     //type
unsigned char dir;       //dir
unsigned char value;     //value
unsigned char lvalue;    //latch value
char pord;               //pin port number
unsigned short port;     //port address
float avalue;            //analog value
unsigned char ovalue;    //defaut open pin value
}picpin;

#define PD_OUT	  0x00
#define PD_IN	  0x01


#define PT_CMOS    0x01
#define PT_TTL     0x02	
#define PT_ANALOG  0x04
#define PT_ANAREF  0x05
#define PT_USART   0x06
#define PT_NC  	   0xFF


//family
#define P16 1
#define P18 2

//P16 processors
#define P16F628     0x07C0
#define P16F877     0x09A0
#define P16F628A    0x1060	
#define P16F648A    0x1100	
#define P16F648AICD    0x1120	
#define P16F877A    0x0E20
#define P16F777     0x0DE0

//P18 processors
#define P18F452     0x0420
#define P18F4620    0x0C00
#define P18F4550    0x1200

//4K word
#define BUFFMAX 8192 

typedef struct 
{
  unsigned int  RAMSIZE;
  unsigned int  ROMSIZE;
  unsigned int  EEPROMSIZE;
  unsigned int  IDSIZE;
  unsigned int  CONFIGSIZE;	
  unsigned char STACKSIZE;
  unsigned char  PINCOUNT;
  unsigned char CCPCOUNT;
  unsigned char ADCCOUNT;
  unsigned char family;
  unsigned int  processor;
  unsigned short  debugv[8];
  unsigned char  *ram;
  unsigned short *prog;
  unsigned short *id;
  unsigned char  *eeprom;
  unsigned short *config;
  unsigned int pc;
  unsigned int jpc;
  unsigned short lram;  //loaded register 
  unsigned short rram;  //readed register 
  unsigned short *stack;
  unsigned char  w;
  unsigned char  wdt;
  unsigned char  s2;
  float   	 freq;
  unsigned char  pwd;
  picpin *pins;
  unsigned char *ccp;
  unsigned char *adc;
  unsigned char *usart;
  unsigned char pgc;
  unsigned char pgd;
  unsigned char sck;
  unsigned char sdo;
  unsigned char sdi;
  unsigned char t0cki;
  unsigned char t1cki;
  unsigned char intlv;
//on chip debbuger
unsigned char ocd_pgca;
unsigned char ocd_pgc;
//periferic
unsigned char debug;
unsigned char sstep;
unsigned char dbg;
unsigned char frst;
int cp0;
int cp1;
int cp2;
int cp2_;
int cp3;
int t2pr;
//timer input
unsigned char t0cki_;
unsigned char t1cki_;
//interrupt
unsigned char int0;
unsigned char int1;
unsigned char int2;
//pin value
unsigned char int0v;
unsigned char int1v;
unsigned char int2v;
//portb int mismatch
unsigned char portbm;

int adcstep;

float twdt;

int ee_wr;

unsigned char porta;
unsigned char portb;
unsigned char portc;
unsigned char portd;
unsigned char porte;

unsigned char trisa;
unsigned char trisb;
unsigned char trisc;
unsigned char trisd;
unsigned char trise;

unsigned char adcon1;
//MSSP

unsigned char ssp_ck;
unsigned char ssp_sck;
unsigned char ssp_scka;
unsigned char sspsr;
unsigned char ssp_bit;

//USART 
  int sr; 
  unsigned char recb;
  int serialc;
  unsigned char txtemp;
  unsigned char RCREG2;
//serial emulation
  char SERIALDEVICE[100];
  unsigned int serialbaud; //serial baud emulated
  float serialexbaud;      //exac serial baud
//  FILE * sfout;
#ifdef _WIN_
  HANDLE serialfd;
#else
  int serialfd;
#endif
  int s_open;
  int flowcontrol;
  int ctspin;
  int rtspin;		
  unsigned char buff[BUFFMAX];
  int bc;
} _pic;



void pic_set_serial(_pic * pic, char * name, int flowcontrol,int ctspin,int  rtspin);
int pic_init(_pic * pic,char family, int processor, const char * fname, int lrom,float freq);
int pic_reset(_pic * pic,int flags);
void pic_step(_pic * pic,int print);
void pic_end(_pic * pic);

unsigned char pic_get_pin(_pic * pic, unsigned char pin);
int pic_set_pin(_pic * pic,unsigned char pin,unsigned char value);
int pic_set_apin(_pic * pic,unsigned char pin,float value);
unsigned char pic_get_pin_type(_pic * pic, unsigned char pin);
unsigned char pic_get_pin_dir(_pic * pic, unsigned char pin);

void pic_icsp_init(_pic * pic);
int pic_icsp(_pic * pic, int print);

void pic_icsp_init18(_pic * pic);
int pic_icsp18(_pic * pic, int print);

int write_ihx(_pic * pic,const char * fname);
int write_ihx18(_pic * pic,const char * fname);

int getprocbyname(char *str);
int getfprocbyname(char *str);
char * getnamebyproc(int proc,char *str);

#include"p16fxxx_defs.h"

#include"p18fxxx_defs.h"


#ifdef __cplusplus
}
#endif 

