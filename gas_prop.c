#include <stdio.h>

#include <gas_eq.h>

int main(int argc, char *argv[]) {

  // Get substance and convert to upper case
  char *substance = argv[1];
  
  // Get input temperature
  float temperature;
  sscanf(argv[2], "%f", &temperature); 

  struct substance_state *ss = get_substance_state(substance, temperature);

  printf("\nSubstance\t%s\nTemperature\t%.2f K\ncp0\t\t%.3f kJ/(kmol K)\nh0\t\t%.1f kJ/kmol\ns0\t\t%.3f kJ/(kmol K)\ng0\t\t%.1f kJ/kmol\nPr\t\t%E\n\n", ss->substance, ss->temperature, ss->cp0, ss->h0, ss->s0, ss->g0, ss->Pr);

  return 0;
}

