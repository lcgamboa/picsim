;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 2.9.0 #5416 (Jan 10 2010) (UNIX)
; This file was generated Mon Jun 20 20:13:18 2011
;--------------------------------------------------------
; PIC16 port for the Microchip 16-bit core micros
;--------------------------------------------------------

	.ident "SDCC version 2.9.0 #5416 [pic16 port]"
	.file	"i2c.c"
	list	p=18f452

	radix dec

;--------------------------------------------------------
; public variables in this module
;--------------------------------------------------------
	global _i2c_init
	global _i2c_start
	global _i2c_stop
	global _i2c_wb
	global _i2c_rb
	global _delay

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

;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
; I code from now on!
; ; Starting pCode block
S_i2c__i2c_rb	code
_i2c_rb:
	.line	81; i2c.c	unsigned char i2c_rb(void)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVFF	r0x02, POSTDEC1
	MOVFF	r0x03, POSTDEC1
	.line	86; i2c.c	ret=0;
	CLRF	r0x00
	.line	88; i2c.c	ICLK=0;
	BCF	_PORTCbits, 3
	.line	89; i2c.c	TIDAT=1;
	BSF	_TRISCbits, 4
	.line	90; i2c.c	IDAT=1;
	BSF	_PORTCbits, 4
	.line	91; i2c.c	for(i=7;i>=0;i--)
	MOVLW	0x07
	MOVWF	r0x01
_00142_DS_:
	BSF	STATUS, 0
	BTFSS	r0x01, 7
	BCF	STATUS, 0
	BC	_00145_DS_
	.line	93; i2c.c	ICLK=1;
	BSF	_PORTCbits, 3
	.line	94; i2c.c	delay();
	CALL	_delay
	.line	95; i2c.c	ret|=(IDAT<<i);
	CLRF	r0x02
	BTFSC	_PORTCbits, 4
	INCF	r0x02, F
	MOVFF	r0x02, r0x03
	MOVF	r0x01, W
	BZ	_00151_DS_
	BN	_00154_DS_
	NEGF	WREG
	BCF	STATUS, 0
_00152_DS_:
	RLCF	r0x03, F
	ADDLW	0x01
	BNC	_00152_DS_
	BRA	_00151_DS_
_00154_DS_:
	BCF	STATUS, 0
_00153_DS_:
	RRCF	r0x03, F
	ADDLW	0x01
	BNC	_00153_DS_
_00151_DS_:
	MOVF	r0x03, W
	IORWF	r0x00, F
	.line	96; i2c.c	ICLK=0;
	BCF	_PORTCbits, 3
	.line	91; i2c.c	for(i=7;i>=0;i--)
	DECF	r0x01, F
	BRA	_00142_DS_
_00145_DS_:
	.line	98; i2c.c	TIDAT=0;
	BCF	_TRISCbits, 4
	.line	99; i2c.c	IDAT=0;
	BCF	_PORTCbits, 4
	.line	100; i2c.c	delay();
	CALL	_delay
	.line	101; i2c.c	ICLK=1;
	BSF	_PORTCbits, 3
	.line	102; i2c.c	delay();
	CALL	_delay
	.line	103; i2c.c	ICLK=0;
	BCF	_PORTCbits, 3
	.line	105; i2c.c	return ret;
	MOVF	r0x00, W
	MOVFF	PREINC1, r0x03
	MOVFF	PREINC1, r0x02
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_i2c__i2c_wb	code
_i2c_wb:
	.line	61; i2c.c	void i2c_wb(unsigned char val)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVFF	r0x02, POSTDEC1
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
	.line	65; i2c.c	ICLK=0;
	BCF	_PORTCbits, 3
	.line	67; i2c.c	for(i=7;i>=0;i--)		
	MOVLW	0x07
	MOVWF	r0x01
_00125_DS_:
	BSF	STATUS, 0
	BTFSS	r0x01, 7
	BCF	STATUS, 0
	BC	_00128_DS_
	.line	69; i2c.c	IDAT=((val>>i)& 0x01);
	MOVFF	r0x00, r0x02
	MOVF	r0x01, W
	BZ	_00134_DS_
	BN	_00137_DS_
	NEGF	WREG
	BCF	STATUS, 0
_00135_DS_:
	RRCF	r0x02, F
	ADDLW	0x01
	BNC	_00135_DS_
	BRA	_00134_DS_
_00137_DS_:
	BCF	STATUS, 0
_00136_DS_:
	RLCF	r0x02, F
	ADDLW	0x01
	BNC	_00136_DS_
_00134_DS_:
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
	.line	70; i2c.c	ICLK=1;
	BSF	_PORTCbits, 3
	.line	71; i2c.c	delay();
	CALL	_delay
	.line	72; i2c.c	ICLK=0;
	BCF	_PORTCbits, 3
	.line	67; i2c.c	for(i=7;i>=0;i--)		
	DECF	r0x01, F
	BRA	_00125_DS_
_00128_DS_:
	.line	74; i2c.c	IDAT=1;
	BSF	_PORTCbits, 4
	.line	75; i2c.c	delay();
	CALL	_delay
	.line	76; i2c.c	ICLK=1;
	BSF	_PORTCbits, 3
	.line	77; i2c.c	delay();
	CALL	_delay
	.line	78; i2c.c	ICLK=0;
	BCF	_PORTCbits, 3
	MOVFF	PREINC1, r0x02
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_i2c__i2c_stop	code
_i2c_stop:
	.line	52; i2c.c	void i2c_stop(void)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	.line	54; i2c.c	ICLK=1;
	BSF	_PORTCbits, 3
	.line	55; i2c.c	IDAT=0;
	BCF	_PORTCbits, 4
	.line	56; i2c.c	delay();
	CALL	_delay
	.line	57; i2c.c	IDAT=1;
	BSF	_PORTCbits, 4
	.line	58; i2c.c	delay();
	CALL	_delay
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_i2c__i2c_start	code
_i2c_start:
	.line	43; i2c.c	void i2c_start(void)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	.line	45; i2c.c	ICLK=1;
	BSF	_PORTCbits, 3
	.line	46; i2c.c	IDAT=1;
	BSF	_PORTCbits, 4
	.line	47; i2c.c	delay();
	CALL	_delay
	.line	48; i2c.c	IDAT=0;
	BCF	_PORTCbits, 4
	.line	49; i2c.c	delay();
	CALL	_delay
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_i2c__i2c_init	code
_i2c_init:
	.line	36; i2c.c	void i2c_init(void)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	.line	38; i2c.c	TIDAT=0;
	BCF	_TRISCbits, 4
	.line	39; i2c.c	ICLK=1;
	BSF	_PORTCbits, 3
	.line	40; i2c.c	IDAT=1;
	BSF	_PORTCbits, 4
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_i2c__delay	code
_delay:
	.line	28; i2c.c	void delay(void)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	NOP 
	NOP 
	NOP 
	NOP 
	MOVFF	PREINC1, FSR2L
	RETURN	



; Statistics:
; code size:	  368 (0x0170) bytes ( 0.28%)
;           	  184 (0x00b8) words
; udata size:	    0 (0x0000) bytes ( 0.00%)
; access size:	    4 (0x0004) bytes


	end
