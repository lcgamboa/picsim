/* ########################################################################

   PICsim - PIC simulator

   ########################################################################

   Copyright (c) : 2008-2015  Luis Claudio Gambôa Lopes

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


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"picsim.h"

int
parse_hex(char *line,int bytes)
{
  char snum[200];
  int num;
    
  strncpy(snum,line,bytes);
  snum[bytes]='\0';
  sscanf(snum,"%X",&num);

  return num; 
};


unsigned char
checksum(char* str)
{
  unsigned int i;
  unsigned char acum=0;

  for(i=0; i < ((strlen(str)-1)/2);i++)
  {
    acum+=parse_hex(str+1+(i*2),2);
  }
  
  return acum;
}


int
read_ihx(_pic * pic,const char * fname, int lrom)
{
  FILE* fin;
  int  lc=0;
  unsigned int bc;
  char line[256];
  unsigned int nbytes,addr,type;  
  unsigned int addrx;
  unsigned short addrh=0;
  unsigned short addrl=0;
  char *mptr;

  fin=fopen(fname,"r");

  if(fin)
  {
    do
    {
      fgets(line,256,fin);
      lc++;
  
      /*for dos file*/ 
      if(line[strlen(line)-2]=='\r')
      {
        line[strlen(line)-2]='\n';
        line[strlen(line)-1]=0;
      } 

      if(checksum(line) == 0)
      {
        nbytes=parse_hex(line+1,2);
        addr=parse_hex(line+3,4);
        type=parse_hex(line+7,2);

	switch(type)
	{
	  case 0:
	    addrl=addr/2;

            if((((addrh<<16)|addrl)<<1) == 0x400E )
	    {
              //config
               mptr=(char*)pic->config;
               for(bc=0;bc < nbytes;bc++)
	       {
	         addrx=((addrh<<16)|addr)+bc-0x400E;
                 if((addrx/2) < pic->CONFIGSIZE)
	           mptr[addrx]=parse_hex(line+9+(bc*2),2);
               }
	    }
            else
	    {
              if((((addrh<<16)|addrl)<<1) >= 0x4200 )
              { 
                //EEPROM
                if(lrom == 1) 
                for(bc=0;bc < nbytes;bc+=2)
	        {
                  addrx= (((addrh<<16)|addr)+bc-0x4200)/2;
                  if(addrx < pic->EEPROMSIZE*2)
	            pic->eeprom[addrx]=parse_hex(line+9+(bc*2),2);
                }
              }
              else
              {
                if((((addrh<<16)|addrl)<<1) >= 0x4000 )
                {
                  //IDS
                  mptr=(char*)pic->id;
                  for(bc=0;bc < nbytes;bc++)
	          {
	            addrx=((addrh<<16)|addr)+bc-0x4000;
                    if((addrx/2) < pic->IDSIZE)
	              mptr[addrx]=parse_hex(line+9+(bc*2),2);
                  }
                } 
                else
                {
                  //prog mem
                  mptr=(char*)pic->prog;
                  for(bc=0;bc < nbytes;bc++)
	          {
	            addrx=((addrh<<16)|addr)+bc;
                    if((addrx/2) < pic->ROMSIZE)
	              mptr[addrx]=parse_hex(line+9+(bc*2),2);
                  }
                }
              }
	    }
	  break;
	  case 1:
            fclose(fin);  
	    return 1;
	  break;
	  case 4:
	    addrh=((parse_hex(line+9,2)<<8)|parse_hex(line+11,2));
	  break;
	}
      }
      else
      {
        printf("ERRO: Picsim->File bad checksum line %i!(%s)\n",lc,fname);
        fclose(fin);  
        return 0;
      }
     }
     while(!feof(fin));
     fclose(fin);  
  }
  else
  {
    printf("ERRO: Picsim->File not found!(%s)\n",fname);
    return 0;
  }
  return 1;
};


