#include <stdio.h> // fornece printf e perror
#include <stdlib.h> //alocação de mem dinamica e exit
#include <string.h> // manipulacao de strings (strlen e memset)
#include <unistd.h> // read, write e close
#include <arpa/inet.h> // sockets
#include "main_header.h"


 const char *bad_req =  "HTTP/1.1 400 Bad Request\r\n"
                        "Content-Type: application/json\r\n"
                        "Content-Length: 36\r\n"
                        "\r\n"
                        "{\"errors\":[{\"message\":\"Bad Request\"}]}";


int connect_socket() {
    int server_fd;
    struct sockaddr_in address;

    // Cria o socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Erro ao criar o socket");
        exit(EXIT_FAILURE);
    }

    int opt = 1;

    //BIND DO SOCKET
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Erro ao associar o socket");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("Erro ao escutar");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    return server_fd;
}


void begin_loop(int server_fd) {
    int new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};

    printf("Servidor HTTP rodando em http://localhost:%d\n", PORT);

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
            perror("Erro ao aceitar conexão");
            continue;
        }

        memset(buffer, 0, BUFFER_SIZE);
        read(new_socket, buffer, BUFFER_SIZE - 1);

        char *body = strstr(buffer, "\r\n\r\n");

        // REQUISICAO AO GRAPHQL
        if (body) {
            body += 4; 

            char query_extracted[1024] = {0};
            char graphql_response[1024] = {0};

            if (extract_graphql_query(body, query_extracted, sizeof(query_extracted))) {
                execute_graphql(query_extracted, graphql_response, sizeof(graphql_response));

                char http_response[BUFFER_SIZE];
                snprintf(http_response, sizeof(http_response),
                        "HTTP/1.1 200 OK\r\n"
                        "Content-Type: application/json\r\n" 
                        "Content-Length: %zu\r\n"
                        "Access-Control-Allow-Origin: *\r\n"
                        "\r\n"
                        "%s",
                        strlen(graphql_response), graphql_response);

                write(new_socket, http_response, strlen(http_response));
            } else {
                write(new_socket, bad_req, strlen(bad_req));
            }
        }

        close(new_socket);
    }
}