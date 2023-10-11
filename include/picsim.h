/* ########################################################################

   PICsim - PIC simulator

   ########################################################################

   Copyright (c) : 2008-2022  Luis Claudio Gamboa Lopes

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

/**
 * @file picsim.h
 * @author Luis Claudio Gamboa Lopes
 *
 * @brief PICsim - PIC Simulator - API
 *
 * PICsim emulates a microcontroller
 * PIC16F84A/16F628/16F777/16F877A/18F452/18F4520/18F4550/18F4620 and periferics
 * such as USART and timers, the simulator architecture permit easy
 * implementation of external elements in c language.
 * @see https://github.com/lcgamboa/picsim
 */

/** @mainpage notitle
 *
 * @section intro_sec Introduction
 *
 * This is the documentation of using the picsim simulation library functions.
 *
 * @section example Library functions usage simple example
 *
 * Demonstration of a simple example of using picsim library functions
 *
 * @subsection simple picsim_simple.c
 * @include picsim_simple.c
 *
 * @subsection makefile Makefile
 * @include Makefile
 *
 */

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef PICSIM
#define PICSIM

#ifdef _WIN_
#include <windows.h>
#endif

#include "bitbang_uart.h"
#include "p16fxxx_defs.h"
#include "p16fxxxe_defs.h"
#include "p18fxxx_defs.h"

#define SERIAL_MAX 2
#define BUFFMAX 8192 // 4K word

  /**
   * @brief PICsim pin structure
   *
   * Internal structure used to describe one pin.
   */
  typedef struct
  {
    unsigned char ptype;   ///< @ref pintype
    unsigned char dir;     ///< @ref pindir
    unsigned char value;   ///< value
    unsigned char lvalue;  ///< latch value
    char pord;             ///< pin port number
    unsigned char *port;   ///< port address
    float avalue;          ///< analog input value
    unsigned char ovalue;  ///< defaut open pin value
    float oavalue;         ///< analog output value
    unsigned char lsvalue; ///< last set value (used by open collector simulation)
  } picpin;

  /**
   * @brief PICsim pin structure
   *
   * Internal structure used to describe one pin.
   */
  typedef struct
  {
    unsigned char pin;    ///< pin
    unsigned char ovalue; ///< old value
    unsigned char cap_ps; ///< capture pre scaler
  } ccp_t;

  /**
   * @brief PICsim serial structure
   *
   * Internal structure used to describe one serial connection.
   */
  typedef struct
  {
    // USART
    unsigned char recb;
    int serialc;
    unsigned char txtemp[2];
    char txtc;
    unsigned char RCREG2;
    // serial emulation
    char SERIALDEVICE[100];
    unsigned int serialbaud; // serial baud emulated
    float serialexbaud;      // exac serial baud
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
    unsigned char *serial_TXSTA;
    unsigned char *serial_PIR;
    unsigned char *serial_PIE;
    unsigned char RXIF_mask;
    unsigned char TXIF_mask;
    unsigned char *serial_RCSTA;
    unsigned char *serial_SPBRG;
    unsigned char *serial_SPBRGH;
    unsigned char *serial_BAUDCTL;
    unsigned char *serial_RCREG;
    unsigned char *serial_TXREG;
    unsigned short serial_TXREG_ADDR;
    unsigned short serial_RCSTA_ADDR;
    unsigned short serial_RCREG_ADDR;
    unsigned char *serial_TRIS_RX;
    unsigned char serial_TRIS_RX_MASK;
    bb_uart_t bbuart;
  } _serial;

/**
 * \defgroup pindir pin dir
 * @{
 */
#define PD_OUT 0x00
#define PD_IN 0x01
/**@}*/

/**
 * \defgroup pintype pin types
 * @{
 */
#define PT_POWER 0x00
#define PT_DIGITAL 0x01
#define PT_ANALOG 0x04
#define PT_ANAREF 0x05
#define PT_USART 0x06
#define PT_NC 0xFF
/**@}*/

/**
 * \defgroup family pic family
 * @{
 */
// family
#define P16 1
#define P18 2
#define P16E 3
/**@}*/

// FIXME remove all IDs

// P16 processors
#define P16F84A 0x0560

/*
  #define P16F628      0x07C0
#define P16F877      0x09A0
#define P16F628A     0x1060
#define P16F648A     0x1100
#define P16F648AICD  0x1120
#define P16F877A     0x0E20
 */
#define P16F777 0x0DE0
/*
    //P16E processors
#define P16F1619     0x307D
#define P16F1788     0x302B
#define P16F1789     0x302A
 */
