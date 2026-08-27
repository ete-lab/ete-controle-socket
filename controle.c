#include <winsock.h>
#include <stdio.h>
#include <string.h>
#include "comum.h"
#include "esone.h"

struct camac_ext ext;

// --- PROGRAMA PRINCIPAL ---
int main() {
    WSADATA wsa;
    SOCKET servidor, cliente;
    struct sockaddr_in servidorAddr, clienteAddr;
    int addrLen;
    char buffer[1024];
    int bytesLidos;
    struct parametros parametros;
    int retorno;
    char respostaHttp[1024];
    const char *corpoResposta;
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
        printf("bytes lidos: %d\n", bytesLidos);
        if (bytesLidos > 0) {
            if (buffer[bytesLidos - 1] == '\n') buffer[bytesLidos - 1] = '\0';
            if (buffer[bytesLidos - 1] == '\r') buffer[bytesLidos - 1] = '\0';
            printf("Extrair parametros \n");
            if (extrairParametros(buffer, &parametros)) {
                retorno = executar(
                    parametros.branch,
                    parametros.crate,
                    parametros.station,
                    parametros.subaddress,
                    parametros.function,
                    parametros.data
                );
                corpoResposta = resposta("sucesso", "executar", "Comando executado.");
            } else {
                retorno = -1;
                corpoResposta = resposta("erro", "executar", "JSON invalido.");
            }

            sprintf(respostaHttp,
                "HTTP/1.1 %s\r\n"
                "Content-Type: application/json; charset=utf-8\r\n"
                "Connection: close\r\n"
                "\r\n"
                "%s",
                retorno == -1 ? "400 Bad Request" : "200 OK",
                corpoResposta
            );
            send(cliente, respostaHttp, (int)strlen(respostaHttp), 0);
        }

        closesocket(cliente);
    }

    closesocket(servidor);
    WSACleanup();
    return 0;
}
