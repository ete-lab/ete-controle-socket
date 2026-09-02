#include <stdio.h>
#include <string.h>

int extractJson(char *buffer, char *json) {
    const char *json_start; 
    
    printf("[INFO] Buffer recebido:\n%s\n", buffer);
    
    // Encontra o ponteiro para o início do JSON
    json_start = strchr(buffer, '{');

    if (json_start != NULL) {
        printf("[INFO] JSON Extraído com sucesso:\n%s\n", json_start);
        strcpy(json, json_start);
        printf("[INFO] JSON copiado para a variável 'json':\n%s\n", json);
        return 1; // Sucesso
    } else {
        printf("[ERROR] JSON não encontrado no buffer.\n");
    }

    return 0;
}
