#include<picsim/picsim.h>
#include<stdio.h>

int main()
{
  int i;
  unsigned char val;
  //microcontroller object
  _pic pic1; 

  //set serial port
  pic_set_serial(&pic1,0, "/dev/tnt2",0,0,0);
  //pic_set_serial(&pic1,"COM2",0,0,0);

  //initialization and program loading
  pic_init(&pic1, getprocbyname("PIC16F628A"), "../../../examples/shift/shift.hex", 1, 4e6);

  //enable print messages of internal instruction execution (slow down the simulation speed) 
  pic1.print=1;

  //loop 
  for(i=0;i<1000;i++)
  {
      //execute one instruction cycle	   
      pic_step(&pic1);
      //read digital pin 1
      val=pic_get_pin(&pic1, 1);
      //write digital pin 2
      pic_set_pin(&pic1, 2, val);
  }
 
  //free internal memory
  pic_end(&pic1);
} 
