    #include <p16f628a.inc>

    __CONFIG _WDT_OFF & _PWRTE_OFF & _RC_OSC_CLKOUT & _MCLRE_ON & _BOREN_OFF & _LVP_OFF & _DATA_CP_OFF & _CP_OFF

   org 0x00
start:


;escrita
   BSF     STATUS, RP0  ;Bank 1
  
   MOVLW    0xAB
   MOVWF    EEDATA

   MOVLW 0x02        ;endereço
   MOVWF EEADR       ;Address to read

   BSF     EECON1, WREN ;Enable write

   MOVLW   0X55          ;
   MOVWF   EECON2       ;Write 55h
   MOVLW   0XAA          ;
   MOVWF   EECON2       ;Write AAh
   BSF     EECON1,WR    ;Set WR bit
                     ;begin write

;leitura
   CLRW
   BSF   EECON1, RD  ;EE Read
   MOVF  EEDATA, W   ;W = EEDATA

   BCF   STATUS, RP0 ;Bank 0

   goto    $              ; loop forever
END
