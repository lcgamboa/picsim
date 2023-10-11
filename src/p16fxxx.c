/* ########################################################################

   PICsim - PIC simulator

   ########################################################################

   Copyright (c) : 2008-2022  Luis Claudio Gamboa Lopes

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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/picsim.h"

void pic_decode_16(_pic* pic) {
    unsigned short temp;
    unsigned short opc;
    unsigned short bank = ((*pic->P16map.STATUS) & 0x0060) << 2;
    unsigned short afsr =
        (((*pic->P16map.STATUS) & 0x0080) << 1) | pic->ram[bank | (sfr_addr(pic->P16map.FSR) & 0x007F)];
    //  unsigned short  pc_ant;

    if (pic->pc != 0x2004)
        opc = pic->prog[pic->pc];
    else
        opc = pic->id[4];

    pic->lram = 0x8000;
    pic->rram = 0x8000;

    if (pic->sleep == 1) {
        if (pic->print)
            printf("sleep WDT=%i wdt=%f ms=%i\n", pic->getconf(pic, CFG_WDT), pic->twdt, pic->wdt);
        return;
    }

    if (pic->s2 == 1) {
        pic->s2 = 0;
        if (pic->jpc != 0xFFFFF) {
            pic->pc = pic->jpc;
            pic->jpc = 0xFFFFF;
        }
        return;
    }

    // print (Address)
    if (pic->print) {
        printf("pc=%#06X\t", pic->pc);
        if (pic->pc != 0x2004)
            printf("prog=%#06X\t", pic->prog[pic->pc]);
        else
            printf("prog=%#06X\t", pic->id[4]);
    }

    pic->pc++;
    if (pic->pc >= pic->ROMSIZE)
        pic->pc = 0;

    // pc
    temp = pic->pc & 0x00FF;
    pic->ram[(0x0000) | (sfr_addr(pic->P16map.PCL) & 0x007F)] = temp;
    pic->ram[(0x0080) | (sfr_addr(pic->P16map.PCL) & 0x007F)] = temp;
    if (pic->processor != P16F84A) {
        pic->ram[(0x0100) | (sfr_addr(pic->P16map.PCL) & 0x007F)] = temp;
        pic->ram[(0x0180) | (sfr_addr(pic->P16map.PCL) & 0x007F)] = temp;
    }
    // pc_ant = temp;

    temp = pic->ram[afsr];
    pic->ram[(0x0000) | (sfr_addr(pic->P16map.INDF) & 0x007F)] = temp;
    pic->ram[(0x0080) | (sfr_addr(pic->P16map.INDF) & 0x007F)] = temp;
    if (pic->processor != P16F84A) {
        pic->ram[(0x0100) | (sfr_addr(pic->P16map.INDF) & 0x007F)] = temp;
        pic->ram[(0x0180) | (sfr_addr(pic->P16map.INDF) & 0x007F)] = temp;
    }

    switch (opc & 0x3000) {
        case 0x0000:
            switch (opc & 0x0F00) {
                case 0x0000:
                    switch (opc & 0x0080) {
                        case 0x0000:
                            switch (opc & 0x007F) {
                                case 0x0000:
                                case 0x0020:
                                case 0x0040:
                                case 0x0060:
                                    // NOP     --  	No Operation                 1     0000000
                                    // xx00000
                                    if (pic->print)
                                        printf("NOP\n");
                                    break;
                                case 0x0008:
                                    /// RETURN  --  	Return from Subroutine       2     0000000
                                    /// 0001000
                                    if (pic->print)
                                        printf("RETURN\n");
                                    pic->jpc = pic->stack[0];
                                    for (temp = 0; temp < 7; temp++)
                                        pic->stack[temp] = pic->stack[temp + 1];
                                    pic->stack[7] = 0;
                                    pic->s2 = 1;
                                    //		  if((pic->ram[ICKBUG] & 0x80)== 0x80)printf("Out DEBUG
                                    // mode\n");
                                    pic->debug = 0;
                                    pic->sstep = 0;
                                    pic->dbg = 0;
#ifdef ICSPDBG
                                    (*pic->P16map.ICKBUG) &= ~0x80;
#endif
                                    break;
                                case 0x0063: {
                                    unsigned char* status = &pic->ram[bank | (sfr_addr(pic->P16map.STATUS) & 0x007F)];
                                    // SLEEP   --  	Go into Standby mode         1     0000000
                                    // 1100011 TO,PD
                                    if (pic->print)
                                        printf("SLEEP\n");
                                    pic->wdt = 0;
                                    pic->twdt = 0;
                                    pic->sleep = 1;
                                    *status &= ~0x08;
                                    *status |= 0x10;
                                } break;
                                case 0x0064: {
                                    unsigned char* status = &pic->ram[bank | (sfr_addr(pic->P16map.STATUS) & 0x007F)];
                                    // CLRWDT  --  	Clear Watchdog Timer         1     0000000
                                    // 1100100 TO,PD
                                    if (pic->print)
                                        printf("CLRWDT\n");
                                    pic->wdt = 0;
                                    pic->twdt = 0;
                                    *status |= 0x08;
                                    *status |= 0x10;
                                } break;
                                case 0x0009: {
                                    // RETFIE  --  	Return from interrupt        2     0000000
                                    // 0001001
                                    unsigned char* intcon = &pic->ram[bank | (sfr_addr(pic->P16map.INTCON) & 0x007F)];
                                    if (pic->print)
                                        printf("RETFIE\n");
                                    pic->jpc = pic->stack[0];
                                    for (temp = 0; temp < 7; temp++)
                                        pic->stack[temp] = pic->stack[temp + 1];
                                    pic->stack[7] = 0;
                                    pic->s2 = 1;
                                    *intcon |= 0x80;
                                    pic->lram = sfr_addr(pic->P16map.INTCON);
                                } break;
                                default:
                                    printf("unknown opcode 0x%04X at 0x%06X !\n", opc, pic->pc - 2);
                                    break;
                            };
                            break;
                        case 0x0080:
                            // MOVWF   f  	Move W to f                  1     0000001 fffffff
                            if (pic->print)
                                printf("MOVWF %#04X\n", opc & 0x007F);
                            pic->ram[bank | (opc & 0x007F)] = pic->w;
                            pic->lram = bank | (opc & 0x007F);
                            break;
                        default:
                            printf("unknown opcode 0x%04X at 0x%06X !\n", opc, pic->pc - 2);
                            break;
                    }
                    break;
                case 0x0100:
                    switch (opc & 0x0080) {
                        case 0x0000:
                            // CLRW    --  	Clear W                      1     0000010 xxxxxxx Z
                            if (pic->print)
                                printf("CLRW\n");
                            pic->w = 0;
                            break;
                        case 0x0080:
                            // CLRF    f  	Clear f                      1     0000011 fffffff Z 2
                            if (pic->print)
                                printf("CLRF %#04X\n", opc & 0x007F);
                            pic->ram[bank | (opc & 0x007F)] = 0;
                            pic->lram = bank | (opc & 0x007F);
                            break;
                        default:
                            printf("unknown opcode 0x%04X at 0x%06X !\n", opc, pic->pc - 2);
                            break;
                    };
                    break;
                case 0x0200: {
                    // SUBWF   f, d 	Subtract W from f            1     000010 dfffffff
                    // C,DC,Z  1, 2
                    unsigned char* status = &pic->ram[bank | (sfr_addr(pic->P16map.STATUS) & 0x007F)];
                    if (pic->print)
                        printf("SUBWF %#04X,%d\n", opc & 0x007F, (opc & 0x0080) >> 7);

                    if ((0xF0 & ((0x0F & (~pic->w)) + 1 + (0x0F & pic->ram[bank | (opc & 0x007F)]))) != 0)
                        *status |= 0x02;
                    else
                        *status &= ~0x02;

                    temp = (~pic->w + 1) + pic->ram[bank | (opc & 0x007F)];

                    if ((0xFF00 & temp) != 0)
                        *status &= ~0x01;
                    else
                        *status |= 0x01;

                    if ((opc & 0x0080) == 0) {
                        pic->w = (unsigned char)(0x00FF & temp);
                        if (pic->w == 0)
                            *status |= 0x04;
                        else
                            *status &= ~0x04;
                    } else {
                        pic->ram[bank | (opc & 0x007F)] = (unsigned char)(0x00FF & temp);
                        pic->lram = bank | (opc & 0x007F);
                        if (pic->ram[bank | (opc & 0x007F)] == 0)
                            *status |= 0x04;
                        else
                            *status &= ~0x04;
                    }
                } break;
                case 0x0300: {
                    // DECF    f, d 	Decrement f                  1     000011 dfffffff Z 1,
                    // 2
                    unsigned char* status = &pic->ram[bank | (sfr_addr(pic->P16map.STATUS) & 0x007F)];
                    if (pic->print)
                        printf("DECF %#04X,%d\n", opc & 0x007F, (opc & 0x0080) >> 7);
                    if ((opc & 0x0080) == 0) {
                        pic->w = pic->ram[bank | (opc & 0x007F)] - 1;
                        if (pic->w == 0)
                            *status |= 0x04;
                        else
                            *status &= ~0x04;
                    } else {
                        pic->ram[bank | (opc & 0x007F)]--;
                        pic->lram = bank | (opc & 0x007F);
                        if (pic->ram[bank | (opc & 0x007F)] == 0)
                            *status |= 0x04;
                        else
                            *status &= ~0x04;
                    }
                } break;
                case 0x0400: {
                    // IORWF   f, d 	Inclusive OR W with f        1     000100 dfffffff Z 1,
                    // 2
                    unsigned char* status = &pic->ram[bank | (sfr_addr(pic->P16map.STATUS) & 0x007F)];
                    if (pic->print)
                        printf("IORWF %#04X,%d\n", opc & 0x007F, (opc & 0x0080) >> 7);
                    if ((opc & 0x0080) == 0) {
                        pic->w = pic->w | pic->ram[bank | (opc & 0x007F)];
                        if (pic->w == 0)
                            *status |= 0x04;
                        else
                            *status &= ~0x04;
                    } else {
                        pic->ram[bank | (opc & 0x007F)] = pic->w | pic->ram[bank | (opc & 0x007F)];
                        pic->lram = bank | (opc & 0x007F);
                        if (pic->ram[bank | (opc & 0x007F)] == 0)
                            *status |= 0x04;
                        else
                            *status &= ~0x04;
                    }
                } break;
                case 0x0500: {
                    // ANDWF   f, d 	AND W with f                 1     000101 dfffffff
                    // Z       1, 2
                    unsigned char* status = &pic->ram[bank | (sfr_addr(pic->P16map.STATUS) & 0x007F)];
                    if (pic->print)
                        printf("ANDWF %#04X,%d\n", opc & 0x007F, (opc & 0x0080) >> 7);
                    if ((opc & 0x0080) == 0) {
                        pic->w = pic->w & pic->ram[bank | (opc & 0x007F)];
                        if (pic->w == 0)
                            *status |= 0x04;
                        else
                            *status &= ~0x04;
                    } else {
                        pic->ram[bank | (opc & 0x007F)] = pic->w & pic->ram[bank | (opc & 0x007F)];
                        pic->lram = bank | (opc & 0x007F);
                        if (pic->ram[bank | (opc & 0x007F)] == 0)
                            *status |= 0x04;
                        else
                            *status &= ~0x04;
                    }
                } break;
                case 0x0600: {
                    // XORWF   f, d 	Exclusive OR W with f        1     000110 dfffffff Z 1,
                    // 2
                    unsigned char* status = &pic->ram[bank | (sfr_addr(pic->P16map.STATUS) & 0x007F)];
                    if (pic->print)
                        printf("XORWF %#04X,%d\n", opc & 0x007F, (opc & 0x0080) >> 7);
                    if ((opc & 0x0080) == 0) {
                        pic->w = pic->w ^ pic->ram[bank | (opc & 0x007F)];
                        if (pic->w == 0)
                            *status |= 0x04;
                        else
                            *status &= ~0x04;
                    } else {
                        pic->ram[bank | (opc & 0x007F)] = pic->w ^ pic->ram[bank | (opc & 0x007F)];
                        pic->lram = bank | (opc & 0x007F);
                        if (pic->ram[bank | (opc & 0x007F)] == 0)
                            *status |= 0x04;
                        else
                            *status &= ~0x04;
                    }
                } break;
                case 0x0700: {
                    // ADDWF	f, d 	Add W and f                  1     000111 dfffffff
                    // C,DC,Z  1, 2
                    unsigned char* status = &pic->ram[bank | (sfr_addr(pic->P16map.STATUS) & 0x007F)];
                    if (pic->print)
                        printf("ADDWF %#04X,%d\n", opc & 0x007F, (opc & 0x0080) >> 7);

                    if ((0xF0 & ((0x0F & pic->w) + (0x0F & pic->ram[bank | (opc & 0x007F)]))) != 0)
                        *status |= 0x02;
                    else
                        *status &= ~0x02;

                    temp = pic->w + pic->ram[bank | (opc & 0x007F)];

                    if ((0xFF00 & temp) != 0)
                        *status |= 0x01;
                    else
                        *status &= ~0x01;

                    if ((opc & 0x0080) == 0) {
                        pic->w = (unsigned char)(0x00FF & temp);
                        if (pic->w == 0)
                            *status |= 0x04;
                        else
                            *status &= ~0x04;
                    } else {
                        pic->ram[bank | (opc & 0x007F)] = (unsigned char)(0x00FF & temp);
                        pic->lram = bank | (opc & 0x007F);
                        if (pic->ram[bank | (opc & 0x007F)] == 0)
                            *status |= 0x04;
                        else
                            *status &= ~0x04;
                    }
                } break;
                case 0x0800: {
                    // MOVF    f, d 	Move f                       1     001000 dfffffff Z 1,
                    // 2
                    unsigned char* status = &pic->ram[bank | (sfr_addr(pic->P16map.STATUS) & 0x007F)];
                    if (pic->print)
                        printf("MOVF %#04X,%d\n", opc & 0x007F, (opc & 0x0080) >> 7);
                    if ((opc & 0x0080) == 0) {
                        pic->w = pic->ram[bank | (opc & 0x007F)];
                        if (pic->w == 0)
                            *status |= 0x04;
                        else
                            *status &= ~0x04;
                        pic->rram = bank | (opc & 0x007F);
                    } else {
                        if (pic->ram[bank | (opc & 0x007F)] == 0)
                            *status |= 0x04;
                        else
                            *status &= ~0x04;
                        pic->rram = bank | (opc & 0x007F);
                        pic->lram = bank | (opc & 0x007F);
                    }
                } break;
                case 0x0900: {
                    // COMF    f, d 	Complement f                 1     001001 dfffffff Z 1,
                    // 2
                    unsigned char* status = &pic->ram[bank | (sfr_addr(pic->P16map.STATUS) & 0x007F)];
                    if (pic->print)
                        printf("COMF %#04X,%d\n", opc & 0x007F, (opc & 0x0080) >> 7);
                    if ((opc & 0x0080) == 0) {
                        pic->w = ~pic->ram[bank | (opc & 0x007F)];
                        if (pic->w == 0)
                            *status |= 0x04;
                        else
                            *status &= ~0x04;
                    } else {
                        pic->ram[bank | (opc & 0x007F)] = ~pic->ram[bank | (opc & 0x007F)];
                        pic->lram = bank | (opc & 0x007F);
                        if (pic->ram[bank | (opc & 0x007F)] == 0)
                            *status |= 0x04;
                        else
                            *status &= ~0x04;
                    }
                } break;
                case 0x0A00: {
                    // INCF    f, d 	Increment f                  1     001010 dfffffff
                    // Z       1, 2
                    unsigned char* status = &pic->ram[bank | (sfr_addr(pic->P16map.STATUS) & 0x007F)];
                    if (pic->print)
                        printf("INCF %#04X,%d\n", opc & 0x007F, (opc & 0x0080) >> 7);
                    if ((opc & 0x0080) == 0) {
                        pic->w = pic->ram[bank | (opc & 0x007F)] + 1;
                        if (pic->w == 0)
                            *status |= 0x04;
                        else
                            *status &= ~0x04;
                    } else {
                        pic->ram[bank | (opc & 0x007F)]++;
                        pic->lram = bank | (opc & 0x007F);
                        if (pic->ram[bank | (opc & 0x007F)] == 0)
                            *status |= 0x04;
                        else
                            *status &= ~0x04;
                    }
                } break;
                case 0x0B00:
                    // DECFSZ  f, d 	Decrement f, Skip if 0       1(2)  001011 dfffffff
                    // 1, 2, 3
                    if (pic->print)
                        printf("DECFSZ %#04X,%d\n", opc & 0x007F, (opc & 0x0080) >> 7);
                    if ((opc & 0x0080) == 0) {
                        pic->w = pic->ram[bank | (opc & 0x007F)] - 1;
                        if (pic->w == 0) {
                            pic->jpc = pic->pc + 1;
                            pic->s2 = 1;
                        };
                    } else {
                        pic->ram[bank | (opc & 0x007F)]--;
                        pic->lram = bank | (opc & 0x007F);
                        if (pic->ram[bank | (opc & 0x007F)] == 0) {
                            pic->jpc = pic->pc + 1;
                            pic->s2 = 1;
                        };
                    };
                    break;
                case 0x0C00: {
                    // RRF     f, d 	Rotate Right f through Carry 1     001100 dfffffff
                    // C       1, 2
                    unsigned char* status = &pic->ram[bank | (sfr_addr(pic->P16map.STATUS) & 0x007F)];
                    if (pic->print)
                        printf("RRF %#04X,%d\n", opc & 0x007F, (opc & 0x0080) >> 7);
                    temp = (pic->ram[bank | (opc & 0x007F)]);
                    if ((*status & 0x01) == 0x01)
                        temp |= 0x0100;
                    if ((temp & 0x0001) == 0x01)
                        *status |= 0x01;
                    else
                        *status &= ~0x01;
                    temp = temp >> 1;
                    pic->rram = bank | (opc & 0x007F);
                    if ((opc & 0x0080) == 0) {
                        pic->w = 0x00FF & temp;
                    } else {
                        pic->ram[bank | (opc & 0x007F)] = 0x00FF & temp;
                        pic->lram = bank | (opc & 0x007F);
                    }
                } break;
                case 0x0D00: {
                    // RLF     f, d 	Rotate Left f through Carry  1     001101 dfffffff
                    // C       1, 2
                    unsigned char* status = &pic->ram[bank | (sfr_addr(pic->P16map.STATUS) & 0x007F)];
                    if (pic->print)
                        printf("RLF %#04X,%d\n", opc & 0x007F, (opc & 0x0080) >> 7);
                    temp = (pic->ram[bank | (opc & 0x007F)]);
                    temp = temp << 1;
                    if ((*status & 0x01) == 0x01)
                        temp |= 0x0001;
                    if ((temp & 0x0100) == 0x0100)
                        *status |= 0x0001;
                    else
                        *status &= ~0x0001;
                    pic->rram = bank | (opc & 0x007F);
                    if ((opc & 0x0080) == 0) {
                        pic->w = 0x00FF & temp;
                    } else {
                        pic->ram[bank | (opc & 0x007F)] = 0x00FF & temp;
                        pic->lram = bank | (opc & 0x007F);
                    }
                } break;
                case 0x0E00:
                    // SWAPF   f, d 	Swap nibbles in f            1     001110 dfffffff
                    // 1, 2
                    if (pic->print)
                        printf("SWAPF %#04X,%d\n", opc & 0x007F, (opc & 0x0080) >> 7);
                    if ((opc & 0x0080) == 0) {
                        pic->w = ((pic->ram[bank | (opc & 0x007F)] & 0x0F) << 4) |
                                 ((pic->ram[bank | (opc & 0x007F)] & 0xF0) >> 4);

                    } else {
                        pic->ram[bank | (opc & 0x007F)] = ((pic->ram[bank | (opc & 0x007F)] & 0x0F) << 4) |
                                                          ((pic->ram[bank | (opc & 0x007F)] & 0xF0) >> 4);
                        pic->lram = bank | (opc & 0x007F);
                    };
                    break;
                case 0x0F00:
                    // INCFSZ  f, d 	Increment f, Skip if 0       1(2)  001111 dfffffff
                    // 1, 2, 3
                    if (pic->print)
                        printf("INCFSZ %#04X,%d\n", opc & 0x007F, (opc & 0x0080) >> 7);
                    if ((opc & 0x0080) == 0) {
                        pic->w = pic->ram[bank | (opc & 0x007F)] + 1;
                        if (pic->w == 0) {
                            pic->jpc = pic->pc + 1;
                            pic->s2 = 1;
                        };
                    } else {
                        pic->ram[bank | (opc & 0x007F)]++;
                        pic->lram = bank | (opc & 0x007F);
                        if (pic->ram[bank | (opc & 0x007F)] == 0) {
                            pic->jpc = pic->pc + 1;
                            pic->s2 = 1;
                        };
                    };
                    break;
                default:
                    printf("unknown opcode 0x%04X at 0x%06X !\n", opc, pic->pc - 2);
                    break;
            }
            break;
        case 0x1000:
            switch (opc & 0x0C00) {
                case 0x0000:
                    // BCF     f, b 	Bit Clear f                  1     0100 bbbfffffff 1, 2
                    if (pic->print)
                        printf("BCF %#04X,%d\n", opc & 0x007F, (opc & 0x0380) >> 7);
                    pic->ram[bank | (opc & 0x007F)] &= ~(0x01 << ((opc & 0x0380) >> 7));
                    pic->lram = bank | (opc & 0x007F);
                    break;
                case 0x0400:
                    // BSF     f, b 	Bit Set f                    1     0101 bbbfffffff 1, 2
                    if (pic->print)
                        printf("BSF %#04X,%d\n", opc & 0x007F, (opc & 0x0380) >> 7);
                    pic->ram[bank | (opc & 0x007F)] |= (0x01 << ((opc & 0x0380) >> 7));
                    pic->lram = bank | (opc & 0x007F);
                    break;
                case 0x0800:
                    // BTFSC   f, b 	Bit Test f, Skip if Clear    1(2)  0110 bbbfffffff 3
                    if (pic->print)
                        printf("BTFSC %#04X,%d\n", opc & 0x007F, (opc & 0x0380) >> 7);
                    if ((pic->ram[bank | (opc & 0x007F)] & (0x01 << ((opc & 0x0380) >> 7))) == 0) {
                        pic->jpc = pic->pc + 1;
                        pic->s2 = 1;
                    }
                    break;
                case 0x0C00:
                    // BTFSS   f, b 	Bit Test f, Skip if Set      1(2)  0111 bbbfffffff 3
                    if (pic->print)
                        printf("BTFSS %#04X,%d\n", opc & 0x007F, (opc & 0x0380) >> 7);
                    if ((pic->ram[bank | (opc & 0x007F)] & (0x01 << ((opc & 0x0380) >> 7))) != 0) {
                        pic->jpc = pic->pc + 1;
                        pic->s2 = 1;
                    }
                    break;
                default:
                    printf("unknown opcode 0x%04X at 0x%06X !\n", opc, pic->pc - 2);
                    break;
            };
            break;
        case 0x2000:
            switch (opc & 0x0800) {
                case 0x0000:
                    // CALL    k  	Call subroutine              2     100 kkkkkkkkkkk
                    if (pic->print)
                        printf("CALL %#05X\n", opc & 0x07FF);
                    for (temp = 7; temp > 0; temp--)
                        pic->stack[temp] = pic->stack[temp - 1];
                    pic->stack[0] = pic->pc;
                    pic->jpc =
                        ((pic->ram[bank | (sfr_addr(pic->P16map.PCLATH) & 0x007F)] & 0x18) << 8) | (opc & 0x07FF);
                    pic->s2 = 1;
                    break;
                case 0x0800:
                    // GOTO    k  	Go to address                2     101 kkkkkkkkkkk
                    if (pic->print)
                        printf("GOTO %#05X\n", opc & 0x07FF);
#ifdef ICSPDBG
                    if (pic->getconf(CFG_DEBUG) && ((((*pic->P16map.ICKBUG)) & 0x80) == 0x80))  // DEBUG ON
                        //	    pic->jpc=((0x18)<<8)|(opc & 0x07FF);
                        pic->jpc = (pic->ROMSIZE - 1) & (((0xF8) << 8) | (opc & 0x07FF));
                    else
                        pic->jpc =
                            ((pic->ram[bank | (sfr_addr(pic->P16map.PCLATH) & 0x007F)] & 0x18) << 8) | (opc & 0x07FF);
#else
                    pic->jpc =
                        ((pic->ram[bank | (sfr_addr(pic->P16map.PCLATH) & 0x007F)] & 0x18) << 8) | (opc & 0x07FF);
#endif
                    pic->s2 = 1;
                    break;
                default:
                    printf("unknown opcode 0x%04X at 0x%06X !\n", opc, pic->pc - 2);
                    break;
            }
            break;
        case 0x3000:
            switch (opc & 0x0F00) {
                case 0x0000:
                case 0x0100:
                case 0x0200:
                case 0x0300:
                    // MOVLW   k  	Move literal to W            1     1100xx kkkkkkkk
                    if (pic->print)
                        printf("MOVLW %#04X\n", opc & 0x00FF);
                    pic->w = (opc & 0x00FF);
                    break;
                case 0x0400:
                case 0x0500:
                case 0x0600:
                case 0x0700:
                    // RETLW   k  	Return with literal in W     2     1101xx kkkkkkkk
                    if (pic->print)
                        printf("RETLW %#04X\n", opc & 0x00FF);
                    pic->jpc = pic->stack[0];
                    for (temp = 0; temp < 7; temp++)
                        pic->stack[temp] = pic->stack[temp + 1];
                    pic->stack[7] = 0;
                    pic->s2 = 1;
                    pic->w = (opc & 0x00FF);
                    break;
                case 0x0800: {
                    // IORLW   k  	Inclusive OR literal with W  1     111000 kkkkkkkk Z
                    unsigned char* status = &pic->ram[bank | (sfr_addr(pic->P16map.STATUS) & 0x007F)];
                    if (pic->print)
                        printf("IORLW %#04X\n", opc & 0x00FF);
                    pic->w |= (opc & 0x00FF);
                    if (pic->w == 0)
                        *status |= 0x04;
                    else
                        *status &= ~0x04;
                } break;
                case 0x0900: {
                    // ANDLW   k 	AND literal with W           1     111001 kkkkkkkk Z
                    unsigned char* status = &pic->ram[bank | (sfr_addr(pic->P16map.STATUS) & 0x007F)];
                    if (pic->print)
                        printf("ANDLW %#04X\n", opc & 0x00FF);
                    pic->w &= (opc & 0x00FF);
                    if (pic->w == 0)
                        *status |= 0x04;
                    else
                        *status &= ~0x04;
                } break;
                case 0x0A00: {
                    // XORLW   k  	Exclusive OR literal with W  1     111010 kkkkkkkk Z
                    unsigned char* status = &pic->ram[bank | (sfr_addr(pic->P16map.STATUS) & 0x007F)];
                    if (pic->print)
                        printf("XORLW %#04X\n", opc & 0x00FF);
                    pic->w ^= (opc & 0x00FF);
                    if (pic->w == 0)
                        *status |= 0x04;
                    else
                        *status &= ~0x04;
                } break;
                case 0x0C00:
                case 0x0D00: {
                    // SUBLW   k  	Subtract W from literal      1     11110x kkkkkkkk
                    // C,DC,Z
                    unsigned char* status = &pic->ram[bank | (sfr_addr(pic->P16map.STATUS) & 0x007F)];
                    if (pic->print)
                        printf("SUBLW %#04X\n", opc & 0x00FF);

                    if ((0xF0 & ((0x0F & (~pic->w)) + 1 + (opc & 0x000F))) != 0)
                        *status |= 0x02;
                    else
                        *status &= ~0x02;

                    temp = (~pic->w + 1) + (opc & 0x00FF);
                    pic->w = (unsigned char)(0x00FF & temp);

                    if ((0xFF00 & temp) != 0)
                        *status &= ~0x01;
                    else
                        *status |= 0x01;

                    if (pic->w == 0)
                        *status |= 0x04;
                    else
                        *status &= ~0x04;
                } break;
                case 0x0E00:
                case 0x0F00: {
                    // ADDLW   k  	Add literal and W            1     11111x kkkkkkkk
                    // C,DC,Z
                    unsigned char* status = &pic->ram[bank | (sfr_addr(pic->P16map.STATUS) & 0x007F)];
                    if (pic->print)
                        printf("ADDLW %#04X\n", opc & 0x00FF);

                    if ((0xF0 & ((0x0F & pic->w) + (opc & 0x000F))) != 0)
                        *status |= 0x02;
                    else
                        *status &= ~0x02;

                    temp = pic->w + (opc & 0x00FF);
                    pic->w = (unsigned char)(0x00FF & temp);

                    if ((0xFF00 & temp) != 0)
                        *status |= 0x01;
                    else
                        *status &= ~0x01;

                    if (pic->w == 0)
                        *status |= 0x04;
                    else
                        *status &= ~0x04;
                } break;
                default:
                    printf("unknown opcode 0x%04X at 0x%06X !\n", opc, pic->pc - 2);
                    break;
            }
            break;
        default:
            printf("unknown opcode 0x%04X at 0x%06X !\n", opc, pic->pc - 2);
            break;
    }

    if (pic->lram == (bank | (sfr_addr(pic->P16map.INDF) & 0x007F))) {
        pic->ram[afsr] = pic->ram[bank | (sfr_addr(pic->P16map.INDF) & 0x007F)];
        pic->lram = afsr;
    }

    /*faz espelhamento de memoria*/

    if (pic->processor != P16F84A) {
        temp = pic->ram[bank | (sfr_addr(pic->P16map.STATUS) & 0x007F)];
        pic->ram[(0x0000) | (sfr_addr(pic->P16map.STATUS) & 0x007F)] = temp;
        pic->ram[(0x0080) | (sfr_addr(pic->P16map.STATUS) & 0x007F)] = temp;
        pic->ram[(0x0100) | (sfr_addr(pic->P16map.STATUS) & 0x007F)] = temp;
        pic->ram[(0x0180) | (sfr_addr(pic->P16map.STATUS) & 0x007F)] = temp;

        temp = pic->ram[bank | (sfr_addr(pic->P16map.INTCON) & 0x007F)];
        pic->ram[(0x0000) | (sfr_addr(pic->P16map.INTCON) & 0x007F)] = temp;
        pic->ram[(0x0080) | (sfr_addr(pic->P16map.INTCON) & 0x007F)] = temp;
        pic->ram[(0x0100) | (sfr_addr(pic->P16map.INTCON) & 0x007F)] = temp;
        pic->ram[(0x0180) | (sfr_addr(pic->P16map.INTCON) & 0x007F)] = temp;

        temp = pic->ram[bank | (sfr_addr(pic->P16map.PCLATH) & 0x007F)];
        pic->ram[(0x0000) | (sfr_addr(pic->P16map.PCLATH) & 0x007F)] = temp;
        pic->ram[(0x0080) | (sfr_addr(pic->P16map.PCLATH) & 0x007F)] = temp;
        pic->ram[(0x0100) | (sfr_addr(pic->P16map.PCLATH) & 0x007F)] = temp;
        pic->ram[(0x0180) | (sfr_addr(pic->P16map.PCLATH) & 0x007F)] = temp;

        temp = pic->ram[bank | (sfr_addr(pic->P16map.PCL) & 0x007F)];
        pic->ram[(0x0000) | (sfr_addr(pic->P16map.PCL) & 0x007F)] = temp;
        pic->ram[(0x0080) | (sfr_addr(pic->P16map.PCL) & 0x007F)] = temp;
        pic->ram[(0x0100) | (sfr_addr(pic->P16map.PCL) & 0x007F)] = temp;
        pic->ram[(0x0180) | (sfr_addr(pic->P16map.PCL) & 0x007F)] = temp;

        temp = pic->ram[bank | (sfr_addr(pic->P16map.FSR) & 0x007F)];
        pic->ram[(0x0000) | (sfr_addr(pic->P16map.FSR) & 0x007F)] = temp;
        pic->ram[(0x0080) | (sfr_addr(pic->P16map.FSR) & 0x007F)] = temp;
        pic->ram[(0x0100) | (sfr_addr(pic->P16map.FSR) & 0x007F)] = temp;
        pic->ram[(0x0180) | (sfr_addr(pic->P16map.FSR) & 0x007F)] = temp;

        if ((bank | (sfr_addr(pic->P16map.PCL) & 0x007F)) == pic->rram) {
            temp = (pic->pc & 0x1F00) >> 8;
            pic->ram[0x0000 | (sfr_addr(pic->P16map.PCLATH) & 0x007F)] = temp;
            pic->ram[0x0080 | (sfr_addr(pic->P16map.PCLATH) & 0x007F)] = temp;
            pic->ram[0x0100 | (sfr_addr(pic->P16map.PCLATH) & 0x007F)] = temp;
            pic->ram[0x0180 | (sfr_addr(pic->P16map.PCLATH) & 0x007F)] = temp;
        }

        if (pic->port_mirror) {
            if ((bank == 0x000) || (bank == 0x100)) {
                temp = pic->ram[bank | (sfr_addr(pic->P16map.PORTA) & 0x007F)];
                pic->ram[(0x0000) | (sfr_addr(pic->P16map.PORTA) & 0x007F)] = temp;
                pic->ram[(0x0100) | (sfr_addr(pic->P16map.PORTA) & 0x007F)] = temp;
                temp = pic->ram[bank | (sfr_addr(pic->P16map.PORTB) & 0x007F)];
                pic->ram[(0x0000) | (sfr_addr(pic->P16map.PORTB) & 0x007F)] = temp;
                pic->ram[(0x0100) | (sfr_addr(pic->P16map.PORTB) & 0x007F)] = temp;
                temp = pic->ram[bank | (sfr_addr(pic->P16map.PORTC) & 0x007F)];
                pic->ram[(0x0000) | (sfr_addr(pic->P16map.PORTC) & 0x007F)] = temp;
                pic->ram[(0x0100) | (sfr_addr(pic->P16map.PORTC) & 0x007F)] = temp;
            } else {
                temp = pic->ram[bank | (sfr_addr(pic->P16map.TRISA) & 0x007F)];
                pic->ram[(0x0080) | (sfr_addr(pic->P16map.TRISA) & 0x007F)] = temp;
                pic->ram[(0x0180) | (sfr_addr(pic->P16map.TRISA) & 0x007F)] = temp;
                temp = pic->ram[bank | (sfr_addr(pic->P16map.TRISB) & 0x007F)];
                pic->ram[(0x0080) | (sfr_addr(pic->P16map.TRISB) & 0x007F)] = temp;
                pic->ram[(0x0180) | (sfr_addr(pic->P16map.TRISB) & 0x007F)] = temp;
                temp = pic->ram[bank | (sfr_addr(pic->P16map.TRISC) & 0x007F)];
                pic->ram[(0x0080) | (sfr_addr(pic->P16map.TRISC) & 0x007F)] = temp;
                pic->ram[(0x0180) | (sfr_addr(pic->P16map.TRISC) & 0x007F)] = temp;
            }
        }

        /*

          if(0x0070 != (bank|0x70))
          memcpy(&pic->ram[0x0070],&pic->ram[bank|0x70],16); if(0x00F0 !=
          (bank|0x70)) memcpy(&pic->ram[0x00F0],&pic->ram[bank|0x70],16); if(0x0170
          != (bank|0x70)) memcpy(&pic->ram[0x0170],&pic->ram[bank|0x70],16);
          if(0x01F0 != (bank|0x70))
          memcpy(&pic->ram[0x01F0],&pic->ram[bank|0x70],16);
          //printf("\n");
         */
        if ((pic->lram & 0x007F) >= 0x0070) {
            temp = pic->ram[pic->lram];
            pic->ram[0x0070 | (0x007F & pic->lram)] = temp;
            pic->ram[0x00F0 | (0x007F & pic->lram)] = temp;
            pic->ram[0x0170 | (0x007F & pic->lram)] = temp;
            pic->ram[0x01F0 | (0x007F & pic->lram)] = temp;
        }
    } else  // PIC16F84A
    {
        temp = pic->ram[bank | (sfr_addr(pic->P16map.STATUS) & 0x007F)];
        pic->ram[(0x0000) | (sfr_addr(pic->P16map.STATUS) & 0x007F)] = temp;
        pic->ram[(0x0080) | (sfr_addr(pic->P16map.STATUS) & 0x007F)] = temp;

        temp = pic->ram[bank | (sfr_addr(pic->P16map.INTCON) & 0x007F)];
        pic->ram[(0x0000) | (sfr_addr(pic->P16map.INTCON) & 0x007F)] = temp;
        pic->ram[(0x0080) | (sfr_addr(pic->P16map.INTCON) & 0x007F)] = temp;

        temp = pic->ram[bank | (sfr_addr(pic->P16map.PCLATH) & 0x007F)];
        pic->ram[(0x0000) | (sfr_addr(pic->P16map.PCLATH) & 0x007F)] = temp;
        pic->ram[(0x0080) | (sfr_addr(pic->P16map.PCLATH) & 0x007F)] = temp;

        temp = pic->ram[bank | (sfr_addr(pic->P16map.PCL) & 0x007F)];
        pic->ram[(0x0000) | (sfr_addr(pic->P16map.PCL) & 0x007F)] = temp;
        pic->ram[(0x0080) | (sfr_addr(pic->P16map.PCL) & 0x007F)] = temp;

        temp = pic->ram[bank | (sfr_addr(pic->P16map.FSR) & 0x007F)];
        pic->ram[(0x0000) | (sfr_addr(pic->P16map.FSR) & 0x007F)] = temp;
        pic->ram[(0x0080) | (sfr_addr(pic->P16map.FSR) & 0x007F)] = temp;

        if ((bank | (sfr_addr(pic->P16map.PCL) & 0x007F)) == pic->rram) {
            temp = (pic->pc & 0x1F00) >> 8;
            pic->ram[0x0000 | (sfr_addr(pic->P16map.PCLATH) & 0x007F)] = temp;
            pic->ram[0x0080 | (sfr_addr(pic->P16map.PCLATH) & 0x007F)] = temp;
        }

        /*

          if(0x0070 != (bank|0x70))
          memcpy(&pic->ram[0x0070],&pic->ram[bank|0x70],16); if(0x00F0 !=
          (bank|0x70)) memcpy(&pic->ram[0x00F0],&pic->ram[bank|0x70],16);
          //printf("\n");
         */
        if ((pic->lram & 0x007F) >= 0x0070) {
            temp = pic->ram[pic->lram];
            pic->ram[0x0070 | (0x007F & pic->lram)] = temp;
            pic->ram[0x00F0 | (0x007F & pic->lram)] = temp;
        }

    }  // final espelhamento

    // if((pic->ram[bank|(PCL & 0x007F)]) != (pc_ant&0x00FF))
    if ((bank | (sfr_addr(pic->P16map.PCL) & 0x007F)) == pic->lram) {
        pic->pc = ((pic->ram[bank | (sfr_addr(pic->P16map.PCLATH) & 0x007F)] & 0x1F) << 8) |
                  pic->ram[bank | (sfr_addr(pic->P16map.PCL) & 0x007F)];
    }

    if ((pic->rram != 0x8000) && (pic->print))
        printf("mem read  %#06X: %10s= %#06X\n", pic->rram, getFSRname_16(pic->rram), pic->ram[pic->rram]);
    if ((pic->lram != 0x8000) && (pic->print))
        printf("mem write %#06X: %10s= %#06X\n", pic->lram, getFSRname_16(pic->lram), pic->ram[pic->lram]);

    // latchs
    if ((pic->lram == sfr_addr(pic->P16map.PORTA)) || (pic->lram == (sfr_addr(pic->P16map.PORTA) + 0x100))) {
        pic->p16latch[0] = (*pic->P16map.PORTA);
    }

    if ((pic->lram == sfr_addr(pic->P16map.PORTB)) || (pic->lram == (sfr_addr(pic->P16map.PORTB) + 0x100))) {
        pic->p16latch[1] = (*pic->P16map.PORTB);
    }

    if (pic->P16map.PORTC) {
        if ((pic->lram == sfr_addr(pic->P16map.PORTC)) || (pic->lram == (sfr_addr(pic->P16map.PORTC) + 0x100))) {
            pic->p16latch[2] = (*pic->P16map.PORTC);
        }
    }

    if (pic->P16map.PORTD) {
        if ((pic->lram == sfr_addr(pic->P16map.PORTD)) || (pic->lram == (sfr_addr(pic->P16map.PORTD) + 0x100))) {
            pic->p16latch[3] = (*pic->P16map.PORTD);
        }
    }

    if (pic->P16map.PORTE) {
        if ((pic->lram == sfr_addr(pic->P16map.PORTE)) || (pic->lram == (sfr_addr(pic->P16map.PORTE) + 0x100))) {
            pic->p16latch[4] = (*pic->P16map.PORTE);
        }
    }
}
