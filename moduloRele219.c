#include <stdio.h>
#include <string.h>
#include <conio.h>
#include "comum.h"
#include "esone.h"


int qx;
int branchAux = BRANCH;
int crateAux = CRATE;
int moduloRele219 = MODULO_RELE_219;

int execute(int *funcao, short *shortData, int *subAddress){
    cdreg(&ext, &branchAux, &crateAux, &moduloRele219, subAddress);
    cssa(funcao, &ext, shortData, &qx);
    return qx;
}

