#include <stdio.h>

const char *resposta(const char *status, const char *comando, const char *mensagem) {
    static char json[512];

    sprintf(json,
        "{\n"
        "  \"status\": \"%s\",\n"
        "  \"comando\": \"%s\",\n"
        "  \"mensagem\": \"%s\"\n"
        "}\n",
        status, comando, mensagem);

    return json;
}
