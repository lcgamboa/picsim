/* ----------------------------------------------------------------------- */
/* tmr0 - contador 8 bits */


#include <pic18f452.h>

code char at __CONFIG1H CONFIG1H = _OSC_HS_1H & _OSCS_OFF_1H;
code char at __CONFIG2L CONFIG2L = _PUT_OFF_2L & _BODEN_OFF_2L & _BODENV_2_0V_2L;
code char at __CONFIG2H CONFIG2H = _WDT_OFF_2H & _WDTPS_1_128_2H;
code char at __CONFIG3H CONFIG3H = _CCP2MUX_RC1_3H;
code char at __CONFIG4L CONFIG4L = _STVR_ON_4L & _LVP_OFF_4L & _BACKBUG_OFF_4L;
code char at __CONFIG5L CONFIG5L = _CP_0_OFF_5L & _CP_1_OFF_5L & _CP_2_OFF_5L & _CP_3_OFF_5L;
code char at __CONFIG5H CONFIG5H = _CPB_OFF_5H & _CPD_OFF_5H;
code char at __CONFIG6L CONFIG6L = _WRT_0_OFF_6L & _WRT_1_OFF_6L & _WRT_2_OFF_6L & _WRT_3_OFF_6L;
code char at __CONFIG6H CONFIG6H = _WRTC_OFF_6H & _WRTB_OFF_6H & _WRTD_OFF_6H;
code char at __CONFIG7L CONFIG7L = _EBTR_0_OFF_7L & _EBTR_1_OFF_7L & _EBTR_2_OFF_7L & _EBTR_3_OFF_7L;
code char at __CONFIG7H CONFIG7H = _EBTRB_OFF_7H;



#define _tmr0_ini 55
#define _cnt_ini 20;

unsigned char cnt;

void isr() interrupt 1 
{
        cnt=cnt-1;	//decrementa contagem

        if(cnt == 0)	//quando contagem = 0;
        {
	PORTB= PORTB ^0x0FF;	//troca estado PORTB
        cnt=_cnt_ini;		//reinicia contador
        }

	TMR0L=_tmr0_ini;	//reinicia contagem
	INTCONbits.T0IF=0;		// reseta flag TMR0
}

void main() {

	//ADCON0=

	INTCON=0;        //Deliga interrupcoes


        TRISA=0xFE;	//configura PORTA
	TRISB=0x00;	//configura PORTB

/* configuracao TMR0 */
	T0CONbits.TMR0ON=1;
        T0CONbits.T08BIT=1;
	T0CONbits.T0CS=0;		// Seleciona clock do tmr0 como clock_cpu/4 
	T0CONbits.PSA=0;		// Usa pre-scaler
	
	T0CONbits.T0PS2=1;		//111 = clk / 256 
	T0CONbits.T0PS1=1;
        T0CONbits.T0PS0=1;

	TMR0L=_tmr0_ini;	//incicia timer com 55, conta de 55 a 255 (200)

	cnt=_cnt_ini;	//variavel auxiliar

/* tempo entrre interrupcoes do TMR0 = ((256*200*20)/(clock_cpu/4)= para 4MHz =>1.024 segundos*/

/* configura interrupcoes */
//	INTCONbits.GIE=1;		//liga interrupcoes
//	INTCONbits.T0IE=1;		//liga interrupcao do TMR0
	INTCONbits.T0IF=0;		//Apaga flag de interrupcao	
	
	PORTB=0xFF;
        
	while(1)	//espera interrupcoes
        {
         while(!INTCONbits.T0IF);

         cnt=cnt-1;	//decrementa contagem

        if(cnt == 0)	//quando contagem = 0;
        {
	PORTB= PORTB ^0x0FF;	//troca estado PORTB
        cnt=_cnt_ini;		//reinicia contador
        }

	TMR0L=_tmr0_ini;	//reinicia contagem
	INTCONbits.T0IF=0;		// reseta flag TMR0

        };
}
