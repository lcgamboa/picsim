;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.0.1 #6183 (Jun 18 2011) (Linux)
; This file was generated Thu Aug 30 09:52:38 2012
;--------------------------------------------------------
; PIC16 port for the Microchip 16-bit core micros
;--------------------------------------------------------

	.ident "SDCC version 3.0.1 #6183 [pic16 port]"
	.file	"pic18f452c.c"
	list	p=18f452
	__config 0x300001, 0xfa
	__config 0x300002, 0xfd
	__config 0x300003, 0xfe
	__config 0x300005, 0xff
	__config 0x300006, 0xfb
	__config 0x300008, 0xff
	__config 0x300009, 0xff
	__config 0x30000a, 0xff
	__config 0x30000b, 0xff
	__config 0x30000c, 0xff
	__config 0x30000d, 0xff

	radix dec

;--------------------------------------------------------
; public variables in this module
;--------------------------------------------------------
	global _delay
	global _i2c_init
	global _i2c_start
	global _i2c_stop
	global _i2c_wb
	global _i2c_rb
	global _main

;--------------------------------------------------------
; extern variables in this module
;--------------------------------------------------------
	extern _PORTAbits
	extern _PORTBbits
	extern _PORTCbits
	extern _PORTDbits
	extern _PORTEbits
	extern _LATAbits
	extern _LATBbits
	extern _LATCbits
	extern _LATDbits
	extern _LATEbits
	extern _TRISAbits
	extern _TRISBbits
	extern _TRISCbits
	extern _TRISDbits
	extern _TRISEbits
	extern _PIE1bits
	extern _PIR1bits
	extern _IPR1bits
	extern _PIE2bits
	extern _PIR2bits
	extern _IPR2bits
	extern _EECON1bits
	extern _RCSTAbits
	extern _TXSTAbits
	extern _T3CONbits
	extern _CCP2CONbits
	extern _CCP1CONbits
	extern _ADCON1bits
	extern _ADCON0bits
	extern _SSPCON2bits
	extern _SSPCON1bits
	extern _SSPSTATbits
	extern _T2CONbits
	extern _T1CONbits
	extern _RCONbits
	extern _WDTCONbits
	extern _LVDCONbits
	extern _OSCCONbits
	extern _T0CONbits
	extern _STATUSbits
	extern _INTCON3bits
	extern _INTCON2bits
	extern _INTCONbits
	extern _STKPTRbits
	extern _PORTA
	extern _PORTB
	extern _PORTC
	extern _PORTD
	extern _PORTE
	extern _LATA
	extern _LATB
	extern _LATC
	extern _LATD
	extern _LATE
	extern _TRISA
	extern _TRISB
	extern _TRISC
	extern _TRISD
	extern _TRISE
	extern _PIE1
	extern _PIR1
	extern _IPR1
	extern _PIE2
	extern _PIR2
	extern _IPR2
	extern _EECON1
	extern _EECON2
	extern _EEDATA
	extern _EEADR
	extern _RCSTA
	extern _TXSTA
	extern _TXREG
	extern _RCREG
	extern _SPBRG
	extern _T3CON
	extern _TMR3L
	extern _TMR3H
	extern _CCP2CON
	extern _CCPR2L
	extern _CCPR2H
	extern _CCP1CON
	extern _CCPR1L
	extern _CCPR1H
	extern _ADCON1
	extern _ADCON0
	extern _ADRESL
	extern _ADRESH
	extern _SSPCON2
	extern _SSPCON1
	extern _SSPSTAT
	extern _SSPADD
	extern _SSPBUF
	extern _T2CON
	extern _PR2
	extern _TMR2
	extern _T1CON
	extern _TMR1L
	extern _TMR1H
	extern _RCON
	extern _WDTCON
	extern _LVDCON
	extern _OSCCON
	extern _T0CON
	extern _TMR0L
	extern _TMR0H
	extern _STATUS
	extern _FSR2L
	extern _FSR2H
	extern _PLUSW2
	extern _PREINC2
	extern _POSTDEC2
	extern _POSTINC2
	extern _INDF2
	extern _BSR
	extern _FSR1L
	extern _FSR1H
	extern _PLUSW1
	extern _PREINC1
	extern _POSTDEC1
	extern _POSTINC1
	extern _INDF1
	extern _WREG
	extern _FSR0L
	extern _FSR0H
	extern _PLUSW0
	extern _PREINC0
	extern _POSTDEC0
	extern _POSTINC0
	extern _INDF0
	extern _INTCON3
	extern _INTCON2
	extern _INTCON
	extern _PRODL
	extern _PRODH
	extern _TABLAT
	extern _TBLPTRL
	extern _TBLPTRH
	extern _TBLPTRU
	extern _PCL
	extern _PCLATH
	extern _PCLATU
	extern _STKPTR
	extern _TOSL
	extern _TOSH
	extern _TOSU
