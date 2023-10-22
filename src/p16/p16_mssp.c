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

#include "../../include/periferic16.h"
#include "../../include/picsim.h"
#include <stdio.h>

int pic_wr_pin16(_pic *pic, unsigned char pin, unsigned char value);

int pic_dir_pin16(_pic *pic, unsigned char pin, unsigned char dir);

void p16_mssp_rst(_pic *pic)
{
  pic->ssp_sck = 0;
  pic->ssp_scka = 0;
  pic->sspsr = 0;
  pic->ssp_bit = 0;
  pic->sspsr = 0;
  pic->ssp_ck = 0;
}

void p16_mssp(_pic *pic)
{

  // MSSP
  if (((*pic->P16map.SSPCON) & 0x20) == 0x20) // SSPEN
  {

    switch ((*pic->P16map.SSPCON) & 0x0F)
    {
    case 0x00: // SPI Master mode, clock = FOSC/4
    case 0x01: // SPI Master mode, clock = FOSC/16
    case 0x02: // SPI Master mode, clock = FOSC/64
    case 0x03: // SPI Master mode, clock = TMR2 output/2
      // TODO add CLK POL and FREQ support
      if (pic->lram == sfr_addr(pic->P16map.SSPBUF))
      {
        pic->ssp_bit = 8;
        pic->ssp_sck = 1;
        pic_wr_pin16(pic, pic->sck, 0);
        pic_dir_pin16(pic, pic->sdi, PD_IN);
      }
      if (pic->rram == sfr_addr(pic->P16map.SSPBUF))
      {
        (*pic->P16map.SSPSTAT) &= ~0x01; // BF
      }

      if (pic->ssp_bit)
      {
        switch (pic->ssp_sck)
        {
        case 0: // to low
          pic_wr_pin16(pic, pic->sck, 0);
          pic->ssp_bit--;
          break;
        case 1: // midle low
          pic_wr_pin16(
              pic, pic->sdo,
              (((*pic->P16map.SSPBUF) & (1 << ((pic->ssp_bit - 1)))) > 0));
          break;
        case 2: // to high
          pic->sspsr |= (pic->pins[pic->sdi - 1].value) << (pic->ssp_bit - 1);
          pic_wr_pin16(pic, pic->sck, 1);
          break;
        case 3: // midle high
          pic->ssp_sck = -1;
          break;
        }
        pic->ssp_sck++;

        if (!pic->ssp_bit)
        {
          (*pic->P16map.SSPSTAT) |= 0x01; // BF
          (*pic->P16map.PIR1) |= 0x08;    // PSPIF
          (*pic->P16map.SSPBUF) = pic->sspsr;
          pic->sspsr = 0;
        }
      }

      break;
      // case 0x04://SPI Slave mode, clock = SCK pin. SS pin control enabled.
    case 0x05: // SPI Slave mode, clock = SCK pin. SS pin control disabled.
      pic_dir_pin16(pic, pic->sdi, PD_IN);

      if (pic->rram == sfr_addr(pic->P16map.SSPBUF))
      {
        (*pic->P16map.SSPSTAT) &= ~0x01; // BF
      }

      pic->ssp_scka = pic->ssp_sck;
      pic->ssp_sck = pic->pins[pic->sck - 1].value;

      if ((pic->ssp_scka == 0) &&
          (pic->ssp_sck ==
           1)) // CKP =0 CKE =0     //coloca saida na borda de subida
      {
        pic_wr_pin16(pic, pic->sdo,
                     (((*pic->P16map.SSPBUF) & (1 << (7 - pic->ssp_bit))) > 0));
      }

      if ((pic->ssp_scka == 1) &&
          (pic->ssp_sck == 0)) // CKP =0 CKE =0    //le na borda de decida
      {
        pic->sspsr |= (pic->pins[pic->sdi - 1].value) << (7 - pic->ssp_bit);

        // printf("SSP bit =%i    REC=%#02X   SEND=%#02X
        // \n",pic->ssp_bit,pic->sspsr, pic->ram[SSPBUF]);

        pic->ssp_bit++;
      }

      if (pic->ssp_bit >= 8)
      {
        //	   printf("MSSP TX=%#02X
        // RX=%#02X\n",pic->ram[SSPBUF],pic->sspsr);
        (*pic->P16map.SSPBUF) = pic->sspsr;
        pic->sspsr = 0;
        (*pic->P16map.SSPSTAT) |= 0x01; // BF

        // PSPIF
        (*pic->P16map.PIR1) |= 0x08; // PSPIF
        pic->ssp_bit = 0;
      }
      break;
      // case 0x06://I2C Slave mode, 7-bit address
      // case 0x07://I2C Slave mode, 10-bit address
    case 0x08: // I2C Master mode, clock = FOSC /(4 * (SSPADD + 1))
      pic->ssp_sck++;

      if (pic->ssp_sck == 1)
      {

        if (((*pic->P16map.SSPCON2) & 0x01)) // start
        {
          pic_dir_pin16(pic, pic->sck, PD_OUT);
          pic_dir_pin16(pic, pic->sdi, PD_OUT);
          pic_wr_pin16(pic, pic->sdi, 1);
          pic_wr_pin16(pic, pic->sck, 1);
          pic->ssp_ck |= 0x01;
          // printf("I2C_start 1\n");
        }
        else if (((*pic->P16map.SSPCON2) & 0x02)) // restart
        {
          pic_dir_pin16(pic, pic->sdi, PD_OUT);
          pic_wr_pin16(pic, pic->sdi, 1);
          pic_wr_pin16(pic, pic->sck, 1);
          pic->ssp_ck |= 0x02;
          // printf("restar1\n");
        }
        else if (((*pic->P16map.SSPCON2) & 0x04)) // stop
        {
          pic_dir_pin16(pic, pic->sdi, PD_OUT);
          pic_wr_pin16(pic, pic->sdi, 0);
          pic_wr_pin16(pic, pic->sck, 1);
          pic->ssp_ck |= 0x04;
          // printf("stop1\n");
        }
      }

      if (pic->ssp_sck == ((((*pic->P16map.SSPADD) + 1) / 2)))
      {

        if (((*pic->P16map.SSPCON2) & 0x01) && (pic->ssp_ck & 0x01)) // start
        {
          (*pic->P16map.SSPCON2) &= ~0x01;
          pic_dir_pin16(pic, pic->sck, PD_OUT);
          pic_wr_pin16(pic, pic->sdi, 0);
          pic_wr_pin16(pic, pic->sck, 1);
          (*pic->P16map.PIR1) |= 0x08; // SSPIF
          pic->ssp_ck &= ~0x01;
          // printf("start 2\n");
        }
        else if (((*pic->P16map.SSPCON2) & 0x02) &&
                 (pic->ssp_ck & 0x02)) // restart
        {
          (*pic->P16map.SSPCON2) &= ~0x02;

          pic_wr_pin16(pic, pic->sdi, 0);
          pic_wr_pin16(pic, pic->sck, 1);
          (*pic->P16map.PIR1) |= 0x08; // SSPIF
          pic->ssp_ck &= ~0x02;
          // printf("restart 2\n");
        }
        else if (((*pic->P16map.SSPCON2) & 0x04) &&
                 (pic->ssp_ck & 0x04)) // stop
        {
          (*pic->P16map.SSPCON2) &= ~0x04;
          pic->ssp_bit = 11;
          pic_wr_pin16(pic, pic->sdi, 1);
          pic_wr_pin16(pic, pic->sck, 1);
          (*pic->P16map.PIR1) |= 0x08; // SSPIF
          pic->ssp_ck &= ~0x04;
          // printf("stop 2\n");
        }
      }

      if (pic->lram == sfr_addr(pic->P16map.SSPBUF))
      {
        (*pic->P16map.SSPSTAT) |= 0x04; // R/W
        // printf("SPPBUF write (%#02X)!!!!\n",pic->ram[SSPBUF]);
        pic->ssp_bit = 0;
        pic_dir_pin16(pic, pic->sdi, PD_OUT);
        (*pic->P16map.SSPSTAT) |= 0x01; // BF
      }

      if (!((*pic->P16map.SSPCON2) & 0x08))
        pic->ssp_scka = 0;

      if (((*pic->P16map.SSPCON2) & 0x08) && (pic->ssp_scka == 0))
      {
        pic->ssp_bit = 0;

        // printf("read\n");
        (*pic->P16map.SSPBUF) = 0;
        pic_dir_pin16(pic, pic->sdi, PD_IN);
        (*pic->P16map.SSPSTAT) &= ~0x01; // BF

        pic->ssp_scka = 1;
      }

      if (pic->ssp_sck > (*pic->P16map.SSPADD))
      {
        pic->ssp_sck = 0;

        // write
        if ((((*pic->P16map.SSPSTAT) & 0x04)) && (pic->ssp_bit < 10))
        {

          if (pic->pins[pic->sck - 1].value == 0)
          {
            if(pic->ssp_bit < 8)
            {
              pic_wr_pin16(
                pic, pic->sdi,
                ((*pic->P16map.SSPBUF) & (0x01 << (7 - pic->ssp_bit))) > 0);
            }
          
            pic->ssp_bit++;
          }

          pic_wr_pin16(pic, pic->sck, !pic->pins[pic->sck - 1].value);

          if ((pic->pins[pic->sck - 1].value == 0) && (pic->ssp_bit == 8))
          {
              pic_dir_pin16(pic, pic->sdi, PD_IN);
          }

          if ((pic->pins[pic->sck - 1].value == 1) && (pic->ssp_bit == 9))
          {
            if (pic->pins[pic->sdi - 1].value)
              (*pic->P16map.SSPCON2) |= 0x40; // ACKSTAT
            else
              (*pic->P16map.SSPCON2) &= ~0x40; // ACKSTAT
          }

          if ((pic->pins[pic->sck - 1].value == 0) && (pic->ssp_bit == 9))
          {
            (*pic->P16map.SSPSTAT) &= ~0x04; // R/W
            (*pic->P16map.PIR1) |= 0x08;     // SSPIF
            (*pic->P16map.SSPSTAT) &= ~0x01; // BF
            pic->ssp_bit++; //to finish
          }

          //    printf("wbit(%i)  sck=%i  sda=%i
          //    \n",pic->ssp_bit,pic->pins[pic->sck-1].value,pic->pins[pic->sdi-1].value);
        }

        // read
        if ((((*pic->P16map.SSPCON2) & 0x08) ||
             ((*pic->P16map.SSPCON2) & 0x10)) &&
            (pic->ssp_bit <= 11))
        {

          if ((pic->pins[pic->sck - 1].value == 1) && (pic->ssp_bit <= 8))
          {
            pic->ssp_bit++;
            (*pic->P16map.SSPBUF) |=
                (pic->pins[pic->sdi - 1].value << (8 - pic->ssp_bit));
            if (pic->ssp_bit == 8)
            {
              (*pic->P16map.SSPCON2) &= ~0x10; // ACKDT
              (*pic->P16map.PIR1) |= 0x08;     // SSPIF
              pic->ssp_bit++;

              (*pic->P16map.SSPCON2) &= ~0x08;
              (*pic->P16map.SSPSTAT) |= 0x01; // BF
              // printf("recebido1 %02X\n",pic->ram[SSPBUF]);
            }
          }

          if ((pic->ssp_bit <= 8) ||
              ((pic->ssp_bit == 9) && (pic->pins[pic->sck - 1].value == 1)) ||
              (pic->ssp_bit > 9))
          {
            pic_wr_pin16(pic, pic->sck, !pic->pins[pic->sck - 1].value);
          }

          if ((pic->pins[pic->sck - 1].value == 0) && (pic->ssp_bit > 9))
          {
            (*pic->P16map.PIR1) |= 0x08; // SSPIF
            pic->ssp_bit++;

            (*pic->P16map.SSPCON2) &= ~0x10; // ACKDT
          }

          if (((*pic->P16map.SSPCON2) & 0x10) &&
              (pic->pins[pic->sck - 1].value == 0) && (pic->ssp_bit > 8))
          {
            pic_dir_pin16(pic, pic->sdi, PD_OUT);
            pic_wr_pin16(pic, pic->sdi, ((*pic->P16map.SSPCON2) & 0x20) > 0);
            pic->ssp_bit++;
          }

          //  printf("rbit(%i)  sck=%i  sda=%i
          //  sdadir=%i\n",pic->ssp_bit,pic->pins[pic->sck-1].value,pic->pins[pic->sdi-1].value,pic->pins[pic->sdi-1].dir);

          if (pic->ssp_bit == 11)
          {
            pic_dir_pin16(pic, pic->sdi, PD_IN);
          }
        }
      }
      break;
      // case 0x09://Reserved
      // case 0x0A://Reserved
      // case 0x0B://I2C Firmware Controlled Master mode (Slave Idle)
      // case 0x0C://Reserved
      // case 0x0D://Reserved
      // case 0x0E://I2C Slave mode, 7-bit address with Start and Stop bit
      // interrupts enabled case 0x0F://I2C Slave mode, 10-bit address with
      // Start and Stop bit interrupts enabled
    default: // Unknown
      if (pic->ssp_sck == 0)
      {
        printf(" %#02X SPI mode not implemented!\n",
               ((*pic->P16map.SSPCON) & 0x0F));
      }
      pic->ssp_sck++;
      break;
    }
  }
  else
  {
    pic->ssp_sck = 0;
    pic->ssp_scka = 0;
    pic->ssp_bit = 0;
  }
}
