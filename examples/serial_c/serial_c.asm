;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 2.8.0 #5117 (Jun  2 2008) (UNIX)
; This file was generated Sat Jul  3 22:26:51 2010
;--------------------------------------------------------
; PIC port for the 14-bit core
;--------------------------------------------------------
	.file	"serial_c.c"
	list	p=16f628a
	radix dec
	include "p16f628a.inc"
;--------------------------------------------------------
; config word 
;--------------------------------------------------------
	__config 0x3f0a
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
	extern	___sdcc_saved_fsr
	extern	__sdcc_gsinit_startup
;--------------------------------------------------------
; global declarations
;--------------------------------------------------------
	global	_delay
	global	_main
	global	_cmd
	global	_DD
	global	_EE
	global	_FF

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
UD_serial_c_0	udata
_cmd	res	1

UD_serial_c_1	udata
_DD	res	1

UD_serial_c_2	udata
_EE	res	1

UD_serial_c_3	udata
_FF	res	1

;--------------------------------------------------------
; absolute symbol definitions
;--------------------------------------------------------
;--------------------------------------------------------
; compiler-defined variables
;--------------------------------------------------------
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
; interrupt and initialization code
;--------------------------------------------------------
c_interrupt	code	0x4
__sdcc_interrupt
;***
;  pBlock Stats: dbName = I
;***
;entry:  _Intr	;Function start
; 0 exit points
;; Starting pCode block
;; gen.c:2327:resultRemat *{*
;; gen.c:2686:genLabel *{*
;; ***	genLabel  2689
;; gen.c:2327:resultRemat *{*
;; gen.c:2372:genFunction *{*
;; ***	genFunction  2374 curr label offset=4previous max_key=8 
_Intr	;Function start
; 0 exit points
; >>> gen.c:2429:genFunction
	.line	20; "serial_c.c"	static void Intr(void) interrupt 0 {
	MOVWF	WSAVE
; >>> gen.c:2430:genFunction
	SWAPF	STATUS,W
; >>> gen.c:2435:genFunction
	CLRF	STATUS
; >>> gen.c:2436:genFunction
	MOVWF	SSAVE
; >>> gen.c:2438:genFunction
	MOVF	PCLATH,W
; >>> gen.c:2440:genFunction
	CLRF	PCLATH
; >>> gen.c:2441:genFunction
	MOVWF	PSAVE
; >>> gen.c:2443:genFunction
	MOVF	FSR,W
; >>> gen.c:2444:genFunction
	.line	22; "serial_c.c"	}
	BANKSEL	___sdcc_saved_fsr
	MOVWF	___sdcc_saved_fsr
	MOVWF	FSR
; >>> gen.c:2600:genEndFunction
	MOVF	PSAVE,W
; >>> gen.c:2601:genEndFunction
	MOVWF	PCLATH
; >>> gen.c:2602:genEndFunction
	CLRF	STATUS
; >>> gen.c:2604:genEndFunction
	SWAPF	SSAVE,W
; >>> gen.c:2605:genEndFunction
	MOVWF	STATUS
; >>> gen.c:2606:genEndFunction
	SWAPF	WSAVE,F
; >>> gen.c:2607:genEndFunction
	SWAPF	WSAVE,W
END_OF_INTERRUPT
	RETFIE	
;; gen.c:8749:genpic14Code *{*

;--------------------------------------------------------
; code
;--------------------------------------------------------
code_serial_c	code
;***
;  pBlock Stats: dbName = M
;***
;entry:  _main	;Function start
; 2 exit points
;has an exit
;; Starting pCode block
;; gen.c:2327:resultRemat *{*
;; gen.c:2686:genLabel *{*
;; ***	genLabel  2689
;; gen.c:2327:resultRemat *{*
;; gen.c:2372:genFunction *{*
;; ***	genFunction  2374 curr label offset=16previous max_key=0 
_main	;Function start
; 2 exit points
;; gen.c:2327:resultRemat *{*
;; gen.c:8139:genAssign *{*
;; ***	genAssign  8140
;; ***	aopForSym 393
;;	404 sym->rname = _CMCON, size = 1
;; 	line = 8149 result AOP_DIR=_CMCON, size=1, left -=-, size=0, right AOP_LIT=0x07, size=1
;; ***	genAssign  8241
; >>> gen.c:8246:genAssign
	.line	27; "serial_c.c"	CMCON=7;	//desabilita os amp-ops internos
	MOVLW	0x07
; >>> gen.c:8248:genAssign
;;	1036
;;	1052  _CMCON   offset=0
	BANKSEL	_CMCON
	MOVWF	_CMCON
;; gen.c:2327:resultRemat *{*
;; gen.c:8139:genAssign *{*
;; ***	genAssign  8140
;; ***	aopForSym 393
;;	404 sym->rname = _INTCON, size = 1
;; 	line = 8149 result AOP_DIR=_INTCON, size=1, left -=-, size=0, right AOP_LIT=0x00, size=1
;; ***	genAssign  8241
; >>> gen.c:8250:genAssign
;;	1036
;;	1050  _INTCON   offset=0 - had to alloc by reg name
	.line	29; "serial_c.c"	INTCON = 0;    // Limpa a flag de interrupcoes.
	CLRF	_INTCON
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:7895:genPointerSet *{*
;; ***	genPointerSet  7896
;; gen.c:7723:genNearPointerSet *{*
;; ***	genNearPointerSet  7724
;;	689
;;	aopForRemat 474
;;	495: rname _OPTION_REG_bits, val 0, const = 0
;; ***	genNearPointerSet  7741
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_OPTION_REG_bits
;; 	line = 7743 result AOP_PCODE=_OPTION_REG_bits, size=2, left -=-, size=0, right AOP_LIT=0x00, size=1
;; gen.c:7472:genPackBits *{*
;; ***	genPackBits  7473
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_OPTION_REG_bits
; >>> gen.c:7498:genPackBits
	.line	31; "serial_c.c"	NOT_RBPU=0;  //desabilita pull-up da porta b
	BANKSEL	_OPTION_REG_bits
	BCF	_OPTION_REG_bits,7
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:7895:genPointerSet *{*
;; ***	genPointerSet  7896
;; gen.c:7723:genNearPointerSet *{*
;; ***	genNearPointerSet  7724
;;	689
;;	aopForRemat 474
;;	495: rname _INTCON_bits, val 0, const = 0
;; ***	genNearPointerSet  7741
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_INTCON_bits
;; 	line = 7743 result AOP_PCODE=_INTCON_bits, size=2, left -=-, size=0, right AOP_LIT=0x00, size=1
;; gen.c:7472:genPackBits *{*
;; ***	genPackBits  7473
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_INTCON_bits
; >>> gen.c:7498:genPackBits
	.line	32; "serial_c.c"	GIE=0;       //desabilita interrupcoes
	BANKSEL	_INTCON_bits
	BCF	_INTCON_bits,7
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
	.line	35; "serial_c.c"	TX9=0;    //transmiss�o em 8 bits
	BANKSEL	_TXSTA_bits
	BCF	_TXSTA_bits,6
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
	.line	36; "serial_c.c"	TXEN=1; //habilita transmiss�o
	BSF	_TXSTA_bits,5
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
	.line	37; "serial_c.c"	SYNC=0; //modo assincrono
	BCF	_TXSTA_bits,4
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
	.line	38; "serial_c.c"	BRGH=0; //low baud rate
	BCF	_TXSTA_bits,2
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
	.line	39; "serial_c.c"	SPEN=1; //habilita porta serial - rx
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
;;	495: rname _RCSTA_bits, val 0, const = 0
;; ***	genNearPointerSet  7741
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_RCSTA_bits
;; 	line = 7743 result AOP_PCODE=_RCSTA_bits, size=2, left -=-, size=0, right AOP_LIT=0x00, size=1
;; gen.c:7472:genPackBits *{*
;; ***	genPackBits  7473
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_RCSTA_bits
; >>> gen.c:7498:genPackBits
	.line	40; "serial_c.c"	RX9=0;  //recep��o em 8 bits
	BCF	_RCSTA_bits,6
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
	.line	41; "serial_c.c"	CREN=1; //recep��o cont�nua
	BSF	_RCSTA_bits,4
;; gen.c:2327:resultRemat *{*
;; gen.c:8139:genAssign *{*
;; ***	genAssign  8140
;; ***	aopForSym 393
;;	404 sym->rname = _SPBRG, size = 1
;; 	line = 8149 result AOP_DIR=_SPBRG, size=1, left -=-, size=0, right AOP_LIT=0x19, size=1
;; ***	genAssign  8241
; >>> gen.c:8246:genAssign
	.line	43; "serial_c.c"	SPBRG=25; //baud rate de 9600
	MOVLW	0x19
; >>> gen.c:8248:genAssign
;;	1036
;;	1052  _SPBRG   offset=0
	BANKSEL	_SPBRG
	MOVWF	_SPBRG
;; gen.c:2327:resultRemat *{*
;; gen.c:8139:genAssign *{*
;; ***	genAssign  8140
;; ***	aopForSym 393
;;	404 sym->rname = _TRISB, size = 1
;; 	line = 8149 result AOP_DIR=_TRISB, size=1, left -=-, size=0, right AOP_LIT=0x02, size=1
;; ***	genAssign  8241
; >>> gen.c:8246:genAssign
	.line	45; "serial_c.c"	TRISB=  0x02;  //0b01111010 configura I/O da porta B   
	MOVLW	0x02
; >>> gen.c:8248:genAssign
;;	1036
;;	1052  _TRISB   offset=0
	MOVWF	_TRISB
;; gen.c:2327:resultRemat *{*
;; gen.c:8139:genAssign *{*
;; ***	genAssign  8140
;; ***	aopForSym 393
;;	404 sym->rname = _TRISA, size = 1
;; 	line = 8149 result AOP_DIR=_TRISA, size=1, left -=-, size=0, right AOP_LIT=0xff, size=1
;; ***	genAssign  8241
; >>> gen.c:8246:genAssign
	.line	46; "serial_c.c"	TRISA = 0xFF;
	MOVLW	0xff
; >>> gen.c:8248:genAssign
;;	1036
;;	1052  _TRISA   offset=0
	MOVWF	_TRISA
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:7895:genPointerSet *{*
;; ***	genPointerSet  7896
;; gen.c:7723:genNearPointerSet *{*
;; ***	genNearPointerSet  7724
;;	689
;;	aopForRemat 474
;;	495: rname _PORTA_bits, val 0, const = 0
;; ***	genNearPointerSet  7741
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTA_bits
;; 	line = 7743 result AOP_PCODE=_PORTA_bits, size=2, left -=-, size=0, right AOP_LIT=0x00, size=1
;; gen.c:7472:genPackBits *{*
;; ***	genPackBits  7473
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTA_bits
; >>> gen.c:7498:genPackBits
	.line	48; "serial_c.c"	RA0=0;
	BANKSEL	_PORTA_bits
	BCF	_PORTA_bits,0
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:7895:genPointerSet *{*
;; ***	genPointerSet  7896
;; gen.c:7723:genNearPointerSet *{*
;; ***	genNearPointerSet  7724
;;	689
;;	aopForRemat 474
;;	495: rname _PORTA_bits, val 0, const = 0
;; ***	genNearPointerSet  7741
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTA_bits
;; 	line = 7743 result AOP_PCODE=_PORTA_bits, size=2, left -=-, size=0, right AOP_LIT=0x00, size=1
;; gen.c:7472:genPackBits *{*
;; ***	genPackBits  7473
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTA_bits
; >>> gen.c:7498:genPackBits
	.line	49; "serial_c.c"	RA1=0;
	BCF	_PORTA_bits,1
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:7895:genPointerSet *{*
;; ***	genPointerSet  7896
;; gen.c:7723:genNearPointerSet *{*
;; ***	genNearPointerSet  7724
;;	689
;;	aopForRemat 474
;;	495: rname _PIR1_bits, val 0, const = 0
;; ***	genNearPointerSet  7741
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PIR1_bits
;; 	line = 7743 result AOP_PCODE=_PIR1_bits, size=2, left -=-, size=0, right AOP_LIT=0x00, size=1
;; gen.c:7472:genPackBits *{*
;; ***	genPackBits  7473
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PIR1_bits
; >>> gen.c:7498:genPackBits
	.line	50; "serial_c.c"	RCIF=0;
	BCF	_PIR1_bits,5
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
_00124_DS_
	.line	53; "serial_c.c"	if(RCIF) {
	BANKSEL	_PIR1_bits
	BTFSS	_PIR1_bits,5
; >>> gen.c:7036:genUnpackBits
;; ***	popGetLabel  key=4, label offset 20
	GOTO	_00124_DS_
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:8139:genAssign *{*
;; ***	genAssign  8140
;; ***	aopForSym 393
;;	404 sym->rname = _RCREG, size = 1
;; ***	aopForSym 393
;;	404 sym->rname = _PORTB, size = 1
;; 	line = 8149 result AOP_DIR=_PORTB, size=1, left -=-, size=0, right AOP_DIR=_RCREG, size=1
;; ***	genAssign  8241
;; gen.c:1390:mov2w_op *{*
;; ***	mov2w  1422  offset=0
; >>> gen.c:1427:mov2w
;;	1036
;;	1050  _RCREG   offset=0 - had to alloc by reg name
	.line	54; "serial_c.c"	PORTB=RCREG;
	MOVF	_RCREG,W
; >>> gen.c:8260:genAssign
;;	1036
;;	1052  _PORTB   offset=0
	MOVWF	_PORTB
;; gen.c:2327:resultRemat *{*
;; gen.c:8139:genAssign *{*
;; ***	genAssign  8140
;; ***	aopForSym 393
;;	404 sym->rname = _PORTA, size = 1
;; ***	aopForSym 393
;;	404 sym->rname = _TXREG, size = 1
;; 	line = 8149 result AOP_DIR=_TXREG, size=1, left -=-, size=0, right AOP_DIR=_PORTA, size=1
;; ***	genAssign  8241
;; gen.c:1390:mov2w_op *{*
;; ***	mov2w  1422  offset=0
; >>> gen.c:1427:mov2w
;;	1036
;;	1050  _PORTA   offset=0 - had to alloc by reg name
	.line	55; "serial_c.c"	TXREG=PORTA;
	MOVF	_PORTA,W
; >>> gen.c:8260:genAssign
;;	1036
;;	1052  _TXREG   offset=0
	MOVWF	_TXREG
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:7895:genPointerSet *{*
;; ***	genPointerSet  7896
;; gen.c:7723:genNearPointerSet *{*
;; ***	genNearPointerSet  7724
;;	689
;;	aopForRemat 474
;;	495: rname _PIR1_bits, val 0, const = 0
;; ***	genNearPointerSet  7741
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PIR1_bits
;; 	line = 7743 result AOP_PCODE=_PIR1_bits, size=2, left -=-, size=0, right AOP_LIT=0x00, size=1
;; gen.c:7472:genPackBits *{*
;; ***	genPackBits  7473
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PIR1_bits
; >>> gen.c:7498:genPackBits
	.line	56; "serial_c.c"	RCIF=0;
	BCF	_PIR1_bits,5
;; gen.c:2327:resultRemat *{*
;; gen.c:2703:genGoto *{*
; >>> gen.c:2705:genGoto
;; ***	popGetLabel  key=4, label offset 20
	GOTO	_00124_DS_
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
;entry:  _delay	;Function start
; 2 exit points
;has an exit
;; Starting pCode block
;; gen.c:2327:resultRemat *{*
;; gen.c:2686:genLabel *{*
;; ***	genLabel  2689
;; gen.c:2327:resultRemat *{*
;; gen.c:2372:genFunction *{*
;; ***	genFunction  2374 curr label offset=0previous max_key=0 
_delay	;Function start
; 2 exit points
;; gen.c:2327:resultRemat *{*
;; gen.c:8139:genAssign *{*
;; ***	genAssign  8140
;; ***	aopForSym 393
;;	404 sym->rname = _DD, size = 1
;; 	line = 8149 result AOP_DIR=_DD, size=1, left -=-, size=0, right AOP_LIT=0x00, size=1
;; ***	genAssign  8241
; >>> gen.c:8250:genAssign
;;	1036
;;	1052  _DD   offset=0
	.line	15; "serial_c.c"	for(DD=0;DD<255;DD++)
	BANKSEL	_DD
	CLRF	_DD
;; gen.c:2327:resultRemat *{*
;; gen.c:2686:genLabel *{*
;; ***	genLabel  2689
;; gen.c:2327:resultRemat *{*
;; gen.c:4410:ifxForOp *{*
;; ***	ifxForOp  4412
;; gen.c:4263:genCmpLt *{*
;; ***	genCmpLt  4264
;; ***	aopForSym 393
;;	404 sym->rname = _DD, size = 1
;; gen.c:3365:genCmp *{*
;unsigned compare: left < lit(0xFF=255), size=1
; >>> gen.c:3338:pic14_mov2w_regOrLit
_00108_DS_
	MOVLW	0xff
; >>> gen.c:3473:genCmp
;;	1036
;;	1052  _DD   offset=0
	BANKSEL	_DD
	SUBWF	_DD,W
;; gen.c:3215:genSkipc *{*
; >>> gen.c:3220:genSkipc
	BTFSC	STATUS,0
; >>> gen.c:3224:genSkipc
;; ***	popGetLabel  key=8, label offset 4
	GOTO	_00112_DS_
;genSkipc:3225: created from rifx:0x7ffffffef7a0
;; gen.c:2327:resultRemat *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:8139:genAssign *{*
;; ***	genAssign  8140
;; ***	aopForSym 393
;;	404 sym->rname = _EE, size = 1
;; 	line = 8149 result AOP_DIR=_EE, size=1, left -=-, size=0, right AOP_LIT=0xff, size=1
;; ***	genAssign  8241
; >>> gen.c:8246:genAssign
	.line	16; "serial_c.c"	for(EE=0;EE<255;EE++);
	MOVLW	0xff
; >>> gen.c:8248:genAssign
;;	1036
;;	1052  _EE   offset=0
	BANKSEL	_EE
	MOVWF	_EE
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
;;	404 sym->rname = _EE, size = 1
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
;;	1052  _EE   offset=0
_00107_DS_
	BANKSEL	_EE
	DECF	_EE,F
;; ***	pic14_getDataSize  1492
;; ***	pic14_getDataSize  1492
;; ***	pic14_getDataSize  1492
;; ***	addSign  973
;; genarith.c:974:addSign *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:7965:genIfx *{*
;; ***	genIfx  7966
;; ***	aopForSym 393
;;	404 sym->rname = _EE, size = 1
;; ***	pic14_toBoolean  1566
; >>> gen.c:1572:pic14_toBoolean
	MOVLW	0x00
; >>> gen.c:1580:pic14_toBoolean
;;	1036
;;	1052  _EE   offset=0
	IORWF	_EE,W
; >>> gen.c:8011:genIfx
	BTFSS	STATUS,2
; >>> gen.c:8012:genIfx
;; ***	popGetLabel  key=3, label offset 4
	GOTO	_00107_DS_
;; gen.c:2327:resultRemat *{*
;; gen.c:8139:genAssign *{*
;; ***	genAssign  8140
;; ***	aopForSym 393
;;	404 sym->rname = _EE, size = 1
;; 	line = 8149 result AOP_DIR=_EE, size=1, left -=-, size=0, right AOP_LIT=0xff, size=1
;; ***	genAssign  8241
; >>> gen.c:8246:genAssign
	MOVLW	0xff
; >>> gen.c:8248:genAssign
;;	1036
;;	1052  _EE   offset=0
	MOVWF	_EE
;; gen.c:2327:resultRemat *{*
;; ***	genPlus  718
;; genarith.c:719:genPlus *{*
;; ***	aopForSym 393
;;	404 sym->rname = _DD, size = 1
;; 	line = 725 result AOP_DIR=_DD, size=1, left AOP_DIR=_DD, size=1, right AOP_LIT=0x01, size=1
;; ***	pic14_getDataSize  1492
;; genarith.c:181:genPlusIncr *{*
;; ***	genPlusIncr  183
;; 	result AOP_DIR, left AOP_DIR, right AOP_LIT
;; 	genPlusIncr  195
; >>> genarith.c:207:genPlusIncr
;;	1036
;;	1052  _DD   offset=0
	.line	15; "serial_c.c"	for(DD=0;DD<255;DD++)
	BANKSEL	_DD
	INCF	_DD,F
;; gen.c:2327:resultRemat *{*
;; gen.c:2703:genGoto *{*
; >>> gen.c:2705:genGoto
;; ***	popGetLabel  key=4, label offset 4
	GOTO	_00108_DS_
;; gen.c:2327:resultRemat *{*
;; gen.c:2686:genLabel *{*
;; ***	genLabel  2689
;; gen.c:2327:resultRemat *{*
;; gen.c:2524:genEndFunction *{*
;; ***	genEndFunction  2526
_00112_DS_
	RETURN	
; exit point of _delay
;; gen.c:8749:genpic14Code *{*


;	code size estimation:
;	   65+   14 =    79 instructions (  186 byte)

	end
