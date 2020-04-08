#include "io.h"

//struct* uri parse_io(char* domain);
//char* format_request(struct uri* url);

char** parse_anchors(char* response) {

    // code referenced from https://stackoverflow.com/questions/1085083/regular-expressions-in-c-examples
    // author: Laurence Gonsalves
    regex_t regex;
    int return_value;
    regmatch_t matchptr[2];
    char* temp;
    int size_of_matches = 1;
    char** matches = (char**) malloc(sizeof(char*));
    /* Compile regular expression */
    return_value = regcomp(&regex, "<a[^>]+href=\"([^>|\"]+)\">", (REG_EXTENDED | REG_ICASE));
    if (return_value != 0) {
        fprintf(stderr, "Could not compile regex, error %d\n", return_value);
    }

    /* Execute regular expression */
    int size_of_substring = 0;
    while ((return_value = regexec(&regex, response, 2, matchptr, 0)) == 0) {
        // creating array of strings - matches
        matches = (char**) realloc(matches, sizeof(char*)*size_of_matches);
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

    regfree(&regex);
    return matches;
}

