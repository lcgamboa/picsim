    #include <P18F452.INC>
;processor p18f452

; -----------------------------------------------------------------------
    __CONFIG _CONFIG1H, _HS_OSC_1H & _OSCS_OFF_1H
    __CONFIG _CONFIG2L, _PWRT_OFF_2L & _BOR_OFF_2L & _BORV_20_2L
    __CONFIG _CONFIG2H, _WDT_OFF_2H & _WDTPS_1_2H
    __CONFIG _CONFIG3H, _CCP2MX_ON_3H
    __CONFIG _CONFIG4L, _STVR_ON_4L & _LVP_OFF_4L & _DEBUG_OFF_4L
    __CONFIG _CONFIG5L, _CP0_OFF_5L & _CP1_OFF_5L & _CP2_OFF_5L & _CP3_OFF_5L
    __CONFIG _CONFIG5H, _CPB_OFF_5H & _CPD_OFF_5H
    __CONFIG _CONFIG6L, _WRT0_OFF_6L & _WRT1_OFF_6L & _WRT2_OFF_6L & _WRT3_OFF_6L
    __CONFIG _CONFIG6H, _WRTC_OFF_6H & _WRTB_OFF_6H & _WRTD_OFF_6H
    __CONFIG _CONFIG7L, _EBTR0_OFF_7L & _EBTR1_OFF_7L & _EBTR2_OFF_7L & _EBTR3_OFF_7L
    __CONFIG _CONFIG7H, _EBTRB_OFF_7H

; -----------------------------------------------------------------------



#define DEBUG 0xfd4
#define INBUG  7
#define FRZ    6 
#define SSTP   5
#define SHDW   4
#define BRB7   3
#define BRB6   2
#define BTS7   1
#define BTS6   0



#define var_pclatu 	0x5f4
#define var_pclath 	0x5f5
#define var_6		0x5f6
#define var_7 		0x5f7
#define var_8 		0c5f8
#define var_9 		0x5f9
#define var_a 		0x5fa
#define var_fsr0h 	0x5fb
#define var_fsr0l 	0x5fc
#define var_bsr 	0x5fd
#define var_status 	0x5fe
#define var_w 		0x5ff


; code memory
    org 0x000000
    NOP
    LFSR 0x0,0x5D
    LFSR 0x1,0x5D
    LFSR 0x2,0x5D		
    NOP
    NOP 
    MOVLW 0xFD
    INCF PLUSW2,F,0
    MOVF PLUSW2,W,0 
    NOP
    NOP
    BCF TRISB,0,ACCESS
loop:
    NOP
    NOP
;    dw	0xe0
    BSF PORTB,0,ACCESS
    NOP
    NOP
    BCF PORTB,0,ACCESS
;    rcall teste
    goto loop	
;    goto 0x007DC0

;teste:
;	nop	
;	nop
;	dw	0xe0
;	dw	0xe1  ; TRET 
;	nop
;    	nop
;	return 0


    decf	0x5, 0x1, 0
    sublw	0x7
    mulwf	0x1, 0
    decf	0x3, 0, 0

end
;debug vector

org 0x007DC0
    bra		func_cfg
init:
    rcall	func_RD_var_a
    movf	PCL, W, ACCESS
    rlncf	var_a, W, BANKED
    addwf	PCL, F, ACCESS
    nop
    bra		cmd_exitlrw	;0
    bra		cmd_version	;1
    bra		cmd_rd_ram	;2
    bra		cmd_wr_ram	;3
    bra		cmd_rd_eeprom	;4
    bra		cmd_wr_eeprom	;5
    bra		cmd_rd_prog	;6
    bra		cmd_wr_prog	;7
    bra		cmd_rd_prog	;8
    bra		cmd_wr_prog	;9
    bra		cmd_shdw_ctrl		;a
    bra		cmd_ping	;b
    bra		cmd_rd_TOS		;c
    bra		cmd_ping	;d
    bra		cmd_ping	;e
    bra		cmd_ping	;f
    bra		cmd_ping	;10
    bra		cmd_ping	;11
    bra		cmd_ping	;12
    bra		cmd_ping	;13
    bra		cmd_ping	;14
    bra		cmd_ping	;15
    bra		cmd_ping	;16
    bra		cmd_ping	;17
    bra		cmd_exit		;18
    bra		cmd_exit_step		;19
