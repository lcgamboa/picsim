#define __16f628a
#include "pic/pic16f628a.h"


unsigned int at 0x2007  __CONFIG = 16138;// _INTOSC_OSC_NOCLKOUT&_WDT_OFF&_LVP_OFF&_DATA_CP_OFF&_PWRTE_ON&_MCLRE_OFF;

unsigned char cmd;
unsigned char DD,EE,FF;

#define IN0 !RB4
#define IN1 !RB5


void delay(void){
	for(DD=0;DD<255;DD++)
		for(EE=0;EE<255;EE++);
}


static void Intr(void) interrupt 0 {

}


void main() {

    CMCON=7;	//desabilita os amp-ops internos

    INTCON = 0;    // Limpa a flag de interrupcoes.

    NOT_RBPU=0;  //desabilita pull-up da porta b
    GIE=0;       //desabilita interrupcoes

	//Configuracao da serial
    TX9=0;    //transmiss�o em 8 bits
    TXEN=1; //habilita transmiss�o
    SYNC=0; //modo assincrono
    BRGH=0; //low baud rate
    SPEN=1; //habilita porta serial - rx
    RX9=0;  //recep��o em 8 bits
    CREN=1; //recep��o cont�nua

    SPBRG=25; //baud rate de 9600

    TRISB=  0x02;  //0b01111010 configura I/O da porta B   
    TRISA = 0xFF;

    RA0=0;
    RA1=0;
    RCIF=0;

    while(1) {
        if(RCIF) {
          PORTB=RCREG;
          TXREG=PORTA;
          RCIF=0;
        }
	

	}	

}