;--------------------------------------------------------
;	Equates to used internal registers
;--------------------------------------------------------
STATUS	equ	0xfd8
WREG	equ	0xfe8
FSR0L	equ	0xfe9
FSR1L	equ	0xfe1
FSR2L	equ	0xfd9
POSTDEC1	equ	0xfe5
PREINC1	equ	0xfe4
PLUSW2	equ	0xfdb
PRODH	equ	0xff4


; Internal registers
.registers	udata_ovr	0x0000
r0x00	res	1
r0x01	res	1
r0x02	res	1
r0x03	res	1
r0x04	res	1

udata_pic18f452c_0	udata
_main_val_1_1	res	1

udata_pic18f452c_1	udata
_main_i_1_1	res	1

;--------------------------------------------------------
; interrupt vector 
;--------------------------------------------------------

;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
; I code from now on!
; ; Starting pCode block
S_pic18f452c__main	code
_main:
	.line	107; pic18f452c.c	ADCON1=0x06;
	MOVLW	0x06
	MOVWF	_ADCON1
	.line	108; pic18f452c.c	TRISA=0xFF;
	MOVLW	0xff
	MOVWF	_TRISA
	.line	109; pic18f452c.c	TRISB=0x00;
	CLRF	_TRISB
	.line	110; pic18f452c.c	TRISC=0x11;
	MOVLW	0x11
	MOVWF	_TRISC
	.line	111; pic18f452c.c	TRISD=0x00;
	CLRF	_TRISD
	.line	112; pic18f452c.c	TRISE=0xFC;
	MOVLW	0xfc
	MOVWF	_TRISE
	.line	116; pic18f452c.c	TIDAT=0;
	BCF	_TRISCbits, 4
	.line	117; pic18f452c.c	ICLK=1;
	BSF	_PORTCbits, 3
	.line	118; pic18f452c.c	IDAT=1;
	BSF	_PORTCbits, 4
	.line	120; pic18f452c.c	ICLK=1;
	BSF	_PORTCbits, 3
	.line	121; pic18f452c.c	IDAT=1;
	BSF	_PORTCbits, 4
	NOP 
	NOP 
	NOP 
	NOP 
	.line	126; pic18f452c.c	IDAT=0;
	BCF	_PORTCbits, 4
	NOP 
	NOP 
	NOP 
	NOP 
	.line	133; pic18f452c.c	val=0x5A;
	MOVLW	0x5a
	BANKSEL	_main_val_1_1
	MOVWF	_main_val_1_1, B
	.line	135; pic18f452c.c	ICLK=0;
	BCF	_PORTCbits, 3
	.line	138; pic18f452c.c	for(i=7;i >=0 ;i--)		
	MOVLW	0x07
	BANKSEL	_main_i_1_1
	MOVWF	_main_i_1_1, B
_00162_DS_:
	BSF	STATUS, 0
	BANKSEL	_main_i_1_1
	BTFSS	_main_i_1_1, 7, B
	BCF	STATUS, 0
	BC	_00165_DS_
	.line	140; pic18f452c.c	IDAT=((val>>(i))& 0x01); 
	MOVFF	_main_val_1_1, r0x00
	BANKSEL	_main_i_1_1
	MOVF	_main_i_1_1, W, B
	BZ	_00171_DS_
	BN	_00174_DS_
	NEGF	WREG
	BCF	STATUS, 0
_00172_DS_:
	RRCF	r0x00, F
	ADDLW	0x01
	BNC	_00172_DS_
	BRA	_00171_DS_
_00174_DS_:
	BCF	STATUS, 0
_00173_DS_:
	RLCF	r0x00, F
	ADDLW	0x01
	BNC	_00173_DS_
