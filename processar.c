#include <winsock.h>
#include <stdio.h>
#include <string.h>
#include "comum.h"

// --- PROCESSADOR DE COMANDOS ---
void processarSequencia(const char *dados, SOCKET cliente) {
    char respostaHttp[1024];
    const char *status;
    const char *comando;
    const char *mensagem;

    printf("Comando recebido no processarSequencia.\nValor de dados: %s\n", dados);

    if (strstr(dados, "DESCARREGAR_BANCOS") != NULL) {
		status = "sucesso";
		comando = "DESCARREGAR_BANCOS";
		mensagem = "Chave de descarga do banco acionada.";
	}
    else if (strcmp(dados, "") == 0) {
		status = "sucesso";
		comando = "FECHAR_PORTA";
		mensagem = "Porta fechada com sucesso";
    }
    else {
		status = "erro";
		comando = "";
		mensagem = "Comando desconhecido";
    }

	sprintf(respostaHttp,
		"HTTP/1.1 %s\r\n"
        "Content-Type: application/json; charset=utf-8\r\n"
        "Connection: close\r\n"
        "\r\n"
        "%s",
        strcmp(status, "sucesso") == 0 ? "200 OK" : "400 Bad Request",
        resposta(status, comando, mensagem));

    send(cliente, respostaHttp, (int)strlen(respostaHttp), 0);
}
