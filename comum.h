#ifndef COMUM_H
#define COMUM_H

#define MODULO_RELE_219 9
#define MODULO_ADC_RAP_506 13
#define MODULO_ADC_LENTO_4022 4
#define MODULO_DAC_1082 6
#define BRANCH 0
#define CRATE 0

extern struct camac_ext ext;

void levantarChave(int banco);
void baixarChave(int banco);
void init();
#endif
