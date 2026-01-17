#include "filter.h"
#include <stdlib.h>
#include <string.h>

void add_filter(FilterNode **head, const char *data) {
    FilterNode *new_node = malloc(sizeof(FilterNode));
    if (new_node == NULL) {
        return;
    }
    
    new_node->data = malloc(strlen(data) + 1);
    if (new_node->data == NULL) {
        free(new_node);
        return;
    }
    
    strcpy(new_node->data, data);
    new_node->next = NULL;
    
    if (*head == NULL) {
        *head = new_node;
    } else {
        FilterNode *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}
