;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 2.8.0 #5117 (Jun  2 2008) (UNIX)
; This file was generated Thu Jul 15 17:43:04 2010
;--------------------------------------------------------
; PIC port for the 14-bit core
;--------------------------------------------------------
	.file	"tmr0.c"
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
	global	_isr
	global	_main
	global	_cnt

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
UD_tmr0_0	udata
_cnt	res	1

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
;entry:  _isr	;Function start
; 0 exit points
;; Starting pCode block
;; gen.c:2327:resultRemat *{*
;; gen.c:2686:genLabel *{*
;; ***	genLabel  2689
;; gen.c:2327:resultRemat *{*
;; gen.c:2372:genFunction *{*
;; ***	genFunction  2374 curr label offset=0previous max_key=0 
_isr	;Function start
; 0 exit points
; >>> gen.c:2429:genFunction
	.line	17; "tmr0.c"	void isr() interrupt 0 
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
	BANKSEL	___sdcc_saved_fsr
	MOVWF	___sdcc_saved_fsr
;; gen.c:2327:resultRemat *{*
;; gen.c:4410:ifxForOp *{*
;; ***	ifxForOp  4412
;; gen.c:8641:genDjnz *{*
;; ***	genDjnz  8642
;; genarith.c:1008:genMinus *{*
;; ***	genMinus  1009
;; ***	aopForSym 393
;;	404 sym->rname = _cnt, size = 1
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
;;	1052  _cnt   offset=0
	.line	19; "tmr0.c"	cnt=cnt-1;	//decrementa contagem
	BANKSEL	_cnt
	DECF	_cnt,F
;; ***	pic14_getDataSize  1492
;; ***	pic14_getDataSize  1492
;; ***	pic14_getDataSize  1492
;; ***	addSign  973
;; genarith.c:974:addSign *{*
;; gen.c:2327:resultRemat *{*
;; gen.c:7965:genIfx *{*
;; ***	genIfx  7966
;; ***	aopForSym 393
;;	404 sym->rname = _cnt, size = 1
;; ***	pic14_toBoolean  1566
; >>> gen.c:1572:pic14_toBoolean
	.line	21; "tmr0.c"	if(cnt == 0)	//quando contagem = 0;
	MOVLW	0x00
; >>> gen.c:1580:pic14_toBoolean
;;	1036
;;	1052  _cnt   offset=0
	IORWF	_cnt,W
; >>> gen.c:8011:genIfx
	BTFSS	STATUS,2
; >>> gen.c:8012:genIfx
;; ***	popGetLabel  key=2, label offset 4
	GOTO	_00106_DS_
;; gen.c:2327:resultRemat *{*
;; gen.c:4410:ifxForOp *{*
;; ***	ifxForOp  4412
;; gen.c:5133:genXor *{*
;; ***	genXor  5134
;; ***	aopForSym 393
;;	404 sym->rname = _PORTB, size = 1
;;	654
; >>> gen.c:5251:genXor
	.line	23; "tmr0.c"	PORTB= PORTB ^0x0FF;	//troca estado PORTB
	MOVLW	0xff
; >>> gen.c:5252:genXor
;;	1036
;;	1052  _PORTB   offset=0
	BANKSEL	_PORTB
	XORWF	_PORTB,F
;; gen.c:2327:resultRemat *{*
;; gen.c:8139:genAssign *{*
;; ***	genAssign  8140
;; ***	aopForSym 393
;;	404 sym->rname = _cnt, size = 1
;; 	line = 8149 result AOP_DIR=_cnt, size=1, left -=-, size=0, right AOP_LIT=0x14, size=1
;; ***	genAssign  8241
; >>> gen.c:8246:genAssign
	.line	24; "tmr0.c"	cnt=_cnt_ini;		//reinicia contador
	MOVLW	0x14
; >>> gen.c:8248:genAssign
;;	1036
;;	1052  _cnt   offset=0
	BANKSEL	_cnt
	MOVWF	_cnt
;; gen.c:2327:resultRemat *{*
;; gen.c:2686:genLabel *{*
;; ***	genLabel  2689
;; gen.c:2327:resultRemat *{*
;; gen.c:8139:genAssign *{*
;; ***	genAssign  8140
;; ***	aopForSym 393
;;	404 sym->rname = _TMR0, size = 1
;; 	line = 8149 result AOP_DIR=_TMR0, size=1, left -=-, size=0, right AOP_LIT=0x37, size=1
;; ***	genAssign  8241
; >>> gen.c:8246:genAssign
_00106_DS_
	.line	27; "tmr0.c"	TMR0=_tmr0_ini;	//reinicia contagem
	MOVLW	0x37
; >>> gen.c:8248:genAssign
;;	1036
;;	1052  _TMR0   offset=0
	BANKSEL	_TMR0
	MOVWF	_TMR0
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
	.line	28; "tmr0.c"	T0IF=0;		// reseta flag TMR0
	BCF	_INTCON_bits,2
;; gen.c:2327:resultRemat *{*
;; gen.c:2686:genLabel *{*
;; ***	genLabel  2689
;; gen.c:2327:resultRemat *{*
;; gen.c:2524:genEndFunction *{*
;; ***	genEndFunction  2526
; >>> gen.c:2597:genEndFunction
	BANKSEL	___sdcc_saved_fsr
	MOVF	___sdcc_saved_fsr,W
; >>> gen.c:2598:genEndFunction
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
code_tmr0	code
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
;; ***	genFunction  2374 curr label offset=4previous max_key=2 
_main	;Function start
; 2 exit points
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
	.line	34; "tmr0.c"	INTCON=0;        //Deliga interrupcoes
	BANKSEL	_INTCON
	CLRF	_INTCON
;; gen.c:2327:resultRemat *{*
;; gen.c:8139:genAssign *{*
;; ***	genAssign  8140
;; ***	aopForSym 393
;;	404 sym->rname = _CMCON, size = 1
;; 	line = 8149 result AOP_DIR=_CMCON, size=1, left -=-, size=0, right AOP_LIT=0x07, size=1
;; ***	genAssign  8241
; >>> gen.c:8246:genAssign
	.line	36; "tmr0.c"	CMCON=0x07;	//Desliga comparadores analogicos
	MOVLW	0x07
; >>> gen.c:8248:genAssign
;;	1036
;;	1052  _CMCON   offset=0
	MOVWF	_CMCON
;; gen.c:2327:resultRemat *{*
;; gen.c:8139:genAssign *{*
;; ***	genAssign  8140
;; ***	aopForSym 393
;;	404 sym->rname = _TRISA, size = 1
;; 	line = 8149 result AOP_DIR=_TRISA, size=1, left -=-, size=0, right AOP_LIT=0xfe, size=1
;; ***	genAssign  8241
; >>> gen.c:8246:genAssign
	.line	37; "tmr0.c"	TRISA=0xFE;	//configura PORTA
	MOVLW	0xfe
; >>> gen.c:8248:genAssign
;;	1036
;;	1052  _TRISA   offset=0
	BANKSEL	_TRISA
	MOVWF	_TRISA
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
	.line	38; "tmr0.c"	TRISB=0x00;	//configura PORTB
	CLRF	_TRISB
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
	.line	41; "tmr0.c"	T0CS=0;		// Seleciona clock do tmr0 como clock_cpu/4 
	BCF	_OPTION_REG_bits,5
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
	.line	42; "tmr0.c"	PSA=0;		// Usa pre-scaler
	BCF	_OPTION_REG_bits,3
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
;; 	line = 7743 result AOP_PCODE=_OPTION_REG_bits, size=2, left -=-, size=0, right AOP_LIT=0x01, size=1
;; gen.c:7472:genPackBits *{*
;; ***	genPackBits  7473
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_OPTION_REG_bits
; >>> gen.c:7498:genPackBits
	.line	44; "tmr0.c"	PS2=1;		//111 = clk / 256 
	BSF	_OPTION_REG_bits,2
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
;; 	line = 7743 result AOP_PCODE=_OPTION_REG_bits, size=2, left -=-, size=0, right AOP_LIT=0x01, size=1
;; gen.c:7472:genPackBits *{*
;; ***	genPackBits  7473
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_OPTION_REG_bits
; >>> gen.c:7498:genPackBits
	.line	45; "tmr0.c"	PS1=1;
	BSF	_OPTION_REG_bits,1
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
;; 	line = 7743 result AOP_PCODE=_OPTION_REG_bits, size=2, left -=-, size=0, right AOP_LIT=0x01, size=1
;; gen.c:7472:genPackBits *{*
;; ***	genPackBits  7473
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_OPTION_REG_bits
; >>> gen.c:7498:genPackBits
	.line	46; "tmr0.c"	PS0=1;
	BSF	_OPTION_REG_bits,0
;; gen.c:2327:resultRemat *{*
;; gen.c:8139:genAssign *{*
;; ***	genAssign  8140
;; ***	aopForSym 393
;;	404 sym->rname = _TMR0, size = 1
;; 	line = 8149 result AOP_DIR=_TMR0, size=1, left -=-, size=0, right AOP_LIT=0x37, size=1
;; ***	genAssign  8241
; >>> gen.c:8246:genAssign
	.line	48; "tmr0.c"	TMR0=_tmr0_ini;	//incicia timer com 55, conta de 55 a 255 (200)
	MOVLW	0x37
; >>> gen.c:8248:genAssign
;;	1036
;;	1052  _TMR0   offset=0
	BANKSEL	_TMR0
	MOVWF	_TMR0
;; gen.c:2327:resultRemat *{*
;; gen.c:8139:genAssign *{*
;; ***	genAssign  8140
;; ***	aopForSym 393
;;	404 sym->rname = _cnt, size = 1
;; 	line = 8149 result AOP_DIR=_cnt, size=1, left -=-, size=0, right AOP_LIT=0x14, size=1
;; ***	genAssign  8241
; >>> gen.c:8246:genAssign
	.line	50; "tmr0.c"	cnt=_cnt_ini;	//variavel auxiliar
	MOVLW	0x14
; >>> gen.c:8248:genAssign
;;	1036
;;	1052  _cnt   offset=0
	BANKSEL	_cnt
	MOVWF	_cnt
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
;; 	line = 7743 result AOP_PCODE=_INTCON_bits, size=2, left -=-, size=0, right AOP_LIT=0x01, size=1
;; gen.c:7472:genPackBits *{*
;; ***	genPackBits  7473
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_INTCON_bits
; >>> gen.c:7498:genPackBits
	.line	55; "tmr0.c"	GIE=1;		//liga interrupcoes
	BANKSEL	_INTCON_bits
	BSF	_INTCON_bits,7
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
;; 	line = 7743 result AOP_PCODE=_INTCON_bits, size=2, left -=-, size=0, right AOP_LIT=0x01, size=1
;; gen.c:7472:genPackBits *{*
;; ***	genPackBits  7473
;;	879: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_INTCON_bits
; >>> gen.c:7498:genPackBits
	.line	56; "tmr0.c"	T0IE=1;		//liga interrupcao do TMR0
	BSF	_INTCON_bits,5
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
	.line	57; "tmr0.c"	T0IF=0;		//Apaga flag de interrupcao	
	BCF	_INTCON_bits,2
;; gen.c:2327:resultRemat *{*
;; gen.c:8139:genAssign *{*
;; ***	genAssign  8140
;; ***	aopForSym 393
;;	404 sym->rname = _PORTB, size = 1
;; 	line = 8149 result AOP_DIR=_PORTB, size=1, left -=-, size=0, right AOP_LIT=0xff, size=1
;; ***	genAssign  8241
; >>> gen.c:8246:genAssign
	.line	59; "tmr0.c"	PORTB=0xFF;
	MOVLW	0xff
; >>> gen.c:8248:genAssign
;;	1036
;;	1052  _PORTB   offset=0
	MOVWF	_PORTB
;; gen.c:2327:resultRemat *{*
;; gen.c:2686:genLabel *{*
;; ***	genLabel  2689
;; gen.c:2327:resultRemat *{*
;; gen.c:2703:genGoto *{*
; >>> gen.c:2705:genGoto
;; ***	popGetLabel  key=2, label offset 10
_00112_DS_
	.line	61; "tmr0.c"	while(1)	//espera interrupcoes
	GOTO	_00112_DS_
;; gen.c:2327:resultRemat *{*
;; gen.c:2686:genLabel *{*
;; ***	genLabel  2689
;; gen.c:2327:resultRemat *{*
;; gen.c:2524:genEndFunction *{*
;; ***	genEndFunction  2526
	RETURN	
; exit point of _main


;	code size estimation:
;	   53+   11 =    64 instructions (  150 byte)

	end