_00171_DS_:
	MOVLW	0x01
	ANDWF	r0x00, F
	MOVF	r0x00, W
	ANDLW	0x01
	SWAPF	WREG, W
	MOVWF	PRODH
	MOVF	_PORTCbits, W
	ANDLW	0xef
	IORWF	PRODH, W
	MOVWF	_PORTCbits
	.line	141; pic18f452c.c	ICLK=1;
	BSF	_PORTCbits, 3
	NOP 
	NOP 
	NOP 
	NOP 
	.line	146; pic18f452c.c	ICLK=0;
	BCF	_PORTCbits, 3
	BANKSEL	_main_i_1_1
	.line	138; pic18f452c.c	for(i=7;i >=0 ;i--)		
	DECF	_main_i_1_1, F, B
	BRA	_00162_DS_
_00165_DS_:
	.line	149; pic18f452c.c	IDAT=1;
	BSF	_PORTCbits, 4
	.line	150; pic18f452c.c	delay();
	CALL	_delay
	.line	151; pic18f452c.c	ICLK=1;
	BSF	_PORTCbits, 3
	.line	152; pic18f452c.c	delay();
	CALL	_delay
	.line	153; pic18f452c.c	ICLK=0;
	BCF	_PORTCbits, 3
_00160_DS_:
	.line	170; pic18f452c.c	while(1);
	BRA	_00160_DS_
	RETURN	

; ; Starting pCode block
S_pic18f452c__i2c_rb	code
_i2c_rb:
	.line	76; pic18f452c.c	unsigned char i2c_rb(void)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVFF	r0x02, POSTDEC1
	MOVFF	r0x03, POSTDEC1
	MOVFF	r0x04, POSTDEC1
	.line	79; pic18f452c.c	unsigned char ret=0;
	CLRF	r0x00
	.line	81; pic18f452c.c	ICLK=0;
	BCF	_PORTCbits, 3
	.line	82; pic18f452c.c	TIDAT=1;
	BSF	_TRISCbits, 4
	.line	83; pic18f452c.c	IDAT=1;
	BSF	_PORTCbits, 4
	.line	84; pic18f452c.c	for(i=0;i<8;i++)
	CLRF	r0x01
_00143_DS_:
	MOVLW	0x08
	SUBWF	r0x01, W
	BC	_00146_DS_
	.line	86; pic18f452c.c	ICLK=1;
	BSF	_PORTCbits, 3
	.line	87; pic18f452c.c	delay();
	CALL	_delay
	.line	88; pic18f452c.c	ret|=(IDAT<<(7-i));
	CLRF	r0x02
	BTFSC	_PORTCbits, 4
	INCF	r0x02, F
	MOVF	r0x01, W
	SUBLW	0x07
	MOVWF	r0x03
	MOVFF	r0x02, r0x04
	MOVF	r0x03, W
	BZ	_00153_DS_
	NEGF	WREG
	BCF	STATUS, 0
_00154_DS_:
	RLCF	r0x04, F
	ADDLW	0x01
	BNC	_00154_DS_
_00153_DS_:
	MOVF	r0x04, W
	IORWF	r0x00, F
	.line	89; pic18f452c.c	ICLK=0;
	BCF	_PORTCbits, 3
	.line	84; pic18f452c.c	for(i=0;i<8;i++)
	INCF	r0x01, F
	BRA	_00143_DS_
_00146_DS_:
	.line	91; pic18f452c.c	TIDAT=0;
	BCF	_TRISCbits, 4
	.line	92; pic18f452c.c	IDAT=0;
	BCF	_PORTCbits, 4
	.line	93; pic18f452c.c	delay();
	CALL	_delay
	.line	94; pic18f452c.c	ICLK=1;
	BSF	_PORTCbits, 3
	.line	95; pic18f452c.c	delay();
	CALL	_delay
	.line	96; pic18f452c.c	ICLK=0;
	BCF	_PORTCbits, 3
	.line	98; pic18f452c.c	return ret;
	MOVF	r0x00, W
	MOVFF	PREINC1, r0x04
	MOVFF	PREINC1, r0x03
	MOVFF	PREINC1, r0x02
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_pic18f452c__i2c_wb	code
_i2c_wb:
	.line	58; pic18f452c.c	void i2c_wb(unsigned char val)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVFF	r0x02, POSTDEC1
	MOVFF	r0x03, POSTDEC1
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
	.line	61; pic18f452c.c	ICLK=0;
	BCF	_PORTCbits, 3
	.line	62; pic18f452c.c	for(i=0;i<8;i++)		
	CLRF	r0x01
