#ifndef COMUM_H
#define COMUM_H

#include <winsock.h>

#define MODULO_RELE_219 9
#define MODULO_ADC_RAP_506 13
#define MODULO_ADC_LENTO_4022 4
#define MODULO_DAC_1082 6
#define BRANCH 0
#define CRATE 0

extern struct camac_ext ext;

const char *resposta(const char *status, const char *comando, const char *mensagem);
void processarSequencia(const char *dados, SOCKET cliente);
void levantarChave(int banco);
void baixarChave(int banco);
void init();
void inhibt(int *valor);
int execute(int *funcao, int *subAddress, short *shortData);
#endif
