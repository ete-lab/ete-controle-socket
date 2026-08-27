#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "comum.h"

static int extrairInteiro(const char *json, const char *nome, int *valor) {
    char chave[64];
    const char *inicio;
    char *fim;
    long numero;

    sprintf(chave, "\"%s\"", nome);
    inicio = strstr(json, chave);
    if (inicio == NULL) return 0;

    inicio += strlen(chave);
    while (*inicio == ' ' || *inicio == '\t' || *inicio == '\r' || *inicio == '\n') inicio++;
    if (*inicio != ':') return 0;
    inicio++;
    while (*inicio == ' ' || *inicio == '\t' || *inicio == '\r' || *inicio == '\n') inicio++;

    numero = strtol(inicio, &fim, 10);
    if (fim == inicio) return 0;
    if (*fim != ' ' && *fim != '\t' && *fim != '\r' && *fim != '\n' &&
        *fim != ',' && *fim != '}') return 0;

    *valor = (int)numero;
    return 1;
}

int extrairParametros(const char *json, struct parametros *parametros) {
    if (json == NULL || parametros == NULL) return 0;

    return extrairInteiro(json, "branch", &parametros->branch) &&
           extrairInteiro(json, "crate", &parametros->crate) &&
           extrairInteiro(json, "station", &parametros->station) &&
           extrairInteiro(json, "subaddress", &parametros->subaddress) &&
           extrairInteiro(json, "function", &parametros->function) &&
           extrairInteiro(json, "data", &parametros->data);
}