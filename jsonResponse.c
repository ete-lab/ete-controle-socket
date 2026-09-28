#include <stdio.h>

const char *resposta(const char *status, const char *comando, const char *mensagem, const int data, const int qx) {
    static char json[512];

    sprintf(json,
        "{\n"
        "  \"status\": \"%s\",\n"
        "  \"comando\": \"%s\",\n"
        "  \"mensagem\": \"%s\",\n"
        "  \"data\": %d,\n"
        "  \"qx\": %d\n"
        "}\n",
        status, comando, mensagem, data, qx);

    return json;
}
