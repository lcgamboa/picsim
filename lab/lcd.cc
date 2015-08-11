

#include"lcd.h"
#include<stdio.h>



void lcd_cmd(lcd_t * lcd, char cmd)
{
  int i,j;



  if(!( lcd->flags & L_DL))
  {
     if(lcd->bc)
     {
       lcd->bc=0; 
       cmd= lcd->buff | (((unsigned char)cmd) >>4);
     }
     else
     {
       lcd->bc=1;
       lcd->buff=cmd&0xF0;
       return;
     }
  }

//  printf("LCD cmd=%#04X\n",(unsigned char)cmd);
  
  
  if((cmd & 0x80) == 0x80 )
  {
//Set DDRAM address
    
    i=cmd & 0x7F;
 
    if(i < 40)
    {
       lcd->cursor=i;
    }
    else
    {
       lcd->cursor=i-24;
    }
     
    if(lcd->cursor >= DDRMAX)lcd->cursor =0;
    lcd->cgram_ad=0xFF;
   
    return;
  }
 
  if((cmd & 0x40) == 0x40 )
  {
//Set CGRAM address
    
    lcd->cgram_ad=cmd & 0x3F;

    return;
  }
 
  if((cmd & 0x20) == 0x20 )
  {
//Function set

//Sets interface data length
    if((cmd & 0x10)==0x10) 
    {
      lcd->flags|=L_DL;
    }
    else
    {
      lcd->flags&=~L_DL;
    }
    
//Sets number of display line
    if((cmd & 0x08)==0x08) 
    {
      lcd->flags|=L_NLI;
    }
    else
    {
      lcd->flags&=~L_NLI;
    }

//Sets character font
    if((cmd & 0x04)==0x04) 
    {
      lcd->flags|=L_FNT;
    }
    else
    {
      lcd->flags&=~L_FNT;
    }

    return;
  }
 
  if((cmd & 0x10) == 0x10 )
  {
//Cursor/display shift
  
//Sets shift direction  
    if((cmd & 0x08)==0x08) 
    {
      lcd->flags|=L_LR;
    }
    else
    {
      lcd->flags&=~L_LR;
    }
  
//Sets cursor-move or display-shift  
    if((cmd & 0x04)==0x04) 
    {
      lcd->flags|=L_CD;
    }
    else
    {
      lcd->flags&=~L_CD;
    }


    return;
  }
 
  if((cmd & 0x08) == 0x08 )
  {
//Display On/Off control

//Sets On/Off of all display
    if((cmd & 0x04)==0x04) 
    {
      lcd->flags|=L_DON;
    }
    else
    {
      lcd->flags&=~L_DON;
    }
    
//Sets cursor On/Off 
    if((cmd & 0x02)==0x02) 
    {
      lcd->flags|=L_CON;
    }
    else
    {
      lcd->flags&=~L_CON;
    }

//Set blink of cursor position character    
    if((cmd & 0x01)==0x01) 
    {
      lcd->flags|=L_CBL;
    }
    else
    {
      lcd->flags&=~L_CBL;
    }


    return;
  }
 
  if((cmd & 0x04) == 0x04 )
  {
//Entry mode set

//Sets cursor move direction    
    if((cmd & 0x02)==0x02) 
    {
      lcd->flags|=L_DID;
    }
    else
    {
      lcd->flags&=~L_DID;
    }
   
//specifies to shift the display  
    if((cmd & 0x01)==0x01) 
    {
      lcd->flags|=L_DSH;
    }
    else
    {
      lcd->flags&=~L_DSH;
    }

    return;
  }
 
  if((cmd & 0x02) == 0x02 )
  {
//Cursor home
    lcd->cursor=0;
    return;
  }
 
  if((cmd & 0x01) == 0x01 )
  {
//Clear display
    for(i=0;i<DDRMAX;i++)
    {
      for(j=0;j<5;j++)
      {
        lcd->ddram[i][j]=0;
      }
    }
    lcd->cursor=0;
    lcd->update=1; 
    return;
  }
 

};


void lcd_data(lcd_t * lcd, char data)
{
  int j;
  int fp;
  
   if( !(lcd->flags & L_DON))
   {
      lcd_cmd(lcd,data);
      return;
   }


  if(!( lcd->flags & L_DL))
  {
     if(lcd->bc)
     {
       lcd->bc=0; 
       data= lcd->buff | (((unsigned char)data) >>4);
     }
     else
     {
       lcd->bc=1;
       lcd->buff=data&0xF0;
       return;
     }
  }
      

  /*
  if(data < 0x20)
  {
    printf("LCD dat=ERROR!\n");
    return;
  }
*/
  fp=((unsigned char)data)-0x20;

  if(fp > 96)
  {
 //   printf("LCD dat=ERROR!\n");
    return;
  }

//  printf("LCD dat=%#04X  (%c)\n",(unsigned char)data,data);

  if(lcd->cgram_ad == 0xFF)
  {
    for(j=0;j<5;j++)
    {
      if(fp >= 0)
      {
        if(fp < 128)
          lcd->ddram[lcd->cursor][j]=LCDfont[fp][j];
        else
          lcd->ddram[lcd->cursor][j]=0xFF;
      }
      else
      {
        lcd->ddram[lcd->cursor][j]=lcd->cgram[data&0x07][j];
      }
    }
    lcd->cursor++;
    lcd->update=1; 
    if(lcd->cursor >= DDRMAX)lcd->cursor=0;
  }
  else
  {
    for(j=0;j<5;j++)
    {
      if((data & (0x01<<(4-j))) > 0) 
      {
        lcd->cgram[lcd->cgram_ad >>3][j]|=  (0x01<<(lcd->cgram_ad &0x07));
      }
      else
      { 
        lcd->cgram[lcd->cgram_ad >>3][j]&= ~(0x01<<(lcd->cgram_ad &0x07));
      };  
    }

    lcd->cgram_ad++;	
    if(lcd->cgram_ad >=64)lcd->cgram_ad=0;	
  }  

};



void lcd_rst(lcd_t * lcd)
{
int i,j;

//    printf("LCD rst--------------------------\n");

    for(i=0;i<DDRMAX;i++)
    {
      for(j=0;j<5;j++)
      {
        lcd->ddram[i][j]=0;
      }
    }
    for(i=0;i<8;i++)
    {
      for(j=0;j<5;j++)
      {
        lcd->cgram[i][j]=0;
      }
    }
    lcd->cursor=0;
    lcd->cgram_ad=0xFF;
    lcd->update=1; 
    lcd->bc=0;
    
    return;
};

void lcd_on(lcd_t * lcd,int onoff)
{
  if(onoff == 1 )
  {
    lcd->flags=0;
  };
  lcd_rst(lcd);
};



