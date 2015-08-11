/* ----------------------------------------------------------------------- */
/* tmr0 - contador 8 bits */


#include <pic16f628a.h>


typedef unsigned int word;
word at 0x2007 CONFIG = _WDT_OFF & _PWRTE_OFF & _INTOSC_OSC_NOCLKOUT & _MCLRE_ON & _BOREN_OFF & _LVP_OFF & _DATA_CP_OFF & _CP_OFF;


#define _tmr0_ini 55
#define _cnt_ini 20;

unsigned char cnt;

void isr() interrupt 0 
{
        cnt=cnt-1;	//decrementa contagem

        if(cnt == 0)	//quando contagem = 0;
        {
	PORTB= PORTB ^0x0FF;	//troca estado PORTB
        cnt=_cnt_ini;		//reinicia contador
        }

	TMR0=_tmr0_ini;	//reinicia contagem
	T0IF=0;		// reseta flag TMR0
}

void main() {


	INTCON=0;        //Deliga interrupcoes

	CMCON=0x07;	//Desliga comparadores analogicos
        TRISA=0xFE;	//configura PORTA
	TRISB=0x00;	//configura PORTB

/* configuracao TMR0 */
	T0CS=0;		// Seleciona clock do tmr0 como clock_cpu/4 
	PSA=0;		// Usa pre-scaler
	
	PS2=1;		//111 = clk / 256 
	PS1=1;
        PS0=1;

	TMR0=_tmr0_ini;	//incicia timer com 55, conta de 55 a 255 (200)

	cnt=_cnt_ini;	//variavel auxiliar

/* tempo entrre interrupcoes do TMR0 = ((256*200*20)/(clock_cpu/4)= para 4MHz =>1.024 segundos

/* configura interrupcoes */
	GIE=1;		//liga interrupcoes
	T0IE=1;		//liga interrupcao do TMR0
	T0IF=0;		//Apaga flag de interrupcao	
	
	PORTB=0xFF;
        
	while(1)	//espera interrupcoes
        {
        };
}
