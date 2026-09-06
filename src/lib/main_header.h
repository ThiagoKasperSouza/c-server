#ifndef MAIN_HEADER_H
#define MAIN_HEADER_H

#define PORT 8080
#define BUFFER_SIZE 4096

// Resolver basico para gerar respostas GraphQL em JSON estatico
void execute_graphql(const char *query, char *json_out, size_t max_len);
// Extrai manualmente a string da query GraphQL enviada no JSON
int extract_graphql_query(const char *body, char *output, size_t max_len);
// Cria, configura, associa (bind) e coloca o socket em modo escuta (listen)
int connect_socket();
// Executa o loop principal de aceitacao de conexoes e processamento de requisicoes
void begin_loop(int server_fd);
#endif