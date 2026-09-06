#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "main_header.h"


int extract_graphql_query(const char *body, char *output, size_t max_len) {
    const char *key = "\"query\"";
    char *start = strstr(body, key);
    if (!start) return 0;

    start = strchr(start + strlen(key), '"');
    if (!start) return 0;
    start++; 

    size_t i = 0;
    while (*start != '\0' && *start != '"' && i < max_len - 1) {
        if (*start == '\\' && *(start + 1) != '\0') {
            start++;
        }
        output[i++] = *start++;
    }
    output[i] = '\0';
    return 1;
}


void execute_graphql(const char *query, char *json_out, size_t max_len) {
    if (strstr(query, "hello") != NULL) {
        snprintf(json_out, max_len, "{\"data\":{\"hello\":\"World!\"}}");
    } else if (strstr(query, "usuario") != NULL) {
        snprintf(json_out, max_len, "{\"data\":{\"usuario\":{\"id\":1,\"nome\":\"Dev C\"}}}");
    } else {
        snprintf(json_out, max_len, "{\"errors\":[{\"message\":\"Query nao reconhecida\"}]}");
    }
}
