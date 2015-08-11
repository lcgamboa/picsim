


lcddelay:
	MOVLW	0x80
	MOVWF	D2
lcddelay_:
	DECFSZ	D1,F
	GOTO	lcddelay_
	DECFSZ	D2,F
	GOTO	lcddelay_
;	DECFSZ	D3,F
;	GOTO	lcddelay_
	RETURN
	

lcdinit:

  	BCF	LEN

	CALL	lcddelay
	CALL	lcddelay
	CALL	lcddelay
	CALL	lcddelay
	CALL	lcddelay
	CALL	lcddelay
	MOVLW	0x01
	MOVWF	DADO
	CALL	lcdcmd		;inicializa
	CALL	lcddelay
	CALL	lcddelay
	CALL	lcddelay
  	
	MOVLW	L_ON
	MOVWF	DADO
	CALL	lcdcmd		;//liga

	MOVLW	L_CLR
	MOVWF	DADO
	CALL	lcdcmd		;//limpa

	MOVLW	0x38
	MOVWF	DADO
	CALL	lcdcmd		;//configura 0x30

	CLRF	DCONT
  	RETURN

lcdwrite:
	MOVFW	PORTB
	ANDLW	0x0F
	MOVWF	TEMP
	MOVFW	DADO
	ANDLW	0xF0
	IORWF	TEMP,W	
	MOVWF	PORTB

	MOVFW	DADO
	ANDLW	0x0F
	MOVWF	PORTA
	RETURN

lcddat:
        BSF	LRS
	CALL	lcdwrite
        BSF	LEN
	CALL 	lcddelay
        BCF	LEN
	CALL 	lcddelay
	
	INCF	DCONT,F
	
	MOVLW	0x10
	SUBWF	DCONT,W
	BTFSS	STATUS,Z	
	GOTO	NEXT
	MOVLW	L_L2
	MOVWF	DADO
	CALL	lcdcmd	
	RETURN
	
NEXT:	MOVLW	0x20
	SUBWF	DCONT,W
	BTFSS	STATUS,Z	
	RETURN

	MOVLW	L_CLR
	MOVWF	DADO
	CALL	lcdcmd	

	MOVLW	L_L1
	MOVWF	DADO
	CALL	lcdcmd	
	CLRF	DCONT
	RETURN



lcdcmd:
	BCF	LRS
	CALL 	lcdwrite
	BSF	LEN
	CALL	lcddelay
       	BCF	LEN
	CALL	lcddelay
	RETURN	

;void lcdstrram (char *dat,unsigned char size)
;{
;  static unsigned char s;
  
; for(s =0 ; s < size;s++)  
; {
;   lcddat(dat[s]);
; }; 
;}

;void lcdstrrom (char *dat,unsigned char size)
;{
;  static unsigned char s;
;  static unsigned char c[16]; 
;  //strcpypgm2ram(c,dat);
;  strcpy(c,dat);
;  for(s =0 ; s < size;s++)  
; {
;   lcddat(c[s]);
; };
;}


;void lcdint(unsigned int num)
;{
; static unsigned int d1,d2,d3,d4,d5;
 
; d5=num / 10000;
; d4=(num-(d5*10000)) / 1000;
; d3=(num-(d5*10000)-(d4*1000)) / 100;
; d2=(num-(d5*10000)-(d4*1000)-(d3*100)) / 10;
; d1=(num-(d5*10000)-(d4*1000)-(d3*100)-(d2*10));
 
; lcddat(d5+0X30);
; lcddat(d4+0X30);
; lcddat(d3+0X30);
; lcddat(d2+0X30);
; lcddat(d1+0X30);
;}

