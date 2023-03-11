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
#include "../p18/p18_periferic.h"

void PIC18F4580_map(_pic* pic) {
    memset(&pic->P18map, 0, sizeof(P18map_t));
    /*
    pic->P18map.RXF6SIDH = &pic->ram[0xD60];
    pic->P18map.RXF6SIDL = &pic->ram[0xD61];
    pic->P18map.RXF6EIDH = &pic->ram[0xD62];
    pic->P18map.RXF6EIDL = &pic->ram[0xD63];
    pic->P18map.RXF7SIDH = &pic->ram[0xD64];
    pic->P18map.RXF7SIDL = &pic->ram[0xD65];
    pic->P18map.RXF7EIDH = &pic->ram[0xD66];
    pic->P18map.RXF7EIDL = &pic->ram[0xD67];
    pic->P18map.RXF8SIDH = &pic->ram[0xD68];
    pic->P18map.RXF8SIDL = &pic->ram[0xD69];
    pic->P18map.RXF8EIDH = &pic->ram[0xD6A];
    pic->P18map.RXF8EIDL = &pic->ram[0xD6B];
    pic->P18map.RXF9SIDH = &pic->ram[0xD70];
    pic->P18map.RXF9SIDL = &pic->ram[0xD71];
    pic->P18map.RXF9EIDH = &pic->ram[0xD72];
    pic->P18map.RXF9EIDL = &pic->ram[0xD73];
    pic->P18map.RXF10SIDH = &pic->ram[0xD74];
    pic->P18map.RXF10SIDL = &pic->ram[0xD75];
    pic->P18map.RXF10EIDH = &pic->ram[0xD76];
    pic->P18map.RXF10EIDL = &pic->ram[0xD77];
    pic->P18map.RXF11SIDH = &pic->ram[0xD78];
    pic->P18map.RXF11SIDL = &pic->ram[0xD79];
    pic->P18map.RXF11EIDH = &pic->ram[0xD7A];
    pic->P18map.RXF11EIDL = &pic->ram[0xD7B];
    pic->P18map.RXF12SIDH = &pic->ram[0xD80];
    pic->P18map.RXF12SIDL = &pic->ram[0xD81];
    pic->P18map.RXF12EIDH = &pic->ram[0xD82];
    pic->P18map.RXF12EIDL = &pic->ram[0xD83];
    pic->P18map.RXF13SIDH = &pic->ram[0xD84];
    pic->P18map.RXF13SIDL = &pic->ram[0xD85];
    pic->P18map.RXF13EIDH = &pic->ram[0xD86];
    pic->P18map.RXF13EIDL = &pic->ram[0xD87];
    pic->P18map.RXF14SIDH = &pic->ram[0xD88];
    pic->P18map.RXF14SIDL = &pic->ram[0xD89];
    pic->P18map.RXF14EIDH = &pic->ram[0xD8A];
    pic->P18map.RXF14EIDL = &pic->ram[0xD8B];
    pic->P18map.RXF15SIDH = &pic->ram[0xD90];
    pic->P18map.RXF15SIDL = &pic->ram[0xD91];
    pic->P18map.RXF15EIDH = &pic->ram[0xD92];
    pic->P18map.RXF15EIDL = &pic->ram[0xD93];
    pic->P18map.RXFCON0 = &pic->ram[0xDD4];
    pic->P18map.RXFCON1 = &pic->ram[0xDD5];
    pic->P18map.SDFLC = &pic->ram[0xDD8];
    pic->P18map.RXFBCON0 = &pic->ram[0xDE0];
    pic->P18map.RXFBCON1 = &pic->ram[0xDE1];
    pic->P18map.RXFBCON2 = &pic->ram[0xDE2];
    pic->P18map.RXFBCON3 = &pic->ram[0xDE3];
    pic->P18map.RXFBCON4 = &pic->ram[0xDE4];
    pic->P18map.RXFBCON5 = &pic->ram[0xDE5];
    pic->P18map.RXFBCON6 = &pic->ram[0xDE6];
    pic->P18map.RXFBCON7 = &pic->ram[0xDE7];
    pic->P18map.MSEL0 = &pic->ram[0xDF0];
    pic->P18map.MSEL1 = &pic->ram[0xDF1];
    pic->P18map.MSEL2 = &pic->ram[0xDF2];
    pic->P18map.MSEL3 = &pic->ram[0xDF3];
    pic->P18map.BSEL0 = &pic->ram[0xDF8];
    pic->P18map.BIE0 = &pic->ram[0xDFA];
    pic->P18map.TXBIE = &pic->ram[0xDFC];
    pic->P18map.B0CON = &pic->ram[0xE20];
    pic->P18map.B0SIDH = &pic->ram[0xE21];
    pic->P18map.B0SIDL = &pic->ram[0xE22];
    pic->P18map.B0EIDH = &pic->ram[0xE23];
    pic->P18map.B0EIDL = &pic->ram[0xE24];
    pic->P18map.B0DLC = &pic->ram[0xE25];
    pic->P18map.B0D0 = &pic->ram[0xE26];
    pic->P18map.B0D1 = &pic->ram[0xE27];
    pic->P18map.B0D2 = &pic->ram[0xE28];
    pic->P18map.B0D3 = &pic->ram[0xE29];
    pic->P18map.B0D4 = &pic->ram[0xE2A];
    pic->P18map.B0D5 = &pic->ram[0xE2B];
    pic->P18map.B0D6 = &pic->ram[0xE2C];
    pic->P18map.B0D7 = &pic->ram[0xE2D];
    pic->P18map.CANSTAT_RO9 = &pic->ram[0xE2E];
    pic->P18map.CANCON_RO9 = &pic->ram[0xE2F];
    pic->P18map.B1CON = &pic->ram[0xE30];
    pic->P18map.B1SIDH = &pic->ram[0xE31];
    pic->P18map.B1SIDL = &pic->ram[0xE32];
    pic->P18map.B1EIDH = &pic->ram[0xE33];
    pic->P18map.B1EIDL = &pic->ram[0xE34];
    pic->P18map.B1DLC = &pic->ram[0xE35];
    pic->P18map.B1D0 = &pic->ram[0xE36];
    pic->P18map.B1D1 = &pic->ram[0xE37];
    pic->P18map.B1D2 = &pic->ram[0xE38];
    pic->P18map.B1D3 = &pic->ram[0xE39];
    pic->P18map.B1D4 = &pic->ram[0xE3A];
    pic->P18map.B1D5 = &pic->ram[0xE3B];
    pic->P18map.B1D6 = &pic->ram[0xE3C];
    pic->P18map.B1D7 = &pic->ram[0xE3D];
    pic->P18map.CANSTAT_RO8 = &pic->ram[0xE3E];
    pic->P18map.CANCON_RO8 = &pic->ram[0xE3F];
    pic->P18map.B2CON = &pic->ram[0xE40];
    pic->P18map.B2SIDH = &pic->ram[0xE41];
    pic->P18map.B2SIDL = &pic->ram[0xE42];
    pic->P18map.B2EIDH = &pic->ram[0xE43];
    pic->P18map.B2EIDL = &pic->ram[0xE44];
    pic->P18map.B2DLC = &pic->ram[0xE45];
    pic->P18map.B2D0 = &pic->ram[0xE46];
    pic->P18map.B2D1 = &pic->ram[0xE47];
    pic->P18map.B2D2 = &pic->ram[0xE48];
    pic->P18map.B2D3 = &pic->ram[0xE49];
    pic->P18map.B2D4 = &pic->ram[0xE4A];
    pic->P18map.B2D5 = &pic->ram[0xE4B];
    pic->P18map.B2D6 = &pic->ram[0xE4C];
    pic->P18map.B2D7 = &pic->ram[0xE4D];
    pic->P18map.CANSTAT_RO7 = &pic->ram[0xE4E];
    pic->P18map.CANCON_RO7 = &pic->ram[0xE4F];
    pic->P18map.B3CON = &pic->ram[0xE50];
    pic->P18map.B3SIDH = &pic->ram[0xE51];
    pic->P18map.B3SIDL = &pic->ram[0xE52];
    pic->P18map.B3EIDH = &pic->ram[0xE53];
    pic->P18map.B3EIDL = &pic->ram[0xE54];
    pic->P18map.B3DLC = &pic->ram[0xE55];
    pic->P18map.B3D0 = &pic->ram[0xE56];
    pic->P18map.B3D1 = &pic->ram[0xE57];
    pic->P18map.B3D2 = &pic->ram[0xE58];
    pic->P18map.B3D3 = &pic->ram[0xE59];
    pic->P18map.B3D4 = &pic->ram[0xE5A];
    pic->P18map.B3D5 = &pic->ram[0xE5B];
    pic->P18map.B3D6 = &pic->ram[0xE5C];
    pic->P18map.B3D7 = &pic->ram[0xE5D];
    pic->P18map.CANSTAT_RO6 = &pic->ram[0xE5E];
    pic->P18map.CANCON_RO6 = &pic->ram[0xE5F];
    pic->P18map.B4CON = &pic->ram[0xE60];
    pic->P18map.B4SIDH = &pic->ram[0xE61];
    pic->P18map.B4SIDL = &pic->ram[0xE62];
    pic->P18map.B4EIDH = &pic->ram[0xE63];
    pic->P18map.B4EIDL = &pic->ram[0xE64];
    pic->P18map.B4DLC = &pic->ram[0xE65];
    pic->P18map.B4D0 = &pic->ram[0xE66];
    pic->P18map.B4D1 = &pic->ram[0xE67];
    pic->P18map.B4D2 = &pic->ram[0xE68];
    pic->P18map.B4D3 = &pic->ram[0xE69];
    pic->P18map.B4D4 = &pic->ram[0xE6A];
    pic->P18map.B4D5 = &pic->ram[0xE6B];
    pic->P18map.B4D6 = &pic->ram[0xE6C];
    pic->P18map.B4D7 = &pic->ram[0xE6D];
    pic->P18map.CANSTAT_RO5 = &pic->ram[0xE6E];
    pic->P18map.CANCON_RO5 = &pic->ram[0xE6F];
    pic->P18map.B5CON = &pic->ram[0xE70];
    pic->P18map.B5SIDH = &pic->ram[0xE71];
    pic->P18map.B5SIDL = &pic->ram[0xE72];
    pic->P18map.B5EIDH = &pic->ram[0xE73];
    pic->P18map.B5EIDL = &pic->ram[0xE74];
    pic->P18map.B5DLC = &pic->ram[0xE75];
    pic->P18map.B5D0 = &pic->ram[0xE76];
    pic->P18map.B5D1 = &pic->ram[0xE77];
    pic->P18map.B5D2 = &pic->ram[0xE78];
    pic->P18map.B5D3 = &pic->ram[0xE79];
    pic->P18map.B5D4 = &pic->ram[0xE7A];
    pic->P18map.B5D5 = &pic->ram[0xE7B];
    pic->P18map.B5D6 = &pic->ram[0xE7C];
    pic->P18map.B5D7 = &pic->ram[0xE7D];
    pic->P18map.CANSTAT_RO4 = &pic->ram[0xE7E];
    pic->P18map.CANCON_RO4 = &pic->ram[0xE7F];
    pic->P18map.RXF0SIDH = &pic->ram[0xF00];
    pic->P18map.RXF0SIDL = &pic->ram[0xF01];
    pic->P18map.RXF0EIDH = &pic->ram[0xF02];
    pic->P18map.RXF0EIDL = &pic->ram[0xF03];
    pic->P18map.RXF1SIDH = &pic->ram[0xF04];
    pic->P18map.RXF1SIDL = &pic->ram[0xF05];
    pic->P18map.RXF1EIDH = &pic->ram[0xF06];
    pic->P18map.RXF1EIDL = &pic->ram[0xF07];
    pic->P18map.RXF2SIDH = &pic->ram[0xF08];
    pic->P18map.RXF2SIDL = &pic->ram[0xF09];
    pic->P18map.RXF2EIDH = &pic->ram[0xF0A];
    pic->P18map.RXF2EIDL = &pic->ram[0xF0B];
    pic->P18map.RXF3SIDH = &pic->ram[0xF0C];
    pic->P18map.RXF3SIDL = &pic->ram[0xF0D];
    pic->P18map.RXF3EIDH = &pic->ram[0xF0E];
    pic->P18map.RXF3EIDL = &pic->ram[0xF0F];
    pic->P18map.RXF4SIDH = &pic->ram[0xF10];
    pic->P18map.RXF4SIDL = &pic->ram[0xF11];
    pic->P18map.RXF4EIDH = &pic->ram[0xF12];
    pic->P18map.RXF4EIDL = &pic->ram[0xF13];
    pic->P18map.RXF5SIDH = &pic->ram[0xF14];
    pic->P18map.RXF5SIDL = &pic->ram[0xF15];
    pic->P18map.RXF5EIDH = &pic->ram[0xF16];
    pic->P18map.RXF5EIDL = &pic->ram[0xF17];
    pic->P18map.RXM0SIDH = &pic->ram[0xF18];
    pic->P18map.RXM0SIDL = &pic->ram[0xF19];
    pic->P18map.RXM0EIDH = &pic->ram[0xF1A];
    pic->P18map.RXM0EIDL = &pic->ram[0xF1B];
    pic->P18map.RXM1SIDH = &pic->ram[0xF1C];
    pic->P18map.RXM1SIDL = &pic->ram[0xF1D];
    pic->P18map.RXM1EIDH = &pic->ram[0xF1E];
    pic->P18map.RXM1EIDL = &pic->ram[0xF1F];
    pic->P18map.TXB2CON = &pic->ram[0xF20];
    pic->P18map.TXB2SIDH = &pic->ram[0xF21];
    pic->P18map.TXB2SIDL = &pic->ram[0xF22];
    pic->P18map.TXB2EIDH = &pic->ram[0xF23];
    pic->P18map.TXB2EIDL = &pic->ram[0xF24];
    pic->P18map.TXB2DLC = &pic->ram[0xF25];
    pic->P18map.TXB2D0 = &pic->ram[0xF26];
    pic->P18map.TXB2D1 = &pic->ram[0xF27];
    pic->P18map.TXB2D2 = &pic->ram[0xF28];
    pic->P18map.TXB2D3 = &pic->ram[0xF29];
    pic->P18map.TXB2D4 = &pic->ram[0xF2A];
    pic->P18map.TXB2D5 = &pic->ram[0xF2B];
    pic->P18map.TXB2D6 = &pic->ram[0xF2C];
    pic->P18map.TXB2D7 = &pic->ram[0xF2D];
    pic->P18map.CANSTAT_RO3 = &pic->ram[0xF2E];
    pic->P18map.CANCON_RO3 = &pic->ram[0xF2F];
    pic->P18map.TXB1CON = &pic->ram[0xF30];
    pic->P18map.TXB1SIDH = &pic->ram[0xF31];
    pic->P18map.TXB1SIDL = &pic->ram[0xF32];
    pic->P18map.TXB1EIDH = &pic->ram[0xF33];
    pic->P18map.TXB1EIDL = &pic->ram[0xF34];
    pic->P18map.TXB1DLC = &pic->ram[0xF35];
    pic->P18map.TXB1D0 = &pic->ram[0xF36];
    pic->P18map.TXB1D1 = &pic->ram[0xF37];
    pic->P18map.TXB1D2 = &pic->ram[0xF38];
    pic->P18map.TXB1D3 = &pic->ram[0xF39];
    pic->P18map.TXB1D4 = &pic->ram[0xF3A];
    pic->P18map.TXB1D5 = &pic->ram[0xF3B];
    pic->P18map.TXB1D6 = &pic->ram[0xF3C];
    pic->P18map.TXB1D7 = &pic->ram[0xF3D];
    pic->P18map.CANSTAT_RO2 = &pic->ram[0xF3E];
    pic->P18map.CANCON_RO2 = &pic->ram[0xF3F];
    pic->P18map.TXB0CON = &pic->ram[0xF40];
    pic->P18map.TXB0SIDH = &pic->ram[0xF41];
    pic->P18map.TXB0SIDL = &pic->ram[0xF42];
    pic->P18map.TXB0EIDH = &pic->ram[0xF43];
    pic->P18map.TXB0EIDL = &pic->ram[0xF44];
    pic->P18map.TXB0DLC = &pic->ram[0xF45];
    pic->P18map.TXB0D0 = &pic->ram[0xF46];
    pic->P18map.TXB0D1 = &pic->ram[0xF47];
    pic->P18map.TXB0D2 = &pic->ram[0xF48];
    pic->P18map.TXB0D3 = &pic->ram[0xF49];
    pic->P18map.TXB0D4 = &pic->ram[0xF4A];
    pic->P18map.TXB0D5 = &pic->ram[0xF4B];
    pic->P18map.TXB0D6 = &pic->ram[0xF4C];
    pic->P18map.TXB0D7 = &pic->ram[0xF4D];
    pic->P18map.CANSTAT_RO1 = &pic->ram[0xF4E];
    pic->P18map.CANCON_RO1 = &pic->ram[0xF4F];
    pic->P18map.RXB1CON = &pic->ram[0xF50];
    pic->P18map.RXB1SIDH = &pic->ram[0xF51];
    pic->P18map.RXB1SIDL = &pic->ram[0xF52];
    pic->P18map.RXB1EIDH = &pic->ram[0xF53];
    pic->P18map.RXB1EIDL = &pic->ram[0xF54];
    pic->P18map.RXB1DLC = &pic->ram[0xF55];
    pic->P18map.RXB1D0 = &pic->ram[0xF56];
    pic->P18map.RXB1D1 = &pic->ram[0xF57];
    pic->P18map.RXB1D2 = &pic->ram[0xF58];
    pic->P18map.RXB1D3 = &pic->ram[0xF59];
    pic->P18map.RXB1D4 = &pic->ram[0xF5A];
    pic->P18map.RXB1D5 = &pic->ram[0xF5B];
    pic->P18map.RXB1D6 = &pic->ram[0xF5C];
    pic->P18map.RXB1D7 = &pic->ram[0xF5D];
    pic->P18map.CANSTAT_RO0 = &pic->ram[0xF5E];
    pic->P18map.CANCON_RO0 = &pic->ram[0xF5F];
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
    pic->P18map.BRGCON1 = &pic->ram[0xF70];
    pic->P18map.BRGCON2 = &pic->ram[0xF71];
    pic->P18map.BRGCON3 = &pic->ram[0xF72];
    pic->P18map.CIOCON = &pic->ram[0xF73];
    pic->P18map.COMSTAT = &pic->ram[0xF74];
    pic->P18map.RXERRCNT = &pic->ram[0xF75];
    pic->P18map.TXERRCNT = &pic->ram[0xF76];
    pic->P18map.ECANCON = &pic->ram[0xF77];
    */
    pic->P18map.PORTA = &pic->ram[0xF80];
    pic->P18map.PORTB = &pic->ram[0xF81];
    pic->P18map.PORTC = &pic->ram[0xF82];
    pic->P18map.PORTD = &pic->ram[0xF83];
    pic->P18map.PORTE = &pic->ram[0xF84];
    pic->P18map.LATA = &pic->ram[0xF89];
    pic->P18map.LATB = &pic->ram[0xF8A];
    pic->P18map.LATC = &pic->ram[0xF8B];
    pic->P18map.LATD = &pic->ram[0xF8C];
    pic->P18map.LATE = &pic->ram[0xF8D];
    pic->P18map.TRISA = &pic->ram[0xF92];
    pic->P18map.TRISB = &pic->ram[0xF93];
    pic->P18map.TRISC = &pic->ram[0xF94];
    pic->P18map.TRISD = &pic->ram[0xF95];
    pic->P18map.TRISE = &pic->ram[0xF96];
    // pic->P18map.OSCTUNE = &pic->ram[0xF9B];
    pic->P18map.PIE1 = &pic->ram[0xF9D];
    pic->P18map.PIR1 = &pic->ram[0xF9E];
    pic->P18map.IPR1 = &pic->ram[0xF9F];
    pic->P18map.PIE2 = &pic->ram[0xFA0];
    pic->P18map.PIR2 = &pic->ram[0xFA1];
    pic->P18map.IPR2 = &pic->ram[0xFA2];
    pic->P18map.PIE3 = &pic->ram[0xFA3];
    pic->P18map.PIR3 = &pic->ram[0xFA4];
    pic->P18map.IPR3 = &pic->ram[0xFA5];
    pic->P18map.EECON1 = &pic->ram[0xFA6];
    pic->P18map.EECON2 = &pic->ram[0xFA7];
    pic->P18map.EEDATA = &pic->ram[0xFA8];
    pic->P18map.EEADR = &pic->ram[0xFA9];
    pic->P18map.RCSTA = &pic->ram[0xFAB];
    pic->P18map.TXSTA = &pic->ram[0xFAC];
    pic->P18map.TXREG = &pic->ram[0xFAD];
    pic->P18map.RCREG = &pic->ram[0xFAE];
    pic->P18map.SPBRG = &pic->ram[0xFAF];
    pic->P18map.SPBRGH = &pic->ram[0xFB0];
    pic->P18map.T3CON = &pic->ram[0xFB1];
    pic->P18map.TMR3L = &pic->ram[0xFB2];
    pic->P18map.TMR3H = &pic->ram[0xFB3];
    /*
    pic->P18map.CMCON = &pic->ram[0xFB4];
    pic->P18map.CVRCON = &pic->ram[0xFB5];
    pic->P18map.ECCP1AS = &pic->ram[0xFB6];
    pic->P18map.ECCP1DEL = &pic->ram[0xFB7];
    */
    pic->P18map.BAUDCON = &pic->ram[0xFB8];
    /*
    pic->P18map.ECCP1CON = &pic->ram[0xFBA];
    pic->P18map.ECCPR1L = &pic->ram[0xFBB];
    pic->P18map.ECCPR1H = &pic->ram[0xFBC];
    */
    pic->P18map.CCP1CON = &pic->ram[0xFBD];
    pic->P18map.CCPR1L = &pic->ram[0xFBE];
    pic->P18map.CCPR1H = &pic->ram[0xFBF];
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
    // pic->P18map.HLVDCON = &pic->ram[0xFD2];
    // pic->P18map.OSCCON = &pic->ram[0xFD3];
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

01 - MCLR Vpp RE3
02 - RA0 AN0 CVref
03 - RA1 AN1
04 - RA2 AN2 Vref-
05 - RA3 AN3 Vref+
06 - RA4 T0CKI
07 - RA5 AN4 SS HLVDIN
08 - RE0 RD AN5
09 - RE1 WR AN6 C1OUT
10 - RE2 CS AN7 C2OUT
11 - Vdd
12 - Vss
13 - OSC1 CLKI RA7
14 - OSC2 CLKO RA6
15 - RC0 T1OSO T13CKI
16 - RC1 T1OSI
17 - RC2 CCP1
18 - RC3 SCK SCL
19 - RD0 PSP0 C1IN+
20 - RD1 PSP1 C1IN-
21 - RD2 PSP2 C2IN+
22 - RD3 PSP3 C2IN-
23 - RC4 SDI SDA
24 - RC5 SDO
25 - RC6 TX CK
26 - RC7 RX DT
27 - RD4 PSP4 ECCP1 P1A
28 - RD5 PSP5 P1B
29 - RD6 PSP6 P1C
30 - RD7 PSP7 P1D
31 - Vss
32 - Vdd
33 - RB0 INT0 FLT0 AN10
34 - RB1 INT1 AN8
35 - RB2 INT2 CANTX
36 - RB3 CANRX
37 - RB4 KBI0 AN9
38 - RB5 KBI1 PGM
39 - RB6 KBI2 PGC
40 - RB7 KBI3 PGD
 */

/*
======================
Family=P18
processor=PIC18F4580
deviceid=0x1a80
 */

void PIC18F4580_reset(_pic* pic) {
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
    pic->pins[5].port = pic->P18map.PORTA;
    pic->pins[5].pord = 4;
    pic->pins[6].port = pic->P18map.PORTA;
    pic->pins[6].pord = 5;
    pic->pins[7].port = pic->P18map.PORTE;
    pic->pins[7].pord = 0;
    pic->pins[8].port = pic->P18map.PORTE;
    pic->pins[8].pord = 1;
    pic->pins[9].port = pic->P18map.PORTE;
    pic->pins[9].pord = 2;
    pic->pins[10].port = P_VDD;
    pic->pins[10].pord = -1;
    pic->pins[10].value = 1;
    pic->pins[11].port = P_VSS;
    pic->pins[11].pord = -1;
    pic->pins[12].port = pic->P18map.PORTA;
    pic->pins[12].pord = 7;
    pic->pins[13].port = pic->P18map.PORTA;
    pic->pins[13].pord = 6;
    pic->pins[14].port = pic->P18map.PORTC;
    pic->pins[14].pord = 0;
    pic->pins[15].port = pic->P18map.PORTC;
    pic->pins[15].pord = 1;
    pic->pins[16].port = pic->P18map.PORTC;
    pic->pins[16].pord = 2;
    pic->pins[17].port = pic->P18map.PORTC;
    pic->pins[17].pord = 3;
    pic->pins[18].port = pic->P18map.PORTD;
    pic->pins[18].pord = 0;
    pic->pins[19].port = pic->P18map.PORTD;
    pic->pins[19].pord = 1;
    pic->pins[20].port = pic->P18map.PORTD;
    pic->pins[20].pord = 2;
    pic->pins[21].port = pic->P18map.PORTD;
    pic->pins[21].pord = 3;
    pic->pins[22].port = pic->P18map.PORTC;
    pic->pins[22].pord = 4;
    pic->pins[23].port = pic->P18map.PORTC;
    pic->pins[23].pord = 5;
    pic->pins[24].port = pic->P18map.PORTC;
    pic->pins[24].pord = 6;
    pic->pins[25].port = pic->P18map.PORTC;
    pic->pins[25].pord = 7;
    pic->pins[26].port = pic->P18map.PORTD;
    pic->pins[26].pord = 4;
    pic->pins[27].port = pic->P18map.PORTD;
    pic->pins[27].pord = 5;
    pic->pins[28].port = pic->P18map.PORTD;
    pic->pins[28].pord = 6;
    pic->pins[29].port = pic->P18map.PORTD;
    pic->pins[29].pord = 7;
    pic->pins[30].port = P_VSS;
    pic->pins[30].pord = -1;
    pic->pins[31].port = P_VDD;
    pic->pins[31].pord = -1;
    pic->pins[31].value = 1;
    pic->pins[32].port = pic->P18map.PORTB;
    pic->pins[32].pord = 0;
    pic->pins[33].port = pic->P18map.PORTB;
    pic->pins[33].pord = 1;
    pic->pins[34].port = pic->P18map.PORTB;
    pic->pins[34].pord = 2;
    pic->pins[35].port = pic->P18map.PORTB;
    pic->pins[35].pord = 3;
    pic->pins[36].port = pic->P18map.PORTB;
    pic->pins[36].pord = 4;
    pic->pins[37].port = pic->P18map.PORTB;
    pic->pins[37].pord = 5;
    pic->pins[38].port = pic->P18map.PORTB;
    pic->pins[38].pord = 6;
    pic->pins[39].port = pic->P18map.PORTB;
    pic->pins[39].pord = 7;

    pic->mclr = 1;

    pic->ccp[0].pin = 17;
    pic->ccp[1].pin = 27;

    pic->adc[0] = 36;
    pic->adc[1] = 3;
    pic->adc[2] = 4;
    pic->adc[3] = 5;
    pic->adc[4] = 7;
    pic->adc[5] = 8;
    pic->adc[6] = 9;
    pic->adc[7] = 10;
    pic->adc[8] = 34;
    pic->adc[9] = 37;
    pic->adc[10] = 33;

    pic->usart_rx[0] = 26;
    pic->usart_tx[0] = 25;

    pic->pgc = 39;
    pic->pgd = 40;

    pic->sck = 18;
    pic->sdo = 24;
    pic->sdi = 23;

    pic->t0cki = 6;
    pic->t1cki = 15;

    pic->int0 = 33;
    pic->int1 = 34;
    pic->int2 = 35;

    p18_tmr0_rst(pic);
    p18_tmr1_rst(pic);
    p18_tmr2_rst(pic);
    p18_adc_rst(pic);
    p18_wdt_rst(pic);
    p18_eeprom_rst(pic);
    p18_mssp_rst(pic);
    p18_int_pin_rst(pic);
    p18_int_portb_rst(pic);
    p18_uart_rst(pic, 0);
}

void PIC18F4580_periferic(_pic* pic) {
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

int PIC18F4580_getconf(_pic* pic, unsigned int cfg) {
    switch (cfg) {
        case CFG_MCLR:
            return ((pic->config[2] & 0x8000) > 0);
            break;
        case CFG_WDT:
            return ((pic->config[1] & 0x0100) > 0);
            break;
        case CFG_WDT_DIV:
            return ((pic->config[1] & 0x1E00) >> 9);
            break;
        case CFG_DEBUG:
            return ((pic->config[3] & 0x0080) == 0);
            break;
    }
    return 0;
}

void PIC18F4580_disable_debug(_pic* pic) {
    pic->config[3] |= 0x0080;
}

void PIC18F4580_stop(_pic* pic) {
    p18_uart_stop(pic, 0);
}

void PIC18F4580_start(_pic* pic) {
    pic->ROMSIZE = 16384;
    pic->EEPROMSIZE = 256;
    pic->RAMSIZE = 4096;
    pic->PINCOUNT = 40;
    pic->IDSIZE = 8;
    pic->CONFIGSIZE = 7;
    pic->STACKSIZE = 31;
    pic->CCPCOUNT = 2;
    pic->ADCCOUNT = 11;
    pic->USARTCOUNT = 1;
    pic->WDT_MS = 4;
    pic->reset = PIC18F4580_reset;
    pic->mmap = PIC18F4580_map;
    pic->getconf = PIC18F4580_getconf;
    pic->periferic = PIC18F4580_periferic;
    pic->interrupt = interrupt18;
    pic->stop = PIC18F4580_stop;
    pic->disable_debug = PIC18F4580_disable_debug;

    p18_uart_start(pic, 0);
}

init_pic(PIC18F4580, P18, 0x1a80);
