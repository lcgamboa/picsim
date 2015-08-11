
	LIST	   P=16F628A
	INCLUDE	   <p16f628A.inc>

	__CONFIG   _CP_OFF & _WDT_OFF & _PWRTE_OFF & _BODEN_OFF & _MCLRE_OFF & _INTRC_OSC_NOCLKOUT & _LVP_OFF

	ERRORLEVEL -302		

	
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
;	BTFSS	PIR1,RCIF ;verifica se interupcao é da porta serial		
;	GOTO FIMS
	BANKSEL RCREG
	MOVFW	RCREG
	MOVWF	PORTB

	MOVFW	PORTA
	MOVWF	TXREG
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
	MOVLW	B'11111111'
	MOVWF	TRISA		
	MOVLW	B'00000010'
	MOVWF	TRISB		;PORTB	,RB1 IN
	BANKSEL	PORTB

;	inicializa serial
	MOVLW	B'10010000'
	MOVWF	RCSTA
	BANKSEL	TXSTA
	MOVLW	B'00100100'  
	MOVWF	TXSTA
	MOVLW	D'25'		;25 = 9600-8N1
	MOVWF	SPBRG
	BANKSEL	RCSTA	

;	habilita interrupcoes
	MOVLW	B'11000000'	;habilita GIE PEIE 
	MOVWF	INTCON
        BANKSEL PIE1
	MOVLW	B'00100000'	;habilita RCIE 
	MOVWF	PIE1
	BANKSEL PIR1

	CLRF PORTB
;loop infinito
	CLRW
MAIN:	
;	ADDLW	0x01
;	MOVWF	TXREG
	GOTO	MAIN
	END	