_00125_DS_:
	MOVLW	0x08
	SUBWF	r0x01, W
	BC	_00128_DS_
	.line	64; pic18f452c.c	IDAT=((val>>(7-i))& 0x01);
	MOVFF	r0x01, r0x02
	CLRF	r0x03
	MOVF	r0x02, W
	SUBLW	0x07
	MOVWF	r0x02
	MOVLW	0x00
	SUBFWB	r0x03, F
	MOVF	r0x02, W
	MOVWF	FSR0L
	MOVFF	r0x00, r0x02
	MOVF	FSR0L, W
	BZ	_00135_DS_
	BN	_00138_DS_
	NEGF	WREG
	BCF	STATUS, 0
_00136_DS_:
	RRCF	r0x02, F
	ADDLW	0x01
	BNC	_00136_DS_
	BRA	_00135_DS_
_00138_DS_:
	BCF	STATUS, 0
_00137_DS_:
	RLCF	r0x02, F
	ADDLW	0x01
	BNC	_00137_DS_
_00135_DS_:
	MOVLW	0x01
	ANDWF	r0x02, F
	MOVF	r0x02, W
	ANDLW	0x01
	SWAPF	WREG, W
	MOVWF	PRODH
	MOVF	_PORTCbits, W
	ANDLW	0xef
	IORWF	PRODH, W
	MOVWF	_PORTCbits
	.line	65; pic18f452c.c	ICLK=1;
	BSF	_PORTCbits, 3
	.line	66; pic18f452c.c	delay();
	CALL	_delay
	.line	67; pic18f452c.c	ICLK=0;
	BCF	_PORTCbits, 3
	.line	62; pic18f452c.c	for(i=0;i<8;i++)		
	INCF	r0x01, F
	BRA	_00125_DS_
_00128_DS_:
	.line	69; pic18f452c.c	IDAT=1;
	BSF	_PORTCbits, 4
	.line	70; pic18f452c.c	delay();
	CALL	_delay
	.line	71; pic18f452c.c	ICLK=1;
	BSF	_PORTCbits, 3
	.line	72; pic18f452c.c	delay();
	CALL	_delay
	.line	73; pic18f452c.c	ICLK=0;
	BCF	_PORTCbits, 3
	MOVFF	PREINC1, r0x03
	MOVFF	PREINC1, r0x02
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_pic18f452c__i2c_stop	code
_i2c_stop:
	.line	49; pic18f452c.c	void i2c_stop(void)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	.line	51; pic18f452c.c	ICLK=1;
	BSF	_PORTCbits, 3
	.line	52; pic18f452c.c	IDAT=0;
	BCF	_PORTCbits, 4
	.line	53; pic18f452c.c	delay();
	CALL	_delay
	.line	54; pic18f452c.c	IDAT=1;
	BSF	_PORTCbits, 4
	.line	55; pic18f452c.c	delay();
	CALL	_delay
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_pic18f452c__i2c_start	code
_i2c_start:
	.line	40; pic18f452c.c	void i2c_start(void)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	.line	42; pic18f452c.c	ICLK=1;
	BSF	_PORTCbits, 3
	.line	43; pic18f452c.c	IDAT=1;
	BSF	_PORTCbits, 4
	.line	44; pic18f452c.c	delay();
	CALL	_delay
	.line	45; pic18f452c.c	IDAT=0;
	BCF	_PORTCbits, 4
	.line	46; pic18f452c.c	delay();
	CALL	_delay
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_pic18f452c__i2c_init	code
_i2c_init:
	.line	33; pic18f452c.c	void i2c_init(void)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	.line	35; pic18f452c.c	TIDAT=0;
	BCF	_TRISCbits, 4
	.line	36; pic18f452c.c	ICLK=1;
	BSF	_PORTCbits, 3
	.line	37; pic18f452c.c	IDAT=1;
	BSF	_PORTCbits, 4
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_pic18f452c__delay	code
_delay:
	.line	25; pic18f452c.c	void delay(void)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	NOP 
	NOP 
	NOP 
	NOP 
	MOVFF	PREINC1, FSR2L
	RETURN	



; Statistics:
; code size:	  550 (0x0226) bytes ( 0.42%)
;           	  275 (0x0113) words
; udata size:	    2 (0x0002) bytes ( 0.16%)
; access size:	    5 (0x0005) bytes


	end
