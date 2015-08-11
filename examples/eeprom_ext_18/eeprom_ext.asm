;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 2.9.0 #5416 (Jan 10 2010) (UNIX)
; This file was generated Mon Jun 20 20:13:18 2011
;--------------------------------------------------------
; PIC16 port for the Microchip 16-bit core micros
;--------------------------------------------------------

	.ident "SDCC version 2.9.0 #5416 [pic16 port]"
	.file	"eeprom_ext.c"
	list	p=18f452

	radix dec

;--------------------------------------------------------
; public variables in this module
;--------------------------------------------------------
	global _e2pext_r
	global _e2pext_w

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
	extern _i2c_start
	extern _i2c_stop
	extern _i2c_wb
	extern _i2c_rb
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


; Internal registers
.registers	udata_ovr	0x0000
r0x00	res	1
r0x01	res	1
r0x02	res	1
r0x03	res	1
r0x04	res	1
r0x05	res	1
r0x06	res	1
r0x07	res	1
r0x08	res	1

;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
; I code from now on!
; ; Starting pCode block
S_eeprom_ext__e2pext_w	code
_e2pext_w:
	.line	67; eeprom_ext.c	void e2pext_w(unsigned int addr, unsigned char val)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVFF	r0x02, POSTDEC1
	MOVFF	r0x03, POSTDEC1
	MOVFF	r0x04, POSTDEC1
	MOVFF	r0x05, POSTDEC1
	MOVFF	r0x06, POSTDEC1
	MOVFF	r0x07, POSTDEC1
	MOVFF	r0x08, POSTDEC1
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
	MOVLW	0x03
	MOVFF	PLUSW2, r0x01
	MOVLW	0x04
	MOVFF	PLUSW2, r0x02
	.line	74; eeprom_ext.c	tmp=val;
	CLRF	r0x03
	.line	75; eeprom_ext.c	ah=(addr&0x0100)>>8;
	CLRF	r0x04
	MOVLW	0x01
	ANDWF	r0x01, W
	MOVWF	r0x05
	MOVF	r0x05, W
	MOVWF	r0x04
	CLRF	r0x05
	.line	76; eeprom_ext.c	al=addr&0x00FF;
	MOVF	r0x00, W
	MOVWF	r0x05
	CLRF	r0x06
	.line	79; eeprom_ext.c	do
	CLRF	r0x06
_00120_DS_:
	.line	81; eeprom_ext.c	i2c_start();
	CALL	_i2c_start
	.line	82; eeprom_ext.c	if(ah)
	MOVF	r0x04, W
	BZ	_00117_DS_
	.line	84; eeprom_ext.c	i2c_wb(0xA2);
	MOVLW	0xa2
	MOVWF	POSTDEC1
	CALL	_i2c_wb
	INCF	FSR1L, F
	BRA	_00118_DS_
_00117_DS_:
	.line	88; eeprom_ext.c	i2c_wb(0xA0);
	MOVLW	0xa0
	MOVWF	POSTDEC1
	CALL	_i2c_wb
	INCF	FSR1L, F
_00118_DS_:
	.line	91; eeprom_ext.c	i2c_wb(al);
	MOVF	r0x05, W
	MOVWF	POSTDEC1
	CALL	_i2c_wb
	INCF	FSR1L, F
	.line	92; eeprom_ext.c	i2c_wb(tmp);
	MOVF	r0x02, W
	MOVWF	r0x07
	MOVF	r0x07, W
	MOVWF	POSTDEC1
	CALL	_i2c_wb
	INCF	FSR1L, F
	.line	93; eeprom_ext.c	i2c_stop();
	CALL	_i2c_stop
	.line	95; eeprom_ext.c	nt++;
	INCF	r0x06, F
	.line	97; eeprom_ext.c	while((tmp != e2pext_r(addr))&&(nt < 10));
	MOVF	r0x01, W
	MOVWF	POSTDEC1
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	CALL	_e2pext_r
	MOVWF	r0x07
	MOVLW	0x02
	ADDWF	FSR1L, F
	CLRF	r0x08
	MOVF	r0x02, W
	XORWF	r0x07, W
	BNZ	_00132_DS_
	MOVF	r0x03, W
	XORWF	r0x08, W
	BZ	_00123_DS_
_00132_DS_:
	MOVLW	0x0a
	SUBWF	r0x06, W
	BNC	_00120_DS_
_00123_DS_:
	MOVFF	PREINC1, r0x08
	MOVFF	PREINC1, r0x07
	MOVFF	PREINC1, r0x06
	MOVFF	PREINC1, r0x05
	MOVFF	PREINC1, r0x04
	MOVFF	PREINC1, r0x03
	MOVFF	PREINC1, r0x02
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_eeprom_ext__e2pext_r	code
_e2pext_r:
	.line	29; eeprom_ext.c	unsigned char e2pext_r(unsigned int addr)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVFF	r0x02, POSTDEC1
	MOVFF	r0x03, POSTDEC1
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
	MOVLW	0x03
	MOVFF	PLUSW2, r0x01
	.line	35; eeprom_ext.c	ah=(addr&0x0100)>>8;
	CLRF	r0x02
	MOVLW	0x01
	ANDWF	r0x01, W
	MOVWF	r0x03
	MOVF	r0x03, W
	MOVWF	r0x02
	CLRF	r0x03
	.line	36; eeprom_ext.c	al=addr&0x00FF;
	CLRF	r0x01
	.line	38; eeprom_ext.c	i2c_start();	
	CALL	_i2c_start
	.line	40; eeprom_ext.c	if(ah)
	MOVF	r0x02, W
	BZ	_00106_DS_
	.line	42; eeprom_ext.c	i2c_wb(0xA2);
	MOVLW	0xa2
	MOVWF	POSTDEC1
	CALL	_i2c_wb
	INCF	FSR1L, F
	BRA	_00107_DS_
_00106_DS_:
	.line	46; eeprom_ext.c	i2c_wb(0xA0);
	MOVLW	0xa0
	MOVWF	POSTDEC1
	CALL	_i2c_wb
	INCF	FSR1L, F
_00107_DS_:
	.line	49; eeprom_ext.c	i2c_wb(al);
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	CALL	_i2c_wb
	INCF	FSR1L, F
	.line	51; eeprom_ext.c	i2c_start();
	CALL	_i2c_start
	.line	52; eeprom_ext.c	if(ah)
	MOVF	r0x02, W
	BZ	_00109_DS_
	.line	54; eeprom_ext.c	i2c_wb(0xA3);
	MOVLW	0xa3
	MOVWF	POSTDEC1
	CALL	_i2c_wb
	INCF	FSR1L, F
	BRA	_00110_DS_
_00109_DS_:
	.line	58; eeprom_ext.c	i2c_wb(0xA1);
	MOVLW	0xa1
	MOVWF	POSTDEC1
	CALL	_i2c_wb
	INCF	FSR1L, F
_00110_DS_:
	.line	60; eeprom_ext.c	ret=i2c_rb();
	CALL	_i2c_rb
	MOVWF	r0x00
	.line	61; eeprom_ext.c	i2c_stop();
	CALL	_i2c_stop
	.line	63; eeprom_ext.c	return ret;	
	MOVF	r0x00, W
	MOVFF	PREINC1, r0x03
	MOVFF	PREINC1, r0x02
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	



; Statistics:
; code size:	  382 (0x017e) bytes ( 0.29%)
;           	  191 (0x00bf) words
; udata size:	    0 (0x0000) bytes ( 0.00%)
; access size:	    9 (0x0009) bytes


	end
