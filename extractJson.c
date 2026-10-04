#include <stdio.h>
#include <string.h>
/*
int extractJson(char *buffer, char *json) {
    const char *json_start; 
    
    printf("[INFO] Buffer recebido:\n%s\n", buffer);
    
    // Encontra o ponteiro para o início do JSON
    json_start = strstr(buffer, '{');

    if (json_start != NULL) {
        printf("[INFO] JSON Extraido com sucesso:\n%s\n", json_start);
        strncpy(json, json_start, 511);
        json[511] = '\0';
        printf("[INFO] JSON copiado para a variavel 'json':\n%s\n", json);
        return 1; // Sucesso
    } else {
        printf("[ERROR] JSON nao encontrado no buffer.\n");
    }

    return 0;
}

*/

int extractJson(char *buffer, char *json) {
    const char *json_start; 
    
    printf("\n[INFO] Buffer recebido (conteudo do corpo):\n%s\n", buffer);
    
    // Encontra o ponteiro para o início do JSON
    json_start = strstr(buffer, "{");

    if (json_start != NULL) {
        printf("[INFO] JSON Extraido com sucesso:\n%s\n", json_start);
        
        // Copia no máximo 511 bytes para evitar estouro em 'json[512]'
        strncpy(json, json_start, 511);
        
        // GARANTIA DE TERMINAÇÃO SEGURA: 
        // Força o último caractere do buffer a ser nulo caso a string seja maior que 511
        json[511] = '\0'; 
        
        printf("[INFO] JSON copiado para a variavel 'json':\n%s\n", json);
        return 1; // Sucesso
    } else {
        printf("[ERROR] JSON nao encontrado no buffer.\n");
    }

    return 0;
}

