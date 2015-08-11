
void
CPWindow1::board_4(void)
{
  int i;
  int l,c,x,y;
  unsigned char pi;
  unsigned char pinv;
  //const picpin * pins;
  const picpin * pins;
  
  unsigned char L[4];
  

  
  draw1.Canvas.Init(scale,scale);
  

//lab5 draw 
  for(i=0;i<outputc;i++)
  {
    if(!output[i].r)
    {
       
      draw1.Canvas.SetFgColor (30, 0, 0);
      
      switch(output[i].id) 
      {
        case O_A1: draw1.Canvas.SetColor (0, lm1[18], 0);break;
        case O_B1: draw1.Canvas.SetColor (0, lm1[19], 0);break;
        case O_C1: draw1.Canvas.SetColor (0, lm1[20], 0);break;
        case O_D1: draw1.Canvas.SetColor (0, lm1[21], 0);break;
        case O_E1: draw1.Canvas.SetColor (0, lm1[26], 0);break;
        case O_F1: draw1.Canvas.SetColor (0, lm1[27], 0);break;
        case O_G1: draw1.Canvas.SetColor (0, lm1[28], 0);break;
        case O_P1: draw1.Canvas.SetColor (0, lm1[29], 0);break;
          
        case O_A2: draw1.Canvas.SetColor (0, lm2[18], 0);break;
        case O_B2: draw1.Canvas.SetColor (0, lm2[19], 0);break;
        case O_C2: draw1.Canvas.SetColor (0, lm2[20], 0);break;
        case O_D2: draw1.Canvas.SetColor (0, lm2[21], 0);break;
        case O_E2: draw1.Canvas.SetColor (0, lm2[26], 0);break;
        case O_F2: draw1.Canvas.SetColor (0, lm2[27], 0);break;
        case O_G2: draw1.Canvas.SetColor (0, lm2[28], 0);break;
        case O_P2: draw1.Canvas.SetColor (0, lm2[29], 0);break;
      
        case O_A3: draw1.Canvas.SetColor (0, lm3[18], 0);break;
        case O_B3: draw1.Canvas.SetColor (0, lm3[19], 0);break;
        case O_C3: draw1.Canvas.SetColor (0, lm3[20], 0);break;
        case O_D3: draw1.Canvas.SetColor (0, lm3[21], 0);break;
        case O_E3: draw1.Canvas.SetColor (0, lm3[26], 0);break;
        case O_F3: draw1.Canvas.SetColor (0, lm3[27], 0);break;
        case O_G3: draw1.Canvas.SetColor (0, lm3[28], 0);break;
        case O_P3: draw1.Canvas.SetColor (0, lm3[29], 0);break;
      
        case O_A4: draw1.Canvas.SetColor (0, lm4[18], 0);break;
        case O_B4: draw1.Canvas.SetColor (0, lm4[19], 0);break;
        case O_C4: draw1.Canvas.SetColor (0, lm4[20], 0);break;
        case O_D4: draw1.Canvas.SetColor (0, lm4[21], 0);break;
        case O_E4: draw1.Canvas.SetColor (0, lm4[26], 0);break;
        case O_F4: draw1.Canvas.SetColor (0, lm4[27], 0);break;
        case O_G4: draw1.Canvas.SetColor (0, lm4[28], 0);break;
        case O_P4: draw1.Canvas.SetColor (0, lm4[29], 0);break;
     
        case O_RL1:
                 if(dip[3])
                    draw1.Canvas.SetColor (0,lm[14], 0);
                 else
                    draw1.Canvas.SetColor (0,15, 0);
                 break;
        case O_RL2: 
                 if(dip[4])
                    draw1.Canvas.SetColor (0,lm[7] , 0);
                 else                  
                    draw1.Canvas.SetColor (0,15, 0);
                 break;
 

        case O_LCD: draw1.Canvas.SetColor (0, 90*picpwr+40, 0);break;

        default : 
           if((output[i].name[0]=='D')&&(output[i].name[1]=='P') )
           {
             draw1.Canvas.SetBgColor (250, 250, 250);break;
           };
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
                    draw1.Canvas.SetColor (0, 35 , 0);
                 }
                 else
                 {
                    draw1.Canvas.SetFgColor (0, 90*picpwr+35 , 0);
                    draw1.Canvas.SetColor (0, 90*picpwr+35 , 0);
                 }
       //          draw1.Canvas.Rectangle (1, output[i].x1+12+(x*4)+(c*22), output[i].y1+8+(y*4)+(l*38), 4,4 );
                 draw1.Canvas.Rectangle (1, output[i].x1+2+(x*4)+(c*23), output[i].y1+10+(y*4)+(l*35), 4,4 );
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
         //draw1.Canvas.SetColor (220, 220, 0);
         //draw1.Canvas.Circle (1,output[i].x1+(int)((output[i].x2-output[i].x1)*0.20), output[i].y1+((output[i].y2-output[i].y1)/2),3);
       }
       else
       {
         draw1.Canvas.SetBgColor (70, 70, 70);
         draw1.Canvas.Rectangle (1, output[i].x1, output[i].y1,output[i].x2-output[i].x1 , (int)((output[i].y2-output[i].y1)*0.65));
         //draw1.Canvas.SetColor (220, 220, 0);
         //draw1.Canvas.Circle (1,output[i].x1+(int)((output[i].x2-output[i].x1)*0.80), output[i].y1+((output[i].y2-output[i].y1)/2),3);
       };
      }       
        
    }
    else
    {
      draw1.Canvas.SetFgColor (0, 0, 0);
      
          
        draw1.Canvas.SetColor (25, 15, 15);
 
        if(dip[9])
        switch(output[i].id)
        {
          case O_RB0: draw1.Canvas.SetColor (lm[32], 0, 0);break;
          case O_RB1: draw1.Canvas.SetColor (lm[33], 0, 0);break;
          case O_RB2: draw1.Canvas.SetColor (lm[34], 0, 0);break;
          case O_RB3: draw1.Canvas.SetColor (lm[35], 0, 0);break;
          case O_RB4: draw1.Canvas.SetColor (lm[36], 0, 0);break;
          case O_RB5: draw1.Canvas.SetColor (lm[37], 0, 0);break;
          case O_RB6: draw1.Canvas.SetColor (lm[38], 0, 0);break;
          case O_RB7: draw1.Canvas.SetColor (lm[39], 0, 0);break;
        }
         

        if(dip[8])
        switch(output[i].id)
        {
          case O_RD0: draw1.Canvas.SetColor (lm[18], 0, 0);break;
          case O_RD1: draw1.Canvas.SetColor (lm[19], 0, 0);break;
          case O_RD2: draw1.Canvas.SetColor (lm[20], 0, 0);break;
          case O_RD3: draw1.Canvas.SetColor (lm[21], 0, 0);break;
          case O_RD4: draw1.Canvas.SetColor (lm[26], 0, 0);break;
          case O_RD5: draw1.Canvas.SetColor (lm[27], 0, 0);break;
          case O_RD6: draw1.Canvas.SetColor (lm[28], 0, 0);break;
          case O_RD7: draw1.Canvas.SetColor (lm[29], 0, 0);break;
        }
          
      if(output[i].id == O_LPWR)draw1.Canvas.SetColor (0,255*picpwr, 0);
      
      draw1.Canvas.Circle (1,output[i].x1, output[i].y1,output[i].r );
    };    

  };
  rtc2_update(&rtc2);
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


 if(picpwr)
   for(i=0;i<NSTEP;i++)
      {
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


        pic_step(&pic,0);
/*
        for(pi=0;pi < pic.PINCOUNT;pi++)
        {
           lm[pi]+=pins[pi].value;
           //if((!pins[pi].dir)&&(pins[pi].value)) lm[pi]++;
        }
*/
      
//outputs     
          lm[32]+=pins[32].value;
          lm[33]+=pins[33].value;
          lm[34]+=pins[34].value;
          lm[35]+=pins[35].value;
          lm[36]+=pins[36].value;
          lm[37]+=pins[37].value;
          lm[38]+=pins[38].value;
          lm[39]+=pins[39].value;

          lm[18]+=pins[18].value;
          lm[19]+=pins[19].value;
          lm[20]+=pins[20].value;
          lm[21]+=pins[21].value;
          lm[26]+=pins[26].value;
          lm[27]+=pins[27].value;
          lm[28]+=pins[28].value;
          lm[29]+=pins[29].value;
        
          lm[23]+=pins[23].value;
          lm[16]+=pins[16].value;
          lm[14]+=pins[14].value;
          lm[7]+=pins[7].value;

//inputs
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

            for(pi=18;pi<30;pi++)
            {
              pinv=pins[pi].value;
              if((pinv)&&(pins[3].value)&&(dip[10])) lm1[pi]++;
              if((pinv)&&(pins[4].value)&&(dip[11])) lm2[pi]++;
              if((pinv)&&(pins[5].value)&&(dip[12])) lm3[pi]++;
              if((pinv)&&(pins[6].value)&&(dip[13])) lm4[pi]++;
            }

	if(dip[7])lm[32]=0;

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


//lcd dipins[2].display code

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
     
     }

   //fim STEP
   
/*
     if( ((100.0*lm[16])/NSTEP) > 40)
     {
       buzz.Stop(); 
       buzz.Play(); 
     }
*/
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
  
 
};

