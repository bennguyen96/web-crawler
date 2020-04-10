#include "crawler.h"

int main(int argc, char** argv){
    // initialising variables
    int sockfd, n;
    struct sockaddr_in server_addr;
    struct hostent* server;
    char* buffer = malloc(BUFFER_SIZE*sizeof(char));

    char** parsed;
    int* array_size = malloc(sizeof(int));
    char* file = NULL;
    char* seen_array[MAX_PAGES];
    int size_seen_array = 0;

    if (argc < 2) {
        fprintf(stderr, "Usage %s hostname.\n", argv[0]);
        exit(0);
    }

    llist* list = create_llist(argv[1]);
        while (list != NULL) {
            char* response = malloc(100000*sizeof(char));
            // need to format uri properly
            // if string contains illegal characters/strings that we dont need to parse
            list->website = format_uri(list->website, list->crawled_from);
            if (list->website == NULL) {
                list = pop_llist(list);
                continue;
            }
            // check if formatted uri has been seen before
            int i = 0;
            for (i = 0; i < size_seen_array; ++i) {
                if (strcmp(list->website, seen_array[i]) == 0) {
                    continue;
                }
            }
            if (seen_array[i] != NULL) {
                if (strcmp(list->website, seen_array[i]) == 0) {
                    list = pop_llist(list);
                    continue;
                }
            }
            // external library function to parse fixed uri
            struct uri uri = {0};
            uriparse(list->website, &uri);
            file = uri.path;
            // retrieving server IP if exists
            server = gethostbyname(uri.host);
            if (server == NULL) {
                fprintf(stderr, "ERROR, no such host\n");
                list = pop_llist(list);
                continue;
            }

            // initialising server socket
            bzero((char *) &server_addr, sizeof(server_addr));
            server_addr.sin_family = AF_INET;
            // copying ip address over to server_addr struct
            bcopy(server->h_addr_list[0], (char *) &server_addr.sin_addr.s_addr, server->h_length);
            // assigning portno for server_addr struct
            server_addr.sin_port = htons(PORT_NO);

            // create client socket
            sockfd = socket(AF_INET, SOCK_STREAM, 0);

            if (sockfd < 0) {
                perror("ERROR opening socket");
                exit(0);
            }

            if (connect(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
                perror("ERROR connecting");
                exit(0);
            }

            format_request(buffer, file, server->h_name);
            fprintf(stdout, "%s\n", buffer);
            n = write(sockfd, buffer, BUFFER_SIZE);
            if (n < 0) {
                perror("ERROR writing to socket");
                exit(0);
            }

            bzero(buffer, BUFFER_SIZE);
            int size = 0;
            while ((n = (read(sockfd, buffer, BUFFER_SIZE - 1))) != 0) {
                if (n < 0) {
                    perror("ERROR reading from socket");
                    exit(0);
                }
                size += BUFFER_SIZE;
//                response = realloc(response, size);
//                response[size - 1] = '\0';
                strcat(response, buffer);
                bzero(buffer, BUFFER_SIZE);
            }
            parsed = parse_anchors(response, array_size);
            for (int i = 0; i < *array_size; ++i) {
                list = insert_llist(list, parsed[i]);
                free(parsed[i]);
            }
            free(response);
        // add to seen_array, seen_array will be free'd
        seen_array[size_seen_array++] = list->website;
        list = pop_llist(list);
        }

    free(buffer);
    free(parsed);
    free(array_size);
    exit(1);
}

