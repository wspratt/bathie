#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <gas_eq.h>

// Universal gas constant
float R_bar = 8.31434E+00; // kJ / (kmol * K)

// Argon (Ar)
float AR_M = 3.9948E+01;
float AR_HI[] = { 2.5000000E+00, 0.0000000E+00, 0.0000000E+00, 0.0000000E+00, 0.0000000E+00, -7.4537500E+02, 4.3661076E+00 };
float AR_LO[] = { 2.5000000E+00, 0.0000000E+00, 0.0000000E+00, 0.0000000E+00, 0.0000000E+00, -7.4537500E+02, 4.3661076E+00 };

// Carbon Monoxide (CO)
float CO_M = 2.80106E+01;
float CO_HI[] = { 2.9511519E+00, 1.5525567E-03, -6.1911411E-07, 1.1350336E-10, -7.7882732E-15, -1.4231827E+04, 6.5314450E+00 };
float CO_LO[] = { 3.7871332E+00, -2.1709523E-03, 5.0757337E-06, -3.4737726E-09, 7.7216841E-13, -1.4363508E+04, 2.6335459E+00 };

// Carbon Dioxide (CO2)
float CO2_M = 4.40100E+01;
float CO2_HI[] = { 4.4129266E+00, 3.1922896E-03, -1.2978230E-06, 2.4147446E-10, -1.6742986E-14, -4.8944043E+04, -7.2875769E-01 };
float CO2_LO[] = { 2.1701000E+00, 1.0378115E-02, -1.0733938E-05, 6.3459175E-09, -1.6280701E-12, -4.8352602E+04, 1.0664388E+01 };

// Hydrogen (H2)
float H2_M = 2.0159E+00;
float H2_HI[] = { 3.0436897E+00, 6.1187110E-04, -7.3993551E-09, -2.0331907E-11, 2.4593791E-15, -8.5491002E+02, -1.6481339E+00 };
float H2_LO[] = { 2.8460849E+00, 4.1932116E-03, -9.6119332E-06, 9.5122662E-09, -3.3093421E-12, -9.6725372E+02, -1.4117850E+00 };

// Water (H2O)
float H2O_M = 1.80153E+01;
float H2O_HI[] = { 2.6707532E+00, 3.0317115E-03, -8.5351570E-07, 1.1790853E-10, -6.1973568E-15, -2.9888994E+04, 6.8838391E+00 };
float H2O_LO[] = { 4.1565016E+00, -1.7244334E-03, 5.6982316E-06, -4.593044E-09, 1.4233654E-12, -3.0288770E+04, -6.8616246E-01 };

// Nitrogen (N2)
float N2_M = 2.80134E+01;
float N2_HI[] = { 2.8545761E+00, 1.5976316E-03, -6.2566254E-07, 1.1315849E-10, -7.6897070E-15, -8.9017445E+02, 6.3902879E+00 };
float N2_LO[] = { 3.6916148E+00, -1.3332552E-03, 2.6503100E-06, -9.7688341E-10, -9.9772234E-14, -1.0628336E+03, 2.2874980E+00 };

// Oxygen (O2)
float O2_M = 3.19988E+01;
float O2_HI[] = { 3.5976129E+00, 7.8145603E-04, -2.2386670E-07, 4.2490159E-11, -3.3460204E-15, -1.1927918E+03, 3.7492659E+00 };
float O2_LO[] = { 3.7189946E+00, -2.5167288E-03, 8.5837353E-06, -8.2998716E-09, 2.7082180E-12, -1.0576706E+03, 3.9080704E+00 };


struct substance_state * get_substance_state(char *substance, float temperature) {

  for (int i = 0; i < strlen(substance); i++) 
    substance[i] = toupper(substance[i]);

  struct substance_state *ss;
  ss->substance = substance;
  ss->temperature = temperature;

  float *a_ptr;

  if (strcmp(substance, "AR") == 0) { // Argon (Ar)
    ss->M_bar = AR_M;
    if (temperature < 1000)
      a_ptr = AR_LO;
    else
      a_ptr = AR_HI;
  } else if (strcmp(substance, "CO") == 0) { // Carbon Monoxide (CO)
    ss->M_bar = CO_M;
    if (temperature < 1000)
      a_ptr = CO_LO;
    else
      a_ptr = CO_HI;
  } else if (strcmp(substance, "CO2") == 0) { // Carbon Dioxide (CO2)
    ss->M_bar = CO2_M;
    if (temperature < 1000) 
      a_ptr = CO2_LO;
    else
      a_ptr = CO2_HI;
  } else if (strcmp(substance, "H2") == 0) { // Hydrogen (H2)
    ss->M_bar = H2_M;
    if (temperature < 1000)
      a_ptr = H2_LO;
    else
      a_ptr = H2_HI;
  } else if (strcmp(substance, "H2O") == 0) { // Water (H2O)
    ss->M_bar = H2O_M;
    if (temperature < 1000)
      a_ptr = H2O_LO;
    else
      a_ptr = H2O_HI;
  } else if (strcmp(substance, "N2") == 0) { // Nitrogen (N2)
    ss->M_bar = N2_M;
    if (temperature < 1000)
      a_ptr = N2_LO;
    else
      a_ptr = N2_HI;
  } else if (strcmp(substance, "O2") == 0) { // Oxygen (O2)
    ss->M_bar = O2_M;
    if (temperature < 1000)
      a_ptr = O2_LO;
    else
      a_ptr = O2_HI;
  } else {
    printf("Substance %s not found!\n", substance);
    exit(1);
  }

  ss->R = R_bar / ss->M_bar;
  ss->cp = R_bar * (a_ptr[0] + a_ptr[1] * temperature + a_ptr[2] * pow(temperature, 2) + a_ptr[3] * pow(temperature, 3) + a_ptr[4] * pow(temperature, 4)) / ss->M_bar;
  ss->cv = ss->cp - ss->R;
  ss->k = ss->cp / ss->cv;
  ss->h0 = R_bar * temperature * (a_ptr[0] + a_ptr[1] * temperature / 2. + a_ptr[2] * pow(temperature, 2) / 3. + a_ptr[3] * pow(temperature, 3) / 4. + a_ptr[4] * pow(temperature, 4) / 5. + a_ptr[5] / temperature) / ss->M_bar;
  ss->s0 = R_bar * (a_ptr[0] * log(temperature) + a_ptr[1] * temperature + a_ptr[2] * pow(temperature, 2) / 2. + a_ptr[3]  * pow(temperature, 3) / 3. + a_ptr[4] * pow(temperature, 4) / 4. + a_ptr[6]) / ss->M_bar;
  ss->g0 = R_bar * temperature * (a_ptr[0] * (1 - log(temperature)) - a_ptr[1] * temperature / 2. - a_ptr[2] * pow(temperature, 2) / 6. - a_ptr[3] * pow(temperature, 3) / 12. - a_ptr[4] * pow(temperature, 4) / 20. + a_ptr[5] / temperature - a_ptr[6]) / ss->M_bar;
  ss->Pr = exp(ss->s0 / ss->R);

  return ss;

}
