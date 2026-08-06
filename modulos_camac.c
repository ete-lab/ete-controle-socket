#include <stdio.h>
#include <esone.h>
#include "comum.h"
#include <windows.h>

void executarTesteModulos(int n) {
    int b = 0, c = 0, a = 0, f16 = 1, f0 = 0;
    int sa = 0, q;
    short i, j, k;
    struct camac_ext ext;
 
    printf("Test for CFSA (Estacao: %d)...\n", n);

    ccinit();

    cdreg(&ext, &b, &c, &n, &sa);

    for (i = 0x0000; i <= 0x0004; i++) {
		k = i;
		printf("\nValor de i : %d\n", i);
        cssa(&f16, &ext, &k, &q);
        cssa(&f0, &ext, &j, &q);
        
        printf("valor de i = %d, valor de j = %d .\n", i, j);
        if (i != j) {
            printf("    ***Error: wrote 0x%04X Read back 0x%04X \n", i, j);
        }
		Sleep(100);
    }
    printf("Teste completed\n");
}