#include <winsock.h>
#include <stdio.h>
#include <string.h>
#include "modulos_camac.h" // Inclui o nosso novo arquivo

// --- PROCESSADOR DE COMANDOS ---
void processarSequencia(const char *dados, SOCKET cliente) {
    char resposta[512];
    
    printf("Comando recebido no processarSequencia.\nValor de dados: %s\n", dados);

    if (strstr(dados, "TESTE_MODULOS") != NULL) {
		int station_para_teste = 4;
		printf("**Entrou no if de TESTE MODULOS");
        
		printf("** chama executarTesteModulos(4)");
        executarTesteModulos(station_para_teste);
        printf("** sai do modulo executarTesteModulos(4)");
		printf("** resposta = %s\n", resposta);
        sprintf(resposta, "OK! Teste de modulos executado na estacao %d.\n", station_para_teste);
    } 
    else if (strcmp(dados, "FECHAR_PORTA") == 0) {
        sprintf(resposta, "OK! Porta fechada.\n");
    }
    else {
        sprintf(resposta, "ERRO: Comando desconhecido.\n");
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

    addrLen = sizeof(clienteAddr);

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
    printf("Servidor de Hardware (CAMAC) rodando na porta 8080...\n");

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
			printf("chamando processarSequencia");
            processarSequencia(buffer, cliente);
			printf("finalizado processarSequencia");
        }

        closesocket(cliente);
    }

    closesocket(servidor);
    WSACleanup();
    return 0;
}