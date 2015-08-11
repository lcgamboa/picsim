;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 2.8.0 #5117 (Jun  2 2008) (UNIX)
; This file was generated Fri Jul 16 00:11:14 2010
;--------------------------------------------------------
; PIC port for the 14-bit core
;--------------------------------------------------------
;	.file	"sdcc.c"
	list	p=16f628a
	radix dec
	include "p16f628a.inc"
;--------------------------------------------------------
; config word 
;--------------------------------------------------------
	__config 0x3f38
;--------------------------------------------------------
; external declarations
;--------------------------------------------------------
	extern	_nop
	extern	_CCP1CON_bits
	extern	_CMCON_bits
	extern	_EECON1_bits
	extern	_INTCON_bits
	extern	_OPTION_REG_bits
	extern	_PCON_bits
	extern	_PIE1_bits
	extern	_PIR1_bits
	extern	_PORTA_bits
	extern	_PORTB_bits
	extern	_RCSTA_bits
	extern	_STATUS_bits
	extern	_T1CON_bits
	extern	_T2CON_bits
	extern	_TRISA_bits
	extern	_TRISB_bits
	extern	_TXSTA_bits
	extern	_VRCON_bits
	extern	_INDF
	extern	_TMR0
	extern	_PCL
	extern	_STATUS
	extern	_FSR
	extern	_PORTA
	extern	_PORTB
	extern	_PCLATH
	extern	_INTCON
	extern	_PIR1
	extern	_TMR1L
	extern	_TMR1H
	extern	_T1CON
	extern	_TMR2
	extern	_T2CON
	extern	_CCPR1L
	extern	_CCPR1H
	extern	_CCP1CON
	extern	_RCSTA
	extern	_TXREG
	extern	_RCREG
	extern	_CMCON
	extern	_OPTION_REG
	extern	_TRISA
	extern	_TRISB
	extern	_PIE1
	extern	_PCON
	extern	_PR2
	extern	_TXSTA
	extern	_SPBRG
	extern	_EEDATA
	extern	_EEADR
	extern	_EECON1
	extern	_EECON2
	extern	_VRCON
	extern	__sdcc_gsinit_startup
;--------------------------------------------------------
; global declarations
;--------------------------------------------------------
	global	_main
	global	_cont1
	global	_cont2
	global	_i

	global PSAVE
	global SSAVE
	global WSAVE
	global STK12
	global STK11
	global STK10
	global STK09
	global STK08
	global STK07
	global STK06
	global STK05
	global STK04
	global STK03
	global STK02
	global STK01
	global STK00

sharebank udata_ovr 0x0070
PSAVE	res 1
SSAVE	res 1
WSAVE	res 1
STK12	res 1
STK11	res 1
STK10	res 1
STK09	res 1
STK08	res 1
STK07	res 1
STK06	res 1
STK05	res 1
STK04	res 1
STK03	res 1
STK02	res 1
STK01	res 1
STK00	res 1

;--------------------------------------------------------
; global definitions
;--------------------------------------------------------
UD_sdcc_0	udata
_i	res	2

;--------------------------------------------------------
; absolute symbol definitions
;--------------------------------------------------------
;--------------------------------------------------------
; compiler-defined variables
;--------------------------------------------------------
;--------------------------------------------------------
; initialized data
;--------------------------------------------------------

ID_sdcc_0	idata
_cont1
	db	0x01


ID_sdcc_1	idata
_cont2
	db	0xfe

;--------------------------------------------------------
; overlayable items in internal ram 
;--------------------------------------------------------
;	udata_ovr
;--------------------------------------------------------
; reset vector 
;--------------------------------------------------------
STARTUP	code
	nop
	pagesel __sdcc_gsinit_startup
	goto	__sdcc_gsinit_startup
;--------------------------------------------------------
; code
;--------------------------------------------------------
code_sdcc	code
;***
;  pBlock Stats: dbName = M
;***
;entry:  _main	;Function start
; 2 exit points
;has an exit
;functions called:
;   _nop
;   _nop
;; Starting pCode block
_main	;Function start
; 2 exit points
;	.line	20; "sdcc.c"	TRISA=0xFF;
	MOVLW	0xff
	BANKSEL	_TRISA
	MOVWF	_TRISA
;	.line	21; "sdcc.c"	TRISB=0;
	CLRF	_TRISB
_00106_DS_
;	.line	25; "sdcc.c"	PORTB=cont1;
	BANKSEL	_cont1
	MOVF	_cont1,W
	BANKSEL	_PORTB
	MOVWF	_PORTB
;	.line	26; "sdcc.c"	cont1++;
	BANKSEL	_cont1
	INCF	_cont1,F
;	.line	28; "sdcc.c"	for(i=0; i < 5120; i++)
	BANKSEL	_i
	CLRF	_i
	CLRF	(_i + 1)
;unsigned compare: left < lit(0x1400=5120), size=2
_00108_DS_
	MOVLW	0x14
	BANKSEL	_i
	SUBWF	(_i + 1),W
	BTFSS	STATUS,2
	GOTO	_00117_DS_
	MOVLW	0x00
	SUBWF	_i,W
_00117_DS_
	BTFSC	STATUS,0
	GOTO	_00106_DS_
;genSkipc:3225: created from rifx:0x7ffffffefff0
;	.line	30; "sdcc.c"	nop(); 
	PAGESEL	_nop
	CALL	_nop
	PAGESEL	$
;	.line	28; "sdcc.c"	for(i=0; i < 5120; i++)
	BANKSEL	_i
	INCF	_i,F
	BTFSC	STATUS,2
	INCF	(_i + 1),F
	GOTO	_00108_DS_
	RETURN	
; exit point of _main


;	code size estimation:
;	   22+    9 =    31 instructions (   80 byte)

	end
