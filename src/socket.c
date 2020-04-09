#include "socket.h"

create_socket()

int send_request(int sockfd, struct* hostent server, char* buffer, char* request_template) {
    sprintf(buffer, "GET %s / HTTP/1.1\r\n\r\n User-Agent: benn1\r\n Host: %s\r\n Connection: keep-alive", file, server->h_name);
    n = write(sockfd, buffer, sizeof(buffer));
    if (n < 0) {
        perror("ERROR writing to socket");
        exit(0);
}

int read_response(int sockfd, char* buffer) {

}