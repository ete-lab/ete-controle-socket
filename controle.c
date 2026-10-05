#include <winsock.h>
#include <stdio.h>
#include <string.h>
#include "comum.h"
#include "esone.h"
#include "cJSON.h"

struct camac_ext ext;

// --- PROGRAMA PRINCIPAL ---
int main()
{
    WSADATA wsa;
    SOCKET servidor, cliente;
    struct sockaddr_in servidorAddr, clienteAddr;
    int addrLen;
    char buffer[1024] = {0};
    char json[512] = {0};
    int bytesLidos;
    struct parametros parametros;
    retorno retornoStruct;
    char respostaHttp[1024];
    const char *corpoResposta;
    int valor = 0;
    char versao[] = "1.0.1-SNAPSHOT";
    // char *string_json;
    char *mensagemRetorno = "";
    char *statusRetorno = "";
    char *comandoRetorno = "desconhecido";
    addrLen = sizeof(clienteAddr);

    init(); // inicializa CAMAC

    printf("\nPrograma reles versao: %s\n", versao);
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("\n[ERROR] Falha ao inicializar Winsock.\n");
        return 1;
    }

    servidor = socket(AF_INET, SOCK_STREAM, 0);
    if (servidor == INVALID_SOCKET)
    {
        printf("\n[ERROR] Falha ao criar socket.\n");
        WSACleanup();
        return 1;
    }

    servidorAddr.sin_family = AF_INET;
    servidorAddr.sin_addr.s_addr = INADDR_ANY;
    servidorAddr.sin_port = htons(8080);

    if (bind(servidor, (struct sockaddr *)&servidorAddr, sizeof(servidorAddr)) == SOCKET_ERROR)
    {
        printf("\n[ERROR] Erro no bind da porta 8080.\n");
        closesocket(servidor);
        WSACleanup();
        return 1;
    }

    listen(servidor, 3);
    printf("\n[INFO] Servidor de Hardware (CAMAC) rodando na porta 8080...\n");

    while (1)
    {
        cliente = accept(servidor, (struct sockaddr *)&clienteAddr, &addrLen);
        if (cliente == INVALID_SOCKET)
        {
            continue;
        }

        printf("[INFO] Conexao recebida de um cliente.\n");

        memset(buffer, 0, sizeof(buffer));
        bytesLidos = recv(cliente, buffer, sizeof(buffer) - 1, 0);
        printf("\n[INFO] Bytes lidos: %d\n", bytesLidos);
        if (bytesLidos > 0)
        {
            // Garante que o bloco lido inicialmente é tratado como string
            buffer[bytesLidos] = '\0'; 

            printf("\n[INFO] Verificar necessidade de mais dados.\n");
            
            // Se for um POST e ainda não tiver a chave '{', busca o resto no socket
            if (strstr(buffer, "POST") != NULL && strstr(buffer, "{") == NULL)
            {
                char *proximo_bloco = buffer + bytesLidos;
                int espaco_restante = sizeof(buffer) - bytesLidos - 1;

                int maisBytes = recv(cliente, proximo_bloco, espaco_restante, 0);
                if (maisBytes > 0)
                {
                    bytesLidos += maisBytes;
                    buffer[bytesLidos] = '\0'; // Atualiza o fim real da string acumulada
                }
            }

            printf("\n[INFO] Total de bytes acumulados: %d\n", bytesLidos);

            extractJson(buffer, json);
            
            if (extrairParametros(json, &parametros))
            {
                retornoStruct = executar(
                    parametros.branch,
                    parametros.crate,
                    parametros.station,
                    parametros.subaddress,
                    parametros.function,
                    parametros.dataword
                );
                //status, comando, mensagem
                if(parametros.function >=0 && parametros.function < 16) {
                    comandoRetorno = "read";
                } else if(parametros.function >=16 && parametros.function < 25) {
                    comandoRetorno = "write";
                } else if(parametros.function == 25) {
                    comandoRetorno = "execute";
                } else {
                    comandoRetorno = "desconhecido";
                }
                if (retornoStruct.qx == 0) {
                    statusRetorno = "Erro Grave / No-X";
                    mensagemRetorno = "O módulo não respondeu (pode estar ausente ou desligado).";
                } else if(retornoStruct.qx == 1) {
                        statusRetorno = "Comando Aceito, Resposta Falsa";
                        mensagemRetorno = "O módulo existe e entendeu o comando, mas a operação lógica retornou falso.";
                    } else if(retornoStruct.qx == 3){
                            statusRetorno = "Sucesso";
                            mensagemRetorno = "Comando aceito (X=1) e operação realizada com sucesso (Q=1).";
                        } else {
                                statusRetorno = "Erro Desconhecido";
                                mensagemRetorno = "Erro desconhecido.";                    
                            }
                corpoResposta = resposta(statusRetorno, comandoRetorno, mensagemRetorno, retornoStruct.data, retornoStruct.qx);
            } else {
                corpoResposta = resposta("erro", "executar", "JSON invalido.", 0, retornoStruct.qx);
                }
            sprintf(respostaHttp,
                    "HTTP/1.1 %s\r\n"
                    "Content-Type: application/json; charset=utf-8\r\n"
                    "Connection: close\r\n"
                    "\r\n"
                    "%s",
                    retornoStruct.data < 0  || retornoStruct.data > 65535 ? "400 Bad Request" : "200 OK",
                    corpoResposta);
            send(cliente, respostaHttp, (int)strlen(respostaHttp), 0);
        }

        closesocket(cliente);
    }
    closesocket(servidor);
    WSACleanup();
    return 0;
}
