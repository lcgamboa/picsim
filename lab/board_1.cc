
#include"picsimlab1.h"

void
CPWindow1::board_1(void)
{
  int i;
  int j;
  unsigned char pi;
  unsigned char pinv;
  const picpin * pins;
  
  draw1.Canvas.Init(scale,scale);
  


//lab1 draw 
  for(i=0;i<outputc;i++)
  {
    if(!output[i].r)
    {
      draw1.Canvas.SetFgColor (30, 0, 0);
      
      if(jmp[0])
      {
          switch(output[i].id)
          {         
            case O_A1: draw1.Canvas.SetColor (lm1[7], 0, 0);break;
            case O_B1: draw1.Canvas.SetColor (lm1[8], 0, 0);break;
            case O_C1: draw1.Canvas.SetColor (lm1[10], 0, 0);break;
            case O_D1: draw1.Canvas.SetColor (lm1[11], 0, 0);break;
            case O_E1: draw1.Canvas.SetColor (lm1[12], 0, 0);break;
            case O_F1: draw1.Canvas.SetColor (lm1[6], 0, 0);break;
            case O_G1: draw1.Canvas.SetColor (lm1[5], 0, 0);break;
            case O_P1: draw1.Canvas.SetColor (lm1[9], 0, 0);break;
            case O_A2: draw1.Canvas.SetColor (lm2[7], 0, 0);break;
            case O_B2: draw1.Canvas.SetColor (lm2[8], 0, 0);break;
            case O_C2: draw1.Canvas.SetColor (lm2[10], 0, 0);break;
            case O_D2: draw1.Canvas.SetColor (lm2[11], 0, 0);break;
            case O_E2: draw1.Canvas.SetColor (lm2[12], 0, 0);break;
            case O_F2: draw1.Canvas.SetColor (lm2[6], 0, 0);break;
            case O_G2: draw1.Canvas.SetColor (lm2[5], 0, 0);break;
            case O_P2: draw1.Canvas.SetColor (lm2[9], 0, 0);break;
          }
      }
      else
      {
        draw1.Canvas.SetColor (30, 0, 0);
      } 

      if(output[i].id == O_JP1) draw1.Canvas.SetColor (150, 150, 150);

      draw1.Canvas.Rectangle (1, output[i].x1, output[i].y1, output[i].x2-output[i].x1,output[i].y2-output[i].y1 );

       
      if(output[i].id == O_JP1)
      {
       if(!jmp[0])
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
      
 
      if(!jmp[0])
      {
        switch(output[i].id)
        {
          case O_RB0: draw1.Canvas.SetColor (lm[5], 0, 0);break;
          case O_RB1: draw1.Canvas.SetColor (lm[6], 0, 0);break;
          case O_RB2: draw1.Canvas.SetColor (lm[7], 0, 0);break;
          case O_RB3: draw1.Canvas.SetColor (lm[8], 0, 0);break;
          case O_RB4: draw1.Canvas.SetColor (lm[9], 0, 0);break;
          case O_RB5: draw1.Canvas.SetColor (lm[10], 0, 0);break;
          case O_RB6: draw1.Canvas.SetColor (lm[11], 0, 0);break;
          case O_RB7: draw1.Canvas.SetColor (lm[12], 0, 0);break;
        }
      }
      else
      {
         if((output[i].name[0]=='R')&&(output[i].name[1]=='B'))
            draw1.Canvas.SetColor (30, 0, 0);
      }

      switch(output[i].id)
      {
        case O_RA0: draw1.Canvas.SetColor (0, lm[16], 0);break;
        case O_RA1: draw1.Canvas.SetColor (0, lm[17], 0);break;
        case O_RA2: draw1.Canvas.SetColor (0, lm[0], 0);break;
        case O_RA3: draw1.Canvas.SetColor (0, lm[1], 0);break;
        case O_RA0L: draw1.Canvas.SetColor (lm[16],lm[16], 0);break;
      }
      
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
     };

 pins = pic.pins;

  
 j=JUMP+1;
 if(picpwr)
   for(i=0;i<NSTEP;i++)
      {
 
          if(j >JUMP)
          {  
          pic_set_pin(&pic,18,p_BT1); 
          pic_set_pin(&pic,1,p_BT2); 
          pic_set_pin(&pic,2,p_BT3); 
          pic_set_pin(&pic,3,p_BT4);
          } 
        pic_step(&pic,0);

          if(j >JUMP)
          {  
        for(pi=0;pi < pic.PINCOUNT;pi++)
        {
           lm[pi]+=pins[pi].value;
           //if((!pins[pi].dir)&&(pins[pi].value)) lm[pi]++;
        }
        
          //pull-up extern 
          if((pins[17].dir)&&(p_BT1))lm[17]++; 
          if((pins[0].dir)&&(p_BT2))lm[0]++; 
          if((pins[1].dir)&&(p_BT3))lm[1]++;

            if(jmp[0])
            {
              for(pi=5;pi<13;pi++)
              {
                pinv=pic_get_pin(&pic,pi+1);
                if((pinv)&&(!pins[9].value)) lm1[pi]++;
                if((pinv)&&(pins[9].value)) lm2[pi]++;
              }
            }
          j=0;
          } 
          j++;
     }
   //fim STEP
   
     for(pi=0;pi < pic.PINCOUNT;pi++)
     { 
      lm[pi]= (int)(((225.0*lm[pi])/NSTEPJ)+30);
      lm1[pi]= (int)(((600.0*lm1[pi])/NSTEPJ)+30);
      lm2[pi]= (int)(((600.0*lm2[pi])/NSTEPJ)+30);
      if(lm1[pi] > 255)lm1[pi]=255;
      if(lm2[pi] > 255)lm2[pi]=255;
     }

     lm1[9]=30; 
     lm2[9]=30;

};

