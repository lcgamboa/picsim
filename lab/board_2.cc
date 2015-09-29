
#include"picsimlab1.h"

void
CPWindow1::board_2(void)
{
  int i;
  int j;
  int l,c,x,y;
  unsigned char pi;
  const picpin * pins;
  
  unsigned char L[4];
  

  
  draw1.Canvas.Init(scale,scale);
  

  //lcd blink timer
          if((lcd.flags & L_CON )&&(lcd.flags & L_CBL))
          {
            lcd.blinkc++;
            if(lcd.blinkc > 4)
            {
              lcd.blinkc=0;   
              lcd.update=1;
              lcd.blink^=1;
            }
          }
          else
           lcd.blink=0;

//lab2 draw 
  for(i=0;i<outputc;i++)
  {
    if(!output[i].r)
    {
       
      draw1.Canvas.SetFgColor (30, 0, 0);
      
      switch(output[i].id) 
      {
        case O_LCD: draw1.Canvas.SetColor (0, 90*picpwr+40, 0);break;

      }


      if(output[i].id != O_LCD)
        draw1.Canvas.Rectangle (1, output[i].x1, output[i].y1, output[i].x2-output[i].x1,output[i].y2-output[i].y1 );

//draw lcd text 
   
      if((output[i].id == O_LCD)&&(lcd.update))
      {
         lcd.update=0;
        draw1.Canvas.Rectangle (1, output[i].x1, output[i].y1, output[i].x2-output[i].x1,output[i].y2-output[i].y1 );
        
         for(l=0;l<2;l++)
         {
           for(c=0;c<16;c++)
           {
             for(x=0;x<5;x++)
             { 
               for(y=0;y<8;y++)
               {
                 int cs= c-lcd.shift;
                 if(cs < 0) cs= 40+(cs%40);
                 if(cs >= 40 )cs=cs%40;

                 if((lcd.ddram[cs+(40*l)][x]  & (0x01<<y))&& (lcd.flags & L_DON))
                 {  
                    draw1.Canvas.SetFgColor (0, 35 , 0);
                    draw1.Canvas.SetColor (0, 35 , 0);
                 }
                 else
                 {
                    draw1.Canvas.SetFgColor (0, 90*picpwr+35 , 0);
                    draw1.Canvas.SetColor (0, 90*picpwr+35 , 0);
                 }
                 //draw1.Canvas.Rectangle (1, output[i].x1+12+(x*4)+(c*22), output[i].y1+8+(y*4)+(l*38), 4,4 );
                 draw1.Canvas.Rectangle (1, output[i].x1+2+(x*4)+(c*23), output[i].y1+10+(y*4)+(l*35), 4,4 );
               }
             }
           }
         } 
//cursor  
         if((lcd.flags & L_DON)&&(lcd.flags & L_CON))
         {
           if(lcd.ddram_ad < 40)
           {
             l=0;
             c=(lcd.ddram_ad+lcd.shift);
           }
           else
           {
             l=1;
             c=lcd.ddram_ad-40+lcd.shift;  
           }
           
           if(c < 0) c= 40+(c%40);
           if(c >= 40 )c=c%40;      
           
         
           if((c >= 0)&& (c< 16)) //draw only visible columns
           {    
             draw1.Canvas.SetFgColor (0, 35 , 0);
             draw1.Canvas.SetColor (0, 35 , 0);
            
             if(lcd.blink)
               draw1.Canvas.Rectangle (1, output[i].x1+2+(c*23), output[i].y1+10 +(l*35), 20,32 );  
             else    
               draw1.Canvas.Rectangle (1, output[i].x1+2+(c*23), output[i].y1+38+(l*35), 20,4 );
           }
         }
      }
       
    }
    else
    {
      draw1.Canvas.SetFgColor (0, 0, 0);
      
 
      switch(output[i].id)
      {
        case O_RA1: draw1.Canvas.SetColor (lm[17], 0, 0);break;
        case O_RA2: draw1.Canvas.SetColor (lm[0], 0, 0);break;
        case O_RA6: draw1.Canvas.SetColor (lm[14], 0, 0);break;
        case O_RA7: draw1.Canvas.SetColor (lm[15], 0, 0);break;
      }

      if(output[i].id == O_LPWR)draw1.Canvas.SetColor (0,255*picpwr, 0);
      
      draw1.Canvas.Circle (1,output[i].x1, output[i].y1,output[i].r );
    };
   };    

   rtc_update(&rtc);

//end draw

  draw1.Canvas.End();
  draw1.Update ();
  
     for(pi=0;pi < pic.PINCOUNT;pi++)
     {
       lm[pi]=0;
     };

 pins = pic.pins;


 j=JUMP+1;
 if(picpwr)
   for(i=0;i<NSTEP;i++)
      {
          if(j >JUMP)
          {  
          //FIXME keyboard slow!!!! default value must be set to 0
 
          L[0]=pic_get_pin(&pic,18);
          L[1]=pic_get_pin(&pic,1);
          L[2]=pic_get_pin(&pic,15);
          L[3]=pic_get_pin(&pic,16);

          if(((L[0])&&(p_CL1 == 1))||((L[1])&&(p_CL1 == 2))||
           ((L[2])&&(p_CL1 == 3))||((L[3])&&(p_CL1 == 4)))
          {
             pic_set_pin(&pic,13,1); 
          }
          else
          {
             pic_set_pin(&pic,13,0);
          }

          if(((L[0])&&(p_CL2 == 1))||((L[1])&&(p_CL2 == 2))||
           ((L[2])&&(p_CL2 == 3))||((L[3])&&(p_CL2 == 4)))
          {
             pic_set_pin(&pic,12,1); 
          }
          else
          {
             pic_set_pin(&pic,12,0);
          }

          if(((L[0])&&(p_CL3 == 1))||((L[1])&&(p_CL3 == 2))||
           ((L[2])&&(p_CL3 == 3))||((L[3])&&(p_CL3 == 4)))
          {
             pic_set_pin(&pic,11,1); 
          }
          else
          {
             pic_set_pin(&pic,11,0);
          }
          } 
  
        pic_step(&pic,0);

          if(j >JUMP)
          {  
        for(pi=0;pi < pic.PINCOUNT;pi++)
        {
           lm[pi]+=pins[pi].value;
           //if((!pins[pi].dir)&&(pins[pi].value)) lm[pi]++;
        }
        
          j=0;
          } 
          j++;

//serial lcd display code
    if(( pins[9].value)&&(!clko))
    {
      d= (d<<1)|pins[8].value;
    };

    clko=pins[9].value;
 
    if((!pins[16].dir)&&(!pins[16].value))
    {
      if(!lcde)
      {

        if((!pins[8].dir)&&(!pins[8].value))
        {
          lcd_cmd(&lcd,d);
        }
        else if((!pins[8].dir)&&(pins[8].value))
        {
          lcd_data(&lcd,d);
        }
        lcde=1;
      }  
    }
    else
    {
      lcde=0;
    }


//i2c code
        if(pins[2].dir)
        {
          sda=1;
        }
        else
        {
          sda=pins[2].value;
        }
        
        if(pins[1].dir)
        {
          sck=1;
	  pic_set_pin(&pic,2,1);
        }
        else
        {
          sck=pins[1].value;
        }
	pic_set_pin(&pic,3, mi2c_io(&mi2c,sck,sda) | rtc_io(&rtc,sck,sda));
  };
   //fim STEP
   

     for(pi=0;pi < pic.PINCOUNT;pi++)
     { 
      lm[pi]= (int)(((225.0*lm[pi])/NSTEPJ)+30);
     }

};

