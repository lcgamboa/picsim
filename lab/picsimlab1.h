#ifndef CPWINDOW1 
#define CPWINDOW1

#include<lxrad/lxrad.h>
#include "../picsim.h"
#include "lcd.h"
#include "mi2c.h"
#include "rtc.h"
#include "rtc2.h"
#include "id.h"

#include<wx/sound.h>
#include "wx/stdpaths.h"

#define JUMP 100 //sampled IO refresh

typedef struct
{
unsigned int x1;
unsigned int x2;
unsigned int y1;
unsigned int y2;
char name[10];
unsigned short id;
}input_t;

typedef struct
{
unsigned int x1;
unsigned int x2;
unsigned int y1;
unsigned int y2;
unsigned int r;
char name[10];
unsigned short id;
//int lval;
}output_t;

class CPWindow1:public CPWindow
{
  public:
  /*#Controls*/
  CTimer timer1;
  CFileDialog filedialog1;
  CDraw draw1;
  CCombo combo1;
  CLabel label1;
  CLabel label3;
  CCombo combo2;
  CScroll scroll1;
  CGauge gauge1;
  CGauge gauge2;
  CMenu menu1;
  CPMenu menu1_File;
  CPMenu menu1_Help;
  CItemMenu menu1_File_LoadHex;
  CItemMenu menu1_File_ReloadLast;
  CItemMenu menu1_File_Configure;
  CItemMenu menu1_File_Exit;
  CItemMenu menu1_Help_Contents;
  CItemMenu menu1_Help_Examples;
  CItemMenu menu1_Help_About;
  CStatusbar statusbar1;
  CLabel label4;
  CLabel label5;
  CLabel label2;
  CScroll scroll2;
  CLabel label6;
  CLabel label7;
  CCombo combo3;
  /*#Events*/
  void _EvOnCreate(CControl * control);
  void _EvOnDestroy(CControl * control);
  void _EvOnShow(CControl * control);
  void timer1_EvOnTime(CControl * control);
  void draw1_EvMouseButtonPress(CControl * control, uint button, uint x, uint y,uint state);
  void draw1_EvMouseButtonRelease(CControl * control, uint button, uint x, uint y,uint state);
  void draw1_EvKeyboardPress(CControl * control, uint key, uint x, uint y,uint mask);
  void draw1_EvKeyboardRelease(CControl * control, uint key, uint x, uint y,uint mask);
  void combo1_EvOnComboChange(CControl * control);
  void combo2_EvOnComboChange(CControl * control);
  void menu1_File_LoadHex_EvMenuActive(CControl * control);
  void menu1_File_ReloadLast_EvMenuActive(CControl * control);
  void menu1_File_Configure_EvMenuActive(CControl * control);
  void menu1_File_Exit_EvMenuActive(CControl * control);
  void menu1_Help_Contents_EvMenuActive(CControl * control);
  void menu1_Help_Examples_EvMenuActive(CControl * control);
  void menu1_Help_About_EvMenuActive(CControl * control);
  void combo3_EvOnComboChange(CControl * control);

  /*#Others*/
  CPWindow1(void);
  void board_1(void);
  void board_2(void);
  void board_3(void);
  void board_4(void);
  private:



long int NSTEP;
long int NSTEPJ;

input_t  input[90];
output_t output[90];

int inputc;
int outputc;

int picrun;

int picpwr;

int picrst;

int jmp[10];
int dip[20];

int lab;
int lab_;
char family;
int proc;

int board_proc[4];
int board_family[4];

_pic pic;

unsigned int lm[50]; //luminosidade media
unsigned int lm1[50]; //luminosidade media display
unsigned int lm2[50]; //luminosidade media display
unsigned int lm3[50]; //luminosidade media display
unsigned int lm4[50]; //luminosidade media display


int p_BT1; 
int p_BT2; 
int p_BT3; 
int p_BT4; 
int p_BT5; 
int p_BT6; 
int p_BT7; 

int p_CL1; 
int p_CL2; 
int p_CL3; 

lcd_t lcd;

mi2c_t mi2c;
rtc_t rtc;
rtc2_t rtc2;

int lcde;

wxSound buzz;

char share[512];

float vp1in;
float vp2in;
float vp2[2];
float temp[2];
float ref;

int rpmstp;
int rpmc;

float over;
unsigned char clko;
unsigned char d;

String PATH;
String FNAME;

unsigned char sda,sck;

int plWidth;
int plHeight;
double scale;

int create;

};

extern CPWindow1 Window1 ;

#endif /*#CPWINDOW1*/

