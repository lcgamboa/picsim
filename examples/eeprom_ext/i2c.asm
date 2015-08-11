;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 2.9.0 #5416 (Jan 10 2010) (UNIX)
; This file was generated Thu Jun 16 17:51:45 2011
;--------------------------------------------------------
; PIC port for the 14-bit core
;--------------------------------------------------------
	.file	"i2c.c"
	list	p=16f877a
	radix dec
	include "p16f877a.inc"
;--------------------------------------------------------
; external declarations
;--------------------------------------------------------
	extern	_i2c_acktst
	extern	_ADCON0_bits
	extern	_ADCON1_bits
	extern	_CCP1CON_bits
	extern	_CCP2CON_bits
	extern	_CMCON_bits
	extern	_CVRCON_bits
	extern	_EECON1_bits
	extern	_INTCON_bits
	extern	_OPTION_REG_bits
	extern	_PCON_bits
	extern	_PIE1_bits
	extern	_PIE2_bits
	extern	_PIR1_bits
	extern	_PIR2_bits
	extern	_PORTA_bits
	extern	_PORTB_bits
	extern	_PORTC_bits
	extern	_PORTD_bits
	extern	_PORTE_bits
	extern	_RCSTA_bits
	extern	_SSPCON_bits
	extern	_SSPCON2_bits
	extern	_SSPSTAT_bits
	extern	_STATUS_bits
	extern	_T1CON_bits
	extern	_T2CON_bits
	extern	_TRISA_bits
	extern	_TRISB_bits
	extern	_TRISC_bits
	extern	_TRISD_bits
	extern	_TRISE_bits
	extern	_TXSTA_bits
	extern	_INDF
	extern	_TMR0
	extern	_PCL
	extern	_STATUS
	extern	_FSR
	extern	_PORTA
	extern	_PORTB
	extern	_PORTC
	extern	_PORTD
	extern	_PORTE
	extern	_PCLATH
	extern	_INTCON
	extern	_PIR1
	extern	_PIR2
	extern	_TMR1L
	extern	_TMR1H
	extern	_T1CON
	extern	_TMR2
	extern	_T2CON
	extern	_SSPBUF
	extern	_SSPCON
	extern	_CCPR1L
	extern	_CCPR1H
	extern	_CCP1CON
	extern	_RCSTA
	extern	_TXREG
	extern	_RCREG
	extern	_CCPR2L
	extern	_CCPR2H
	extern	_CCP2CON
	extern	_ADRESH
	extern	_ADCON0
	extern	_OPTION_REG
	extern	_TRISA
	extern	_TRISB
	extern	_TRISC
	extern	_TRISD
	extern	_TRISE
	extern	_PIE1
	extern	_PIE2
	extern	_PCON
	extern	_SSPCON2
	extern	_PR2
	extern	_SSPADD
	extern	_SSPSTAT
	extern	_TXSTA
	extern	_SPBRG
	extern	_CMCON
	extern	_CVRCON
	extern	_ADRESL
	extern	_ADCON1
	extern	_EEDATA
	extern	_EEADR
	extern	_EEDATH
	extern	_EEADRH
	extern	_EECON1
	extern	_EECON2

	extern PSAVE
	extern SSAVE
	extern WSAVE
	extern STK12
	extern STK11
	extern STK10
	extern STK09
	extern STK08
	extern STK07
	extern STK06
	extern STK05
	extern STK04
	extern STK03
	extern STK02
	extern STK01
	extern STK00
;--------------------------------------------------------
; global declarations
;--------------------------------------------------------
	global	_i2c_rb
	global	_i2c_wb
	global	_i2c_stop
	global	_i2c_start
	global	_i2c_init
	global	_delay

