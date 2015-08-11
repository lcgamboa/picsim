
	LIST	   P=16F628A
	INCLUDE	   <p16f628A.inc>
	INCLUDE	   <lcd.inc>
	
	__CONFIG   _CP_OFF & _WDT_OFF & _PWRTE_ON & _BODEN_OFF & _MCLRE_OFF & _HS_OSC & _LVP_OFF

;_INTRC_OSC_NOCLKOUT

	ERRORLEVEL -302		

	
	CBLOCK 0x20
		DADO
		TEMP
		DCONT
		D1
		D2
		D3
	ENDC

	CBLOCK	0x70	;variaveis para salvar contexto na interrupcao	
		W_TEMP		
		S_TEMP		
	ENDC 

;inico
	ORG	0X0000 
	GOTO	INICIO

;interrupcao
	ORG 	0X0004
;salva contexto
	MOVWF	W_TEMP
	SWAPF	STATUS,W
	MOVWF	S_TEMP
;le serial
;	BTFSS	PIR1,RCIF ;verifica se interupcao e da porta serial		
;	GOTO FIMS
	BANKSEL RCREG

;	MOVLW	L_L1
;	MOVWF	DADO
;	CALL	lcdcmd	

	MOVFW	RCREG
	MOVWF	TXREG
	MOVWF	DADO
	CALL	lcddat
	BCF	PIR1,RCIF		
;restaura contexto
FIMS:	SWAPF	S_TEMP,W
       	MOVWF	STATUS
       	SWAPF	W_TEMP,F
       	SWAPF	W_TEMP,W
       	RETFIE
     
;programa principal
INICIO:	
;	configura portas	
	MOVLW	B'00000111'
	MOVWF	CMCON		;configura	RA0,RA1,RA2,RA3
		
	BANKSEL	TRISA
	MOVLW	B'11110000'
	MOVWF	TRISA		
	MOVLW	B'00000010'
	MOVWF	TRISB		;PORTB	,RB1 IN
	BANKSEL	PORTB

;	inicializa serial
	MOVLW	B'10010000'	
	MOVWF	RCSTA
	BANKSEL	TXSTA
	MOVLW	B'00100000'  ;BRGH=0
	MOVWF	TXSTA
	MOVLW	D'255'		;255 20MHZ = 1200-8N1
	MOVWF	SPBRG
	BANKSEL	RCSTA	

	CALL	lcdinit

	MOVLW	L_L1
	MOVWF	DADO
	CALL	lcdcmd		

	MOVLW	A'O'
	MOVWF	DADO
	CALL	lcddat

	MOVLW	A'K'
	MOVWF	DADO
	CALL	lcddat

;	habilita interrupcoes
	MOVLW	B'11000000'	;habilita GIE PEIE 
	MOVWF	INTCON
        BANKSEL PIE1
	MOVLW	B'00100000'	;habilita RCIE 
	MOVWF	PIE1
	BANKSEL PIR1



MAIN:	
	
	;corrige erros
        BTFSC   RCSTA,FERR
        MOVFW   RCREG

        BTFSS   RCSTA,OERR
        GOTO    MAIN
        BCF     RCSTA,CREN
        BSF     RCSTA,CREN

	GOTO	MAIN

	INCLUDE	   <lcd.asm>

	END	


