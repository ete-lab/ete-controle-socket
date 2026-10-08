#include <stdio.h>
#include "comum.h"
#include "esone.h"

retorno executar(int branch, int crate, int station, int subaddress, int function, short dataword) {
    
    retorno retornoStruct;
    int qx;
    retornoStruct.data = dataword;

    printf("\n[INFO] Executando branch %d crate %d station %d function %d subaddress %d data %04hx.\n",
        branch, crate, station, function, subaddress, dataword);

    cdreg(&ext, &branch, &crate, &station, &subaddress);
    printf("\n[INFO] ext a : %d, n : %d, c : %d\n", ext.a, ext.n, ext.c);


    printf("\n[INFO] Executando funcao cssa %d com subaddress %d e data %04hx.\n", function, subaddress, dataword);
    cssa(&function, &ext, &dataword, &qx);
    printf("\n[INFO] Funcao %d executada com sucesso.\n", function);


    printf("\n[INFO] Retorno da Qx: %d .\n", qx);
    retornoStruct.qx = qx;
    printf("\n[INFO] Retorno da Qx no struct: %d .\n", retornoStruct.qx);

    retornoStruct.data = dataword;
    if(function == 16)
        printf("\n[INFO] Retorno da funcao %d: %04hx .\n", function, retornoStruct.data);
    else printf("\n[INFO] Retorno da funcao %d: %04hx .\n", function, retornoStruct.data);

    return retornoStruct;
}