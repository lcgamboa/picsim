;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 2.8.0 #5117 (Jun  2 2008) (UNIX)
; This file was generated Sat Jan 29 15:05:40 2011
;--------------------------------------------------------
; PIC16 port for the Microchip 16-bit core micros
;--------------------------------------------------------

	.ident "SDCC version 2.8.0 #5117 [pic16 port]"
	.file	"tmr0.c"
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
	global _cnt
	global _isr
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
PCLATH	equ	0xffa
PCLATU	equ	0xffb
WREG	equ	0xfe8
BSR	equ	0xfe0
FSR0L	equ	0xfe9
FSR0H	equ	0xfea
FSR1L	equ	0xfe1
FSR2L	equ	0xfd9
POSTDEC1	equ	0xfe5
PREINC1	equ	0xfe4
PRODL	equ	0xff3
PRODH	equ	0xff4

udata_tmr0_0	udata
_cnt	res	1

;--------------------------------------------------------
; interrupt vector 
;--------------------------------------------------------

;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
; ; Starting pCode block for absolute section
; ;-----------------------------------------
S_tmr0_ivec_0x1_isr	code	0X000008
ivec_0x1_isr:
	GOTO	_isr

; I code from now on!
; ; Starting pCode block
S_tmr0__main	code
_main:
	.line	44; tmr0.c	INTCON=0;        //Deliga interrupcoes
	CLRF	_INTCON
	.line	47; tmr0.c	TRISA=0xFE;	//configura PORTA
	MOVLW	0xfe
	MOVWF	_TRISA
	.line	48; tmr0.c	TRISB=0x00;	//configura PORTB
	CLRF	_TRISB
	.line	51; tmr0.c	T0CONbits.TMR0ON=1;
	BSF	_T0CONbits, 7
	.line	52; tmr0.c	T0CONbits.T08BIT=1;
	BSF	_T0CONbits, 6
	.line	53; tmr0.c	T0CONbits.T0CS=0;		// Seleciona clock do tmr0 como clock_cpu/4 
	BCF	_T0CONbits, 5
	.line	54; tmr0.c	T0CONbits.PSA=0;		// Usa pre-scaler
	BCF	_T0CONbits, 3
	.line	56; tmr0.c	T0CONbits.T0PS2=1;		//111 = clk / 256 
	BSF	_T0CONbits, 2
	.line	57; tmr0.c	T0CONbits.T0PS1=1;
	BSF	_T0CONbits, 1
	.line	58; tmr0.c	T0CONbits.T0PS0=1;
	BSF	_T0CONbits, 0
	.line	60; tmr0.c	TMR0L=_tmr0_ini;	//incicia timer com 55, conta de 55 a 255 (200)
	MOVLW	0x37
	MOVWF	_TMR0L
	.line	62; tmr0.c	cnt=_cnt_ini;	//variavel auxiliar
	MOVLW	0x14
	BANKSEL	_cnt
	MOVWF	_cnt, B
	.line	69; tmr0.c	INTCONbits.T0IF=0;		//Apaga flag de interrupcao	
	BCF	_INTCONbits, 2
	.line	71; tmr0.c	PORTB=0xFF;
	MOVLW	0xff
	MOVWF	_PORTB
_00111_DS_:
	.line	75; tmr0.c	while(!INTCONbits.T0IF);
	BTFSS	_INTCONbits, 2
	GOTO	_00111_DS_
	BANKSEL	_cnt
	.line	77; tmr0.c	cnt=cnt-1;	//decrementa contagem
	DECF	_cnt, F, B
	BANKSEL	_cnt
	.line	79; tmr0.c	if(cnt == 0)	//quando contagem = 0;
	MOVF	_cnt, W, B
	BTFSS	STATUS, 2
	GOTO	_00115_DS_
	.line	81; tmr0.c	PORTB= PORTB ^0x0FF;	//troca estado PORTB
	MOVLW	0xff
	XORWF	_PORTB, F
	.line	82; tmr0.c	cnt=_cnt_ini;		//reinicia contador
	MOVLW	0x14
	BANKSEL	_cnt
	MOVWF	_cnt, B
_00115_DS_:
	.line	85; tmr0.c	TMR0L=_tmr0_ini;	//reinicia contagem
	MOVLW	0x37
	MOVWF	_TMR0L
	.line	86; tmr0.c	INTCONbits.T0IF=0;		// reseta flag TMR0
	BCF	_INTCONbits, 2
	GOTO	_00111_DS_
	RETURN	

; ; Starting pCode block
S_tmr0__isr	code
_isr:
	.line	26; tmr0.c	void isr() interrupt 1 
	MOVFF	WREG, POSTDEC1
	MOVFF	STATUS, POSTDEC1
	MOVFF	BSR, POSTDEC1
	MOVFF	PRODL, POSTDEC1
	MOVFF	PRODH, POSTDEC1
	MOVFF	FSR0L, POSTDEC1
	MOVFF	FSR0H, POSTDEC1
	MOVFF	PCLATH, POSTDEC1
	MOVFF	PCLATU, POSTDEC1
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	BANKSEL	_cnt
	.line	28; tmr0.c	cnt=cnt-1;	//decrementa contagem
	DECF	_cnt, F, B
	BANKSEL	_cnt
	.line	30; tmr0.c	if(cnt == 0)	//quando contagem = 0;
	MOVF	_cnt, W, B
	BTFSS	STATUS, 2
	GOTO	_00106_DS_
	.line	32; tmr0.c	PORTB= PORTB ^0x0FF;	//troca estado PORTB
	MOVLW	0xff
	XORWF	_PORTB, F
	.line	33; tmr0.c	cnt=_cnt_ini;		//reinicia contador
	MOVLW	0x14
	BANKSEL	_cnt
	MOVWF	_cnt, B
_00106_DS_:
	.line	36; tmr0.c	TMR0L=_tmr0_ini;	//reinicia contagem
	MOVLW	0x37
	MOVWF	_TMR0L
	.line	37; tmr0.c	INTCONbits.T0IF=0;		// reseta flag TMR0
	BCF	_INTCONbits, 2
	MOVFF	PREINC1, FSR2L
	MOVFF	PREINC1, PCLATU
	MOVFF	PREINC1, PCLATH
	MOVFF	PREINC1, FSR0H
	MOVFF	PREINC1, FSR0L
	MOVFF	PREINC1, PRODH
	MOVFF	PREINC1, PRODL
	MOVFF	PREINC1, BSR
	MOVFF	PREINC1, STATUS
	MOVFF	PREINC1, WREG
	RETFIE	



; Statistics:
; code size:	  198 (0x00c6) bytes ( 0.15%)
;           	   99 (0x0063) words
; udata size:	    1 (0x0001) bytes ( 0.08%)
; access size:	    0 (0x0000) bytes


	end
