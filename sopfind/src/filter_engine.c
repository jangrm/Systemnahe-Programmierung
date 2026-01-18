#include "filter.h"
#include <stdlib.h>
#include <string.h>

// Forward declarations for filter functions
int filter_name(const char *path, const struct stat *st, void *data);
int filter_type(const char *path, const struct stat *st, void *data);

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

void parse_argv_filters(FilterNode **filter_head, int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-name") == 0) {
            if (i + 1 < argc) {
                char *name_pattern = malloc(strlen(argv[i + 1]) + 1);
                if (name_pattern != NULL) {
                    strcpy(name_pattern, argv[i + 1]);
                    add_filter(filter_head, (void *)name_pattern);
                }
                i++;
            }
        } else if (strcmp(argv[i], "-type") == 0) {
            if (i + 1 < argc) {
                char *type_char = malloc(sizeof(char));
                if (type_char != NULL) {
                    *type_char = argv[i + 1][0];
                    add_filter(filter_head, (void *)type_char);
                }
                i++;
            }
        }
    }
}
