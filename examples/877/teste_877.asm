
    #include <p16f877a.inc>

    __CONFIG _HS_OSC & _WDT_OFF & _PWRTE_ON & _BODEN_OFF & _LVP_OFF & _CPD_OFF & _WRT_OFF & _DEBUG_ON & _CP_OFF


; -----------------------------------------------------------------------
; Variables declaration
INT_VAR UDATA_SHR
w_saved      RES 1 ; variable used for context saving
status_saved RES 1 ; variable used for context saving
pclath_saved RES 1 ; variable used for context saving

DD1           RES 1 ; example variable
DD2           RES 1 ; example variable
DD3           RES 1 ; example variable


; -----------------------------------------------------------------------
; reset vector
STARTUP CODE 0x000
    nop                    ; needed for ICD2 debugging
start
    BANKSEL TRISB
    MOVLW  0xFE	
    MOVWF TRISB
    BANKSEL PORTB	
loop:
    MOVLW 0xFF
    XORWF PORTB,F
    DECFSZ  DD1,F
    GOTO $-1	
;    DECFSZ  DD2,F
;    GOTO $-3		
    goto    loop              ; loop forever

	END