int
read_ihx_18(_pic * pic,const char * fname, int lrom)
{
  FILE* fin;
  int  lc=0;
  unsigned int bc;
  char line[256];
  unsigned int nbytes,addr,type;  
  unsigned int addrx;
  unsigned short addrh=0;
  //unsigned short addrl=0;
  char *mptr;

  fin=fopen(fname,"r");

  if(fin)
  {
    do
    {
      fgets(line,256,fin);
      lc++;
  
      /*for dos file*/ 
      if(line[strlen(line)-2]=='\r')
      {
        line[strlen(line)-2]='\n';
        line[strlen(line)-1]=0;
      } 

      if(checksum(line) == 0)
      {
        nbytes=parse_hex(line+1,2);
        addr=parse_hex(line+3,4);
        type=parse_hex(line+7,2);

	switch(type)
	{
	  case 0:
	    //addrl=addr/2;

            if(addrh == 0x0030 )
	    {
              //config
              mptr=(char*)pic->config;
              for(bc=0;bc < nbytes;bc++)
	      {
	        addrx=addr+bc;
                if((addrx/2) < pic->CONFIGSIZE)
	          mptr[addrx]=parse_hex(line+9+(bc*2),2);
              }
	    }
            else
	    {
              if(addrh == 0x00F0 )
              { 
                //EEPROM
                if(lrom == 1) 
                for(bc=0;bc < nbytes;bc++)
	        {
                  addrx= addr+bc;
                  if(addrx < pic->EEPROMSIZE)
	            pic->eeprom[addrx]= parse_hex(line+9+(bc*2),2);
                }
              }
              else
              {
                if(addrh == 0x0020 )
                {
                  //IDS
                  mptr=(char*)pic->id;
                  for(bc=0;bc < nbytes;bc++)
	          {
	            addrx=addr+bc;
                    if((addrx/2) < pic->IDSIZE)
	              mptr[addrx]=parse_hex(line+9+(bc*2),2);
                  }
                } 
                else
                {
                  //prog mem
                  mptr=(char*)pic->prog;
                  for(bc=0;bc < nbytes;bc++)
	          {
	            addrx=addr+bc;
                    if((addrx/2) < pic->ROMSIZE)
	             mptr[addrx]=parse_hex(line+9+(bc*2),2);
                  }
                }
              }
	    }
	  break;
	  case 1:
            fclose(fin);  
	    return 1;
	  break;
	  case 4:
	    addrh=((parse_hex(line+9,2)<<8)|parse_hex(line+11,2));
	  break;
	}
      }
      else
      {
        printf("ERRO: Picsim->File bad checksum line %i!(%s)\n",lc,fname);
        fclose(fin);  
        return 0;
      }
     }
     while(!feof(fin));
     fclose(fin); 
  }
  else
  {
    printf("ERRO: Picsim->File not found!(%s)\n",fname);
    return 0;
  }
  return 1;
};


