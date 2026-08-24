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
    int subAddress;
    int f_write = 16;
    int f_execute = 25;
    short shortData = 0x0000;
    int retorno = 99;
    
    printf("Comando recebido no processarSequencia.\nValor de dados: %s\n", dados);

    if (strstr(dados, "DESCARREGAR_BANCOS") != NULL) {
      status = "sucesso";
      comando = "DESCARREGAR_BANCOS";
      mensagem = "Chave de descarga do banco acionada.";
    }
    if (strstr(dados, "CONECTAR_BANCOS") != NULL) {
      shortData = 0x1987;
      subAddress = 0;

      retorno = execute(&f_write, &subAddress, &shortData);
      printf("\n[INFO] Retorno na escrita: %d ", retorno);

      retorno = execute(&f_execute, &subAddress, &shortData);
      printf("\n[INFO] Retorno na escrita: %d \n", retorno);

      status = "sucesso";
      comando = "CONECTAR_BANCOS";
      mensagem = "Bancos Conectados.";
    }
    else if (strstr(dados, "CONECTAR_BANCO_VERTICAL") != NULL) {
      shortData = 0x0182;
      subAddress = 0;

      retorno = execute(&f_write, &subAddress, &shortData);
      printf("\n[INFO] Retorno na escrita: %d ", retorno);

      retorno = execute(&f_execute, &subAddress, &shortData);
      printf("\n[INFO] Retorno na escrita: %d \n", retorno);

      status = "sucesso";
      comando = "CONECTAR_BANCO_VERTICAL";
      mensagem = "Fonte vertical conectada.";
    }
    else if (strstr(dados, "CONECTAR_BANCO_TOROIDAL") != NULL) {
      status = "sucesso";
      comando = "CONECTAR_BANCO_TOROIDAL";
      mensagem = "Fonte toroidal conectada.";
    }
    else if (strstr(dados, "CONECTAR_BANCO_OMICO") != NULL) {
      status = "sucesso";
      comando = "CONECTAR_BANCO_OMICO";
      mensagem = "Fonte omico conectada.";
    }
    else if (strstr(dados, "ABORTAR") != NULL) {
      shortData = 0x0000;
      subAddress = 0;

      retorno = execute(&f_write, &subAddress, &shortData);
      printf("\n[INFO] Retorno na escrita: %d ", retorno);

      retorno = execute(&f_execute, &subAddress, &shortData);
      printf("\n[INFO] Retorno na escrita: %d \n", retorno);

      status = "sucesso";
      comando = "ABORTAR";
      mensagem = "Sistema abortado.";
    }
    else if (strcmp(dados, "") == 0) {
      status = "sucesso";
      comando = "FECHAR_PORTA";
      mensagem = "Porta fechada com sucesso";
    }
    else {
      status = "erro";
      comando = "Nao registrado.";
      mensagem = "Comando desconhecido";
    }
    sprintf(respostaHttp,
      "HTTP/1.1 %s\r\n"
      "Content-Type: application/json; charset=utf-8\r\n"
      "Connection: close\r\n"
      "\r\n"
      "%s",
      strcmp(status, "sucesso") == 0 ? "200 OK" : "400 Bad Request",
      resposta(status, comando, mensagem)
    );

    send(cliente, respostaHttp, (int)strlen(respostaHttp), 0);
}
