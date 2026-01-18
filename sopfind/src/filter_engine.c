#include "filter.h"
#include <stdlib.h>
#include <string.h>

void add_filter(FilterNode **head, void *data) {
    FilterNode *new_node = malloc(sizeof(FilterNode));
    if (new_node == NULL) {
        return;
    }
    
    new_node->data = data;
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

int evaluate_filters(FilterNode *head, PredicateFunc predicate, const char *path, const struct stat *st) {
    if (predicate == NULL) {
        return 0;
    }

    FilterNode *current = head;
    while (current != NULL) {
        int passed = predicate(path, st, current->data);
        if (passed == 0) {
            return 0;
        }
        current = current->next;
    }

    return 1;
}

void free_filters(FilterNode *head) {
    FilterNode *current = head;
    while (current != NULL) {
        FilterNode *next = current->next;
        free(current);
        current = next;
    }
}
