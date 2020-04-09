#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <stdbool.h>
#include "io.h"
#include "LList.h"

#ifndef PORT_NO
#define PORT_NO 80
#endif
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1024
#endif
#ifndef RESPONSE_SIZE
#define RESPONSE_SIZE 1024
#endif