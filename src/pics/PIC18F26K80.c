/* ########################################################################

   PICsim - PIC simulator

   ########################################################################

   Copyright (c) : 2019-2021  Luis Claudio Gamboa Lopes

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

void PIC18F26K80_map(_pic* pic) {
    memset(&pic->P18map, 0, sizeof(P18map_t));
    /*
    pic->P18map.RXERRCNT = &pic->ram[0xE41];
    pic->P18map.TXERRCNT = &pic->ram[0xE42];
    pic->P18map.BRGCON1 = &pic->ram[0xE43];
    pic->P18map.BRGCON2 = &pic->ram[0xE44];
    pic->P18map.BRGCON3 = &pic->ram[0xE45];
    pic->P18map.RXFCON0 = &pic->ram[0xE46];
    pic->P18map.RXFCON1 = &pic->ram[0xE47];
    pic->P18map.RXF6SIDH = &pic->ram[0xE48];
    pic->P18map.RXF6SIDL = &pic->ram[0xE49];
    pic->P18map.RXF6EIDH = &pic->ram[0xE4A];
    pic->P18map.RXF6EIDL = &pic->ram[0xE4B];
    pic->P18map.RXF7SIDH = &pic->ram[0xE4C];
    pic->P18map.RXF7SIDL = &pic->ram[0xE4D];
    pic->P18map.RXF7EIDH = &pic->ram[0xE4E];
    pic->P18map.RXF7EIDL = &pic->ram[0xE4F];
    pic->P18map.RXF8SIDH = &pic->ram[0xE50];
    pic->P18map.RXF8SIDL = &pic->ram[0xE51];
    pic->P18map.RXF8EIDH = &pic->ram[0xE52];
    pic->P18map.RXF8EIDL = &pic->ram[0xE53];
    pic->P18map.RXF9SIDH = &pic->ram[0xE54];
    pic->P18map.RXF9SIDL = &pic->ram[0xE55];
    pic->P18map.RXF9EIDH = &pic->ram[0xE56];
    pic->P18map.RXF9EIDL = &pic->ram[0xE57];
    pic->P18map.RXF10SIDH = &pic->ram[0xE58];
    pic->P18map.RXF10SIDL = &pic->ram[0xE59];
    pic->P18map.RXF10EIDH = &pic->ram[0xE5A];
    pic->P18map.RXF10EIDL = &pic->ram[0xE5B];
    pic->P18map.RXF11SIDH = &pic->ram[0xE5C];
    pic->P18map.RXF11SIDL = &pic->ram[0xE5D];
    pic->P18map.RXF11EIDH = &pic->ram[0xE5E];
    pic->P18map.RXF11EIDL = &pic->ram[0xE5F];
    pic->P18map.RXF12SIDH = &pic->ram[0xE60];
    pic->P18map.RXF12SIDL = &pic->ram[0xE61];
    pic->P18map.RXF12EIDH = &pic->ram[0xE62];
    pic->P18map.RXF12EIDL = &pic->ram[0xE63];
    pic->P18map.RXF13SIDH = &pic->ram[0xE64];
    pic->P18map.RXF13SIDL = &pic->ram[0xE65];
    pic->P18map.RXF13EIDH = &pic->ram[0xE66];
    pic->P18map.RXF13EIDL = &pic->ram[0xE67];
    pic->P18map.RXF14SIDH = &pic->ram[0xE68];
    pic->P18map.RXF14SIDL = &pic->ram[0xE69];
    pic->P18map.RXF14EIDH = &pic->ram[0xE6A];
    pic->P18map.RXF14EIDL = &pic->ram[0xE6B];
    pic->P18map.RXF15SIDH = &pic->ram[0xE6C];
    pic->P18map.RXF15SIDL = &pic->ram[0xE6D];
    pic->P18map.RXF15EIDH = &pic->ram[0xE6E];
    pic->P18map.RXF15EIDL = &pic->ram[0xE6F];
    pic->P18map.SDFLC = &pic->ram[0xE70];
    pic->P18map.RXFBCON0 = &pic->ram[0xE71];
    pic->P18map.RXFBCON1 = &pic->ram[0xE72];
    pic->P18map.RXFBCON2 = &pic->ram[0xE73];
    pic->P18map.RXFBCON3 = &pic->ram[0xE74];
    pic->P18map.RXFBCON4 = &pic->ram[0xE75];
    pic->P18map.RXFBCON5 = &pic->ram[0xE76];
    pic->P18map.RXFBCON6 = &pic->ram[0xE77];
    pic->P18map.RXFBCON7 = &pic->ram[0xE78];
    pic->P18map.MSEL0 = &pic->ram[0xE79];
    pic->P18map.MSEL1 = &pic->ram[0xE7A];
    pic->P18map.MSEL2 = &pic->ram[0xE7B];
    pic->P18map.MSEL3 = &pic->ram[0xE7C];
    pic->P18map.BSEL0 = &pic->ram[0xE7D];
    pic->P18map.BIE0 = &pic->ram[0xE7E];
    pic->P18map.TXBIE = &pic->ram[0xE7F];
    pic->P18map.B0CON = &pic->ram[0xE80];
    pic->P18map.B0SIDH = &pic->ram[0xE81];
    pic->P18map.B0SIDL = &pic->ram[0xE82];
    pic->P18map.B0EIDH = &pic->ram[0xE83];
    pic->P18map.B0EIDL = &pic->ram[0xE84];
    pic->P18map.B0DLC = &pic->ram[0xE85];
    pic->P18map.B0D0 = &pic->ram[0xE86];
    pic->P18map.B0D1 = &pic->ram[0xE87];
    pic->P18map.B0D2 = &pic->ram[0xE88];
    pic->P18map.B0D3 = &pic->ram[0xE89];
    pic->P18map.B0D4 = &pic->ram[0xE8A];
    pic->P18map.B0D5 = &pic->ram[0xE8B];
    pic->P18map.B0D6 = &pic->ram[0xE8C];
    pic->P18map.B0D7 = &pic->ram[0xE8D];
    pic->P18map.CANSTAT_RO9 = &pic->ram[0xE8E];
    pic->P18map.CANCON_RO9 = &pic->ram[0xE8F];
    pic->P18map.B1CON = &pic->ram[0xE90];
    pic->P18map.B1SIDH = &pic->ram[0xE91];
    pic->P18map.B1SIDL = &pic->ram[0xE92];
    pic->P18map.B1EIDH = &pic->ram[0xE93];
    pic->P18map.B1EIDL = &pic->ram[0xE94];
    pic->P18map.B1DLC = &pic->ram[0xE95];
    pic->P18map.B1D0 = &pic->ram[0xE96];
    pic->P18map.B1D1 = &pic->ram[0xE97];
    pic->P18map.B1D2 = &pic->ram[0xE98];
    pic->P18map.B1D3 = &pic->ram[0xE99];
    pic->P18map.B1D4 = &pic->ram[0xE9A];
    pic->P18map.B1D5 = &pic->ram[0xE9B];
    pic->P18map.B1D6 = &pic->ram[0xE9C];
    pic->P18map.B1D7 = &pic->ram[0xE9D];
    pic->P18map.CANSTAT_RO8 = &pic->ram[0xE9E];
    pic->P18map.CANCON_RO8 = &pic->ram[0xE9F];
    pic->P18map.B2CON = &pic->ram[0xEA0];
    pic->P18map.B2SIDH = &pic->ram[0xEA1];
    pic->P18map.B2SIDL = &pic->ram[0xEA2];
    pic->P18map.B2EIDH = &pic->ram[0xEA3];
    pic->P18map.B2EIDL = &pic->ram[0xEA4];
    pic->P18map.B2DLC = &pic->ram[0xEA5];
    pic->P18map.B2D0 = &pic->ram[0xEA6];
    pic->P18map.B2D1 = &pic->ram[0xEA7];
    pic->P18map.B2D2 = &pic->ram[0xEA8];
    pic->P18map.B2D3 = &pic->ram[0xEA9];
    pic->P18map.B2D4 = &pic->ram[0xEAA];
    pic->P18map.B2D5 = &pic->ram[0xEAB];
    pic->P18map.B2D6 = &pic->ram[0xEAC];
    pic->P18map.B2D7 = &pic->ram[0xEAD];
    pic->P18map.CANSTAT_RO7 = &pic->ram[0xEAE];
    pic->P18map.CANCON_RO7 = &pic->ram[0xEAF];
    pic->P18map.B3CON = &pic->ram[0xEB0];
    pic->P18map.B3SIDH = &pic->ram[0xEB1];
    pic->P18map.B3SIDL = &pic->ram[0xEB2];
    pic->P18map.B3EIDH = &pic->ram[0xEB3];
    pic->P18map.B3EIDL = &pic->ram[0xEB4];
    pic->P18map.B3DLC = &pic->ram[0xEB5];
    pic->P18map.B3D0 = &pic->ram[0xEB6];
    pic->P18map.B3D1 = &pic->ram[0xEB7];
    pic->P18map.B3D2 = &pic->ram[0xEB8];
    pic->P18map.B3D3 = &pic->ram[0xEB9];
    pic->P18map.B3D4 = &pic->ram[0xEBA];
    pic->P18map.B3D5 = &pic->ram[0xEBB];
    pic->P18map.B3D6 = &pic->ram[0xEBC];
    pic->P18map.B3D7 = &pic->ram[0xEBD];
    pic->P18map.CANSTAT_RO6 = &pic->ram[0xEBE];
    pic->P18map.CANCON_RO6 = &pic->ram[0xEBF];
    pic->P18map.B4CON = &pic->ram[0xEC0];
    pic->P18map.B4SIDH = &pic->ram[0xEC1];
    pic->P18map.B4SIDL = &pic->ram[0xEC2];
    pic->P18map.B4EIDH = &pic->ram[0xEC3];
    pic->P18map.B4EIDL = &pic->ram[0xEC4];
    pic->P18map.B4DLC = &pic->ram[0xEC5];
    pic->P18map.B4D0 = &pic->ram[0xEC6];
    pic->P18map.B4D1 = &pic->ram[0xEC7];
    pic->P18map.B4D2 = &pic->ram[0xEC8];
    pic->P18map.B4D3 = &pic->ram[0xEC9];
    pic->P18map.B4D4 = &pic->ram[0xECA];
    pic->P18map.B4D5 = &pic->ram[0xECB];
    pic->P18map.B4D6 = &pic->ram[0xECC];
    pic->P18map.B4D7 = &pic->ram[0xECD];
    pic->P18map.CANSTAT_RO5 = &pic->ram[0xECE];
    pic->P18map.CANCON_RO5 = &pic->ram[0xECF];
    pic->P18map.B5CON = &pic->ram[0xED0];
    pic->P18map.B5SIDH = &pic->ram[0xED1];
    pic->P18map.B5SIDL = &pic->ram[0xED2];
    pic->P18map.B5EIDH = &pic->ram[0xED3];
    pic->P18map.B5EIDL = &pic->ram[0xED4];
    pic->P18map.B5DLC = &pic->ram[0xED5];
    pic->P18map.B5D0 = &pic->ram[0xED6];
    pic->P18map.B5D1 = &pic->ram[0xED7];
    pic->P18map.B5D2 = &pic->ram[0xED8];
    pic->P18map.B5D3 = &pic->ram[0xED9];
    pic->P18map.B5D4 = &pic->ram[0xEDA];
    pic->P18map.B5D5 = &pic->ram[0xEDB];
    pic->P18map.B5D6 = &pic->ram[0xEDC];
    pic->P18map.B5D7 = &pic->ram[0xEDD];
    pic->P18map.CANSTAT_RO4 = &pic->ram[0xEDE];
    pic->P18map.CANCON_RO4 = &pic->ram[0xEDF];
    pic->P18map.RXF0SIDH = &pic->ram[0xEE0];
    pic->P18map.RXF0SIDL = &pic->ram[0xEE1];
    pic->P18map.RXF0EIDH = &pic->ram[0xEE2];
    pic->P18map.RXF0EIDL = &pic->ram[0xEE3];
    pic->P18map.RXF1SIDH = &pic->ram[0xEE4];
    pic->P18map.RXF1SIDL = &pic->ram[0xEE5];
    pic->P18map.RXF1EIDH = &pic->ram[0xEE6];
    pic->P18map.RXF1EIDL = &pic->ram[0xEE7];
    pic->P18map.RXF2SIDH = &pic->ram[0xEE8];
    pic->P18map.RXF2SIDL = &pic->ram[0xEE9];
    pic->P18map.RXF2EIDH = &pic->ram[0xEEA];
    pic->P18map.RXF2EIDL = &pic->ram[0xEEB];
    pic->P18map.RXF3SIDH = &pic->ram[0xEEC];
    pic->P18map.RXF3SIDL = &pic->ram[0xEED];
    pic->P18map.RXF3EIDH = &pic->ram[0xEEE];
    pic->P18map.RXF3EIDL = &pic->ram[0xEEF];
    pic->P18map.RXF4SIDH = &pic->ram[0xEF0];
    pic->P18map.RXF4SIDL = &pic->ram[0xEF1];
    pic->P18map.RXF4EIDH = &pic->ram[0xEF2];
    pic->P18map.RXF4EIDL = &pic->ram[0xEF3];
    pic->P18map.RXF5SIDH = &pic->ram[0xEF4];
    pic->P18map.RXF5SIDL = &pic->ram[0xEF5];
    pic->P18map.RXF5EIDH = &pic->ram[0xEF6];
    pic->P18map.RXF5EIDL = &pic->ram[0xEF7];
    pic->P18map.RXM0SIDH = &pic->ram[0xEF8];
    pic->P18map.RXM0SIDL = &pic->ram[0xEF9];
    pic->P18map.RXM0EIDH = &pic->ram[0xEFA];
    pic->P18map.RXM0EIDL = &pic->ram[0xEFB];
    pic->P18map.RXM1SIDH = &pic->ram[0xEFC];
    pic->P18map.RXM1SIDL = &pic->ram[0xEFD];
    pic->P18map.RXM1EIDH = &pic->ram[0xEFE];
    pic->P18map.RXM1EIDL = &pic->ram[0xEFF];
    pic->P18map.TXB2CON = &pic->ram[0xF00];
    pic->P18map.TXB2SIDH = &pic->ram[0xF01];
    pic->P18map.TXB2SIDL = &pic->ram[0xF02];
    pic->P18map.TXB2EIDH = &pic->ram[0xF03];
    pic->P18map.TXB2EIDL = &pic->ram[0xF04];
    pic->P18map.TXB2DLC = &pic->ram[0xF05];
    pic->P18map.TXB2D0 = &pic->ram[0xF06];
    pic->P18map.TXB2D1 = &pic->ram[0xF07];
    pic->P18map.TXB2D2 = &pic->ram[0xF08];
    pic->P18map.TXB2D3 = &pic->ram[0xF09];
    pic->P18map.TXB2D4 = &pic->ram[0xF0A];
    pic->P18map.TXB2D5 = &pic->ram[0xF0B];
    pic->P18map.TXB2D6 = &pic->ram[0xF0C];
    pic->P18map.TXB2D7 = &pic->ram[0xF0D];
    pic->P18map.CANSTAT_RO3 = &pic->ram[0xF0E];
    pic->P18map.CANCON_RO3 = &pic->ram[0xF0F];
    pic->P18map.TXB1CON = &pic->ram[0xF10];
    pic->P18map.TXB1SIDH = &pic->ram[0xF11];
    pic->P18map.TXB1SIDL = &pic->ram[0xF12];
    pic->P18map.TXB1EIDH = &pic->ram[0xF13];
    pic->P18map.TXB1EIDL = &pic->ram[0xF14];
    pic->P18map.TXB1DLC = &pic->ram[0xF15];
    pic->P18map.TXB1D0 = &pic->ram[0xF16];
    pic->P18map.TXB1D1 = &pic->ram[0xF17];
    pic->P18map.TXB1D2 = &pic->ram[0xF18];
    pic->P18map.TXB1D3 = &pic->ram[0xF19];
    pic->P18map.TXB1D4 = &pic->ram[0xF1A];
    pic->P18map.TXB1D5 = &pic->ram[0xF1B];
    pic->P18map.TXB1D6 = &pic->ram[0xF1C];
    pic->P18map.TXB1D7 = &pic->ram[0xF1D];
    pic->P18map.CANSTAT_RO2 = &pic->ram[0xF1E];
    pic->P18map.CANCON_RO2 = &pic->ram[0xF1F];
    pic->P18map.TXB0CON = &pic->ram[0xF20];
    pic->P18map.TXB0SIDH = &pic->ram[0xF21];
    pic->P18map.TXB0SIDL = &pic->ram[0xF22];
    pic->P18map.TXB0EIDH = &pic->ram[0xF23];
    pic->P18map.TXB0EIDL = &pic->ram[0xF24];
    pic->P18map.TXB0DLC = &pic->ram[0xF25];
    pic->P18map.TXB0D0 = &pic->ram[0xF26];
    pic->P18map.TXB0D1 = &pic->ram[0xF27];
    pic->P18map.TXB0D2 = &pic->ram[0xF28];
    pic->P18map.TXB0D3 = &pic->ram[0xF29];
    pic->P18map.TXB0D4 = &pic->ram[0xF2A];
    pic->P18map.TXB0D5 = &pic->ram[0xF2B];
    pic->P18map.TXB0D6 = &pic->ram[0xF2C];
    pic->P18map.TXB0D7 = &pic->ram[0xF2D];
    pic->P18map.CANSTAT_RO1 = &pic->ram[0xF2E];
    pic->P18map.CANCON_RO1 = &pic->ram[0xF2F];
    pic->P18map.RXB1CON = &pic->ram[0xF30];
    pic->P18map.RXB1SIDH = &pic->ram[0xF31];
    pic->P18map.RXB1SIDL = &pic->ram[0xF32];
    pic->P18map.RXB1EIDH = &pic->ram[0xF33];
    pic->P18map.RXB1EIDL = &pic->ram[0xF34];
    pic->P18map.RXB1DLC = &pic->ram[0xF35];
    pic->P18map.RXB1D0 = &pic->ram[0xF36];
    pic->P18map.RXB1D1 = &pic->ram[0xF37];
    pic->P18map.RXB1D2 = &pic->ram[0xF38];
    pic->P18map.RXB1D3 = &pic->ram[0xF39];
    pic->P18map.RXB1D4 = &pic->ram[0xF3A];
    pic->P18map.RXB1D5 = &pic->ram[0xF3B];
    pic->P18map.RXB1D6 = &pic->ram[0xF3C];
    pic->P18map.RXB1D7 = &pic->ram[0xF3D];
    pic->P18map.CANSTAT_RO0 = &pic->ram[0xF3E];
    pic->P18map.CANCON_RO0 = &pic->ram[0xF3F];
    pic->P18map.CCP5CON = &pic->ram[0xF47];
    pic->P18map.CCPR5L = &pic->ram[0xF48];
    pic->P18map.CCPR5H = &pic->ram[0xF49];
    pic->P18map.CCP4CON = &pic->ram[0xF4A];
    pic->P18map.CCPR4L = &pic->ram[0xF4B];
    pic->P18map.CCPR4H = &pic->ram[0xF4C];
    pic->P18map.CCP3CON = &pic->ram[0xF4D];
    pic->P18map.CCPR3L = &pic->ram[0xF4E];
    pic->P18map.CCPR3H = &pic->ram[0xF4F];
    */
    pic->P18map.CCP2CON = &pic->ram[0xF50];
    pic->P18map.CCPR2L = &pic->ram[0xF51];
    pic->P18map.CCPR2H = &pic->ram[0xF52];
    /*
    pic->P18map.CTMUICON = &pic->ram[0xF53];
    pic->P18map.CTMUCONL = &pic->ram[0xF54];
    pic->P18map.CTMUCONH = &pic->ram[0xF55];
    pic->P18map.PADCFG1 = &pic->ram[0xF56];
    pic->P18map.PMD2 = &pic->ram[0xF57];
    pic->P18map.PMD1 = &pic->ram[0xF58];
    pic->P18map.PMD0 = &pic->ram[0xF59];
    pic->P18map.IOCB = &pic->ram[0xF5A];
    pic->P18map.WPUB = &pic->ram[0xF5B];
    pic->P18map.ANCON1 = &pic->ram[0xF5C];
    pic->P18map.ANCON0 = &pic->ram[0xF5D];
    pic->P18map.CM2CON = &pic->ram[0xF5E];
    pic->P18map.CM1CON = &pic->ram[0xF5F];
    pic->P18map.RXB0CON = &pic->ram[0xF60];
    pic->P18map.RXB0SIDH = &pic->ram[0xF61];
    pic->P18map.RXB0SIDL = &pic->ram[0xF62];
    pic->P18map.RXB0EIDH = &pic->ram[0xF63];
    pic->P18map.RXB0EIDL = &pic->ram[0xF64];
    pic->P18map.RXB0DLC = &pic->ram[0xF65];
    pic->P18map.RXB0D0 = &pic->ram[0xF66];
    pic->P18map.RXB0D1 = &pic->ram[0xF67];
    pic->P18map.RXB0D2 = &pic->ram[0xF68];
    pic->P18map.RXB0D3 = &pic->ram[0xF69];
    pic->P18map.RXB0D4 = &pic->ram[0xF6A];
    pic->P18map.RXB0D5 = &pic->ram[0xF6B];
    pic->P18map.RXB0D6 = &pic->ram[0xF6C];
    pic->P18map.RXB0D7 = &pic->ram[0xF6D];
    pic->P18map.CANSTAT = &pic->ram[0xF6E];
    pic->P18map.CANCON = &pic->ram[0xF6F];
    pic->P18map.CIOCON = &pic->ram[0xF70];
    pic->P18map.COMSTAT = &pic->ram[0xF71];
    pic->P18map.ECANCON = &pic->ram[0xF72];
    */
    pic->P18map.EEDATA = &pic->ram[0xF73];
    pic->P18map.EEADR = &pic->ram[0xF74];
    pic->P18map.EEADRH = &pic->ram[0xF75];
    pic->P18map.PIE5 = &pic->ram[0xF76];
    pic->P18map.PIR5 = &pic->ram[0xF77];
    pic->P18map.IPR5 = &pic->ram[0xF78];
    pic->P18map.TXREG2 = &pic->ram[0xF79];
    pic->P18map.RCREG2 = &pic->ram[0xF7A];
    pic->P18map.SPBRG2 = &pic->ram[0xF7B];
    pic->P18map.SPBRGH2 = &pic->ram[0xF7C];
    pic->P18map.SPBRGH1 = &pic->ram[0xF7D];
    pic->P18map.EECON2 = &pic->ram[0xF7E];
    pic->P18map.EECON1 = &pic->ram[0xF7F];
    pic->P18map.PORTA = &pic->ram[0xF80];
    pic->P18map.PORTB = &pic->ram[0xF81];
    pic->P18map.PORTC = &pic->ram[0xF82];
    pic->P18map.PORTE = &pic->ram[0xF84];
    /*
    pic->P18map.TMR4 = &pic->ram[0xF87];
    pic->P18map.T4CON = &pic->ram[0xF88];
    */
    pic->P18map.LATA = &pic->ram[0xF89];
    pic->P18map.LATB = &pic->ram[0xF8A];
    pic->P18map.LATC = &pic->ram[0xF8B];
    /*
    pic->P18map.SLRCON = &pic->ram[0xF90];
    pic->P18map.ODCON = &pic->ram[0xF91];
    */
    pic->P18map.TRISA = &pic->ram[0xF92];
    pic->P18map.TRISB = &pic->ram[0xF93];
    pic->P18map.TRISC = &pic->ram[0xF94];
    /*
    pic->P18map.CCPTMRS = &pic->ram[0xF99];
    pic->P18map.REFOCON = &pic->ram[0xF9A];
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
    // pic->P18map.RCSTA2 = &pic->ram[0xFA6];
    pic->P18map.BAUDCON1 = &pic->ram[0xFA7];
    /*
    pic->P18map.HLVDCON = &pic->ram[0xFA8];
    pic->P18map.PR4 = &pic->ram[0xFA9];
    pic->P18map.T1GCON = &pic->ram[0xFAA];
    */
    pic->P18map.RCSTA1 = &pic->ram[0xFAB];
    pic->P18map.TXSTA1 = &pic->ram[0xFAC];
    pic->P18map.TXREG1 = &pic->ram[0xFAD];
    pic->P18map.RCREG1 = &pic->ram[0xFAE];
    pic->P18map.SPBRG1 = &pic->ram[0xFAF];
    // pic->P18map.T3GCON = &pic->ram[0xFB0];
    pic->P18map.T3CON = &pic->ram[0xFB1];
    pic->P18map.TMR3L = &pic->ram[0xFB2];
    pic->P18map.TMR3H = &pic->ram[0xFB3];
    /*
    pic->P18map.CMSTAT = &pic->ram[0xFB4];
    pic->P18map.CVRCON = &pic->ram[0xFB5];
    */
    pic->P18map.PIE4 = &pic->ram[0xFB6];
    pic->P18map.PIR4 = &pic->ram[0xFB7];
    pic->P18map.IPR4 = &pic->ram[0xFB8];
    pic->P18map.BAUDCON2 = &pic->ram[0xFB9];
    // pic->P18map.TXSTA2 = &pic->ram[0xFBA];
    pic->P18map.CCP1CON = &pic->ram[0xFBB];
    pic->P18map.CCPR1L = &pic->ram[0xFBC];
    pic->P18map.CCPR1H = &pic->ram[0xFBD];
    /*
    pic->P18map.ECCP1DEL = &pic->ram[0xFBE];
    pic->P18map.ECCP1AS = &pic->ram[0xFBF];
    */
    pic->P18map.ADCON2 = &pic->ram[0xFC0];
    pic->P18map.ADCON1 = &pic->ram[0xFC1];
    pic->P18map.ADCON0 = &pic->ram[0xFC2];
    pic->P18map.ADRESL = &pic->ram[0xFC3];
    pic->P18map.ADRESH = &pic->ram[0xFC4];
    pic->P18map.SSPCON2 = &pic->ram[0xFC5];
    pic->P18map.SSPCON1 = &pic->ram[0xFC6];
    pic->P18map.SSPSTAT = &pic->ram[0xFC7];
    pic->P18map.SSPADD = &pic->ram[0xFC8];
    pic->P18map.SSPBUF = &pic->ram[0xFC9];
    pic->P18map.T2CON = &pic->ram[0xFCA];
    pic->P18map.PR2 = &pic->ram[0xFCB];
    pic->P18map.TMR2 = &pic->ram[0xFCC];
    pic->P18map.T1CON = &pic->ram[0xFCD];
    pic->P18map.TMR1L = &pic->ram[0xFCE];
    pic->P18map.TMR1H = &pic->ram[0xFCF];
    pic->P18map.RCON = &pic->ram[0xFD0];
    pic->P18map.WDTCON = &pic->ram[0xFD1];
    /*
    pic->P18map.OSCCON2 = &pic->ram[0xFD2];
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

01 - MCLR RE3
02 - RA0 CVref AN0 ULPWU
03 - RA1 AN1
04 - RA2 Vref- AN2
05 - RA3 Vref+ AN3
06 - Vddcore Vcap
07 - RA5 AN4 C2INB HLVDIN T1CKI SS CTMUI
08 - Vss
09 - OSC1 CLKIN RA7
10 - OSC2 CLKOUT RA6
11 - RC0 SOSCO SCLKI
12 - RC1 SOSCI
13 - RC2 T1G CCP2
14 - RC3 REFO SCL SCK
15 - RC4 SDA SDI
16 - RC5 SDO
17 - RC6 CANTX TX1 CK1 CCP3
18 - RC7 CANRX RX1 DT1 CCP4
19 - Vss
20 - Vdd
21 - RB0 AN10 C1INA FLT0 INT0
22 - RB1 AN8 C1INB P1B CTDIN INT1
23 - RB2 CANTX C1OUT P1C CTED1 INT2
24 - RB3 CANRX C2OUT P1D CTED2 INT3
25 - RB4 AN9 C2INA ECCP1 P1A CTPLS KBI0
26 - RB5 T0CKI T3CKI CCP5 KBI1
27 - RB6 PGC TX2 CK2 KBI2
28 - RB7 PGD T3G RX2 DT2 KBI3
 */

