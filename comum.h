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

struct parametros {
	int branch;
	int crate;
	int station;
	int subaddress;
	int function;
	int dataword;
};


typedef struct{ 
    short data;
	short qx;
} retorno;


const char *resposta(const char *status, const char *comando, const char *mensagem, const int data, const int qx);
void processarSequencia(const char *dados, SOCKET cliente);
int extrairParametros(const char *json, struct parametros *parametros);
retorno executar(int branch, int crate, int station, int subaddress, int function, int data);
void init();
void inhibt(int *valor);
int execute(int *funcao, int *subAddress, short *shortData);
#endif
