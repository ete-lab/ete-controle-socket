#include <winsock.h>
#include <stdio.h>
#include <string.h>
#include "comum.h"

// --- PROCESSADOR DE COMANDOS ---
void processarSequencia(const char *dados, SOCKET cliente) {
    char resposta[512];

    printf("Comando recebido no processarSequencia.\nValor de dados: %s\n", dados);

    if (strstr(dados, "DESCARREGAR_BANCOS") != NULL) {
		sprintf(resposta,
			"HTTP/1.1 200 OK\r\n"
            "Content-Type: application/json; charset=utf-8\r\n"
            "Connection: close\r\n"
            "\r\n"
            "{\n"
            "  \"status\": \"sucesso\",\n"
            "  \"comando\": \"DESCARREGAR_BANCOS\",\n"
            "  \"mensagem\": \"Chave de descarga do banco acionada.\"\n"
            "}\n");

	}
    else if (strcmp(dados, "") == 0) {
        sprintf(resposta,
			"HTTP/1.1 200 OK\r\n"
            "Content-Type: application/json; charset=utf-8\r\n"
            "Connection: close\r\n"
            "\r\n"
            "{\n"
            "  \"status\": \"sucesso\",\n"
            "  \"comando\": \"FECHAR_PORTA\",\n"
            "  \"mensagem\": \"Porta fechada com sucesso\"\n"
            "}\n");
    }
	
    else {
        sprintf(resposta,
			"HTTP/1.1 400 Bad Request\r\n"
            "Content-Type: application/json; charset=utf-8\r\n"
            "Connection: close\r\n"
            "\r\n"
            "{\n"
            "  \"status\": \"erro\",\n"
            "  \"mensagem\": \"Comando desconhecido\"\n"
            "}\n");
    }

    send(cliente, resposta, (int)strlen(resposta), 0);
}
