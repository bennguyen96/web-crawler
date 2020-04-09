#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char* website;
    char* crawled_from;
    struct node* next;
} llist;

llist* create_llist(char* website);

llist* insert_llist(llist* head, char* website);

//char* get_website(llist*head);

llist* pop_llist(llist* head);