;-------------------------------------------------
cmd_ping:
    clrf	var_a, BANKED
    rcall	func_WR_var_a
    rcall	func_WR_var_a
    bra		init
;-------------------------------------------------
func_cfg:
    movff	BSR, var_bsr
    movlb	0x5
    movff	STATUS, var_status
    movwf	var_w, BANKED
    movff	FSR0L, var_fsr0l
    movff	FSR0H, var_fsr0h
    movff	PCLATH, var_pclath
    movff	PCLATU, var_pclatu
    movf	DEBUG, W, ACCESS
    andlw	0xc8
    iorlw	0x52
    movwf	DEBUG, ACCESS
    tstfsz	STKPTR, ACCESS
    bra		init
    incf	STKPTR, F, ACCESS
    clrf	TOSL, ACCESS
    clrf	TOSH, ACCESS
    clrf	TOSU, ACCESS
    bra		init
;-------------------------------------------------
cmd_exitlrw:
    rcall	func_WR_var_a
    movlw	0
    movwf	var_a, BANKED
    rcall	func_WR_var_a
    bra		init
;-------------------------------------------------
cmd_version:
    rcall	func_WR_var_a
    movlw	0x2
    movwf	var_a, BANKED
    rcall	func_WR_var_a
    movlw	0
    movwf	var_a, BANKED
    rcall	func_WR_var_a
    movlw	0
    movwf	var_a, BANKED
    rcall	func_WR_var_a
    bra		init
;-------------------------------------------------
cmd_rd_ram:
    bcf		var_6, 0, BANKED
    bra		$+4
cmd_wr_ram:
    bsf		var_6, 0, BANKED
    rcall	func_WR_var_a
    rcall	func_RD_var_a
    movff	var_a, FSR0L
    rcall	func_RD_var_a
    movff	var_a, FSR0H
    rcall	func_RD_var_a
    movff	var_a, var_9
    rcall	func_RD_var_a
    movff	var_a, var_8
    tstfsz	var_9, BANKED
    incf	var_8, 0x1, BANKED
rep3:
    btfsc	var_6, 0, BANKED
    bra		0x7e8a
    movff	POSTINC0, var_a
    rcall	func_WR_var_a
    bra		0x7e90
    rcall	func_RD_var_a
    movff	var_a, POSTINC0
    decfsz	var_9, F, BANKED
    bra		rep3
    decfsz	var_8, F, BANKED
    bra		rep3
    bra		init
;-------------------------------------------------
cmd_rd_eeprom:
    bcf		var_6, 0, BANKED
    bra		$+6
cmd_wr_eeprom:
    bsf		var_6, 0, BANKED
    bra		$+2
    rcall	func_WR_var_a
    rcall	func_RD_var_a
    movwf	EEADR, ACCESS
    rcall	func_RD_var_a
    rcall	func_RD_var_a
    movff	var_a, var_9
    rcall	func_RD_var_a
    bcf		EECON1, 0x7, ACCESS
rep4:
    btfsc	var_6, 0, BANKED
    bra		0x7ec2
    bsf		EECON1, 0, ACCESS
    movff	EEDATA, var_a
    rcall	func_WR_var_a
    bra		0x7ed0
    bsf		EECON1, 0x2, ACCESS
    rcall	func_RD_var_a
    movff	var_a, EEDATA
    rcall	func_program_eeprom
    btfsc	EECON1, 0x1, ACCESS
    bra		0x7ecc
    incf	EEADR, 0x1, ACCESS
    decfsz	var_9, F, BANKED
    bra		rep4
    bcf		EECON1, 0x2, ACCESS
    bra		init
;-------------------------------------------------
cmd_rd_prog:
    bcf		var_6, 0, BANKED
    bra		0x7ee0
cmd_wr_prog:
    bsf		var_6, 0, BANKED
    rcall	func_WR_var_a
    rcall	func_RD_var_a
    movff	var_a, TBLPTRL
    rcall	func_RD_var_a
    movff	var_a, TBLPTRH
    rcall	func_RD_var_a
    movff	var_a, TBLPTRU
    rcall	func_RD_var_a
    rcall	func_RD_var_a
    movff	var_a, var_9
    rcall	func_RD_var_a
    movff	var_a, var_8
    incf	var_8, F, BANKED
    btfss	var_6, 0, BANKED
    bra		rep5
    movlw	0x94
    movwf	EECON1, ACCESS
    rcall	func_program_eeprom
    nop