#define P16F18855 0X306C
/*
#define P16F1939     0x23C0
#define P16F18324    0x303A

    //P18 processors
 */
#define P18F452 0x0420
/*
#define P18F4520    0x1080
#define P18F4620    0x0C00
#define P18F4550    0x1200
#define P18F45K50   0x5C00
#define P18F27K40   0x6960
#define P18F47K40   0x6900
    */

/**
 * \defgroup cfg config flags
 * @{
 */
// CFG bits
#define CFG_MCLR 0x01
#define CFG_WDT 0x02
#define CFG_DEBUG 0x04
#define CFG_WDT_DIV 0x08
/**@}*/

/**
 * \defgroup packaging packaging type
 * @{
 */
// PACKAGING
#define PDIP 0
#define QFN 1
/**@}*/

/**
 * \defgroup hexload HEX functions errors
 * @{
 */
// HEX load Errors
#define HEX_OK 0     ///< No erro
#define HEX_NFOUND 1 ///< File not found
#define HEX_CHKSUM 2 ///< Checksum error
#define HEX_NWRITE 3 ///< File write error
                     /**@}*/

  extern unsigned char NO_IO[6];

// pin without IO
#define P_VDD &NO_IO[0]
#define P_VSS &NO_IO[1]
#define P_RST &NO_IO[2]
#define P_OSC &NO_IO[3]
#define P_USB &NO_IO[4]
#define P_NC &NO_IO[5]

  /**
   @brief PICsim PIC structure

  Structure used to describe pic microcontroller .
   */
  typedef struct _pic _pic;

  struct _pic
  {
    unsigned char print; ///< print information ON/OFF
    unsigned int RAMSIZE;
    unsigned int ROMSIZE;
    unsigned int EEPROMSIZE;
    unsigned int IDSIZE;
    unsigned int CONFIGSIZE;
    unsigned char STACKSIZE;
    unsigned char PINCOUNT;
    unsigned char CCPCOUNT;
    unsigned char ADCCOUNT;
    unsigned char USARTCOUNT;
    unsigned char WDT_MS;
    unsigned char family;   ///< @ref family
    unsigned int processor; ///< @ref procid
    unsigned short debugv[8];
    unsigned char *ram;
    unsigned short *prog;
    unsigned short *id;
    unsigned char *eeprom;
    unsigned short *config;
    unsigned int pc;
    unsigned int jpc;
    unsigned short lram; ///< loaded register
    unsigned short rram; ///< readed register
    unsigned int *stack;
    unsigned char w;
    unsigned char wdt;
    unsigned char s2;
    unsigned long long cycles;
    float freq;          ///< frequency
    unsigned char sleep; ///< sleep mode on
    unsigned char pkg;   ///<  @ref packaging
    picpin *pins;
    unsigned char mclr;
    ccp_t *ccp;
    unsigned char *adc;
    unsigned char *usart_rx;
    unsigned char *usart_tx;
    unsigned char pgc;
    unsigned char pgd;
    unsigned char sck;
    unsigned char sdo;
    unsigned char sdi;
    unsigned char t0cki;
    unsigned char t1cki;
    unsigned char intlv;
    // on chip debbuger
    unsigned char ocd_pgca;
    unsigned char ocd_pgc;
    // periferic
    unsigned char debug;
    unsigned char sstep;
    unsigned char dbg;
    unsigned char frst;
    // timers
    int cp0;
    int cp1;
    int cp2;
    int cp2_;
    int cp3;
    int t2pr;
    // timer input
    unsigned char t0cki_;
    unsigned char t1cki_;
    // interrupt
    unsigned char int0;
    unsigned char int1;
    unsigned char int2;
    // pin value
    unsigned char int0v;
    unsigned char int1v;
    unsigned char int2v;
    // portb int mismatch
    unsigned char portbm;
    // adc
    float vcc; ///< Microcontroller VCC used by ADC
    int adcstep;
    unsigned char adcon1;
    // wdt
    float twdt;
    // eeprom
    int ee_wr;
    // ports
    unsigned char p16latch[5];
    unsigned char porta;
    unsigned char portb;
    unsigned char portc;
    unsigned char portd;
    unsigned char porte;
    unsigned char portf;
    unsigned char portg;
    unsigned char trisa;
    unsigned char trisb;
    unsigned char trisc;
    unsigned char trisd;
    unsigned char trise;
    unsigned char trisf;
    unsigned char trisg;
    unsigned char ioupdated;
    unsigned char port_mirror;
    // MSSP
    unsigned char ssp_ck;
    unsigned char ssp_sck;
    unsigned char ssp_scka;
    unsigned char sspsr;
    unsigned char ssp_bit;

    _serial serial[SERIAL_MAX];

    void (*reset)(_pic *pic);
    void (*mmap)(_pic *pic);
    int (*getconf)(_pic *pic, unsigned int);
    void (*disable_debug)(_pic *pic);
    void (*periferic)(_pic *pic);
    int (*interrupt)(_pic *pic);
    void (*stop)(_pic *pic);

    union
    {
      P16map_t P16map;
      P16Emap_t P16Emap;
      P18map_t P18map;
    };
  };

  /**
   * @brief Configure the serial port connection
   *
   *  Use to link the PICSim serial to one serial port
   *
   * @param pic_ pointer to pic object
   * @param nser number of serial
   * @param name Name of serial port
   * @param flowcontrol use flowcontrol
   * @param ctspin  CTS pin if flowcontrol = 1
   * @param rtspin  RTS pin if flowcontrol = 1
   * @return  Return 0 if success, 1 otherwise
   */
  int pic_set_serial(_pic *pic_, int nser, const char *name, int flowcontrol,
                     int ctspin, int rtspin);

  /**
   * @brief Initialize one pic object
   *
   *  Use to initialize the _pic object structure
   *
   * @param pic_ pointer to pic object
   * @param processor microcontroller ID
   * @param fname Name of hex file to load
   * @param leeprom Load EEprom from file if equal to 1
   * @param freq Frequency of microcontoller
   * @return  Return 1 if success, 0 otherwise
   */
  int pic_init(_pic *pic_, int processor, const char *fname, int leeprom,
               float freq);

  /**
   * @brief Reset the microcontroller
   *
   *  Reset the microcontroller to initial state
   *
   * @param flags  0 = WDT reset  1 = Power on reset   -1 = MCLRE pin reset
   * @return Return 1 if success, 0 otherwise
   */
  int pic_reset(_pic *pic_, int flags);

  /**
   * @brief erase the microcontroller FLASH
   *
   */
  void pic_erase_flash(_pic *pic_);

  /**
   * @brief Execute one simulation step
   *
   * Execute one simulation step, must be call continuously to run the program
   * in pic flash memory
   */
  void pic_step(_pic *pic_);

  /**
   * @brief finalize and free pic object internal memory
   *
   */
  void pic_end(_pic *pic_);

  /**
   * @brief Get digital value of one pin
   *
   * @param pin pin number
   * @return pin value 0 or 1
   */
  unsigned char pic_get_pin(_pic *pic_, unsigned char pin);

  /**
   * @brief Set digital value of one pin
   *
   * @param pin pin number
   * @param value pin value 0 or 1
   * @return  Return 1 if success, 0 otherwise
   */
  int pic_set_pin(_pic *pic_, unsigned char pin, unsigned char value);

  /**
   * @brief Set digital value of one pin
   *
   * @param pin pin number
   * @param value pin analog value from 0 to 5
   * @return Return 1 if success, 0 otherwise
   */
  int pic_set_apin(_pic *pic_, unsigned char pin, float value);

  /**
   * @brief Get type of one pin
   *
   * @param pin pin number
   * @return @ref pintype
   */
  unsigned char pic_get_pin_type(_pic *pic_, unsigned char pin);

  /**
   * @brief Get dir of one pin
   *
   * @param pin pin number
   * @return @ref pindir
   */
  unsigned char pic_get_pin_dir(_pic *pic_, unsigned char pin);

  /**
   * @brief Get Default Open Value of one pin (external PULL UP)
   *
   * @param pin pin number
   * @return value 0 or 1
   */
  unsigned char pic_get_pin_DOV(_pic *pic_, unsigned char pin);

  /**
   * @brief Set Default Open Value of one pin (external PULL UP)
   *
   * @param pin pin number
   * @param value pin default value 0 or 1
   * @return Return 1 if success, 0 otherwise
   */
  int pic_set_pin_DOV(_pic *pic_, unsigned char pin, unsigned char value);

  /**
   * @brief Initialize P16 ICSP support
   */
  void pic_icsp_init(_pic *pic_);

  /**
   * @brief Run P16 ICSP (must be pooling)
   * @return Return 1 if success, 0 otherwise
   */
  int pic_icsp(_pic *pic_);

  /**
   * @brief Initialize P18 ICSP support
   */
  void pic_icsp_init18(_pic *pic_);

  /**
   * @brief Run P18 ICSP (must be pooling)
   * @return Return 1 if success, 0 otherwise
   */
  int pic_icsp18(_pic *pic_);

  /**
   * @brief Read HEX file to P16 microcontroller
   *
   * @param fname name of .hex file
   * @param leeprom flag to load or not the microcontroller data eeprom form file
   * @return @ref hexload
   */
  int read_ihx(_pic *pic_, const char *fname, int leeprom);

  /**
   * @brief Read HEX file to P16E microcontroller
   *
   * @param fname name of .hex file
   * @param leeprom flag to load or not the microcontroller data eeprom form file
   * @return @ref hexload
   */
  int read_ihx_16e(_pic *pic_, const char *fname, int leeprom);

  /**
   * @brief Read HEX file to P18 microcontroller
   *
   * @param fname name of .hex file
   * @param leeprom flag to load or not the microcontroller data eeprom form file
   * @return @ref hexload
   */
  int read_ihx_18(_pic *pic_, const char *fname, int leeprom);

  /**
   * @brief Dump all non volatile P16 microcontroller memory to HEX file
   *
   * @param fname name of .hex file
   * @return @ref hexload
   */
  int write_ihx(_pic *pic_, const char *fname);

  /**
   * @brief Dump all non volatile P16E microcontroller memory to HEX file
   *
   * @param fname name of .hex file
   * @return @ref hexload
   */
  int write_ihx16e(_pic *pic_, const char *fname);

  /**
   * @brief Dump all non volatile P18 microcontroller memory to HEX file
   *
   * @param fname name of .hex file
   * @return @ref hexload
   */
  int write_ihx18(_pic *pic_, const char *fname);

  /**
   * @brief Return list name of supported processors
   *
   * @param variable to return the number of supported processors
   * @return array of names
   */
  int getproclist(char list[][30], int size);

  /**
   * @brief Return processor ID by name
   *
   * @param str name of microcontoller
   * @return ID of microcontroller
   */
  unsigned int getprocbyname(const char *str);

  /**
   * @brief Return processor family ID by name
   *
   * @param str name of microcontoller
   * @return family ID of microcontroller
   */
  unsigned int getfprocbyname(const char *str);

  /**
   * @brief Return processor family ID by ID
   *
   * @param proc ID of microcontoller
   * @return family ID of microcontroller
   */
  unsigned int getfprocbynumber(int proc);

  /**
   * @brief Return processor name by ID
   *
   * @param proc ID of microcontoller
   * @param str string to return the name of microcontroller
   * @return filled str parameter
   */
  char *getnamebyproc(int proc, char *str);

  /**
   * @brief Return P16 FSR name by address
   *
   * @param addr address of FSR
   * @return FSR name
   */
  const char *getFSRname_16(unsigned int addr);

  /**
   * @brief Return P16E FSR name by address
   *
   * @param addr address of FSR
   * @return FSR name
   */
  const char *getFSRname_16E(unsigned int addr);

  /**
   * @brief Return P16E2 FSR name by address
   *
   * @param addr address of FSR
   * @return FSR name
   */
  const char *getFSRname_16E2(unsigned int addr);

  /**
   * @brief Return P18 FSR name by address
   *
   * @param addr address of FSR
   * @return FSR name
   */
  const char *getFSRname_18(unsigned int addr);

  /**
   * @brief Return pin name
   *
   * @param pic_ pointer to pic object
   * @param pin pin number
   * @param str string to return the name of pin
   * @return filled str parameter
   */
  const char *getPinName(_pic *pic, int pin, char *pname);

/**
 * @brief Return the mapped address of FSR struct member
 *
 * @param fsr P16map_t, P16Emap_t or P18map_t struct member.
 * @return address of ram
 */
#define sfr_addr(fsr) (fsr - pic->ram)

  typedef struct
  {
    unsigned short ID;
    char name[30];
    unsigned char family;
    void (*start)(_pic *pic);
  } pic_desc;

#define PMAX 35

  extern pic_desc PICS[PMAX];
  extern int PIC_count;

#define init_pic(function, family, ID)                                         \
  static pic_desc desc_##function = {ID, #function, family, function##_start}; \
  static void __attribute__((constructor)) init_##function(void);              \
  static void init_##function(void)                                            \
  {                                                                            \
    pic_register(desc_##function);                                             \
  }

  void pic_register(pic_desc picd);

#endif

#ifdef __cplusplus
}
#endif
