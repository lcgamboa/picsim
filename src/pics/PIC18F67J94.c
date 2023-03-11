/* ########################################################################

   PICsim - PIC simulator

   ########################################################################

   Copyright (c) : 2019-2022  Luis Claudio Gamboa Lopes

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

   For e-mail suggestions :  lcgamboa@yahoo.com
   ######################################################################## */

#include <string.h>
#include "../../include/picsim.h"

void PIC18F67J94_map(_pic* pic) {
    memset(&pic->P18map, 0, sizeof(P18map_t));
    /*
     pic->P18map.UEP0 = &pic->ram[0xDFF];
     pic->P18map.UEP1 = &pic->ram[0xE00];
     pic->P18map.UEP2 = &pic->ram[0xE01];
     pic->P18map.UEP3 = &pic->ram[0xE02];
     pic->P18map.UEP4 = &pic->ram[0xE03];
     pic->P18map.UEP5 = &pic->ram[0xE04];
     pic->P18map.UEP6 = &pic->ram[0xE05];
     pic->P18map.UEP7 = &pic->ram[0xE06];
     pic->P18map.UEP8 = &pic->ram[0xE07];
     pic->P18map.UEP9 = &pic->ram[0xE08];
     pic->P18map.UEP10 = &pic->ram[0xE09];
     pic->P18map.UEP11 = &pic->ram[0xE0A];
     pic->P18map.UEP12 = &pic->ram[0xE0B];
     pic->P18map.UEP13 = &pic->ram[0xE0C];
     pic->P18map.UEP14 = &pic->ram[0xE0D];
     pic->P18map.UEP15 = &pic->ram[0xE0E];
     pic->P18map.UEIE = &pic->ram[0xE0F];
     pic->P18map.UIE = &pic->ram[0xE10];
     pic->P18map.UCFG = &pic->ram[0xE11];
     pic->P18map.RPOR0_1 = &pic->ram[0xE12];
     pic->P18map.RPOR2_3 = &pic->ram[0xE13];
     pic->P18map.RPOR4_5 = &pic->ram[0xE14];
     pic->P18map.RPOR6_7 = &pic->ram[0xE15];
     pic->P18map.RPOR8_9 = &pic->ram[0xE16];
     pic->P18map.RPOR10_11 = &pic->ram[0xE17];
     pic->P18map.RPOR12_13 = &pic->ram[0xE18];
     pic->P18map.RPOR14_15 = &pic->ram[0xE19];
     pic->P18map.RPOR16_17 = &pic->ram[0xE1A];
     pic->P18map.RPOR18_19 = &pic->ram[0xE1B];
     pic->P18map.RPOR20_21 = &pic->ram[0xE1C];
     pic->P18map.RPOR22_23 = &pic->ram[0xE1D];
     pic->P18map.RPOR24_25 = &pic->ram[0xE1E];
     pic->P18map.RPOR26_27 = &pic->ram[0xE1F];
     pic->P18map.RPOR28_29 = &pic->ram[0xE20];
     pic->P18map.RPOR30_31 = &pic->ram[0xE21];
     pic->P18map.RPOR32_33 = &pic->ram[0xE22];
     pic->P18map.RPOR34_35 = &pic->ram[0xE23];
     pic->P18map.RPOR36_37 = &pic->ram[0xE24];
     pic->P18map.RPOR38_39 = &pic->ram[0xE25];
     pic->P18map.RPOR40_41 = &pic->ram[0xE26];
     pic->P18map.RPOR42_43 = &pic->ram[0xE27];
     pic->P18map.RPOR44_45 = &pic->ram[0xE28];
     pic->P18map.RPOR46 = &pic->ram[0xE29];
     pic->P18map.RPINR0_1 = &pic->ram[0xE2A];
     pic->P18map.RPINR2_3 = &pic->ram[0xE2B];
     pic->P18map.RPINR4_5 = &pic->ram[0xE2C];
     pic->P18map.RPINR6_7 = &pic->ram[0xE2D];
     pic->P18map.RPINR8_9 = &pic->ram[0xE2E];
     pic->P18map.RPINR10_11 = &pic->ram[0xE2F];
     pic->P18map.RPINR12_13 = &pic->ram[0xE30];
     pic->P18map.RPINR14_15 = &pic->ram[0xE31];
     pic->P18map.RPINR16_17 = &pic->ram[0xE32];
     pic->P18map.RPINR18_19 = &pic->ram[0xE33];
     pic->P18map.RPINR20_21 = &pic->ram[0xE34];
     pic->P18map.RPINR22_23 = &pic->ram[0xE35];
     pic->P18map.RPINR24_25 = &pic->ram[0xE36];
     pic->P18map.RPINR26_27 = &pic->ram[0xE37];
     pic->P18map.RPINR28_29 = &pic->ram[0xE38];
     pic->P18map.RPINR30_31 = &pic->ram[0xE39];
     pic->P18map.RPINR32_33 = &pic->ram[0xE3A];
     pic->P18map.RPINR34_35 = &pic->ram[0xE3B];
     pic->P18map.RPINR36_37 = &pic->ram[0xE3C];
     pic->P18map.RPINR38_39 = &pic->ram[0xE3D];
     pic->P18map.RPINR40_41 = &pic->ram[0xE3E];
     pic->P18map.RPINR42_43 = &pic->ram[0xE3F];
     pic->P18map.RPINR44_45 = &pic->ram[0xE40];
     pic->P18map.RPINR46_47 = &pic->ram[0xE41];
     pic->P18map.RPINR48_49 = &pic->ram[0xE42];
     pic->P18map.RPINR50_51 = &pic->ram[0xE43];
     pic->P18map.RPINR52_53 = &pic->ram[0xE44];
     pic->P18map.ANCON3 = &pic->ram[0xE45];
     pic->P18map.ANCON2 = &pic->ram[0xE46];
     pic->P18map.ANCON1 = &pic->ram[0xE47];
     pic->P18map.ADCBUF1L = &pic->ram[0xE48];
     pic->P18map.ADCBUF1H = &pic->ram[0xE49];
     pic->P18map.ADCBUF2L = &pic->ram[0xE4A];
     pic->P18map.ADCBUF2H = &pic->ram[0xE4B];
     pic->P18map.ADCBUF3L = &pic->ram[0xE4C];
     pic->P18map.ADCBUF3H = &pic->ram[0xE4D];
     pic->P18map.ADCBUF4L = &pic->ram[0xE4E];
     pic->P18map.ADCBUF4H = &pic->ram[0xE4F];
     pic->P18map.ADCBUF5L = &pic->ram[0xE50];
     pic->P18map.ADCBUF5H = &pic->ram[0xE51];
     pic->P18map.ADCBUF6L = &pic->ram[0xE52];
     pic->P18map.ADCBUF6H = &pic->ram[0xE53];
     pic->P18map.ADCBUF7L = &pic->ram[0xE54];
     pic->P18map.ADCBUF7H = &pic->ram[0xE55];
     pic->P18map.ADCBUF8L = &pic->ram[0xE56];
     pic->P18map.ADCBUF8H = &pic->ram[0xE57];
     pic->P18map.ADCBUF9L = &pic->ram[0xE58];
     pic->P18map.ADCBUF9H = &pic->ram[0xE59];
     pic->P18map.ADCBUF10L = &pic->ram[0xE5A];
     pic->P18map.ADCBUF10H = &pic->ram[0xE5B];
     pic->P18map.ADCBUF11L = &pic->ram[0xE5C];
     pic->P18map.ADCBUF11H = &pic->ram[0xE5D];
     pic->P18map.ADCBUF12L = &pic->ram[0xE5E];
     pic->P18map.ADCBUF12H = &pic->ram[0xE5F];
     pic->P18map.ADCBUF13L = &pic->ram[0xE60];
     pic->P18map.ADCBUF13H = &pic->ram[0xE61];
     pic->P18map.ADCBUF14L = &pic->ram[0xE62];
     pic->P18map.ADCBUF14H = &pic->ram[0xE63];
     pic->P18map.ADCBUF15L = &pic->ram[0xE64];
     pic->P18map.ADCBUF15H = &pic->ram[0xE65];
     pic->P18map.ADCBUF16L = &pic->ram[0xE66];
     pic->P18map.ADCBUF16H = &pic->ram[0xE67];
     pic->P18map.ADCBUF17L = &pic->ram[0xE68];
     pic->P18map.ADCBUF17H = &pic->ram[0xE69];
     pic->P18map.ADCBUF18L = &pic->ram[0xE6A];
     pic->P18map.ADCBUF18H = &pic->ram[0xE6B];
     pic->P18map.ADCBUF19L = &pic->ram[0xE6C];
     pic->P18map.ADCBUF19H = &pic->ram[0xE6D];
     pic->P18map.ADCBUF20L = &pic->ram[0xE6E];
     pic->P18map.ADCBUF20H = &pic->ram[0xE6F];
     pic->P18map.ADCBUF21L = &pic->ram[0xE70];
     pic->P18map.ADCBUF21H = &pic->ram[0xE71];
     pic->P18map.ADCBUF22L = &pic->ram[0xE72];
     pic->P18map.ADCBUF22H = &pic->ram[0xE73];
     pic->P18map.ADCBUF23L = &pic->ram[0xE74];
     pic->P18map.ADCBUF23H = &pic->ram[0xE75];
     pic->P18map.ADCBUF24L = &pic->ram[0xE76];
     pic->P18map.ADCBUF24H = &pic->ram[0xE77];
     pic->P18map.ADCBUF25L = &pic->ram[0xE78];
     pic->P18map.ADCBUF25H = &pic->ram[0xE79];
     pic->P18map.ADCTMUEN0L = &pic->ram[0xE7A];
     pic->P18map.ADCTMUEN0H = &pic->ram[0xE7B];
     pic->P18map.ADCTMUEN1L = &pic->ram[0xE7C];
     pic->P18map.ADCTMUEN1H = &pic->ram[0xE7D];
     pic->P18map.ADCHIT0L = &pic->ram[0xE7E];
     pic->P18map.ADCHIT0H = &pic->ram[0xE7F];
     pic->P18map.ADCHIT1L = &pic->ram[0xE80];
     pic->P18map.ADCHIT1H = &pic->ram[0xE81];
     pic->P18map.ADCSS0L = &pic->ram[0xE82];
     pic->P18map.ADCSS0H = &pic->ram[0xE83];
     pic->P18map.ADCSS1L = &pic->ram[0xE84];
     pic->P18map.ADCSS1H = &pic->ram[0xE85];
     pic->P18map.ADCHS0L = &pic->ram[0xE86];
     pic->P18map.ADCHS0H = &pic->ram[0xE87];
     pic->P18map.ADCON5L = &pic->ram[0xE88];
     pic->P18map.ADCON5H = &pic->ram[0xE89];
     pic->P18map.ADCON3L = &pic->ram[0xE8A];
     pic->P18map.ADCON3H = &pic->ram[0xE8B];
     pic->P18map.ADCON2L = &pic->ram[0xE8C];
     pic->P18map.ADCON2H = &pic->ram[0xE8D];
     pic->P18map.LCDDATA0 = &pic->ram[0xE8E];
     pic->P18map.LCDDATA1 = &pic->ram[0xE8F];
     pic->P18map.LCDDATA2 = &pic->ram[0xE90];
     pic->P18map.LCDDATA3 = &pic->ram[0xE91];
     pic->P18map.LCDDATA4 = &pic->ram[0xE92];
     pic->P18map.LCDDATA5 = &pic->ram[0xE93];
     pic->P18map.LCDDATA6 = &pic->ram[0xE94];
     pic->P18map.LCDDATA7 = &pic->ram[0xE95];
     pic->P18map.LCDDATA8 = &pic->ram[0xE96];
     pic->P18map.LCDDATA9 = &pic->ram[0xE97];
     pic->P18map.LCDDATA10 = &pic->ram[0xE98];
     pic->P18map.LCDDATA11 = &pic->ram[0xE99];
     pic->P18map.LCDDATA12 = &pic->ram[0xE9A];
     pic->P18map.LCDDATA13 = &pic->ram[0xE9B];
     pic->P18map.LCDDATA14 = &pic->ram[0xE9C];
     pic->P18map.LCDDATA15 = &pic->ram[0xE9D];
     pic->P18map.LCDDATA16 = &pic->ram[0xE9E];
     pic->P18map.LCDDATA17 = &pic->ram[0xE9F];
     pic->P18map.LCDDATA18 = &pic->ram[0xEA0];
     pic->P18map.LCDDATA19 = &pic->ram[0xEA1];
     pic->P18map.LCDDATA20 = &pic->ram[0xEA2];
     pic->P18map.LCDDATA21 = &pic->ram[0xEA3];
     pic->P18map.LCDDATA22 = &pic->ram[0xEA4];
     pic->P18map.LCDDATA23 = &pic->ram[0xEA5];
     pic->P18map.LCDDATA24 = &pic->ram[0xEA6];
     pic->P18map.LCDDATA25 = &pic->ram[0xEA7];
     pic->P18map.LCDDATA26 = &pic->ram[0xEA8];
     pic->P18map.LCDDATA27 = &pic->ram[0xEA9];
     pic->P18map.LCDDATA28 = &pic->ram[0xEAA];
     pic->P18map.LCDDATA29 = &pic->ram[0xEAB];
     pic->P18map.LCDDATA30 = &pic->ram[0xEAC];
     pic->P18map.LCDDATA31 = &pic->ram[0xEAD];
     pic->P18map.LCDDATA32 = &pic->ram[0xEAE];
     pic->P18map.LCDDATA33 = &pic->ram[0xEAF];
     pic->P18map.LCDDATA34 = &pic->ram[0xEB0];
     pic->P18map.LCDDATA35 = &pic->ram[0xEB1];
     pic->P18map.LCDDATA36 = &pic->ram[0xEB2];
     pic->P18map.LCDDATA37 = &pic->ram[0xEB3];
     pic->P18map.LCDDATA38 = &pic->ram[0xEB4];
     pic->P18map.LCDDATA39 = &pic->ram[0xEB5];
     pic->P18map.LCDDATA40 = &pic->ram[0xEB6];
     pic->P18map.LCDDATA41 = &pic->ram[0xEB7];
     pic->P18map.LCDDATA42 = &pic->ram[0xEB8];
     pic->P18map.LCDDATA43 = &pic->ram[0xEB9];
     pic->P18map.LCDDATA44 = &pic->ram[0xEBA];
     pic->P18map.LCDDATA45 = &pic->ram[0xEBB];
     pic->P18map.LCDDATA46 = &pic->ram[0xEBC];
     pic->P18map.LCDDATA47 = &pic->ram[0xEBD];
     pic->P18map.LCDDATA48 = &pic->ram[0xEBE];
     pic->P18map.LCDDATA49 = &pic->ram[0xEBF];
     pic->P18map.LCDDATA50 = &pic->ram[0xEC0];
     pic->P18map.LCDDATA51 = &pic->ram[0xEC1];
     pic->P18map.LCDDATA52 = &pic->ram[0xEC2];
     pic->P18map.LCDDATA53 = &pic->ram[0xEC3];
     pic->P18map.LCDDATA54 = &pic->ram[0xEC4];
     pic->P18map.LCDDATA55 = &pic->ram[0xEC5];
     pic->P18map.LCDDATA56 = &pic->ram[0xEC6];
     pic->P18map.LCDDATA57 = &pic->ram[0xEC7];
     pic->P18map.LCDDATA58 = &pic->ram[0xEC8];
     pic->P18map.LCDDATA59 = &pic->ram[0xEC9];
     pic->P18map.LCDDATA60 = &pic->ram[0xECA];
     pic->P18map.LCDDATA61 = &pic->ram[0xECB];
     pic->P18map.LCDDATA62 = &pic->ram[0xECC];
     pic->P18map.LCDDATA63 = &pic->ram[0xECD];
     pic->P18map.LCDSE0 = &pic->ram[0xECE];
     pic->P18map.LCDSE1 = &pic->ram[0xECF];
     pic->P18map.LCDSE2 = &pic->ram[0xED0];
     pic->P18map.LCDSE3 = &pic->ram[0xED1];
     pic->P18map.LCDSE4 = &pic->ram[0xED2];
     pic->P18map.LCDSE5 = &pic->ram[0xED3];
     pic->P18map.LCDSE6 = &pic->ram[0xED4];
     pic->P18map.LCDSE7 = &pic->ram[0xED5];
     pic->P18map.LCDRL = &pic->ram[0xED6];
     pic->P18map.LCDREF = &pic->ram[0xED7];
     pic->P18map.LCDREG = &pic->ram[0xED8];
     pic->P18map.LCDCON = &pic->ram[0xED9];
     pic->P18map.LCDPS = &pic->ram[0xEDA];
     pic->P18map.REFO2CON3 = &pic->ram[0xEDB];
     pic->P18map.REFO2CON2 = &pic->ram[0xEDC];
     pic->P18map.REFO2CON1 = &pic->ram[0xEDD];
     pic->P18map.REFO2CON = &pic->ram[0xEDE];
     pic->P18map.REFO1CON3 = &pic->ram[0xEDF];
     pic->P18map.REFO1CON2 = &pic->ram[0xEE0];
     pic->P18map.REFO1CON1 = &pic->ram[0xEE1];
     pic->P18map.REFO1CON = &pic->ram[0xEE2];
     pic->P18map.ODCON2 = &pic->ram[0xEEA];
     pic->P18map.ODCON1 = &pic->ram[0xEEB];
     pic->P18map.MDCARL = &pic->ram[0xEEC];
     pic->P18map.MDCARH = &pic->ram[0xEED];
     pic->P18map.MDSRC = &pic->ram[0xEEE];
     pic->P18map.MDCON = &pic->ram[0xEEF];
     pic->P18map.PMD4 = &pic->ram[0xEF0];
     pic->P18map.PMD3 = &pic->ram[0xEF1];
     pic->P18map.PMD2 = &pic->ram[0xEF2];
     pic->P18map.PMD1 = &pic->ram[0xEF3];
     pic->P18map.PMD0 = &pic->ram[0xEF4];
     pic->P18map.CTMUCON4 = &pic->ram[0xEF5];
     pic->P18map.CTMUCON3 = &pic->ram[0xEF6];
     pic->P18map.CTMUCON2 = &pic->ram[0xEF7];
     pic->P18map.CTMUCON1 = &pic->ram[0xEF8];
     pic->P18map.TXREG4 = &pic->ram[0xEF9];
     pic->P18map.RCREG4 = &pic->ram[0xEFA];
     pic->P18map.SPBRG4 = &pic->ram[0xEFB];
     pic->P18map.SPBRGH4 = &pic->ram[0xEFC];
     pic->P18map.BAUDCON4 = &pic->ram[0xEFD];
     pic->P18map.TXSTA4 = &pic->ram[0xEFE];
     pic->P18map.RCSTA4 = &pic->ram[0xEFF];
     pic->P18map.DMACON2 = &pic->ram[0xF00];
     pic->P18map.ANCFG = &pic->ram[0xF01];
     pic->P18map.SSP2ADD = &pic->ram[0xF02];
     pic->P18map.SSP2BUF = &pic->ram[0xF03];
     pic->P18map.T4CON = &pic->ram[0xF04];
     pic->P18map.PR4 = &pic->ram[0xF05];
     pic->P18map.TMR4 = &pic->ram[0xF06];
     pic->P18map.CCP7CON = &pic->ram[0xF07];
     pic->P18map.CCPR7L = &pic->ram[0xF08];
     pic->P18map.CCPR7H = &pic->ram[0xF09];
     pic->P18map.CCP6CON = &pic->ram[0xF0A];
     pic->P18map.CCPR6L = &pic->ram[0xF0B];
     pic->P18map.CCPR6H = &pic->ram[0xF0C];
     pic->P18map.CCP5CON = &pic->ram[0xF0D];
     pic->P18map.CCPR5L = &pic->ram[0xF0E];
     pic->P18map.CCPR5H = &pic->ram[0xF0F];
     pic->P18map.CCP4CON = &pic->ram[0xF10];
     pic->P18map.CCPR4L = &pic->ram[0xF11];
     pic->P18map.CCPR4H = &pic->ram[0xF12];
     pic->P18map.T5GCON = &pic->ram[0xF13];
     pic->P18map.T5CON = &pic->ram[0xF14];
     pic->P18map.TMR5L = &pic->ram[0xF15];
     pic->P18map.TMR5H = &pic->ram[0xF16];
     pic->P18map.SSP2MSK = &pic->ram[0xF17];
     pic->P18map.SSP2CON2 = &pic->ram[0xF18];
     pic->P18map.SSP2CON1 = &pic->ram[0xF19];
     pic->P18map.SSP2STAT = &pic->ram[0xF1A];
     pic->P18map.PSTR3CON = &pic->ram[0xF1B];
     pic->P18map.PSTR2CON = &pic->ram[0xF1C];
     pic->P18map.TXREG2 = &pic->ram[0xF1D];
     pic->P18map.RCREG2 = &pic->ram[0xF1E];
     pic->P18map.SPBRG2 = &pic->ram[0xF1F];
     pic->P18map.SPBRGH2 = &pic->ram[0xF20];
     pic->P18map.DSGPR3 = &pic->ram[0xF21];
     pic->P18map.DSGPR2 = &pic->ram[0xF22];
     pic->P18map.DSGPR1 = &pic->ram[0xF23];
     pic->P18map.DSGPR0 = &pic->ram[0xF24];
     pic->P18map.DSWAKEH = &pic->ram[0xF25];
     pic->P18map.DSWAKEL = &pic->ram[0xF26];
     pic->P18map.DSCONH = &pic->ram[0xF27];
     pic->P18map.DSCONL = &pic->ram[0xF28];
     pic->P18map.TXREG3 = &pic->ram[0xF29];
     pic->P18map.RCREG3 = &pic->ram[0xF2A];
     pic->P18map.SPBRG3 = &pic->ram[0xF2B];
     pic->P18map.SPBRGH3 = &pic->ram[0xF2C];
     pic->P18map.BAUDCON3 = &pic->ram[0xF2D];
     pic->P18map.TXSTA3 = &pic->ram[0xF2E];
     pic->P18map.RCSTA3 = &pic->ram[0xF2F];
     */
    pic->P18map.SPBRGH = &pic->ram[0xF30];
    /*
    pic->P18map.BAUDCON2 = &pic->ram[0xF31];
    pic->P18map.TXSTA2 = &pic->ram[0xF32];
    pic->P18map.RCSTA2 = &pic->ram[0xF33];
    pic->P18map.CCPTMRS2 = &pic->ram[0xF34];
    pic->P18map.CCPTMRS1 = &pic->ram[0xF35];
    pic->P18map.CCPTMRS0 = &pic->ram[0xF36];
    pic->P18map.CM3CON = &pic->ram[0xF37];
    pic->P18map.CM2CON = &pic->ram[0xF38];s
    pic->P18map.SSP2CON3 = &pic->ram[0xF39];
    pic->P18map.T8CON = &pic->ram[0xF3A];
    pic->P18map.PR8 = &pic->ram[0xF3B];
    pic->P18map.TMR8 = &pic->ram[0xF3C];
    pic->P18map.T6CON = &pic->ram[0xF3D];
    pic->P18map.PR6 = &pic->ram[0xF3E];
    pic->P18map.TMR6 = &pic->ram[0xF3F];
    pic->P18map.CCP10CON = &pic->ram[0xF40];
    pic->P18map.CCPR10L = &pic->ram[0xF41];
    pic->P18map.CCPR10H = &pic->ram[0xF42];
    pic->P18map.CCP9CON = &pic->ram[0xF43];
    pic->P18map.CCPR9L = &pic->ram[0xF44];
    pic->P18map.CCPR9H = &pic->ram[0xF45];
    pic->P18map.CCP8CON = &pic->ram[0xF46];
    pic->P18map.CCPR8L = &pic->ram[0xF47];
    pic->P18map.CCPR8H = &pic->ram[0xF48];
    pic->P18map.CCP3CON = &pic->ram[0xF49];
    pic->P18map.CCPR3L = &pic->ram[0xF4A];
    pic->P18map.CCPR3H = &pic->ram[0xF4B];
    pic->P18map.ECCP3DEL = &pic->ram[0xF4C];
    pic->P18map.ECCP3AS = &pic->ram[0xF4D];
    */
    pic->P18map.CCP2CON = &pic->ram[0xF4E];
    pic->P18map.CCPR2L = &pic->ram[0xF4F];
    pic->P18map.CCPR2H = &pic->ram[0xF50];
    /*
    pic->P18map.ECCP2DEL = &pic->ram[0xF51];
    pic->P18map.ECCP2AS = &pic->ram[0xF52];
    pic->P18map.CM1CON = &pic->ram[0xF53];
    pic->P18map.PADCFG1 = &pic->ram[0xF54];
    pic->P18map.IOCN = &pic->ram[0xF55];
    pic->P18map.IOCP = &pic->ram[0xF56];
    pic->P18map.RTCCON2 = &pic->ram[0xF57];
    pic->P18map.ALRMVALL = &pic->ram[0xF58];
    pic->P18map.ALRMVALH = &pic->ram[0xF59];
    pic->P18map.ALRMRPT = &pic->ram[0xF5A];
    pic->P18map.ALRMCFG = &pic->ram[0xF5B];
    pic->P18map.RTCVALL = &pic->ram[0xF5C];
    pic->P18map.RTCVALH = &pic->ram[0xF5D];
    pic->P18map.RTCCAL = &pic->ram[0xF5E];
    pic->P18map.RTCCON1 = &pic->ram[0xF5F];
    pic->P18map.DMACON1 = &pic->ram[0xF60];
    */
    pic->P18map.PIE6 = &pic->ram[0xF61];
    /*
    pic->P18map.WPUB = &pic->ram[0xF62];
    pic->P18map.ACTCON = &pic->ram[0xF63];
    pic->P18map.OSCCON4 = &pic->ram[0xF64];
    pic->P18map.OSCCON3 = &pic->ram[0xF65];
    pic->P18map.OSCCON2 = &pic->ram[0xF66];
    */
    pic->P18map.BAUDCON = &pic->ram[0xF67];
    /*
    pic->P18map.SSP1MSK = &pic->ram[0xF68];
    pic->P18map.SSP1CON3 = &pic->ram[0xF69];
    pic->P18map.TXBUF = &pic->ram[0xF6A];
    pic->P18map.DMABCH = &pic->ram[0xF6B];
    pic->P18map.DMABCL = &pic->ram[0xF6C];
    pic->P18map.RXADDRH = &pic->ram[0xF6D];
    pic->P18map.RXADDRL = &pic->ram[0xF6E];
    pic->P18map.TXADDRH = &pic->ram[0xF6F];
    pic->P18map.TXADDRL = &pic->ram[0xF70];
    pic->P18map.PORTVP = &pic->ram[0xF71];
    pic->P18map.LATVP = &pic->ram[0xF72];
    pic->P18map.TRISVP = &pic->ram[0xF73];
    pic->P18map.UADDR = &pic->ram[0xF74];
    pic->P18map.UCON = &pic->ram[0xF75];
    pic->P18map.USTAT = &pic->ram[0xF76];
    pic->P18map.UEIR = &pic->ram[0xF77];
    pic->P18map.UIR = &pic->ram[0xF78];
    pic->P18map.UFRMH = &pic->ram[0xF79];
    pic->P18map.UFRML = &pic->ram[0xF7A];
    pic->P18map.RCON4 = &pic->ram[0xF7B];
    pic->P18map.RCON3 = &pic->ram[0xF7C];
    pic->P18map.RCON2 = &pic->ram[0xF7D];
    */
    pic->P18map.EECON2 = &pic->ram[0xF7E];
    pic->P18map.EECON1 = &pic->ram[0xF7F];
    pic->P18map.PORTA = &pic->ram[0xF80];
    pic->P18map.PORTB = &pic->ram[0xF81];
    pic->P18map.PORTC = &pic->ram[0xF82];
    pic->P18map.PORTD = &pic->ram[0xF83];
    pic->P18map.PORTE = &pic->ram[0xF84];
    pic->P18map.PORTF = &pic->ram[0xF85];
    pic->P18map.PORTG = &pic->ram[0xF86];
    pic->P18map.LATA = &pic->ram[0xF89];
    pic->P18map.LATB = &pic->ram[0xF8A];
    pic->P18map.LATC = &pic->ram[0xF8B];
    pic->P18map.LATD = &pic->ram[0xF8C];
    pic->P18map.LATE = &pic->ram[0xF8D];
    pic->P18map.LATF = &pic->ram[0xF8E];
    pic->P18map.LATG = &pic->ram[0xF8F];
    pic->P18map.TRISA = &pic->ram[0xF92];
    pic->P18map.TRISB = &pic->ram[0xF93];
    pic->P18map.TRISC = &pic->ram[0xF94];
    pic->P18map.TRISD = &pic->ram[0xF95];
    pic->P18map.TRISE = &pic->ram[0xF96];
    pic->P18map.TRISF = &pic->ram[0xF97];
    pic->P18map.TRISG = &pic->ram[0xF98];
    /*
    pic->P18map.OSCTUNE = &pic->ram[0xF9B];
    pic->P18map.PSTR1CON = &pic->ram[0xF9C];
    */
    pic->P18map.PIE1 = &pic->ram[0xF9D];
    pic->P18map.PIR1 = &pic->ram[0xF9E];
    pic->P18map.IPR1 = &pic->ram[0xF9F];
    pic->P18map.PIE2 = &pic->ram[0xFA0];
    pic->P18map.PIR2 = &pic->ram[0xFA1];
    pic->P18map.IPR2 = &pic->ram[0xFA2];
    pic->P18map.PIE3 = &pic->ram[0xFA3];
    pic->P18map.PIR3 = &pic->ram[0xFA4];
    pic->P18map.IPR3 = &pic->ram[0xFA5];
    pic->P18map.PIR6 = &pic->ram[0xFA6];
    /*
    pic->P18map.PSPCON = &pic->ram[0xFA7];
    pic->P18map.HLVDCON = &pic->ram[0xFA8];
    */
    pic->P18map.IPR6 = &pic->ram[0xFA9];
    /*
    pic->P18map.T1GCON = &pic->ram[0xFAA];
     */
    pic->P18map.RCSTA = &pic->ram[0xFAB];
    pic->P18map.TXSTA = &pic->ram[0xFAC];
    pic->P18map.TXREG = &pic->ram[0xFAD];
    pic->P18map.RCREG = &pic->ram[0xFAE];
    pic->P18map.SPBRG = &pic->ram[0xFAF];
    // pic->P18map.T3GCON = &pic->ram[0xFB0];
    pic->P18map.T3CON = &pic->ram[0xFB1];
    pic->P18map.TMR3L = &pic->ram[0xFB2];
    pic->P18map.TMR3H = &pic->ram[0xFB3];
    pic->P18map.PIE4 = &pic->ram[0xFB4];
    pic->P18map.PIR4 = &pic->ram[0xFB5];
    pic->P18map.IPR4 = &pic->ram[0xFB6];
    pic->P18map.PIE5 = &pic->ram[0xFB7];
    pic->P18map.PIR5 = &pic->ram[0xFB8];
    pic->P18map.CCP1CON = &pic->ram[0xFB9];
    pic->P18map.CCPR1L = &pic->ram[0xFBA];
    pic->P18map.CCPR1H = &pic->ram[0xFBB];
    /*
    pic->P18map.ECCP1DEL = &pic->ram[0xFBC];
    pic->P18map.ECCP1AS = &pic->ram[0xFBD];
    pic->P18map.CVRCONL = &pic->ram[0xFBE];
    pic->P18map.CVRCONH = &pic->ram[0xFBF];
    pic->P18map.ADCON1L = &pic->ram[0xFC0];
    pic->P18map.ADCON1H = &pic->ram[0xFC1];
    pic->P18map.ADCBUF0L = &pic->ram[0xFC2];
    pic->P18map.ADCBUF0H = &pic->ram[0xFC3];
    pic->P18map.CMSTAT = &pic->ram[0xFC4];
     */
    pic->P18map.SSP1CON2 = &pic->ram[0xFC5];
    pic->P18map.SSP1CON1 = &pic->ram[0xFC6];
    pic->P18map.SSP1STAT = &pic->ram[0xFC7];
    pic->P18map.SSP1ADD = &pic->ram[0xFC8];
    pic->P18map.SSP1BUF = &pic->ram[0xFC9];
    pic->P18map.T2CON = &pic->ram[0xFCA];
    pic->P18map.PR2 = &pic->ram[0xFCB];
    pic->P18map.TMR2 = &pic->ram[0xFCC];
    pic->P18map.T1CON = &pic->ram[0xFCD];
    pic->P18map.TMR1L = &pic->ram[0xFCE];
    pic->P18map.TMR1H = &pic->ram[0xFCF];
    pic->P18map.RCON = &pic->ram[0xFD0];
    /*
    pic->P18map.IOCF = &pic->ram[0xFD1];
     */
    pic->P18map.IPR5 = &pic->ram[0xFD2];
    /*
    pic->P18map.OSCCON = &pic->ram[0xFD3];
    */
    pic->P18map.T0CON = &pic->ram[0xFD5];
    pic->P18map.TMR0L = &pic->ram[0xFD6];
    pic->P18map.TMR0H = &pic->ram[0xFD7];
    pic->P18map.STATUS = &pic->ram[0xFD8];
    pic->P18map.FSR2L = &pic->ram[0xFD9];
    pic->P18map.FSR2H = &pic->ram[0xFDA];
    pic->P18map.PLUSW2 = &pic->ram[0xFDB];
    pic->P18map.PREINC2 = &pic->ram[0xFDC];
    pic->P18map.POSTDEC2 = &pic->ram[0xFDD];
    pic->P18map.POSTINC2 = &pic->ram[0xFDE];
    pic->P18map.INDF2 = &pic->ram[0xFDF];
    pic->P18map.BSR = &pic->ram[0xFE0];
    pic->P18map.FSR1L = &pic->ram[0xFE1];
    pic->P18map.FSR1H = &pic->ram[0xFE2];
    pic->P18map.PLUSW1 = &pic->ram[0xFE3];
    pic->P18map.PREINC1 = &pic->ram[0xFE4];
    pic->P18map.POSTDEC1 = &pic->ram[0xFE5];
    pic->P18map.POSTINC1 = &pic->ram[0xFE6];
    pic->P18map.INDF1 = &pic->ram[0xFE7];
    pic->P18map.WREG = &pic->ram[0xFE8];
    pic->P18map.FSR0L = &pic->ram[0xFE9];
    pic->P18map.FSR0H = &pic->ram[0xFEA];
    pic->P18map.PLUSW0 = &pic->ram[0xFEB];
    pic->P18map.PREINC0 = &pic->ram[0xFEC];
    pic->P18map.POSTDEC0 = &pic->ram[0xFED];
    pic->P18map.POSTINC0 = &pic->ram[0xFEE];
    pic->P18map.INDF0 = &pic->ram[0xFEF];
    pic->P18map.INTCON3 = &pic->ram[0xFF0];
    pic->P18map.INTCON2 = &pic->ram[0xFF1];
    pic->P18map.INTCON = &pic->ram[0xFF2];
    pic->P18map.PRODL = &pic->ram[0xFF3];
    pic->P18map.PRODH = &pic->ram[0xFF4];
    pic->P18map.TABLAT = &pic->ram[0xFF5];
    pic->P18map.TBLPTRL = &pic->ram[0xFF6];
    pic->P18map.TBLPTRH = &pic->ram[0xFF7];
    pic->P18map.TBLPTRU = &pic->ram[0xFF8];
    pic->P18map.PCL = &pic->ram[0xFF9];
    pic->P18map.PCLATH = &pic->ram[0xFFA];
    pic->P18map.PCLATU = &pic->ram[0xFFB];
    pic->P18map.STKPTR = &pic->ram[0xFFC];
    pic->P18map.TOSL = &pic->ram[0xFFD];
    pic->P18map.TOSH = &pic->ram[0xFFE];
    pic->P18map.TOSU = &pic->ram[0xFFF];
}

