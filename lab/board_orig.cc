
void
CPWindow1::board_5(void)
{
  int i;
  int l,c,x,y;
  unsigned char pi;
  unsigned char pinv;
  clock_t cstart, cend;
  double cpu_time_used;
  const picpin * pins;
  
  unsigned char L[4];
  

   cstart = clock();
  //code here:)
  //mprint(wxT("timer1_EvOnTime\n"));
  
  draw1.Canvas.Init(scale,scale);
  


//lab1 draw 
switch(lab)
{
case 1:
  for(i=0;i<outputc;i++)
  {
    if(!output[i].r)
    {
      draw1.Canvas.SetFgColor (30, 0, 0);
      
      if(jmp[0])
      {
          switch(output[i].id)
          {         
            case O_A1: draw1.Canvas.SetBgColor (lm1[7], 0, 0);break;
            case O_B1: draw1.Canvas.SetBgColor (lm1[8], 0, 0);break;
            case O_C1: draw1.Canvas.SetBgColor (lm1[10], 0, 0);break;
            case O_D1: draw1.Canvas.SetBgColor (lm1[11], 0, 0);break;
            case O_E1: draw1.Canvas.SetBgColor (lm1[12], 0, 0);break;
            case O_F1: draw1.Canvas.SetBgColor (lm1[6], 0, 0);break;
            case O_G1: draw1.Canvas.SetBgColor (lm1[5], 0, 0);break;
            case O_P1: draw1.Canvas.SetBgColor (lm1[9], 0, 0);break;
            case O_A2: draw1.Canvas.SetBgColor (lm2[7], 0, 0);break;
            case O_B2: draw1.Canvas.SetBgColor (lm2[8], 0, 0);break;
            case O_C2: draw1.Canvas.SetBgColor (lm2[10], 0, 0);break;
            case O_D2: draw1.Canvas.SetBgColor (lm2[11], 0, 0);break;
            case O_E2: draw1.Canvas.SetBgColor (lm2[12], 0, 0);break;
            case O_F2: draw1.Canvas.SetBgColor (lm2[6], 0, 0);break;
            case O_G2: draw1.Canvas.SetBgColor (lm2[5], 0, 0);break;
            case O_P2: draw1.Canvas.SetBgColor (lm2[9], 0, 0);break;
          }
      }
      else
      {
        draw1.Canvas.SetBgColor (30, 0, 0);
      } 

      if(output[i].id == O_JP1) draw1.Canvas.SetBgColor (150, 150, 150);

      draw1.Canvas.Rectangle (1, output[i].x1, output[i].y1, output[i].x2-output[i].x1,output[i].y2-output[i].y1 );

       
      if(output[i].id == O_JP1)
      {
       if(!jmp[0])
       {
         draw1.Canvas.SetBgColor (70, 70, 70);
         draw1.Canvas.Rectangle (1, output[i].x1, output[i].y1, (int)((output[i].x2-output[i].x1)*0.65),output[i].y2-output[i].y1 );
         draw1.Canvas.SetBgColor (220, 220, 0);
         draw1.Canvas.Circle (1,output[i].x1+(int)((output[i].x2-output[i].x1)*0.80), output[i].y1+((output[i].y2-output[i].y1)/2),3);
       }
       else
       {
         draw1.Canvas.SetBgColor (70, 70, 70);
         draw1.Canvas.Rectangle (1, output[i].x1+((int)((output[i].x2-output[i].x1)*0.35)), output[i].y1, (int)((output[i].x2-output[i].x1)*0.65),output[i].y2-output[i].y1 );
         draw1.Canvas.SetBgColor (220, 220, 0);
         draw1.Canvas.Circle (1,output[i].x1+(int)((output[i].x2-output[i].x1)*0.20), output[i].y1+((output[i].y2-output[i].y1)/2),3);
       };
      }       
 
    }
    else
    {
      draw1.Canvas.SetFgColor (0, 0, 0);
      
 
      if(!jmp[0])
      {
        switch(output[i].id)
        {
          case O_RB0: draw1.Canvas.SetBgColor (lm[5], 0, 0);break;
          case O_RB1: draw1.Canvas.SetBgColor (lm[6], 0, 0);break;
          case O_RB2: draw1.Canvas.SetBgColor (lm[7], 0, 0);break;
          case O_RB3: draw1.Canvas.SetBgColor (lm[8], 0, 0);break;
          case O_RB4: draw1.Canvas.SetBgColor (lm[9], 0, 0);break;
          case O_RB5: draw1.Canvas.SetBgColor (lm[10], 0, 0);break;
          case O_RB6: draw1.Canvas.SetBgColor (lm[11], 0, 0);break;
          case O_RB7: draw1.Canvas.SetBgColor (lm[12], 0, 0);break;
        }
      }
      else
      {
         if((output[i].name[0]=='R')&&(output[i].name[1]=='B'))
            draw1.Canvas.SetBgColor (30, 0, 0);
      }

      switch(output[i].id)
      {
        case O_RA0: draw1.Canvas.SetBgColor (0, lm[16], 0);break;
        case O_RA1: draw1.Canvas.SetBgColor (0, lm[17], 0);break;
        case O_RA2: draw1.Canvas.SetBgColor (0, lm[0], 0);break;
        case O_RA3: draw1.Canvas.SetBgColor (0, lm[1], 0);break;
        case O_RA0L: draw1.Canvas.SetBgColor (lm[16],lm[16], 0);break;
      }
      
      draw1.Canvas.Circle (1,output[i].x1, output[i].y1,output[i].r );
    };    

  };
break;

case 2:
 
  for(i=0;i<outputc;i++)
  {
    if(!output[i].r)
    {
       
      draw1.Canvas.SetFgColor (30, 0, 0);
      
      switch(output[i].id) 
      {
        case O_LCD: draw1.Canvas.SetBgColor (0, 90*picpwr+40, 0);break;

        //default : if((output[i].name[0]=='J')&&(output[i].name[1]=='P')) draw1.Canvas.SetBgColor (150, 150, 150);break;
      }

      //if(output[i].id == O_JP1) draw1.Canvas.SetBgColor (150, 150, 150);

      if(output[i].id != O_LCD)
        draw1.Canvas.Rectangle (1, output[i].x1, output[i].y1, output[i].x2-output[i].x1,output[i].y2-output[i].y1 );

/*
      if(output[i].id == O_JP2)
      {
       if(!jmp[1])
       {
         draw1.Canvas.SetBgColor (70, 70, 70);
         draw1.Canvas.Rectangle (1, output[i].x1, output[i].y1, (int)((output[i].x2-output[i].x1)*0.65),output[i].y2-output[i].y1 );
         draw1.Canvas.SetBgColor (220, 220, 0);
         draw1.Canvas.Circle (1,output[i].x1+(int)((output[i].x2-output[i].x1)*0.80), output[i].y1+((output[i].y2-output[i].y1)/2),3);
       }
       else
       {
         draw1.Canvas.SetBgColor (70, 70, 70);
         draw1.Canvas.Rectangle (1, output[i].x1+((int)((output[i].x2-output[i].x1)*0.35)), output[i].y1, (int)((output[i].x2-output[i].x1)*0.65),output[i].y2-output[i].y1 );
         draw1.Canvas.SetBgColor (220, 220, 0);
         draw1.Canvas.Circle (1,output[i].x1+(int)((output[i].x2-output[i].x1)*0.20), output[i].y1+((output[i].y2-output[i].y1)/2),3);
       };
      }       
*/
 
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
                 if(lcd.ddram[c+(40*l)][x]  & (0x01<<y))
                 {  
                    draw1.Canvas.SetFgColor (0, 35 , 0);
                    draw1.Canvas.SetBgColor (0, 35 , 0);
                 }
                 else
                 {
                    draw1.Canvas.SetFgColor (0, 90*picpwr+35 , 0);
                    draw1.Canvas.SetBgColor (0, 90*picpwr+35 , 0);
                 }
                 draw1.Canvas.Rectangle (1, output[i].x1+26+(x*4)+(c*22), output[i].y1+16+(y*4)+(l*38), 4,4 );
               }
             }
           }
         } 
      };
       
    }
    else
    {
      draw1.Canvas.SetFgColor (0, 0, 0);
      
 
      switch(output[i].id)
      {
        case O_RA1: draw1.Canvas.SetBgColor (lm[17], 0, 0);break;
        case O_RA2: draw1.Canvas.SetBgColor (lm[0], 0, 0);break;
        case O_RA6: draw1.Canvas.SetBgColor (lm[14], 0, 0);break;
        case O_RA7: draw1.Canvas.SetBgColor (lm[15], 0, 0);break;
      }

      if(output[i].id == O_LPWR)draw1.Canvas.SetBgColor (0,255*picpwr, 0);
      
      draw1.Canvas.Circle (1,output[i].x1, output[i].y1,output[i].r );
    };
   };    

   rtc_update(&rtc);

