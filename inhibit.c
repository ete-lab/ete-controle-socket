#include <stdio.h>
#include "comum.h"
#include "esone.h"
/*
CCCI com true: Define (set) o sinal de Inhibit. Os módulos ficam bloqueados.
CCCI com false: Limpa (reset) o sinal de Inhibit. Os módulos são liberados para trabalhar.
*/

void inhibt(int *valor){
    ccci(&ext, valor);
}

int inhibtStatus(){
    int estado;
    ctci(&ext, &estado);
    return estado;
}