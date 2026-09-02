#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "comum.h"
#include "cJSON.h"

static int extrairInteiroDoObjeto(cJSON *objeto, const char *nome, int *valor) {
    cJSON *item;

    if (objeto == NULL || nome == NULL || valor == NULL) return 0;

    item = cJSON_GetObjectItem(objeto, nome);
    if (item == NULL || item->type != cJSON_Number) return 0;

    *valor = item->valueint;
    return 1;
}

static int extrairCrate(cJSON *objeto, int *valor) {
    cJSON *item;

    if (objeto == NULL || valor == NULL) return 0;

    item = cJSON_GetObjectItem(objeto, "crate");
    if (item == NULL) {
        item = cJSON_GetObjectItem(objeto, "create");
    }
    if (item == NULL || item->type != cJSON_Number) return 0;

    *valor = item->valueint;
    return 1;
}

int extrairParametros(const char *json, struct parametros *parametros) {
    cJSON *raiz;
    int ok;
    printf("\n[INFO] Extracao de parametros do JSON: %s\n", json);

    if (json == NULL || parametros == NULL) return 0;

    raiz = cJSON_Parse(json);
    if (raiz == NULL || raiz->type != cJSON_Object) {
        if (raiz != NULL) cJSON_Delete(raiz);
        return 0;
    }

    ok = extrairInteiroDoObjeto(raiz, "branch", &parametros->branch) &&
         extrairCrate(raiz, &parametros->crate) &&
         extrairInteiroDoObjeto(raiz, "station", &parametros->station) &&
         extrairInteiroDoObjeto(raiz, "subaddress", &parametros->subaddress) &&
         extrairInteiroDoObjeto(raiz, "function", &parametros->function) &&
         extrairInteiroDoObjeto(raiz, "data", &parametros->data);
        
    printf("\n[INFO] Extracao de parametros para a struct parametros: branch=%d, crate=%d, station=%d, subaddress=%d, function=%d, data=0x%04d\n", 
        parametros->branch, parametros->crate, parametros->station, parametros->subaddress, parametros->function, parametros->data);


    cJSON_Delete(raiz);
    return ok;
}