break;

case 3:
case 4:
//lab3 draw
  for(i=0;i<outputc;i++)
  {
    if(!output[i].r)
    {
       
      draw1.Canvas.SetFgColor (30, 0, 0);
      
      switch(output[i].id) 
      {
        case O_A1: draw1.Canvas.SetBgColor (lm1[18], 0, 0);break;
        case O_B1: draw1.Canvas.SetBgColor (lm1[19], 0, 0);break;
        case O_C1: draw1.Canvas.SetBgColor (lm1[20], 0, 0);break;
        case O_D1: draw1.Canvas.SetBgColor (lm1[21], 0, 0);break;
        case O_E1: draw1.Canvas.SetBgColor (lm1[26], 0, 0);break;
        case O_F1: draw1.Canvas.SetBgColor (lm1[27], 0, 0);break;
        case O_G1: draw1.Canvas.SetBgColor (lm1[28], 0, 0);break;
        case O_P1: draw1.Canvas.SetBgColor (lm1[29], 0, 0);break;
          
        case O_A2: draw1.Canvas.SetBgColor (lm2[18], 0, 0);break;
        case O_B2: draw1.Canvas.SetBgColor (lm2[19], 0, 0);break;
        case O_C2: draw1.Canvas.SetBgColor (lm2[20], 0, 0);break;
        case O_D2: draw1.Canvas.SetBgColor (lm2[21], 0, 0);break;
        case O_E2: draw1.Canvas.SetBgColor (lm2[26], 0, 0);break;
        case O_F2: draw1.Canvas.SetBgColor (lm2[27], 0, 0);break;
        case O_G2: draw1.Canvas.SetBgColor (lm2[28], 0, 0);break;
        case O_P2: draw1.Canvas.SetBgColor (lm2[29], 0, 0);break;
      
        case O_A3: draw1.Canvas.SetBgColor (lm3[18], 0, 0);break;
        case O_B3: draw1.Canvas.SetBgColor (lm3[19], 0, 0);break;
        case O_C3: draw1.Canvas.SetBgColor (lm3[20], 0, 0);break;
        case O_D3: draw1.Canvas.SetBgColor (lm3[21], 0, 0);break;
        case O_E3: draw1.Canvas.SetBgColor (lm3[26], 0, 0);break;
        case O_F3: draw1.Canvas.SetBgColor (lm3[27], 0, 0);break;
        case O_G3: draw1.Canvas.SetBgColor (lm3[28], 0, 0);break;
        case O_P3: draw1.Canvas.SetBgColor (lm3[29], 0, 0);break;
      
        case O_A4: draw1.Canvas.SetBgColor (lm4[18], 0, 0);break;
        case O_B4: draw1.Canvas.SetBgColor (lm4[19], 0, 0);break;
        case O_C4: draw1.Canvas.SetBgColor (lm4[20], 0, 0);break;
        case O_D4: draw1.Canvas.SetBgColor (lm4[21], 0, 0);break;
        case O_E4: draw1.Canvas.SetBgColor (lm4[26], 0, 0);break;
        case O_F4: draw1.Canvas.SetBgColor (lm4[27], 0, 0);break;
        case O_G4: draw1.Canvas.SetBgColor (lm4[28], 0, 0);break;
        case O_P4: draw1.Canvas.SetBgColor (lm4[29], 0, 0);break;
     
        case O_LCD: draw1.Canvas.SetBgColor (0, 90*picpwr+40, 0);break;

        default : if((output[i].name[0]=='J')&&(output[i].name[1]=='P')) draw1.Canvas.SetBgColor (150, 150, 150);break;
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
                 if(lcd.ddram[c+(40*l)][x]  & (0x01<<y))
                 {  
                    draw1.Canvas.SetFgColor (0, 35 , 0);
                    draw1.Canvas.SetBgColor (0, 35 , 0);
                 }
                 else
                 {
                    draw1.Canvas.SetFgColor (0, 90*picpwr+35 , 0);
                    draw1.Canvas.SetBgColor (0, 90*picpwr+35 , 0);
                 }
                 draw1.Canvas.Rectangle (1, output[i].x1+26+(x*4)+(c*22), output[i].y1+16+(y*4)+(l*38), 4,4 );
               }
             }
           }
         } 
      };
       
      if((output[i].name[0]=='J')&&(output[i].name[1]=='P'))
      {
       if(!jmp[output[i].name[2]-0x31])
       {
         draw1.Canvas.SetBgColor (70, 70, 70);
         draw1.Canvas.Rectangle (1, output[i].x1, output[i].y1, (int)((output[i].x2-output[i].x1)*0.65),output[i].y2-output[i].y1 );
         draw1.Canvas.SetBgColor (220, 220, 0);
         draw1.Canvas.Circle (1,output[i].x1+(int)((output[i].x2-output[i].x1)*0.80), output[i].y1+((output[i].y2-output[i].y1)/2),3);
       }
       else
       {
         draw1.Canvas.SetBgColor (70, 70, 70);
         draw1.Canvas.Rectangle (1, output[i].x1+((int)((output[i].x2-output[i].x1)*0.35)), output[i].y1, (int)((output[i].x2-output[i].x1)*0.65),output[i].y2-output[i].y1 );
         draw1.Canvas.SetBgColor (220, 220, 0);
         draw1.Canvas.Circle (1,output[i].x1+(int)((output[i].x2-output[i].x1)*0.20), output[i].y1+((output[i].y2-output[i].y1)/2),3);
       };
      }       
