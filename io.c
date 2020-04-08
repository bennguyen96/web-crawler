#include "io.h"

//struct* uri parse_io(char* domain) {
//
//}

int main(int argc, char* argv[]){
    if (argc < 2) {
        return -1;
    }
    char* response = argv[1];
    char** words = parse_anchors(response);
    int i = 0;
//    while (words[i] != NULL) {
//        free(words[i]);
//    }
//    free(words);
    return 0;
}

//char* format_request(struct uri* url) {

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
    return_value = regcomp(&regex, "Index", (REG_EXTENDED | REG_ICASE | REG_NEWLINE));
    if (return_value != 0) {
        fprintf(stderr, "Could not compile regex, error %d\n", return_value);
        exit(1);
    }

    /* Execute regular expression */
    int size_of_substring = 0;
    while ((return_value = regexec(&regex, response, 2, matchptr, 0)) == 0) {
        matches = (char**) realloc(matches, sizeof(char*)*size_of_matches);
        size_of_substring = matchptr[1].rm_eo - matchptr[1].rm_so;
        temp = (char*) malloc((size_of_substring + 1)*sizeof(char));
        strncpy(temp, &response[matchptr[1].rm_so], size_of_substring);
        temp[size_of_substring] = '\0';
        response = response + matchptr[0].rm_eo;
        size_of_substring = 0;
        matches[size_of_matches - 1] = temp;
        size_of_matches++;
    }
    printf("%d", return_value);
    for (int i = 0; i < size_of_matches - 1; ++i) {
        printf("%s\n", matches[i]);
    }
    return matches;
}

