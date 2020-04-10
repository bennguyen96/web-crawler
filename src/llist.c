#include "llist.h"

llist* create_llist(char* page) {
    llist* head = (llist*) malloc(sizeof(llist));
    assert(head);
    head->website = (char*) malloc(sizeof(char)*(strlen(page)+1));
    strcpy(head->website, page);
    head->crawled_from = NULL;
    head->next = NULL;
    return head;
}

llist* insert_llist(llist* head, char* page) {
    llist* next = (llist*) malloc(sizeof(llist));
    assert(next);
    next->website = (char*) malloc(sizeof(char)*(strlen(page)+1));
    strcpy(next->website, page);
    next->crawled_from = (char*) malloc(sizeof(char)*(strlen(head->website)+1));
    strcpy(next->crawled_from, head->website);
    next->next = NULL;
    llist* temp = head;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = next;
    return head;
}

//char* get_website(llist* head) {
//    return head->website;
//}

llist* pop_llist(llist* head) {
    llist* temp = head->next;
    head->next = NULL;
    free(head->website);
    free(head->crawled_from);
    return temp;
}