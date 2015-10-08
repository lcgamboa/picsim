

/* outputs */

#define O_RB0	1
#define O_RB1	2
#define O_RB2	3
#define O_RB3	4
#define O_RB4	5
#define O_RB5	6
#define O_RB6	7
#define O_RB7	8

#define O_RA0	9
#define O_RA1	10
#define O_RA2	11
#define O_RA3	12

#define O_RA0L	13

#define O_A1	14
#define O_B1	15
#define O_C1	16
#define O_D1	17
#define O_E1	18
#define O_F1	19
#define O_G1	20
#define O_P1	21

#define O_A2	22
#define O_B2	23
#define O_C2	24
#define O_D2	25
#define O_E2	26
#define O_F2	27
#define O_G2	28
#define O_P2	29

#define O_LPWR	30
#define O_LCD	31
#define O_A3	32
#define O_B3	33
#define O_C3	34
#define O_D3	35
#define O_E3	36
#define O_F3	37
#define O_G3	38
#define O_P3	39
#define O_A4	40
#define O_B4	41
#define O_C4	42
#define O_D4	43
#define O_E4	44
#define O_F4	45
#define O_G4	46
#define O_P4	47
#define O_JP1	48
#define O_JP2	49
#define O_JP3	50
#define O_JP4	51
#define O_JP5	52
#define O_JP6	53
#define O_JP7	54
#define O_JP8	55

#define O_RA6	56
#define O_RA7	57

#define O_RD0	58
#define O_RD1	59
#define O_RD2	60
#define O_RD3	61
#define O_RD4	62
#define O_RD5	63
#define O_RD6	64
#define O_RD7	65

#define O_PRG	66
#define O_RUN	67

#define O_RL1	68
#define O_RL2	69

#define O_D01	70
#define O_D02	71
#define O_D03	72
#define O_D04	73
#define O_D05	74
#define O_D06	75
#define O_D07	76
#define O_D08	77
#define O_D09	78
#define O_D10	79
#define O_D11	80
#define O_D12	81
#define O_D13	82
#define O_D14	83
#define O_D15	84
#define O_D16	85
#define O_D17	86
#define O_D18	87
#define O_D19	88
#define O_D20	89

#define O_VT	90



/*inputsa*/

#define I_RST	1
#define I_RA1	2
#define I_RA2	3
#define I_RA3	4
#define I_RA4	5
#define I_PWR	6
#define I_ICSP	7
#define I_JP1	8

#define I_RB0	9
#define I_RB1	10
#define I_RB2	11
#define I_RB3	12
#define I_JP2	13
#define I_JP3	14
#define I_PT1	15
#define I_PT2	16
#define I_PT3	17
#define I_JP4	18
#define I_JP5	19
#define I_JP6	20
#define I_JP7	21
#define I_JP8	22


#define I_TC1   23
#define I_TC2   24
#define I_TC3   25
#define I_TC4   26
#define I_TC5   27
#define I_TC6   28
#define I_TC7   29
#define I_TC8   30
#define I_TC9   31
#define I_TCA   32
#define I_TC0   33
#define I_TCT   34

#define I_RB4	35
#define I_RB5	36
#define I_RA5	37


#define I_D01	38
#define I_D02	39
#define I_D03	40
#define I_D04	41
#define I_D05	42
#define I_D06	43
#define I_D07	44
#define I_D08	45
#define I_D09	46
#define I_D10	47
#define I_D11	48
#define I_D12	49
#define I_D13	50
#define I_D14	51
#define I_D15	52
#define I_D16	53
#define I_D17	54
#define I_D18	55
#define I_D19	56
#define I_D20	57

/*function*/

unsigned short get_in_id(char * name);
unsigned short get_out_id(char * name);