/*PINS

01 - RE1 PSPWR RP29 LCDBIAS2 HSTCLK2 LCDCLK
02 - RE0 PSPRD RP28 LCDBIAS1 HSTCLK1 LCDPHASE
03 - RG0 RP46 AN8 SEG28 COM4
04 - RG1 RP39 AN19 SEG29 COM5
05 - RG2 RP42 C3INA AN18 SEG30 COM6
06 - RG3 RP43 C3INB AN17 SEG31 COM7
07 - MCLR
08 - RG4 RTCC RP44 C3INC AN16 SEG26
09 - Vss
10 - Vddcore VCAP
11 - RF7 RP38 AN5 SEG25
12 - RF6 RP40 C1INA AN11 SEG24
13 - RF5 RP35 C1INB AN10 CVREF SEG23
14 - RF4 RP45 D+
15 - RF3 RP41 D-
16 - RF2 RP36 C2INB CTCMP AN7 SEG20
17 - Vusb
18 - Vbat
19 - CVREF+ Avdd
20 - CVREF- VSEL2 Avss
21 - RA3 RP3 AN3 VREF+
22 - RA2 RP2 AN2 Vref- SEG21
23 - RA1 RP1 AN1 SEG18
24 - RA0 RP0 AN1- AN0 SEG19
25 - VSEL1 Vss
26 - Vdd
27 - RA5 RP5 C3INA C2INA C1INA LVDIN AN4 SEG15
28 - RA4 RP4 AN6 SEG14
29 - RC1 SOSCI
30 - RC0 PWRLCLK SCLKI SOSCO
31 - RC6 CTED11 USBOEN RP18 SEG27
32 - RC7 CTED12 RP19 SEG22
33 - RC2 CTED7 RP11 AN9 SEG13
34 - RC3 CTED8 RP15 SCL1 SEG17
35 - RC4 CTED9 RP17 SDA1 SEG16
36 - RC5 CTED10 RP16 SEG12
37 - RB7 CTED6 EMUD PGD
38 - Vdd
39 - RA7 RP10 CLKI OSCI
40 - RA6 RP6 CLKO OSCO
41 - VSEL3b Vss
42 - RB6 CTED5 EMUC PGC
43 - RB5 CTED4 RP13 SEG8
44 - RB4 CTED3 RP12 SEG11
45 - RB3 CTED2 RP7 SEG10
46 - RB2 CTED1 RP14 SEG9
47 - RB1 RP9 VLCAP2
48 - RB0 INT0 CTED13 RP8 VLCAP1
49 - RD7 PSPD7 REFO2 RP27 SEG7
50 - RD6 PSPD6 RP26 SCL2 SEG6
51 - RD5 PSPD5 RP25 SDA2 SEG5
52 - RD4 PSPD4 RP24 SEG4
53 - RD3 PSPD3 RP23 SEG3
54 - RD2 PSPD2 RP22 SEG2
55 - RD1 PSPD1 RP21 SEG1
56 - Vss
57 - VSEL0 Vdd
58 - RD0 PSPD0 RP20 SEG0
59 - RE7 RP31 LCDBIAS0
60 - RE6 RP34 COM3
61 - RE5 RP37 COM2
62 - RE4 RP32 COM1
63 - RE3 REFO1 RP33 COM0
64 - RE2 PSPCS RP30 LCDBIAS3
 */

