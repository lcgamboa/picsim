
#include"picsimlab1.h"

void
CPWindow1::board_3(void)
{
  int i;
  int j;
  int l,c,x,y;
  unsigned char pi;
  unsigned char pinv;
  const picpin * pins;
  
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

//lab3 draw
  for(i=0;i<outputc;i++)
  {
    if(!output[i].r)
    {
       
      draw1.Canvas.SetFgColor (30, 0, 0);
      
      switch(output[i].id) 
      {
        case O_A1: draw1.Canvas.SetColor (lm1[18], 0, 0);break;
        case O_B1: draw1.Canvas.SetColor (lm1[19], 0, 0);break;
        case O_C1: draw1.Canvas.SetColor (lm1[20], 0, 0);break;
        case O_D1: draw1.Canvas.SetColor (lm1[21], 0, 0);break;
        case O_E1: draw1.Canvas.SetColor (lm1[26], 0, 0);break;
        case O_F1: draw1.Canvas.SetColor (lm1[27], 0, 0);break;
        case O_G1: draw1.Canvas.SetColor (lm1[28], 0, 0);break;
        case O_P1: draw1.Canvas.SetColor (lm1[29], 0, 0);break;
          
        case O_A2: draw1.Canvas.SetColor (lm2[18], 0, 0);break;
        case O_B2: draw1.Canvas.SetColor (lm2[19], 0, 0);break;
        case O_C2: draw1.Canvas.SetColor (lm2[20], 0, 0);break;
        case O_D2: draw1.Canvas.SetColor (lm2[21], 0, 0);break;
        case O_E2: draw1.Canvas.SetColor (lm2[26], 0, 0);break;
        case O_F2: draw1.Canvas.SetColor (lm2[27], 0, 0);break;
        case O_G2: draw1.Canvas.SetColor (lm2[28], 0, 0);break;
        case O_P2: draw1.Canvas.SetColor (lm2[29], 0, 0);break;
      
        case O_A3: draw1.Canvas.SetColor (lm3[18], 0, 0);break;
        case O_B3: draw1.Canvas.SetColor (lm3[19], 0, 0);break;
        case O_C3: draw1.Canvas.SetColor (lm3[20], 0, 0);break;
        case O_D3: draw1.Canvas.SetColor (lm3[21], 0, 0);break;
        case O_E3: draw1.Canvas.SetColor (lm3[26], 0, 0);break;
        case O_F3: draw1.Canvas.SetColor (lm3[27], 0, 0);break;
        case O_G3: draw1.Canvas.SetColor (lm3[28], 0, 0);break;
        case O_P3: draw1.Canvas.SetColor (lm3[29], 0, 0);break;
      
        case O_A4: draw1.Canvas.SetColor (lm4[18], 0, 0);break;
        case O_B4: draw1.Canvas.SetColor (lm4[19], 0, 0);break;
        case O_C4: draw1.Canvas.SetColor (lm4[20], 0, 0);break;
        case O_D4: draw1.Canvas.SetColor (lm4[21], 0, 0);break;
        case O_E4: draw1.Canvas.SetColor (lm4[26], 0, 0);break;
        case O_F4: draw1.Canvas.SetColor (lm4[27], 0, 0);break;
        case O_G4: draw1.Canvas.SetColor (lm4[28], 0, 0);break;
        case O_P4: draw1.Canvas.SetColor (lm4[29], 0, 0);break;
     
        case O_LCD: draw1.Canvas.SetColor (0, 90*picpwr+40, 0);break;

        default : if((output[i].name[0]=='J')&&(output[i].name[1]=='P')) draw1.Canvas.SetColor (150, 150, 150);break;
      }

      if(output[i].id != O_LCD)
        draw1.Canvas.Rectangle (1, output[i].x1, output[i].y1, output[i].x2-output[i].x1,output[i].y2-output[i].y1 );
 
//draw lcd text 
   
      if((output[i].id == O_LCD)&&(lcd.update))
      {
         draw1.Canvas.Rectangle (1, output[i].x1, output[i].y1, output[i].x2-output[i].x1,output[i].y2-output[i].y1 );
         lcd.update=0;

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

       
      if((output[i].name[0]=='J')&&(output[i].name[1]=='P'))
      {
       if(!jmp[output[i].name[2]-0x31])
       {
         draw1.Canvas.SetColor (70, 70, 70);
         draw1.Canvas.Rectangle (1, output[i].x1, output[i].y1, (int)((output[i].x2-output[i].x1)*0.65),output[i].y2-output[i].y1 );
         draw1.Canvas.SetColor (220, 220, 0);
         draw1.Canvas.Circle (1,output[i].x1+(int)((output[i].x2-output[i].x1)*0.80), output[i].y1+((output[i].y2-output[i].y1)/2),3);
       }
       else
       {
         draw1.Canvas.SetColor (70, 70, 70);
         draw1.Canvas.Rectangle (1, output[i].x1+((int)((output[i].x2-output[i].x1)*0.35)), output[i].y1, (int)((output[i].x2-output[i].x1)*0.65),output[i].y2-output[i].y1 );
         draw1.Canvas.SetColor (220, 220, 0);
         draw1.Canvas.Circle (1,output[i].x1+(int)((output[i].x2-output[i].x1)*0.20), output[i].y1+((output[i].y2-output[i].y1)/2),3);
       };
      }       
       
    }
    else
    {
      draw1.Canvas.SetFgColor (0, 0, 0);
      
 
        switch(output[i].id)
        {
          case O_RB0: draw1.Canvas.SetColor (lm[32], 0, 0);break;
          case O_RB1: draw1.Canvas.SetColor (lm[33], 0, 0);break;
          case O_RB2: draw1.Canvas.SetColor (lm[34], 0, 0);break;
          case O_RB3: draw1.Canvas.SetColor (lm[35], 0, 0);break;
        }
      if(output[i].id == O_LPWR)draw1.Canvas.SetColor (0,255*picpwr, 0);
      
      draw1.Canvas.Circle (1,output[i].x1, output[i].y1,output[i].r );
    };    

  };
//end draw

  draw1.Canvas.End();
  draw1.Update ();
  
     for(pi=0;pi < pic.PINCOUNT;pi++)
     {
       lm[pi]=0;
       lm1[pi]=0;
       lm2[pi]=0;
       lm3[pi]=0;
       lm4[pi]=0;
     };
   
        
 pins = pic.pins;


 j=JUMP+1;
 if(picpwr)
   for(i=0;i<NSTEP;i++)
      {
 
          if(j >JUMP)
          {  
          pic_set_pin(&pic,33,p_BT1); 
          pic_set_pin(&pic,34,p_BT2); 
          pic_set_pin(&pic,35,p_BT3); 
          pic_set_pin(&pic,36,p_BT4);
          
          rpmc++;
          if(rpmc > rpmstp) 
          {
             rpmc=0;
             pic_set_pin(&pic,15, !pic_get_pin(&pic,15));
          }
          }
         
        pic_step(&pic,0);

          if(j >JUMP)
          {  
/*
        for(pi=0;pi < pic.PINCOUNT;pi++)
        {
           //if((!pins[pi].dir)&&(pins[pi].value)) lm[pi]++;
           lm[pi]+=pins[pi].value;
        }
*/       

//output 
          lm[32]+=pins[32].value;
          lm[33]+=pins[33].value;
          lm[34]+=pins[34].value;
          lm[35]+=pins[35].value;

          lm[6]+=pins[6].value;
          lm[15]+=pins[15].value;
          lm[16]+=pins[16].value;


//input
          if((pins[32].dir)&&(p_BT1))lm[32]++; 
          if((pins[33].dir)&&(p_BT2))lm[33]++; 
          if((pins[34].dir)&&(p_BT3))lm[34]++; 
          if((pins[35].dir)&&(p_BT4))lm[35]++; 

  
            for(pi=18;pi<30;pi++)
            {
              pinv=pins[pi].value;
              if((pinv)&&(pins[39].value)) lm1[pi]++;
              if((pinv)&&(pins[38].value)) lm2[pi]++;
              if((pinv)&&(pins[37].value)) lm3[pi]++;
              if((pinv)&&(pins[36].value)) lm4[pi]++;
            }
     
//potênciometro p2
//p2 rc circuit

   if(!pins[2].dir)
     {
        //decarga por RA1  
        vp2[1]=vp2[0]=5*pins[2].value;
     }

     vp2[1]=vp2[0];

     vp2[0]=vp2in*0.00021+vp2[1]*0.99979;
 
     if(pins[2].ptype < 3)
      pic_set_pin(&pic,3,vp2[0] > 1.25);
     else
      pic_set_apin(&pic,3,vp2[0]);
     


//lcd dipins[2].dirsplay code
    if((!pins[8].dir)&&(!pins[8].value))
    {
      if(!lcde)
      {
      d=0; 
      if(pins[29].value) d|= 0x80;
      if(pins[28].value) d|= 0x40;
      if(pins[27].value) d|= 0x20;
      if(pins[26].value) d|= 0x10;
      if(pins[21].value) d|= 0x08;
      if(pins[20].value) d|= 0x04;
      if(pins[19].value) d|= 0x02;
      if(pins[18].value) d|= 0x01;

      if((!pins[7].dir)&&(!pins[7].value))
      {
        lcd_cmd(&lcd,d);
      }
      else if((!pins[7].dir)&&(pins[7].value))
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
          j=0;
          } 
          j++;
     
//i2c code
        if(pins[22].dir)
        {
          sda=1;
        }
        else
        {
          sda=pins[22].value;
        }
        
        if(pins[17].dir)
        {
          sck=1;
	  pic_set_pin(&pic,18,1);
        }
        else
        {
          sck=pins[17].value;
        }
	pic_set_pin(&pic,23,mi2c_io(&mi2c,sck,sda));

 }
   //fim STEP
   

     if( ((100.0*lm[6])/NSTEPJ) > 40)
     {
       if(!sound_on)
       {
         buzz.Play(wxSOUND_ASYNC|wxSOUND_LOOP); 
         sound_on=1;
       }
     }
     else
     {
       buzz.Stop(); 
       sound_on=0;
     }

     //Ventilador
     gauge1.SetValue((100.0*lm[15])/NSTEPJ); 
     //Aquecedor
     gauge2.SetValue((100.0*lm[16])/NSTEPJ); 

     //sensor ventilador
     rpmstp=((float)NSTEPJ*NSTEPJ)/(144.0*(lm[15]+1));
   
     //tensão p2
     vp2in=((5.0*(scroll1.GetPosition()))/(scroll1.GetRange()-1));

     //temperatura 
     ref=((50.0*lm[16])/NSTEPJ)-((50.0*lm[15])/NSTEPJ); 

     if(ref < 0)
       ref=0; 
 
       temp[1]=temp[0];    
       temp[0]=((27.5+ref)*0.003)+temp[1]*(0.997);

     pic_set_apin(&pic,2,(10.0/255)*(temp[0]+15));
    
     //referencia
     pic_set_apin(&pic,5,2.5);

     for(pi=0;pi < pic.PINCOUNT;pi++)
     { 
      lm[pi]= (int)(((225.0*lm[pi])/NSTEPJ)+30);

      lm1[pi]= (int)(((600.0*lm1[pi])/NSTEPJ)+30);
      lm2[pi]= (int)(((600.0*lm2[pi])/NSTEPJ)+30);
      lm3[pi]= (int)(((600.0*lm3[pi])/NSTEPJ)+30);
      lm4[pi]= (int)(((600.0*lm4[pi])/NSTEPJ)+30);
      if(lm1[pi] > 255)lm1[pi]=255;
      if(lm2[pi] > 255)lm2[pi]=255;
      if(lm3[pi] > 255)lm3[pi]=255;
      if(lm4[pi] > 255)lm4[pi]=255;
     }

};

