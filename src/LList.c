#include "LList.h"

llist* create_llist(char* page) {
    llist* head = (llist*) malloc(sizeof(llist));
    assert(head);
    head->website = (char*) malloc(sizeof(char)*strlen(page));
    strcpy(head->website, page);
    head->next = NULL;
    return head;
}

llist* insert_llist(llist* head, char* page) {
    llist* next = (llist*) malloc(sizeof(llist));
    assert(next);
    next->website = (char*) malloc(sizeof(char)*strlen(page));
    strcpy(next->website, page);
    next->crawled_from = (char*) malloc(sizeof(char)*strlen(head->website));
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
    return temp;
}