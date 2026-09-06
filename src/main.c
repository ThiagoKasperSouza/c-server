#include <stdio.h>
#include <unistd.h>
#include "main_header.h"

int main() {
    int server_fd = connect_socket();
    begin_loop(server_fd);

    close(server_fd);
    return 0;
}