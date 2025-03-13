#ifndef __GAS_EQ_H__
#define __GAS_EQ_H__

struct substance_state {
  char *substance;
  float M_bar;
  float R;
  float R_bar;
  float temperature;
  float cp;
  float cv;
  float k;
  float h0;
  float s0;
  float g0;
  float Pr;
};

struct substance_state * get_substance_state(char* substance, float temperature);

#endif
