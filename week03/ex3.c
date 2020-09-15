#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next_node;
} node_t;

void print_list(node_t *head){
    node_t *current = head;

    while (current != NULL){
        printf("%d", current->data);
        current = current->next_node;
    }
}

void insert_node(node_t *head, int val){
    node_t *current = head;

    while (current != NULL){
        current = current->next_node;
    }

    int a;
    current->next_node = (node_t *) malloc(sizeof(node_t));
    current->next_node->data = val;
    current->next_node->next_node = NULL;
}


int delete_node(node_t *head)
{
    // return value: retval
    int retval = 0;

    // 1 item
    if (head->next_node == NULL){
        retval = head->data;
        free(head);
        return retval;
    }

    node_t *current = head;
    while (current->next_node->next_node != NULL) {
        current = current->next_node;
    }
    retval = current->next_node->data;
    free(current->next_node);
    current->next_node = NULL;
    return retval;
}

int main(){
    node_t *head = NULL;
    head = (node_t*) malloc(sizeof(node_t));
    if (head = NULL){
        return 1;
    }
    head->data = 1;
    head->next_node = (node_t*) malloc(sizeof(node_t));
    head->next_node->data = 3;
    head->next_node->next_node = NULL;
    print_list(head);
    delete_node(head);
    print_list(head);

    return 0;
}
