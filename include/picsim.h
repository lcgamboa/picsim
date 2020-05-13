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

#ifdef __cplusplus
extern "C" {
#endif


#ifndef PICSIM
#define PICSIM

#ifdef _WIN_
#include <windows.h>
#endif

#include"p16fxxx_defs.h"
#include"p16fxxxe_defs.h"
#include"p18fxxx_defs.h"

    typedef struct {
        unsigned char ptype; //type
        unsigned char dir; //dir
        unsigned char value; //value
        unsigned char lvalue; //latch value
        char pord; //pin port number
        unsigned char * port; //port address
        float avalue; //analog input value
        unsigned char ovalue; //defaut open pin value
        float oavalue; //analog output value
    } picpin;

#define PD_OUT   0x00
#define PD_IN   0x01


#define PT_CMOS    0x01
#define PT_TTL     0x02 
#define PT_ANALOG  0x04
#define PT_ANAREF  0x05
#define PT_USART   0x06
#define PT_NC      0xFF


    //family
#define P16   1
#define P18   2
#define P16E  3

    //P16 processors
#define P16F84A      0x0560
#define P16F628      0x07C0
#define P16F877      0x09A0
#define P16F628A     0x1060 
#define P16F648A     0x1100 
#define P16F648AICD  0x1120 
#define P16F877A     0x0E20
#define P16F777      0x0DE0

    //P16E processors
#define P16F1619     0x307D
#define P16F1788     0x302B
#define P16F1789     0x302A  
#define P16F18855    0X306C
#define P16F1939     0x23C0

    //P18 processors
#define P18F452     0x0420
#define P18F4520    0x1080
#define P18F4620    0x0C00
#define P18F4550    0x1200
#define P18F45K50   0x5C00
#define P18F27K40   0x6960

    //4K word
#define BUFFMAX 8192 


extern unsigned char NO_IO[5];

    //pin without IO
#define P_VDD &NO_IO[0]
#define P_VSS &NO_IO[1]
#define P_RST &NO_IO[2]
#define P_OSC &NO_IO[3]
#define P_USB &NO_IO[4]

    //CFG bits
#define CFG_MCLR   0x01
#define CFG_WDT    0x02
#define CFG_DEBUG  0x04

   //PACKAGING
#define PDIP 0
#define QFN  1

    typedef struct {
        unsigned char print; //print information ON/OFF  
        unsigned int RAMSIZE;
        unsigned int ROMSIZE;
        unsigned int EEPROMSIZE;
        unsigned int IDSIZE;
        unsigned int CONFIGSIZE;
        unsigned char STACKSIZE;
        unsigned char PINCOUNT;
        unsigned char CCPCOUNT;
        unsigned char ADCCOUNT;
        unsigned char WDT_MS;
        unsigned char family;
        unsigned int processor;
        unsigned short debugv[8];
        unsigned char *ram;
        unsigned short *prog;
        unsigned short *id;
        unsigned char *eeprom;
        unsigned short *config;
        unsigned int pc;
        unsigned int jpc;
        unsigned short lram; //loaded register 
        unsigned short rram; //readed register 
        unsigned short *stack;
        unsigned char w;
        unsigned char wdt;
        unsigned char s2;
        float freq;
        unsigned char sleep; //sleep mode on
        unsigned char pkg; //packaging
        picpin *pins;
        unsigned char mclr;
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
        //timers
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
        //adc
        int adcstep;
        unsigned char adcon1;
        //wdt
        float twdt;
        //eeprom
        int ee_wr;
        //ports
        unsigned char p16latch[5];
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
        unsigned char txtemp[2];
        char txtc;
        unsigned char RCREG2;
        //serial emulation
        char SERIALDEVICE[100];
        unsigned int serialbaud; //serial baud emulated
        float serialexbaud; //exac serial baud
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
        unsigned char * serial_PIR1;
        unsigned char * serial_TXSTA;
        unsigned char * serial_PIE1;
        unsigned char * serial_RCSTA;
        unsigned char * serial_SPBRG;
        unsigned char * serial_RCREG;
        unsigned char * serial_TXREG;
        unsigned short serial_TXREG_ADDR;
        unsigned short serial_RCSTA_ADDR;
        unsigned short serial_RCREG_ADDR;
        unsigned char * serial_TRIS_RX;
        unsigned char serial_TRIS_RX_MASK;

        void (*reset)(void);
        void (*mmap)(void);
        int  (*getconf)(unsigned int);
        void (*periferic)(void);
        int  (*interrupt)(void);
        
        union {
            P16map_t P16map;
            P16Emap_t P16Emap;
            P18map_t P18map;
        };
    } _pic;

    extern _pic * pic; //global pointer 


    void pic_set_serial(_pic * pic_, const char * name, int flowcontrol, int ctspin, int rtspin);
    int pic_init(_pic * pic_, int processor, const char * fname, int lrom, float freq);
    int pic_reset(int flags);
    void pic_erase_flash(void);
    void pic_step(void);
    void pic_end(void);

    unsigned char pic_get_pin(unsigned char pin);
    int pic_set_pin(unsigned char pin, unsigned char value);
    int pic_set_apin(unsigned char pin, float value);
    unsigned char pic_get_pin_type(unsigned char pin);
    unsigned char pic_get_pin_dir(unsigned char pin);
    unsigned char pic_get_pin_DOV(unsigned char pin); //get default open value
    int pic_set_pin_DOV(unsigned char pin, unsigned char value); //set default open value

    void pic_icsp_init(void);
    int pic_icsp(void);

    void pic_icsp_init18(void);
    int pic_icsp18(void);

    int read_ihx(const char * fname, int leeprom);
    int read_ihx_16e(const char * fname, int leeprom);
    int read_ihx_18(const char * fname, int leeprom);

    int write_ihx(const char * fname);
    int write_ihx16e(const char * fname);
    int write_ihx18(const char * fname);

    int getprocbyname(const char *str);
    int getfprocbyname(const char *str);
    int getfprocbynumber(int proc);
    char * getnamebyproc(int proc, char *str);
    const char * getFSRname_16(unsigned int addr);
    const char * getFSRname_16E(unsigned int addr);
    const char * getFSRname_16E2(unsigned int addr);
    const char * getFSRname_18(unsigned int addr);
    const char * getPinName(_pic * pic, int pin, char * pname);

#define sfr_addr(fsr) (fsr - pic->ram)


    //Errors
#define HEX_NFOUND 1
#define HEX_CHKSUM 2
#define HEX_NWRITE 3


#endif

#ifdef __cplusplus
}
#endif 