/*      
      if(output[i].id == O_JP1)
      {
       if(jmp[0] == 0)
       {
         draw1.Canvas.SetBgColor (70, 70, 70);
         draw1.Canvas.Rectangle (1, output[i].x1, output[i].y1, (int)((output[i].x2-output[i].x1)*0.65),output[i].y2-output[i].y1 );
         draw1.Canvas.SetBgColor (220, 220, 0);
         draw1.Canvas.Circle (1,output[i].x1+(int)((output[i].x2-output[i].x1)*0.80), output[i].y1+((output[i].y2-output[i].y1)/2),3);
       }
       else
       {
         draw1.Canvas.SetBgColor (70, 70, 70);
         draw1.Canvas.Rectangle (1, output[i].x1+((int)((output[i].x2-output[i].x1)*0.35)), output[i].y1, (int)((output[i].x2-output[i].x1)*0.65),output[i].y2-output[i].y1 );
         draw1.Canvas.SetBgColor (220, 220, 0);
         draw1.Canvas.Circle (1,output[i].x1+(int)((output[i].x2-output[i].x1)*0.20), output[i].y1+((output[i].y2-output[i].y1)/2),3);
       };
      }
*/

       
    }
    else
    {
      draw1.Canvas.SetFgColor (0, 0, 0);
      
 
      //if(dsp_led == 0)
      {
        switch(output[i].id)
        {
          case O_RB0: draw1.Canvas.SetBgColor (lm[32], 0, 0);break;
          case O_RB1: draw1.Canvas.SetBgColor (lm[33], 0, 0);break;
          case O_RB2: draw1.Canvas.SetBgColor (lm[34], 0, 0);break;
          case O_RB3: draw1.Canvas.SetBgColor (lm[35], 0, 0);break;
        }
      } 
/* 
      else
      {
         if(strstr(output[i].name,"RB") != NULL)
            draw1.Canvas.SetBgColor (30, 0, 0);
      }
*/
      if(output[i].id == O_LPWR)draw1.Canvas.SetBgColor (0,255*picpwr, 0);
      
      draw1.Canvas.Circle (1,output[i].x1, output[i].y1,output[i].r );
    };    

  };
  break;