;--------------------------------------------------------
; global definitions
;--------------------------------------------------------
;--------------------------------------------------------
; absolute symbol definitions
;--------------------------------------------------------
;--------------------------------------------------------
; compiler-defined variables
;--------------------------------------------------------
UDL_i2c_0	udata
r0x1005	res	1
r0x1006	res	1
r0x1007	res	1
r0x1008	res	1
r0x1009	res	1
r0x1000	res	1
r0x1001	res	1
r0x1002	res	1
r0x1003	res	1
r0x1004	res	1
;--------------------------------------------------------
; initialized data
;--------------------------------------------------------
;--------------------------------------------------------
; overlayable items in internal ram 
;--------------------------------------------------------
;	udata_ovr
;--------------------------------------------------------
; code
;--------------------------------------------------------
code_i2c	code
;***
;  pBlock Stats: dbName = C
;***
;entry:  _i2c_rb	;Function start
; 2 exit points
;has an exit
;functions called:
;   _delay
;   _delay
;   _delay
;   _delay
;   _delay
;   _delay
;5 compiler assigned registers:
;   r0x1000
;   r0x1001
;   r0x1002
;   r0x1003
;   r0x1004
;; Starting pCode block
;; gen.c:2261:resultRemat *{*
;; gen.c:2597:genLabel *{*
;; ***	genLabel  2600
;; gen.c:2261:resultRemat *{*
;; gen.c:2283:genFunction *{*
;; ***	genFunction  2285 curr label offset=20previous max_key=14 
_i2c_rb	;Function start
; 2 exit points
;; gen.c:2261:resultRemat *{*
;; gen.c:6332:genAssign *{*
;; ***	genAssign  6333
;;	721 register type nRegs=1
;; 	line = 6342 result AOP_REG=r0x104D, size=1, left -=-, size=0, right AOP_LIT=0x00, size=1
;; ***	genAssign  6434
; >>> gen.c:6443:genAssign
;;	1109 rIdx = r0x104D 
	.line	82; "i2c.c"	unsigned char ret=0;
	BANKSEL	r0x1000
	CLRF	r0x1000
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:6117:genPointerSet *{*
;; ***	genPointerSet  6118
;; gen.c:5945:genNearPointerSet *{*
;; ***	genNearPointerSet  5946
;;	641
;;	aopForRemat 425
;;	446: rname _PORTC_bits, val 0, const = 0
;; ***	genNearPointerSet  5963
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTC_bits
;; 	line = 5965 result AOP_PCODE=_PORTC_bits, size=2, left -=-, size=0, right AOP_LIT=0x00, size=1
;; gen.c:5694:genPackBits *{*
;; ***	genPackBits  5695
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTC_bits
; >>> gen.c:5720:genPackBits
	.line	84; "i2c.c"	ICLK=0;
	BANKSEL	_PORTC_bits
	BCF	_PORTC_bits,3
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:6117:genPointerSet *{*
;; ***	genPointerSet  6118
;; gen.c:5945:genNearPointerSet *{*
;; ***	genNearPointerSet  5946
;;	641
;;	aopForRemat 425
;;	446: rname _TRISC_bits, val 0, const = 0
;; ***	genNearPointerSet  5963
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_TRISC_bits
;; 	line = 5965 result AOP_PCODE=_TRISC_bits, size=2, left -=-, size=0, right AOP_LIT=0x01, size=1
;; gen.c:5694:genPackBits *{*
;; ***	genPackBits  5695
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_TRISC_bits
; >>> gen.c:5720:genPackBits
	.line	85; "i2c.c"	TIDAT=1;
	BANKSEL	_TRISC_bits
	BSF	_TRISC_bits,4
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:6117:genPointerSet *{*
;; ***	genPointerSet  6118
;; gen.c:5945:genNearPointerSet *{*
;; ***	genNearPointerSet  5946
;;	641
;;	aopForRemat 425
;;	446: rname _PORTC_bits, val 0, const = 0
;; ***	genNearPointerSet  5963
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTC_bits
;; 	line = 5965 result AOP_PCODE=_PORTC_bits, size=2, left -=-, size=0, right AOP_LIT=0x01, size=1
;; gen.c:5694:genPackBits *{*
;; ***	genPackBits  5695
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTC_bits
; >>> gen.c:5720:genPackBits
	.line	86; "i2c.c"	IDAT=1;
	BANKSEL	_PORTC_bits
	BSF	_PORTC_bits,4
;; gen.c:2261:resultRemat *{*
;; gen.c:6332:genAssign *{*
;; ***	genAssign  6333
;;	721 register type nRegs=1
;; 	line = 6342 result AOP_REG=r0x104E, size=1, left -=-, size=0, right AOP_LIT=0x00, size=1
;; ***	genAssign  6434
; >>> gen.c:6443:genAssign
;;	1109 rIdx = r0x104E 
	.line	87; "i2c.c"	for(i=0;i<8;i++)
	BANKSEL	r0x1001
	CLRF	r0x1001
;; gen.c:2261:resultRemat *{*
;; gen.c:2597:genLabel *{*
;; ***	genLabel  2600
;; gen.c:2261:resultRemat *{*
;; gen.c:3504:ifxForOp *{*
;; ***	ifxForOp  3506
;; gen.c:3357:genCmpLt *{*
;; ***	genCmpLt  3358
;;	721 register type nRegs=1
;; gen.c:3126:genCmp *{*
;signed compare: left < lit(0x8=8), size=1, mask=ff
;; ***	mov2w  1356  offset=0
; >>> gen.c:1361:mov2w
;;	1109 rIdx = r0x104E 
_00139_DS_
	BANKSEL	r0x1001
	MOVF	r0x1001,W
; >>> gen.c:3250:genCmp
	ADDLW	0x80
; >>> gen.c:3251:genCmp
	ADDLW	0x78
;; gen.c:3073:genSkipc *{*
; >>> gen.c:3078:genSkipc
	BTFSC	STATUS,0
; >>> gen.c:3082:genSkipc
;; ***	popGetLabel  key=4, label offset 38
	GOTO	_00142_DS_
;genSkipc:3083: created from rifx:0xbfa62ea4
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:6117:genPointerSet *{*
;; ***	genPointerSet  6118
;; gen.c:5945:genNearPointerSet *{*
;; ***	genNearPointerSet  5946
;;	641
;;	aopForRemat 425
;;	446: rname _PORTC_bits, val 0, const = 0
;; ***	genNearPointerSet  5963
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTC_bits
;; 	line = 5965 result AOP_PCODE=_PORTC_bits, size=2, left -=-, size=0, right AOP_LIT=0x01, size=1
;; gen.c:5694:genPackBits *{*
;; ***	genPackBits  5695
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTC_bits
; >>> gen.c:5720:genPackBits
	.line	89; "i2c.c"	ICLK=1;
	BANKSEL	_PORTC_bits
	BSF	_PORTC_bits,3
;; gen.c:2261:resultRemat *{*
;; gen.c:2030:genCall *{*
;; ***	genCall  2032
;; gen.c:1765:saveRegisters *{*
;; ***	saveRegisters  1767
; >>> gen.c:2118:genCall
	.line	90; "i2c.c"	delay();
	CALL	_delay
;; gen.c:1809:unsaveRegisters *{*
;; ***	unsaveRegisters  1811
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:5608:genPointerGet *{*
;; ***	genPointerGet  5609
;; gen.c:5397:genNearPointerGet *{*
;; ***	genNearPointerGet  5398
;;	641
;;	aopForRemat 425
;;	446: rname _PORTC_bits, val 0, const = 0
;; ***	genNearPointerGet  5414
;;	721 register type nRegs=1
;; gen.c:3504:ifxForOp *{*
;; ***	ifxForOp  3506
;; NULL :(	3526
;; gen.c:5240:genUnpackBits *{*
;; ***	genUnpackBits  5241
; >>> gen.c:5264:genUnpackBits
;;	1109 rIdx = r0x104F 
	.line	91; "i2c.c"	ret|=(IDAT<<(7-i));
	BANKSEL	r0x1002
	CLRF	r0x1002
; >>> gen.c:5269:genUnpackBits
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTC_bits
	BANKSEL	_PORTC_bits
	BTFSS	_PORTC_bits,4
	GOTO	_00001_DS_
; >>> gen.c:5289:genUnpackBits
;;	1109 rIdx = r0x104F 
	BANKSEL	r0x1002
	INCF	r0x1002,F
;; ***	pic14_getDataSize  1426
;; ***	addSign  797
;; genarith.c:798:addSign *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:3504:ifxForOp *{*
;; ***	ifxForOp  3506
;; NULL :(	3526
;; gen.c:6695:genDjnz *{*
;; ***	genDjnz  6696
;; genarith.c:832:genMinus *{*
;; ***	genMinus  833
;;	721 register type nRegs=1
;;	721 register type nRegs=1
;; 	result AOP_REG, left AOP_LIT, right AOP_REG
;; ***	pic14_getDataSize  1426
;; ***	pic14_getDataSize  1426
;; left is lit	line 950 result AOP_REG, left AOP_LIT, right AOP_REG
;; ***	mov2w  1356  offset=0
; >>> gen.c:1361:mov2w
;;	1109 rIdx = r0x104E 
_00001_DS_
	BANKSEL	r0x1001
	MOVF	r0x1001,W
; >>> genarith.c:989:genMinus
	SUBLW	0x07
; >>> genarith.c:990:genMinus
;;	1109 rIdx = r0x1050 
	MOVWF	r0x1003
;; gen.c:2261:resultRemat *{*
;; gen.c:4988:genGenericShift *{*
;; ***	genGenericShift  4992
;;	721 register type nRegs=1
;;	721 register type nRegs=1
;;	721 register type nRegs=1
;; ***	mov2w  1356  offset=0
; >>> gen.c:1361:mov2w
;;	1109 rIdx = r0x104F 
	MOVF	r0x1002,W
; >>> gen.c:1367:movwf
;;	1109 rIdx = r0x1051 
	MOVWF	r0x1004
;; ***	pic14_getDataSize  1426
;; ***	addSign  797
;; genarith.c:798:addSign *{*
;; ***	mov2w  1356  offset=0
; >>> gen.c:1361:mov2w
;;	1109 rIdx = r0x1050 
	MOVF	r0x1003,W
; >>> gen.c:5058:genGenericShift
	BTFSC	r0x1003,7
; >>> gen.c:5059:genGenericShift
;; ***	popGetLabel  key=13, label offset 38
	GOTO	_00152_DS_
; >>> gen.c:5061:genGenericShift
	SUBLW	0x00
; >>> gen.c:5063:genGenericShift
	BTFSC	STATUS,2
; >>> gen.c:5064:genGenericShift
;; ***	popGetLabel  key=12, label offset 38
	GOTO	_00150_DS_
;; gen.c:4944:genMultiAsm *{*
;; ***	genMultiAsm  4945
; >>> gen.c:4958:genMultiAsm
;;	1109 rIdx = r0x1051 
_00149_DS_
	BANKSEL	r0x1004
	RLF	r0x1004,F
; >>> gen.c:5069:genGenericShift
	ADDLW	0x01
; >>> gen.c:5070:genGenericShift
	BTFSS	STATUS,0
; >>> gen.c:5071:genGenericShift
;; ***	popGetLabel  key=11, label offset 38
	GOTO	_00149_DS_
; >>> gen.c:5080:genGenericShift
;; ***	popGetLabel  key=12, label offset 38
	GOTO	_00150_DS_
;; gen.c:4970:loadSignToC *{*
; >>> gen.c:4973:loadSignToC
_00152_DS_
	BCF	STATUS,0
; >>> gen.c:4974:loadSignToC
	BANKSEL	r0x1004
	BTFSC	r0x1004,7
; >>> gen.c:4975:loadSignToC
	BSF	STATUS,0
;; gen.c:4944:genMultiAsm *{*
;; ***	genMultiAsm  4945
; >>> gen.c:4958:genMultiAsm
;;	1109 rIdx = r0x1051 
	RRF	r0x1004,F
; >>> gen.c:5089:genGenericShift
	ADDLW	0x01
; >>> gen.c:5090:genGenericShift
	BTFSS	STATUS,0
; >>> gen.c:5091:genGenericShift
;; ***	popGetLabel  key=14, label offset 38
	GOTO	_00152_DS_
;; gen.c:2261:resultRemat *{*
;; gen.c:3504:ifxForOp *{*
;; ***	ifxForOp  3506
;; NULL :(	3526
;; gen.c:3981:genOr *{*
;; ***	genOr  3982
;;	721 register type nRegs=1
;;	721 register type nRegs=1
;;	606
;; 	line = 3988 result AOP_REG=r0x104D, size=1, left AOP_REG=r0x104D, size=1, right AOP_REG=r0x1051, size=1
;; 	line = 4013 result AOP_REG=r0x104D, size=1, left AOP_REG=r0x104D, size=1, right AOP_REG=r0x1051, size=1
; >>> gen.c:4155:genOr
;;	1109 rIdx = r0x1051 
_00150_DS_
	BANKSEL	r0x1004
	MOVF	r0x1004,W
; >>> gen.c:4156:genOr
;;	1109 rIdx = r0x104D 
	IORWF	r0x1000,F
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:6117:genPointerSet *{*
;; ***	genPointerSet  6118
;; gen.c:5945:genNearPointerSet *{*
;; ***	genNearPointerSet  5946
;;	641
;;	aopForRemat 425
;;	446: rname _PORTC_bits, val 0, const = 0
;; ***	genNearPointerSet  5963
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTC_bits
;; 	line = 5965 result AOP_PCODE=_PORTC_bits, size=2, left -=-, size=0, right AOP_LIT=0x00, size=1
;; gen.c:5694:genPackBits *{*
;; ***	genPackBits  5695
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTC_bits
; >>> gen.c:5720:genPackBits
	.line	92; "i2c.c"	ICLK=0;
	BANKSEL	_PORTC_bits
	BCF	_PORTC_bits,3
;; gen.c:2261:resultRemat *{*
;; ***	genPlus  547
;; genarith.c:548:genPlus *{*
;;	721 register type nRegs=1
;;	606
;; 	line = 554 result AOP_REG=r0x104E, size=1, left AOP_REG=r0x104E, size=1, right AOP_LIT=0x01, size=1
;; ***	pic14_getDataSize  1426
;; genarith.c:142:genPlusIncr *{*
;; ***	genPlusIncr  144
;; 	result AOP_REG, left AOP_REG, right AOP_LIT
;; 	genPlusIncr  156
; >>> genarith.c:168:genPlusIncr
;;	1109 rIdx = r0x104E 
	.line	87; "i2c.c"	for(i=0;i<8;i++)
	BANKSEL	r0x1001
	INCF	r0x1001,F
;; gen.c:2261:resultRemat *{*
;; gen.c:2614:genGoto *{*
; >>> gen.c:2616:genGoto
;; ***	popGetLabel  key=1, label offset 38
	GOTO	_00139_DS_
;; gen.c:2261:resultRemat *{*
;; gen.c:2597:genLabel *{*
;; ***	genLabel  2600
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:6117:genPointerSet *{*
;; ***	genPointerSet  6118
;; gen.c:5945:genNearPointerSet *{*
;; ***	genNearPointerSet  5946
;;	641
;;	aopForRemat 425
;;	446: rname _TRISC_bits, val 0, const = 0
;; ***	genNearPointerSet  5963
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_TRISC_bits
;; 	line = 5965 result AOP_PCODE=_TRISC_bits, size=2, left -=-, size=0, right AOP_LIT=0x00, size=1
;; gen.c:5694:genPackBits *{*
;; ***	genPackBits  5695
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_TRISC_bits
; >>> gen.c:5720:genPackBits
_00142_DS_
	.line	94; "i2c.c"	TIDAT=0;
	BANKSEL	_TRISC_bits
	BCF	_TRISC_bits,4
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:6117:genPointerSet *{*
;; ***	genPointerSet  6118
;; gen.c:5945:genNearPointerSet *{*
;; ***	genNearPointerSet  5946
;;	641
;;	aopForRemat 425
;;	446: rname _PORTC_bits, val 0, const = 0
;; ***	genNearPointerSet  5963
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTC_bits
;; 	line = 5965 result AOP_PCODE=_PORTC_bits, size=2, left -=-, size=0, right AOP_LIT=0x00, size=1
;; gen.c:5694:genPackBits *{*
;; ***	genPackBits  5695
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTC_bits
; >>> gen.c:5720:genPackBits
	.line	95; "i2c.c"	IDAT=0;
	BANKSEL	_PORTC_bits
	BCF	_PORTC_bits,4
;; gen.c:2261:resultRemat *{*
;; gen.c:2030:genCall *{*
;; ***	genCall  2032
;; gen.c:1765:saveRegisters *{*
;; ***	saveRegisters  1767
; >>> gen.c:2118:genCall
	.line	96; "i2c.c"	delay();
	CALL	_delay
;; gen.c:1809:unsaveRegisters *{*
;; ***	unsaveRegisters  1811
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:6117:genPointerSet *{*
;; ***	genPointerSet  6118
;; gen.c:5945:genNearPointerSet *{*
;; ***	genNearPointerSet  5946
;;	641
;;	aopForRemat 425
;;	446: rname _PORTC_bits, val 0, const = 0
;; ***	genNearPointerSet  5963
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTC_bits
;; 	line = 5965 result AOP_PCODE=_PORTC_bits, size=2, left -=-, size=0, right AOP_LIT=0x01, size=1
;; gen.c:5694:genPackBits *{*
;; ***	genPackBits  5695
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTC_bits
; >>> gen.c:5720:genPackBits
	.line	97; "i2c.c"	ICLK=1;
	BANKSEL	_PORTC_bits
	BSF	_PORTC_bits,3
;; gen.c:2261:resultRemat *{*
;; gen.c:2030:genCall *{*
;; ***	genCall  2032
;; gen.c:1765:saveRegisters *{*
;; ***	saveRegisters  1767
; >>> gen.c:2118:genCall
	.line	98; "i2c.c"	delay();
	CALL	_delay
;; gen.c:1809:unsaveRegisters *{*
;; ***	unsaveRegisters  1811
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:6117:genPointerSet *{*
;; ***	genPointerSet  6118
;; gen.c:5945:genNearPointerSet *{*
;; ***	genNearPointerSet  5946
;;	641
;;	aopForRemat 425
;;	446: rname _PORTC_bits, val 0, const = 0
;; ***	genNearPointerSet  5963
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTC_bits
;; 	line = 5965 result AOP_PCODE=_PORTC_bits, size=2, left -=-, size=0, right AOP_LIT=0x00, size=1
;; gen.c:5694:genPackBits *{*
;; ***	genPackBits  5695
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTC_bits
; >>> gen.c:5720:genPackBits
	.line	99; "i2c.c"	ICLK=0;
	BANKSEL	_PORTC_bits
	BCF	_PORTC_bits,3
;; gen.c:2261:resultRemat *{*
;; gen.c:2561:genRet *{*
;; ***	genRet  2563
;;	721 register type nRegs=1
;; gen.c:1324:mov2w_op *{*
;; ***	mov2w  1356  offset=0
; >>> gen.c:1361:mov2w
;;	1109 rIdx = r0x104D 
	.line	101; "i2c.c"	return ret;
	BANKSEL	r0x1000
	MOVF	r0x1000,W
;; gen.c:2261:resultRemat *{*
;; gen.c:2597:genLabel *{*
;; ***	genLabel  2600
;; gen.c:2261:resultRemat *{*
;; gen.c:2435:genEndFunction *{*
;; ***	genEndFunction  2437
	RETURN	
; exit point of _i2c_rb

;***
;  pBlock Stats: dbName = C
;***
;entry:  _i2c_wb	;Function start
; 2 exit points
;has an exit
;functions called:
;   _delay
;   _delay
;   _delay
;   _delay
;   _delay
;   _delay
;5 compiler assigned registers:
;   r0x1005
;   r0x1006
;   r0x1007
;   r0x1008
;   r0x1009
;; Starting pCode block
;; gen.c:2261:resultRemat *{*
;; gen.c:2597:genLabel *{*
;; ***	genLabel  2600
;; gen.c:2261:resultRemat *{*
;; gen.c:2283:genFunction *{*
;; ***	genFunction  2285 curr label offset=16previous max_key=0 
_i2c_wb	;Function start
; 2 exit points
;; gen.c:2261:resultRemat *{*
;; gen.c:6739:genReceive *{*
;; ***	genReceive  6740
;;	721 register type nRegs=1
;; gen.c:1866:assignResultValue *{*
;; ***	assignResultValue  1868
;; 	line = 1870 result -=-, size=0, left AOP_REG=r0x1048, size=1, right -=-, size=0
; >>> gen.c:1367:movwf
;;	1109 rIdx = r0x1048 
	.line	61; "i2c.c"	void i2c_wb(unsigned char val)
	BANKSEL	r0x1005
	MOVWF	r0x1005
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:6117:genPointerSet *{*
;; ***	genPointerSet  6118
;; gen.c:5945:genNearPointerSet *{*
;; ***	genNearPointerSet  5946
;;	641
;;	aopForRemat 425
;;	446: rname _PORTC_bits, val 0, const = 0
;; ***	genNearPointerSet  5963
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTC_bits
;; 	line = 5965 result AOP_PCODE=_PORTC_bits, size=2, left -=-, size=0, right AOP_LIT=0x00, size=1
;; gen.c:5694:genPackBits *{*
;; ***	genPackBits  5695
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTC_bits
; >>> gen.c:5720:genPackBits
	.line	64; "i2c.c"	ICLK=0;
	BANKSEL	_PORTC_bits
	BCF	_PORTC_bits,3
;; gen.c:2261:resultRemat *{*
;; gen.c:6332:genAssign *{*
;; ***	genAssign  6333
;;	721 register type nRegs=1
;; 	line = 6342 result AOP_REG=r0x1049, size=1, left -=-, size=0, right AOP_LIT=0x00, size=1
;; ***	genAssign  6434
; >>> gen.c:6443:genAssign
;;	1109 rIdx = r0x1049 
	.line	65; "i2c.c"	for(i=0;i<8;i++)		
	BANKSEL	r0x1006
	CLRF	r0x1006
;; gen.c:2261:resultRemat *{*
;; gen.c:2597:genLabel *{*
;; ***	genLabel  2600
;; gen.c:2261:resultRemat *{*
;; gen.c:3504:ifxForOp *{*
;; ***	ifxForOp  3506
;; gen.c:3357:genCmpLt *{*
;; ***	genCmpLt  3358
;;	721 register type nRegs=1
;; gen.c:3126:genCmp *{*
;signed compare: left < lit(0x8=8), size=1, mask=ff
;; ***	mov2w  1356  offset=0
; >>> gen.c:1361:mov2w
;;	1109 rIdx = r0x1049 
_00121_DS_
	BANKSEL	r0x1006
	MOVF	r0x1006,W
; >>> gen.c:3250:genCmp
	ADDLW	0x80
; >>> gen.c:3251:genCmp
	ADDLW	0x78
;; gen.c:3073:genSkipc *{*
; >>> gen.c:3078:genSkipc
	BTFSC	STATUS,0
; >>> gen.c:3082:genSkipc
;; ***	popGetLabel  key=4, label offset 20
	GOTO	_00124_DS_
;genSkipc:3083: created from rifx:0xbfa62ea4
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:6521:genCast *{*
;; ***	genCast  6522
;;	721 register type nRegs=1
;;	721 register type nRegs=2
;; 	line = 6530 result AOP_REG=r0x104A, size=2, left -=-, size=0, right AOP_REG=r0x1049, size=1
; >>> gen.c:6676:genCast
;;	1109 rIdx = r0x1049 
	.line	67; "i2c.c"	IDAT=((val>>(7-i))& 0x01);
	MOVF	r0x1006,W
; >>> gen.c:6677:genCast
;;	1109 rIdx = r0x104A 
	MOVWF	r0x1007
;; ***	pic14_getDataSize  1426
;; ***	addSign  797
;; genarith.c:798:addSign *{*
; >>> genarith.c:804:addSign
;;	1109 rIdx = r0x104B 
	CLRF	r0x1008
; >>> genarith.c:805:addSign
	BTFSC	r0x1007,7
; >>> genarith.c:806:addSign
;;	1109 rIdx = r0x104B 
	DECF	r0x1008,F
;; gen.c:2261:resultRemat *{*
;; gen.c:3504:ifxForOp *{*
;; ***	ifxForOp  3506
;; NULL :(	3526
;; gen.c:6695:genDjnz *{*
;; ***	genDjnz  6696
;; genarith.c:832:genMinus *{*
;; ***	genMinus  833
;;	721 register type nRegs=2
;;	721 register type nRegs=2
;; 	result AOP_REG, left AOP_LIT, right AOP_REG
;; ***	pic14_getDataSize  1426
;; ***	pic14_getDataSize  1426
;; left is lit	line 950 result AOP_REG, left AOP_LIT, right AOP_REG
;; ***	mov2w  1356  offset=0
; >>> gen.c:1361:mov2w
;;	1109 rIdx = r0x104A 
	MOVF	r0x1007,W
; >>> genarith.c:989:genMinus
	SUBLW	0x07
; >>> genarith.c:990:genMinus
;;	1109 rIdx = r0x104A 
	MOVWF	r0x1007
;; ***	mov2w  1356  offset=1
; >>> gen.c:1361:mov2w
;;	1109 rIdx = r0x104B 
	MOVF	r0x1008,W
; >>> genarith.c:1085:genMinus
	BTFSS	STATUS,0
; >>> genarith.c:1086:genMinus
;;	1109 rIdx = r0x104B 
	INCF	r0x1008,W
; >>> genarith.c:1089:genMinus
	SUBLW	0x00
; >>> genarith.c:1090:genMinus
;;	1109 rIdx = r0x104B 
	MOVWF	r0x1008
;; gen.c:2261:resultRemat *{*
;; gen.c:4988:genGenericShift *{*
;; ***	genGenericShift  4992
;;	721 register type nRegs=2
;;	721 register type nRegs=1
;;	721 register type nRegs=1
;; ***	mov2w  1356  offset=0
; >>> gen.c:1361:mov2w
;;	1109 rIdx = r0x1048 
	MOVF	r0x1005,W
; >>> gen.c:1367:movwf
;;	1109 rIdx = r0x104C 
	MOVWF	r0x1009
;; ***	pic14_getDataSize  1426
;; ***	addSign  797
;; genarith.c:798:addSign *{*
;; ***	mov2w  1356  offset=0
; >>> gen.c:1361:mov2w
;;	1109 rIdx = r0x104A 
	MOVF	r0x1007,W
; >>> gen.c:5058:genGenericShift
	BTFSC	r0x1007,7
; >>> gen.c:5059:genGenericShift
;; ***	popGetLabel  key=13, label offset 20
	GOTO	_00133_DS_
; >>> gen.c:5061:genGenericShift
	SUBLW	0x00
; >>> gen.c:5063:genGenericShift
	BTFSC	STATUS,2
; >>> gen.c:5064:genGenericShift
;; ***	popGetLabel  key=12, label offset 20
	GOTO	_00132_DS_
;; gen.c:4944:genMultiAsm *{*
;; ***	genMultiAsm  4945
; >>> gen.c:4958:genMultiAsm
;;	1109 rIdx = r0x104C 
_00131_DS_
	BANKSEL	r0x1009
	RRF	r0x1009,F
; >>> gen.c:5069:genGenericShift
	ADDLW	0x01
; >>> gen.c:5070:genGenericShift
	BTFSS	STATUS,0
; >>> gen.c:5071:genGenericShift
;; ***	popGetLabel  key=11, label offset 20
	GOTO	_00131_DS_
; >>> gen.c:5080:genGenericShift
;; ***	popGetLabel  key=12, label offset 20
	GOTO	_00132_DS_
; >>> gen.c:5084:genGenericShift
_00133_DS_
	BCF	STATUS,0
;; gen.c:4944:genMultiAsm *{*
;; ***	genMultiAsm  4945
; >>> gen.c:4958:genMultiAsm
;;	1109 rIdx = r0x104C 
_00134_DS_
	BANKSEL	r0x1009
	RLF	r0x1009,F
; >>> gen.c:5089:genGenericShift
	ADDLW	0x01
; >>> gen.c:5090:genGenericShift
	BTFSS	STATUS,0
; >>> gen.c:5091:genGenericShift
;; ***	popGetLabel  key=14, label offset 20
	GOTO	_00134_DS_
;; gen.c:2261:resultRemat *{*
;; gen.c:3504:ifxForOp *{*
;; ***	ifxForOp  3506
;; NULL :(	3526
;; gen.c:3719:genAnd *{*
;; ***	genAnd  3720
;;	721 register type nRegs=1
;;	721 register type nRegs=1
;; 	line = 3754 result AOP_REG=r0x104A, size=1, left AOP_REG=r0x104C, size=1, right AOP_LIT=0x01, size=1
; >>> gen.c:3952:genAnd
_00132_DS_
	MOVLW	0x01
; >>> gen.c:3953:genAnd
;;	1109 rIdx = r0x104C 
	BANKSEL	r0x1009
	ANDWF	r0x1009,W
; >>> gen.c:3954:genAnd
;;	1109 rIdx = r0x104A 
	MOVWF	r0x1007
;; gen.c:2261:resultRemat *{*
;; gen.c:6117:genPointerSet *{*
;; ***	genPointerSet  6118
;; gen.c:5945:genNearPointerSet *{*
;; ***	genNearPointerSet  5946
;;	641
;;	aopForRemat 425
;;	446: rname _PORTC_bits, val 0, const = 0
;; ***	genNearPointerSet  5963
;;	721 register type nRegs=1
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTC_bits
;; 	line = 5965 result AOP_PCODE=_PORTC_bits, size=2, left -=-, size=0, right AOP_REG=r0x104A, size=1
;; gen.c:5694:genPackBits *{*
;; ***	genPackBits  5695
; >>> gen.c:5793:genPackBits
;;	1109 rIdx = r0x104A 
	RRF	r0x1007,W
; >>> gen.c:5794:genPackBits
	BTFSC	STATUS,0
	GOTO	_00002_DS_
; >>> gen.c:5795:genPackBits
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTC_bits
	BANKSEL	_PORTC_bits
	BCF	_PORTC_bits,4
; >>> gen.c:5796:genPackBits
_00002_DS_
	BTFSS	STATUS,0
	GOTO	_00003_DS_
; >>> gen.c:5797:genPackBits
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTC_bits
	BANKSEL	_PORTC_bits
	BSF	_PORTC_bits,4
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:6117:genPointerSet *{*
;; ***	genPointerSet  6118
;; gen.c:5945:genNearPointerSet *{*
;; ***	genNearPointerSet  5946
;;	641
;;	aopForRemat 425
;;	446: rname _PORTC_bits, val 0, const = 0
;; ***	genNearPointerSet  5963
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTC_bits
;; 	line = 5965 result AOP_PCODE=_PORTC_bits, size=2, left -=-, size=0, right AOP_LIT=0x01, size=1
;; gen.c:5694:genPackBits *{*
;; ***	genPackBits  5695
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTC_bits
; >>> gen.c:5720:genPackBits
_00003_DS_
	.line	68; "i2c.c"	ICLK=1;
	BANKSEL	_PORTC_bits
	BSF	_PORTC_bits,3
;; gen.c:2261:resultRemat *{*
;; gen.c:2030:genCall *{*
;; ***	genCall  2032
;; gen.c:1765:saveRegisters *{*
;; ***	saveRegisters  1767
; >>> gen.c:2118:genCall
	.line	69; "i2c.c"	delay();
	CALL	_delay
;; gen.c:1809:unsaveRegisters *{*
;; ***	unsaveRegisters  1811
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:6117:genPointerSet *{*
;; ***	genPointerSet  6118
;; gen.c:5945:genNearPointerSet *{*
;; ***	genNearPointerSet  5946
;;	641
;;	aopForRemat 425
;;	446: rname _PORTC_bits, val 0, const = 0
;; ***	genNearPointerSet  5963
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTC_bits
;; 	line = 5965 result AOP_PCODE=_PORTC_bits, size=2, left -=-, size=0, right AOP_LIT=0x00, size=1
;; gen.c:5694:genPackBits *{*
;; ***	genPackBits  5695
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTC_bits
; >>> gen.c:5720:genPackBits
	.line	70; "i2c.c"	ICLK=0;
	BANKSEL	_PORTC_bits
	BCF	_PORTC_bits,3
;; gen.c:2261:resultRemat *{*
;; ***	genPlus  547
;; genarith.c:548:genPlus *{*
;;	721 register type nRegs=1
;;	606
;; 	line = 554 result AOP_REG=r0x1049, size=1, left AOP_REG=r0x1049, size=1, right AOP_LIT=0x01, size=1
;; ***	pic14_getDataSize  1426
;; genarith.c:142:genPlusIncr *{*
;; ***	genPlusIncr  144
;; 	result AOP_REG, left AOP_REG, right AOP_LIT
;; 	genPlusIncr  156
; >>> genarith.c:168:genPlusIncr
;;	1109 rIdx = r0x1049 
	.line	65; "i2c.c"	for(i=0;i<8;i++)		
	BANKSEL	r0x1006
	INCF	r0x1006,F
;; gen.c:2261:resultRemat *{*
;; gen.c:2614:genGoto *{*
; >>> gen.c:2616:genGoto
;; ***	popGetLabel  key=1, label offset 20
	GOTO	_00121_DS_
;; gen.c:2261:resultRemat *{*
;; gen.c:2597:genLabel *{*
;; ***	genLabel  2600
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:6117:genPointerSet *{*
;; ***	genPointerSet  6118
;; gen.c:5945:genNearPointerSet *{*
;; ***	genNearPointerSet  5946
;;	641
;;	aopForRemat 425
;;	446: rname _PORTC_bits, val 0, const = 0
;; ***	genNearPointerSet  5963
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTC_bits
;; 	line = 5965 result AOP_PCODE=_PORTC_bits, size=2, left -=-, size=0, right AOP_LIT=0x01, size=1
;; gen.c:5694:genPackBits *{*
;; ***	genPackBits  5695
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTC_bits
; >>> gen.c:5720:genPackBits
_00124_DS_
	.line	72; "i2c.c"	IDAT=1;
	BANKSEL	_PORTC_bits
	BSF	_PORTC_bits,4
;; gen.c:2261:resultRemat *{*
;; gen.c:2030:genCall *{*
;; ***	genCall  2032
;; gen.c:1765:saveRegisters *{*
;; ***	saveRegisters  1767
; >>> gen.c:2118:genCall
	.line	73; "i2c.c"	delay();
	CALL	_delay
;; gen.c:1809:unsaveRegisters *{*
;; ***	unsaveRegisters  1811
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:6117:genPointerSet *{*
;; ***	genPointerSet  6118
;; gen.c:5945:genNearPointerSet *{*
;; ***	genNearPointerSet  5946
;;	641
;;	aopForRemat 425
;;	446: rname _PORTC_bits, val 0, const = 0
;; ***	genNearPointerSet  5963
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTC_bits
;; 	line = 5965 result AOP_PCODE=_PORTC_bits, size=2, left -=-, size=0, right AOP_LIT=0x01, size=1
;; gen.c:5694:genPackBits *{*
;; ***	genPackBits  5695
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTC_bits
; >>> gen.c:5720:genPackBits
	.line	74; "i2c.c"	ICLK=1;
	BANKSEL	_PORTC_bits
	BSF	_PORTC_bits,3
;; gen.c:2261:resultRemat *{*
;; gen.c:2030:genCall *{*
;; ***	genCall  2032
;; gen.c:1765:saveRegisters *{*
;; ***	saveRegisters  1767
; >>> gen.c:2118:genCall
	.line	75; "i2c.c"	delay();
	CALL	_delay
;; gen.c:1809:unsaveRegisters *{*
;; ***	unsaveRegisters  1811
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:6117:genPointerSet *{*
;; ***	genPointerSet  6118
;; gen.c:5945:genNearPointerSet *{*
;; ***	genNearPointerSet  5946
;;	641
;;	aopForRemat 425
;;	446: rname _PORTC_bits, val 0, const = 0
;; ***	genNearPointerSet  5963
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTC_bits
;; 	line = 5965 result AOP_PCODE=_PORTC_bits, size=2, left -=-, size=0, right AOP_LIT=0x00, size=1
;; gen.c:5694:genPackBits *{*
;; ***	genPackBits  5695
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTC_bits
; >>> gen.c:5720:genPackBits
	.line	76; "i2c.c"	ICLK=0;
	BANKSEL	_PORTC_bits
	BCF	_PORTC_bits,3
;; gen.c:2261:resultRemat *{*
;; gen.c:2597:genLabel *{*
;; ***	genLabel  2600
;; gen.c:2261:resultRemat *{*
;; gen.c:2435:genEndFunction *{*
;; ***	genEndFunction  2437
	RETURN	
; exit point of _i2c_wb
;; gen.c:6803:genpic14Code *{*

;***
;  pBlock Stats: dbName = C
;***
;entry:  _i2c_stop	;Function start
; 2 exit points
;has an exit
;functions called:
;   _delay
;   _delay
;   _delay
;   _delay
;; Starting pCode block
;; gen.c:2261:resultRemat *{*
;; gen.c:2597:genLabel *{*
;; ***	genLabel  2600
;; gen.c:2261:resultRemat *{*
;; gen.c:2283:genFunction *{*
;; ***	genFunction  2285 curr label offset=12previous max_key=0 
_i2c_stop	;Function start
; 2 exit points
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:6117:genPointerSet *{*
;; ***	genPointerSet  6118
;; gen.c:5945:genNearPointerSet *{*
;; ***	genNearPointerSet  5946
;;	641
;;	aopForRemat 425
;;	446: rname _PORTC_bits, val 0, const = 0
;; ***	genNearPointerSet  5963
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTC_bits
;; 	line = 5965 result AOP_PCODE=_PORTC_bits, size=2, left -=-, size=0, right AOP_LIT=0x01, size=1
;; gen.c:5694:genPackBits *{*
;; ***	genPackBits  5695
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTC_bits
; >>> gen.c:5720:genPackBits
	.line	54; "i2c.c"	ICLK=1;
	BANKSEL	_PORTC_bits
	BSF	_PORTC_bits,3
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:6117:genPointerSet *{*
;; ***	genPointerSet  6118
;; gen.c:5945:genNearPointerSet *{*
;; ***	genNearPointerSet  5946
;;	641
;;	aopForRemat 425
;;	446: rname _PORTC_bits, val 0, const = 0
;; ***	genNearPointerSet  5963
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTC_bits
;; 	line = 5965 result AOP_PCODE=_PORTC_bits, size=2, left -=-, size=0, right AOP_LIT=0x00, size=1
;; gen.c:5694:genPackBits *{*
;; ***	genPackBits  5695
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTC_bits
; >>> gen.c:5720:genPackBits
	.line	55; "i2c.c"	IDAT=0;
	BCF	_PORTC_bits,4
;; gen.c:2261:resultRemat *{*
;; gen.c:2030:genCall *{*
;; ***	genCall  2032
;; gen.c:1765:saveRegisters *{*
;; ***	saveRegisters  1767
; >>> gen.c:2118:genCall
	.line	56; "i2c.c"	delay();
	CALL	_delay
;; gen.c:1809:unsaveRegisters *{*
;; ***	unsaveRegisters  1811
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:6117:genPointerSet *{*
;; ***	genPointerSet  6118
;; gen.c:5945:genNearPointerSet *{*
;; ***	genNearPointerSet  5946
;;	641
;;	aopForRemat 425
;;	446: rname _PORTC_bits, val 0, const = 0
;; ***	genNearPointerSet  5963
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTC_bits
;; 	line = 5965 result AOP_PCODE=_PORTC_bits, size=2, left -=-, size=0, right AOP_LIT=0x01, size=1
;; gen.c:5694:genPackBits *{*
;; ***	genPackBits  5695
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTC_bits
; >>> gen.c:5720:genPackBits
	.line	57; "i2c.c"	IDAT=1;
	BANKSEL	_PORTC_bits
	BSF	_PORTC_bits,4
;; gen.c:2261:resultRemat *{*
;; gen.c:2030:genCall *{*
;; ***	genCall  2032
;; gen.c:1765:saveRegisters *{*
;; ***	saveRegisters  1767
; >>> gen.c:2118:genCall
	.line	58; "i2c.c"	delay();
	CALL	_delay
;; gen.c:1809:unsaveRegisters *{*
;; ***	unsaveRegisters  1811
;; gen.c:2261:resultRemat *{*
;; gen.c:2597:genLabel *{*
;; ***	genLabel  2600
;; gen.c:2261:resultRemat *{*
;; gen.c:2435:genEndFunction *{*
;; ***	genEndFunction  2437
	RETURN	
; exit point of _i2c_stop
;; gen.c:6803:genpic14Code *{*

;***
;  pBlock Stats: dbName = C
;***
;entry:  _i2c_start	;Function start
; 2 exit points
;has an exit
;functions called:
;   _delay
;   _delay
;   _delay
;   _delay
;; Starting pCode block
;; gen.c:2261:resultRemat *{*
;; gen.c:2597:genLabel *{*
;; ***	genLabel  2600
;; gen.c:2261:resultRemat *{*
;; gen.c:2283:genFunction *{*
;; ***	genFunction  2285 curr label offset=8previous max_key=0 
_i2c_start	;Function start
; 2 exit points
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:6117:genPointerSet *{*
;; ***	genPointerSet  6118
;; gen.c:5945:genNearPointerSet *{*
;; ***	genNearPointerSet  5946
;;	641
;;	aopForRemat 425
;;	446: rname _PORTC_bits, val 0, const = 0
;; ***	genNearPointerSet  5963
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTC_bits
;; 	line = 5965 result AOP_PCODE=_PORTC_bits, size=2, left -=-, size=0, right AOP_LIT=0x01, size=1
;; gen.c:5694:genPackBits *{*
;; ***	genPackBits  5695
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTC_bits
; >>> gen.c:5720:genPackBits
	.line	45; "i2c.c"	ICLK=1;
	BANKSEL	_PORTC_bits
	BSF	_PORTC_bits,3
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:6117:genPointerSet *{*
;; ***	genPointerSet  6118
;; gen.c:5945:genNearPointerSet *{*
;; ***	genNearPointerSet  5946
;;	641
;;	aopForRemat 425
;;	446: rname _PORTC_bits, val 0, const = 0
;; ***	genNearPointerSet  5963
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTC_bits
;; 	line = 5965 result AOP_PCODE=_PORTC_bits, size=2, left -=-, size=0, right AOP_LIT=0x01, size=1
;; gen.c:5694:genPackBits *{*
;; ***	genPackBits  5695
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTC_bits
; >>> gen.c:5720:genPackBits
	.line	46; "i2c.c"	IDAT=1;
	BSF	_PORTC_bits,4
;; gen.c:2261:resultRemat *{*
;; gen.c:2030:genCall *{*
;; ***	genCall  2032
;; gen.c:1765:saveRegisters *{*
;; ***	saveRegisters  1767
; >>> gen.c:2118:genCall
	.line	47; "i2c.c"	delay();
	CALL	_delay
;; gen.c:1809:unsaveRegisters *{*
;; ***	unsaveRegisters  1811
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:6117:genPointerSet *{*
;; ***	genPointerSet  6118
;; gen.c:5945:genNearPointerSet *{*
;; ***	genNearPointerSet  5946
;;	641
;;	aopForRemat 425
;;	446: rname _PORTC_bits, val 0, const = 0
;; ***	genNearPointerSet  5963
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTC_bits
;; 	line = 5965 result AOP_PCODE=_PORTC_bits, size=2, left -=-, size=0, right AOP_LIT=0x00, size=1
;; gen.c:5694:genPackBits *{*
;; ***	genPackBits  5695
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTC_bits
; >>> gen.c:5720:genPackBits
	.line	48; "i2c.c"	IDAT=0;
	BANKSEL	_PORTC_bits
	BCF	_PORTC_bits,4
;; gen.c:2261:resultRemat *{*
;; gen.c:2030:genCall *{*
;; ***	genCall  2032
;; gen.c:1765:saveRegisters *{*
;; ***	saveRegisters  1767
; >>> gen.c:2118:genCall
	.line	49; "i2c.c"	delay();
	CALL	_delay
;; gen.c:1809:unsaveRegisters *{*
;; ***	unsaveRegisters  1811
;; gen.c:2261:resultRemat *{*
;; gen.c:2597:genLabel *{*
;; ***	genLabel  2600
;; gen.c:2261:resultRemat *{*
;; gen.c:2435:genEndFunction *{*
;; ***	genEndFunction  2437
	RETURN	
; exit point of _i2c_start
;; gen.c:6803:genpic14Code *{*

;***
;  pBlock Stats: dbName = C
;***
;entry:  _i2c_init	;Function start
; 2 exit points
;has an exit
;; Starting pCode block
;; gen.c:2261:resultRemat *{*
;; gen.c:2597:genLabel *{*
;; ***	genLabel  2600
;; gen.c:2261:resultRemat *{*
;; gen.c:2283:genFunction *{*
;; ***	genFunction  2285 curr label offset=4previous max_key=0 
_i2c_init	;Function start
; 2 exit points
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:6117:genPointerSet *{*
;; ***	genPointerSet  6118
;; gen.c:5945:genNearPointerSet *{*
;; ***	genNearPointerSet  5946
;;	641
;;	aopForRemat 425
;;	446: rname _TRISC_bits, val 0, const = 0
;; ***	genNearPointerSet  5963
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_TRISC_bits
;; 	line = 5965 result AOP_PCODE=_TRISC_bits, size=2, left -=-, size=0, right AOP_LIT=0x00, size=1
;; gen.c:5694:genPackBits *{*
;; ***	genPackBits  5695
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_TRISC_bits
; >>> gen.c:5720:genPackBits
	.line	38; "i2c.c"	TIDAT=0;
	BANKSEL	_TRISC_bits
	BCF	_TRISC_bits,4
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:6117:genPointerSet *{*
;; ***	genPointerSet  6118
;; gen.c:5945:genNearPointerSet *{*
;; ***	genNearPointerSet  5946
;;	641
;;	aopForRemat 425
;;	446: rname _PORTC_bits, val 0, const = 0
;; ***	genNearPointerSet  5963
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTC_bits
;; 	line = 5965 result AOP_PCODE=_PORTC_bits, size=2, left -=-, size=0, right AOP_LIT=0x01, size=1
;; gen.c:5694:genPackBits *{*
;; ***	genPackBits  5695
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTC_bits
; >>> gen.c:5720:genPackBits
	.line	39; "i2c.c"	ICLK=1;
	BANKSEL	_PORTC_bits
	BSF	_PORTC_bits,3
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:6117:genPointerSet *{*
;; ***	genPointerSet  6118
;; gen.c:5945:genNearPointerSet *{*
;; ***	genNearPointerSet  5946
;;	641
;;	aopForRemat 425
;;	446: rname _PORTC_bits, val 0, const = 0
;; ***	genNearPointerSet  5963
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTC_bits
;; 	line = 5965 result AOP_PCODE=_PORTC_bits, size=2, left -=-, size=0, right AOP_LIT=0x01, size=1
;; gen.c:5694:genPackBits *{*
;; ***	genPackBits  5695
;;	858: aopGet AOP_PCODE type PO_IMMEDIATE
;;	_PORTC_bits
; >>> gen.c:5720:genPackBits
	.line	40; "i2c.c"	IDAT=1;
	BSF	_PORTC_bits,4
;; gen.c:2261:resultRemat *{*
;; gen.c:2597:genLabel *{*
;; ***	genLabel  2600
;; gen.c:2261:resultRemat *{*
;; gen.c:2435:genEndFunction *{*
;; ***	genEndFunction  2437
	RETURN	
; exit point of _i2c_init
;; gen.c:6803:genpic14Code *{*

;***
;  pBlock Stats: dbName = C
;***
;entry:  _delay	;Function start
; 2 exit points
;has an exit
;; Starting pCode block
;; gen.c:2261:resultRemat *{*
;; gen.c:2597:genLabel *{*
;; ***	genLabel  2600
;; gen.c:2261:resultRemat *{*
;; gen.c:2283:genFunction *{*
;; ***	genFunction  2285 curr label offset=0previous max_key=0 
_delay	;Function start
; 2 exit points
;; gen.c:2261:resultRemat *{*
;; gen.c:4425:genInline *{*
;; ***	genInline  4426
	NOP 
;; gen.c:2261:resultRemat *{*
;; gen.c:4425:genInline *{*
;; ***	genInline  4426
	NOP 
;; gen.c:2261:resultRemat *{*
;; gen.c:4425:genInline *{*
;; ***	genInline  4426
	NOP 
;; gen.c:2261:resultRemat *{*
;; gen.c:4425:genInline *{*
;; ***	genInline  4426
	NOP 
;; gen.c:2261:resultRemat *{*
;; gen.c:2597:genLabel *{*
;; ***	genLabel  2600
;; gen.c:2261:resultRemat *{*
;; gen.c:2435:genEndFunction *{*
;; ***	genEndFunction  2437
	RETURN	
; exit point of _delay
;; gen.c:6803:genpic14Code *{*


;	code size estimation:
;	  129+   42 =   171 instructions (  426 byte)

	end
