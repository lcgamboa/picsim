;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 2.8.0 #5117 (Jul 24 2008) (UNIX)
; This file was generated Thu Jul 24 18:42:28 2008
;--------------------------------------------------------
; PIC port for the 14-bit core
;--------------------------------------------------------
	.file	"spi.c"
	list	p=16f628a
	radix dec
	include "p16f628a.inc"
;--------------------------------------------------------
; config word 
;--------------------------------------------------------
	__config 0x3f50
;--------------------------------------------------------
; external declarations
;--------------------------------------------------------
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
	global	_setPixel
	global	_sendData
	global	_shiftBits
	global	_sendCMD
	global	_delay_ms
	global	_putc
	global	_getc
	global	_main
	global	_n
	global	_s1
	global	_s2
	global	_r
	global	_g
	global	_b

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
UD_spi_0	udata
_n	res	1

UD_spi_1	udata
_s1	res	1

UD_spi_2	udata
_s2	res	1

UD_spi_3	udata
_r	res	1

UD_spi_4	udata
_g	res	1

UD_spi_5	udata
_b	res	1

;--------------------------------------------------------
; absolute symbol definitions
;--------------------------------------------------------
;--------------------------------------------------------
; compiler-defined variables
;--------------------------------------------------------
UDL_spi_0	udata
r0x100B	res	1
r0x100C	res	1
r0x1009	res	1
r0x100A	res	1
_c	res	1
_d	res	1
_e	res	1
;--------------------------------------------------------
; initialized data
;--------------------------------------------------------
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
code_spi	code
;***
;  pBlock Stats: dbName = M
;***
;entry:  _main	;Function start
; 2 exit points
;has an exit
;functions called:
;   _putc
;   _putc
;   _putc
;   _putc
;   _delay_ms
;   _delay_ms
;   _delay_ms
;   _sendCMD
;   _sendCMD
;   _sendCMD
;   _delay_ms
;   _sendCMD
;   _sendCMD
;   _sendCMD
;   _sendCMD
;   _sendCMD
;   _sendData
;   _sendCMD
;   _sendData
;   _sendCMD
;   _sendData
;   _sendCMD
;   _sendData
;   _sendData
;   _sendCMD
;   _sendData
;   _sendData
;   _sendCMD
;   _setPixel
;   _setPixel
;   _setPixel
;   _setPixel
;   _putc
;   _putc
;   _putc
;   _putc
;   _putc
;   _getc
;   _getc
;   _getc
;   _setPixel
;   _putc
;   _putc
;   _putc
;   _putc
;   _putc
;   _delay_ms
;   _delay_ms
;   _delay_ms
;   _sendCMD
;   _sendCMD
;   _sendCMD
;   _delay_ms
;   _sendCMD
;   _sendCMD
;   _sendCMD
;   _sendCMD
;   _sendCMD
;   _sendData
;   _sendCMD
;   _sendData
;   _sendCMD
;   _sendData
;   _sendCMD
;   _sendData
;   _sendData
;   _sendCMD
;   _sendData
;   _sendData
;   _sendCMD
;   _setPixel
;   _setPixel
;   _setPixel
;   _setPixel
;   _putc
;   _putc
;   _putc
;   _putc
;   _putc
;   _getc
;   _getc
;   _getc
;   _setPixel
;   _putc
;4 compiler assigned registers:
;   r0x1009
;   r0x100A
;   STK01
;   STK00
;; Starting pCode block
;; gen.c:2327:resultRemat *{*
;; gen.c:2686:genLabel *{*
;; ***	genLabel  2689
;; gen.c:2327:resultRemat *{*
;; gen.c:2372:genFunction *{*
;; ***	genFunction  2374 curr label offset=68previous max_key=1 
_main	;Function start
; 2 exit points
;; gen.c:2327:resultRemat *{*
;; gen.c:8139:genAssign *{*
;; ***	genAssign  8140
;; ***	aopForSym 393
;;	404 sym->rname = _n, size = 1
;; 	line = 8149 result AOP_DIR=_n, size=1, left -=-, size=0, right AOP_LIT=0x00, size=1
;; ***	genAssign  8241
; >>> gen.c:8250:genAssign
;;	1036
;;	1052  _n   offset=0
	.line	190; "spi.c"	n=0; 
	BANKSEL	_n
	CLRF	_n
;; gen.c:2327:resultRemat *{*
;; gen.c:8139:genAssign *{*
;; ***	genAssign  8140
;; ***	aopForSym 393
;;	404 sym->rname = _TRISB, size = 1
;; 	line = 8149 result AOP_DIR=_TRISB, size=1, left -=-, size=0, right AOP_LIT=0x00, size=1
;; ***	genAssign  8241
; >>> gen.c:8250:genAssign
;;	1036
;;	1052  _TRISB   offset=0
	.line	192; "spi.c"	TRISB=0;
	BANKSEL	_TRISB
	CLRF	_TRISB
;; gen.c:2327:resultRemat *{*
;; gen.c:8139:genAssign *{*
;; ***	genAssign  8140
;; ***	aopForSym 393
;;	404 sym->rname = _TRISB, size = 1
;; 	line = 8149 result AOP_DIR=_TRISB, size=1, left -=-, size=0, right AOP_LIT=0x06, size=1
;; ***	genAssign  8241
; >>> gen.c:8246:genAssign
	.line	193; "spi.c"	TRISB=TX_BIT|RX_BIT;	// These need to be 1 for USART to work
	MOVLW	0x06
; >>> gen.c:8248:genAssign
;;	1036
;;	1052  _TRISB   offset=0
	MOVWF	_TRISB
;; gen.c:2327:resultRemat *{*
;; gen.c:8139:genAssign *{*
;; ***	genAssign  8140
;; ***	aopForSym 393
;;	404 sym->rname = _SPBRG, size = 1
;; 	line = 8149 result AOP_DIR=_SPBRG, size=1, left -=-, size=0, right AOP_LIT=0x0c, size=1
;; ***	genAssign  8241
; >>> gen.c:8246:genAssign
	.line	195; "spi.c"	SPBRG=SPBRG_VALUE ;	// Baud Rate register, calculated by macro
	MOVLW	0x0c
; >>> gen.c:8248:genAssign
;;	1036
;;	1052  _SPBRG   offset=0
	MOVWF	_SPBRG
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:7895:genPointerSet *{*
;; ***	genPointerSet  7896
;; gen.c:7723:genNearPointerSet *{*
;; ***	genNearPointerSet  7724
;;	689
;;	aopForRemat 474
;;	495: rname _TXSTA_bits, val 0, const = 0
;; ***	genNearPointerSet  7741
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_TXSTA_bits
;; 	line = 7743 result AOP_PCODE=_TXSTA_bits, size=2, left -=-, size=0, right AOP_LIT=0x01, size=1
;; gen.c:7472:genPackBits *{*
;; ***	genPackBits  7473
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_TXSTA_bits
; >>> gen.c:7498:genPackBits
	.line	197; "spi.c"	BRGH=BAUD_HI;
	BSF	_TXSTA_bits,2
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:7895:genPointerSet *{*
;; ***	genPointerSet  7896
;; gen.c:7723:genNearPointerSet *{*
;; ***	genNearPointerSet  7724
;;	689
;;	aopForRemat 474
;;	495: rname _TXSTA_bits, val 0, const = 0
;; ***	genNearPointerSet  7741
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_TXSTA_bits
;; 	line = 7743 result AOP_PCODE=_TXSTA_bits, size=2, left -=-, size=0, right AOP_LIT=0x00, size=1
;; gen.c:7472:genPackBits *{*
;; ***	genPackBits  7473
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_TXSTA_bits
; >>> gen.c:7498:genPackBits
	.line	199; "spi.c"	SYNC=0;			// Disable Synchronous/Enable Asynchronous
	BCF	_TXSTA_bits,4
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:7895:genPointerSet *{*
;; ***	genPointerSet  7896
;; gen.c:7723:genNearPointerSet *{*
;; ***	genNearPointerSet  7724
;;	689
;;	aopForRemat 474
;;	495: rname _RCSTA_bits, val 0, const = 0
;; ***	genNearPointerSet  7741
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_RCSTA_bits
;; 	line = 7743 result AOP_PCODE=_RCSTA_bits, size=2, left -=-, size=0, right AOP_LIT=0x01, size=1
;; gen.c:7472:genPackBits *{*
;; ***	genPackBits  7473
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_RCSTA_bits
; >>> gen.c:7498:genPackBits
	.line	200; "spi.c"	SPEN=1;			// Enable serial port
	BANKSEL	_RCSTA_bits
	BSF	_RCSTA_bits,7
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:7895:genPointerSet *{*
;; ***	genPointerSet  7896
;; gen.c:7723:genNearPointerSet *{*
;; ***	genNearPointerSet  7724
;;	689
;;	aopForRemat 474
;;	495: rname _TXSTA_bits, val 0, const = 0
;; ***	genNearPointerSet  7741
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_TXSTA_bits
;; 	line = 7743 result AOP_PCODE=_TXSTA_bits, size=2, left -=-, size=0, right AOP_LIT=0x01, size=1
;; gen.c:7472:genPackBits *{*
;; ***	genPackBits  7473
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_TXSTA_bits
; >>> gen.c:7498:genPackBits
	.line	201; "spi.c"	TXEN=1;			// Enable transmission mode
	BANKSEL	_TXSTA_bits
	BSF	_TXSTA_bits,5
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:7895:genPointerSet *{*
;; ***	genPointerSet  7896
;; gen.c:7723:genNearPointerSet *{*
;; ***	genNearPointerSet  7724
;;	689
;;	aopForRemat 474
;;	495: rname _RCSTA_bits, val 0, const = 0
;; ***	genNearPointerSet  7741
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_RCSTA_bits
;; 	line = 7743 result AOP_PCODE=_RCSTA_bits, size=2, left -=-, size=0, right AOP_LIT=0x01, size=1
;; gen.c:7472:genPackBits *{*
;; ***	genPackBits  7473
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_RCSTA_bits
; >>> gen.c:7498:genPackBits
	.line	202; "spi.c"	CREN=1;			// Enable reception mod
	BANKSEL	_RCSTA_bits
	BSF	_RCSTA_bits,4
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:2096:genCall *{*
;; ***	genCall  2098
;; gen.c:1781:saveRegisters *{*
;; ***	saveRegisters  1783
;; 	2145 left AOP_LIT
;; gen.c:1390:mov2w_op *{*
; >>> gen.c:1405:mov2w_op
	.line	205; "spi.c"	putc('O');
	MOVLW	0x4f
; >>> gen.c:2184:genCall
	CALL	_putc
;; gen.c:1825:unsaveRegisters *{*
;; ***	unsaveRegisters  1827
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:2096:genCall *{*
;; ***	genCall  2098
;; gen.c:1781:saveRegisters *{*
;; ***	saveRegisters  1783
;; 	2145 left AOP_LIT
;; gen.c:1390:mov2w_op *{*
; >>> gen.c:1405:mov2w_op
	.line	206; "spi.c"	putc('K');
	MOVLW	0x4b
; >>> gen.c:2184:genCall
	CALL	_putc
;; gen.c:1825:unsaveRegisters *{*
;; ***	unsaveRegisters  1827
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:2096:genCall *{*
;; ***	genCall  2098
;; gen.c:1781:saveRegisters *{*
;; ***	saveRegisters  1783
;; 	2145 left AOP_LIT
;; gen.c:1390:mov2w_op *{*
; >>> gen.c:1405:mov2w_op
	.line	207; "spi.c"	putc('\n');
	MOVLW	0x0a
; >>> gen.c:2184:genCall
	CALL	_putc
;; gen.c:1825:unsaveRegisters *{*
;; ***	unsaveRegisters  1827
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:2096:genCall *{*
;; ***	genCall  2098
;; gen.c:1781:saveRegisters *{*
;; ***	saveRegisters  1783
;; 	2145 left AOP_LIT
;; gen.c:1390:mov2w_op *{*
; >>> gen.c:1405:mov2w_op
	.line	208; "spi.c"	putc('\r');
	MOVLW	0x0d
; >>> gen.c:2184:genCall
	CALL	_putc
;; gen.c:1825:unsaveRegisters *{*
;; ***	unsaveRegisters  1827
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:7895:genPointerSet *{*
;; ***	genPointerSet  7896
;; gen.c:7723:genNearPointerSet *{*
;; ***	genNearPointerSet  7724
;;	689
;;	aopForRemat 474
;;	495: rname _PORTB_bits, val 0, const = 0
;; ***	genNearPointerSet  7741
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
;; 	line = 7743 result AOP_PCODE=_PORTB_bits, size=2, left -=-, size=0, right AOP_LIT=0x00, size=1
;; gen.c:7472:genPackBits *{*
;; ***	genPackBits  7473
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
; >>> gen.c:7498:genPackBits
	.line	211; "spi.c"	CS0
	BANKSEL	_PORTB_bits
	BCF	_PORTB_bits,5
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:7895:genPointerSet *{*
;; ***	genPointerSet  7896
;; gen.c:7723:genNearPointerSet *{*
;; ***	genNearPointerSet  7724
;;	689
;;	aopForRemat 474
;;	495: rname _PORTB_bits, val 0, const = 0
;; ***	genNearPointerSet  7741
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
;; 	line = 7743 result AOP_PCODE=_PORTB_bits, size=2, left -=-, size=0, right AOP_LIT=0x00, size=1
;; gen.c:7472:genPackBits *{*
;; ***	genPackBits  7473
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
; >>> gen.c:7498:genPackBits
	.line	212; "spi.c"	SDA0
	BCF	_PORTB_bits,6
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:7895:genPointerSet *{*
;; ***	genPointerSet  7896
;; gen.c:7723:genNearPointerSet *{*
;; ***	genNearPointerSet  7724
;;	689
;;	aopForRemat 474
;;	495: rname _PORTB_bits, val 0, const = 0
;; ***	genNearPointerSet  7741
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
;; 	line = 7743 result AOP_PCODE=_PORTB_bits, size=2, left -=-, size=0, right AOP_LIT=0x01, size=1
;; gen.c:7472:genPackBits *{*
;; ***	genPackBits  7473
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
; >>> gen.c:7498:genPackBits
	.line	213; "spi.c"	CLK1
	BSF	_PORTB_bits,7
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:7895:genPointerSet *{*
;; ***	genPointerSet  7896
;; gen.c:7723:genNearPointerSet *{*
;; ***	genNearPointerSet  7724
;;	689
;;	aopForRemat 474
;;	495: rname _PORTB_bits, val 0, const = 0
;; ***	genNearPointerSet  7741
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
;; 	line = 7743 result AOP_PCODE=_PORTB_bits, size=2, left -=-, size=0, right AOP_LIT=0x01, size=1
;; gen.c:7472:genPackBits *{*
;; ***	genPackBits  7473
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
; >>> gen.c:7498:genPackBits
	.line	215; "spi.c"	RESET1 	
	BSF	_PORTB_bits,4
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:2096:genCall *{*
;; ***	genCall  2098
;; gen.c:1781:saveRegisters *{*
;; ***	saveRegisters  1783
;; 	2145 left AOP_LIT
;; gen.c:1390:mov2w_op *{*
; >>> gen.c:1405:mov2w_op
	.line	216; "spi.c"	delay_ms(10);
	MOVLW	0x0a
; >>> gen.c:2184:genCall
	CALL	_delay_ms
;; gen.c:1825:unsaveRegisters *{*
;; ***	unsaveRegisters  1827
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:7895:genPointerSet *{*
;; ***	genPointerSet  7896
;; gen.c:7723:genNearPointerSet *{*
;; ***	genNearPointerSet  7724
;;	689
;;	aopForRemat 474
;;	495: rname _PORTB_bits, val 0, const = 0
;; ***	genNearPointerSet  7741
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
;; 	line = 7743 result AOP_PCODE=_PORTB_bits, size=2, left -=-, size=0, right AOP_LIT=0x00, size=1
;; gen.c:7472:genPackBits *{*
;; ***	genPackBits  7473
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
; >>> gen.c:7498:genPackBits
	.line	217; "spi.c"	RESET0
	BANKSEL	_PORTB_bits
	BCF	_PORTB_bits,4
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:2096:genCall *{*
;; ***	genCall  2098
;; gen.c:1781:saveRegisters *{*
;; ***	saveRegisters  1783
;; 	2145 left AOP_LIT
;; gen.c:1390:mov2w_op *{*
; >>> gen.c:1405:mov2w_op
	.line	218; "spi.c"	delay_ms(10);
	MOVLW	0x0a
; >>> gen.c:2184:genCall
	CALL	_delay_ms
;; gen.c:1825:unsaveRegisters *{*
;; ***	unsaveRegisters  1827
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:7895:genPointerSet *{*
;; ***	genPointerSet  7896
;; gen.c:7723:genNearPointerSet *{*
;; ***	genNearPointerSet  7724
;;	689
;;	aopForRemat 474
;;	495: rname _PORTB_bits, val 0, const = 0
;; ***	genNearPointerSet  7741
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
;; 	line = 7743 result AOP_PCODE=_PORTB_bits, size=2, left -=-, size=0, right AOP_LIT=0x01, size=1
;; gen.c:7472:genPackBits *{*
;; ***	genPackBits  7473
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
; >>> gen.c:7498:genPackBits
	.line	219; "spi.c"	RESET1
	BANKSEL	_PORTB_bits
	BSF	_PORTB_bits,4
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:7895:genPointerSet *{*
;; ***	genPointerSet  7896
;; gen.c:7723:genNearPointerSet *{*
;; ***	genNearPointerSet  7724
;;	689
;;	aopForRemat 474
;;	495: rname _PORTB_bits, val 0, const = 0
;; ***	genNearPointerSet  7741
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
;; 	line = 7743 result AOP_PCODE=_PORTB_bits, size=2, left -=-, size=0, right AOP_LIT=0x01, size=1
;; gen.c:7472:genPackBits *{*
;; ***	genPackBits  7473
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
; >>> gen.c:7498:genPackBits
	.line	221; "spi.c"	CLK1
	BSF	_PORTB_bits,7
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:7895:genPointerSet *{*
;; ***	genPointerSet  7896
;; gen.c:7723:genNearPointerSet *{*
;; ***	genNearPointerSet  7724
;;	689
;;	aopForRemat 474
;;	495: rname _PORTB_bits, val 0, const = 0
;; ***	genNearPointerSet  7741
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
;; 	line = 7743 result AOP_PCODE=_PORTB_bits, size=2, left -=-, size=0, right AOP_LIT=0x01, size=1
;; gen.c:7472:genPackBits *{*
;; ***	genPackBits  7473
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
; >>> gen.c:7498:genPackBits
	.line	222; "spi.c"	SDA1
	BSF	_PORTB_bits,6
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:7895:genPointerSet *{*
;; ***	genPointerSet  7896
;; gen.c:7723:genNearPointerSet *{*
;; ***	genNearPointerSet  7724
;;	689
;;	aopForRemat 474
;;	495: rname _PORTB_bits, val 0, const = 0
;; ***	genNearPointerSet  7741
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
;; 	line = 7743 result AOP_PCODE=_PORTB_bits, size=2, left -=-, size=0, right AOP_LIT=0x01, size=1
;; gen.c:7472:genPackBits *{*
;; ***	genPackBits  7473
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
; >>> gen.c:7498:genPackBits
	.line	223; "spi.c"	CLK1
	BSF	_PORTB_bits,7
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:2096:genCall *{*
;; ***	genCall  2098
;; gen.c:1781:saveRegisters *{*
;; ***	saveRegisters  1783
;; 	2145 left AOP_LIT
;; gen.c:1390:mov2w_op *{*
; >>> gen.c:1405:mov2w_op
	.line	225; "spi.c"	delay_ms(10);
	MOVLW	0x0a
; >>> gen.c:2184:genCall
	CALL	_delay_ms
;; gen.c:1825:unsaveRegisters *{*
;; ***	unsaveRegisters  1827
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:2096:genCall *{*
;; ***	genCall  2098
;; gen.c:1781:saveRegisters *{*
;; ***	saveRegisters  1783
;; 	2145 left AOP_LIT
;; gen.c:1390:mov2w_op *{*
; >>> gen.c:1405:mov2w_op
	.line	228; "spi.c"	sendCMD(0x01);
	MOVLW	0x01
; >>> gen.c:2184:genCall
	CALL	_sendCMD
;; gen.c:1825:unsaveRegisters *{*
;; ***	unsaveRegisters  1827
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:2096:genCall *{*
;; ***	genCall  2098
;; gen.c:1781:saveRegisters *{*
;; ***	saveRegisters  1783
;; 	2145 left AOP_LIT
;; gen.c:1390:mov2w_op *{*
; >>> gen.c:1405:mov2w_op
	.line	231; "spi.c"	sendCMD(0x11);
	MOVLW	0x11
; >>> gen.c:2184:genCall
	CALL	_sendCMD
;; gen.c:1825:unsaveRegisters *{*
;; ***	unsaveRegisters  1827
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:2096:genCall *{*
;; ***	genCall  2098
;; gen.c:1781:saveRegisters *{*
;; ***	saveRegisters  1783
;; 	2145 left AOP_LIT
;; gen.c:1390:mov2w_op *{*
; >>> gen.c:1405:mov2w_op
	.line	234; "spi.c"	sendCMD(0x03);
	MOVLW	0x03
; >>> gen.c:2184:genCall
	CALL	_sendCMD
;; gen.c:1825:unsaveRegisters *{*
;; ***	unsaveRegisters  1827
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:2096:genCall *{*
;; ***	genCall  2098
;; gen.c:1781:saveRegisters *{*
;; ***	saveRegisters  1783
;; 	2145 left AOP_LIT
;; gen.c:1390:mov2w_op *{*
; >>> gen.c:1405:mov2w_op
	.line	236; "spi.c"	delay_ms(10);
	MOVLW	0x0a
; >>> gen.c:2184:genCall
	CALL	_delay_ms
;; gen.c:1825:unsaveRegisters *{*
;; ***	unsaveRegisters  1827
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:2096:genCall *{*
;; ***	genCall  2098
;; gen.c:1781:saveRegisters *{*
;; ***	saveRegisters  1783
;; 	2145 left AOP_LIT
;; gen.c:1390:mov2w_op *{*
; >>> gen.c:1405:mov2w_op
	.line	239; "spi.c"	sendCMD(0x29);
	MOVLW	0x29
; >>> gen.c:2184:genCall
	CALL	_sendCMD
;; gen.c:1825:unsaveRegisters *{*
;; ***	unsaveRegisters  1827
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:2096:genCall *{*
;; ***	genCall  2098
;; gen.c:1781:saveRegisters *{*
;; ***	saveRegisters  1783
;; 	2145 left AOP_LIT
;; gen.c:1390:mov2w_op *{*
; >>> gen.c:1405:mov2w_op
	.line	242; "spi.c"	sendCMD(0x13);
	MOVLW	0x13
; >>> gen.c:2184:genCall
	CALL	_sendCMD
;; gen.c:1825:unsaveRegisters *{*
;; ***	unsaveRegisters  1827
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:2096:genCall *{*
;; ***	genCall  2098
;; gen.c:1781:saveRegisters *{*
;; ***	saveRegisters  1783
;; 	2145 left AOP_LIT
;; gen.c:1390:mov2w_op *{*
; >>> gen.c:1405:mov2w_op
	.line	245; "spi.c"	sendCMD(0x21);
	MOVLW	0x21
; >>> gen.c:2184:genCall
	CALL	_sendCMD
;; gen.c:1825:unsaveRegisters *{*
;; ***	unsaveRegisters  1827
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:2096:genCall *{*
;; ***	genCall  2098
;; gen.c:1781:saveRegisters *{*
;; ***	saveRegisters  1783
;; 	2145 left AOP_LIT
;; gen.c:1390:mov2w_op *{*
; >>> gen.c:1405:mov2w_op
	.line	248; "spi.c"	sendCMD(0xBA);
	MOVLW	0xba
; >>> gen.c:2184:genCall
	CALL	_sendCMD
;; gen.c:1825:unsaveRegisters *{*
;; ***	unsaveRegisters  1827
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:2096:genCall *{*
;; ***	genCall  2098
;; gen.c:1781:saveRegisters *{*
;; ***	saveRegisters  1783
;; 	2145 left AOP_LIT
;; gen.c:1390:mov2w_op *{*
; >>> gen.c:1405:mov2w_op
	.line	251; "spi.c"	sendCMD(0x36);
	MOVLW	0x36
; >>> gen.c:2184:genCall
	CALL	_sendCMD
;; gen.c:1825:unsaveRegisters *{*
;; ***	unsaveRegisters  1827
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:2096:genCall *{*
;; ***	genCall  2098
;; gen.c:1781:saveRegisters *{*
;; ***	saveRegisters  1783
;; 	2145 left AOP_LIT
;; gen.c:1390:mov2w_op *{*
; >>> gen.c:1405:mov2w_op
	.line	254; "spi.c"	sendData(8|128);   //rgb + MirrorY
	MOVLW	0x88
; >>> gen.c:2184:genCall
	CALL	_sendData
;; gen.c:1825:unsaveRegisters *{*
;; ***	unsaveRegisters  1827
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:2096:genCall *{*
;; ***	genCall  2098
;; gen.c:1781:saveRegisters *{*
;; ***	saveRegisters  1783
;; 	2145 left AOP_LIT
;; gen.c:1390:mov2w_op *{*
; >>> gen.c:1405:mov2w_op
	.line	257; "spi.c"	sendCMD(0x3A);
	MOVLW	0x3a
; >>> gen.c:2184:genCall
	CALL	_sendCMD
;; gen.c:1825:unsaveRegisters *{*
;; ***	unsaveRegisters  1827
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:2096:genCall *{*
;; ***	genCall  2098
;; gen.c:1781:saveRegisters *{*
;; ***	saveRegisters  1783
;; 	2145 left AOP_LIT
;; gen.c:1390:mov2w_op *{*
; >>> gen.c:1405:mov2w_op
	.line	258; "spi.c"	sendData(3);   //12-Bit per Pixel (default)
	MOVLW	0x03
; >>> gen.c:2184:genCall
	CALL	_sendData
;; gen.c:1825:unsaveRegisters *{*
;; ***	unsaveRegisters  1827
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:2096:genCall *{*
;; ***	genCall  2098
;; gen.c:1781:saveRegisters *{*
;; ***	saveRegisters  1783
;; 	2145 left AOP_LIT
;; gen.c:1390:mov2w_op *{*
; >>> gen.c:1405:mov2w_op
	.line	261; "spi.c"	sendCMD(0x25);
	MOVLW	0x25
; >>> gen.c:2184:genCall
	CALL	_sendCMD
;; gen.c:1825:unsaveRegisters *{*
;; ***	unsaveRegisters  1827
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:2096:genCall *{*
;; ***	genCall  2098
;; gen.c:1781:saveRegisters *{*
;; ***	saveRegisters  1783
;; 	2145 left AOP_LIT
;; gen.c:1390:mov2w_op *{*
; >>> gen.c:1405:mov2w_op
	.line	262; "spi.c"	sendData(63);
	MOVLW	0x3f
; >>> gen.c:2184:genCall
	CALL	_sendData
;; gen.c:1825:unsaveRegisters *{*
;; ***	unsaveRegisters  1827
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:2096:genCall *{*
;; ***	genCall  2098
;; gen.c:1781:saveRegisters *{*
;; ***	saveRegisters  1783
;; 	2145 left AOP_LIT
;; gen.c:1390:mov2w_op *{*
; >>> gen.c:1405:mov2w_op
	.line	266; "spi.c"	sendCMD(0x2A);
	MOVLW	0x2a
; >>> gen.c:2184:genCall
	CALL	_sendCMD
;; gen.c:1825:unsaveRegisters *{*
;; ***	unsaveRegisters  1827
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:2096:genCall *{*
;; ***	genCall  2098
;; gen.c:1781:saveRegisters *{*
;; ***	saveRegisters  1783
;; 	2145 left AOP_LIT
;; gen.c:1390:mov2w_op *{*
; >>> gen.c:1405:mov2w_op
	.line	267; "spi.c"	sendData(0);
	MOVLW	0x00
; >>> gen.c:2184:genCall
	CALL	_sendData
;; gen.c:1825:unsaveRegisters *{*
;; ***	unsaveRegisters  1827
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:2096:genCall *{*
;; ***	genCall  2098
;; gen.c:1781:saveRegisters *{*
;; ***	saveRegisters  1783
;; 	2145 left AOP_LIT
;; gen.c:1390:mov2w_op *{*
; >>> gen.c:1405:mov2w_op
	.line	268; "spi.c"	sendData(131);
	MOVLW	0x83
; >>> gen.c:2184:genCall
	CALL	_sendData
;; gen.c:1825:unsaveRegisters *{*
;; ***	unsaveRegisters  1827
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:2096:genCall *{*
;; ***	genCall  2098
;; gen.c:1781:saveRegisters *{*
;; ***	saveRegisters  1783
;; 	2145 left AOP_LIT
;; gen.c:1390:mov2w_op *{*
; >>> gen.c:1405:mov2w_op
	.line	271; "spi.c"	sendCMD(0x2B);
	MOVLW	0x2b
; >>> gen.c:2184:genCall
	CALL	_sendCMD
;; gen.c:1825:unsaveRegisters *{*
;; ***	unsaveRegisters  1827
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:2096:genCall *{*
;; ***	genCall  2098
;; gen.c:1781:saveRegisters *{*
;; ***	saveRegisters  1783
;; 	2145 left AOP_LIT
;; gen.c:1390:mov2w_op *{*
; >>> gen.c:1405:mov2w_op
	.line	272; "spi.c"	sendData(0);
	MOVLW	0x00
; >>> gen.c:2184:genCall
	CALL	_sendData
;; gen.c:1825:unsaveRegisters *{*
;; ***	unsaveRegisters  1827
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:2096:genCall *{*
;; ***	genCall  2098
;; gen.c:1781:saveRegisters *{*
;; ***	saveRegisters  1783
;; 	2145 left AOP_LIT
;; gen.c:1390:mov2w_op *{*
; >>> gen.c:1405:mov2w_op
	.line	273; "spi.c"	sendData(131);
	MOVLW	0x83
; >>> gen.c:2184:genCall
	CALL	_sendData
;; gen.c:1825:unsaveRegisters *{*
;; ***	unsaveRegisters  1827
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:2096:genCall *{*
;; ***	genCall  2098
;; gen.c:1781:saveRegisters *{*
;; ***	saveRegisters  1783
;; 	2145 left AOP_LIT
;; gen.c:1390:mov2w_op *{*
; >>> gen.c:1405:mov2w_op
	.line	276; "spi.c"	sendCMD(0x2C);
	MOVLW	0x2c
; >>> gen.c:2184:genCall
	CALL	_sendCMD
;; gen.c:1825:unsaveRegisters *{*
;; ***	unsaveRegisters  1827
;; gen.c:2327:resultRemat *{*
;; gen.c:8139:genAssign *{*
;; ***	genAssign  8140
;;	769 register type nRegs=2
;; 	line = 8149 result AOP_REG=r0x1057, size=2, left -=-, size=0, right AOP_LIT=0x04, size=2
;; ***	genAssign  8241
; >>> gen.c:8246:genAssign
	.line	281; "spi.c"	for (i=0;i<132*33;i++) {
	MOVLW	0x04
; >>> gen.c:8248:genAssign
;;	1150 rIdx = r0x1057 
	BANKSEL	r0x1009
	MOVWF	r0x1009
;; ***	genAssign  8241
; >>> gen.c:8246:genAssign
	MOVLW	0x11
; >>> gen.c:8248:genAssign
;;	1150 rIdx = r0x1059 
	MOVWF	r0x100A
;; gen.c:2327:resultRemat *{*
;; gen.c:2686:genLabel *{*
;; ***	genLabel  2689
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:2096:genCall *{*
;; ***	genCall  2098
;; gen.c:1781:saveRegisters *{*
;; ***	saveRegisters  1783
;; 	2145 left AOP_LIT
;; gen.c:1390:mov2w_op *{*
; >>> gen.c:1405:mov2w_op
_00179_DS_
	.line	282; "spi.c"	setPixel(255,0,0);
	MOVLW	0x00
;; 	2145 left AOP_LIT
; >>> gen.c:2153:genCall
;; ***	popRegFromIdx,1066  , rIdx=0x7e
	MOVWF	STK01
;; gen.c:1390:mov2w_op *{*
; >>> gen.c:1405:mov2w_op
	MOVLW	0x00
;; 	2145 left AOP_LIT
; >>> gen.c:2153:genCall
;; ***	popRegFromIdx,1066  , rIdx=0x7f
	MOVWF	STK00
;; gen.c:1390:mov2w_op *{*
; >>> gen.c:1405:mov2w_op
	MOVLW	0xff
; >>> gen.c:2184:genCall
	CALL	_setPixel
;; gen.c:1825:unsaveRegisters *{*
;; ***	unsaveRegisters  1827
;; gen.c:2327:resultRemat *{*
;; gen.c:4410:ifxForOp *{*
;; ***	ifxForOp  4412
;; gen.c:8641:genDjnz *{*
;; ***	genDjnz  8642
;; genarith.c:1008:genMinus *{*
;; ***	genMinus  1009
;;	769 register type nRegs=2
;;	654
;; 	result AOP_REG, left AOP_REG, right AOP_LIT
;; ***	pic14_getDataSize  1492
;; ***	pic14_getDataSize  1492
;; genarith.c:399:genAddLit *{*
;; ***	genAddLit  400
;; ***	pic14_getDataSize  1492
;; ***	pic14_getDataSize  1492
;; hi = ff	genAddLit  471
; >>> genarith.c:488:genAddLit
	MOVLW	0xff
; >>> genarith.c:489:genAddLit
;;	1150 rIdx = r0x1057 
	BANKSEL	r0x1009
	ADDWF	r0x1009,F
; >>> genarith.c:490:genAddLit
	BTFSS	STATUS,0
; >>> genarith.c:491:genAddLit
;;	1150 rIdx = r0x1059 
	DECF	r0x100A,F
;; ***	pic14_getDataSize  1492
;; ***	pic14_getDataSize  1492
;; ***	pic14_getDataSize  1492
;; ***	addSign  973
;; genarith.c:974:addSign *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:7965:genIfx *{*
;; ***	genIfx  7966
;;	769 register type nRegs=2
;; ***	pic14_toBoolean  1566
; >>> gen.c:1575:pic14_toBoolean
;;	1150 rIdx = r0x1057 
	.line	281; "spi.c"	for (i=0;i<132*33;i++) {
	MOVF	r0x1009,W
; >>> gen.c:1580:pic14_toBoolean
;;	1150 rIdx = r0x1059 
	IORWF	r0x100A,W
; >>> gen.c:8011:genIfx
	BTFSS	STATUS,2
; >>> gen.c:8012:genIfx
;; ***	popGetLabel  key=6, label offset 73
	GOTO	_00179_DS_
;; gen.c:2327:resultRemat *{*
;; gen.c:8139:genAssign *{*
;; ***	genAssign  8140
;;	769 register type nRegs=2
;; 	line = 8149 result AOP_REG=r0x1057, size=2, left -=-, size=0, right AOP_LIT=0x04, size=2
;; ***	genAssign  8241
; >>> gen.c:8246:genAssign
	.line	286; "spi.c"	for (i=0;i<132*33;i++) {
	MOVLW	0x04
; >>> gen.c:8248:genAssign
;;	1150 rIdx = r0x1057 
	MOVWF	r0x1009
;; ***	genAssign  8241
; >>> gen.c:8246:genAssign
	MOVLW	0x11
; >>> gen.c:8248:genAssign
;;	1150 rIdx = r0x1059 
	MOVWF	r0x100A
;; gen.c:2327:resultRemat *{*
;; gen.c:2686:genLabel *{*
;; ***	genLabel  2689
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:2096:genCall *{*
;; ***	genCall  2098
;; gen.c:1781:saveRegisters *{*
;; ***	saveRegisters  1783
;; 	2145 left AOP_LIT
;; gen.c:1390:mov2w_op *{*
; >>> gen.c:1405:mov2w_op
_00182_DS_
	.line	287; "spi.c"	setPixel(0,255,0);
	MOVLW	0x00
;; 	2145 left AOP_LIT
; >>> gen.c:2153:genCall
;; ***	popRegFromIdx,1066  , rIdx=0x7e
	MOVWF	STK01
;; gen.c:1390:mov2w_op *{*
; >>> gen.c:1405:mov2w_op
	MOVLW	0xff
;; 	2145 left AOP_LIT
; >>> gen.c:2153:genCall
;; ***	popRegFromIdx,1066  , rIdx=0x7f
	MOVWF	STK00
;; gen.c:1390:mov2w_op *{*
; >>> gen.c:1405:mov2w_op
	MOVLW	0x00
; >>> gen.c:2184:genCall
	CALL	_setPixel
;; gen.c:1825:unsaveRegisters *{*
;; ***	unsaveRegisters  1827
;; gen.c:2327:resultRemat *{*
;; gen.c:4410:ifxForOp *{*
;; ***	ifxForOp  4412
;; gen.c:8641:genDjnz *{*
;; ***	genDjnz  8642
;; genarith.c:1008:genMinus *{*
;; ***	genMinus  1009
;;	769 register type nRegs=2
;;	654
;; 	result AOP_REG, left AOP_REG, right AOP_LIT
;; ***	pic14_getDataSize  1492
;; ***	pic14_getDataSize  1492
;; genarith.c:399:genAddLit *{*
;; ***	genAddLit  400
;; ***	pic14_getDataSize  1492
;; ***	pic14_getDataSize  1492
;; hi = ff	genAddLit  471
; >>> genarith.c:488:genAddLit
	MOVLW	0xff
; >>> genarith.c:489:genAddLit
;;	1150 rIdx = r0x1057 
	BANKSEL	r0x1009
	ADDWF	r0x1009,F
; >>> genarith.c:490:genAddLit
	BTFSS	STATUS,0
; >>> genarith.c:491:genAddLit
;;	1150 rIdx = r0x1059 
	DECF	r0x100A,F
;; ***	pic14_getDataSize  1492
;; ***	pic14_getDataSize  1492
;; ***	pic14_getDataSize  1492
;; ***	addSign  973
;; genarith.c:974:addSign *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:7965:genIfx *{*
;; ***	genIfx  7966
;;	769 register type nRegs=2
;; ***	pic14_toBoolean  1566
; >>> gen.c:1575:pic14_toBoolean
;;	1150 rIdx = r0x1057 
	.line	286; "spi.c"	for (i=0;i<132*33;i++) {
	MOVF	r0x1009,W
; >>> gen.c:1580:pic14_toBoolean
;;	1150 rIdx = r0x1059 
	IORWF	r0x100A,W
; >>> gen.c:8011:genIfx
	BTFSS	STATUS,2
; >>> gen.c:8012:genIfx
;; ***	popGetLabel  key=9, label offset 73
	GOTO	_00182_DS_
;; gen.c:2327:resultRemat *{*
;; gen.c:8139:genAssign *{*
;; ***	genAssign  8140
;;	769 register type nRegs=2
;; 	line = 8149 result AOP_REG=r0x1057, size=2, left -=-, size=0, right AOP_LIT=0x04, size=2
;; ***	genAssign  8241
; >>> gen.c:8246:genAssign
	.line	291; "spi.c"	for (i=0;i<132*33;i++) {
	MOVLW	0x04
; >>> gen.c:8248:genAssign
;;	1150 rIdx = r0x1057 
	MOVWF	r0x1009
;; ***	genAssign  8241
; >>> gen.c:8246:genAssign
	MOVLW	0x11
; >>> gen.c:8248:genAssign
;;	1150 rIdx = r0x1059 
	MOVWF	r0x100A
;; gen.c:2327:resultRemat *{*
;; gen.c:2686:genLabel *{*
;; ***	genLabel  2689
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:2096:genCall *{*
;; ***	genCall  2098
;; gen.c:1781:saveRegisters *{*
;; ***	saveRegisters  1783
;; 	2145 left AOP_LIT
;; gen.c:1390:mov2w_op *{*
; >>> gen.c:1405:mov2w_op
_00185_DS_
	.line	292; "spi.c"	setPixel(0,0,255);
	MOVLW	0xff
;; 	2145 left AOP_LIT
; >>> gen.c:2153:genCall
;; ***	popRegFromIdx,1066  , rIdx=0x7e
	MOVWF	STK01
;; gen.c:1390:mov2w_op *{*
; >>> gen.c:1405:mov2w_op
	MOVLW	0x00
;; 	2145 left AOP_LIT
; >>> gen.c:2153:genCall
;; ***	popRegFromIdx,1066  , rIdx=0x7f
	MOVWF	STK00
;; gen.c:1390:mov2w_op *{*
; >>> gen.c:1405:mov2w_op
	MOVLW	0x00
; >>> gen.c:2184:genCall
	CALL	_setPixel
;; gen.c:1825:unsaveRegisters *{*
;; ***	unsaveRegisters  1827
;; gen.c:2327:resultRemat *{*
;; gen.c:4410:ifxForOp *{*
;; ***	ifxForOp  4412
;; gen.c:8641:genDjnz *{*
;; ***	genDjnz  8642
;; genarith.c:1008:genMinus *{*
;; ***	genMinus  1009
;;	769 register type nRegs=2
;;	654
;; 	result AOP_REG, left AOP_REG, right AOP_LIT
;; ***	pic14_getDataSize  1492
;; ***	pic14_getDataSize  1492
;; genarith.c:399:genAddLit *{*
;; ***	genAddLit  400
;; ***	pic14_getDataSize  1492
;; ***	pic14_getDataSize  1492
;; hi = ff	genAddLit  471
; >>> genarith.c:488:genAddLit
	MOVLW	0xff
; >>> genarith.c:489:genAddLit
;;	1150 rIdx = r0x1057 
	BANKSEL	r0x1009
	ADDWF	r0x1009,F
; >>> genarith.c:490:genAddLit
	BTFSS	STATUS,0
; >>> genarith.c:491:genAddLit
;;	1150 rIdx = r0x1059 
	DECF	r0x100A,F
;; ***	pic14_getDataSize  1492
;; ***	pic14_getDataSize  1492
;; ***	pic14_getDataSize  1492
;; ***	addSign  973
;; genarith.c:974:addSign *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:7965:genIfx *{*
;; ***	genIfx  7966
;;	769 register type nRegs=2
;; ***	pic14_toBoolean  1566
; >>> gen.c:1575:pic14_toBoolean
;;	1150 rIdx = r0x1057 
	.line	291; "spi.c"	for (i=0;i<132*33;i++) {
	MOVF	r0x1009,W
; >>> gen.c:1580:pic14_toBoolean
;;	1150 rIdx = r0x1059 
	IORWF	r0x100A,W
; >>> gen.c:8011:genIfx
	BTFSS	STATUS,2
; >>> gen.c:8012:genIfx
;; ***	popGetLabel  key=12, label offset 73
	GOTO	_00185_DS_
;; gen.c:2327:resultRemat *{*
;; gen.c:8139:genAssign *{*
;; ***	genAssign  8140
;;	769 register type nRegs=2
;; 	line = 8149 result AOP_REG=r0x1057, size=2, left -=-, size=0, right AOP_LIT=0x04, size=2
;; ***	genAssign  8241
; >>> gen.c:8246:genAssign
	.line	296; "spi.c"	for (i=0;i<132*33;i++) {
	MOVLW	0x04
; >>> gen.c:8248:genAssign
;;	1150 rIdx = r0x1057 
	MOVWF	r0x1009
;; ***	genAssign  8241
; >>> gen.c:8246:genAssign
	MOVLW	0x11
; >>> gen.c:8248:genAssign
;;	1150 rIdx = r0x1059 
	MOVWF	r0x100A
;; gen.c:2327:resultRemat *{*
;; gen.c:2686:genLabel *{*
;; ***	genLabel  2689
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:2096:genCall *{*
;; ***	genCall  2098
;; gen.c:1781:saveRegisters *{*
;; ***	saveRegisters  1783
;; 	2145 left AOP_LIT
;; gen.c:1390:mov2w_op *{*
; >>> gen.c:1405:mov2w_op
_00188_DS_
	.line	297; "spi.c"	setPixel(255,255,255);
	MOVLW	0xff
;; 	2145 left AOP_LIT
; >>> gen.c:2153:genCall
;; ***	popRegFromIdx,1066  , rIdx=0x7e
	MOVWF	STK01
;; gen.c:1390:mov2w_op *{*
; >>> gen.c:1405:mov2w_op
	MOVLW	0xff
;; 	2145 left AOP_LIT
; >>> gen.c:2153:genCall
;; ***	popRegFromIdx,1066  , rIdx=0x7f
	MOVWF	STK00
;; gen.c:1390:mov2w_op *{*
; >>> gen.c:1405:mov2w_op
	MOVLW	0xff
; >>> gen.c:2184:genCall
	CALL	_setPixel
;; gen.c:1825:unsaveRegisters *{*
;; ***	unsaveRegisters  1827
;; gen.c:2327:resultRemat *{*
;; gen.c:4410:ifxForOp *{*
;; ***	ifxForOp  4412
;; gen.c:8641:genDjnz *{*
;; ***	genDjnz  8642
;; genarith.c:1008:genMinus *{*
;; ***	genMinus  1009
;;	769 register type nRegs=2
;;	654
;; 	result AOP_REG, left AOP_REG, right AOP_LIT
;; ***	pic14_getDataSize  1492
;; ***	pic14_getDataSize  1492
;; genarith.c:399:genAddLit *{*
;; ***	genAddLit  400
;; ***	pic14_getDataSize  1492
;; ***	pic14_getDataSize  1492
;; hi = ff	genAddLit  471
; >>> genarith.c:488:genAddLit
	MOVLW	0xff
; >>> genarith.c:489:genAddLit
;;	1150 rIdx = r0x1057 
	BANKSEL	r0x1009
	ADDWF	r0x1009,F
; >>> genarith.c:490:genAddLit
	BTFSS	STATUS,0
; >>> genarith.c:491:genAddLit
;;	1150 rIdx = r0x1059 
	DECF	r0x100A,F
;; ***	pic14_getDataSize  1492
;; ***	pic14_getDataSize  1492
;; ***	pic14_getDataSize  1492
;; ***	addSign  973
;; genarith.c:974:addSign *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:7965:genIfx *{*
;; ***	genIfx  7966
;;	769 register type nRegs=2
;; ***	pic14_toBoolean  1566
; >>> gen.c:1575:pic14_toBoolean
;;	1150 rIdx = r0x1057 
	.line	296; "spi.c"	for (i=0;i<132*33;i++) {
	MOVF	r0x1009,W
; >>> gen.c:1580:pic14_toBoolean
;;	1150 rIdx = r0x1059 
	IORWF	r0x100A,W
; >>> gen.c:8011:genIfx
	BTFSS	STATUS,2
; >>> gen.c:8012:genIfx
;; ***	popGetLabel  key=15, label offset 73
	GOTO	_00188_DS_
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:2096:genCall *{*
;; ***	genCall  2098
;; gen.c:1781:saveRegisters *{*
;; ***	saveRegisters  1783
;; 	2145 left AOP_LIT
;; gen.c:1390:mov2w_op *{*
; >>> gen.c:1405:mov2w_op
	.line	304; "spi.c"	putc('F');
	MOVLW	0x46
; >>> gen.c:2184:genCall
	CALL	_putc
;; gen.c:1825:unsaveRegisters *{*
;; ***	unsaveRegisters  1827
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:2096:genCall *{*
;; ***	genCall  2098
;; gen.c:1781:saveRegisters *{*
;; ***	saveRegisters  1783
;; 	2145 left AOP_LIT
;; gen.c:1390:mov2w_op *{*
; >>> gen.c:1405:mov2w_op
	.line	305; "spi.c"	putc('I');
	MOVLW	0x49
; >>> gen.c:2184:genCall
	CALL	_putc
;; gen.c:1825:unsaveRegisters *{*
;; ***	unsaveRegisters  1827
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:2096:genCall *{*
;; ***	genCall  2098
;; gen.c:1781:saveRegisters *{*
;; ***	saveRegisters  1783
;; 	2145 left AOP_LIT
;; gen.c:1390:mov2w_op *{*
; >>> gen.c:1405:mov2w_op
	.line	306; "spi.c"	putc('M');
	MOVLW	0x4d
; >>> gen.c:2184:genCall
	CALL	_putc
;; gen.c:1825:unsaveRegisters *{*
;; ***	unsaveRegisters  1827
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:2096:genCall *{*
;; ***	genCall  2098
;; gen.c:1781:saveRegisters *{*
;; ***	saveRegisters  1783
;; 	2145 left AOP_LIT
;; gen.c:1390:mov2w_op *{*
; >>> gen.c:1405:mov2w_op
	.line	307; "spi.c"	putc('\n');
	MOVLW	0x0a
; >>> gen.c:2184:genCall
	CALL	_putc
;; gen.c:1825:unsaveRegisters *{*
;; ***	unsaveRegisters  1827
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:2096:genCall *{*
;; ***	genCall  2098
;; gen.c:1781:saveRegisters *{*
;; ***	saveRegisters  1783
;; 	2145 left AOP_LIT
;; gen.c:1390:mov2w_op *{*
; >>> gen.c:1405:mov2w_op
	.line	308; "spi.c"	putc('\r');		
	MOVLW	0x0d
; >>> gen.c:2184:genCall
	CALL	_putc
;; gen.c:1825:unsaveRegisters *{*
;; ***	unsaveRegisters  1827
;; gen.c:2327:resultRemat *{*
;; gen.c:2686:genLabel *{*
;; ***	genLabel  2689
;; gen.c:2327:resultRemat *{*
;; gen.c:2096:genCall *{*
;; ***	genCall  2098
;; gen.c:1781:saveRegisters *{*
;; ***	saveRegisters  1783
; >>> gen.c:2184:genCall
_00175_DS_
	.line	319; "spi.c"	r = getc();
	CALL	_getc
;;	654
;; gen.c:1882:assignResultValue *{*
;; ***	assignResultValue  1884
;; 	line = 1886 result -=-, size=0, left AOP_DIR=_r, size=1, right -=-, size=0
; >>> gen.c:1433:movwf
;;	1036
;;	1052  _r   offset=0
	BANKSEL	_r
	MOVWF	_r
;; 	2204 left AOP_DIR
;; gen.c:1825:unsaveRegisters *{*
;; ***	unsaveRegisters  1827
;; gen.c:2327:resultRemat *{*
;; gen.c:2096:genCall *{*
;; ***	genCall  2098
;; gen.c:1781:saveRegisters *{*
;; ***	saveRegisters  1783
; >>> gen.c:2184:genCall
	.line	320; "spi.c"	g = getc();
	CALL	_getc
;; ***	aopForSym 393
;;	404 sym->rname = _g, size = 1
;; gen.c:1882:assignResultValue *{*
;; ***	assignResultValue  1884
;; 	line = 1886 result -=-, size=0, left AOP_DIR=_g, size=1, right -=-, size=0
; >>> gen.c:1433:movwf
;;	1036
;;	1052  _g   offset=0
	BANKSEL	_g
	MOVWF	_g
;; 	2204 left AOP_DIR
;; gen.c:1825:unsaveRegisters *{*
;; ***	unsaveRegisters  1827
;; gen.c:2327:resultRemat *{*
;; gen.c:2096:genCall *{*
;; ***	genCall  2098
;; gen.c:1781:saveRegisters *{*
;; ***	saveRegisters  1783
; >>> gen.c:2184:genCall
	.line	321; "spi.c"	b = getc();
	CALL	_getc
;;	654
;; gen.c:1882:assignResultValue *{*
;; ***	assignResultValue  1884
;; 	line = 1886 result -=-, size=0, left AOP_DIR=_b, size=1, right -=-, size=0
; >>> gen.c:1433:movwf
;;	1036
;;	1052  _b   offset=0
	BANKSEL	_b
	MOVWF	_b
;; 	2204 left AOP_DIR
;; gen.c:1825:unsaveRegisters *{*
;; ***	unsaveRegisters  1827
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:2096:genCall *{*
;; ***	genCall  2098
;; gen.c:1781:saveRegisters *{*
;; ***	saveRegisters  1783
;; ***	aopForSym 393
;;	404 sym->rname = _b, size = 1
;; ***	aopForSym 393
;;	404 sym->rname = _g, size = 1
;; ***	aopForSym 393
;;	404 sym->rname = _r, size = 1
;; ***	aopForSym 393
;;	404 sym->rname = _b, size = 1
;; 	2145 left AOP_DIR
;; gen.c:1390:mov2w_op *{*
;; ***	mov2w  1422  offset=0
; >>> gen.c:1427:mov2w
;;	1036
;;	1052  _b   offset=0
	.line	322; "spi.c"	setPixel(r,g,b);
	MOVF	_b,W
;; ***	aopForSym 393
;;	404 sym->rname = _g, size = 1
;; 	2145 left AOP_DIR
; >>> gen.c:2153:genCall
;; ***	popRegFromIdx,1066  , rIdx=0x7e
	MOVWF	STK01
;; gen.c:1390:mov2w_op *{*
;; ***	mov2w  1422  offset=0
; >>> gen.c:1427:mov2w
;;	1036
;;	1052  _g   offset=0
	BANKSEL	_g
	MOVF	_g,W
;; ***	aopForSym 393
;;	404 sym->rname = _r, size = 1
;; 	2145 left AOP_DIR
; >>> gen.c:2153:genCall
;; ***	popRegFromIdx,1066  , rIdx=0x7f
	MOVWF	STK00
;; gen.c:1390:mov2w_op *{*
;; ***	mov2w  1422  offset=0
; >>> gen.c:1427:mov2w
;;	1036
;;	1052  _r   offset=0
	BANKSEL	_r
	MOVF	_r,W
; >>> gen.c:2184:genCall
	CALL	_setPixel
;; gen.c:1825:unsaveRegisters *{*
;; ***	unsaveRegisters  1827
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:2096:genCall *{*
;; ***	genCall  2098
;; gen.c:1781:saveRegisters *{*
;; ***	saveRegisters  1783
;; 	2145 left AOP_LIT
;; gen.c:1390:mov2w_op *{*
; >>> gen.c:1405:mov2w_op
	.line	323; "spi.c"	putc('.');
	MOVLW	0x2e
; >>> gen.c:2184:genCall
	CALL	_putc
;; gen.c:1825:unsaveRegisters *{*
;; ***	unsaveRegisters  1827
;; gen.c:2327:resultRemat *{*
;; gen.c:2703:genGoto *{*
; >>> gen.c:2705:genGoto
;; ***	popGetLabel  key=2, label offset 73
	GOTO	_00175_DS_
;; gen.c:2327:resultRemat *{*
;; gen.c:2686:genLabel *{*
;; ***	genLabel  2689
;; gen.c:2327:resultRemat *{*
;; gen.c:2524:genEndFunction *{*
;; ***	genEndFunction  2526
	RETURN	
; exit point of _main

;***
;  pBlock Stats: dbName = C
;***
;entry:  _getc	;Function start
; 2 exit points
;has an exit
;; Starting pCode block
;; gen.c:2327:resultRemat *{*
;; gen.c:2686:genLabel *{*
;; ***	genLabel  2689
;; gen.c:2327:resultRemat *{*
;; gen.c:2372:genFunction *{*
;; ***	genFunction  2374 curr label offset=64previous max_key=0 
_getc	;Function start
; 2 exit points
;; gen.c:2327:resultRemat *{*
;; gen.c:2686:genLabel *{*
;; ***	genLabel  2689
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:7386:genPointerGet *{*
;; ***	genPointerGet  7387
;; gen.c:7175:genNearPointerGet *{*
;; ***	genNearPointerGet  7176
;;	689
;;	aopForRemat 474
;;	495: rname _PIR1_bits, val 0, const = 0
;; ***	genNearPointerGet  7192
;;	769 register type nRegs=1
;; gen.c:4410:ifxForOp *{*
;; ***	ifxForOp  4412
;; gen.c:7018:genUnpackBits *{*
;; ***	genUnpackBits  7019
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PIR1_bits
; >>> gen.c:7035:genUnpackBits
_00169_DS_
	.line	181; "spi.c"	while(!RCIF);	// Wait until data recieved
	BANKSEL	_PIR1_bits
	BTFSS	_PIR1_bits,5
; >>> gen.c:7036:genUnpackBits
;; ***	popGetLabel  key=1, label offset 68
	GOTO	_00169_DS_
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:2650:genRet *{*
;; ***	genRet  2652
;; ***	aopForSym 393
;;	404 sym->rname = _RCREG, size = 1
;; gen.c:1390:mov2w_op *{*
;; ***	mov2w  1422  offset=0
; >>> gen.c:1427:mov2w
;;	1036
;;	1050  _RCREG   offset=0 - had to alloc by reg name
	.line	182; "spi.c"	return RCREG;	// Store for later
	MOVF	_RCREG,W
;; gen.c:2327:resultRemat *{*
;; gen.c:2686:genLabel *{*
;; ***	genLabel  2689
;; gen.c:2327:resultRemat *{*
;; gen.c:2524:genEndFunction *{*
;; ***	genEndFunction  2526
	RETURN	
; exit point of _getc
;; gen.c:8749:genpic14Code *{*

;***
;  pBlock Stats: dbName = C
;***
;entry:  _putc	;Function start
; 2 exit points
;has an exit
;; Starting pCode block
;; gen.c:2327:resultRemat *{*
;; gen.c:2686:genLabel *{*
;; ***	genLabel  2689
;; gen.c:2327:resultRemat *{*
;; gen.c:2372:genFunction *{*
;; ***	genFunction  2374 curr label offset=56previous max_key=4 
_putc	;Function start
; 2 exit points
;; gen.c:2327:resultRemat *{*
;; gen.c:8685:genReceive *{*
;; ***	genReceive  8686
;; ***	aopForSym 393
;;	404 sym->rname = _TXREG, size = 1
;; gen.c:1882:assignResultValue *{*
;; ***	assignResultValue  1884
;; 	line = 1886 result -=-, size=0, left AOP_DIR=_TXREG, size=1, right -=-, size=0
; >>> gen.c:1433:movwf
;;	1036
;;	1052  _TXREG   offset=0
	.line	173; "spi.c"	void putc(unsigned char datax)
	BANKSEL	_TXREG
	MOVWF	_TXREG
;; gen.c:2327:resultRemat *{*
;; gen.c:2686:genLabel *{*
;; ***	genLabel  2689
;; gen.c:2327:resultRemat *{*
;; gen.c:2524:genEndFunction *{*
;; ***	genEndFunction  2526
	.line	176; "spi.c"	TXREG=datax;
	RETURN	
; exit point of _putc
;; gen.c:8749:genpic14Code *{*

;***
;  pBlock Stats: dbName = C
;***
;entry:  _setPixel	;Function start
; 2 exit points
;has an exit
;functions called:
;   _sendData
;   _sendData
;   _sendData
;   _sendData
;   _sendData
;   _sendData
;4 compiler assigned registers:
;   STK00
;   STK01
;   r0x100B
;   r0x100C
;; Starting pCode block
;; gen.c:2327:resultRemat *{*
;; gen.c:2686:genLabel *{*
;; ***	genLabel  2689
;; gen.c:2327:resultRemat *{*
;; gen.c:2372:genFunction *{*
;; ***	genFunction  2374 curr label offset=52previous max_key=0 
_setPixel	;Function start
; 2 exit points
;; gen.c:2327:resultRemat *{*
;; gen.c:8685:genReceive *{*
;; ***	genReceive  8686
;; ***	aopForSym 393
;;	404 sym->rname = _r, size = 1
;; gen.c:1882:assignResultValue *{*
;; ***	assignResultValue  1884
;; 	line = 1886 result -=-, size=0, left AOP_DIR=_r, size=1, right -=-, size=0
; >>> gen.c:1433:movwf
;;	1036
;;	1052  _r   offset=0
	.line	155; "spi.c"	void setPixel(byte r_,byte g_,byte b_) {
	BANKSEL	_r
	MOVWF	_r
;; gen.c:2327:resultRemat *{*
;; gen.c:8685:genReceive *{*
;; ***	genReceive  8686
;; ***	aopForSym 393
;;	404 sym->rname = _g, size = 1
;; gen.c:1882:assignResultValue *{*
;; ***	assignResultValue  1884
;; 	line = 1886 result -=-, size=0, left AOP_DIR=_g, size=1, right -=-, size=0
; >>> gen.c:1459:get_returnvalue
;; ***	popRegFromIdx,1066  , rIdx=0x7f
	MOVF	STK00,W
; >>> gen.c:1433:movwf
;;	1036
;;	1052  _g   offset=0
	BANKSEL	_g
	MOVWF	_g
;; gen.c:2327:resultRemat *{*
;; gen.c:8685:genReceive *{*
;; ***	genReceive  8686
;; ***	aopForSym 393
;;	404 sym->rname = _b, size = 1
;; gen.c:1882:assignResultValue *{*
;; ***	assignResultValue  1884
;; 	line = 1886 result -=-, size=0, left AOP_DIR=_b, size=1, right -=-, size=0
; >>> gen.c:1459:get_returnvalue
;; ***	popRegFromIdx,1066  , rIdx=0x7e
	MOVF	STK01,W
; >>> gen.c:1433:movwf
;;	1036
;;	1052  _b   offset=0
	BANKSEL	_b
	MOVWF	_b
;; gen.c:2327:resultRemat *{*
;; gen.c:7965:genIfx *{*
;; ***	genIfx  7966
;; ***	aopForSym 393
;;	404 sym->rname = _n, size = 1
;; ***	pic14_toBoolean  1566
; >>> gen.c:1572:pic14_toBoolean
	.line	161; "spi.c"	if (n==0) {
	MOVLW	0x00
; >>> gen.c:1580:pic14_toBoolean
;;	1036
;;	1052  _n   offset=0
	BANKSEL	_n
	IORWF	_n,W
; >>> gen.c:8011:genIfx
	BTFSS	STATUS,2
; >>> gen.c:8012:genIfx
;; ***	popGetLabel  key=2, label offset 56
	GOTO	_00158_DS_
;; gen.c:2327:resultRemat *{*
;; gen.c:4410:ifxForOp *{*
;; ***	ifxForOp  4412
;; NULL :(	4432
;; gen.c:4625:genAnd *{*
;; ***	genAnd  4626
;; ***	aopForSym 393
;;	404 sym->rname = _r, size = 1
;;	769 register type nRegs=1
;; 	line = 4660 result AOP_REG=r0x1055, size=1, left AOP_DIR=_r, size=1, right AOP_LIT=0xf0, size=1
; >>> gen.c:4858:genAnd
	.line	162; "spi.c"	s1=(r & 240) | (g>>4);
	MOVLW	0xf0
; >>> gen.c:4859:genAnd
;;	1036
;;	1052  _r   offset=0
	BANKSEL	_r
	ANDWF	_r,W
; >>> gen.c:4860:genAnd
;;	1150 rIdx = r0x1055 
	BANKSEL	r0x100B
	MOVWF	r0x100B
;; gen.c:2327:resultRemat *{*
;; gen.c:6767:genGenericShift *{*
;; ***	genGenericShift  6771
;; ***	aopForSym 393
;;	404 sym->rname = _g, size = 1
;;	769 register type nRegs=1
; >>> gen.c:6104:shiftRight_Left2ResultLit
;;	1036
;;	1052  _g   offset=0
	BANKSEL	_g
	SWAPF	_g,W
; >>> gen.c:6105:shiftRight_Left2ResultLit
	ANDLW	0x0f
; >>> gen.c:6106:shiftRight_Left2ResultLit
;;	1150 rIdx = r0x1056 
	BANKSEL	r0x100C
	MOVWF	r0x100C
	IORWF	r0x100B,W
; >>> gen.c:5114:genOr
;;	1036
;;	1052  _s1   offset=0
	BANKSEL	_s1
	MOVWF	_s1
;; gen.c:2327:resultRemat *{*
;; gen.c:4410:ifxForOp *{*
;; ***	ifxForOp  4412
;; gen.c:4625:genAnd *{*
;; ***	genAnd  4626
;; ***	aopForSym 393
;;	404 sym->rname = _b, size = 1
;; ***	aopForSym 393
;;	404 sym->rname = _s2, size = 1
;; 	line = 4660 result AOP_DIR=_s2, size=1, left AOP_DIR=_b, size=1, right AOP_LIT=0xf0, size=1
; >>> gen.c:4858:genAnd
	.line	163; "spi.c"	s2=(b & 240);
	MOVLW	0xf0
; >>> gen.c:4859:genAnd
;;	1036
;;	1052  _b   offset=0
	BANKSEL	_b
	ANDWF	_b,W
; >>> gen.c:4860:genAnd
;;	1036
;;	1052  _s2   offset=0
	BANKSEL	_s2
	MOVWF	_s2
;; gen.c:2327:resultRemat *{*
;; gen.c:8139:genAssign *{*
;; ***	genAssign  8140
;; ***	aopForSym 393
;;	404 sym->rname = _n, size = 1
;; 	line = 8149 result AOP_DIR=_n, size=1, left -=-, size=0, right AOP_LIT=0x01, size=1
;; ***	genAssign  8241
; >>> gen.c:8246:genAssign
	.line	164; "spi.c"	n=1;
	MOVLW	0x01
; >>> gen.c:8248:genAssign
;;	1036
;;	1052  _n   offset=0
	BANKSEL	_n
	MOVWF	_n
;; gen.c:2327:resultRemat *{*
;; gen.c:2703:genGoto *{*
; >>> gen.c:2705:genGoto
;; ***	popGetLabel  key=4, label offset 56
	GOTO	_00160_DS_
;; gen.c:2327:resultRemat *{*
;; gen.c:2686:genLabel *{*
;; ***	genLabel  2689
;; gen.c:2327:resultRemat *{*
;; gen.c:8139:genAssign *{*
;; ***	genAssign  8140
;; ***	aopForSym 393
;;	404 sym->rname = _n, size = 1
;; 	line = 8149 result AOP_DIR=_n, size=1, left -=-, size=0, right AOP_LIT=0x00, size=1
;; ***	genAssign  8241
; >>> gen.c:8250:genAssign
;;	1036
;;	1052  _n   offset=0
_00158_DS_
	.line	166; "spi.c"	n=0;
	BANKSEL	_n
	CLRF	_n
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:2096:genCall *{*
;; ***	genCall  2098
;; gen.c:1781:saveRegisters *{*
;; ***	saveRegisters  1783
;; ***	aopForSym 393
;;	404 sym->rname = _s1, size = 1
;; ***	aopForSym 393
;;	404 sym->rname = _s1, size = 1
;; 	2145 left AOP_DIR
;; gen.c:1390:mov2w_op *{*
;; ***	mov2w  1422  offset=0
; >>> gen.c:1427:mov2w
;;	1036
;;	1052  _s1   offset=0
	.line	167; "spi.c"	sendData(s1);
	BANKSEL	_s1
	MOVF	_s1,W
; >>> gen.c:2184:genCall
	CALL	_sendData
;; gen.c:1825:unsaveRegisters *{*
;; ***	unsaveRegisters  1827
;; gen.c:2327:resultRemat *{*
;; gen.c:6767:genGenericShift *{*
;; ***	genGenericShift  6771
;; ***	aopForSym 393
;;	404 sym->rname = _r, size = 1
;;	769 register type nRegs=1
; >>> gen.c:6104:shiftRight_Left2ResultLit
;;	1036
;;	1052  _r   offset=0
	.line	168; "spi.c"	sendData(s2|(r>>4));
	BANKSEL	_r
	SWAPF	_r,W
; >>> gen.c:6105:shiftRight_Left2ResultLit
	ANDLW	0x0f
; >>> gen.c:6106:shiftRight_Left2ResultLit
;;	1150 rIdx = r0x1055 
	BANKSEL	r0x100B
	MOVWF	r0x100B
;; ***	pic14_getDataSize  1492
;; ***	addSign  973
;; genarith.c:974:addSign *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:4410:ifxForOp *{*
;; ***	ifxForOp  4412
;; NULL :(	4432
;; gen.c:4887:genOr *{*
;; ***	genOr  4888
;; ***	aopForSym 393
;;	404 sym->rname = _s2, size = 1
;;	769 register type nRegs=1
;; 	line = 4894 result AOP_REG=r0x1055, size=1, left AOP_DIR=_s2, size=1, right AOP_REG=r0x1055, size=1
;; 	line = 4919 result AOP_REG=r0x1055, size=1, left AOP_REG=r0x1055, size=1, right AOP_DIR=_s2, size=1
; >>> gen.c:5061:genOr
;;	1036
;;	1052  _s2   offset=0
	BANKSEL	_s2
	MOVF	_s2,W
; >>> gen.c:5062:genOr
;;	1150 rIdx = r0x1055 
	BANKSEL	r0x100B
	IORWF	r0x100B,F
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:2096:genCall *{*
;; ***	genCall  2098
;; gen.c:1781:saveRegisters *{*
;; ***	saveRegisters  1783
;;	769 register type nRegs=1
;;	769 register type nRegs=1
;; 	2145 left AOP_REG
;; gen.c:1390:mov2w_op *{*
;; ***	mov2w  1422  offset=0
; >>> gen.c:1427:mov2w
;;	1150 rIdx = r0x1055 
	MOVF	r0x100B,W
; >>> gen.c:2184:genCall
	CALL	_sendData
;; gen.c:1825:unsaveRegisters *{*
;; ***	unsaveRegisters  1827
;; gen.c:2327:resultRemat *{*
;; gen.c:4410:ifxForOp *{*
;; ***	ifxForOp  4412
;; NULL :(	4432
;; gen.c:4625:genAnd *{*
;; ***	genAnd  4626
;;	654
;;	769 register type nRegs=1
;; 	line = 4660 result AOP_REG=r0x1055, size=1, left AOP_DIR=_g, size=1, right AOP_LIT=0xf0, size=1
; >>> gen.c:4858:genAnd
	.line	169; "spi.c"	sendData((g&240) | (b>>4));
	MOVLW	0xf0
; >>> gen.c:4859:genAnd
;;	1036
;;	1052  _g   offset=0
	BANKSEL	_g
	ANDWF	_g,W
; >>> gen.c:4860:genAnd
;;	1150 rIdx = r0x1055 
	BANKSEL	r0x100B
	MOVWF	r0x100B
;; gen.c:2327:resultRemat *{*
;; gen.c:6767:genGenericShift *{*
;; ***	genGenericShift  6771
;; ***	aopForSym 393
;;	404 sym->rname = _b, size = 1
;;	769 register type nRegs=1
; >>> gen.c:6104:shiftRight_Left2ResultLit
;;	1036
;;	1052  _b   offset=0
	BANKSEL	_b
	SWAPF	_b,W
; >>> gen.c:6105:shiftRight_Left2ResultLit
	ANDLW	0x0f
; >>> gen.c:6106:shiftRight_Left2ResultLit
;;	1150 rIdx = r0x1056 
	BANKSEL	r0x100C
	MOVWF	r0x100C
	IORWF	r0x100B,F
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:2096:genCall *{*
;; ***	genCall  2098
;; gen.c:1781:saveRegisters *{*
;; ***	saveRegisters  1783
;;	769 register type nRegs=1
;;	769 register type nRegs=1
;; 	2145 left AOP_REG
;; gen.c:1390:mov2w_op *{*
;; ***	mov2w  1422  offset=0
; >>> gen.c:1427:mov2w
;;	1150 rIdx = r0x1055 
	MOVF	r0x100B,W
; >>> gen.c:2184:genCall
	CALL	_sendData
;; gen.c:1825:unsaveRegisters *{*
;; ***	unsaveRegisters  1827
;; gen.c:2327:resultRemat *{*
;; gen.c:2686:genLabel *{*
;; ***	genLabel  2689
;; gen.c:2327:resultRemat *{*
;; gen.c:2524:genEndFunction *{*
;; ***	genEndFunction  2526
_00160_DS_
	RETURN	
; exit point of _setPixel
;; gen.c:8749:genpic14Code *{*

;***
;  pBlock Stats: dbName = C
;***
;entry:  _sendData	;Function start
; 2 exit points
;has an exit
;functions called:
;   _shiftBits
;   _shiftBits
;1 compiler assigned register :
;   r0x100B
;; Starting pCode block
;; gen.c:2327:resultRemat *{*
;; gen.c:2686:genLabel *{*
;; ***	genLabel  2689
;; gen.c:2327:resultRemat *{*
;; gen.c:2372:genFunction *{*
;; ***	genFunction  2374 curr label offset=24previous max_key=24 
_sendData	;Function start
; 2 exit points
;; gen.c:2327:resultRemat *{*
;; gen.c:8685:genReceive *{*
;; ***	genReceive  8686
;;	769 register type nRegs=1
;; gen.c:1882:assignResultValue *{*
;; ***	assignResultValue  1884
;; 	line = 1886 result -=-, size=0, left AOP_REG=r0x104E, size=1, right -=-, size=0
; >>> gen.c:1433:movwf
;;	1150 rIdx = r0x104E 
	.line	145; "spi.c"	void sendData(byte datax) {
	BANKSEL	r0x100B
	MOVWF	r0x100B
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:7895:genPointerSet *{*
;; ***	genPointerSet  7896
;; gen.c:7723:genNearPointerSet *{*
;; ***	genNearPointerSet  7724
;;	689
;;	aopForRemat 474
;;	495: rname _PORTB_bits, val 0, const = 0
;; ***	genNearPointerSet  7741
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
;; 	line = 7743 result AOP_PCODE=_PORTB_bits, size=2, left -=-, size=0, right AOP_LIT=0x00, size=1
;; gen.c:7472:genPackBits *{*
;; ***	genPackBits  7473
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
; >>> gen.c:7498:genPackBits
	.line	147; "spi.c"	CLK0
	BANKSEL	_PORTB_bits
	BCF	_PORTB_bits,7
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:7895:genPointerSet *{*
;; ***	genPointerSet  7896
;; gen.c:7723:genNearPointerSet *{*
;; ***	genNearPointerSet  7724
;;	689
;;	aopForRemat 474
;;	495: rname _PORTB_bits, val 0, const = 0
;; ***	genNearPointerSet  7741
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
;; 	line = 7743 result AOP_PCODE=_PORTB_bits, size=2, left -=-, size=0, right AOP_LIT=0x01, size=1
;; gen.c:7472:genPackBits *{*
;; ***	genPackBits  7473
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
; >>> gen.c:7498:genPackBits
	.line	148; "spi.c"	SDA1                                                 //1 for param
	BSF	_PORTB_bits,6
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:7895:genPointerSet *{*
;; ***	genPointerSet  7896
;; gen.c:7723:genNearPointerSet *{*
;; ***	genNearPointerSet  7724
;;	689
;;	aopForRemat 474
;;	495: rname _PORTB_bits, val 0, const = 0
;; ***	genNearPointerSet  7741
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
;; 	line = 7743 result AOP_PCODE=_PORTB_bits, size=2, left -=-, size=0, right AOP_LIT=0x01, size=1
;; gen.c:7472:genPackBits *{*
;; ***	genPackBits  7473
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
; >>> gen.c:7498:genPackBits
	.line	149; "spi.c"	CLK1
	BSF	_PORTB_bits,7
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:2096:genCall *{*
;; ***	genCall  2098
;; gen.c:1781:saveRegisters *{*
;; ***	saveRegisters  1783
;;	769 register type nRegs=1
;;	769 register type nRegs=1
;; 	2145 left AOP_REG
;; gen.c:1390:mov2w_op *{*
;; ***	mov2w  1422  offset=0
; >>> gen.c:1427:mov2w
;;	1150 rIdx = r0x104E 
	.line	151; "spi.c"	shiftBits(datax);
	BANKSEL	r0x100B
	MOVF	r0x100B,W
; >>> gen.c:2184:genCall
	CALL	_shiftBits
;; gen.c:1825:unsaveRegisters *{*
;; ***	unsaveRegisters  1827
;; gen.c:2327:resultRemat *{*
;; gen.c:2686:genLabel *{*
;; ***	genLabel  2689
;; gen.c:2327:resultRemat *{*
;; gen.c:2524:genEndFunction *{*
;; ***	genEndFunction  2526
	RETURN	
; exit point of _sendData
;; gen.c:8749:genpic14Code *{*

;***
;  pBlock Stats: dbName = C
;***
;entry:  _shiftBits	;Function start
; 2 exit points
;has an exit
;1 compiler assigned register :
;   r0x100C
;; Starting pCode block
;; gen.c:2327:resultRemat *{*
;; gen.c:2686:genLabel *{*
;; ***	genLabel  2689
;; gen.c:2327:resultRemat *{*
;; gen.c:2372:genFunction *{*
;; ***	genFunction  2374 curr label offset=20previous max_key=0 
_shiftBits	;Function start
; 2 exit points
;; gen.c:2327:resultRemat *{*
;; gen.c:8685:genReceive *{*
;; ***	genReceive  8686
;;	769 register type nRegs=1
;; gen.c:1882:assignResultValue *{*
;; ***	assignResultValue  1884
;; 	line = 1886 result -=-, size=0, left AOP_REG=r0x104D, size=1, right -=-, size=0
; >>> gen.c:1433:movwf
;;	1150 rIdx = r0x104D 
	.line	110; "spi.c"	void shiftBits(byte b) {
	BANKSEL	r0x100C
	MOVWF	r0x100C
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:7895:genPointerSet *{*
;; ***	genPointerSet  7896
;; gen.c:7723:genNearPointerSet *{*
;; ***	genNearPointerSet  7724
;;	689
;;	aopForRemat 474
;;	495: rname _PORTB_bits, val 0, const = 0
;; ***	genNearPointerSet  7741
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
;; 	line = 7743 result AOP_PCODE=_PORTB_bits, size=2, left -=-, size=0, right AOP_LIT=0x00, size=1
;; gen.c:7472:genPackBits *{*
;; ***	genPackBits  7473
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
; >>> gen.c:7498:genPackBits
	.line	112; "spi.c"	CLK0
	BANKSEL	_PORTB_bits
	BCF	_PORTB_bits,7
;; gen.c:2327:resultRemat *{*
;; gen.c:4410:ifxForOp *{*
;; ***	ifxForOp  4412
;; gen.c:4625:genAnd *{*
;; ***	genAnd  4626
;;	769 register type nRegs=1
;; 	line = 4660 result AOP_CRY=0x00, size=0, left AOP_REG=r0x104D, size=1, right AOP_LIT=0x80, size=1
;; gen.c:4552:isLiteralBit *{*
;; ***	isLiteralBit  4553
; >>> gen.c:4729:genAnd
	.line	113; "spi.c"	if ((b&128)!=0) SDA1 else SDA0
	BANKSEL	r0x100C
	BTFSS	r0x100C,7
; >>> gen.c:4730:genAnd
;; ***	popGetLabel  key=2, label offset 24
	GOTO	_00126_DS_
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:7895:genPointerSet *{*
;; ***	genPointerSet  7896
;; gen.c:7723:genNearPointerSet *{*
;; ***	genNearPointerSet  7724
;;	689
;;	aopForRemat 474
;;	495: rname _PORTB_bits, val 0, const = 0
;; ***	genNearPointerSet  7741
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
;; 	line = 7743 result AOP_PCODE=_PORTB_bits, size=2, left -=-, size=0, right AOP_LIT=0x01, size=1
;; gen.c:7472:genPackBits *{*
;; ***	genPackBits  7473
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
; >>> gen.c:7498:genPackBits
	BANKSEL	_PORTB_bits
	BSF	_PORTB_bits,6
;; gen.c:2327:resultRemat *{*
;; gen.c:2703:genGoto *{*
; >>> gen.c:2705:genGoto
;; ***	popGetLabel  key=3, label offset 24
	GOTO	_00127_DS_
;; gen.c:2327:resultRemat *{*
;; gen.c:2686:genLabel *{*
;; ***	genLabel  2689
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:7895:genPointerSet *{*
;; ***	genPointerSet  7896
;; gen.c:7723:genNearPointerSet *{*
;; ***	genNearPointerSet  7724
;;	689
;;	aopForRemat 474
;;	495: rname _PORTB_bits, val 0, const = 0
;; ***	genNearPointerSet  7741
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
;; 	line = 7743 result AOP_PCODE=_PORTB_bits, size=2, left -=-, size=0, right AOP_LIT=0x00, size=1
;; gen.c:7472:genPackBits *{*
;; ***	genPackBits  7473
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
; >>> gen.c:7498:genPackBits
_00126_DS_
	BANKSEL	_PORTB_bits
	BCF	_PORTB_bits,6
;; gen.c:2327:resultRemat *{*
;; gen.c:2686:genLabel *{*
;; ***	genLabel  2689
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:7895:genPointerSet *{*
;; ***	genPointerSet  7896
;; gen.c:7723:genNearPointerSet *{*
;; ***	genNearPointerSet  7724
;;	689
;;	aopForRemat 474
;;	495: rname _PORTB_bits, val 0, const = 0
;; ***	genNearPointerSet  7741
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
;; 	line = 7743 result AOP_PCODE=_PORTB_bits, size=2, left -=-, size=0, right AOP_LIT=0x01, size=1
;; gen.c:7472:genPackBits *{*
;; ***	genPackBits  7473
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
; >>> gen.c:7498:genPackBits
_00127_DS_
	.line	114; "spi.c"	CLK1
	BANKSEL	_PORTB_bits
	BSF	_PORTB_bits,7
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:7895:genPointerSet *{*
;; ***	genPointerSet  7896
;; gen.c:7723:genNearPointerSet *{*
;; ***	genNearPointerSet  7724
;;	689
;;	aopForRemat 474
;;	495: rname _PORTB_bits, val 0, const = 0
;; ***	genNearPointerSet  7741
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
;; 	line = 7743 result AOP_PCODE=_PORTB_bits, size=2, left -=-, size=0, right AOP_LIT=0x00, size=1
;; gen.c:7472:genPackBits *{*
;; ***	genPackBits  7473
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
; >>> gen.c:7498:genPackBits
	.line	116; "spi.c"	CLK0
	BCF	_PORTB_bits,7
;; gen.c:2327:resultRemat *{*
;; gen.c:4410:ifxForOp *{*
;; ***	ifxForOp  4412
;; gen.c:4625:genAnd *{*
;; ***	genAnd  4626
;;	769 register type nRegs=1
;; 	line = 4660 result AOP_CRY=0x00, size=0, left AOP_REG=r0x104D, size=1, right AOP_LIT=0x40, size=1
;; gen.c:4552:isLiteralBit *{*
;; ***	isLiteralBit  4553
; >>> gen.c:4729:genAnd
	.line	117; "spi.c"	if ((b&64)!=0) SDA1 else SDA0
	BANKSEL	r0x100C
	BTFSS	r0x100C,6
; >>> gen.c:4730:genAnd
;; ***	popGetLabel  key=5, label offset 24
	GOTO	_00129_DS_
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:7895:genPointerSet *{*
;; ***	genPointerSet  7896
;; gen.c:7723:genNearPointerSet *{*
;; ***	genNearPointerSet  7724
;;	689
;;	aopForRemat 474
;;	495: rname _PORTB_bits, val 0, const = 0
;; ***	genNearPointerSet  7741
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
;; 	line = 7743 result AOP_PCODE=_PORTB_bits, size=2, left -=-, size=0, right AOP_LIT=0x01, size=1
;; gen.c:7472:genPackBits *{*
;; ***	genPackBits  7473
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
; >>> gen.c:7498:genPackBits
	BANKSEL	_PORTB_bits
	BSF	_PORTB_bits,6
;; gen.c:2327:resultRemat *{*
;; gen.c:2703:genGoto *{*
; >>> gen.c:2705:genGoto
;; ***	popGetLabel  key=6, label offset 24
	GOTO	_00130_DS_
;; gen.c:2327:resultRemat *{*
;; gen.c:2686:genLabel *{*
;; ***	genLabel  2689
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:7895:genPointerSet *{*
;; ***	genPointerSet  7896
;; gen.c:7723:genNearPointerSet *{*
;; ***	genNearPointerSet  7724
;;	689
;;	aopForRemat 474
;;	495: rname _PORTB_bits, val 0, const = 0
;; ***	genNearPointerSet  7741
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
;; 	line = 7743 result AOP_PCODE=_PORTB_bits, size=2, left -=-, size=0, right AOP_LIT=0x00, size=1
;; gen.c:7472:genPackBits *{*
;; ***	genPackBits  7473
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
; >>> gen.c:7498:genPackBits
_00129_DS_
	BANKSEL	_PORTB_bits
	BCF	_PORTB_bits,6
;; gen.c:2327:resultRemat *{*
;; gen.c:2686:genLabel *{*
;; ***	genLabel  2689
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:7895:genPointerSet *{*
;; ***	genPointerSet  7896
;; gen.c:7723:genNearPointerSet *{*
;; ***	genNearPointerSet  7724
;;	689
;;	aopForRemat 474
;;	495: rname _PORTB_bits, val 0, const = 0
;; ***	genNearPointerSet  7741
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
;; 	line = 7743 result AOP_PCODE=_PORTB_bits, size=2, left -=-, size=0, right AOP_LIT=0x01, size=1
;; gen.c:7472:genPackBits *{*
;; ***	genPackBits  7473
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
; >>> gen.c:7498:genPackBits
_00130_DS_
	.line	118; "spi.c"	CLK1
	BANKSEL	_PORTB_bits
	BSF	_PORTB_bits,7
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:7895:genPointerSet *{*
;; ***	genPointerSet  7896
;; gen.c:7723:genNearPointerSet *{*
;; ***	genNearPointerSet  7724
;;	689
;;	aopForRemat 474
;;	495: rname _PORTB_bits, val 0, const = 0
;; ***	genNearPointerSet  7741
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
;; 	line = 7743 result AOP_PCODE=_PORTB_bits, size=2, left -=-, size=0, right AOP_LIT=0x00, size=1
;; gen.c:7472:genPackBits *{*
;; ***	genPackBits  7473
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
; >>> gen.c:7498:genPackBits
	.line	120; "spi.c"	CLK0
	BCF	_PORTB_bits,7
;; gen.c:2327:resultRemat *{*
;; gen.c:4410:ifxForOp *{*
;; ***	ifxForOp  4412
;; gen.c:4625:genAnd *{*
;; ***	genAnd  4626
;;	769 register type nRegs=1
;; 	line = 4660 result AOP_CRY=0x00, size=0, left AOP_REG=r0x104D, size=1, right AOP_LIT=0x20, size=1
;; gen.c:4552:isLiteralBit *{*
;; ***	isLiteralBit  4553
; >>> gen.c:4729:genAnd
	.line	121; "spi.c"	if ((b&32)!=0) SDA1 else SDA0
	BANKSEL	r0x100C
	BTFSS	r0x100C,5
; >>> gen.c:4730:genAnd
;; ***	popGetLabel  key=8, label offset 24
	GOTO	_00132_DS_
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:7895:genPointerSet *{*
;; ***	genPointerSet  7896
;; gen.c:7723:genNearPointerSet *{*
;; ***	genNearPointerSet  7724
;;	689
;;	aopForRemat 474
;;	495: rname _PORTB_bits, val 0, const = 0
;; ***	genNearPointerSet  7741
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
;; 	line = 7743 result AOP_PCODE=_PORTB_bits, size=2, left -=-, size=0, right AOP_LIT=0x01, size=1
;; gen.c:7472:genPackBits *{*
;; ***	genPackBits  7473
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
; >>> gen.c:7498:genPackBits
	BANKSEL	_PORTB_bits
	BSF	_PORTB_bits,6
;; gen.c:2327:resultRemat *{*
;; gen.c:2703:genGoto *{*
; >>> gen.c:2705:genGoto
;; ***	popGetLabel  key=9, label offset 24
	GOTO	_00133_DS_
;; gen.c:2327:resultRemat *{*
;; gen.c:2686:genLabel *{*
;; ***	genLabel  2689
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:7895:genPointerSet *{*
;; ***	genPointerSet  7896
;; gen.c:7723:genNearPointerSet *{*
;; ***	genNearPointerSet  7724
;;	689
;;	aopForRemat 474
;;	495: rname _PORTB_bits, val 0, const = 0
;; ***	genNearPointerSet  7741
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
;; 	line = 7743 result AOP_PCODE=_PORTB_bits, size=2, left -=-, size=0, right AOP_LIT=0x00, size=1
;; gen.c:7472:genPackBits *{*
;; ***	genPackBits  7473
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
; >>> gen.c:7498:genPackBits
_00132_DS_
	BANKSEL	_PORTB_bits
	BCF	_PORTB_bits,6
;; gen.c:2327:resultRemat *{*
;; gen.c:2686:genLabel *{*
;; ***	genLabel  2689
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:7895:genPointerSet *{*
;; ***	genPointerSet  7896
;; gen.c:7723:genNearPointerSet *{*
;; ***	genNearPointerSet  7724
;;	689
;;	aopForRemat 474
;;	495: rname _PORTB_bits, val 0, const = 0
;; ***	genNearPointerSet  7741
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
;; 	line = 7743 result AOP_PCODE=_PORTB_bits, size=2, left -=-, size=0, right AOP_LIT=0x01, size=1
;; gen.c:7472:genPackBits *{*
;; ***	genPackBits  7473
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
; >>> gen.c:7498:genPackBits
_00133_DS_
	.line	122; "spi.c"	CLK1
	BANKSEL	_PORTB_bits
	BSF	_PORTB_bits,7
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:7895:genPointerSet *{*
;; ***	genPointerSet  7896
;; gen.c:7723:genNearPointerSet *{*
;; ***	genNearPointerSet  7724
;;	689
;;	aopForRemat 474
;;	495: rname _PORTB_bits, val 0, const = 0
;; ***	genNearPointerSet  7741
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
;; 	line = 7743 result AOP_PCODE=_PORTB_bits, size=2, left -=-, size=0, right AOP_LIT=0x00, size=1
;; gen.c:7472:genPackBits *{*
;; ***	genPackBits  7473
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
; >>> gen.c:7498:genPackBits
	.line	124; "spi.c"	CLK0
	BCF	_PORTB_bits,7
;; gen.c:2327:resultRemat *{*
;; gen.c:4410:ifxForOp *{*
;; ***	ifxForOp  4412
;; gen.c:4625:genAnd *{*
;; ***	genAnd  4626
;;	769 register type nRegs=1
;; 	line = 4660 result AOP_CRY=0x00, size=0, left AOP_REG=r0x104D, size=1, right AOP_LIT=0x10, size=1
;; gen.c:4552:isLiteralBit *{*
;; ***	isLiteralBit  4553
; >>> gen.c:4729:genAnd
	.line	125; "spi.c"	if ((b&16)!=0) SDA1 else SDA0
	BANKSEL	r0x100C
	BTFSS	r0x100C,4
; >>> gen.c:4730:genAnd
;; ***	popGetLabel  key=11, label offset 24
	GOTO	_00135_DS_
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:7895:genPointerSet *{*
;; ***	genPointerSet  7896
;; gen.c:7723:genNearPointerSet *{*
;; ***	genNearPointerSet  7724
;;	689
;;	aopForRemat 474
;;	495: rname _PORTB_bits, val 0, const = 0
;; ***	genNearPointerSet  7741
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
;; 	line = 7743 result AOP_PCODE=_PORTB_bits, size=2, left -=-, size=0, right AOP_LIT=0x01, size=1
;; gen.c:7472:genPackBits *{*
;; ***	genPackBits  7473
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
; >>> gen.c:7498:genPackBits
	BANKSEL	_PORTB_bits
	BSF	_PORTB_bits,6
;; gen.c:2327:resultRemat *{*
;; gen.c:2703:genGoto *{*
; >>> gen.c:2705:genGoto
;; ***	popGetLabel  key=12, label offset 24
	GOTO	_00136_DS_
;; gen.c:2327:resultRemat *{*
;; gen.c:2686:genLabel *{*
;; ***	genLabel  2689
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:7895:genPointerSet *{*
;; ***	genPointerSet  7896
;; gen.c:7723:genNearPointerSet *{*
;; ***	genNearPointerSet  7724
;;	689
;;	aopForRemat 474
;;	495: rname _PORTB_bits, val 0, const = 0
;; ***	genNearPointerSet  7741
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
;; 	line = 7743 result AOP_PCODE=_PORTB_bits, size=2, left -=-, size=0, right AOP_LIT=0x00, size=1
;; gen.c:7472:genPackBits *{*
;; ***	genPackBits  7473
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
; >>> gen.c:7498:genPackBits
_00135_DS_
	BANKSEL	_PORTB_bits
	BCF	_PORTB_bits,6
;; gen.c:2327:resultRemat *{*
;; gen.c:2686:genLabel *{*
;; ***	genLabel  2689
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:7895:genPointerSet *{*
;; ***	genPointerSet  7896
;; gen.c:7723:genNearPointerSet *{*
;; ***	genNearPointerSet  7724
;;	689
;;	aopForRemat 474
;;	495: rname _PORTB_bits, val 0, const = 0
;; ***	genNearPointerSet  7741
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
;; 	line = 7743 result AOP_PCODE=_PORTB_bits, size=2, left -=-, size=0, right AOP_LIT=0x01, size=1
;; gen.c:7472:genPackBits *{*
;; ***	genPackBits  7473
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
; >>> gen.c:7498:genPackBits
_00136_DS_
	.line	126; "spi.c"	CLK1
	BANKSEL	_PORTB_bits
	BSF	_PORTB_bits,7
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:7895:genPointerSet *{*
;; ***	genPointerSet  7896
;; gen.c:7723:genNearPointerSet *{*
;; ***	genNearPointerSet  7724
;;	689
;;	aopForRemat 474
;;	495: rname _PORTB_bits, val 0, const = 0
;; ***	genNearPointerSet  7741
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
;; 	line = 7743 result AOP_PCODE=_PORTB_bits, size=2, left -=-, size=0, right AOP_LIT=0x00, size=1
;; gen.c:7472:genPackBits *{*
;; ***	genPackBits  7473
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
; >>> gen.c:7498:genPackBits
	.line	128; "spi.c"	CLK0
	BCF	_PORTB_bits,7
;; gen.c:2327:resultRemat *{*
;; gen.c:4410:ifxForOp *{*
;; ***	ifxForOp  4412
;; gen.c:4625:genAnd *{*
;; ***	genAnd  4626
;;	769 register type nRegs=1
;; 	line = 4660 result AOP_CRY=0x00, size=0, left AOP_REG=r0x104D, size=1, right AOP_LIT=0x08, size=1
;; gen.c:4552:isLiteralBit *{*
;; ***	isLiteralBit  4553
; >>> gen.c:4729:genAnd
	.line	129; "spi.c"	if ((b&8)!=0) SDA1 else SDA0
	BANKSEL	r0x100C
	BTFSS	r0x100C,3
; >>> gen.c:4730:genAnd
;; ***	popGetLabel  key=14, label offset 24
	GOTO	_00138_DS_
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:7895:genPointerSet *{*
;; ***	genPointerSet  7896
;; gen.c:7723:genNearPointerSet *{*
;; ***	genNearPointerSet  7724
;;	689
;;	aopForRemat 474
;;	495: rname _PORTB_bits, val 0, const = 0
;; ***	genNearPointerSet  7741
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
;; 	line = 7743 result AOP_PCODE=_PORTB_bits, size=2, left -=-, size=0, right AOP_LIT=0x01, size=1
;; gen.c:7472:genPackBits *{*
;; ***	genPackBits  7473
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
; >>> gen.c:7498:genPackBits
	BANKSEL	_PORTB_bits
	BSF	_PORTB_bits,6
;; gen.c:2327:resultRemat *{*
;; gen.c:2703:genGoto *{*
; >>> gen.c:2705:genGoto
;; ***	popGetLabel  key=15, label offset 24
	GOTO	_00139_DS_
;; gen.c:2327:resultRemat *{*
;; gen.c:2686:genLabel *{*
;; ***	genLabel  2689
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:7895:genPointerSet *{*
;; ***	genPointerSet  7896
;; gen.c:7723:genNearPointerSet *{*
;; ***	genNearPointerSet  7724
;;	689
;;	aopForRemat 474
;;	495: rname _PORTB_bits, val 0, const = 0
;; ***	genNearPointerSet  7741
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
;; 	line = 7743 result AOP_PCODE=_PORTB_bits, size=2, left -=-, size=0, right AOP_LIT=0x00, size=1
;; gen.c:7472:genPackBits *{*
;; ***	genPackBits  7473
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
; >>> gen.c:7498:genPackBits
_00138_DS_
	BANKSEL	_PORTB_bits
	BCF	_PORTB_bits,6
;; gen.c:2327:resultRemat *{*
;; gen.c:2686:genLabel *{*
;; ***	genLabel  2689
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:7895:genPointerSet *{*
;; ***	genPointerSet  7896
;; gen.c:7723:genNearPointerSet *{*
;; ***	genNearPointerSet  7724
;;	689
;;	aopForRemat 474
;;	495: rname _PORTB_bits, val 0, const = 0
;; ***	genNearPointerSet  7741
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
;; 	line = 7743 result AOP_PCODE=_PORTB_bits, size=2, left -=-, size=0, right AOP_LIT=0x01, size=1
;; gen.c:7472:genPackBits *{*
;; ***	genPackBits  7473
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
; >>> gen.c:7498:genPackBits
_00139_DS_
	.line	130; "spi.c"	CLK1
	BANKSEL	_PORTB_bits
	BSF	_PORTB_bits,7
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:7895:genPointerSet *{*
;; ***	genPointerSet  7896
;; gen.c:7723:genNearPointerSet *{*
;; ***	genNearPointerSet  7724
;;	689
;;	aopForRemat 474
;;	495: rname _PORTB_bits, val 0, const = 0
;; ***	genNearPointerSet  7741
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
;; 	line = 7743 result AOP_PCODE=_PORTB_bits, size=2, left -=-, size=0, right AOP_LIT=0x00, size=1
;; gen.c:7472:genPackBits *{*
;; ***	genPackBits  7473
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
; >>> gen.c:7498:genPackBits
	.line	132; "spi.c"	CLK0
	BCF	_PORTB_bits,7
;; gen.c:2327:resultRemat *{*
;; gen.c:4410:ifxForOp *{*
;; ***	ifxForOp  4412
;; gen.c:4625:genAnd *{*
;; ***	genAnd  4626
;;	769 register type nRegs=1
;; 	line = 4660 result AOP_CRY=0x00, size=0, left AOP_REG=r0x104D, size=1, right AOP_LIT=0x04, size=1
;; gen.c:4552:isLiteralBit *{*
;; ***	isLiteralBit  4553
; >>> gen.c:4729:genAnd
	.line	133; "spi.c"	if ((b&4)!=0) SDA1 else SDA0
	BANKSEL	r0x100C
	BTFSS	r0x100C,2
; >>> gen.c:4730:genAnd
;; ***	popGetLabel  key=17, label offset 24
	GOTO	_00141_DS_
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:7895:genPointerSet *{*
;; ***	genPointerSet  7896
;; gen.c:7723:genNearPointerSet *{*
;; ***	genNearPointerSet  7724
;;	689
;;	aopForRemat 474
;;	495: rname _PORTB_bits, val 0, const = 0
;; ***	genNearPointerSet  7741
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
;; 	line = 7743 result AOP_PCODE=_PORTB_bits, size=2, left -=-, size=0, right AOP_LIT=0x01, size=1
;; gen.c:7472:genPackBits *{*
;; ***	genPackBits  7473
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
; >>> gen.c:7498:genPackBits
	BANKSEL	_PORTB_bits
	BSF	_PORTB_bits,6
;; gen.c:2327:resultRemat *{*
;; gen.c:2703:genGoto *{*
; >>> gen.c:2705:genGoto
;; ***	popGetLabel  key=18, label offset 24
	GOTO	_00142_DS_
;; gen.c:2327:resultRemat *{*
;; gen.c:2686:genLabel *{*
;; ***	genLabel  2689
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:7895:genPointerSet *{*
;; ***	genPointerSet  7896
;; gen.c:7723:genNearPointerSet *{*
;; ***	genNearPointerSet  7724
;;	689
;;	aopForRemat 474
;;	495: rname _PORTB_bits, val 0, const = 0
;; ***	genNearPointerSet  7741
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
;; 	line = 7743 result AOP_PCODE=_PORTB_bits, size=2, left -=-, size=0, right AOP_LIT=0x00, size=1
;; gen.c:7472:genPackBits *{*
;; ***	genPackBits  7473
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
; >>> gen.c:7498:genPackBits
_00141_DS_
	BANKSEL	_PORTB_bits
	BCF	_PORTB_bits,6
;; gen.c:2327:resultRemat *{*
;; gen.c:2686:genLabel *{*
;; ***	genLabel  2689
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:7895:genPointerSet *{*
;; ***	genPointerSet  7896
;; gen.c:7723:genNearPointerSet *{*
;; ***	genNearPointerSet  7724
;;	689
;;	aopForRemat 474
;;	495: rname _PORTB_bits, val 0, const = 0
;; ***	genNearPointerSet  7741
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
;; 	line = 7743 result AOP_PCODE=_PORTB_bits, size=2, left -=-, size=0, right AOP_LIT=0x01, size=1
;; gen.c:7472:genPackBits *{*
;; ***	genPackBits  7473
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
; >>> gen.c:7498:genPackBits
_00142_DS_
	.line	134; "spi.c"	CLK1
	BANKSEL	_PORTB_bits
	BSF	_PORTB_bits,7
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:7895:genPointerSet *{*
;; ***	genPointerSet  7896
;; gen.c:7723:genNearPointerSet *{*
;; ***	genNearPointerSet  7724
;;	689
;;	aopForRemat 474
;;	495: rname _PORTB_bits, val 0, const = 0
;; ***	genNearPointerSet  7741
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
;; 	line = 7743 result AOP_PCODE=_PORTB_bits, size=2, left -=-, size=0, right AOP_LIT=0x00, size=1
;; gen.c:7472:genPackBits *{*
;; ***	genPackBits  7473
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
; >>> gen.c:7498:genPackBits
	.line	136; "spi.c"	CLK0
	BCF	_PORTB_bits,7
;; gen.c:2327:resultRemat *{*
;; gen.c:4410:ifxForOp *{*
;; ***	ifxForOp  4412
;; gen.c:4625:genAnd *{*
;; ***	genAnd  4626
;;	769 register type nRegs=1
;; 	line = 4660 result AOP_CRY=0x00, size=0, left AOP_REG=r0x104D, size=1, right AOP_LIT=0x02, size=1
;; gen.c:4552:isLiteralBit *{*
;; ***	isLiteralBit  4553
; >>> gen.c:4729:genAnd
	.line	137; "spi.c"	if ((b&2)!=0) SDA1 else SDA0
	BANKSEL	r0x100C
	BTFSS	r0x100C,1
; >>> gen.c:4730:genAnd
;; ***	popGetLabel  key=20, label offset 24
	GOTO	_00144_DS_
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:7895:genPointerSet *{*
;; ***	genPointerSet  7896
;; gen.c:7723:genNearPointerSet *{*
;; ***	genNearPointerSet  7724
;;	689
;;	aopForRemat 474
;;	495: rname _PORTB_bits, val 0, const = 0
;; ***	genNearPointerSet  7741
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
;; 	line = 7743 result AOP_PCODE=_PORTB_bits, size=2, left -=-, size=0, right AOP_LIT=0x01, size=1
;; gen.c:7472:genPackBits *{*
;; ***	genPackBits  7473
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
; >>> gen.c:7498:genPackBits
	BANKSEL	_PORTB_bits
	BSF	_PORTB_bits,6
;; gen.c:2327:resultRemat *{*
;; gen.c:2703:genGoto *{*
; >>> gen.c:2705:genGoto
;; ***	popGetLabel  key=21, label offset 24
	GOTO	_00145_DS_
;; gen.c:2327:resultRemat *{*
;; gen.c:2686:genLabel *{*
;; ***	genLabel  2689
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:7895:genPointerSet *{*
;; ***	genPointerSet  7896
;; gen.c:7723:genNearPointerSet *{*
;; ***	genNearPointerSet  7724
;;	689
;;	aopForRemat 474
;;	495: rname _PORTB_bits, val 0, const = 0
;; ***	genNearPointerSet  7741
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
;; 	line = 7743 result AOP_PCODE=_PORTB_bits, size=2, left -=-, size=0, right AOP_LIT=0x00, size=1
;; gen.c:7472:genPackBits *{*
;; ***	genPackBits  7473
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
; >>> gen.c:7498:genPackBits
_00144_DS_
	BANKSEL	_PORTB_bits
	BCF	_PORTB_bits,6
;; gen.c:2327:resultRemat *{*
;; gen.c:2686:genLabel *{*
;; ***	genLabel  2689
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:7895:genPointerSet *{*
;; ***	genPointerSet  7896
;; gen.c:7723:genNearPointerSet *{*
;; ***	genNearPointerSet  7724
;;	689
;;	aopForRemat 474
;;	495: rname _PORTB_bits, val 0, const = 0
;; ***	genNearPointerSet  7741
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
;; 	line = 7743 result AOP_PCODE=_PORTB_bits, size=2, left -=-, size=0, right AOP_LIT=0x01, size=1
;; gen.c:7472:genPackBits *{*
;; ***	genPackBits  7473
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
; >>> gen.c:7498:genPackBits
_00145_DS_
	.line	138; "spi.c"	CLK1
	BANKSEL	_PORTB_bits
	BSF	_PORTB_bits,7
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:7895:genPointerSet *{*
;; ***	genPointerSet  7896
;; gen.c:7723:genNearPointerSet *{*
;; ***	genNearPointerSet  7724
;;	689
;;	aopForRemat 474
;;	495: rname _PORTB_bits, val 0, const = 0
;; ***	genNearPointerSet  7741
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
;; 	line = 7743 result AOP_PCODE=_PORTB_bits, size=2, left -=-, size=0, right AOP_LIT=0x00, size=1
;; gen.c:7472:genPackBits *{*
;; ***	genPackBits  7473
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
; >>> gen.c:7498:genPackBits
	.line	140; "spi.c"	CLK0
	BCF	_PORTB_bits,7
;; gen.c:2327:resultRemat *{*
;; gen.c:4410:ifxForOp *{*
;; ***	ifxForOp  4412
;; gen.c:4625:genAnd *{*
;; ***	genAnd  4626
;;	769 register type nRegs=1
;; 	line = 4660 result AOP_CRY=0x00, size=0, left AOP_REG=r0x104D, size=1, right AOP_LIT=0x01, size=1
;; gen.c:4552:isLiteralBit *{*
;; ***	isLiteralBit  4553
; >>> gen.c:4729:genAnd
	.line	141; "spi.c"	if ((b&1)!=0) SDA1 else SDA0
	BANKSEL	r0x100C
	BTFSS	r0x100C,0
; >>> gen.c:4730:genAnd
;; ***	popGetLabel  key=23, label offset 24
	GOTO	_00147_DS_
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:7895:genPointerSet *{*
;; ***	genPointerSet  7896
;; gen.c:7723:genNearPointerSet *{*
;; ***	genNearPointerSet  7724
;;	689
;;	aopForRemat 474
;;	495: rname _PORTB_bits, val 0, const = 0
;; ***	genNearPointerSet  7741
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
;; 	line = 7743 result AOP_PCODE=_PORTB_bits, size=2, left -=-, size=0, right AOP_LIT=0x01, size=1
;; gen.c:7472:genPackBits *{*
;; ***	genPackBits  7473
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
; >>> gen.c:7498:genPackBits
	BANKSEL	_PORTB_bits
	BSF	_PORTB_bits,6
;; gen.c:2327:resultRemat *{*
;; gen.c:2703:genGoto *{*
; >>> gen.c:2705:genGoto
;; ***	popGetLabel  key=24, label offset 24
	GOTO	_00148_DS_
;; gen.c:2327:resultRemat *{*
;; gen.c:2686:genLabel *{*
;; ***	genLabel  2689
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:7895:genPointerSet *{*
;; ***	genPointerSet  7896
;; gen.c:7723:genNearPointerSet *{*
;; ***	genNearPointerSet  7724
;;	689
;;	aopForRemat 474
;;	495: rname _PORTB_bits, val 0, const = 0
;; ***	genNearPointerSet  7741
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
;; 	line = 7743 result AOP_PCODE=_PORTB_bits, size=2, left -=-, size=0, right AOP_LIT=0x00, size=1
;; gen.c:7472:genPackBits *{*
;; ***	genPackBits  7473
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
; >>> gen.c:7498:genPackBits
_00147_DS_
	BANKSEL	_PORTB_bits
	BCF	_PORTB_bits,6
;; gen.c:2327:resultRemat *{*
;; gen.c:2686:genLabel *{*
;; ***	genLabel  2689
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:7895:genPointerSet *{*
;; ***	genPointerSet  7896
;; gen.c:7723:genNearPointerSet *{*
;; ***	genNearPointerSet  7724
;;	689
;;	aopForRemat 474
;;	495: rname _PORTB_bits, val 0, const = 0
;; ***	genNearPointerSet  7741
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
;; 	line = 7743 result AOP_PCODE=_PORTB_bits, size=2, left -=-, size=0, right AOP_LIT=0x01, size=1
;; gen.c:7472:genPackBits *{*
;; ***	genPackBits  7473
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
; >>> gen.c:7498:genPackBits
_00148_DS_
	.line	142; "spi.c"	CLK1
	BANKSEL	_PORTB_bits
	BSF	_PORTB_bits,7
;; gen.c:2327:resultRemat *{*
;; gen.c:2686:genLabel *{*
;; ***	genLabel  2689
;; gen.c:2327:resultRemat *{*
;; gen.c:2524:genEndFunction *{*
;; ***	genEndFunction  2526
	RETURN	
; exit point of _shiftBits
;; gen.c:8749:genpic14Code *{*

;***
;  pBlock Stats: dbName = C
;***
;entry:  _sendCMD	;Function start
; 2 exit points
;has an exit
;functions called:
;   _shiftBits
;   _shiftBits
;1 compiler assigned register :
;   r0x100B
;; Starting pCode block
;; gen.c:2327:resultRemat *{*
;; gen.c:2686:genLabel *{*
;; ***	genLabel  2689
;; gen.c:2327:resultRemat *{*
;; gen.c:2372:genFunction *{*
;; ***	genFunction  2374 curr label offset=4previous max_key=12 
_sendCMD	;Function start
; 2 exit points
;; gen.c:2327:resultRemat *{*
;; gen.c:8685:genReceive *{*
;; ***	genReceive  8686
;;	769 register type nRegs=1
;; gen.c:1882:assignResultValue *{*
;; ***	assignResultValue  1884
;; 	line = 1886 result -=-, size=0, left AOP_REG=r0x104C, size=1, right -=-, size=0
; >>> gen.c:1433:movwf
;;	1150 rIdx = r0x104C 
	.line	101; "spi.c"	void sendCMD(byte datax) {
	BANKSEL	r0x100B
	MOVWF	r0x100B
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:7895:genPointerSet *{*
;; ***	genPointerSet  7896
;; gen.c:7723:genNearPointerSet *{*
;; ***	genNearPointerSet  7724
;;	689
;;	aopForRemat 474
;;	495: rname _PORTB_bits, val 0, const = 0
;; ***	genNearPointerSet  7741
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
;; 	line = 7743 result AOP_PCODE=_PORTB_bits, size=2, left -=-, size=0, right AOP_LIT=0x00, size=1
;; gen.c:7472:genPackBits *{*
;; ***	genPackBits  7473
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
; >>> gen.c:7498:genPackBits
	.line	103; "spi.c"	CLK0
	BANKSEL	_PORTB_bits
	BCF	_PORTB_bits,7
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:7895:genPointerSet *{*
;; ***	genPointerSet  7896
;; gen.c:7723:genNearPointerSet *{*
;; ***	genNearPointerSet  7724
;;	689
;;	aopForRemat 474
;;	495: rname _PORTB_bits, val 0, const = 0
;; ***	genNearPointerSet  7741
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
;; 	line = 7743 result AOP_PCODE=_PORTB_bits, size=2, left -=-, size=0, right AOP_LIT=0x00, size=1
;; gen.c:7472:genPackBits *{*
;; ***	genPackBits  7473
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
; >>> gen.c:7498:genPackBits
	.line	104; "spi.c"	SDA0                                                 //1 para cmd
	BCF	_PORTB_bits,6
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:7895:genPointerSet *{*
;; ***	genPointerSet  7896
;; gen.c:7723:genNearPointerSet *{*
;; ***	genNearPointerSet  7724
;;	689
;;	aopForRemat 474
;;	495: rname _PORTB_bits, val 0, const = 0
;; ***	genNearPointerSet  7741
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
;; 	line = 7743 result AOP_PCODE=_PORTB_bits, size=2, left -=-, size=0, right AOP_LIT=0x01, size=1
;; gen.c:7472:genPackBits *{*
;; ***	genPackBits  7473
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTB_bits
; >>> gen.c:7498:genPackBits
	.line	105; "spi.c"	CLK1
	BSF	_PORTB_bits,7
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:2096:genCall *{*
;; ***	genCall  2098
;; gen.c:1781:saveRegisters *{*
;; ***	saveRegisters  1783
;;	769 register type nRegs=1
;;	769 register type nRegs=1
;; 	2145 left AOP_REG
;; gen.c:1390:mov2w_op *{*
;; ***	mov2w  1422  offset=0
; >>> gen.c:1427:mov2w
;;	1150 rIdx = r0x104C 
	.line	107; "spi.c"	shiftBits(datax);
	BANKSEL	r0x100B
	MOVF	r0x100B,W
; >>> gen.c:2182:genCall
	PAGESEL	_shiftBits
; >>> gen.c:2184:genCall
	CALL	_shiftBits
; >>> gen.c:2189:genCall
	PAGESEL	$
;; gen.c:1825:unsaveRegisters *{*
;; ***	unsaveRegisters  1827
;; gen.c:2327:resultRemat *{*
;; gen.c:2686:genLabel *{*
;; ***	genLabel  2689
;; gen.c:2327:resultRemat *{*
;; gen.c:2524:genEndFunction *{*
;; ***	genEndFunction  2526
	RETURN	
; exit point of _sendCMD
;; gen.c:8749:genpic14Code *{*

;***
;  pBlock Stats: dbName = C
;***
;entry:  _delay_ms	;Function start
; 2 exit points
;has an exit
;1 compiler assigned register :
;   r0x100B
;; Starting pCode block
;; gen.c:2327:resultRemat *{*
;; gen.c:2686:genLabel *{*
;; ***	genLabel  2689
;; gen.c:2327:resultRemat *{*
;; gen.c:2372:genFunction *{*
;; ***	genFunction  2374 curr label offset=0previous max_key=0 
_delay_ms	;Function start
; 2 exit points
;; gen.c:2327:resultRemat *{*
;; gen.c:8685:genReceive *{*
;; ***	genReceive  8686
;;	769 register type nRegs=1
;; gen.c:1882:assignResultValue *{*
;; ***	assignResultValue  1884
;; 	line = 1886 result -=-, size=0, left AOP_REG=r0x104B, size=1, right -=-, size=0
; >>> gen.c:1433:movwf
;;	1150 rIdx = r0x104B 
	.line	92; "spi.c"	void delay_ms(unsigned char loop)
	BANKSEL	r0x100B
	MOVWF	r0x100B
;; gen.c:2327:resultRemat *{*
;; gen.c:8139:genAssign *{*
;; ***	genAssign  8140
;; ***	aopForSym 393
;;	404 sym->rname = _c, size = 1
;; 	line = 8149 result AOP_DIR=_c, size=1, left -=-, size=0, right AOP_LIT=0x00, size=1
;; ***	genAssign  8241
; >>> gen.c:8250:genAssign
;;	1036
;;	1052  _c   offset=0
	.line	94; "spi.c"	for(c=0;c<loop;c++)
	BANKSEL	_c
	CLRF	_c
;; gen.c:2327:resultRemat *{*
;; gen.c:2686:genLabel *{*
;; ***	genLabel  2689
;; gen.c:2327:resultRemat *{*
;; gen.c:4410:ifxForOp *{*
;; ***	ifxForOp  4412
;; gen.c:4263:genCmpLt *{*
;; ***	genCmpLt  4264
;; ***	aopForSym 393
;;	404 sym->rname = _c, size = 1
;;	769 register type nRegs=1
;; gen.c:3365:genCmp *{*
; >>> gen.c:3340:pic14_mov2w_regOrLit
;;	1150 rIdx = r0x104B 
_00112_DS_
	BANKSEL	r0x100B
	MOVF	r0x100B,W
; >>> gen.c:3473:genCmp
;;	1036
;;	1052  _c   offset=0
	BANKSEL	_c
	SUBWF	_c,W
;; gen.c:3215:genSkipc *{*
; >>> gen.c:3220:genSkipc
	BTFSC	STATUS,0
; >>> gen.c:3224:genSkipc
;; ***	popGetLabel  key=12, label offset 4
	GOTO	_00116_DS_
;genSkipc:3225: created from rifx:0xbfe2b6c0
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:8139:genAssign *{*
;; ***	genAssign  8140
;; ***	aopForSym 393
;;	404 sym->rname = _d, size = 1
;; 	line = 8149 result AOP_DIR=_d, size=1, left -=-, size=0, right AOP_LIT=0x00, size=1
;; ***	genAssign  8241
; >>> gen.c:8250:genAssign
;;	1036
;;	1052  _d   offset=0
	.line	95; "spi.c"	for(d=0;d<255;d++)
	BANKSEL	_d
	CLRF	_d
;; gen.c:2327:resultRemat *{*
;; gen.c:2686:genLabel *{*
;; ***	genLabel  2689
;; gen.c:2327:resultRemat *{*
;; gen.c:4410:ifxForOp *{*
;; ***	ifxForOp  4412
;; gen.c:4263:genCmpLt *{*
;; ***	genCmpLt  4264
;; ***	aopForSym 393
;;	404 sym->rname = _d, size = 1
;; gen.c:3365:genCmp *{*
;unsigned compare: left < lit(0xFF=255), size=1
; >>> gen.c:3338:pic14_mov2w_regOrLit
_00108_DS_
	MOVLW	0xff
; >>> gen.c:3473:genCmp
;;	1036
;;	1052  _d   offset=0
	BANKSEL	_d
	SUBWF	_d,W
;; gen.c:3215:genSkipc *{*
; >>> gen.c:3220:genSkipc
	BTFSC	STATUS,0
; >>> gen.c:3224:genSkipc
;; ***	popGetLabel  key=10, label offset 4
	GOTO	_00114_DS_
;genSkipc:3225: created from rifx:0xbfe2b6c0
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:8139:genAssign *{*
;; ***	genAssign  8140
;; ***	aopForSym 393
;;	404 sym->rname = _e, size = 1
;; 	line = 8149 result AOP_DIR=_e, size=1, left -=-, size=0, right AOP_LIT=0x04, size=1
;; ***	genAssign  8241
; >>> gen.c:8246:genAssign
	.line	96; "spi.c"	for(e=0;e<4;e++);
	MOVLW	0x04
; >>> gen.c:8248:genAssign
;;	1036
;;	1052  _e   offset=0
	BANKSEL	_e
	MOVWF	_e
;; gen.c:2327:resultRemat *{*
;; gen.c:2686:genLabel *{*
;; ***	genLabel  2689
;; gen.c:2327:resultRemat *{*
;; gen.c:4410:ifxForOp *{*
;; ***	ifxForOp  4412
;; gen.c:8641:genDjnz *{*
;; ***	genDjnz  8642
;; genarith.c:1008:genMinus *{*
;; ***	genMinus  1009
;; ***	aopForSym 393
;;	404 sym->rname = _e, size = 1
;;	654
;; 	result AOP_DIR, left AOP_DIR, right AOP_LIT
;; ***	pic14_getDataSize  1492
;; ***	pic14_getDataSize  1492
;; genarith.c:399:genAddLit *{*
;; ***	genAddLit  400
;; ***	pic14_getDataSize  1492
;; ***	pic14_getDataSize  1492
;; genarith.c:362:genAddLit2byte *{*
; >>> genarith.c:371:genAddLit2byte
;;	1036
;;	1052  _e   offset=0
_00107_DS_
	BANKSEL	_e
	DECF	_e,F
;; ***	pic14_getDataSize  1492
;; ***	pic14_getDataSize  1492
;; ***	pic14_getDataSize  1492
;; ***	addSign  973
;; genarith.c:974:addSign *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:7965:genIfx *{*
;; ***	genIfx  7966
;; ***	aopForSym 393
;;	404 sym->rname = _e, size = 1
;; ***	pic14_toBoolean  1566
; >>> gen.c:1572:pic14_toBoolean
	MOVF	_e,W
	BTFSS	STATUS,2
; >>> gen.c:8012:genIfx
;; ***	popGetLabel  key=3, label offset 4
	GOTO	_00107_DS_
;; gen.c:2327:resultRemat *{*
;; gen.c:8139:genAssign *{*
;; ***	genAssign  8140
;; ***	aopForSym 393
;;	404 sym->rname = _e, size = 1
;; 	line = 8149 result AOP_DIR=_e, size=1, left -=-, size=0, right AOP_LIT=0x04, size=1
;; ***	genAssign  8241
; >>> gen.c:8246:genAssign
	MOVLW	0x04
; >>> gen.c:8248:genAssign
;;	1036
;;	1052  _e   offset=0
	MOVWF	_e
;; gen.c:2327:resultRemat *{*
;; ***	genPlus  718
;; genarith.c:719:genPlus *{*
;; ***	aopForSym 393
;;	404 sym->rname = _d, size = 1
;; 	line = 725 result AOP_DIR=_d, size=1, left AOP_DIR=_d, size=1, right AOP_LIT=0x01, size=1
;; ***	pic14_getDataSize  1492
;; genarith.c:181:genPlusIncr *{*
;; ***	genPlusIncr  183
;; 	result AOP_DIR, left AOP_DIR, right AOP_LIT
;; 	genPlusIncr  195
; >>> genarith.c:207:genPlusIncr
;;	1036
;;	1052  _d   offset=0
	.line	95; "spi.c"	for(d=0;d<255;d++)
	BANKSEL	_d
	INCF	_d,F
;; gen.c:2327:resultRemat *{*
;; gen.c:2703:genGoto *{*
; >>> gen.c:2705:genGoto
;; ***	popGetLabel  key=4, label offset 4
	GOTO	_00108_DS_
;; gen.c:2327:resultRemat *{*
;; gen.c:2686:genLabel *{*
;; ***	genLabel  2689
;; gen.c:2327:resultRemat *{*
;; ***	genPlus  718
;; genarith.c:719:genPlus *{*
;; ***	aopForSym 393
;;	404 sym->rname = _c, size = 1
;; 	line = 725 result AOP_DIR=_c, size=1, left AOP_DIR=_c, size=1, right AOP_LIT=0x01, size=1
;; ***	pic14_getDataSize  1492
;; genarith.c:181:genPlusIncr *{*
;; ***	genPlusIncr  183
;; 	result AOP_DIR, left AOP_DIR, right AOP_LIT
;; 	genPlusIncr  195
; >>> genarith.c:207:genPlusIncr
;;	1036
;;	1052  _c   offset=0
_00114_DS_
	.line	94; "spi.c"	for(c=0;c<loop;c++)
	BANKSEL	_c
	INCF	_c,F
;; gen.c:2327:resultRemat *{*
;; gen.c:2703:genGoto *{*
; >>> gen.c:2705:genGoto
;; ***	popGetLabel  key=8, label offset 4
	GOTO	_00112_DS_
;; gen.c:2327:resultRemat *{*
;; gen.c:2686:genLabel *{*
;; ***	genLabel  2689
;; gen.c:2327:resultRemat *{*
;; gen.c:2524:genEndFunction *{*
;; ***	genEndFunction  2526
_00116_DS_
	RETURN	
; exit point of _delay_ms
;; gen.c:8749:genpic14Code *{*


;	code size estimation:
;	  319+   94 =   413 instructions ( 1014 byte)

	end