case 5:
case 6:
//lab5 draw
  for(i=0;i<outputc;i++)
  {
    if(!output[i].r)
    {
       
      draw1.Canvas.SetFgColor (30, 0, 0);
      
      switch(output[i].id) 
      {
        case O_A1: draw1.Canvas.SetBgColor (0, lm1[18], 0);break;
        case O_B1: draw1.Canvas.SetBgColor (0, lm1[19], 0);break;
        case O_C1: draw1.Canvas.SetBgColor (0, lm1[20], 0);break;
        case O_D1: draw1.Canvas.SetBgColor (0, lm1[21], 0);break;
        case O_E1: draw1.Canvas.SetBgColor (0, lm1[26], 0);break;
        case O_F1: draw1.Canvas.SetBgColor (0, lm1[27], 0);break;
        case O_G1: draw1.Canvas.SetBgColor (0, lm1[28], 0);break;
        case O_P1: draw1.Canvas.SetBgColor (0, lm1[29], 0);break;
          
        case O_A2: draw1.Canvas.SetBgColor (0, lm2[18], 0);break;
        case O_B2: draw1.Canvas.SetBgColor (0, lm2[19], 0);break;
        case O_C2: draw1.Canvas.SetBgColor (0, lm2[20], 0);break;
        case O_D2: draw1.Canvas.SetBgColor (0, lm2[21], 0);break;
        case O_E2: draw1.Canvas.SetBgColor (0, lm2[26], 0);break;
        case O_F2: draw1.Canvas.SetBgColor (0, lm2[27], 0);break;
        case O_G2: draw1.Canvas.SetBgColor (0, lm2[28], 0);break;
        case O_P2: draw1.Canvas.SetBgColor (0, lm2[29], 0);break;
      
        case O_A3: draw1.Canvas.SetBgColor (0, lm3[18], 0);break;
        case O_B3: draw1.Canvas.SetBgColor (0, lm3[19], 0);break;
        case O_C3: draw1.Canvas.SetBgColor (0, lm3[20], 0);break;
        case O_D3: draw1.Canvas.SetBgColor (0, lm3[21], 0);break;
        case O_E3: draw1.Canvas.SetBgColor (0, lm3[26], 0);break;
        case O_F3: draw1.Canvas.SetBgColor (0, lm3[27], 0);break;
        case O_G3: draw1.Canvas.SetBgColor (0, lm3[28], 0);break;
        case O_P3: draw1.Canvas.SetBgColor (0, lm3[29], 0);break;
      
        case O_A4: draw1.Canvas.SetBgColor (0, lm4[18], 0);break;
        case O_B4: draw1.Canvas.SetBgColor (0, lm4[19], 0);break;
        case O_C4: draw1.Canvas.SetBgColor (0, lm4[20], 0);break;
        case O_D4: draw1.Canvas.SetBgColor (0, lm4[21], 0);break;
        case O_E4: draw1.Canvas.SetBgColor (0, lm4[26], 0);break;
        case O_F4: draw1.Canvas.SetBgColor (0, lm4[27], 0);break;
        case O_G4: draw1.Canvas.SetBgColor (0, lm4[28], 0);break;
        case O_P4: draw1.Canvas.SetBgColor (0, lm4[29], 0);break;
     
        case O_RL1:
                 if(dip[3])
                    draw1.Canvas.SetBgColor (0,lm[14], 0);
                 else
                    draw1.Canvas.SetBgColor (0,15, 0);
                 break;
        case O_RL2: 
                 if(dip[4])
                    draw1.Canvas.SetBgColor (0,lm[7] , 0);
                 else                  
                    draw1.Canvas.SetBgColor (0,15, 0);
                 break;
 

        case O_LCD: draw1.Canvas.SetBgColor (0, 90*picpwr+40, 0);break;

        default : if((output[i].name[0]=='D')&&(output[i].name[1]=='P') ) draw1.Canvas.SetBgColor (250, 250, 250);break;
      }
     
      if(output[i].id != O_LCD)
        draw1.Canvas.Rectangle (1, output[i].x1, output[i].y1, output[i].x2-output[i].x1,output[i].y2-output[i].y1 );
 
//draw lcd text 
      if(dip[0])
      {
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
                 if(lcd.ddram[c+(40*l)][x]  & (0x01<<y))
                 {  
                    draw1.Canvas.SetFgColor (0, 35 , 0);
                    draw1.Canvas.SetBgColor (0, 35 , 0);
                 }
                 else
                 {
                    draw1.Canvas.SetFgColor (0, 90*picpwr+35 , 0);
                    draw1.Canvas.SetBgColor (0, 90*picpwr+35 , 0);
                 }
                 draw1.Canvas.Rectangle (1, output[i].x1+26+(x*4)+(c*22), output[i].y1+16+(y*4)+(l*38), 4,4 );
               }
             }
           }
         } 
      }
      }
      else
      {
         draw1.Canvas.Rectangle (1, output[i].x1, output[i].y1, output[i].x2-output[i].x1,output[i].y2-output[i].y1 );
      } 
       
      if((output[i].name[0]=='D')&&(output[i].name[1]=='P'))
      {
       if(!dip[(((output[i].name[2]-0x30)*10)+(output[i].name[3]-0x30))-1 ])
       {
         draw1.Canvas.SetBgColor (70, 70, 70);
         draw1.Canvas.Rectangle (1, output[i].x1,output[i].y1+((int)((output[i].y2-output[i].y1)*0.35)),output[i].x2-output[i].x1 , (int)((output[i].y2-output[i].y1)*0.65) );
         //draw1.Canvas.SetBgColor (220, 220, 0);
         //draw1.Canvas.Circle (1,output[i].x1+(int)((output[i].x2-output[i].x1)*0.20), output[i].y1+((output[i].y2-output[i].y1)/2),3);
       }
       else
       {
         draw1.Canvas.SetBgColor (70, 70, 70);
         draw1.Canvas.Rectangle (1, output[i].x1, output[i].y1,output[i].x2-output[i].x1 , (int)((output[i].y2-output[i].y1)*0.65));
         //draw1.Canvas.SetBgColor (220, 220, 0);
         //draw1.Canvas.Circle (1,output[i].x1+(int)((output[i].x2-output[i].x1)*0.80), output[i].y1+((output[i].y2-output[i].y1)/2),3);
       };
      }       
       
    }
    else
    {
      draw1.Canvas.SetFgColor (0, 0, 0);
      
          
        draw1.Canvas.SetBgColor (25, 15, 15);
 
        if(dip[9])
        switch(output[i].id)
        {
          case O_RB0: draw1.Canvas.SetBgColor (lm[32], 0, 0);break;
          case O_RB1: draw1.Canvas.SetBgColor (lm[33], 0, 0);break;
          case O_RB2: draw1.Canvas.SetBgColor (lm[34], 0, 0);break;
          case O_RB3: draw1.Canvas.SetBgColor (lm[35], 0, 0);break;
          case O_RB4: draw1.Canvas.SetBgColor (lm[36], 0, 0);break;
          case O_RB5: draw1.Canvas.SetBgColor (lm[37], 0, 0);break;
          case O_RB6: draw1.Canvas.SetBgColor (lm[38], 0, 0);break;
          case O_RB7: draw1.Canvas.SetBgColor (lm[39], 0, 0);break;
        }
         

        if(dip[8])
        switch(output[i].id)
        {
          case O_RD0: draw1.Canvas.SetBgColor (lm[18], 0, 0);break;
          case O_RD1: draw1.Canvas.SetBgColor (lm[19], 0, 0);break;
          case O_RD2: draw1.Canvas.SetBgColor (lm[20], 0, 0);break;
          case O_RD3: draw1.Canvas.SetBgColor (lm[21], 0, 0);break;
          case O_RD4: draw1.Canvas.SetBgColor (lm[26], 0, 0);break;
          case O_RD5: draw1.Canvas.SetBgColor (lm[27], 0, 0);break;
          case O_RD6: draw1.Canvas.SetBgColor (lm[28], 0, 0);break;
          case O_RD7: draw1.Canvas.SetBgColor (lm[29], 0, 0);break;
        }
          
      if(output[i].id == O_LPWR)draw1.Canvas.SetBgColor (0,255*picpwr, 0);
      
      draw1.Canvas.Circle (1,output[i].x1, output[i].y1,output[i].r );
    };    

  };
  rtc2_update(&rtc2);
  break;
  default:
    printf("Erro!\n"); 
    exit(-1);			
  break;
}
//end draw

  draw1.Canvas.End();
  draw1.Update ();
  
   switch(lab)
   {
   case 1: 
     for(pi=0;pi < pic.PINCOUNT;pi++)
     {
       lm[pi]=0;
       lm1[pi]=0;
       lm2[pi]=0;
     };
   break;
   case 2:
     for(pi=0;pi < pic.PINCOUNT;pi++)
     {
       lm[pi]=0;
     };
   break;
   case 3:		
   case 4:		
   case 5:		
   case 6:		
     for(pi=0;pi < pic.PINCOUNT;pi++)
     {
       lm[pi]=0;
       lm1[pi]=0;
       lm2[pi]=0;
       lm3[pi]=0;
       lm4[pi]=0;
     };
   break; 
   }
   
        


 pins = pic.pins;


 if(picpwr)
   for(i=0;i<NSTEP;i++)
      {
 
         switch(lab)
         {      
         case 1:  
          pic_set_pin(&pic,18,p_BT1); 
          pic_set_pin(&pic,1,p_BT2); 
          pic_set_pin(&pic,2,p_BT3); 
          pic_set_pin(&pic,3,p_BT4); 
         break;

         case 2:
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
         break;
        case 3:
        case 4:
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
          break; 
        case 5:
        case 6:
          pic_set_pin(&pic,33,p_BT1); 
          pic_set_pin(&pic,34,p_BT2); 
          pic_set_pin(&pic,35,p_BT3); 
          pic_set_pin(&pic,36,p_BT4);
          pic_set_pin(&pic,37,p_BT5);
          pic_set_pin(&pic,38,p_BT6);
          pic_set_pin(&pic,7,p_BT7);
          

          pic_set_pin(&pic,39,1);
          pic_set_pin(&pic,40,1);
          
          pic_set_pin(&pic,19,1);
          pic_set_pin(&pic,20,1);
          pic_set_pin(&pic,21,1);
          pic_set_pin(&pic,22,1);
          pic_set_pin(&pic,27,1);
          pic_set_pin(&pic,28,1);
          pic_set_pin(&pic,29,1);
          pic_set_pin(&pic,30,1);

          rpmc++;
          if(rpmc > rpmstp) 
          {
             rpmc=0;
             if(dip[14]) 
                 pic_set_pin(&pic,15, !pic_get_pin(&pic,15));
          }

          L[0]=!pic_get_pin(&pic,33);
          L[1]=!pic_get_pin(&pic,34);
          L[2]=!pic_get_pin(&pic,35);



          if(((L[0])&&(p_CL1 == 1))||((L[1])&&(p_CL2 == 1))||((L[2])&&(p_CL3 == 1)))
          {
             pic_set_pin(&pic,22,0); 
          }
          else
          {
             pic_set_pin(&pic,22,1);
          }

          if(((L[0])&&(p_CL1 == 2))||((L[1])&&(p_CL2 == 2))||((L[2])&&(p_CL3 == 2)))
          {
             pic_set_pin(&pic,21,0); 
          }
          else
          {
             pic_set_pin(&pic,21,1);
          }

          if(((L[0])&&(p_CL1 == 3))||((L[1])&&(p_CL2 == 3))||((L[2])&&(p_CL3 == 3)))
          {
             pic_set_pin(&pic,20,0); 
          }
          else
          {
             pic_set_pin(&pic,20,1);
          }

          if(((L[0])&&(p_CL1 == 4))||((L[1])&&(p_CL2 == 4))||((L[2])&&(p_CL3 == 4)))
          {
             pic_set_pin(&pic,19,0); 
          }
          else
          {
             pic_set_pin(&pic,19,1);
          }


          break; 
        } 
  
        pic_step(&pic,0);

        for(pi=0;pi < pic.PINCOUNT;pi++)
        {
           if((!pins[pi].dir)&&(pins[pi].value)) lm[pi]++;
        }
        
        switch(lab)
        {
        case 1:
          //pull-up extern 
          if((pins[17].dir)&&(p_BT1))lm[17]++; 
          if((pins[0].dir)&&(p_BT2))lm[0]++; 
          if((pins[1].dir)&&(p_BT3))lm[1]++;
          break;
        case 2:
          /*????????*/
          break;
        case 3: 
        case 4: 
          if((pins[32].dir)&&(p_BT1))lm[32]++; 
          if((pins[33].dir)&&(p_BT2))lm[33]++; 
          if((pins[34].dir)&&(p_BT3))lm[34]++; 
          if((pins[35].dir)&&(p_BT4))lm[35]++; 
          break;  
        case 5: 
        case 6: 
          if((pins[32].dir)&&(p_BT1))lm[32]++; 
          if((pins[33].dir)&&(p_BT2))lm[33]++; 
          if((pins[34].dir)&&(p_BT3))lm[34]++; 
          if((pins[35].dir)&&(p_BT4))lm[35]++; 
          if((pins[36].dir)&&(p_BT5))lm[36]++; 
          if((pins[37].dir)&&(p_BT6))lm[37]++; 
          
          if((pins[38].dir))lm[38]++; 
          if((pins[39].dir))lm[39]++; 

          if((pins[18].dir))lm[18]++; 
          if((pins[19].dir))lm[19]++; 
          if((pins[20].dir))lm[20]++; 
          if((pins[21].dir))lm[21]++; 
          if((pins[26].dir))lm[26]++; 
          if((pins[27].dir))lm[27]++; 
          if((pins[28].dir))lm[28]++; 
          if((pins[29].dir))lm[29]++; 

       //   if((pins[6].dir )&&(p_BT7))lm[6]++; 
          break;  
        }

  
          switch(lab)
          {
           case 1: 
            if(jmp[0])
            {
              for(pi=5;pi<13;pi++)
              {
                pinv=pic_get_pin(&pic,pi+1);
                if((pinv)&&(!pins[9].value)) lm1[pi]++;
                if((pinv)&&(pins[9].value)) lm2[pi]++;
              }
            }
            break;
          case 2:
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

//lcd display code
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
//end display code 
            break;
          case 3:
          case 4:
            for(pi=18;pi<30;pi++)
            {
              pinv=pins[pi].value;
              if((pinv)&&(pins[39].value)) lm1[pi]++;
              if((pinv)&&(pins[38].value)) lm2[pi]++;
              if((pinv)&&(pins[37].value)) lm3[pi]++;
              if((pinv)&&(pins[36].value)) lm4[pi]++;
            }
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
//end display code 
          break;
          case 5:
          case 6:
            for(pi=18;pi<30;pi++)
            {
              pinv=pins[pi].value;
              if((pinv)&&(pins[3].value)&&(dip[10])) lm1[pi]++;
              if((pinv)&&(pins[4].value)&&(dip[11])) lm2[pi]++;
              if((pinv)&&(pins[5].value)&&(dip[12])) lm3[pi]++;
              if((pinv)&&(pins[6].value)&&(dip[13])) lm4[pi]++;
            }
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
	pic_set_pin(&pic,23,mi2c_io(&mi2c,sck,sda) | rtc2_io(&rtc2,sck,sda));
        
     
// potenciometro p1 e p2
      if(dip[18])pic_set_apin(&pic,2,vp1in);
      if(dip[19])pic_set_apin(&pic,3,vp2in);

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

      if((!pins[9].dir)&&(!pins[9].value))
      {
        lcd_cmd(&lcd,d);
      }
      else if((!pins[9].dir)&&(pins[9].value))
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
//end display code 
          break;
          }
     }
   //fim STEP
   

   //printf("RA5 =%i\n",lm[6]);
  
   switch(lab)
   { 
     case 1:
     for(pi=0;pi < pic.PINCOUNT;pi++)
     { 
      lm[pi]= (int)(((225.0*lm[pi])/NSTEP)+30);
      lm1[pi]= (int)(((600.0*lm1[pi])/NSTEP)+30);
      lm2[pi]= (int)(((600.0*lm2[pi])/NSTEP)+30);
      if(lm1[pi] > 255)lm1[pi]=255;
      if(lm2[pi] > 255)lm2[pi]=255;
     }
     break;
   case 2:
     for(pi=0;pi < pic.PINCOUNT;pi++)
     { 
      lm[pi]= (int)(((225.0*lm[pi])/NSTEP)+30);
     }
     break;
   case 3 :
   case 4 :
     if( ((100.0*lm[6])/NSTEP) > 40)
     {
       buzz.Stop(); 
       buzz.Play(); 
     }

     //Ventilador
     gauge1.SetValue((100.0*lm[15])/NSTEP); 
     //Aquecedor
     gauge2.SetValue((100.0*lm[16])/NSTEP); 

     //sensor ventilador
     rpmstp=((float)NSTEP*NSTEP)/(144.0*(lm[15]+1));
   
     //tensão p2
     vp2in=((5.0*(scroll1.GetPosition()))/(scroll1.GetRange()-1));

     //temperatura 
     ref=((50.0*lm[16])/NSTEP)-((50.0*lm[15])/NSTEP); 

     if(ref < 0)
       ref=0; 
 
       temp[1]=temp[0];    
       temp[0]=((27.5+ref)*0.003)+temp[1]*(0.997);

     pic_set_apin(&pic,2,(10.0/255)*(temp[0]+15));
    
     //referencia
     pic_set_apin(&pic,5,2.5);

     for(pi=0;pi < pic.PINCOUNT;pi++)
     { 
      lm[pi]= (int)(((225.0*lm[pi])/NSTEP)+30);

      lm1[pi]= (int)(((600.0*lm1[pi])/NSTEP)+30);
      lm2[pi]= (int)(((600.0*lm2[pi])/NSTEP)+30);
      lm3[pi]= (int)(((600.0*lm3[pi])/NSTEP)+30);
      lm4[pi]= (int)(((600.0*lm4[pi])/NSTEP)+30);
      if(lm1[pi] > 255)lm1[pi]=255;
      if(lm2[pi] > 255)lm2[pi]=255;
      if(lm3[pi] > 255)lm3[pi]=255;
      if(lm4[pi] > 255)lm4[pi]=255;
     }
    break;
   case 5 :
   case 6 :
     if( ((100.0*lm[6])/NSTEP) > 40)
     {
       buzz.Stop(); 
       buzz.Play(); 
     }


     if(!dip[15])lm[23]=0;//aquecedor
     if(!dip[17])lm[16]=0;//ventilador


     //Ventilador
     gauge1.SetValue((100.0*lm[16])/NSTEP); 
     //Aquecedor
     gauge2.SetValue((100.0*lm[23])/NSTEP); 

     //sensor ventilador
     rpmstp=((float)NSTEP*NSTEP)/(144.0*(lm[16]+1));
   
     //tensão p2
     vp2in=((5.0*(scroll1.GetPosition()))/(scroll1.GetRange()-1));
     vp1in=((5.0*(scroll2.GetPosition()))/(scroll2.GetRange()-1));

     //temepratura 
     ref=((50.0*lm[23])/NSTEP)-((50.0*lm[16])/NSTEP); 

     if(ref < 0)
       ref=0; 
 
       temp[1]=temp[0];    
       temp[0]=((27.5+ref)*0.003)+temp[1]*(0.997);

     if(dip[16])
       pic_set_apin(&pic,4,temp[0]/100.0);
     else
       pic_set_apin(&pic,4,0);

     //referencia
     //pic_set_apin(&pic,5,2.5);

     for(pi=0;pi < pic.PINCOUNT;pi++)
     { 
      lm[pi]= (int)(((225.0*lm[pi])/NSTEP)+30);

      lm1[pi]= (int)(((600.0*lm1[pi])/NSTEP)+30);
      lm2[pi]= (int)(((600.0*lm2[pi])/NSTEP)+30);
      lm3[pi]= (int)(((600.0*lm3[pi])/NSTEP)+30);
      lm4[pi]= (int)(((600.0*lm4[pi])/NSTEP)+30);
      if(lm1[pi] > 255)lm1[pi]=255;
      if(lm2[pi] > 255)lm2[pi]=255;
      if(lm3[pi] > 255)lm3[pi]=255;
      if(lm4[pi] > 255)lm4[pi]=255;
     }
    break;
   }
   
   if(lab == 1) 
   {
     lm1[9]=30; 
     lm2[9]=30;
   }


   cend = clock();
   cpu_time_used = ((double) (cend - cstart)) / CLOCKS_PER_SEC;
   
   //printf("time=%f \n",cpu_time_used); 

   if(cpu_time_used > 0.09)
   {
      over++;

      if(over > 5)
      {
/*   
          picrun=0; 
          picpwr=0; 
          pic_reset(&pic,1);
          lcd_rst(&lcd);
	  mi2c_rst(&mi2c);
	  rtc_rst(&rtc);
	  rtc2_rst(&rtc2);

          p_BT1=0; 
          p_BT2=0; 
          p_BT3=0; 
          p_BT4=0; 
          
          over=0;
         
	 Message(wxT("Clock Overload.\n Decrease Clock and press PWR!")); 
         statusbar1.SetField(0,wxT("Stoped"));
*/
          over=0;

         int newf=((NSTEP-25000.0)/25000.0);//diminui clock
         
         if(newf < 1)newf=1;    

         printf("New Freq=%i\n",newf); 
 

         combo1.SetText(itoa(newf));//diminui clock
         combo1_EvOnComboChange(this);
 


       }  
   }
   else
   {
      over=0;
   }

   if(picpwr) 
      prog_loop(&pic);

};

