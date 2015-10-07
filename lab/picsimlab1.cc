


#define TIMER           0.1      //timer period in s
#define CPUTUSEMAX      0.1      //max period cpu use in s 
#define NSTEPKT     25000.0      //TIMER constant 1MHz/(4.0*timer_freq) 
#define NSTEPKF        40.0      //Freq constant 4.0*timer_freq



#include"picsimlab1.h"
#include"picsimlab1_d.cc"



CPWindow1 Window1;


//Implementation

#include"picsimlab2.h"
#include"picsimlab3.h"

#include<dirent.h>

extern char PROGDEVICE[100];

char SERIALDEVICE[100];

int prog_init(void);
int prog_loop(_pic * pic);
int prog_end(void);


void
CPWindow1::timer1_EvOnTime(CControl * control)
{

 clock_t cstart=0, cend=0;
 double cpu_time_used;

  //TODO implement loop in one separed thread
  cstart = clock();

  switch(lab)
  {
    case 1:
     board_1();
     break;
    case 2:
     board_2();
     break;
    case 3:
     board_3();
     break;
    case 4:
     board_4();
     break;
  }

   cend = clock();
   cpu_time_used = ((double) (cend - cstart)) / CLOCKS_PER_SEC;


   //printf("time=%f \n",cpu_time_used);


   if(cpu_time_used > CPUTUSEMAX)
   {
      over+=(cpu_time_used-CPUTUSEMAX);
   
      //printf("over= %f   \n",over);

      if(over > 0.5)
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

         int newf=((NSTEP-NSTEPKT)/NSTEPKT);//diminui clock
         
         if(newf <= 1)newf=1;    

         //printf("New Freq=%i\n",newf); 
 

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


   cstart=0;
  // Application->ProcessEvents();


};


void
CPWindow1::timer2_EvOnTime(CControl * control)
{

//serial port status
   if(lab > 1)
   {
#ifndef _WIN_
    if(pic.serialfd > 0)
#else
    if(pic.serialfd != INVALID_HANDLE_VALUE)
#endif
      statusbar1.SetField(2,wxT("Serial Port: ")+String::FromAscii(SERIALDEVICE)+wxT(":")+itoa(pic.serialbaud)+wxT("(")+String().Format("%4.1f",fabs((100.0*pic.serialexbaud-100.0*pic.serialbaud)/pic.serialexbaud))+wxT("%)"));
    else  
      statusbar1.SetField(2,wxT("Serial Port: ")+String::FromAscii(SERIALDEVICE)+wxT(" (ERROR)"));
   }

   if(lab > 2)
   {
      label8.SetText(wxT("Temp: ")+String().Format("%5.2f",temp[0])+wxT("°C"));
   }

 
};



void
CPWindow1::draw1_EvMouseButtonPress(CControl * control, uint button, uint x, uint y,uint state)
{
  int i,pa;
 
  x=x/scale;
  y=y/scale;
  
  //code here:)
  //printf("draw1_EvMouseButtonPress (%u  %u)\n",x,y);

  for(i=0;i<inputc;i++)
  {
    if(((input[i].x1 <= x)&&(input[i].x2 >= x))&&((input[i].y1 <= y)&&(input[i].y2 >= y)))
    {
   
      switch(input[i].id) 
      { 
      case I_ICSP:
      {
        pa=picpwr; 
        picpwr=0;
        if(filedialog1.Run())
        {
  	  pic_end(&pic);
  	  mi2c_end(&mi2c);
  	  rtc_end(&rtc);
  	  rtc2_end(&rtc2);
          pic_set_serial(&pic,SERIALDEVICE,0,0,0);
          picrun=pic_init(&pic,family,proc,filedialog1.GetFileName().char_str(),1,NSTEP*NSTEPKF);
          lcd_rst(&lcd);
          pic.config[0] |= 0x0800; //disable DEBUG
          switch(lab)
          {
            case 2: 
	      mi2c_init(&mi2c,512);
	      rtc_init(&rtc);
              break;
            case 1:
            case 3: 
	      mi2c_init(&mi2c,4);
              break;
            case 4: 
	      mi2c_init(&mi2c,4);
	      rtc2_init(&rtc2);
              break;
          };
 
          if(picrun) 
            Window1.SetTitle(wxT("PicsimLab - ")+basename(filedialog1.GetFileName()));          
          else
            Window1.SetTitle(wxT("PicsimLab"));
          
          p_BT1=1; 
          p_BT2=1; 
          p_BT3=1; 
          p_BT4=1; 
          p_BT5=1; 
          p_BT6=1; 
          p_BT7=1; 
          
          switch(lab)
          {
           case 1:
            pic_set_pin(&pic,18,p_BT1); 
            pic_set_pin(&pic,1,p_BT2); 
            pic_set_pin(&pic,2,p_BT3); 
            pic_set_pin(&pic,3,p_BT4);
            break;
          case 2:
            p_CL1=0; 
            p_CL2=0; 
            p_CL3=0; 
            pic_set_pin(&pic,13,p_CL1); 
            pic_set_pin(&pic,12,p_CL2); 
            pic_set_pin(&pic,11,p_CL3); 
            break;
          case 3: 
            pic_set_pin(&pic,33,p_BT1); 
            pic_set_pin(&pic,34,p_BT2); 
            pic_set_pin(&pic,35,p_BT3); 
            pic_set_pin(&pic,36,p_BT4);  
            break;  
          case 4: 
            pic_set_pin(&pic,33,p_BT1); 
            pic_set_pin(&pic,34,p_BT2); 
            pic_set_pin(&pic,35,p_BT3); 
            pic_set_pin(&pic,36,p_BT4);
            pic_set_pin(&pic,37,p_BT5);
            pic_set_pin(&pic,38,p_BT6);
            pic_set_pin(&pic,7,p_BT7);
            
            p_CL1=0; 
            p_CL2=0; 
            p_CL3=0; 
            pic_set_pin(&pic,33,p_CL1); 
            pic_set_pin(&pic,34,p_CL2); 
            pic_set_pin(&pic,35,p_CL3); 
 
            break; 
          } 
          PATH=filedialog1.GetDir();
          FNAME=filedialog1.GetFileName();
        }
        picpwr=pa;
      };break;  
      
      case I_JP1:
      {
        jmp[0]^=0x01; 
      };break;
      case I_JP2:
      {
        jmp[1]^=0x01; 
      };break;
      case I_JP3:
      {
        jmp[2]^=0x01; 
      };break;
      case I_JP4:
      {
        jmp[3]^=0x01; 
      };break;
      case I_JP5:
      {
        jmp[4]^=0x01; 
      };break;
      case I_JP6:
      {
        jmp[5]^=0x01; 
      };break;
      case I_JP7:
      {
        jmp[6]^=0x01; 
      };break;
      case I_JP8:
      {
        jmp[7]^=0x01; 
      };break;
      case I_D01:
      {
        dip[0]^=0x01; 
      };break;
      case I_D02:
      {
        dip[1]^=0x01; 
      };break;
      case I_D03:
      {
        dip[2]^=0x01; 
      };break;
      case I_D04:
      {
        dip[3]^=0x01; 
      };break;
      case I_D05:
      {
        dip[4]^=0x01; 
      };break;
      case I_D06:
      {
        dip[5]^=0x01; 
      };break;
      case I_D07:
      {
        dip[6]^=0x01; 
      };break;
      case I_D08:
      {
        dip[7]^=0x01; 
      };break;
      case I_D09:
      {
        dip[8]^=0x01; 
      };break;
      case I_D10:
      {
        dip[9]^=0x01; 
      };break;
      case I_D11:
      {
        dip[10]^=0x01; 
      };break;
      case I_D12:
      {
        dip[11]^=0x01; 
      };break;
      case I_D13:
      {
        dip[12]^=0x01; 
      };break;
      case I_D14:
      {
        dip[13]^=0x01; 
      };break;
      case I_D15:
      {
        dip[14]^=0x01; 
      };break;
      case I_D16:
      {
        dip[15]^=0x01; 
      };break;
      case I_D17:
      {
        dip[16]^=0x01; 
      };break;
      case I_D18:
      {
        dip[17]^=0x01; 
      };break;
      case I_D19:
      {
        dip[18]^=0x01; 
      };break;
      case I_D20:
      {
        dip[19]^=0x01; 
      };break;
      
      case I_PWR:
      {
        if(picpwr) 
        { 
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
          statusbar1.SetField(0,wxT("Stoped"));
        }
        else
        {
          picpwr=1;
          picrun=1;
          pic_reset(&pic,1);  
          lcd_rst(&lcd);
	  mi2c_rst(&mi2c);
	  rtc_rst(&rtc);
	  rtc2_rst(&rtc2);
        
          p_BT1=1; 
          p_BT2=1; 
          p_BT3=1; 
          p_BT4=1;
          p_BT5=1;
          p_BT6=1;
          p_BT7=1;
          
          switch(lab)
          { 
           case 1: 
            pic_set_pin(&pic,18,p_BT1); 
            pic_set_pin(&pic,1,p_BT2); 
            pic_set_pin(&pic,2,p_BT3); 
            pic_set_pin(&pic,3,p_BT4);
            break;
           case 2:
            p_CL1=0; 
            p_CL2=0; 
            p_CL3=0; 
            pic_set_pin(&pic,13,p_CL1); 
            pic_set_pin(&pic,12,p_CL2); 
            pic_set_pin(&pic,11,p_CL3); 
            break;
           case 3: 
            pic_set_pin(&pic,33,p_BT1); 
            pic_set_pin(&pic,34,p_BT2); 
            pic_set_pin(&pic,35,p_BT3); 
            pic_set_pin(&pic,36,p_BT4); 
            break;
           case 4: 
            pic_set_pin(&pic,33,p_BT1); 
            pic_set_pin(&pic,34,p_BT2); 
            pic_set_pin(&pic,35,p_BT3); 
            pic_set_pin(&pic,36,p_BT4); 
            pic_set_pin(&pic,37,p_BT5); 
            pic_set_pin(&pic,38,p_BT6); 
            pic_set_pin(&pic,7,p_BT7); 
            p_CL1=0; 
            p_CL2=0; 
            p_CL3=0; 
            pic_set_pin(&pic,33,p_CL1); 
            pic_set_pin(&pic,34,p_CL2); 
            pic_set_pin(&pic,35,p_CL3); 
            break;
          }  
          statusbar1.SetField(0,wxT("Running..."));
        } 
      };break;
      
      case I_RST:
      {
          if(picpwr)
          {
             picpwr=0;
             picrst=1;
          } 
      };break;
      
      case I_RA1:
        {
          p_BT1=0;
        };break;
      case I_RA2:
        {
          p_BT2=0; 
        };break;
      case I_RA3:
        {
          p_BT3=0; 
        };break;
      case I_RA4:
        {
          p_BT4=0; 
        };break;
      case I_RA5:
        {
          p_BT7=0; 
        };break;
      case I_RB0:
        {
          p_BT1=0;
        };break;
      case I_RB1:
        {
          p_BT2=0; 
        };break;
      case I_RB2:
        {
          p_BT3=0; 
        };break;
      case I_RB3:
        {
          p_BT4=0; 
        };break;
      case I_RB4:
        {
          p_BT5=0; 
        };break;
      case I_RB5:
        {
          p_BT6=0; 
        };break;

      case I_TC1:
        {
          p_CL1=1;
        };break;
      case I_TC2:
        {
          p_CL2=1; 
        };break;
      case I_TC3:
        {
          p_CL3=1; 
        };break;

      case I_TC4:
        {
          p_CL1=2; 
        };break;
      case I_TC5:
        {
          p_CL2=2; 
        };break;
      case I_TC6:
        {
          p_CL3=2; 
        };break;

      case I_TC7:
        {
          p_CL1=3; 
        };break;
      case I_TC8:
        {
          p_CL2=3; 
        };break;
      case I_TC9:
        {
          p_CL3=3; 
        };break;
      
      case I_TCA:
        {
          p_CL1=4; 
        };break;
      case I_TC0:
        {
          p_CL2=4; 
        };break;
      case I_TCT:
        {
          p_CL3=4; 
        };break;

      }
    }
  }

};


void
CPWindow1::draw1_EvMouseButtonRelease(CControl * control, uint button, uint x, uint y,uint state)
{
  int i;
  
  x=x/scale;
  y=y/scale;

  //code here:)
  //mprint(wxT("draw1_EvMouseButtonRelease\n"));
      

  for(i=0;i<inputc;i++)
  {
    if(((input[i].x1 <= x)&&(input[i].x2 >= x))&&((input[i].y1 <= y)&&(input[i].y2 >= y)))
    {
      switch(input[i].id)
      {
      case I_RST:
      {
          if(picrst)
          {
            picpwr=1;
            picrst=0;

            if(pic_reset(&pic,-1))
            { 
              lcd_rst(&lcd);
	      mi2c_rst(&mi2c);
	      rtc_rst(&rtc);
	      rtc2_rst(&rtc2);

              p_BT1=1; 
              p_BT2=1; 
              p_BT3=1; 
              p_BT4=1; 
              p_BT5=1; 
              p_BT6=1; 
              p_BT7=1; 
          
              switch(lab)
              { 
               case 1:
                pic_set_pin(&pic,18,p_BT1); 
                pic_set_pin(&pic,1,p_BT2); 
                pic_set_pin(&pic,2,p_BT3); 
                pic_set_pin(&pic,3,p_BT4);
                break;  
              case 2:
                p_CL1=0; 
                p_CL2=0; 
                p_CL3=0; 
                pic_set_pin(&pic,13,p_CL1); 
                pic_set_pin(&pic,12,p_CL2); 
                pic_set_pin(&pic,11,p_CL3); 
                break;
              case 3:
                pic_set_pin(&pic,33,p_BT1); 
                pic_set_pin(&pic,34,p_BT2); 
                pic_set_pin(&pic,35,p_BT3); 
                pic_set_pin(&pic,36,p_BT4); 
                break;
              case 4:
                pic_set_pin(&pic,33,p_BT1); 
                pic_set_pin(&pic,34,p_BT2); 
                pic_set_pin(&pic,35,p_BT3); 
                pic_set_pin(&pic,36,p_BT4); 
                pic_set_pin(&pic,37,p_BT5); 
                pic_set_pin(&pic,38,p_BT6); 
                pic_set_pin(&pic,7,p_BT7); 
                p_CL1=0; 
                p_CL2=0; 
                p_CL3=0; 
                pic_set_pin(&pic,33,p_CL1); 
                pic_set_pin(&pic,34,p_CL2); 
                pic_set_pin(&pic,35,p_CL3); 
                break;
              }
            }
          } 
      };break;
      
        case I_RA1:
        {
          p_BT1=1; 
        };break;
        case I_RA2:
        {
          p_BT2=1; 
        };break;
        case I_RA3:
        {
          p_BT3=1; 
        };break;
        case I_RA4:
        {
          p_BT4=1; 
        };break;
        case I_RA5:
        {
          p_BT7=1; 
        };break;
        case I_RB0:
        {
          p_BT1=1; 
        };break;
        case I_RB1:
        {
          p_BT2=1; 
        };break;
        case I_RB2:
        {
          p_BT3=1; 
        };break;
        case I_RB3:
        {
          p_BT4=1; 
        };break;
        case I_RB4:
        {
          p_BT5=1; 
        };break;
        case I_RB5:
        {
          p_BT6=1; 
        };break;

        case I_TC1:
        case I_TC4:
        case I_TC7:
        case I_TCA:
        {
          p_CL1=0; 
        };break;

        case I_TC2:
        case I_TC5:
        case I_TC8:
        case I_TC0:
        {
          p_CL2=0; 
        };break;

        case I_TC3:
        case I_TC6:
        case I_TC9:
        case I_TCT:
        {
          p_CL3=0; 
        };break;
      }
    } 
  }
};


void
CPWindow1::draw1_EvKeyboardPress(CControl * control, uint key, uint x, uint y,uint mask)
{
  //code here:)
  //mprint(wxT("draw1_EvKeyboardPress\n"));


  switch(lab)
  {
   case 1:
   case 3:
  if(key == '1')
  {
    p_BT1=0; 
  }
  if(key == '2')
  {
    p_BT2=0; 
  }
  if(key == '3')
  {
    p_BT3=0; 
  }
  if(key == '4')
  {
    p_BT4=0; 
  }
  break;
  case 2:
  case 4:
  if(key == '1')
  {
    p_CL1=1; 
  }
  if(key == '2')
  {
    p_CL2=1; 
  }
  if(key == '3')
  {
    p_CL3=1; 
  }

  if(key == '4')
  {
    p_CL1=2; 
  }
  if(key == '5')
  {
    p_CL2=2; 
  }
  if(key == '6')
  {
    p_CL3=2; 
  }

  if(key == '7')
  {
    p_CL1=3; 
  }
  if(key == '8')
  {
    p_CL2=3; 
  }
  if(key == '9')
  {
    p_CL3=3; 
  }

  if(key == '*')
  {
    p_CL1=4; 
  }
  if(key == '0')
  {
    p_CL2=4; 
  }
  if(key == '#')
  {
    p_CL3=4; 
  }
  break;
  }
 
};


void
CPWindow1::draw1_EvKeyboardRelease(CControl * control, uint key, uint x, uint y,uint mask)
{
  //code here:)
  //mprint(wxT("draw1_EvKeyboardRelease\n"));
  
  switch(lab)
  {
  case 1:
  case 3: 
  if(key == '1')
  {
    p_BT1=1; 
  }
  
  if(key == '2')
  {
    p_BT2=1; 
  }
  
  if(key == '3')
  {
    p_BT3=1; 
  }
  
  if(key == '4')
  {
    p_BT4=1; 
  }
  break;
  case 4: 
  case 2:
  if((key == '1')||(key == '4')||(key == '7')||(key == '*'))
  {
    p_CL1=0; 
  }
  if((key == '2')||(key == '5')||(key == '8')||(key == '0'))
  {
    p_CL2=0; 
  }
  if((key == '3')||(key == '6')||(key == '9')||(key == '#'))
  {
    p_CL3=0; 
  }
  break;
  }

};

void
CPWindow1::_EvOnCreate(CControl * control)
{
  FILE *fin;


  char line[256];
  char fname[1024];

  char *it;
  char *shape;
  char *coords;
  char *name;
  char *value;

  char home[1024];
  
  int x1,y1,x2,y2,r;
  
  int i;

  
  inputc=0; 
  outputc=0;
  picrun=1;
  picpwr=1;
  picrst=0;
  
  board_family[0]=P16;
  board_family[1]=P16;
  board_family[2]=P16;
  board_family[3]=P16;

  board_proc[0]=P16F628A;
  board_proc[1]=P16F628A;
  board_proc[2]=P16F877A;
  board_proc[3]=P16F877A;

  PATH=wxGetCwd(); 

  if(!share[0])
  {
#ifndef _WIN_
    strcpy(share,_SHARE_);
#else
    strcpy(share,(char*)wxGetCwd().char_str());
    strcat(share,"/");
    strcat(share,_SHARE_);
#endif
  }

if(!create)
{  
  Window2.html1.SetLoadFile(String::FromAscii(share)+wxT("doc/HELP.html"));
  buzz.Create(String::FromAscii(share)+wxT("buzzer.wav"));

#ifdef _WIN_
 Window3.combo1.SetItems(wxT("COM1,COM2,COM3,COM4,COM5,COM6,COM7,COM8,COM9,COM10,"));
 Window3.combo2.SetItems(wxT("COM1,COM2,COM3,COM4,COM5,COM6,COM7,COM8,COM9,COM10,"));
#else
 Window3.combo1.SetItems(wxT("/dev/ttyS0,/dev/ttyS1,/dev/ttyS2,/dev/ttyS3,/dev/tnt0,/dev/tnt1,/dev/tnt2,/dev/tnt3,/dev/tnt4,/dev/tnt5,"));
 Window3.combo2.SetItems(wxT("/dev/ttyS0,/dev/ttyS1,/dev/ttyS2,/dev/ttyS3,/dev/tnt0,/dev/tnt1,/dev/tnt2,/dev/tnt3,/dev/tnt4,/dev/tnt5,"));
#endif

}
create++;

//load options
  

  wxStandardPathsBase& stdp = wxStandardPaths::Get();
  strcpy(home,(char*)stdp.GetUserDataDir().char_str());

  sprintf(fname,"%s/picsimlab.ini",home);

  fin=fopen(fname,"r");
  
  
   SERIALDEVICE[0]=0;
   PROGDEVICE[0]=0;
  if(fin)
  {
    while(fgets(line,256,fin))
    {
      name=strtok(line,"= ");
      strtok(NULL," ");
      value=strtok(NULL,"\"");
      if((name == NULL)||(value==NULL))continue;
#ifndef _WIN_
      if(!strcmp("lser",name))strcpy(SERIALDEVICE,value);
      if(!strcmp("lprog",name))strcpy(PROGDEVICE,value);
#else
      if(!strcmp("wser",name))strcpy(SERIALDEVICE,value);
      if(!strcmp("wprog",name))strcpy(PROGDEVICE,value);
#endif
      
      if(!strcmp(name,"lab"))
      {
        sscanf(value,"%i",&i);
        combo2.SetText(itoa(i));
        lab=i;
        lab_=i; 
        switch(lab)
        {
          case 1:
          case 2: 
            //family=P16;
            //proc=P16F628A;
            //combo3.SetText(wxT("PIC16F628A"));
            combo3.SetItems(wxT("PIC16F628A,PIC16F648A,PIC16F648AICD,"));
          break;
          case 3:
            //family=P16;
            //proc=P16F877A;
            //combo3.SetText(wxT("PIC16F877A"));
            combo3.SetItems(wxT("PIC16F877A,PIC16F777,PIC18F452,PIC18F4620,PIC18F4550,"));
          break;
  	  case 4: 
            //family=P18;
            //proc=P18F452;
            //combo3.SetText(wxT("PIC18F452"));
            combo3.SetItems(wxT("PIC16F877A,PIC16F777,PIC18F452,PIC18F4620,PIC18F4550,"));
          break;
          default:
            Message(wxT("Invalid Board! Using Default."));
            lab=1;//default  
            lab_=1;//default  
            combo2.SetText(wxT("1"));
            combo3.SetItems(wxT("PIC16F628A,PIC16F648A,PIC16F648AICD,"));
            //exit(-1);
          break;
        } 
      }
      if(!strcmp(name,"clock"))
      {
        sscanf(value,"%i",&i);
        combo1.SetText(itoa(i)); 
        combo1_EvOnComboChange(control);
      }

      if(!strcmp(name,"lpath"))
      {
         PATH=String(value,wxConvUTF8);
      }
      
      if(!strcmp(name,"lfile"))
      {
         FNAME=String(value,wxConvUTF8);
      }
      
      if(!strcmp(name,"jmp"))
      {
        for(i=0;i<10;i++)
        {
          if(value[i] == '0')      
            jmp[i]=0;
          else
            jmp[i]=1;
        } 
      }

      if(!strcmp(name,"dip"))
      {
        for(i=0;i<20;i++) 
        {   
          if(value[i] == '0')      
            dip[i]=0;
          else
            dip[i]=1;
        }
      }
      
      if(!strcmp(name,"bproc"))
      {
        for(i=0;i<4;i++) 
        {   
          value[(i*7)+6]=0; 
          sscanf(value+(i*7),"0x%04X",&board_proc[i]);
        }
      }
      
      if(!strcmp(name,"bfamily"))
      {
        for(i=0;i<4;i++) 
        {   
          value[(i*5)+4]=0; 
          sscanf(value+(i*5),"0x%02X",&board_family[i]);
        }
      }

    }
    fclose(fin);
  }
  else
  {
    printf("Error open config file!\n");

#ifndef _WIN_   
   strcpy(SERIALDEVICE,"/dev/tnt2");
   strcpy(PROGDEVICE,"/dev/tnt4");
#else
   strcpy(SERIALDEVICE,"com6");
   strcpy(PROGDEVICE,"com8");
#endif
  }
     
  family=board_family[lab-1];
  proc=board_proc[lab-1];
  combo3.SetText(String::FromAscii(getnamebyproc(proc,fname)));
  
  filedialog1.SetDir(PATH);

//load maps  
  sprintf(fname,"%sinput%d.map",share,lab);
  fin=fopen(fname,"r");

  if(fin)
  {
    while(fgets(line,256,fin))
    {
      it=strtok(line,"< =\"");
      if(!strcmp("img",it))
      {
        do
        { 
          name=strtok(NULL,"< =\"");
          value=strtok(NULL,"< =\"");

          if(!strcmp("width",name))
          {
            sscanf(value,"%i",&x1);
            plWidth=x1;
	    draw1.SetWidth(x1*scale);
	    Window1.SetWidth(185+x1*scale);
          }
          
 	  if(!strcmp("height",name))
          {
            sscanf(value,"%i",&y1);
            plHeight=y1;
	    draw1.SetHeight(y1*scale);
#ifdef _WIN_
	    Window1.SetHeight(75+y1*scale);
#else
	    Window1.SetHeight(55+y1*scale);
#endif
          }

        }
	while(value != NULL); 
       
//        printf("%s %s %s\n",name,shape,coords);

      }
      else if(!strcmp("area",it))
      {
        strtok(NULL,"< =\"");
        shape=strtok(NULL,"< =\"");
        strtok(NULL,"< =\"");
        coords=strtok(NULL,"< =\"");
        strtok(NULL,"< =\"");
        name=strtok(NULL,"< =\"");
        
//        printf("%s %s %s\n",name,shape,coords);
       
//        if(strcmp("rect",shape)== 0)
//        {
          sscanf(coords,"%i,%i,%i,%i\n",&x1,&y1,&x2,&y2);
//          printf("rect=%i,%i,%i,%i\n",x1,y1,x2,y2);

          input[inputc].x1=x1; 
          input[inputc].y1=y1; 
          input[inputc].x2=x2; 
          input[inputc].y2=y2;
          strcpy(input[inputc].name,name); 
          input[inputc].id=get_in_id(input[inputc].name);
          inputc++;
//        }
//        else 
//        {
//          sscanf(coords,"%i,%i,%i\n",&x1,&y1,&r);
//          printf("circle=%i,%i,%i\n",x1,y1,r);
//        }
      }
    } 
    fclose(fin);
  }
  else
  {
    //Message(wxT("Error open input.map")); Not use this in create!!
    printf("Error open input.map!\n");
  }
 
 
  sprintf(fname,"%soutput%d.map",share,lab);
  fin=fopen(fname,"r");

  if(fin)
  {
    while(fgets(line,256,fin))
    {
      it=strtok(line,"< =\"");
      if(!strcmp("area",it))
      {
        strtok(NULL,"< =\"");
        shape=strtok(NULL,"< =\"");
        strtok(NULL,"< =\"");
        coords=strtok(NULL,"< =\"");
        strtok(NULL,"< =\"");
        name=strtok(NULL,"< =\"");
        
//        printf("%s %s %s\n",name,shape,coords);
        
	if(!strcmp("rect",shape))
        {
          sscanf(coords,"%i,%i,%i,%i\n",&x1,&y1,&x2,&y2);
//          printf("rect=%i,%i,%i,%i\n",x1,y1,x2,y2);
          
          output[outputc].x1=x1; 
          output[outputc].y1=y1; 
          output[outputc].x2=x2; 
          output[outputc].y2=y2;
          output[outputc].r=0;
//          output[outputc].lval=-1;
          strcpy(output[outputc].name,name); 
          output[outputc].id=get_out_id(output[outputc].name);
          outputc++;
        }
        else 
        {
          sscanf(coords,"%i,%i,%i\n",&x1,&y1,&r);
//          printf("circle=%i,%i,%i\n",x1,y1,r);
          
          output[outputc].x1=x1; 
          output[outputc].y1=y1; 
          output[outputc].r=r; 
//          output[outputc].lval=-1;
          strcpy(output[outputc].name,name); 
          output[outputc].id=get_out_id(output[outputc].name);
          outputc++;
        }
      }
    } 
  
    fclose(fin);
  }
  else
  {
    //Message(wxT("Error open output.map")); not use this in create!!!
    printf("Error open output.map!\n");
  }
  

  sprintf(fname,"%spicsimlab%d.png",share,lab);
  //fin=fopen(fname,"r");

/*
  draw1.Canvas.Init();
  draw1.Canvas.Rectangle(1,0,0,draw1.GetWidth(),draw1.GetHeight());;
  draw1.Canvas.End();
*/  

  draw1.SetImgFileName(String(fname,wxConvUTF8),scale,scale);

  //picrun=
  pic_set_serial(&pic,SERIALDEVICE,0,0,0);


  sprintf(fname,"%s/mdump_%02i.hex",home,lab);
 
  pic_init(&pic,family,proc,fname,1,NSTEP*NSTEPKF);


  lcd_rst(&lcd);
          switch(lab)
          {
            case 2: 
	      mi2c_init(&mi2c,512);
	      rtc_init(&rtc);
              break;
            case 1:
            case 3: 
	      mi2c_init(&mi2c,4);
              break;
            case 4:
	      mi2c_init(&mi2c,4);
	      rtc2_init(&rtc2);
              break;  
          };
      
  p_BT1=1; 
  p_BT2=1; 
  p_BT3=1; 
  p_BT4=1;
  p_BT5=1;
  p_BT6=1;
  p_BT7=1;
 

  switch(lab)
  { 
   case 1:
    pic_set_pin(&pic,18,p_BT1); 
    pic_set_pin(&pic,1,p_BT2); 
    pic_set_pin(&pic,2,p_BT3); 
    pic_set_pin(&pic,3,p_BT4); 
    
    gauge1.SetVisible(0);
    gauge2.SetVisible(0);
    scroll1.SetVisible(0);
    scroll2.SetVisible(0);
    label3.SetVisible(0);
    label4.SetVisible(0);
    label5.SetVisible(0);
    label6.SetVisible(0);
    label8.SetVisible(0);

    statusbar1.SetField(2,wxT(""));
    break;
  case 2:
    p_CL1=0; 
    p_CL2=0; 
    p_CL3=0; 
    pic_set_pin(&pic,13,p_CL1); 
    pic_set_pin(&pic,12,p_CL2); 
    pic_set_pin(&pic,11,p_CL3); 

    gauge1.SetVisible(0);
    gauge2.SetVisible(0);
    scroll1.SetVisible(0);
    scroll2.SetVisible(0);
    label3.SetVisible(0);
    label4.SetVisible(0);
    label5.SetVisible(0);
    label6.SetVisible(0);
    label8.SetVisible(0);

#ifndef _WIN_
    if(pic.serialfd > 0)
#else
    if(pic.serialfd != INVALID_HANDLE_VALUE)
#endif
      statusbar1.SetField(2,wxT("Serial Port: ")+String::FromAscii(SERIALDEVICE)+wxT(":")+itoa(pic.serialbaud)+wxT("(")+String().Format("%4.1f",fabs((100.0*pic.serialexbaud-100.0*pic.serialbaud)/pic.serialexbaud))+wxT("%)"));
    else  
      statusbar1.SetField(2,wxT("Serial Port: ")+String::FromAscii(SERIALDEVICE)+wxT(" (ERROR)"));
    break; 
  case 3: 
    pic_set_pin(&pic,33,p_BT1); 
    pic_set_pin(&pic,34,p_BT2); 
    pic_set_pin(&pic,35,p_BT3); 
    pic_set_pin(&pic,36,p_BT4); 
  
    gauge1.SetVisible(1);
    gauge2.SetVisible(1);
    scroll1.SetVisible(1);
    scroll2.SetVisible(0);
    label3.SetVisible(1);
    label4.SetVisible(1);
    label5.SetVisible(1);
    label6.SetVisible(0);
    label8.SetVisible(1);
#ifndef _WIN_
    if(pic.serialfd > 0)
#else
    if(pic.serialfd != INVALID_HANDLE_VALUE)
#endif
      statusbar1.SetField(2,wxT("Serial Port: ")+String::FromAscii(SERIALDEVICE)+wxT(":")+itoa(pic.serialbaud)+wxT("(")+String().Format("%4.1f",fabs((100.0*pic.serialexbaud-100.0*pic.serialbaud)/pic.serialexbaud))+wxT("%)"));
    else
      statusbar1.SetField(2,wxT("Serial Port: ")+String::FromAscii(SERIALDEVICE)+wxT(" (ERROR)"));
    break;
  case 4: 
    pic_set_pin(&pic,33,p_BT1); 
    pic_set_pin(&pic,34,p_BT2); 
    pic_set_pin(&pic,35,p_BT3); 
    pic_set_pin(&pic,36,p_BT4); 
    pic_set_pin(&pic,37,p_BT5); 
    pic_set_pin(&pic,38,p_BT6); 
    pic_set_pin(&pic,7,p_BT7); 
    
    p_CL1=0; 
    p_CL2=0; 
    p_CL3=0; 
    pic_set_pin(&pic,33,p_CL1); 
    pic_set_pin(&pic,34,p_CL2); 
    pic_set_pin(&pic,35,p_CL3); 
  
    gauge1.SetVisible(1);
    gauge2.SetVisible(1);
    scroll1.SetVisible(1);
    scroll2.SetVisible(1);
    label3.SetVisible(1);
    label4.SetVisible(1);
    label5.SetVisible(1);
    label6.SetVisible(1);
    label8.SetVisible(1);
    
#ifndef _WIN_
    if(pic.serialfd > 0)
#else
    if(pic.serialfd != INVALID_HANDLE_VALUE)
#endif
      statusbar1.SetField(2,wxT("Serial Port: ")+String::FromAscii(SERIALDEVICE)+wxT(":")+itoa(pic.serialbaud)+wxT("(")+String().Format("%4.1f",fabs((100.0*pic.serialexbaud-100.0*pic.serialbaud)/pic.serialexbaud))+wxT("%)"));
    else
      statusbar1.SetField(2,wxT("Serial Port: ")+String::FromAscii(SERIALDEVICE)+wxT(" (ERROR)"));
    break;
  }
  

  if(prog_init() >= 0 ) 
     statusbar1.SetField(1,wxT("Programmer Port: ")+String::FromAscii(PROGDEVICE));
  else
     statusbar1.SetField(1,wxT("Programmer Port: ")+String::FromAscii(PROGDEVICE)+wxT(" (ERROR)"));
 
  statusbar1.SetField(0,wxT("Running..."));

  Application->ProcessEvents();


  timer1.SetRunState(1);
};

void
CPWindow1::combo1_EvOnComboChange(CControl * control)
{

  NSTEP= (int)(atof(combo1.GetText())*NSTEPKT); 
  
  NSTEPJ=NSTEP/JUMP;

  pic.freq=NSTEP*NSTEPKF;
         

  Application->ProcessEvents();
};





void
CPWindow1::combo2_EvOnComboChange(CControl * control)
{

  lab_= lab;
  lab= (int)(atof(combo2.GetText()));
 /*
  switch(lab)
  {
  case 1:
  case 2:
   family=P16;
   proc=P16F628A;
   break;
  case 3:
   family=P16;
   proc=P16F877A;
   break;
  case 4: 
   family=P18;
   proc=P18F452;
   break;
  }
*/
  _EvOnDestroy(control);
  _EvOnCreate(control);
  _EvOnShow(control);
};


void
CPWindow1::_EvOnDestroy(CControl * control)
{
  //code here:)
  //mprint(wxT("_EvOnDestroy\n"));
  char home[256];
  char fname[256];
  FILE * fout; 
  DIR  *dp;
  int i; 
  
  timer1.SetRunState(0);
  
#ifndef _WIN_
  usleep(100);
#else
  Sleep(1);
#endif
 

//write options
  wxTheApp->SetAppName(_T("picsimlab"));
  wxStandardPathsBase& stdp = wxStandardPaths::Get();
  strcpy(home,(char*)stdp.GetUserDataDir().char_str());
 
   dp = opendir (home);

   if(dp)
   {
     closedir(dp);
   }
   else
   {
     remove(home);
#ifndef _WIN_
     mkdir(home, S_IWUSR| S_IRUSR | S_IXUSR | S_IRGRP | S_IROTH ); 
#else     
     mkdir(home);
#endif 
   }

  sprintf(fname,"%s/picsimlab.ini",home);
  
  fout=fopen(fname,"w");

  if(fout)
  {
    fprintf(fout,"lab     = \"%i\"\n",lab);
    fprintf(fout,"clock   = \"%i\"\n",atoi(combo1.GetText()));
    fprintf(fout,"jmp     = \"");
    for(i=0;i<10;i++)
      fprintf(fout,"%i",jmp[i]);
    fprintf(fout,"\"\n");
    fprintf(fout,"dip     = \"");
    for(i=0;i<20;i++)
      fprintf(fout,"%i",dip[i]);
    fprintf(fout,"\"\n");
#ifndef _WIN_
    fprintf(fout,"lser    = \"%s\"\n",SERIALDEVICE);
    fprintf(fout,"lprog   = \"%s\"\n",PROGDEVICE);
#else
    fprintf(fout,"wser    = \"%s\"\n",SERIALDEVICE);
    fprintf(fout,"wprog   = \"%s\"\n",PROGDEVICE);
#endif
    fprintf(fout,"lpath   = \"%s\"\n",(char *) PATH.char_str());
    fprintf(fout,"lfile   = \"%s\"\n",(char *) FNAME.char_str());
    fprintf(fout,"bproc   = \"");
    for(i=0;i<4;i++)
      fprintf(fout,"0x%04X,",board_proc[i]);
    fprintf(fout,"\"\n");
    fprintf(fout,"bfamily = \"");
    for(i=0;i<4;i++)
      fprintf(fout,"0x%02X,",board_family[i]);
    fprintf(fout,"\"\n");
    fclose(fout);
  }
  else
  {
    Message(wxT("Error Writing options!"));
  }
  
//write memory


  sprintf(fname,"%s/mdump_%02i.hex",home,lab_);
  
  switch(family)
  {
    case P16:
      write_ihx(&pic,fname);
      break;
    case P18:
      write_ihx18(&pic,fname);
      break;
  }

  pic_end(&pic);
  mi2c_end(&mi2c);
  rtc_end(&rtc);
  rtc2_end(&rtc2);
  prog_end();

};


void
CPWindow1::menu1_File_LoadHex_EvMenuActive(CControl * control)
{
  int pa;

        pa=picpwr; 
        picpwr=0;
        if(filedialog1.Run())
        {
  	  pic_end(&pic);
  	  mi2c_end(&mi2c);
  	  rtc_end(&rtc);
  	  rtc2_end(&rtc2);
          pic_set_serial(&pic,SERIALDEVICE,0,0,0);
          picrun=pic_init(&pic,family,proc,filedialog1.GetFileName().char_str(),1,NSTEP*NSTEPKF);
          lcd_rst(&lcd);
          pic.config[0] |= 0x0800; //disable DEBUG
          switch(lab)
          {
            case 2: 
	      mi2c_init(&mi2c,512);
	      rtc_init(&rtc);
              break;
            case 1:
            case 3: 
	      mi2c_init(&mi2c,4);
 	      break;
            case 4: 
	      mi2c_init(&mi2c,4);
	      rtc2_init(&rtc2);
              break;
          };
 
          if(picrun) 
            Window1.SetTitle(wxT("PicsimLab - ")+basename(filedialog1.GetFileName()));          
          else
            Window1.SetTitle(wxT("PicsimLab"));
          
          p_BT1=1; 
          p_BT2=1; 
          p_BT3=1; 
          p_BT4=1; 
          p_BT5=1; 
          p_BT6=1; 
          p_BT7=1; 
          
          switch(lab)
          {
           case 1:
            pic_set_pin(&pic,18,p_BT1); 
            pic_set_pin(&pic,1,p_BT2); 
            pic_set_pin(&pic,2,p_BT3); 
            pic_set_pin(&pic,3,p_BT4); 
            break;
           case 2:
            p_CL1=0; 
            p_CL2=0; 
            p_CL3=0; 
            pic_set_pin(&pic,13,p_CL1); 
            pic_set_pin(&pic,12,p_CL2); 
            pic_set_pin(&pic,11,p_CL3); 
            break;
           case 3: 
            pic_set_pin(&pic,33,p_BT1); 
            pic_set_pin(&pic,34,p_BT2); 
            pic_set_pin(&pic,35,p_BT3); 
            pic_set_pin(&pic,36,p_BT4); 
            break;
           case 4: 
            pic_set_pin(&pic,33,p_BT1); 
            pic_set_pin(&pic,34,p_BT2); 
            pic_set_pin(&pic,35,p_BT3); 
            pic_set_pin(&pic,36,p_BT4); 
            pic_set_pin(&pic,37,p_BT5); 
            pic_set_pin(&pic,38,p_BT6); 
            pic_set_pin(&pic,7,p_BT7); 
            p_CL1=0; 
            p_CL2=0; 
            p_CL3=0; 
            pic_set_pin(&pic,33,p_CL1); 
            pic_set_pin(&pic,34,p_CL2); 
            pic_set_pin(&pic,35,p_CL3); 
            break;
          } 
        
          PATH=filedialog1.GetDir();
          FNAME=filedialog1.GetFileName();
        }
        picpwr=pa;
};

void
CPWindow1::menu1_File_Exit_EvMenuActive(CControl * control)
{
  WDestroy();
};

void
CPWindow1::menu1_Help_Contents_EvMenuActive(CControl * control)
{
  Window2.Show();
};


void
CPWindow1::menu1_Help_About_EvMenuActive(CControl * control)
{
  Message(wxT("Developed by L.C. Gamboa\n <lcgamboa@yahoo.com>\n Version: ")+String(wxT(_VERSION_)));
};

void
CPWindow1::menu1_Help_Examples_EvMenuActive(CControl * control)
{
  int pa;

        pa=picpwr; 
        picpwr=0;
        
        filedialog1.SetDir(String::FromAscii(share)+wxT("/examples/"));

        if(filedialog1.Run())
        {
  	  pic_end(&pic);
  	  mi2c_end(&mi2c);
  	  rtc_end(&rtc);
  	  rtc2_end(&rtc2);
          pic_set_serial(&pic,SERIALDEVICE,0,0,0);
          picrun=pic_init(&pic,family,proc,filedialog1.GetFileName().char_str(),1,NSTEP*NSTEPKF);
          lcd_rst(&lcd);
          pic.config[0] |= 0x0800; //disable DEBUG
          switch(lab)
          {
            case 2: 
	      mi2c_init(&mi2c,512);
	      rtc_init(&rtc);
              break;
            case 1:
            case 3: 
	      mi2c_init(&mi2c,4);
	      break; 	
            case 4: 
	      mi2c_init(&mi2c,4);
	      rtc2_init(&rtc2);
              break;
          };
 
          if(picrun) 
            Window1.SetTitle(wxT("PicsimLab - ")+basename(filedialog1.GetFileName()));          
          else
            Window1.SetTitle(wxT("PicsimLab"));
          
          p_BT1=1; 
          p_BT2=1; 
          p_BT3=1; 
          p_BT4=1; 
          p_BT5=1; 
          p_BT6=1; 
          p_BT7=1; 
          
          switch(lab)
          {
           case 1:
            pic_set_pin(&pic,18,p_BT1); 
            pic_set_pin(&pic,1,p_BT2); 
            pic_set_pin(&pic,2,p_BT3); 
            pic_set_pin(&pic,3,p_BT4); 
            break;
           case 2:
            p_CL1=0; 
            p_CL2=0; 
            p_CL3=0; 
            pic_set_pin(&pic,13,p_CL1); 
            pic_set_pin(&pic,12,p_CL2); 
            pic_set_pin(&pic,11,p_CL3); 
            break;
           case 3: 
            pic_set_pin(&pic,33,p_BT1); 
            pic_set_pin(&pic,34,p_BT2); 
            pic_set_pin(&pic,35,p_BT3); 
            pic_set_pin(&pic,36,p_BT4); 
            break;
           case 4: 
            pic_set_pin(&pic,33,p_BT1); 
            pic_set_pin(&pic,34,p_BT2); 
            pic_set_pin(&pic,35,p_BT3); 
            pic_set_pin(&pic,36,p_BT4); 
            pic_set_pin(&pic,37,p_BT5); 
            pic_set_pin(&pic,38,p_BT6); 
            pic_set_pin(&pic,7,p_BT7); 
            p_CL1=0; 
            p_CL2=0; 
            p_CL3=0; 
            pic_set_pin(&pic,33,p_CL1); 
            pic_set_pin(&pic,34,p_CL2); 
            pic_set_pin(&pic,35,p_CL3); 
            break;
          } 
        }
        filedialog1.SetDir(PATH);
        picpwr=pa;
};


//Resize
void
CPWindow1::_EvOnShow(CControl * control)
{
 double scalex,scaley;   
 char fname[1024];

if(timer1.GetRunState())
{
  scalex=((Window1.GetWidth()-185)*1.0)/plWidth;
#ifdef _WIN_
  scaley=((Window1.GetHeight()-75)*1.0)/plHeight;
#else
  scaley=((Window1.GetHeight()-55)*1.0)/plHeight;
#endif

  if(scalex < scaley)
    scale=scalex;
  else
    scale=scaley;


  draw1.SetWidth(plWidth*scale);
  draw1.SetHeight(plHeight*scale);
  
  sprintf(fname,"%spicsimlab%d.png",share,lab);

  lcd.update=1;

   //fin=fopen(fname,"r");

/*
  draw1.Canvas.Init();
  draw1.Canvas.Rectangle(1,0,0,draw1.GetWidth(),draw1.GetHeight());;
  draw1.Canvas.End();
*/
  draw1.SetImgFileName(String(fname,wxConvUTF8),scale,scale);
};

};


void
CPWindow1::menu1_File_Configure_EvMenuActive(CControl * control)
{
  Window3.ShowExclusive();
};


void
CPWindow1::combo3_EvOnComboChange(CControl * control)
{

   board_proc[lab-1]=getprocbyname((char *)combo3.GetText().char_str());
   board_family[lab-1]=getfprocbyname((char *)combo3.GetText().char_str());
  
  _EvOnDestroy(control);
  _EvOnCreate(control);
  _EvOnShow(control);
};


void
CPWindow1::menu1_File_ReloadLast_EvMenuActive(CControl * control)
{
  int pa;

        pa=picpwr; 
        picpwr=0;

        //if(filedialog1.Run())
        //{
  	  pic_end(&pic);
  	  mi2c_end(&mi2c);
  	  rtc_end(&rtc);
  	  rtc2_end(&rtc2);
          pic_set_serial(&pic,SERIALDEVICE,0,0,0);
          picrun=pic_init(&pic,family,proc,FNAME.char_str(),1,NSTEP*NSTEPKF);
          lcd_rst(&lcd);
          pic.config[0] |= 0x0800; //disable DEBUG
          switch(lab)
          {
            case 2: 
	      mi2c_init(&mi2c,512);
	      rtc_init(&rtc);
              break;
            case 1:
            case 3: 
	      mi2c_init(&mi2c,4);
 	      break;
            case 4: 
	      mi2c_init(&mi2c,4);
	      rtc2_init(&rtc2);
              break;
          };
 
          if(picrun) 
            Window1.SetTitle(wxT("PicsimLab - ")+basename(filedialog1.GetFileName()));          
          else
            Window1.SetTitle(wxT("PicsimLab"));
          
          p_BT1=1; 
          p_BT2=1; 
          p_BT3=1; 
          p_BT4=1; 
          p_BT5=1; 
          p_BT6=1; 
          p_BT7=1; 
          
          switch(lab)
          {
           case 1:
            pic_set_pin(&pic,18,p_BT1); 
            pic_set_pin(&pic,1,p_BT2); 
            pic_set_pin(&pic,2,p_BT3); 
            pic_set_pin(&pic,3,p_BT4); 
            break;
           case 2:
            p_CL1=0; 
            p_CL2=0; 
            p_CL3=0; 
            pic_set_pin(&pic,13,p_CL1); 
            pic_set_pin(&pic,12,p_CL2); 
            pic_set_pin(&pic,11,p_CL3); 
            break;
           case 3: 
            pic_set_pin(&pic,33,p_BT1); 
            pic_set_pin(&pic,34,p_BT2); 
            pic_set_pin(&pic,35,p_BT3); 
            pic_set_pin(&pic,36,p_BT4); 
            break;
           case 4: 
            pic_set_pin(&pic,33,p_BT1); 
            pic_set_pin(&pic,34,p_BT2); 
            pic_set_pin(&pic,35,p_BT3); 
            pic_set_pin(&pic,36,p_BT4); 
            pic_set_pin(&pic,37,p_BT5); 
            pic_set_pin(&pic,38,p_BT6); 
            pic_set_pin(&pic,7,p_BT7); 
            p_CL1=0; 
            p_CL2=0; 
            p_CL3=0; 
            pic_set_pin(&pic,33,p_CL1); 
            pic_set_pin(&pic,34,p_CL2); 
            pic_set_pin(&pic,35,p_CL3); 
            break;
          } 
        
        //}
        picpwr=pa;
};



















