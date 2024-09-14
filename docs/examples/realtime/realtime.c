
#include <picsim/picsim.h>
#include <stdio.h>
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>


#define FREQ 4000000L

static _pic pic1;

void timer_callback(int signum)
{
  unsigned char PORTB;
  static unsigned char PORTB_old;
  const unsigned int nsteps = 100e-3 / (4.0 / pic1.freq);
  for (int i = 0; i < nsteps; i++)
  {
    pic_step(&pic1);

    //READ pins
    // PORTB |= pic_get_pin(&pic1, 6);
    // use direct access instead pic_get_pin to speed up

    PORTB = 0;
    PORTB |= pic1.pins[6 - 1].value;       // RB0
    PORTB |= pic1.pins[7 - 1].value << 1;  // RB1
    PORTB |= pic1.pins[8 - 1].value << 2;  // RB2
    PORTB |= pic1.pins[9 - 1].value << 3;  // RB3
    PORTB |= pic1.pins[10 - 1].value << 4; // RB4
    PORTB |= pic1.pins[11 - 1].value << 5; // RB5
    PORTB |= pic1.pins[12 - 1].value << 6; // RB6
    PORTB |= pic1.pins[13 - 1].value << 7; // RB7

    if (PORTB != PORTB_old)
    {
      PORTB_old = PORTB;
      printf("PORTB =0x%02X\n", PORTB);
    }
  }
}

void ctrlc_callback(int signum)
{
  printf("end\n");
  pic_end(&pic1);
  exit(0);
}

int main()
{

  pic_init(&pic1, getprocbyname("PIC16F628A"),  "../../../examples/shift/shift.hex", 1, FREQ);

  struct itimerval new_timer;
  struct itimerval old_timer;

  new_timer.it_value.tv_sec = 0;
  new_timer.it_value.tv_usec = 100 * 1000; //100ms
  new_timer.it_interval.tv_sec = 0;
  new_timer.it_interval.tv_usec = 100 * 1000; //100ms

  setitimer(ITIMER_REAL, &new_timer, &old_timer);
  signal(SIGALRM, timer_callback);
  signal(SIGINT, ctrlc_callback);

  // Waitting forever
  while (sleep(10))
    ;
}
