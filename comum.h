#ifndef COMUM_H
#define COMUM_H

extern int moduloRele219 = 9;
extern int moduloADCrap506 = 13;
extern int moduloADClen4022 = 4;
extern int moduloDAC1082 = 6;
extern struct camac_ext ext;
extern int branch = 0;
extern int crate = 0;

extern int totalBancos = 3;

void executarTesteModulos(int station_number);
void descarregarBancos(int banco[], int tamanho);
void levantarChave(int banco);
void baixarChave(int banco);
//void processarSequencia(const char dados, SOCKET cliente);
#endif