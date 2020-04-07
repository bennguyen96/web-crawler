#include "crawler.h"

int main(int argc, char** argv){
	int sockfd, n;
	struct sockaddr_in serv_addr;
	struct hostent* server;
	
	if (argc < 2) {
		fprintf(stderr, "Please enter a URL to crawl.\n");
	}

	// retrieving server IP and port no

	server = gethostbyname(argv[1]);
	printf("%s", server->h_name);
	if (server == NULL) {
		fprintf(stderr, "ERROR, no such host\n");
		exit(0);
	}
	
	// initialising socket
	bzero((char*)&serv_addr, sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	
	bcopy(server->h_addr_list[0], (char*)&serv_addr.sin_addr.s_addr, server->h_length);

	serv_addr.sin_port = htons(PORT_NO);
	
	// create client socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	if (sockfd < 0) {
		perror("ERROR opening socket");
	}

	if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        	perror("ERROR connecting");
        	exit(0);
    	}
	
}
