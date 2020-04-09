#include "crawler.h"

int main(int argc, char** argv){
    int sockfd, n;
    struct sockaddr_in server_addr;
    struct hostent* server;

    char* buffer = (char*) malloc(BUFFER_SIZE*sizeof(char));
    char* response = (char*) malloc(RESPONSE_SIZE*sizeof(char));
    char** parsed;
    int* array_size = (int*) malloc(sizeof(int));
    char* file = NULL;

    if (argc < 2) {
        fprintf(stderr, "Usage %s hostname.\n", argv[0]);
        exit(0);
    }

    // retrieving server IP
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr, "ERROR, no such host\n");
        exit(0);
    }
    // initialising server socket
    bzero((char*)&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    // copying ip address over to server_addr struct
    bcopy(server->h_addr_list[0], (char*)&server_addr.sin_addr.s_addr, server->h_length);
    // assigning portno for server_addr struct
    server_addr.sin_port = htons(PORT_NO);
    // create client socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(0);
    }

    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("ERROR connecting");
        exit(0);
    }
    // send HTTP request to server
    format_request(buffer, file, server->h_name);
    printf("%s", buffer);
//    sprintf(buffer, "GET / HTTP/1.0\r\n\r\n User-Agent: benn1\r\n Host: %s\r\n", server->h_name);
//    printf("%s", buffer);
    n = write(sockfd, buffer, BUFFER_SIZE);
    if (n < 0) {
        perror("ERROR writing to socket");
        exit(0);
    }

    bzero(buffer, BUFFER_SIZE);
    int size = 0;
    while((n = (read(sockfd, buffer, BUFFER_SIZE - 1))) != 0) {
        if (n < 0) {
            perror("ERROR reading from socket");
            exit(0);
        }
        size += BUFFER_SIZE;
        response = realloc(response, size);
        response[size - 1] = '\0';
        strcat(response, buffer);
        bzero(buffer, BUFFER_SIZE);
    }
//    printf("%s\n", response);
    parsed = parse_anchors(response, array_size);

//    parse urls and visit


    //free everything
    for (int i = 0; i < *array_size; ++i) {
        printf("%s\n", parsed[i]);
        free(parsed[i]);
    }
    free(buffer);
    free(response);
    free(parsed);
    free(array_size);
}
