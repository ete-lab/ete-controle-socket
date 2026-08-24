#include <stdio.h>
#include <string.h>
#include <conio.h>
#include "comum.h"
#include "esone.h"


int qx;
int branchAux = BRANCH;
int crateAux = CRATE;
int moduloRele219 = MODULO_RELE_219;
int retorno;

int execute(int *funcao, int *subAddress, short *shortData){
    printf("\n[INFO] Executando funcao %d com subAddress %d e shortData %04hx .\n", *funcao, *subAddress, *shortData);
    cdreg(&ext, &branchAux, &crateAux, &moduloRele219, subAddress);
    cssa(funcao, &ext, shortData, &qx);
    ctstat(&retorno);
    printf("\n[INFO] Retorno da funcao %d: %d .\n", *funcao, retorno);
    printf("\n[INFO] Retorno da Qx : %d .\n", qx);
    return retorno;
}

