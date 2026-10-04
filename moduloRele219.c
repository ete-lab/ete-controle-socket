#include <stdio.h>
#include <string.h>
#include <conio.h>
#include "comum.h"
#include "esone.h"


int branchAux = BRANCH;
int crateAux = CRATE;
int moduloRele219 = MODULO_RELE_219;

retorno retornoStrunct;

retorno execute(int *funcao, int *subAddress, short *shortData){
    retornoStrunct.data = *shortData;
    printf("\n[INFO] Executando funcao %d com subAddress %d e shortData %04hx .\n", *funcao, *subAddress, retornoStrunct.data);
    cdreg(&ext, &branchAux, &crateAux, &moduloRele219, subAddress);
    cssa(&funcao, &ext, &shortData, retornoStrunct.qx);
    printf("\n[INFO] Retorno da funcao %d: %d .\n", *funcao, retornoStrunct.data );
    printf("\n[INFO] Retorno da Qx : %d .\n", retornoStrunct.qx);
    return retornoStrunct;
}

