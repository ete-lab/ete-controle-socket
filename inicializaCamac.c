#include <stdio.h>
#include "comum.h"
#include "esone.h"

void init(){

    int true = ( 1 == 1);
    int false = ( 1 == 2);
    int retorno = 199;
    int estado;

    ccinit(); // comando obrigatorio de inicializacao do camac
    
    cccc(&ext); //limpa o crate
    
    ccci(&ext, &false); // false = bloqueio retirado. true = bloqueio ativado 
    ctci(&ext, &retorno);

    if(retorno) printf("\nDataway inhibit nabled - retorno = %d .", retorno);
    else printf("\nDataway inhibit disabled - retorno = %d .", retorno);
    ctstat(&estado);

    printf("\r\n\nValor do estado: %d .\n", estado);
    
}