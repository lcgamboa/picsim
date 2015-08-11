
void
CPWindow1::board_1(void)
{
  int i;
  unsigned char pi;
  unsigned char pinv;
  unsigned int  lv;
  const picpin * pins;
  
  
  draw1.Canvas.Init(scale,scale);
  


//lab1 draw 
  for(i=0;i<outputc;i++)
  {
    if(!output[i].r)
    {
      if(output[i].id != O_JP1)
      {
      
      if(jmp[0])
      {
          switch(output[i].id)
          {         
            case O_A1: lv=lm1[7];break;
            case O_B1: lv=lm1[8];break;
            case O_C1: lv=lm1[10];break;
            case O_D1: lv=lm1[11];break;
            case O_E1: lv=lm1[12];break;
            case O_F1: lv=lm1[6];break;
            case O_G1: lv=lm1[5];break;
            case O_P1: lv=lm1[9];break;
            case O_A2: lv=lm2[7];break;
            case O_B2: lv=lm2[8];break;
            case O_C2: lv=lm2[10];break;
            case O_D2: lv=lm2[11];break;
            case O_E2: lv=lm2[12];break;
            case O_F2: lv=lm2[6];break;
            case O_G2: lv=lm2[5];break;
            case O_P2: lv=lm2[9];break;
            default: lv=0; break;
          }
          
          if(output[i].lval != (int)lv)
          {
            output[i].lval= lv;
            draw1.Canvas.SetColor (lv, 0, 0);
            draw1.Canvas.Rectangle (1, output[i].x1, output[i].y1, output[i].x2-output[i].x1,output[i].y2-output[i].y1 );
          }
      }
      else
      {
        if(output[i].lval != 0)
        {
          output[i].lval= 0;
          draw1.Canvas.SetColor (30, 0, 0);
          draw1.Canvas.Rectangle (1, output[i].x1, output[i].y1, output[i].x2-output[i].x1,output[i].y2-output[i].y1 ); 
        }
      } 


      }
      else
      { 
       
      if(output[i].id == O_JP1)
      {
       if(output[i].lval != jmp[0])
       {
         draw1.Canvas.SetColor (150, 150, 150);
         draw1.Canvas.Rectangle (1, output[i].x1, output[i].y1, output[i].x2-output[i].x1,output[i].y2-output[i].y1 );
         output[i].lval= jmp[0];
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
       }
       }
      }       
     }  
    }
    else
    {
      draw1.Canvas.SetFgColor (0, 0, 0);
 
      if(!jmp[0])
      {
        switch(output[i].id)
        {
          case O_RB0: lv=lm[5];break;
          case O_RB1: lv=lm[6];break;
          case O_RB2: lv=lm[7];break;
          case O_RB3: lv=lm[8];break;
          case O_RB4: lv=lm[9];break;
          case O_RB5: lv=lm[10];break;
          case O_RB6: lv=lm[11];break;
          case O_RB7: lv=lm[12];break;
          case O_RA0: lv=lm[16];break;
          case O_RA1: lv=lm[17];break;
          case O_RA2: lv=lm[0];break;
          case O_RA3: lv=lm[1];break;
          case O_RA0L: lv=lm[16];break;
	  default:lv=0;break;
        }
        if(output[i].lval != (int)lv)
        {
          output[i].lval= lv;
          if(output[i].name[0]=='R')
          {
            if(output[i].name[1]=='B')
            {
              draw1.Canvas.SetColor (lv, 0, 0);
            }
            else
            {
              draw1.Canvas.SetColor (0, lv, 0);
            } 
          }
          else
          {
            draw1.Canvas.SetColor (lv, lv, 0);
          }  
          draw1.Canvas.Circle (1,output[i].x1, output[i].y1,output[i].r );
        }
      }
      else
      {
        if(output[i].lval != 0)
        {
          output[i].lval= 0;
          if(output[i].name[0]=='R')
          {
            if(output[i].name[1]=='B')
            {
              draw1.Canvas.SetColor (30, 0, 0);
            }
            else
            {
              draw1.Canvas.SetColor (0, 30, 0);
            } 
          }
          else
          {
            draw1.Canvas.SetColor (30, 30, 0);
          }  
          draw1.Canvas.Circle (1,output[i].x1, output[i].y1,output[i].r );
        }
      }

      
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


 if(picpwr)
   for(i=0;i<NSTEP;i++)
      {
 
          pic_set_pin(&pic,18,p_BT1); 
          pic_set_pin(&pic,1,p_BT2); 
          pic_set_pin(&pic,2,p_BT3); 
          pic_set_pin(&pic,3,p_BT4); 
  
        pic_step(&pic,0);

        for(pi=0;pi < pic.PINCOUNT;pi++)
        {
           if((!pins[pi].dir)&&(pins[pi].value)) lm[pi]++;
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
     }
   //fim STEP
   
     for(pi=0;pi < pic.PINCOUNT;pi++)
     { 
      lm[pi]= (int)(((225.0*lm[pi])/NSTEP)+30);
      lm1[pi]= (int)(((600.0*lm1[pi])/NSTEP)+30);
      lm2[pi]= (int)(((600.0*lm2[pi])/NSTEP)+30);
      if(lm1[pi] > 255)lm1[pi]=255;
      if(lm2[pi] > 255)lm2[pi]=255;
     }

     lm1[9]=30; 
     lm2[9]=30;

};