rep5:
    btfss	var_6, 0, BANKED
    bra		0x7f1e
    rcall	func_RD_var_a
    movff	var_a, TABLAT
    tblwt	*+
    bra		0x7f26
    tblrd	*+
    movff	TABLAT, var_a
    rcall	func_WR_var_a
    decfsz	var_9, F, BANKED
    bra		rep5
    decfsz	var_8, F, BANKED
    bra		rep5
    btfss	var_6, 0, BANKED
    bra		init
    decf	TBLPTRL,F, ACCESS 
    rcall	func_program_eeprom
    nop
    bra		init
;-------------------------------------------------
cmd_shdw_ctrl:
    rcall	func_WR_var_a
    rcall	func_RD_var_a
    movf	var_a, F, BANKED
    btfss	STATUS, Z, ACCESS 
    bra		$+6
    bcf		DEBUG, SHDW, ACCESS
    bra		$+4
    bsf		DEBUG, SHDW, ACCESS
    bra		init
;-------------------------------------------------
cmd_rd_TOS:
    rcall	func_WR_var_a
    movff	TOSL, var_a
    rcall	func_WR_var_a
    movff	TOSH, var_a
    rcall	func_WR_var_a
    movff	TOSU, var_a
    rcall	func_WR_var_a
    bra		init
;-------------------------------------------------
cmd_exit:
    rcall	func_WR_var_a
    bra		jump1
cmd_exit_step:
    rcall	func_WR_var_a
    bsf		DEBUG, SSTP, ACCESS
    bra		jump1
jump1:
    movff	var_fsr0l, FSR0L
    movff	var_fsr0h, FSR0H
    movf	var_w, W, BANKED
    movff	var_status, STATUS
    movff	var_bsr, BSR
    movff	var_pclatu, PCLATU
    movff	var_pclath, PCLATH
    bsf		DEBUG, BTS6, ACCESS
    bcf		DEBUG, SHDW, ACCESS
    dw		0xe1  ; TRET
;-------------------------------------------------
func_program_eeprom:
    movlw	0x55
    movwf	EECON2, ACCESS
    movlw	0xaa
    movwf	EECON2, ACCESS
    bsf		EECON1, 0x1, ACCESS
    return	0
;-------------------------------------------------
func_RD_var_a:
    bsf		DEBUG, BRB6, ACCESS
    bra		$+2
    btfsc	DEBUG, BRB7, ACCESS
    bra		$-2
    btfss	DEBUG, BRB7, ACCESS 
    bra		$-2;
    bcf		DEBUG, BRB6, ACCESS
    movlw	0x14
    decfsz	WREG, W, ACCESS
    bra		$-2
    movlw	0x8
    movwf	var_7, BANKED
rep1:
    bsf		DEBUG, BRB6, ACCESS
    rlncf	var_a, F, BANKED
    bcf		var_a, 0, BANKED
    decf	var_7, F, BANKED
    bcf		DEBUG, BRB6, ACCESS
    btfsc	DEBUG, BRB7, ACCESS
    bsf		var_a, 0, BANKED
    bnz		rep1 
    return	0
;-------------------------------------------------
func_WR_var_a:
    bsf		DEBUG, BRB6, ACCESS
    bra		$+2
    btfsc	DEBUG, BRB7, ACCESS
    bra		$-2
    btfss	DEBUG, BRB7, ACCESS 
    bra		$-2
    bcf		DEBUG, BRB6, ACCESS
    nop
    bcf		DEBUG, BTS7, ACCESS
    movlw	0x1c
    decfsz	WREG, W, ACCESS
    bra		$-2
    movlw	0x8
rep2:
    bsf		DEBUG, BRB6, ACCESS
    btfsc	var_a, 0x7, BANKED
    bsf		DEBUG, BRB7, ACCESS
    btfss	var_a, 0x7, BANKED
    bcf		DEBUG, BRB7, ACCESS
    rlncf	var_a, F, BANKED
    bcf		DEBUG, BRB6, ACCESS
    decfsz	WREG, W, ACCESS
    bra		rep2
    bsf		DEBUG, BTS7, ACCESS
    return	0
    nop

; -----------------------------------------------------------------------
; eeprom memory
end

   

; -----------------------------------------------------------------------
; eeprom memory

;        ORG 0xF00000
a1      DE  05,06,07,08

;        ORG 0x200000
a2      DE  01,02,03,04

end
