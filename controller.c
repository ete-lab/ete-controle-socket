#include <stdio.h>
#include "comum.h"
#include "esone.h"

retorno executar(int branch, int crate, int station, int subaddress, int function, int data) {
    int qx;
    short shortData = (short)data;
    retorno retornoStruct;

    printf("\n[INFO] Executando branch %d crate %d station %d function %d subaddress %d data %04hx.\n",
        branch, crate, station, function, subaddress, shortData);
    cdreg(&ext, &branch, &crate, &station, &subaddress);
    cssa(&function, &ext, &shortData, &qx);
    retornoStruct.data = shortData;
    retornoStruct.qx = qx;
    printf("\n[INFO] Retorno da funcao %d: %d .\n", function, retornoStruct.data);
    printf("\n[INFO] Retorno da Qx: %d .\n", qx);
    return retornoStruct;
}