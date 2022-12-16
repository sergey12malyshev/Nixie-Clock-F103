#include "main.h"
#include "smooth.h"

static void output(uint8_t temper_cnt)
{
  const uint8_t period = 10;
  uint8_t time_cnt = 0;

  if (temper_cnt <= period)
  {
    time_cnt = period - temper_cnt;
  }

  for(uint8_t i = 0; i <= temper_cnt; i++) temper_out();
  for(uint8_t i = 0; i <= time_cnt; i++) time_out();
}

void smooth_transition_time(void) // выполняеться за 280 мс
{
    output(1);
    output(1);
    output(2);
    output(2);
    output(3);
    output(3);
    output(4);
    output(4);
    output(5);
    output(5);
    output(6);
    output(6);
    output(7);
    output(7);
    output(8);
    output(8);
    output(9);
    output(9);
}

void smooth_transition_temp(void)
{
    output(9);
    output(9);
    output(8);
    output(8);
    output(7);
    output(7);
    output(6);
    output(6);
    output(5);
    output(5);
    output(4);
    output(4);
    output(3);
    output(3);
    output(2);
    output(2);
    output(1);
    output(1);
}