#include "../p18/p18_periferic.h"

/*
======================
Family=P18
processor=PIC18F26K80
deviceid=0x6120
 */

void PIC18F26K80_reset(_pic* pic) {
    pic->pins[0].port = pic->P18map.PORTE;
    pic->pins[0].pord = 3;
    pic->pins[1].port = pic->P18map.PORTA;
    pic->pins[1].pord = 0;
    pic->pins[2].port = pic->P18map.PORTA;
    pic->pins[2].pord = 1;
    pic->pins[3].port = pic->P18map.PORTA;
    pic->pins[3].pord = 2;
    pic->pins[4].port = pic->P18map.PORTA;
    pic->pins[4].pord = 3;
    pic->pins[6].port = P_VDD;
    pic->pins[6].pord = -1;
    pic->pins[7].port = P_VSS;
    pic->pins[7].pord = -1;
    pic->pins[8].port = pic->P18map.PORTA;
    pic->pins[8].pord = 7;
    pic->pins[9].port = pic->P18map.PORTA;
    pic->pins[9].pord = 6;
    pic->pins[10].port = pic->P18map.PORTC;
    pic->pins[10].pord = 0;
    pic->pins[11].port = pic->P18map.PORTC;
    pic->pins[11].pord = 1;
    pic->pins[12].port = pic->P18map.PORTC;
    pic->pins[12].pord = 2;
    pic->pins[13].port = pic->P18map.PORTC;
    pic->pins[13].pord = 3;
    pic->pins[14].port = pic->P18map.PORTC;
    pic->pins[14].pord = 4;
    pic->pins[15].port = pic->P18map.PORTC;
    pic->pins[15].pord = 5;
    pic->pins[16].port = pic->P18map.PORTC;
    pic->pins[16].pord = 6;
    pic->pins[17].port = pic->P18map.PORTC;
    pic->pins[17].pord = 7;
    pic->pins[18].port = P_VSS;
    pic->pins[18].pord = -1;
    pic->pins[19].port = P_VDD;
    pic->pins[19].pord = -1;
    pic->pins[19].value = 1;
    pic->pins[20].port = pic->P18map.PORTB;
    pic->pins[20].pord = 0;
    pic->pins[21].port = pic->P18map.PORTB;
    pic->pins[21].pord = 1;
    pic->pins[22].port = pic->P18map.PORTB;
    pic->pins[22].pord = 2;
    pic->pins[23].port = pic->P18map.PORTB;
    pic->pins[23].pord = 3;
    pic->pins[24].port = pic->P18map.PORTB;
    pic->pins[24].pord = 4;
    pic->pins[25].port = pic->P18map.PORTB;
    pic->pins[25].pord = 5;
    pic->pins[26].port = pic->P18map.PORTB;
    pic->pins[26].pord = 6;
    pic->pins[27].port = pic->P18map.PORTB;
    pic->pins[27].pord = 7;

    pic->mclr = 1;

    pic->ccp[0].pin = 0;
    pic->ccp[1].pin = 13;
    pic->ccp[2].pin = 17;
    pic->ccp[3].pin = 25;
    pic->ccp[4].pin = 26;

    pic->adc[0] = 24;
    pic->adc[1] = 3;
    pic->adc[2] = 4;
    pic->adc[3] = 5;
    pic->adc[4] = 7;
    pic->adc[5] = 0;
    pic->adc[6] = 0;
    pic->adc[7] = 0;
    pic->adc[8] = 22;
    pic->adc[9] = 25;
    pic->adc[10] = 21;
    pic->adc[11] = 0;

    pic->usart_rx[0] = 28;
    pic->usart_tx[0] = 27;

    pic->pgc = 27;
    pic->pgd = 28;

    pic->sck = 14;
    pic->sdo = 16;
    pic->sdi = 15;

    pic->t0cki = 26;
    pic->t1cki = 7;

    pic->int0 = 21;
    pic->int1 = 22;
    pic->int2 = 23;

    p18_tmr0_rst(pic);
    p18_tmr1_rst(pic);
    p18_tmr2_rst(pic);
    p18_adc_rst(pic);
    p18_wdt_rst(pic);
    p18_eeprom_rst(pic);
    p18_mssp_rst(pic);
    p18_int_pin_rst(pic);
    p18_int_portb_rst(pic);
    p18_uart_rst_4(pic, 0);
}

