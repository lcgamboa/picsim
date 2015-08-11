    #include <p18f452.inc>
processor p18f452

; -----------------------------------------------------------------------
    __CONFIG _CONFIG1H, _HS_OSC_1H & _OSCS_OFF_1H
    __CONFIG _CONFIG2L, _PWRT_OFF_2L & _BOR_OFF_2L & _BORV_20_2L
    __CONFIG _CONFIG2H, _WDT_OFF_2H & _WDTPS_128_2H
    __CONFIG _CONFIG3H, _CCP2MX_ON_3H
    __CONFIG _CONFIG4L, _STVR_ON_4L & _LVP_OFF_4L & _DEBUG_OFF_4L
    __CONFIG _CONFIG5L, _CP0_OFF_5L & _CP1_OFF_5L & _CP2_OFF_5L & _CP3_OFF_5L
    __CONFIG _CONFIG5H, _CPB_OFF_5H & _CPD_OFF_5H
    __CONFIG _CONFIG6L, _WRT0_OFF_6L & _WRT1_OFF_6L & _WRT2_OFF_6L & _WRT3_OFF_6L
    __CONFIG _CONFIG6H, _WRTC_OFF_6H & _WRTB_OFF_6H & _WRTD_OFF_6H
    __CONFIG _CONFIG7L, _EBTR0_OFF_7L & _EBTR1_OFF_7L & _EBTR2_OFF_7L & _EBTR3_OFF_7L
    __CONFIG _CONFIG7H, _EBTRB_OFF_7H

; -----------------------------------------------------------------------

CBLOCK 0x00
  _A
ENDC

; code memory
org 0x000000

  NOP
  MOVLW 0xFE
  MOVWF TRISB,A
main:  
  MOVLW 0xFF
  XORWF PORTB,F,A
  DECFSZ _A,F,A
  GOTO $-1
  GOTO main
end