#include "../p18/p18_periferic.h"

/*
======================
Family=P18
processor=PIC18F67J94
deviceid=0x63A0
 */

void PIC18F67J94_reset(_pic* pic) {
    pic->pins[0].port = pic->P18map.PORTE;
    pic->pins[0].pord = 1;
    pic->pins[1].port = pic->P18map.PORTE;
    pic->pins[1].pord = 0;
    pic->pins[2].port = pic->P18map.PORTG;
    pic->pins[2].pord = 0;
    pic->pins[3].port = pic->P18map.PORTG;
    pic->pins[3].pord = 1;
    pic->pins[4].port = pic->P18map.PORTG;
    pic->pins[4].pord = 2;
    pic->pins[5].port = pic->P18map.PORTG;
    pic->pins[5].pord = 3;
    pic->pins[6].port = P_RST;
    pic->pins[6].pord = -1;
    pic->pins[7].port = pic->P18map.PORTG;
    pic->pins[7].pord = 4;
    pic->pins[8].port = P_VSS;
    pic->pins[8].pord = -1;
    // pic->pins[ 9].port =  vddcore
    pic->pins[10].port = pic->P18map.PORTF;
    pic->pins[10].pord = 7;
    pic->pins[11].port = pic->P18map.PORTF;
    pic->pins[11].pord = 6;
    pic->pins[12].port = pic->P18map.PORTF;
    pic->pins[12].pord = 5;
    pic->pins[13].port = pic->P18map.PORTF;
    pic->pins[13].pord = 4;
    pic->pins[14].port = pic->P18map.PORTF;
    pic->pins[14].pord = 3;
    pic->pins[15].port = pic->P18map.PORTF;
    pic->pins[15].pord = 2;
    pic->pins[16].port = P_USB;
    pic->pins[16].pord = -1;
    // pic->pins[17].port =vbat
    // pic->pins[18].port = cvref+
    // pic->pins[19].port = cvref-
    pic->pins[20].port = pic->P18map.PORTA;
    pic->pins[20].pord = 3;
    pic->pins[21].port = pic->P18map.PORTA;
    pic->pins[21].pord = 2;
    pic->pins[22].port = pic->P18map.PORTA;
    pic->pins[22].pord = 1;
    pic->pins[23].port = pic->P18map.PORTA;
    pic->pins[23].pord = 0;
    // pic->pins[24].port = vsel1
    pic->pins[25].port = P_VDD;
    pic->pins[25].pord = -1;
    pic->pins[25].value = 1;
    pic->pins[26].port = pic->P18map.PORTA;
    pic->pins[26].pord = 5;
    pic->pins[27].port = pic->P18map.PORTA;
    pic->pins[27].pord = 4;
    pic->pins[28].port = pic->P18map.PORTC;
    pic->pins[28].pord = 1;
    pic->pins[29].port = pic->P18map.PORTC;
    pic->pins[29].pord = 0;
    pic->pins[30].port = pic->P18map.PORTC;
    pic->pins[30].pord = 6;
    pic->pins[31].port = pic->P18map.PORTC;
    pic->pins[31].pord = 7;
    pic->pins[32].port = pic->P18map.PORTC;
    pic->pins[32].pord = 2;
    pic->pins[33].port = pic->P18map.PORTC;
    pic->pins[33].pord = 3;
    pic->pins[34].port = pic->P18map.PORTC;
    pic->pins[34].pord = 4;
    pic->pins[35].port = pic->P18map.PORTC;
    pic->pins[35].pord = 5;
    pic->pins[36].port = pic->P18map.PORTB;
    pic->pins[36].pord = 7;
    pic->pins[37].port = P_VDD;
    pic->pins[37].pord = -1;
    pic->pins[37].value = 1;
    pic->pins[38].port = pic->P18map.PORTA;
    pic->pins[38].pord = 7;
    pic->pins[39].port = pic->P18map.PORTA;
    pic->pins[39].pord = 6;
    // pic->pins[40].port = vsel3b
    pic->pins[41].port = pic->P18map.PORTB;
    pic->pins[41].pord = 6;
    pic->pins[42].port = pic->P18map.PORTB;
    pic->pins[42].pord = 5;
    pic->pins[43].port = pic->P18map.PORTB;
    pic->pins[43].pord = 4;
    pic->pins[44].port = pic->P18map.PORTB;
    pic->pins[44].pord = 3;
    pic->pins[45].port = pic->P18map.PORTB;
    pic->pins[45].pord = 2;
    pic->pins[46].port = pic->P18map.PORTB;
    pic->pins[46].pord = 1;
    pic->pins[47].port = pic->P18map.PORTB;
    pic->pins[47].pord = 0;
    pic->pins[48].port = pic->P18map.PORTD;
    pic->pins[48].pord = 7;
    pic->pins[49].port = pic->P18map.PORTD;
    pic->pins[49].pord = 6;
    pic->pins[50].port = pic->P18map.PORTD;
    pic->pins[50].pord = 5;
    pic->pins[51].port = pic->P18map.PORTD;
    pic->pins[51].pord = 4;
    pic->pins[52].port = pic->P18map.PORTD;
    pic->pins[52].pord = 3;
    pic->pins[53].port = pic->P18map.PORTD;
    pic->pins[53].pord = 2;
    pic->pins[54].port = pic->P18map.PORTD;
    pic->pins[54].pord = 1;
    pic->pins[55].port = P_VSS;
    pic->pins[55].pord = -1;
    // pic->pins[56].port = vsel0
    pic->pins[57].port = pic->P18map.PORTD;
    pic->pins[57].pord = 0;
    pic->pins[58].port = pic->P18map.PORTE;
    pic->pins[58].pord = 7;
    pic->pins[59].port = pic->P18map.PORTE;
    pic->pins[59].pord = 6;
    pic->pins[60].port = pic->P18map.PORTE;
    pic->pins[60].pord = 5;
    pic->pins[61].port = pic->P18map.PORTE;
    pic->pins[61].pord = 4;
    pic->pins[62].port = pic->P18map.PORTE;
    pic->pins[62].pord = 3;
    pic->pins[63].port = pic->P18map.PORTE;
    pic->pins[63].pord = 2;

    pic->mclr = 7;

    pic->adc[0] = 24;
    pic->adc[1] = 24;
    pic->adc[2] = 22;
    pic->adc[3] = 21;
    pic->adc[4] = 27;
    pic->adc[5] = 11;
    pic->adc[6] = 28;
    pic->adc[7] = 16;
    pic->adc[8] = 3;
    pic->adc[9] = 33;
    pic->adc[10] = 13;
    pic->adc[11] = 12;
    pic->adc[12] = 0;
    pic->adc[13] = 0;
    pic->adc[14] = 0;
    pic->adc[15] = 0;
    pic->adc[16] = 8;

    pic->usart_rx[0] = 0;
    pic->usart_tx[0] = 0;

    pic->pgc = 42;
    pic->pgd = 37;

    pic->sck = 0;
    pic->sdo = 0;
    pic->sdi = 0;

    pic->t0cki = 0;
    pic->t1cki = 0;

    pic->int0 = 48;
    pic->int1 = 0;
    pic->int2 = 0;

    p18_tmr0_rst(pic);
    // p18_tmr1_rst (pic);
    // p18_tmr2_rst (pic);
    // p18_adc_rst (pic);
    // p18_wdt_rst (pic);
    // p18_eeprom_rst (pic);
    // p18_mssp_rst (pic);
    // p18_int_pin_rst (pic);
    // p18_int_portb_rst (pic);
    // p18_int_ports_rst (pic);
    p18_uart_rst(pic, 0);
}

