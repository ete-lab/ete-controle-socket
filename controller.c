#include <stdio.h>
#include "comum.h"
#include "esone.h"

retorno executar(int branch, int crate, int station, int subaddress, int function, int dataword) {
    retorno retornoStruct;
    int qx;
    retornoStruct.data = (short)dataword;

    printf("\n[INFO] Executando branch %d crate %d station %d function %d subaddress %d data %04hx.\n",
        branch, crate, station, function, subaddress, retornoStruct.data);
    cdreg(&ext, &branch, &crate, &station, &subaddress);
    printf("\n[INFO] Executando funcao cssa %d com subaddress %d e data %04hx.\n", function, subaddress, retornoStruct.data);
    cssa(&function, &ext, &retornoStruct.data, &qx);
    printf("\n[INFO] Funcao %d executada com sucesso.\n", function);
    printf("\n[INFO] Retorno da Qx: %d .\n", retornoStruct.qx);
    retornoStruct.qx = qx;
    printf("\n[INFO] Retorno da funcao %d: %d .\n", function, retornoStruct.data);
    printf("\n[INFO] Retorno da Qx no struct: %d .\n", retornoStruct.qx);
    return retornoStruct;
}