int
write_ihx(_pic * pic,const char * fname)
{

  FILE * fout;
  unsigned char sum;
  unsigned char nb;
  unsigned int iaddr=0;
  int i;
  char values[100]; 
  char tmp[100]; 

  fout=fopen(fname,"w");

  if(fout)
  {
    fprintf(fout,":020000040000FA\n");
//program memory
    nb=0;
    sum=0;
    for(i=0;i<pic->ROMSIZE;i++)
    {
    
      if(nb==0)
      {
        iaddr=i*2;
        sprintf(values,"%02X%02X",pic->prog[i]&0x00FF ,(pic->prog[i]&0xFF00)>>8);
      }
      else
      {
        sprintf(tmp,"%s%02X%02X",values,pic->prog[i]&0x00FF,(pic->prog[i]&0xFF00)>>8);
        strcpy(values,tmp);
      }

      nb+=2;
      sum+=pic->prog[i]&0x00FF;
      sum+=(pic->prog[i]&0xFF00)>>8;
      if(nb==16)
      {
        sum+=nb;
        sum+=(iaddr&0x00FF);
        sum+=((iaddr&0xFF00)>>8);
      //printf("sum=%02X %02X %02X\n",sum,~sum,(~sum)+1);
        sum=(~sum)+1; 
        fprintf(fout,":%02X%04X00%s%02X\n",nb,iaddr,values,sum);
        nb=0;
        sum=0;
      }
    }
    if(nb)
    {
        sum+=nb;
        sum+=(iaddr&0x00FF);
        sum+=((iaddr&0xFF00)>>8);
        sum=(~sum)+1; 
        fprintf(fout,":%02X%04X00%s%02X\n",nb,iaddr,values,sum);
    }

//ids
    nb=0;
    sum=0;
    for(i=0;i<pic->IDSIZE;i++)
    {
    
      if(nb==0)
      {
        iaddr=0x4000+(i*2);
        sprintf(values,"%02X%02X",pic->id[i]&0x00FF ,(pic->id[i]&0xFF00)>>8);
      }
      else
      {
        sprintf(tmp,"%s%02X%02X",values,pic->id[i]&0x00FF,(pic->id[i]&0xFF00)>>8);
        strcpy(values,tmp);
      }

      nb+=2;
      sum+=pic->id[i]&0x00FF;
      sum+=(pic->id[i]&0xFF00)>>8;
      if(nb==16)
      {
        sum+=nb;
        sum+=(iaddr&0x00FF);
        sum+=((iaddr&0xFF00)>>8);
      //printf("sum=%02X %02X %02X\n",sum,~sum,(~sum)+1);
        sum=(~sum)+1; 
        fprintf(fout,":%02X%04X00%s%02X\n",nb,iaddr,values,sum);
        nb=0;
        sum=0;
      }
    }
    if(nb)
    {
        sum+=nb;
        sum+=(iaddr&0x00FF);
        sum+=((iaddr&0xFF00)>>8);
        sum=(~sum)+1; 
        fprintf(fout,":%02X%04X00%s%02X\n",nb,iaddr,values,sum);
    }

//config
    nb=0;
    sum=0;
    for(i=0;i<pic->CONFIGSIZE;i++)
    {
    
      if(nb==0)
      {
        iaddr=0x400E +(i*2);
        sprintf(values,"%02X%02X",pic->config[i]&0x00FF ,(pic->config[i]&0xFF00)>>8);
      }
      else
      {
        sprintf(tmp,"%s%02X%02X",values,pic->config[i]&0x00FF,(pic->config[i]&0xFF00)>>8);
        strcpy(values,tmp);
      }

      nb+=2;
      sum+=pic->config[i]&0x00FF;
      sum+=(pic->config[i]&0xFF00)>>8;
      if(nb==16)
      {
        sum+=nb;
        sum+=(iaddr&0x00FF);
        sum+=((iaddr&0xFF00)>>8);
      //printf("sum=%02X %02X %02X\n",sum,~sum,(~sum)+1);
        sum=(~sum)+1; 
        fprintf(fout,":%02X%04X00%s%02X\n",nb,iaddr,values,sum);
        nb=0;
        sum=0;
      }
    }
    if(nb)
    {
        sum+=nb;
        sum+=(iaddr&0x00FF);
        sum+=((iaddr&0xFF00)>>8);
        sum=(~sum)+1; 
        fprintf(fout,":%02X%04X00%s%02X\n",nb,iaddr,values,sum);
    }
//eeprom
    nb=0;
    sum=0;
    for(i=0;i<pic->EEPROMSIZE;i++)
    {
    
      if(nb==0)
      {
        iaddr=0x4200+2*i;
        sprintf(values,"%02X00",pic->eeprom[i]);
      }
      else
      {
        sprintf(tmp,"%s%02X00",values,pic->eeprom[i]);
        strcpy(values,tmp);
      }

      nb+=2;
      sum+=pic->eeprom[i];
      if(nb==16)
      {
        sum+=nb;
        sum+=(iaddr&0x00FF);
        sum+=((iaddr&0xFF00)>>8);
      //printf("sum=%02X %02X %02X\n",sum,~sum,(~sum)+1);
        sum=(~sum)+1; 
        fprintf(fout,":%02X%04X00%s%02X\n",nb,iaddr,values,sum);
        nb=0;
        sum=0;
      }
    }
    if(nb)
    {
        sum+=nb;
        sum+=(iaddr&0x00FF);
        sum+=((iaddr&0xFF00)>>8);
        sum=(~sum)+1; 
        fprintf(fout,":%02X%04X00%s%02X\n",nb,iaddr,values,sum);
    }

//end
    fprintf(fout,":00000001FF\n");
    fclose(fout);   
    return 1;
  }
  else
  {
    printf("ERRO: Picsim->File not found!(%s)\n",fname);
    return 0;
  }
  return 1;
}

