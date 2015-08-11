

#include "id.h"
#include "string.h"
#include <stdio.h>

unsigned short get_out_id(char * name)
{

  if(strcmp(name,"RB0")==0)return O_RB0;
  if(strcmp(name,"RB1")==0)return O_RB1;
  if(strcmp(name,"RB2")==0)return O_RB2;
  if(strcmp(name,"RB3")==0)return O_RB3;
  if(strcmp(name,"RB4")==0)return O_RB4;
  if(strcmp(name,"RB5")==0)return O_RB5;
  if(strcmp(name,"RB6")==0)return O_RB6;
  if(strcmp(name,"RB7")==0)return O_RB7;
  
  if(strcmp(name,"RD0")==0)return O_RD0;
  if(strcmp(name,"RD1")==0)return O_RD1;
  if(strcmp(name,"RD2")==0)return O_RD2;
  if(strcmp(name,"RD3")==0)return O_RD3;
  if(strcmp(name,"RD4")==0)return O_RD4;
  if(strcmp(name,"RD5")==0)return O_RD5;
  if(strcmp(name,"RD6")==0)return O_RD6;
  if(strcmp(name,"RD7")==0)return O_RD7;
  
  if(strcmp(name,"PRG")==0)return O_PRG;
  if(strcmp(name,"RUN")==0)return O_RUN;
  
  if(strcmp(name,"RL1")==0)return O_RL1;
  if(strcmp(name,"RL2")==0)return O_RL2;

  if(strcmp(name,"RA0")==0)return O_RA0;	
  if(strcmp(name,"RA1")==0)return O_RA1;	
  if(strcmp(name,"RA2")==0)return O_RA2;	
  if(strcmp(name,"RA3")==0)return O_RA3;	
  
  if(strcmp(name,"RA6")==0)return O_RA6;	
  if(strcmp(name,"RA7")==0)return O_RA7;	

  if(strcmp(name,"RA0L")==0)return O_RA0L;	

  if(strcmp(name,"A1")==0)return O_A1;	
  if(strcmp(name,"B1")==0)return O_B1;	
  if(strcmp(name,"C1")==0)return O_C1;	
  if(strcmp(name,"D1")==0)return O_D1;	
  if(strcmp(name,"E1")==0)return O_E1;	
  if(strcmp(name,"F1")==0)return O_F1;	
  if(strcmp(name,"G1")==0)return O_G1;	
  if(strcmp(name,"P1")==0)return O_P1;	

  if(strcmp(name,"A2")==0)return O_A2;	
  if(strcmp(name,"B2")==0)return O_B2;	
  if(strcmp(name,"C2")==0)return O_C2;	
  if(strcmp(name,"D2")==0)return O_D2;	
  if(strcmp(name,"E2")==0)return O_E2;	
  if(strcmp(name,"F2")==0)return O_F2;	
  if(strcmp(name,"G2")==0)return O_G2;	
  if(strcmp(name,"P2")==0)return O_P2;	

  if(strcmp(name,"LPWR")==0)return O_LPWR;	
  if(strcmp(name,"LCD")==0)return O_LCD;	

  if(strcmp(name,"A3")==0)return O_A3;	
  if(strcmp(name,"B3")==0)return O_B3;	
  if(strcmp(name,"C3")==0)return O_C3;	
  if(strcmp(name,"D3")==0)return O_D3;	
  if(strcmp(name,"E3")==0)return O_E3;	
  if(strcmp(name,"F3")==0)return O_F3;	
  if(strcmp(name,"G3")==0)return O_G3;	
  if(strcmp(name,"P3")==0)return O_P3;	
  
  if(strcmp(name,"A4")==0)return O_A4;	
  if(strcmp(name,"B4")==0)return O_B4;	
  if(strcmp(name,"C4")==0)return O_C4;	
  if(strcmp(name,"D4")==0)return O_D4;	
  if(strcmp(name,"E4")==0)return O_E4;	
  if(strcmp(name,"F4")==0)return O_F4;	
  if(strcmp(name,"G4")==0)return O_G4;	
  if(strcmp(name,"P4")==0)return O_P4;	
  
  if(strcmp(name,"JP1")==0)return O_JP1;	
  if(strcmp(name,"JP2")==0)return O_JP2;	
  if(strcmp(name,"JP3")==0)return O_JP3;	
  if(strcmp(name,"JP4")==0)return O_JP4;	
  if(strcmp(name,"JP5")==0)return O_JP5;	
  if(strcmp(name,"JP6")==0)return O_JP6;	
  if(strcmp(name,"JP7")==0)return O_JP7;	
  if(strcmp(name,"JP8")==0)return O_JP8;	
  
  if(strcmp(name,"DP01")==0)return O_D01;
  if(strcmp(name,"DP02")==0)return O_D02;
  if(strcmp(name,"DP03")==0)return O_D03;
  if(strcmp(name,"DP04")==0)return O_D04;
  if(strcmp(name,"DP05")==0)return O_D05;
  if(strcmp(name,"DP06")==0)return O_D06;
  if(strcmp(name,"DP07")==0)return O_D07;
  if(strcmp(name,"DP08")==0)return O_D08;
  if(strcmp(name,"DP09")==0)return O_D09;
  if(strcmp(name,"DP10")==0)return O_D10;
  if(strcmp(name,"DP11")==0)return O_D11;
  if(strcmp(name,"DP12")==0)return O_D12;
  if(strcmp(name,"DP13")==0)return O_D13;
  if(strcmp(name,"DP14")==0)return O_D14;
  if(strcmp(name,"DP15")==0)return O_D15;
  if(strcmp(name,"DP16")==0)return O_D16;
  if(strcmp(name,"DP17")==0)return O_D17;
  if(strcmp(name,"DP18")==0)return O_D18;
  if(strcmp(name,"DP19")==0)return O_D19;
  if(strcmp(name,"DP20")==0)return O_D20;

  printf("Erro output '%s' don't have a valid id! \n",name);
  return 1;
};

