#include <stdio.h>

#include <gas_eq.h>

int main(int argc, char *argv[]) {

  // Get substance and convert to upper case
  char *substance = argv[1];
  
  // Get input temperature
  float temperature;
  sscanf(argv[2], "%f", &temperature); 

  struct substance_state *ss = get_substance_state(substance, temperature);

  printf("\nSubstance\t\t%s\n", ss->substance);
  printf("Molecular Weight\t%.4f kg/kmol\n", ss->M_bar);
  printf("Gas Constant\t\t%f kJ/(kg K)\n\n", ss->R);

  printf("Temperature\t\t%.2f K\n", ss->temperature);
  printf("cp\t\t\t%.3f kJ/(kg K)\n", ss->cp);
  printf("cv\t\t\t%.3f kJ/(kg K)\n", ss->cv);
  printf("k\t\t\t%.3f\n", ss->k);
  printf("h0\t\t\t%.1f kJ/kg\n", ss->h0);
  printf("s0\t\t\t%.3f kJ/(kg K)\n", ss->s0);
  printf("g0\t\t\t%.1f kJ/kg\n", ss->g0);
  printf("Pr\t\t\t%E\n\n", ss->Pr);

  return 0;
}