int
write_ihx18(_pic * pic,const char * fname)
{

  FILE * fout;
  unsigned char sum;
  unsigned char nb;
  unsigned int iaddr=0;
  int i;
  char values[100]; 
  char tmp[100]; 

  fout=fopen(fname,"w");

  if(fout)
  {
//program memory  //TODO only address < 64K bytes  
    nb=0;
    sum=0;
    fprintf(fout,":020000040000FA\n");
    for(i=0;i<pic->ROMSIZE;i++)
    {
    
      if(nb==0)
      {
        iaddr=i*2;
        sprintf(values,"%02X%02X",pic->prog[i]&0x00FF ,(pic->prog[i]&0xFF00)>>8);
      }
      else
      {
        sprintf(tmp,"%s%02X%02X",values,pic->prog[i]&0x00FF,(pic->prog[i]&0xFF00)>>8);
        strcpy(values,tmp);
      }

      nb+=2;
      sum+=pic->prog[i]&0x00FF;
      sum+=(pic->prog[i]&0xFF00)>>8;
      if(nb==16)
      {
        sum+=nb;
        sum+=(iaddr&0x00FF);
        sum+=((iaddr&0xFF00)>>8);
      //printf("sum=%02X %02X %02X\n",sum,~sum,(~sum)+1);
        sum=(~sum)+1; 
        fprintf(fout,":%02X%04X00%s%02X\n",nb,iaddr,values,sum);
        nb=0;
        sum=0;
      }
    }
    if(nb)
    {
        sum+=nb;
        sum+=(iaddr&0x00FF);
        sum+=((iaddr&0xFF00)>>8);
        sum=(~sum)+1; 
        fprintf(fout,":%02X%04X00%s%02X\n",nb,iaddr,values,sum);
    }

//ids
    nb=0;
    sum=0;
    fprintf(fout,":020000040020DA\n");
    for(i=0;i<pic->IDSIZE;i++)
    {
    
      if(nb==0)
      {
        iaddr=(i*2);
        sprintf(values,"%02X%02X",pic->id[i]&0x00FF ,(pic->id[i]&0xFF00)>>8);
      }
      else
      {
        sprintf(tmp,"%s%02X%02X",values,pic->id[i]&0x00FF,(pic->id[i]&0xFF00)>>8);
        strcpy(values,tmp);
      }

      nb+=2;
      sum+=pic->id[i]&0x00FF;
      sum+=(pic->id[i]&0xFF00)>>8;
      if(nb==16)
      {
        sum+=nb;
        sum+=(iaddr&0x00FF);
        sum+=((iaddr&0xFF00)>>8);
      //printf("sum=%02X %02X %02X\n",sum,~sum,(~sum)+1);
        sum=(~sum)+1; 
        fprintf(fout,":%02X%04X00%s%02X\n",nb,iaddr,values,sum);
        nb=0;
        sum=0;
      }
    }
    if(nb)
    {
        sum+=nb;
        sum+=(iaddr&0x00FF);
        sum+=((iaddr&0xFF00)>>8);
        sum=(~sum)+1; 
        fprintf(fout,":%02X%04X00%s%02X\n",nb,iaddr,values,sum);
    }

//config
    nb=0;
    sum=0;
    fprintf(fout,":020000040030CA\n");
    for(i=0;i<pic->CONFIGSIZE;i++)
    {
    
      if(nb==0)
      {
        iaddr=(i*2);
        sprintf(values,"%02X%02X",pic->config[i]&0x00FF ,(pic->config[i]&0xFF00)>>8);
      }
      else
      {
        sprintf(tmp,"%s%02X%02X",values,pic->config[i]&0x00FF,(pic->config[i]&0xFF00)>>8);
        strcpy(values,tmp);
      }

      nb+=2;
      sum+=pic->config[i]&0x00FF;
      sum+=(pic->config[i]&0xFF00)>>8;
      if(nb==16)
      {
        sum+=nb;
        sum+=(iaddr&0x00FF);
        sum+=((iaddr&0xFF00)>>8);
      //printf("sum=%02X %02X %02X\n",sum,~sum,(~sum)+1);
        sum=(~sum)+1; 
        fprintf(fout,":%02X%04X00%s%02X\n",nb,iaddr,values,sum);
        nb=0;
        sum=0;
      }
    }
    if(nb)
    {
        sum+=nb;
        sum+=(iaddr&0x00FF);
        sum+=((iaddr&0xFF00)>>8);
        sum=(~sum)+1; 
        fprintf(fout,":%02X%04X00%s%02X\n",nb,iaddr,values,sum);
    }
//eeprom
    nb=0;
    sum=0;
    fprintf(fout,":0200000400F00A\n");
    for(i=0;i<pic->EEPROMSIZE;i++)
    {
    
      if(nb==0)
      {
        iaddr=i;
        sprintf(values,"%02X",pic->eeprom[i]);
      }
      else
      {
        sprintf(tmp,"%s%02X",values,pic->eeprom[i]);
        strcpy(values,tmp);
      }

      nb++;
      sum+=pic->eeprom[i];
      if(nb==16)
      {
        sum+=nb;
        sum+=(iaddr&0x00FF);
        sum+=((iaddr&0xFF00)>>8);
      //printf("sum=%02X %02X %02X\n",sum,~sum,(~sum)+1);
        sum=(~sum)+1; 
        fprintf(fout,":%02X%04X00%s%02X\n",nb,iaddr,values,sum);
        nb=0;
        sum=0;
      }
    }
    if(nb)
    {
        sum+=nb;
        sum+=(iaddr&0x00FF);
        sum+=((iaddr&0xFF00)>>8);
        sum=(~sum)+1; 
        fprintf(fout,":%02X%04X00%s%02X\n",nb,iaddr,values,sum);
    }

//end
    fprintf(fout,":00000001FF\n");
    fclose(fout);   
    return 1;
  }
  else
  {
    printf("ERRO: Picsim->File not found!(%s)\n",fname);
    return 0;
  }
  return 1;
}