void PIC18F67J94_periferic(_pic* pic) {
    // p18_mssp (pic);
    // p18_adc (pic);
    // p18_int_pin (pic);
    // p18_int_portb (pic);
    // p18_int_ports (pic);
    p18_tmr0(pic);
    // p18_wdt (pic);
    // p18_eeprom (pic);
    // p18_tmr1 (pic);
    // p18_tmr2 (pic);
    p18_uart(pic, 0);
}

int PIC18F67J94_getconf(_pic* pic, unsigned int cfg) {
    switch (cfg) {
        case CFG_MCLR:
            return 1;
            break;
        case CFG_WDT:
            return ((pic->config[5] & 0x0300));
            break;
        case CFG_WDT_DIV:
            return ((pic->config[5] & 0x00F0) >> 4);
            break;
        case CFG_DEBUG:
            return ((pic->config[0] & 0x0080) == 0);
            break;
    }
    return 0;
}

void PIC18F67J94_disable_debug(_pic* pic) {
    pic->config[0] |= 0x0080;
}

void PIC18F67J94_stop(_pic* pic) {
    p18_uart_stop(pic, 0);
}

void PIC18F67J94_start(_pic* pic) {
    pic->ROMSIZE = 65536;
    pic->EEPROMSIZE = 0;
    pic->RAMSIZE = 4096;
    pic->PINCOUNT = 64;
    pic->IDSIZE = 0;
    pic->CONFIGSIZE = 8;
    pic->STACKSIZE = 31;
    pic->CCPCOUNT = 0;
    pic->ADCCOUNT = 17;
    pic->USARTCOUNT = 1;
    pic->WDT_MS = 1;
    pic->reset = PIC18F67J94_reset;
    pic->mmap = PIC18F67J94_map;
    pic->getconf = PIC18F67J94_getconf;
    pic->periferic = PIC18F67J94_periferic;
    pic->interrupt = interrupt18;
    pic->stop = PIC18F67J94_stop;
    pic->disable_debug = PIC18F67J94_disable_debug;

    p18_uart_start(pic, 0);
}

init_pic(PIC18F67J94, P18, 0x63A0);