unsigned short get_in_id(char * name)
{

  if(strcmp(name,"RST")==0)return I_RST; 
  if(strcmp(name,"RA1")==0)return I_RA1;
  if(strcmp(name,"RA2")==0)return I_RA2;
  if(strcmp(name,"RA3")==0)return I_RA3;
  if(strcmp(name,"RA4")==0)return I_RA4;
  if(strcmp(name,"RA5")==0)return I_RA5;
  if(strcmp(name,"PWR")==0)return I_PWR;
  if(strcmp(name,"ICSP")==0)return I_ICSP;
  if(strcmp(name,"JP1")==0)return I_JP1;

  if(strcmp(name,"RB0")==0)return I_RB0;
  if(strcmp(name,"RB1")==0)return I_RB1;
  if(strcmp(name,"RB2")==0)return I_RB2;
  if(strcmp(name,"RB3")==0)return I_RB3;
  if(strcmp(name,"RB4")==0)return I_RB4;
  if(strcmp(name,"RB5")==0)return I_RB5;
  if(strcmp(name,"JP2")==0)return I_JP2;
  if(strcmp(name,"JP3")==0)return I_JP3;
  if(strcmp(name,"PT1")==0)return I_PT1;
  if(strcmp(name,"PT2")==0)return I_PT2;
  if(strcmp(name,"PT3")==0)return I_PT3;
  if(strcmp(name,"JP4")==0)return I_JP4;
  if(strcmp(name,"JP5")==0)return I_JP5;
  if(strcmp(name,"JP6")==0)return I_JP6;
  if(strcmp(name,"JP7")==0)return I_JP7;
  if(strcmp(name,"JP8")==0)return I_JP8;
  
  if(strcmp(name,"TC1")==0)return I_TC1;
  if(strcmp(name,"TC2")==0)return I_TC2;
  if(strcmp(name,"TC3")==0)return I_TC3;
  if(strcmp(name,"TC4")==0)return I_TC4;
  if(strcmp(name,"TC5")==0)return I_TC5;
  if(strcmp(name,"TC6")==0)return I_TC6;
  if(strcmp(name,"TC7")==0)return I_TC7;
  if(strcmp(name,"TC8")==0)return I_TC8;
  if(strcmp(name,"TC9")==0)return I_TC9;
  if(strcmp(name,"TC*")==0)return I_TCA;
  if(strcmp(name,"TC0")==0)return I_TC0;
  if(strcmp(name,"TC#")==0)return I_TCT;
  
  if(strcmp(name,"DP01")==0)return I_D01;
  if(strcmp(name,"DP02")==0)return I_D02;
  if(strcmp(name,"DP03")==0)return I_D03;
  if(strcmp(name,"DP04")==0)return I_D04;
  if(strcmp(name,"DP05")==0)return I_D05;
  if(strcmp(name,"DP06")==0)return I_D06;
  if(strcmp(name,"DP07")==0)return I_D07;
  if(strcmp(name,"DP08")==0)return I_D08;
  if(strcmp(name,"DP09")==0)return I_D09;
  if(strcmp(name,"DP10")==0)return I_D10;
  if(strcmp(name,"DP11")==0)return I_D11;
  if(strcmp(name,"DP12")==0)return I_D12;
  if(strcmp(name,"DP13")==0)return I_D13;
  if(strcmp(name,"DP14")==0)return I_D14;
  if(strcmp(name,"DP15")==0)return I_D15;
  if(strcmp(name,"DP16")==0)return I_D16;
  if(strcmp(name,"DP17")==0)return I_D17;
  if(strcmp(name,"DP18")==0)return I_D18;
  if(strcmp(name,"DP19")==0)return I_D19;
  if(strcmp(name,"DP20")==0)return I_D20;

  printf("Erro input '%s' don't have a valid id! \n",name);
  return -1;
};

