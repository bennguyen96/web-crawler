#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>
#include "uriparse.h"



void format_request(char* buffer, char* file, char* h_name);
char** parse_anchors(char* response, int* size);
char* format_uri(char* string, char* crawled_from);