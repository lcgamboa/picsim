#ifndef CPWINDOW1 
#define CPWINDOW1

#include<lxrad/lxrad.h>

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
};

extern CPWindow1 Window1 ;

#endif /*#CPWINDOW1*/

