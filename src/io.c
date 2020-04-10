#include "io.h"
static const char* PROTOCOL = "http:";
static const char* DOUBLE_SLASH = "//";
static const char SINGLE_SLASH = '/';

//struct* uri parse_io(char* domain);
void format_request(char* buffer, char* file, char* h_name) {
    if (!file) {
        sprintf(buffer, "GET / HTTP/1.1\r\nUser-Agent: benn1\r\nHost: %s\r\nConnection: close\r\n\r\n", h_name);
    }
    else {
        sprintf(buffer, "GET %s HTTP/1.1\r\nUser-Agent: benn1\r\nHost: %s\r\nConnection: close\r\n\r\n", file, h_name);
    }
}

char** parse_anchors(char* response, int* size) {

    // code referenced from https://stackoverflow.com/questions/1085083/regular-expressions-in-c-examples
    // author: Laurence Gonsalves
    regex_t regex;
    int return_value;
    regmatch_t matchptr[2];
    char* temp;
    int size_of_matches = 1;
    char** matches = malloc(sizeof(char*)*1000);
    /* Compile regular expression */
    return_value = regcomp(&regex, "<a[^>]+href=[[:space:]]\"([^>|\"]+)\"[^>]>", (REG_EXTENDED | REG_ICASE));
    if (return_value != 0) {
        fprintf(stderr, "Could not compile regex, error %d\n", return_value);
    }

    /* Execute regular expression */
    int size_of_substring = 0;
    while ((return_value = regexec(&regex, response, 2, matchptr, 0)) == 0) {
        // gets size of capture group
        size_of_substring = matchptr[1].rm_eo - matchptr[1].rm_so;
        // creating string to store capture group
        temp = (char*) malloc((size_of_substring + 1)*sizeof(char));
        // copying the string of size size_of_substring into temp
        strncpy(temp, &response[matchptr[1].rm_so], size_of_substring);
        // adding null terminator
        temp[size_of_substring] = '\0';
        // resizing original string by increasing its address by the size of the matched string
        response = response + matchptr[0].rm_eo;
        // resetting size_of_substring
        size_of_substring = 0;
        // adding the temp string to the array
        matches[size_of_matches - 1] = temp;
        // increasing size of array
        size_of_matches++;
    }

//    regfree(&regex);
    *size = size_of_matches - 1;
    return matches;
}

char* format_uri(char* website, char* crawled_from) {
    // iterating through all the illegal characters
    if (strstr(website, "?") != NULL) {
        return NULL;
    }
    if (strstr(website, "..") != NULL) {
        return NULL;
    }
    if (strstr(website, "#") != NULL) {
        return NULL;
    }
    if (strstr(website, "%") != NULL) {
        return NULL;
    }
    // check for trailing / and remove
    // size - 1 = null character so check size - 2
    int website_size = strlen(website) + 1;
    if (website[website_size - 2] == SINGLE_SLASH) {
        website[website_size - 2] = '\0';
    }
    if (crawled_from != NULL) {
        int size = strlen(crawled_from) + 1;
        if (crawled_from[size - 2] == SINGLE_SLASH) {
            crawled_from[size - 2] = '\0';
        }
    }
    // look for http protocol in string
    if (strstr(website, PROTOCOL) == NULL) {
        // create buffer to write fixed uri
        char* buffer = (char*) malloc(sizeof(char)*1024);
        // if not present, check for // after http:
        if (strstr(website, DOUBLE_SLASH) == website) {
            // append protocol
            sprintf(buffer, "%s%s", PROTOCOL, website);
            free(website);
            return buffer;
        }
        else {
            // check if it has any //, if it does then ignore
            if (strstr(website, DOUBLE_SLASH) == NULL) {
                return NULL;
            }
            // it is a relative link and use char* crawled_from to generate uri
            sprintf(buffer, "%s%s", crawled_from, website);
            free(website);
            return buffer;
        }
    }
    return website;
}