void PIC18F26K80_periferic(_pic* pic) {
    p18_mssp(pic);
    p18_adc(pic);
    p18_int_pin(pic);
    p18_int_portb(pic);
    p18_tmr0(pic);
    p18_wdt(pic);
    p18_eeprom(pic);
    p18_tmr1(pic);
    p18_tmr2(pic);
    p18_uart(pic, 0);
}

int PIC18F26K80_getconf(_pic* pic, unsigned int cfg) {
    switch (cfg) {
        case CFG_MCLR:
            return ((pic->config[2] & 0x8000) > 0);
            break;
        case CFG_WDT:
            return (pic->config[1] & 0x0300) >> 3;
            break;
        case CFG_WDT_DIV:
            return (pic->config[1] & 0x7C00) >> 10;
            break;
        case CFG_DEBUG:
            return ((pic->config[3] & 0x0080) == 0);
            break;
    }
    return 0;
}

void PIC18F26K80_disable_debug(_pic* pic) {
    pic->config[3] |= 0x0080;
}

void PIC18F26K80_stop(_pic* pic) {
    p18_uart_stop(pic, 0);
}

void PIC18F26K80_start(_pic* pic) {
    pic->ROMSIZE = 32768;
    pic->EEPROMSIZE = 1024;
    pic->RAMSIZE = 4096;
    pic->PINCOUNT = 28;
    pic->IDSIZE = 8;
    pic->CONFIGSIZE = 7;
    pic->STACKSIZE = 31;
    pic->CCPCOUNT = 5;
    pic->ADCCOUNT = 12;
    pic->USARTCOUNT = 1;
    pic->WDT_MS = 4;
    pic->reset = PIC18F26K80_reset;
    pic->mmap = PIC18F26K80_map;
    pic->getconf = PIC18F26K80_getconf;
    pic->periferic = PIC18F26K80_periferic;
    pic->interrupt = interrupt18_2;
    pic->stop = PIC18F26K80_stop;
    pic->disable_debug = PIC18F26K80_disable_debug;

    p18_uart_start(pic, 0);
}

init_pic(PIC18F26K80, P18, 0x6120);
