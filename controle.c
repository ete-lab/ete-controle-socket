#include <winsock.h>
#include <stdio.h>
#include <string.h>
#include "comum.h"
#include "esone.h"

struct camac_ext ext;

// --- PROCESSADOR DE COMANDOS ---
void processarSequencia(const char *dados, SOCKET cliente) {
    char resposta[512];
    int set = 1;
    int clear = 0;

    printf("\r\n**** Comando recebido no processarSequencia.\nValor de dados: %s\n", dados);

    if (strstr(dados, "DESINIBIR") != NULL) {
        inhibt(&clear);

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
    else if (strstr(dados, "INIBIR") != NULL) {
        inhibt(&set);
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
    } else {
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

// --- PROGRAMA PRINCIPAL ---
int main() {
    WSADATA wsa;
    SOCKET servidor, cliente;
    struct sockaddr_in servidorAddr, clienteAddr;
    int addrLen;
    char buffer[1024];
    int bytesLidos;
    int true = 1;
    int false = 0;
    int retorno = 9;
    int state;
    addrLen = sizeof(clienteAddr);

    init(); //inicializa CAMAC

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Falha ao inicializar Winsock.\n");
        return 1;
    }

    servidor = socket(AF_INET, SOCK_STREAM, 0);
    if (servidor == INVALID_SOCKET) {
        printf("Falha ao criar socket.\n");
        WSACleanup();
        return 1;
    }

    servidorAddr.sin_family = AF_INET;
    servidorAddr.sin_addr.s_addr = INADDR_ANY;
    servidorAddr.sin_port = htons(8080);

    if (bind(servidor, (struct sockaddr *)&servidorAddr, sizeof(servidorAddr)) == SOCKET_ERROR) {
        printf("Erro no bind da porta 8080.\n");
        closesocket(servidor);
        WSACleanup();
        return 1;
    }

    listen(servidor, 3);
    printf("\nServidor de Hardware (CAMAC) rodando na porta 8080...\n");

    while (1) {
        cliente = accept(servidor, (struct sockaddr *)&clienteAddr, &addrLen);
        if (cliente == INVALID_SOCKET) {
            continue;
        }

        printf("Conexao recebida de um cliente.\n");

        memset(buffer, 0, sizeof(buffer));
        bytesLidos = recv(cliente, buffer, sizeof(buffer) - 1, 0);

        if (bytesLidos > 0) {
            if (buffer[bytesLidos - 1] == '\n') buffer[bytesLidos - 1] = '\0';
            if (buffer[bytesLidos - 1] == '\r') buffer[bytesLidos - 1] = '\0';
			printf("\nchamando processarSequencia");
            processarSequencia(buffer, cliente);
			printf("\nfinalizado processarSequencia\r\n");
        }

        closesocket(cliente);
    }

    closesocket(servidor);
    WSACleanup();
    return 0;
}
