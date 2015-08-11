;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 2.9.0 #5416 (Jan 10 2010) (UNIX)
; This file was generated Thu Jun 16 17:51:45 2011
;--------------------------------------------------------
; PIC port for the 14-bit core
;--------------------------------------------------------
	.file	"eeprom_ext.c"
	list	p=16f877a
	radix dec
	include "p16f877a.inc"
;--------------------------------------------------------
; external declarations
;--------------------------------------------------------
	extern	_i2c_init
	extern	_i2c_start
	extern	_i2c_stop
	extern	_i2c_wb
	extern	_i2c_rb
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
	global	_e2pext_w
	global	_e2pext_r

;--------------------------------------------------------
; global definitions
;--------------------------------------------------------
;--------------------------------------------------------
; absolute symbol definitions
;--------------------------------------------------------
;--------------------------------------------------------
; compiler-defined variables
;--------------------------------------------------------
UDL_eeprom_ext_0	udata
r0x1001	res	1
r0x1000	res	1
r0x1002	res	1
r0x1003	res	1
r0x1007	res	1
r0x1006	res	1
r0x1008	res	1
r0x1009	res	1
r0x100A	res	1
r0x100B	res	1
r0x100C	res	1
r0x100D	res	1
r0x100E	res	1
r0x100F	res	1
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
code_eeprom_ext	code
;***
;  pBlock Stats: dbName = C
;***
;entry:  _e2pext_w	;Function start
; 2 exit points
;has an exit
;functions called:
;   _i2c_start
;   _i2c_wb
;   _i2c_wb
;   _i2c_wb
;   _i2c_wb
;   _i2c_stop
;   _e2pext_r
;   _i2c_start
;   _i2c_wb
;   _i2c_wb
;   _i2c_wb
;   _i2c_wb
;   _i2c_stop
;   _e2pext_r
;12 compiler assigned registers:
;   r0x1006
;   STK00
;   r0x1007
;   STK01
;   r0x1008
;   r0x1009
;   r0x100A
;   r0x100B
;   r0x100C
;   r0x100D
;   r0x100E
;   r0x100F
;; Starting pCode block
;; gen.c:2261:resultRemat *{*
;; gen.c:2597:genLabel *{*
;; ***	genLabel  2600
;; gen.c:2261:resultRemat *{*
;; gen.c:2283:genFunction *{*
;; ***	genFunction  2285 curr label offset=4previous max_key=6 
_e2pext_w	;Function start
; 2 exit points
;; gen.c:2261:resultRemat *{*
;; gen.c:6739:genReceive *{*
;; ***	genReceive  6740
;;	721 register type nRegs=2
;; gen.c:1866:assignResultValue *{*
;; ***	assignResultValue  1868
;; 	line = 1870 result -=-, size=0, left AOP_REG=r0x104E, size=2, right -=-, size=0
; >>> gen.c:1367:movwf
;;	1109 rIdx = r0x104F 
	.line	66; "eeprom_ext.c"	void e2pext_w(unsigned int addr, unsigned char val)
	BANKSEL	r0x1006
	MOVWF	r0x1006
; >>> gen.c:1393:get_returnvalue
;; ***	popRegFromIdx,1043  , rIdx=0x7f
	MOVF	STK00,W
; >>> gen.c:1367:movwf
;;	1109 rIdx = r0x104E 
	MOVWF	r0x1007
;; gen.c:2261:resultRemat *{*
;; gen.c:6739:genReceive *{*
;; ***	genReceive  6740
;;	721 register type nRegs=1
;; gen.c:1866:assignResultValue *{*
;; ***	assignResultValue  1868
;; 	line = 1870 result -=-, size=0, left AOP_REG=r0x1050, size=1, right -=-, size=0
; >>> gen.c:1393:get_returnvalue
;; ***	popRegFromIdx,1043  , rIdx=0x7e
	MOVF	STK01,W
; >>> gen.c:1367:movwf
;;	1109 rIdx = r0x1050 
	.line	73; "eeprom_ext.c"	tmp=val;
	MOVWF	r0x1008
	MOVWF	r0x1009
;; ***	pic14_getDataSize  1426
;; ***	addSign  797
;; genarith.c:798:addSign *{*
; >>> genarith.c:817:addSign
;;	1109 rIdx = r0x1052 
	CLRF	r0x100A
;; gen.c:2261:resultRemat *{*
;; gen.c:3504:ifxForOp *{*
;; ***	ifxForOp  3506
;; NULL :(	3526
;; gen.c:3719:genAnd *{*
;; ***	genAnd  3720
;;	721 register type nRegs=2
;;	721 register type nRegs=2
;; 	line = 3754 result AOP_REG=r0x1050, size=2, left AOP_REG=r0x104E, size=2, right AOP_LIT=0x00, size=2
; >>> gen.c:3945:genAnd
;;	1109 rIdx = r0x1050 
	.line	74; "eeprom_ext.c"	ah=(addr&0x0100)>>8;
	CLRF	r0x1008
; >>> gen.c:3952:genAnd
	MOVLW	0x01
; >>> gen.c:3953:genAnd
;;	1109 rIdx = r0x104F 
	ANDWF	r0x1006,W
; >>> gen.c:3954:genAnd
;;	1109 rIdx = r0x1053 
	MOVWF	r0x100B
	MOVWF	r0x1008
	MOVWF	r0x100C
;; ***	pic14_getDataSize  1426
;; ***	addSign  797
;; genarith.c:798:addSign *{*
; >>> genarith.c:817:addSign
;;	1109 rIdx = r0x1055 
	CLRF	r0x100D
;; gen.c:2261:resultRemat *{*
;; gen.c:6521:genCast *{*
;; ***	genCast  6522
;;	721 register type nRegs=1
;; 	line = 6530 result AOP_REG=r0x1050, size=1, left -=-, size=0, right AOP_REG=r0x1054, size=2
;; ***	genCast  6636
; >>> gen.c:6656:genCast
;;	1109 rIdx = r0x1054 
;;102	MOVF	r0x100C,W
; >>> gen.c:6657:genCast
;;	1109 rIdx = r0x1050 
;; gen.c:2261:resultRemat *{*
;; gen.c:3504:ifxForOp *{*
;; ***	ifxForOp  3506
;; NULL :(	3526
;; gen.c:3719:genAnd *{*
;; ***	genAnd  3720
;;	721 register type nRegs=2
;;	721 register type nRegs=2
;; 	line = 3754 result AOP_REG=r0x1054, size=2, left AOP_REG=r0x104E, size=2, right AOP_LIT=0xff, size=2
; >>> gen.c:3948:genAnd
;;	1109 rIdx = r0x104E 
;;101	MOVF	r0x1007,W
; >>> gen.c:3949:genAnd
;;	1109 rIdx = r0x1054 
; >>> gen.c:3945:genAnd
;;	1109 rIdx = r0x1055 
	.line	75; "eeprom_ext.c"	al=addr&0x00FF;
	CLRF	r0x100D
;; gen.c:2261:resultRemat *{*
;; gen.c:6521:genCast *{*
;; ***	genCast  6522
;;	721 register type nRegs=2
;;	721 register type nRegs=1
;; 	line = 6530 result AOP_REG=r0x1053, size=1, left -=-, size=0, right AOP_REG=r0x1054, size=2
;; ***	genCast  6636
; >>> gen.c:6656:genCast
;;	1109 rIdx = r0x1054 
;;100	MOVF	r0x100C,W
	MOVF	r0x1007,W
	MOVWF	r0x100C
; >>> gen.c:6657:genCast
;;	1109 rIdx = r0x1053 
	MOVWF	r0x100B
;; gen.c:2261:resultRemat *{*
;; gen.c:6332:genAssign *{*
;; ***	genAssign  6333
;;	721 register type nRegs=1
;; 	line = 6342 result AOP_REG=r0x1054, size=1, left -=-, size=0, right AOP_LIT=0x00, size=1
;; ***	genAssign  6434
; >>> gen.c:6443:genAssign
;;	1109 rIdx = r0x1054 
	.line	78; "eeprom_ext.c"	do
	CLRF	r0x100C
;; gen.c:2261:resultRemat *{*
;; gen.c:2597:genLabel *{*
;; ***	genLabel  2600
;; gen.c:2261:resultRemat *{*
;; gen.c:2030:genCall *{*
;; ***	genCall  2032
;; gen.c:1765:saveRegisters *{*
;; ***	saveRegisters  1767
; >>> gen.c:2116:genCall
_00119_DS_
	.line	80; "eeprom_ext.c"	i2c_start();
	PAGESEL	_i2c_start
; >>> gen.c:2118:genCall
	CALL	_i2c_start
; >>> gen.c:2123:genCall
	PAGESEL	$
;; gen.c:1809:unsaveRegisters *{*
;; ***	unsaveRegisters  1811
;; gen.c:2261:resultRemat *{*
;; gen.c:6187:genIfx *{*
;; ***	genIfx  6188
;;	721 register type nRegs=1
;; ***	pic14_toBoolean  1500
; >>> gen.c:1506:pic14_toBoolean
	.line	81; "eeprom_ext.c"	if(ah)
	BANKSEL	r0x1008
	MOVF	r0x1008,W
	BTFSC	STATUS,2
; >>> gen.c:6237:genIfx
;; ***	popGetLabel  key=2, label offset 14
	GOTO	_00116_DS_
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:2030:genCall *{*
;; ***	genCall  2032
;; gen.c:1765:saveRegisters *{*
;; ***	saveRegisters  1767
;; 	2079 left AOP_LIT
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
	.line	83; "eeprom_ext.c"	i2c_wb(0xA2);
	MOVLW	0xa2
; >>> gen.c:2116:genCall
	PAGESEL	_i2c_wb
; >>> gen.c:2118:genCall
	CALL	_i2c_wb
; >>> gen.c:2123:genCall
	PAGESEL	$
;; gen.c:1809:unsaveRegisters *{*
;; ***	unsaveRegisters  1811
;; gen.c:2261:resultRemat *{*
;; gen.c:2614:genGoto *{*
; >>> gen.c:2616:genGoto
;; ***	popGetLabel  key=3, label offset 14
	GOTO	_00117_DS_
;; gen.c:2261:resultRemat *{*
;; gen.c:2597:genLabel *{*
;; ***	genLabel  2600
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:2030:genCall *{*
;; ***	genCall  2032
;; gen.c:1765:saveRegisters *{*
;; ***	saveRegisters  1767
;; 	2079 left AOP_LIT
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
_00116_DS_
	.line	87; "eeprom_ext.c"	i2c_wb(0xA0);
	MOVLW	0xa0
; >>> gen.c:2116:genCall
	PAGESEL	_i2c_wb
; >>> gen.c:2118:genCall
	CALL	_i2c_wb
; >>> gen.c:2123:genCall
	PAGESEL	$
;; gen.c:1809:unsaveRegisters *{*
;; ***	unsaveRegisters  1811
;; gen.c:2261:resultRemat *{*
;; gen.c:2597:genLabel *{*
;; ***	genLabel  2600
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:2030:genCall *{*
;; ***	genCall  2032
;; gen.c:1765:saveRegisters *{*
;; ***	saveRegisters  1767
;;	721 register type nRegs=1
;;	721 register type nRegs=1
;; 	2079 left AOP_REG
;; gen.c:1324:mov2w_op *{*
;; ***	mov2w  1356  offset=0
; >>> gen.c:1361:mov2w
;;	1109 rIdx = r0x1053 
_00117_DS_
	.line	89; "eeprom_ext.c"	i2c_wb(al);
	BANKSEL	r0x100B
	MOVF	r0x100B,W
; >>> gen.c:2116:genCall
	PAGESEL	_i2c_wb
; >>> gen.c:2118:genCall
	CALL	_i2c_wb
; >>> gen.c:2123:genCall
	PAGESEL	$
;; gen.c:1809:unsaveRegisters *{*
;; ***	unsaveRegisters  1811
;; gen.c:2261:resultRemat *{*
;; gen.c:6521:genCast *{*
;; ***	genCast  6522
;;	721 register type nRegs=2
;;	721 register type nRegs=1
;; 	line = 6530 result AOP_REG=r0x1055, size=1, left -=-, size=0, right AOP_REG=r0x1051, size=2
;; ***	genCast  6636
; >>> gen.c:6656:genCast
;;	1109 rIdx = r0x1051 
	.line	90; "eeprom_ext.c"	i2c_wb(tmp);
	BANKSEL	r0x1009
	MOVF	r0x1009,W
	MOVWF	r0x100D
	PAGESEL	_i2c_wb
; >>> gen.c:2118:genCall
	CALL	_i2c_wb
; >>> gen.c:2123:genCall
	PAGESEL	$
;; gen.c:1809:unsaveRegisters *{*
;; ***	unsaveRegisters  1811
;; gen.c:2261:resultRemat *{*
;; gen.c:2030:genCall *{*
;; ***	genCall  2032
;; gen.c:1765:saveRegisters *{*
;; ***	saveRegisters  1767
; >>> gen.c:2116:genCall
	.line	91; "eeprom_ext.c"	i2c_stop();
	PAGESEL	_i2c_stop
; >>> gen.c:2118:genCall
	CALL	_i2c_stop
; >>> gen.c:2123:genCall
	PAGESEL	$
;; gen.c:1809:unsaveRegisters *{*
;; ***	unsaveRegisters  1811
;; gen.c:2261:resultRemat *{*
;; ***	genPlus  547
;; genarith.c:548:genPlus *{*
;;	721 register type nRegs=1
;;	606
;; 	line = 554 result AOP_REG=r0x1054, size=1, left AOP_REG=r0x1054, size=1, right AOP_LIT=0x01, size=1
;; ***	pic14_getDataSize  1426
;; genarith.c:142:genPlusIncr *{*
;; ***	genPlusIncr  144
;; 	result AOP_REG, left AOP_REG, right AOP_LIT
;; 	genPlusIncr  156
; >>> genarith.c:168:genPlusIncr
;;	1109 rIdx = r0x1054 
	.line	93; "eeprom_ext.c"	nt++;
	BANKSEL	r0x100C
	INCF	r0x100C,F
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:2030:genCall *{*
;; ***	genCall  2032
;; gen.c:1765:saveRegisters *{*
;; ***	saveRegisters  1767
;;	721 register type nRegs=2
;;	721 register type nRegs=2
;; 	2079 left AOP_REG
;; gen.c:1324:mov2w_op *{*
;; ***	mov2w  1356  offset=0
; >>> gen.c:1361:mov2w
;;	1109 rIdx = r0x104E 
	.line	95; "eeprom_ext.c"	while((tmp != e2pext_r(addr))&&(nt < 10));
	MOVF	r0x1007,W
;; 	2079 left AOP_REG
; >>> gen.c:2087:genCall
;; ***	popRegFromIdx,1043  , rIdx=0x7f
	MOVWF	STK00
;; gen.c:1324:mov2w_op *{*
;; ***	mov2w  1356  offset=1
; >>> gen.c:1361:mov2w
;;	1109 rIdx = r0x104F 
	MOVF	r0x1006,W
; >>> gen.c:2118:genCall
	CALL	_e2pext_r
;;	721 register type nRegs=1
;; gen.c:1866:assignResultValue *{*
;; ***	assignResultValue  1868
;; 	line = 1870 result -=-, size=0, left AOP_REG=r0x1055, size=1, right -=-, size=0
; >>> gen.c:1367:movwf
;;	1109 rIdx = r0x1055 
	BANKSEL	r0x100D
	MOVWF	r0x100D
	MOVWF	r0x100E
;; ***	pic14_getDataSize  1426
;; ***	addSign  797
;; genarith.c:798:addSign *{*
; >>> genarith.c:817:addSign
;;	1109 rIdx = r0x1057 
	CLRF	r0x100F
;; gen.c:2261:resultRemat *{*
;; gen.c:3504:ifxForOp *{*
;; ***	ifxForOp  3506
;; gen.c:3388:genCmpEq *{*
;; ***	genCmpEq  3389
;; ifx is non-null
;;	721 register type nRegs=2
;;	721 register type nRegs=2
;; 	line = 3400 result AOP_CRY=0x00, size=0, left AOP_REG=r0x1051, size=2, right AOP_REG=r0x1056, size=2
;; ***	mov2w  1356  offset=0
; >>> gen.c:1361:mov2w
;;	1109 rIdx = r0x1056 
	MOVF	r0x100E,W
; >>> gen.c:3469:genCmpEq
;;	1109 rIdx = r0x1051 
	XORWF	r0x1009,W
; >>> gen.c:3471:genCmpEq
	BTFSS	STATUS,2
; >>> gen.c:3473:genCmpEq
;; ***	popGetLabel  key=14, label offset 14
	GOTO	_00128_DS_
;; ***	mov2w  1356  offset=1
; >>> gen.c:1361:mov2w
;;	1109 rIdx = r0x1057 
	MOVF	r0x100F,W
; >>> gen.c:3469:genCmpEq
;;	1109 rIdx = r0x1052 
	XORWF	r0x100A,W
	BTFSC	STATUS,2
	GOTO	_00122_DS_
_00128_DS_
	MOVLW	0x0a
	BANKSEL	r0x100C
	SUBWF	r0x100C,W
;; gen.c:3073:genSkipc *{*
; >>> gen.c:3080:genSkipc
	BTFSS	STATUS,0
; >>> gen.c:3082:genSkipc
;; ***	popGetLabel  key=5, label offset 14
	GOTO	_00119_DS_
;genSkipc:3083: created from rifx:0xbf919394
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:2597:genLabel *{*
;; ***	genLabel  2600
;; gen.c:2261:resultRemat *{*
;; gen.c:2435:genEndFunction *{*
;; ***	genEndFunction  2437
_00122_DS_
	RETURN	
; exit point of _e2pext_w

;***
;  pBlock Stats: dbName = C
;***
;entry:  _e2pext_r	;Function start
; 2 exit points
;has an exit
;functions called:
;   _i2c_start
;   _i2c_wb
;   _i2c_wb
;   _i2c_wb
;   _i2c_start
;   _i2c_wb
;   _i2c_wb
;   _i2c_rb
;   _i2c_stop
;   _i2c_start
;   _i2c_wb
;   _i2c_wb
;   _i2c_wb
;   _i2c_start
;   _i2c_wb
;   _i2c_wb
;   _i2c_rb
;   _i2c_stop
;7 compiler assigned registers:
;   r0x1000
;   STK00
;   r0x1001
;   r0x1002
;   r0x1003
;   r0x1004
;   r0x1005
;; Starting pCode block
;; gen.c:2261:resultRemat *{*
;; gen.c:2597:genLabel *{*
;; ***	genLabel  2600
;; gen.c:2261:resultRemat *{*
;; gen.c:2283:genFunction *{*
;; ***	genFunction  2285 curr label offset=0previous max_key=0 
_e2pext_r	;Function start
; 2 exit points
;; gen.c:2261:resultRemat *{*
;; gen.c:6739:genReceive *{*
;; ***	genReceive  6740
;;	721 register type nRegs=2
;; gen.c:1866:assignResultValue *{*
;; ***	assignResultValue  1868
;; 	line = 1870 result -=-, size=0, left AOP_REG=r0x1048, size=2, right -=-, size=0
; >>> gen.c:1367:movwf
;;	1109 rIdx = r0x1049 
	.line	29; "eeprom_ext.c"	unsigned char e2pext_r(unsigned int addr)
	BANKSEL	r0x1000
	MOVWF	r0x1000
; >>> gen.c:1393:get_returnvalue
;; ***	popRegFromIdx,1043  , rIdx=0x7f
	MOVF	STK00,W
; >>> gen.c:1367:movwf
;;	1109 rIdx = r0x1048 
	MOVWF	r0x1001
;; gen.c:2261:resultRemat *{*
;; gen.c:3504:ifxForOp *{*
;; ***	ifxForOp  3506
;; NULL :(	3526
;; gen.c:3719:genAnd *{*
;; ***	genAnd  3720
;;	721 register type nRegs=2
;;	721 register type nRegs=2
;; 	line = 3754 result AOP_REG=r0x104A, size=2, left AOP_REG=r0x1048, size=2, right AOP_LIT=0x00, size=2
; >>> gen.c:3945:genAnd
;;	1109 rIdx = r0x104A 
	.line	35; "eeprom_ext.c"	ah=(addr&0x0100)>>8;
	CLRF	r0x1002
; >>> gen.c:3952:genAnd
	MOVLW	0x01
; >>> gen.c:3953:genAnd
;;	1109 rIdx = r0x1049 
	ANDWF	r0x1000,W
; >>> gen.c:3954:genAnd
;;	1109 rIdx = r0x104B 
	MOVWF	r0x1003
	MOVWF	r0x1002
;;1	MOVWF	r0x1004
;; ***	pic14_getDataSize  1426
;; ***	addSign  797
;; genarith.c:798:addSign *{*
; >>> genarith.c:817:addSign
;;	1109 rIdx = r0x104D 
;;1	CLRF	r0x1005
;; gen.c:2261:resultRemat *{*
;; gen.c:6521:genCast *{*
;; ***	genCast  6522
;;	721 register type nRegs=1
;; 	line = 6530 result AOP_REG=r0x104A, size=1, left -=-, size=0, right AOP_REG=r0x104C, size=2
;; ***	genCast  6636
; >>> gen.c:6656:genCast
;;	1109 rIdx = r0x104C 
;;99	MOVF	r0x1004,W
; >>> gen.c:6657:genCast
;;	1109 rIdx = r0x104A 
;; gen.c:2261:resultRemat *{*
;; gen.c:3504:ifxForOp *{*
;; ***	ifxForOp  3506
;; NULL :(	3526
;; gen.c:3719:genAnd *{*
;; ***	genAnd  3720
;;	721 register type nRegs=2
;;	721 register type nRegs=2
;; 	line = 3754 result AOP_REG=r0x1048, size=2, left AOP_REG=r0x1048, size=2, right AOP_LIT=0xff, size=2
; >>> gen.c:3887:genAnd
;;	1109 rIdx = r0x1049 
	.line	36; "eeprom_ext.c"	al=addr&0x00FF;
	CLRF	r0x1000
;; gen.c:2261:resultRemat *{*
;; gen.c:6521:genCast *{*
;; ***	genCast  6522
;;	721 register type nRegs=2
;;	721 register type nRegs=1
;; 	line = 6530 result AOP_REG=r0x104B, size=1, left -=-, size=0, right AOP_REG=r0x1048, size=2
;; ***	genCast  6636
; >>> gen.c:6656:genCast
;;	1109 rIdx = r0x1048 
	MOVF	r0x1001,W
; >>> gen.c:6657:genCast
;;	1109 rIdx = r0x104B 
	MOVWF	r0x1003
;; gen.c:2261:resultRemat *{*
;; gen.c:2030:genCall *{*
;; ***	genCall  2032
;; gen.c:1765:saveRegisters *{*
;; ***	saveRegisters  1767
; >>> gen.c:2116:genCall
	.line	38; "eeprom_ext.c"	i2c_start();	
	PAGESEL	_i2c_start
; >>> gen.c:2118:genCall
	CALL	_i2c_start
; >>> gen.c:2123:genCall
	PAGESEL	$
;; gen.c:1809:unsaveRegisters *{*
;; ***	unsaveRegisters  1811
;; gen.c:2261:resultRemat *{*
;; gen.c:6187:genIfx *{*
;; ***	genIfx  6188
;;	721 register type nRegs=1
;; ***	pic14_toBoolean  1500
; >>> gen.c:1506:pic14_toBoolean
	.line	40; "eeprom_ext.c"	if(ah)
	BANKSEL	r0x1002
	MOVF	r0x1002,W
	BTFSC	STATUS,2
; >>> gen.c:6237:genIfx
;; ***	popGetLabel  key=2, label offset 4
	GOTO	_00106_DS_
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:2030:genCall *{*
;; ***	genCall  2032
;; gen.c:1765:saveRegisters *{*
;; ***	saveRegisters  1767
;; 	2079 left AOP_LIT
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
	.line	42; "eeprom_ext.c"	i2c_wb(0xA2);
	MOVLW	0xa2
; >>> gen.c:2116:genCall
	PAGESEL	_i2c_wb
; >>> gen.c:2118:genCall
	CALL	_i2c_wb
; >>> gen.c:2123:genCall
	PAGESEL	$
;; gen.c:1809:unsaveRegisters *{*
;; ***	unsaveRegisters  1811
;; gen.c:2261:resultRemat *{*
;; gen.c:2614:genGoto *{*
; >>> gen.c:2616:genGoto
;; ***	popGetLabel  key=3, label offset 4
	GOTO	_00107_DS_
;; gen.c:2261:resultRemat *{*
;; gen.c:2597:genLabel *{*
;; ***	genLabel  2600
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:2030:genCall *{*
;; ***	genCall  2032
;; gen.c:1765:saveRegisters *{*
;; ***	saveRegisters  1767
;; 	2079 left AOP_LIT
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
_00106_DS_
	.line	46; "eeprom_ext.c"	i2c_wb(0xA0);
	MOVLW	0xa0
; >>> gen.c:2116:genCall
	PAGESEL	_i2c_wb
; >>> gen.c:2118:genCall
	CALL	_i2c_wb
; >>> gen.c:2123:genCall
	PAGESEL	$
;; gen.c:1809:unsaveRegisters *{*
;; ***	unsaveRegisters  1811
;; gen.c:2261:resultRemat *{*
;; gen.c:2597:genLabel *{*
;; ***	genLabel  2600
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:2030:genCall *{*
;; ***	genCall  2032
;; gen.c:1765:saveRegisters *{*
;; ***	saveRegisters  1767
;;	721 register type nRegs=1
;;	721 register type nRegs=1
;; 	2079 left AOP_REG
;; gen.c:1324:mov2w_op *{*
;; ***	mov2w  1356  offset=0
; >>> gen.c:1361:mov2w
;;	1109 rIdx = r0x104B 
_00107_DS_
	.line	48; "eeprom_ext.c"	i2c_wb(al);
	BANKSEL	r0x1003
	MOVF	r0x1003,W
; >>> gen.c:2116:genCall
	PAGESEL	_i2c_wb
; >>> gen.c:2118:genCall
	CALL	_i2c_wb
; >>> gen.c:2123:genCall
	PAGESEL	$
;; gen.c:1809:unsaveRegisters *{*
;; ***	unsaveRegisters  1811
;; gen.c:2261:resultRemat *{*
;; gen.c:2030:genCall *{*
;; ***	genCall  2032
;; gen.c:1765:saveRegisters *{*
;; ***	saveRegisters  1767
; >>> gen.c:2116:genCall
	.line	50; "eeprom_ext.c"	i2c_start();
	PAGESEL	_i2c_start
; >>> gen.c:2118:genCall
	CALL	_i2c_start
; >>> gen.c:2123:genCall
	PAGESEL	$
;; gen.c:1809:unsaveRegisters *{*
;; ***	unsaveRegisters  1811
;; gen.c:2261:resultRemat *{*
;; gen.c:6187:genIfx *{*
;; ***	genIfx  6188
;;	721 register type nRegs=1
;; ***	pic14_toBoolean  1500
; >>> gen.c:1506:pic14_toBoolean
	.line	51; "eeprom_ext.c"	if(ah)
	BANKSEL	r0x1002
	MOVF	r0x1002,W
	BTFSC	STATUS,2
; >>> gen.c:6237:genIfx
;; ***	popGetLabel  key=5, label offset 4
	GOTO	_00109_DS_
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:2030:genCall *{*
;; ***	genCall  2032
;; gen.c:1765:saveRegisters *{*
;; ***	saveRegisters  1767
;; 	2079 left AOP_LIT
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
	.line	53; "eeprom_ext.c"	i2c_wb(0xA3);
	MOVLW	0xa3
; >>> gen.c:2116:genCall
	PAGESEL	_i2c_wb
; >>> gen.c:2118:genCall
	CALL	_i2c_wb
; >>> gen.c:2123:genCall
	PAGESEL	$
;; gen.c:1809:unsaveRegisters *{*
;; ***	unsaveRegisters  1811
;; gen.c:2261:resultRemat *{*
;; gen.c:2614:genGoto *{*
; >>> gen.c:2616:genGoto
;; ***	popGetLabel  key=6, label offset 4
	GOTO	_00110_DS_
;; gen.c:2261:resultRemat *{*
;; gen.c:2597:genLabel *{*
;; ***	genLabel  2600
;; gen.c:2261:resultRemat *{*
;; gen.c:2261:resultRemat *{*
;; gen.c:2030:genCall *{*
;; ***	genCall  2032
;; gen.c:1765:saveRegisters *{*
;; ***	saveRegisters  1767
;; 	2079 left AOP_LIT
;; gen.c:1324:mov2w_op *{*
; >>> gen.c:1339:mov2w_op
_00109_DS_
	.line	57; "eeprom_ext.c"	i2c_wb(0xA1);
	MOVLW	0xa1
; >>> gen.c:2116:genCall
	PAGESEL	_i2c_wb
; >>> gen.c:2118:genCall
	CALL	_i2c_wb
; >>> gen.c:2123:genCall
	PAGESEL	$
;; gen.c:1809:unsaveRegisters *{*
;; ***	unsaveRegisters  1811
;; gen.c:2261:resultRemat *{*
;; gen.c:2597:genLabel *{*
;; ***	genLabel  2600
;; gen.c:2261:resultRemat *{*
;; gen.c:2030:genCall *{*
;; ***	genCall  2032
;; gen.c:1765:saveRegisters *{*
;; ***	saveRegisters  1767
; >>> gen.c:2116:genCall
_00110_DS_
	.line	59; "eeprom_ext.c"	ret=i2c_rb();
	PAGESEL	_i2c_rb
; >>> gen.c:2118:genCall
	CALL	_i2c_rb
; >>> gen.c:2123:genCall
	PAGESEL	$
;;	721 register type nRegs=1
;; gen.c:1866:assignResultValue *{*
;; ***	assignResultValue  1868
;; 	line = 1870 result -=-, size=0, left AOP_REG=r0x1048, size=1, right -=-, size=0
; >>> gen.c:1367:movwf
;;	1109 rIdx = r0x1048 
	BANKSEL	r0x1001
	MOVWF	r0x1001
;; 	2138 left AOP_REG
;; gen.c:1809:unsaveRegisters *{*
;; ***	unsaveRegisters  1811
;; gen.c:2261:resultRemat *{*
;; gen.c:2030:genCall *{*
;; ***	genCall  2032
;; gen.c:1765:saveRegisters *{*
;; ***	saveRegisters  1767
; >>> gen.c:2116:genCall
	.line	60; "eeprom_ext.c"	i2c_stop();
	PAGESEL	_i2c_stop
; >>> gen.c:2118:genCall
	CALL	_i2c_stop
; >>> gen.c:2123:genCall
	PAGESEL	$
;; gen.c:1809:unsaveRegisters *{*
;; ***	unsaveRegisters  1811
;; gen.c:2261:resultRemat *{*
;; gen.c:2561:genRet *{*
;; ***	genRet  2563
;;	721 register type nRegs=1
;; gen.c:1324:mov2w_op *{*
;; ***	mov2w  1356  offset=0
; >>> gen.c:1361:mov2w
;;	1109 rIdx = r0x1048 
	.line	62; "eeprom_ext.c"	return ret;	
	BANKSEL	r0x1001
	MOVF	r0x1001,W
;; gen.c:2261:resultRemat *{*
;; gen.c:2597:genLabel *{*
;; ***	genLabel  2600
;; gen.c:2261:resultRemat *{*
;; gen.c:2435:genEndFunction *{*
;; ***	genEndFunction  2437
	RETURN	
; exit point of _e2pext_r
;; gen.c:6803:genpic14Code *{*


;	code size estimation:
;	   91+   43 =   134 instructions (  354 byte)

	end
